# include "minitalk.h"

void handler (int signo, siginfo_t *info, void *more_info)
{
      (void) more_info; 
      static char c;
      static int bit;
      static pid_t client_pid;

      if (info -> si_pid) // accessing the pid of the sender process
          client_pid = info -> si_pid;

      // decoding the message
      if (SIGUSR1 == signo){
          c |= (0x80 >> bit);
      }
      else if (SIGUSR2 == signo){
          c &= ~(0x80 >> bit);
      }
      ++bit;

      if (CHAR_BIT == bit)
      {
          bit = 0;
          if ('\0' == c)
          {
                    write(STDOUT_FILENO, "\n", 1);
                    // send signal to client that message is receieved; 
                    Kill(client_pid, SIGUSR2);
                    // c = 0;
                    // return;
          } else {
                    write(STDOUT_FILENO, &c, 1);
          }
          c = 0;
      }

      // Send signal to client that server recieved the char, server is ready for another
      kill(client_pid, SIGUSR1);
}


int main (int ac, char **av)
{
          (void) av;
          if (ac != 1)
	{
		fputs("Usage: ./server\n", stderr);
		return (EXIT_FAILURE);
	}

          printf("Server pid id: %d\n", getpid()); // replace printf with ft_printf of your own

          Signal(SIGUSR1, handler, true);
          Signal(SIGUSR2, handler, true);
          while (1337)
          {
                    pause();
          }
          return (EXIT_SUCCESS);
}
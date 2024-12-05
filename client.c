# include "minitalk.h"

// the volatile qualifier forces the complier to read valie of g_server from the memory each time it is in the code
volatile sig_atomic_t g_server = BUSY;

void ack_handler (int signo)
{
          g_server = READY;
}

void end_handler (int signo)
{
          write(STDOUT_FILENO, "Sent\n", 5);
          exit(EXIT_SUCCESS);
}

void send_char (char c, pid_t server_pid)
{
          int bit;

          bit = 0;
          while (bit < CHAR_BIT )
          {
                    //Bitwise operations
                    if (c & (0x80 >> bit))
                              Kill(server_pid, SIGUSR1);
                    else
                              Kill(server_pid, SIGUSR2);
                    bit++;
                    while (g_server == BUSY)
                              usleep(42);
                    g_server = BUSY;
          }
}

int main (int ac, char **av)
{
          pid_t server_pid;
          char *message;
          int i;

          if (3 != ac)
          {
                    fputs("Usage = ./client <PID> \"Message\"\n", stderr);
                    exit(EXIT_FAILURE);
          }

          server_pid = atoi(av[1]);
          message = av[2];

          Signal(SIGUSR1, ack_handler, false);
          Signal(SIGUSR2, end_handler, false);

          i = 0;
          while (message[i])
                    send_char(message[i++], server_pid);
          send_char('\0', server_pid);

          return (EXIT_SUCCESS);
}
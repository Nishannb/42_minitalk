# include "minitalk.h"

void write_error(const char *message) {
    write(STDERR_FILENO, message, strlen(message));
}

void Signal (int signo, void *handler, bool use_siginfo)
{
          struct sigaction sa = {0};

          if (use_siginfo)
          {
                    sa.sa_flags = SA_SIGINFO;
                    sa.sa_sigaction = handler;
          }
          else
                    sa.sa_handler = handler;
          
          sigemptyset(&sa.sa_mask);
          sigaddset(&sa.sa_mask, SIGUSR1);
          sigaddset(&sa.sa_mask, SIGUSR2);
          
          if (sigaction(signo, &sa, NULL) < 0)
          {
                    write_error("Sigaction handler setup failed\n");
                    exit(EXIT_FAILURE);
          }

     
          
}

void Kill (pid_t server_pid, int signo)
{
          if (kill(server_pid, signo) < 0)
          {
                    write_error("Kill failed\n");
                    exit(EXIT_FAILURE);
          }
}
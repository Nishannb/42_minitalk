#ifndef MINITALK_H
#define MINITALK_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

enum {
          READY,
          BUSY
};

void Signal (int signo, void *handler, bool use_siginfo);
void Kill (pid_t server_pid, int signo);

#endif
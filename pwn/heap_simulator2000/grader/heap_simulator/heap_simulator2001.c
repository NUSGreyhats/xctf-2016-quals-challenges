#define PORT 8002

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>


#ifdef REAL_FLAG
#include "flags.h"
#include "drop_privs.h"
#else
#define FLAG_2001 "ok now try with the real one"
void drop_privileges() {}
#endif

#define error(x) (fputs(x "\n", stderr), exit(1))

#define BUFSIZE 200

static char you_lose[] = "YOU FAIL. GAME OVER!";
char *bye_msg = you_lose;
static char you_win[] = FLAG_2001;

int negchke(int n, const char *err) {
  if (n < 0) {
    perror(err);
    exit(1);
  }
  return n;
}

void recvline(int fd, char *buf, size_t len) {
    char c;
    int i = 0;
    while (recv(fd, &c, 1, 0) && i < len) {
        if (c == '\r' || c == '\n')
            break;
        buf[i] = c;
        i++;
    }
}

void xrecv(int fd, void *buf, size_t len) {
  if (recv(fd, buf, len, MSG_WAITALL) != len)
    error("short read");
}

void xwrite(int fd, const void *buf, size_t len) {
  if (write(fd, buf, len) != len)
    error("short write");
}

int client_fd;

void sendstr(const char *str) {
  unsigned int len = strlen(str);
  xwrite(client_fd, str, len);
}
#define writeend(...) (sendstr(__VA_ARGS__), exit(0))

void readfile(const char *path, char *buf) {
  int fd = negchke(open(path, O_RDONLY), "unable to open file for reading");
  int len = negchke(read(fd, buf, BUFSIZE-1), "read from local file failed");
  buf[len] = '\0';
}

int readint(void) {
    char buf[20];
    recvline(client_fd, buf, sizeof(buf));
    return atoi(buf);
}

/* temp printf */
char *tprintf(const char *fmt, ...) {
  static char buf[BUFSIZE];
  va_list ap;
  va_start(ap, fmt);
  vsnprintf(buf, BUFSIZE, fmt, ap);
  va_end(ap);
  return buf;
}

void say_bye() {
    writeend(bye_msg);
}


void handle_request(void) {
  void *allocs[100] = {0};
  uint32_t alloc_idx;

  sendstr(" **** WELCOME TO THE HEAP SIMULATOR 2001! ****\n\n");
  while (1) {
    sendstr("What would you like to do?\n");
    sendstr(" 1) Allocate memory\n");
    sendstr(" 2) Free memory\n");
    sendstr(" 3) Read some data\n");
    sendstr(" 4) Exit\n\n");

    int cmd = readint();
    uint16_t id;
    switch (cmd) {
        case 1:
            for (alloc_idx = 0; alloc_idx < sizeof(allocs) && allocs[alloc_idx] != NULL; ++alloc_idx) ;

            if (alloc_idx >= sizeof(allocs)) {
                sendstr("Run out of space, free something first!\n");
            } else {
                sendstr("Ok, how much memory do you want (in bytes)?\n");
                uint16_t bytes = readint();
                allocs[alloc_idx] = (void *)alloc(bytes);
                sendstr(tprintf("Allocated with ID = %d\n", alloc_idx));
            }
            dump_heap();
            break;
        case 2:
            sendstr("Please enter the ID of the alloc to free\n");
            id = readint();
            if (id < sizeof(allocs) && allocs[id] != NULL) {
                dealloc(allocs[id]);
                allocs[id] = NULL;
            } else {
                sendstr("Alloc not found\n");
            }
            dump_heap();
            break;
        case 3:
            sendstr("Please enter the ID of the alloc where to read data\n");
            id = readint();
            if (id < sizeof(allocs) && allocs[id] != NULL) {
                sendstr("Ready! Send the data\n");
                recvline(client_fd, allocs[id], 0x100);
            } else {
                sendstr("Alloc not found\n");
            }
            dump_heap();
            break;
        case 4:
            say_bye();
            exit(0);
            break;
        default:
            sendstr("What!?\n");
    };
  }

}

int main(void) {
  int ssock = negchke(socket(AF_INET6, SOCK_STREAM, 0), "unable to create socket");
  struct sockaddr_in6 addr = {
    .sin6_family = AF_INET6,
    .sin6_port = htons(PORT),
    .sin6_addr = IN6ADDR_ANY_INIT
  };
  int one = 1;
  negchke(setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)), "unable to set SO_REUSEADDR");
  negchke(bind(ssock, (struct sockaddr *)&addr, sizeof(addr)), "unable to bind");
  negchke(listen(ssock, 16), "unable to listen");

  //signal(SIGCHLD, SIG_IGN);

  while (1) {
    client_fd = negchke(accept(ssock, NULL, NULL), "unable to accept");
    pid_t pid = negchke(fork(), "unable to fork");
    if (pid == 0) {
      close(ssock);
      drop_privileges();
      handle_request();
      return 0;
    }
    close(client_fd);
  }
}

#include <bits/sockaddr.h>
#include <sys/socket.h>
#include <stddef.h>
#include <unistd.h>

struct server_add {
    const char addr[16];
};

int main(void) {
  int server = socket(AF_INET, SOCK_STREAM, 0);
  if (server == -1) {
    return 1;
  }

  struct server_add address = {
    2,0,
    0x1f, 0x90,
    0,0,0,0,0,0,0,0,0,0,0,0
  };

  if (bind(server, (struct sockaddr *)&address, sizeof address)) {
    return 2;
  }
  if (listen(server, 0)) {
    return 3;
  }

  while (1) {
  int fd = accept(server, NULL, NULL);
  if (fd <= 0) {
    continue;
  }

  int pid = fork();
  
  if (pid == 0) {
    char buf[1024];
    int size = 0;
    while ((size = read(fd,buf, 1024)) > 0) {
      write(fd, buf, size);
    }
    shutdown(fd, SHUT_RDWR);
   }
  }

  return 0;
}

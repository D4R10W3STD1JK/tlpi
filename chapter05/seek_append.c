#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {

  int fd;

  char buf[] = "Test of seek whith append flag";

  fd = open("test.txt", O_WRONLY | O_APPEND);

  if (fd == -1) {
    exit(EXIT_FAILURE);
  }

  if (lseek(fd, 0, SEEK_SET) == -1) {
    printf("Error on seek\n");
    exit(EXIT_FAILURE);
  }

  if (write(fd, buf, 28) == -1) {
    printf("Error or write");
    exit(EXIT_FAILURE);
  }

  if (close(fd) == -1) {
    exit(EXIT_FAILURE);
  }
}

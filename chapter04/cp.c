#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  
  int inputFd, outputFd;
  mode_t filePerms;
  char buf[BUF_SIZE];
  ssize_t numread;

  if (argc != 3) {
    exit(EXIT_FAILURE);
  }

  inputFd = open(argv[1], O_RDONLY);

  if (inputFd == -1) {
    exit(EXIT_FAILURE);
  }
  
  filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

  outputFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, filePerms);

  if (outputFd == -1) {
    exit(EXIT_FAILURE);
  }

  int hole_size = 0;

  while ((numread = read(inputFd, buf, BUF_SIZE)) > 0) {
    for (int i = 0; i < numread; i++) {
      if (buf[i] == '\0')
        hole_size++;
      else if (hole_size > 0) {
        lseek(inputFd, hole_size, SEEK_CUR);
        hole_size = 0;
      }
      else
        write(outputFd, buf+i, 1);
    }
  }
  if (-1 == close(inputFd)) {
    exit(EXIT_FAILURE);
  }
  if (-1 == close(outputFd)){
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}

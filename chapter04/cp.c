#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


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
  exit(EXIT_SUCCESS);
}


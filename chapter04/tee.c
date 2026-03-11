#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
  int opt;
  int numa = 0;
  

  while ((opt = getopt(argc, argv, ":a")) != -1) {
    switch (opt) {
      case 'a':
        numa++;
      break;
      case '?':
        exit(EXIT_FAILURE);
      break;
    }
  }
  
  int numargs = argc - optind;
  char *files[numargs];

  if (optind < argc) {
    for (int i = 0; i < numargs; i++) {
      files[i] = argv[optind + i];
    }
  }
  
  char buf[BUF_SIZE];
  ssize_t numread;

  int outputFD[numargs], openflags;
  mode_t filePerms;
  
  if (numa > 0) {
    openflags = O_WRONLY | O_CREAT | O_APPEND;
  }
  else {
    openflags = O_WRONLY | O_CREAT | O_TRUNC;
  }
  
  for (int i = 0; i < numargs; i++) {
    outputFD[i] = open(files[i], openflags, S_IRUSR | S_IWUSR);

    if (outputFD[i] == -1)
      exit(EXIT_FAILURE);
  }

  while ((numread = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    if (write(STDOUT_FILENO, buf, numread) != numread)
      exit(EXIT_FAILURE);

    for(int i = 0; i < numargs; i++) {
      if (write(outputFD[i], buf, numread) != numread)
        exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < numargs; i++)
    if (close(outputFD[i]) == -1)
      exit(EXIT_FAILURE);

}

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  bool argument = false;
  int fd, openflags;
  size_t size;
  int nbytes;

  if (argc == 3) {
    openflags = O_WRONLY | O_APPEND | O_CREAT;
  }
  else if (argc == 4 && argv[3][0] == 'x') {
    openflags = O_WRONLY | O_CREAT;
    argument = true;
  }
  else {
    exit(EXIT_FAILURE);
  }
  
  nbytes = atoi(argv[2]);

  fd = open(argv[1], openflags, S_IRUSR | S_IWUSR);

  if (fd == -1) {
    exit(EXIT_FAILURE);
  }
  
  for (size_t i = 0; i < nbytes; i++) {
    if (argument)
      lseek(fd, 0, SEEK_END);

    if (write(fd, "x", 1) != 1) {
      exit(EXIT_FAILURE) ;
    }
  }


  if (close(fd) == -1) {
    exit(EXIT_FAILURE);
  }

}

#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
    for (int i = 0; i < numargs; i++){
      printf("%s\n", files[i]);
    }
  }

}

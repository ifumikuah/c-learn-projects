/*Argument Parsing
Parse incoming arguments with unistd.h getopt*/

#include <unistd.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
  char* EXEC_NAME = argv[0];
  int extern optind;
  extern char *optarg;
  int opt;

  time_t* rtime;
  time(rtime);

  while ((opt = getopt(argc, argv, "hp:t")) != -1)
  {
    switch (opt)
    {
    case 'h':
      printf("Usage: %s [OPT] [ARG]\n\n", EXEC_NAME);
      printf("-p=STRING     Prints STRING\n");
      printf("-t            Prints current time\n");
      printf("-h            Help\n");
      break;
    case 'p':
      printf("%s\n", optarg);
      break;
    case 't':
      printf("%s", ctime(rtime));
      break;
    default:
      printf("Error: try %s -h\n", EXEC_NAME);
      return 1;
    }
  }
  return 0;
}
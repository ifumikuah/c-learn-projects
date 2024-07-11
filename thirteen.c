#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <regex.h>
#include <ctype.h>

int opt;
extern int optind;
extern char* optarg;

int unshift = 0;

void shiftop();

int main(int argc, char* argv[]) 
{
  char* EXEC_NAME = argv[0];
  while ((opt = getopt(argc, argv, "s:S:h")) != -1)
  {
    switch (opt)
    {
    case 's':
      unshift = 1;
      shiftop();
      break;
    case 'S':
      shiftop();
      break;
    case 'h':
      printf("Usage: %s [s:S:h] [STDIN]\n\n", EXEC_NAME);
      printf("-s  Unshift letter (shift left)\n");
      printf("-S  Shift letter (shift right)\n");
      printf("-h  Help\n");
      exit(0);
    default:
      printf("Error: try %s -h\n", EXEC_NAME);
      exit(1);
    }
  }

  printf("\n");
  return 0;
}

void shiftop() 
{
  int i = 0;
  while (optarg[i] != '\0')
  {
    if (isalpha(optarg[i]))
    {
      char is_upper = isupper(optarg[i]) ? 'A' : 'a';
      char letter = optarg[i];

      if (unshift)
        letter = is_upper + (optarg[i]-is_upper-13+26) % 26;
      else
        letter = is_upper + (optarg[i]-is_upper+13) % 26;

      printf("%c", letter);
    }
    else
      printf("%c", optarg[i]);
    i++;
  }
}
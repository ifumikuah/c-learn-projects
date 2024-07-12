/* Kitten
a minimal selfmade implementation of cat*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define PROG_NAME "kitten"
#define MAX_LINE_CHAR 150

int exit_status;

void help(int);
void concat(int, char**, bool, bool, bool);

int main(int argc, char** argv) {
  int opt;
  extern int optind;
  extern char* optarg;

  bool squeeze_blank = false;
  bool number_line = false;
  bool show_ends = false;

  while ((opt = getopt(argc, argv, "snEh")) != -1)
  {
    switch (opt)
    {
    case 's':
      squeeze_blank = true;
      break;
    case 'n':
      number_line = true;
      break;
    case 'E':
      show_ends = true;
      break;
    case 'h':
      help(exit_status);
      break;
    default:
      break;
    }
  }
 
  concat(argc, argv, squeeze_blank, number_line, show_ends);
  return exit_status;
}

void help(int status)
{
  printf("--coming soon\n");
  exit(status);
}

void concat(int argc, char** argv, bool squeeze_blank, bool number_line, bool show_ends)
{
  int numbering = 0;
  int fi = optind;
  while (fi < argc)
  {
    FILE* fp;
    fp = fopen(argv[fi], "r");
    if (fp == NULL)
    {
      printf("%s: file doesnt exist!", argv[fi]);
      exit_status = 1;
      fi++;
      continue;
    }

    int repeated_blank = 0;
    char* lbuf = malloc(MAX_LINE_CHAR*sizeof(char));
    while (fgets(lbuf, MAX_LINE_CHAR, fp) != NULL)
    {
      if (squeeze_blank && lbuf[0] == '\n')
      {
        if (repeated_blank > 0)
          continue;
        repeated_blank++;
      }
      else
        repeated_blank = 0;
      if (number_line)
      {
        char number_string[10];
        char* mbuf = malloc(MAX_LINE_CHAR*sizeof(char));
        sprintf(number_string, "%d  ", ++numbering);
        sprintf(mbuf, "%8s%s", number_string, lbuf);
        memcpy(lbuf, mbuf, MAX_LINE_CHAR);
        free(mbuf);
      }
      if (show_ends)
      {
        int len = strlen(lbuf);
        if (lbuf[len-1] == '\n')
        {
          lbuf[len-1] = '$';
          lbuf[len] = '\n';
          lbuf[len+1] = '\0';
        }
      }
      printf("%s", lbuf);
    }
    free(lbuf);
    fclose(fp);
    fi++;
  }
}
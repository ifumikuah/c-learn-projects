/* d_kitten -- dynamic version of kitten - dynamic version */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define PROG_NAME "d_kitten"
#define S_MAX_LINE_CHAR 150

int exit_status;

typedef struct dynamic
{
  FILE* file;
  int fline;
  int fchars;
  int lines[];
} DF;

DF* d_fopen(char*);
void d_fclose(DF*);
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
    default:
      exit_status = 1;
      printf("Error: try %s -h for usage", PROG_NAME);
      return exit_status;
    }
  }
 
  concat(argc, argv, squeeze_blank, number_line, show_ends);
  return exit_status;
}

DF* d_fopen(char* filename)
{
  FILE* f = fopen(filename, "r");
  int* lines_temp;
  lines_temp = malloc(0);

  int tl = 0;
  char buf[S_MAX_LINE_CHAR];
  while (fgets(buf, S_MAX_LINE_CHAR, f) != 0)
  {
    lines_temp = realloc(lines_temp, (tl+1)*sizeof(int));
    lines_temp[tl] = strlen(buf)+1;
    tl++;
  }
  rewind(f);

  int chars_temp = 0;
  while (fgetc(f) != EOF)
    chars_temp++;
  rewind(f);
  
  DF* o = malloc(tl*sizeof(int)+sizeof(DF));
  o->file = f;
  o->fline = tl;
  o->fchars = chars_temp;
  memmove(o->lines, lines_temp, o->fline*sizeof(int));

  free(lines_temp);
  return o;
}

void concat(int argc, char** argv, bool squeeze_blank, bool number_line, bool show_ends)
{
  int numbering = 0;
  int fi = optind;
  while (fi < argc)
  {
    DF* fp;
    fp = d_fopen(argv[fi]);
    if (fp->file == NULL)
    {
      printf("%s: file doesnt exist!", argv[fi]);
      exit_status = 1;
      fi++;
      continue;
    }

    int i = 0;
    int repeated_blank = 0;
    char* lbuf;
    do
    {
      lbuf = malloc(sizeof(char)*fp->lines[i]);
      lbuf = fgets(lbuf, fp->fchars, fp->file);
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
        char* mbuf = malloc(sizeof(char)*fp->lines[i]+10);
        lbuf = (char*) realloc(lbuf, sizeof(char)*fp->lines[i]+10);
        sprintf(number_string, "%d  ", ++numbering);
        sprintf(mbuf, "%8s%s", number_string, lbuf);
        memcpy(lbuf, mbuf, fp->lines[i]+10);
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
      free(lbuf);
    } while (fp->fline > ++i);

    d_fclose(fp);
    fi++;
  }
}

void help(int status)
{
  printf("d_kitten: minimal implementation of GNU utils 'cat' - dynamic version\n\n");
  printf("Usage: %s [OPT] [FILE]...\n\n", PROG_NAME);
  printf("OPT\n");
  printf("-s  suppress repeated empty output lines\n");
  printf("-n  number all output lines\n");
  printf("-E  display $ at end of each line\n");
  printf("-h  display help\n");
  exit(status);
}

void d_fclose(DF* d_file)
{
  fclose(d_file->file);
  free(d_file);
}
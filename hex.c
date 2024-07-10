/* Hex Converter */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

void help();
void tohex(int *in);
void todec(char *in);

enum MODE
{
  HEX = 1,
  DEC
};

int prefix = false;
int uppercase = false;
int mode;

char *EXEC_NAME;
int opt;
extern int optind;
extern char *optarg;

int main(int argc, char *argv[])
{
  EXEC_NAME = argv[0];

  while ((opt = getopt(argc, argv, "PCcx:d:h")) != -1)
  {
    switch (opt)
    {
    case 'P':
      prefix = true;
      break;
    case 'C':
      uppercase = true;
      break;
    case 'c':
      uppercase = false;
      break;
    case 'x':
      mode = HEX;
      int decimal = atoi(optarg);
      tohex(&decimal);
      break;
    case 'd':
      mode = DEC;
      todec(optarg);
      break;
    case 'h':
      help();
      exit(0);
      break;
    default:
      printf("Error: try %s -h\n", EXEC_NAME);
      return 1;
      break;
    }
  }

  printf("\n");
  return 0;
}

void help()
{
  printf("hex: convert signed value to hex, vice versa\n");
  printf("Usage: %s [OPT] [MODE] [VALUE]\n", EXEC_NAME);
  printf("Eligible OPT are [PCch]\n");
  printf("Eligible MODE are [xd]\n\n");
  printf("MODE\n");
  printf("-x=VALUE    Convert to hex\n");
  printf("-d=VALUE    Convert to decimal\n\n");
  printf("OPT\n");
  printf("-P          Enable prefix for hex\n");
  printf("-C          Uppercase format\n");
  printf("-c          Lowercase format\n");
  printf("-h          Help\n");
}

void tohex(int *in)
{
  char ucase = uppercase ? 'A' : 'a';
  char o[10];
  int i = 0;

  if (prefix)
    printf("0x");

  while (*in != 0)
  {
    int v = *in % 16;
    if (v > 9)
      o[i] = v - 10 + ucase;
    else
      o[i] = v + '0';
    *in /= 16;
    i++;
  }

  o[i] = '\0';
  for (; i > -1; i--)
      printf("%c", o[i]);
}

void todec(char *in)
{
  char ucase = uppercase ? 'A' : 'a';
  int sum = 0;
  int exp = 1;
  int len = strlen(in);

  while (--len > -1)
  {
    if (in[len] > '9')
      sum += exp * (in[len] - ucase + 10);
    else
      sum += exp * (in[len] - '0');
    exp *= 16;
  }

  printf("%d", sum);
}
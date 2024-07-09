/* Temperature Converter
USAGE: exec [DEST_UNIT] [SRC_UNIT] [SRC_VALUE]  */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

enum UNITS {CELC = 1, FAHR, KELV};

void fromcelc(int dest, double* val);
void fromfahr(int src, double* val);
void fromkelv(int dest, double* val);

int main(int argc, char* argv[]) {
  char* EXEC_NAME = argv[0];
  int opt;
  int extern optind;
  extern char *optarg;

  /* units, see enum */
  // int src;
  int dest;

  /* values in and out */
  double val = 0.0;

  /* Dest unit */
  while ((opt = getopt(argc, argv, "cfkh")))
  {
    switch (opt)
    {
    case 'c':
      dest = CELC;
      break;
    case 'f':
      dest = FAHR;
      break;
    case 'k':
      dest = KELV;
      break;
    case 'h':
      printf("Usage: %s [DEST_UNIT] [SRC_UNIT] [SRC_VALUE]\n\n", EXEC_NAME);
      printf("Flags that eligible as UNIT are [cfk]\n");
      printf("-c    Celcius\n");
      printf("-f    Fahrenheit\n");
      printf("-k    Kelvin\n");
      printf("-h    Help\n");
      return 0;
    default:
      printf("Error: try %s -h\n", EXEC_NAME);
      return 1;
    }
    break;
  }

  /* Src unit */
  while ((opt = getopt(argc, argv, "c:f:k:")) != -1)
  {
    val = atof(optarg);
    switch (opt)
    {
    case 'c':
      // src = CELC;
      fromcelc(dest, &val);
      break;
    case 'f':
      // src = FAHR;
      fromfahr(dest, &val);
      break;
    case 'k':
      // src = KELV;
      fromkelv(dest, &val);
      break;
    default:
      printf("Invalid unit: try %s -h\n", EXEC_NAME);
      return 1;
    }
  }
  
  printf("%lf\n", val);
  return 0;
}


/* Converts `*val` as celcius, to `(enum UNITS)dest` */
void fromcelc(int dest, double* val) {
  if (dest == FAHR)
    *val = 32 + (*val * 9) / 5;
  if (dest == KELV)
    *val += 273.15;
}

/* Converts `*val` as fahrenheit, to `(enum UNITS)dest` */
void fromfahr(int dest, double* val) {
  if (dest == CELC)
    *val = 5 * (*val - 32) / 9;
  if (dest == KELV)
    *val = 5 * (*val + 459.67) / 9;
}

/* Converts `*val` as kelvin, to `(enum UNITS)dest` */
void fromkelv(int dest, double* val) {
  if (dest == CELC)
    *val -= 273.15;
  if (dest == FAHR)
    *val = -459.67 + (*val * 9) / 5;
}
/* recursive decimal to binary converter */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void binary(int);

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    printf("pass decimal number as argument!!\n");
    return 1;
  }
  else
  {
    if (strcmp(argv[1], "0") == 0)
    {
      printf("0\n");
      return 0;
    }
    binary(atoi(argv[1]));
    printf("\n");
    return 0;
  }
}

void binary(int decimal)
{
  if (decimal == 0)
    return;
    
  binary(decimal/2);
  printf("%d", decimal%2);
}
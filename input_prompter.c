/*Input Prompter*/

#include <stdio.h>

#define MAX 25

int main() {
  char name[MAX];

  printf("Enter name: ");
  fgets(name, MAX, stdin);

  printf("%s", name);
  return 0;
}
#include <ctype.h>
#include <stdio.h>

int main() {
  int c;

  while ((c = getchar()) != EOF) {
    putchar(tolower(c));
  }

  return 0;
}

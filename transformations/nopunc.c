#include <stdio.h>

int main() {
  int c;

  while ((c = getchar()) != EOF) {
    if (c <= 32 || c >= 48 && c <= 57 || c >= 65 && c <= 90 ||
        c >= 97 && c <= 122) {
      putchar(c);
    }

    return 0;
  }
}

#include "all_transformations.h"

#include <ctype.h>
#include <stdio.h>

int is_vowel(int c) {
  c = tolower(c);
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void new_line(int* indent_counter, int indent_change) {
  *indent_counter += indent_change;
  puts("\r\n");
  for (int i = 0; i < 2 * *indent_counter; ++i) {
    putchar(32);
  }
}

void uppercase() {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(toupper(c));
  }
}

void lowercase() {
  int c;
  while ((c = getchar()) != EOF) {
    putchar(tolower(c));
  }
}

void noformat() {
  int c;
  while ((c = getchar()) != EOF) {
    if (c >= 32 || c == 0) {
      putchar(c);
    }
  }
}

void nopunc() {
  int c;
  while ((c = getchar()) != EOF) {
    if (c <= 32 || isalnum(c)) {
      putchar(c);
    }
  }
}

int oink() {
  int c;
  while ((c = getchar()) != EOF) {
    if (is_vowel(c)) {
      while (isalpha(c) || c == 39) {
        putchar(c);
        c = getchar();
      }
      printf("way");
    } else if (isalpha(c)) {
      char word_beginning[MAX_CONSONANTS];
      int i = 0;
      while (!is_vowel(c) && isalpha(c)) {
        if (i <= MAX_CONSONANTS) {
          word_beginning[i] = (char)tolower(c);
          ++i;
          c = getchar();
        } else {
          return 1;
        }
      }
      word_beginning[i] = '\0';
      while (isalpha(c) || c == 39) {
        putchar(c);
        c = getchar();
      }
      printf("%say", word_beginning);
    }
    if (c != EOF) {
      putchar(c);
    }
  }
  return 0;
}

int cleanjson() { return 0; }

int parsehtml() { return 0; }

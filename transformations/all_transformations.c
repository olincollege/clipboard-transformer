#include "all_transformations.h"

#include <ctype.h>
#include <stdio.h>

int is_vowel(int c) {
  c = tolower(c);
  return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

void new_line(int* indent_counter, int indent_change) {
  *indent_counter += indent_change;
  printf("\n");
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

int cleanjson() {
  int c;
  int num_indents = 0;
  int num_open_square_braces = 0;
  int num_open_curly_braces = 0;
  int open_quotes = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
      // white space or closed braces
      case 32:
      case 9:
      case 10:
      case 11:
      case 12:
      case 13:
      case 93:
      case 125:
        if (!open_quotes) break;

      default:
        putchar(c);
        break;
    }
    switch (c) {
      // open braces
      case 91:
        ++num_open_square_braces;
        if (!open_quotes) new_line(&num_indents, 1);
        break;

      case 123:
        ++num_open_curly_braces;
        if (!open_quotes) new_line(&num_indents, 1);
        break;

      // closed braces
      case 93:
        --num_open_square_braces;
        if (!open_quotes) {
          new_line(&num_indents, -1);
          putchar(c);
        }
        break;

      case 125:
        --num_open_curly_braces;
        if (!open_quotes) {
          new_line(&num_indents, -1);
          putchar(c);
        }
        break;

      // comma
      case 44:
        if (!open_quotes) new_line(&num_indents, 0);
        break;

      // colon
      case 58:
        if (!open_quotes) putchar(32);
        break;

      // quote
      case 34:
        if (open_quotes)
          open_quotes = 0;
        else
          open_quotes = 1;
        break;

      // backslash
      case 92:
        c = getchar();
        putchar(c);
        break;

      default:
        break;
    }
  }
  if (!num_indents && !num_open_square_braces && !num_open_curly_braces &&
      !open_quotes) {
    return 0;
  }
  return 1;
}

int parsehtml() { return 0; }

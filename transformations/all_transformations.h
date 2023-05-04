#pragma once

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_CONSONANTS 8

/**
 * Given an int representing a single character, check whether or not that
 * character is a vowel.
 *
 * @param c an int representing a character to check.
 * @return int 1 if c is a vowel, 0 if not.
 */
int is_vowel(int c);

/**
 * Given a number of idents, prints a new line with the appropriate number of
 * indents to standard output.
 *
 * @param indent_counter an int representing the current number of indentations
 * @param indent_change an int representing the change in number of indents to
 * apply
 */
void new_line(int* indent_counter, int indent_change);

/**
 * Given a stream of text from standard input, print the fully capitalized
 * version of the text to standard output.
 */
void uppercase();

/**
 * Given a stream of text from standard input, convert any uppercase letters in
 * the stream to lowercase and print the result to standard output.
 */
void lowercase();

/**
 * Given a stream of text from standard input, remove any formatting ASCII
 * characters (i.e. ASCII < 32). This includes newlines, tabs, etc. The result
 * gets printed to standard output.
 */
void noformat();

/**
 * Given a stream of text from standard input, remove any formatting characters
 * including tabs and new lines, and print the result to standard output.
 */
void nopunc();

/**
 * Given a stream of text from standard input, convert the text to pig latin.
 * Return 0 if successful and 1 if it fails.
 *
 * @return int 0 if the operation is successful and 1 if the conversion fails.
 */
int oink();

/**
 * Given a stream of text from standard input that is in JSON notation, add the
 * proper indentation to format it correctly. Return 0 if successful and 1 if it
 * fails or the input is written in a valid JSON format.
 *
 * @return int 0 if the operation if succesful and 1 if the formatting fails.
 */
int cleanjson();

/**
 * Given a stream of text from standard input that is in HTML notation, remove
 * the HTML tags and print the result to standard output. Two newlines are
 * inserted between paragraphs and sections.
 *
 * @return int 0 if the operation is successful and 1 if the formatting fails.
 */
int parsehtml();

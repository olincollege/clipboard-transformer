#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../transformations/all_transformations.h"

Test(uppercase, lowercase_input, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "lowercase");
  (void)fclose(stdin_file);
  uppercase();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("LOWERCASE");
}

Test(uppercase, mixed_input, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "MiXeD1nPut... with STUFF");
  (void)fclose(stdin_file);
  uppercase();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("MIXED1NPUT... WITH STUFF");
}

Test(lowercase, uppercase_input, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "UPPERCASE");
  (void)fclose(stdin_file);
  lowercase();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("uppercase");
}

Test(lowercase, mixed_input, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "This has 🐻🚀🎉 EMOJIs!!!!");
  (void)fclose(stdin_file);
  lowercase();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("this has 🐻🚀🎉 emojis!!!!");
}

Test(noformat, new_lines_tabs, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "Here is \n\tsome formatted \ntext.");
  (void)fclose(stdin_file);
  noformat();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("Here is some formatted text.");
}

Test(noformat, carriage_return, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "\t\t1. This \r\n2. That \r\n3. )^*Y)(UJ)$");
  (void)fclose(stdin_file);
  noformat();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("1. This 2. That 3. )^*Y)(UJ)$");
}

Test(nopunc, punctuated, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file,
                "Example: this function, A.K.A. \"nopunc()\", removes any "
                "punctuation.\n");
  (void)fclose(stdin_file);
  nopunc();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "Example this function AKA nopunc removes any punctuation\n");
}

Test(nopunc, emojis, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "It should also remove any emojis 🍕🎁🌞 :)");
  (void)fclose(stdin_file);
  nopunc();
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("It should also remove any emojis  ");
}

Test(is_vowel, vowels) {
  char* vowels = "aeiou";
  for (size_t i = 0; i < strlen(vowels); ++i) {
    char c = vowels[i];
    int res = is_vowel((int)c);
    cr_assert_eq(res, 1);
  }
}

Test(is_vowel, consonants) {
  char* consonants = "bcdfghjklmnpqrstvwxyz";
  for (size_t i = 0; i < strlen(consonants); ++i) {
    char c = consonants[i];
    int res = is_vowel((int)c);
    cr_assert_eq(res, 0);
  }
}

Test(is_vowel, other_characters) {
  char* chars = ")*=29Z\"🍒^@#ᗤ";
  for (size_t i = 0; i < strlen(chars); ++i) {
    char c = chars[i];
    int res = is_vowel((int)c);
    cr_assert_eq(res, 0);
  }
}

Test(oink, normal_text, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "This is a normal sentence.");
  (void)fclose(stdin_file);
  int ret = oink();
  cr_assert_eq(ret, 0, "oink returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("isthay isway away ormalnay entencesay.");
}

Test(oink, list, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file,
                "If the input is a list:\n- Pig Latin conversion\n- Still "
                "works\n- What can't it do?");
  (void)fclose(stdin_file);
  int ret = oink();
  cr_assert_eq(ret, 0, "oink returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "Ifway ethay inputway isway away istlay:\n- igpay atinlay onversioncay\n"
      "- illstay orksway\n- atwhay an'tcay itway oday?");
}

Test(new_line, add_indent, .init = cr_redirect_stdout) {
  int ind_counter = 0;
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file, "Some stuff");
  (void)fclose(stdin_file);
  new_line(&ind_counter, 1);
  new_line(&ind_counter, 0);
  new_line(&ind_counter, -1);
  new_line(&ind_counter, 2);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str("\n  \n  \n\n    ");
}

Test(cleanjson, valid_json, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file,
                "{\"name\":\"John Doe\",\"age\": 30,\"address\": \"123 Main "
                "St, Anytown, USA\",\"email\":   \"john.doe@example.com\"}");
  (void)fclose(stdin_file);
  int ret = cleanjson();
  cr_assert_eq(ret, 0, "cleanjson returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "{\n  \"name\": \"John Doe\",\n  \"age\": 30,\n  \"address\": \"123 Main "
      "St, Anytown, USA\",\n  \"email\": \"john.doe@example.com\"\n}");
}

Test(cleanjson, valid_json_long, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file,
                "{\"name\": \"John \\\"Smith\\\"\",\"age\": 42,\"isStudent\": "
                "true,\"grades\": [90, "
                "95, 87],\"address\": {\"street\": \"123 Main St\",\"city\": "
                "\"Anytown\",\"state\": \"CA\",\"zip\": \"12345\"}}");
  (void)fclose(stdin_file);
  int ret = cleanjson();
  cr_assert_eq(ret, 0, "cleanjson returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "{\n  \"name\": \"John \\\"Smith\\\"\",\n  \"age\": 42,\n  "
      "\"isStudent\": "
      "true,\n  \"grades\": [\n    90,\n    95,\n    87\n  ],\n  \"address\": "
      "{\n    \"street\": \"123 Main St\",\n    \"city\": \"Anytown\",\n    "
      "\"state\": \"CA\",\n    \"zip\": \"12345\"\n  }\n}");
}

Test(cleanjson, invalid_json, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file,
                "{\"user\": {{\"username\": \"mike_92\",\"email\": "
                "\"mike92@example.com\"}}");
  (void)fclose(stdin_file);
  int ret = cleanjson();
  cr_assert_eq(ret, 1, "cleanjson returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
}

Test(parsehtml, simple_html, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(
      stdin_file,
      "<!DOCTYPE html>\n<html>\n<head>\n<title>My "
      "Page</title>\n</head>\n<body>\n<h1>Welcome to my page!</h1>\n<p>This is "
      "a sample paragraph.</p>\n<ul>\n<li>Item 1</li>\n<li>Item "
      "2</li>\n<li>Item 3</li>\n</ul>\n</body>\n</html>");
  (void)fclose(stdin_file);
  int ret = parsehtml();
  cr_assert_eq(ret, 0, "parsehtml returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "My Page\n\nWelcome to my page!\n\nThis is a sample paragraph.\n\nItem "
      "1\n\nItem 2\n\nItem 3\n\n");
}

Test(parsehtml, complex_paragraph, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(
      stdin_file,
      "<h1 style=\"color: red;\">Climactic Battle</h1><p>In a <b>climactic "
      "battle</b>, Tito and Sparkle✨ defeated the <i>cake minions</i> and "
      "consumed the 🍦 ice cream sundae, gaining <u>infinite knowledge and "
      "power</u>.</p><p>They used their newfound abilities to turn Cosmic🚀 "
      "Munchies🤤 into a <em>utopia</em>, spreading delicious food and joy "
      "to all dimensions and creating an era of intergalactic "
      "peace.</p>");
  (void)fclose(stdin_file);
  int ret = parsehtml();
  cr_assert_eq(ret, 0, "parsehtml returned %d", ret);
  (void)fflush(stdout);
  (void)fclose(stdout);
  cr_assert_stdout_eq_str(
      "Climactic Battle\n\nIn a climactic battle, Tito and Sparkle✨ defeated "
      "the cake minions and consumed the 🍦 ice cream sundae, gaining infinite "
      "knowledge and power.\n\nThey used their newfound abilities to turn "
      "Cosmic🚀 Munchies🤤 into a utopia, spreading delicious food and joy "
      "to "
      "all dimensions and creating an era of intergalactic peace.\n\n");
}

Test(parsehtml, invalid_html, .init = cr_redirect_stdout) {
  FILE* stdin_file = cr_get_redirected_stdin();
  (void)fprintf(stdin_file,
                "<!DOCTYPE html><html><head><title>Short HTML "
                "Example</title></head><body<h1>Welcome to my "
                "website!</h1><p>Here is some example text.</p></body></html>");
  (void)fclose(stdin_file);
  int ret = parsehtml();
  cr_assert_eq(ret, 1, "parsehtml returned %d", ret);
}

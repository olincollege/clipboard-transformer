#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <criterion/redirect.h>
#include <ctype.h>
#include <stdio.h>

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

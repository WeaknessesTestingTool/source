// COMPILE: gcc test_deposit.c -I. -Wl,--wrap=deposit -lcmocka && ./a.out 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Mandatory headers needed by CMocka                                                                                                                                                         
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

//File under test
#include "bufferoverflow.c"

//MOCK

// Test functions
static void test_func_buf(void** state) {
  (void)state;  //unused variable                                                                                                                                                             

  char *errorLog[20];
  gets(errorLog);

  char stringCompare[20];
  strcat(stringCompare,"Error occurred on:");
  strcat(stringCompare, errorLog);
  
  char buf[BUFSIZ];
  
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  manipulate_error(errorLog);
  assert_string_equal(buf, stringCompare);
  freopen ("/dev/tty", "a", stdout);

  char ch = '-\n';
  strncat(errorLog, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");

  if (fileAddress != NULL) {
    // fprintf(fileAddress, "%d\n", errorLog);
    fputs (errorLog, fileAddress);
    fclose(fileAddress);
  }
  
}

const struct CMUnitTest tests[] = {
  cmocka_unit_test(test_func_buf)
};

int main(int argc, char** argv) {

  return cmocka_run_group_tests (tests, NULL, NULL);
}
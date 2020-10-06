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

char buf[BUFSIZ];
//MOCK

// Test functions
static void test_func_buf(void** state) {
  (void)state;  //unused variable                                                                                                                                                             

  char *errorLog = "Line 3";
  
  char stringCompare[20];
  strcat(stringCompare,"Error occurred on:");
  strcat(stringCompare, errorLog);
  
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  manipulate_error(errorLog);
  
  assert_string_equal(buf, stringCompare);
  freopen ("/dev/tty", "a", stdout);
  
}

const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_func_buf)
      };

int setup (void ** state){
    return 0;
}

int teardown (void ** state){
    memset (&buf, 0, sizeof(buf));
    return 0;
}

int main(int argc, char** argv) {
    
    return cmocka_run_group_tests (tests, NULL, NULL);
}
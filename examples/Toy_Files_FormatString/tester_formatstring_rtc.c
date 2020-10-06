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
#include "format_string.c"

// Test functions
static void test_printWrapper_format(void** state) {
  (void)state;  //unused variable  
  
  char *name = "%xteste";

  char buf[BUFSIZ];
  
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  printWrapper(name);
  assert_string_equal(buf, name);
  freopen ("/dev/tty", "a", stdout);
}

int setup (void ** state){
    return 0;
}

int teardown (void ** state){
    //memset (&response, 0, sizeof(response));
    return 0;
}

int main(int argc, char** argv) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_printWrapper_format)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
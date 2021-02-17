// COMPILE: gcc test_deposit.c -I. -Wl,--wrap=deposit -lcmocka && ./a.out 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Mandatory headers needed by CMocka                                                                                                                                                         
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include <ctype.h>

//File under test
#include "/home/raphael/Documentos/DoctoralFiles/Testing_Cmocka/Projects/Lede/scripts/config/confdata.c"

// Test functions
static void test_printWrapper_format(void** state) {
  (void)state;  //unused variable  
  
  // char *fmt[50];
  // gets(fmt);

  conf_filename = "name";
  conf_lineno = 0;
  char fmt[61] = "%xteste";
   
   
  char name2[256] = "name:0:warning: ";
  strcat(name2, fmt);
  strcat(name2, "\n");
   
  char buf[BUFSIZ];

  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  conf_warning(fmt, 0);
  freopen ("/dev/tty", "a", stdout);
  assert_string_equal(name2, buf);
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
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
#include "htdbm.c"
//#include "format_string.h"

// int __wrap_apr_dbm_firstkey(){
//     return EXIT_SUCCESS;
// }
//extern apr_status_t htdbm_list(void);

// Test functions
static void test_htdbm_list(void** state) {
  (void)state;  //unused variable  
  
  char str1[50] = "%xex";
  char dptr[] = "teste:";
  //gets(str1);
  //*str1 = "testeSTR1";
  
  strcat(dptr, str1);

  int dsize = strlen(dptr);

  char buf[BUFSIZ];
  
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);

  if (dptr)
    htdbm_list(dptr, dsize);
  
  char *name = memchr(dptr, ':', dsize);
  name = name + 1;

  
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
        cmocka_unit_test(test_htdbm_list)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
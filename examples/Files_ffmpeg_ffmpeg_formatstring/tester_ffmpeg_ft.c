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
#include "cmdutils.c"
  
char buf[BUFSIZ];

// Test functions
static void test_log_callback_help(void** state) {
  (void)state;  //unused variable  
  
  //\n = \"
  char *fmt[50];
  gets(fmt);

  int level = 0;
  void *ptr = NULL;  
  va_list vl;

  char ch = '-\n';
  strncat(fmt, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  if (fileAddress != NULL) {
    fputs (fmt, fileAddress);
    fclose(fileAddress);    
  }

  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  
  log_callback_help(ptr, level, fmt, vl);
    
  assert_string_equal(buf, fmt);
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
        cmocka_unit_test(test_log_callback_help)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
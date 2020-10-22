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
#include "command.c"

// Test functions
static void test_adb_forward_remove(void** state) {
  (void)state;  //unused variable  
  char *name[61];
  gets(name);  

  char ch = '-\n';
  strncat(name, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  int i;
  int len = strlen(name);

  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (name, fileAddress);
    fclose(fileAddress);    
   }

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
        cmocka_unit_test(test_adb_forward_remove)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
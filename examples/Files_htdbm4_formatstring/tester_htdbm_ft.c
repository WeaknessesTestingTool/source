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

  char str1[256];
  char dptr[256] = "teste:";
  gets(str1);
  //*str1 = "testeSTR1";
  
  strcat(dptr, str1);

  int dsize = strlen(dptr);

  char ch = '-\n';
  strncat(str1, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  int i;
  int len = strlen(str1);

  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (str1, fileAddress);
    fclose(fileAddress);    
  }

  char buf[BUFSIZ];
  
  freopen("/dev/null", "a", stderr);
  setbuf(stderr, buf);

  if (dptr)
    htdbm_list(dptr, dsize);
  
  char *name = memchr(dptr, ':', dsize);
  name = name + 1;

  printf("buf: %s\n", buf);
  printf("name: %s\n", name);

  assert_string_equal(buf, name);
  freopen ("/dev/tty", "a", stderr);
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
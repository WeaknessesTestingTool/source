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
#include "htdigest.c"
//#include "include/apr_dbm.h"

#define MAX_STRING_LEN 2
#define APR_SUCCESS 0
typedef struct apr_file_t apr_file_t;

//MOCK
int __wrap_apr_file_getc(char *ch, apr_file_t *thefile){
    *ch = "testet";
    return APR_SUCCESS;
}

// Test functions
static void test_get_line(void** state) {
  (void)state;  //unused variable  

  char line[3 * MAX_STRING_LEN];// = "test\n";
  gets(line);
  
char ch = '-\n';
  strncat(line, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  int i;
  int len = strlen(line);

  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (line, fileAddress);
    fclose(fileAddress);    
  }

  apr_file_t *f;
  int ret = 0;

  ret = get_line(line, sizeof(line), f);
  
  assert_int_equal(0,ret);
  //assert_string_equal(sTeste, subs);
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
        cmocka_unit_test(test_get_line)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
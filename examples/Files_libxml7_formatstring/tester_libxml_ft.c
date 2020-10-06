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
#include "libxml.c"
//#include "include/apr_dbm.h"

//char *sTeste;// = "teste:%xteste";

//MOCK
//
// Test functions
static void test_libxml_buildMessage(void** state) {
  (void)state;  //unused variable  
  
  char *dptr[10];
  gets(dptr);  

  char ch = '-\n';
  strncat(dptr, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  int i;
  int len = strlen(dptr);

  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (dptr, fileAddress);
    fclose(fileAddress);    
  }

  va_list arg_ptr;
  // gets(dptr);

  char *str = libxml_buildMessage(dptr, arg_ptr);
  printf("\nstr: %s",str);
  //asser_int_equal(1,1);
  assert_string_equal(dptr, str);
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
        cmocka_unit_test(test_libxml_buildMessage)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
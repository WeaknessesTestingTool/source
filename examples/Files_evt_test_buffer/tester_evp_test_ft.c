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
#include "evp_test.c"

#define apr_isspace(c) (isspace(((unsigned char)(c))))

//Mock

// Test functions
static void test_evp_test_list(void** state) {
  (void)state;  //unused variable  
  
  char **teste;
  char linebuf;
  gets(linebuf);

  printf("TESTE\n");
  
  teste = linebuf;

  char ch = '-\n';
  strncat(linebuf, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (linebuf, fileAddress);
    fclose(fileAddress);    
   }

  remove_space(teste);
  assert_int_equal(1, 1);
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
        cmocka_unit_test(test_evp_test_list)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
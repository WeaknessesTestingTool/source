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
#include "../../src/libomemo.c"
#include "../../src/libomemo_crypto.c"

// Test functions
void test_bundle_get_pep_node_name(void ** state) {
  (void) state;

  char * node_name = (void *) 0;
  char *ichar[250];
  gets(ichar);

  int i = atoi(ichar); 

  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  if (fileAddress != NULL) {
       // Let us use our fputc
    fprintf(fileAddress, "%d\n", i);
    fclose(fileAddress);    
  }

  char *str = "urn:xmpp:omemo:0:bundles:";
  char number[250];
  sprintf(number, "%s%i", str, i);
  
  assert_int_equal(omemo_bundle_get_pep_node_name(i, &node_name), 0);
  assert_string_equal(node_name, number);

  free(node_name);
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
        cmocka_unit_test(test_bundle_get_pep_node_name)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
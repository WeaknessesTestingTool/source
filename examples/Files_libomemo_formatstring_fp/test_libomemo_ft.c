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
uint8_t data[] = {0xB1, 0x6B, 0x00, 0xB5};

void test_bundle_export(void ** state) {
  (void) state;

  uint8_t * data_p = &data[0];
  size_t len = 4;
  uint32_t reg_id = 1337;

  char * publish[256];
  gets(publish);

  char ch = '-\n';
  strncat(publish, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");
  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (publish, fileAddress);
    fclose(fileAddress);    
   }

  omemo_bundle * bundle_p = (void *) 0;
  assert_int_equal(omemo_bundle_create(&bundle_p), 0);
  assert_int_not_equal(omemo_bundle_export(bundle_p, &publish), 0);

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
        cmocka_unit_test(test_bundle_export)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
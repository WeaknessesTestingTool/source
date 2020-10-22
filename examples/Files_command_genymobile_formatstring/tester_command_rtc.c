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

# define HANDLE void*
#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

#if !defined PRIu16 || 0
# undef PRIu16
# ifdef UINT16_MAX
#  define PRIu16 "u"
# endif
#endif
// typedef unsigned short uint16_t;
// typedef UINT16 uint16_t;


//MOCK
// typedef int apr_status_t;

// void __wrap_adb_execute(const char *serial, ...);
//     printf("adb");
// }

// Test functions
static void test_adb_forward_remove(void** state) {
  (void)state;  //unused variable  
  
  short local_port = 1;
  char *serial = "%xteste";

  char *buf = adb_forward_remove(serial, local_port);

  printf("Serial: %s\n", serial);
  printf("buf: %s\n", *buf);
  
  assert_int_equal(1,1);
  //assert_string_equal(dptr, str);
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
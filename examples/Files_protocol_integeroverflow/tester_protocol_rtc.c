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
#include "protocol.c"

#define APR_SUCCESS 0

// #define va_end(ap)              (void) 0
// #define va_start(ap, A)         (void) ((ap) = (((char *) &(A)) + (_bnd (A,_AUPBND))))

// typedef char *va_list;
typedef int apr_status_t;
typedef struct request_rec request_rec;

//Mock
int __wrap_apr_vformatter(int (*flush_func)(apr_vformatter_buff_t *b),
              apr_vformatter_buff_t *c, const char *fmt,
              va_list ap){
    return APR_SUCCESS;
}

int __wrap_buffer_output(){
  return APR_SUCCESS;
}

// int apr_status_t r_flush(apr_vformatter_buff_t *buff) {
//   return APR_SUCCESS;
// }

// Test functions
static void test_protocol(void** state) {
  (void)state;  //unused variable  
  int n = 0;
  // va_list va;
  apr_size_t written;
  const char *fmt;
  fmt = "teste fmt";

  request_rec *r;
  r = malloc(sizeof(request_rec));  
  
  r->connection = malloc(sizeof(conn_rec));
  //r->connection->aborted = 1;
  va_list va;
  
  n = ap_vrprintf(r, fmt, va);
  printf("N: %i\n", n);

  assert_int_equal(strlen(fmt), n);
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
        cmocka_unit_test(test_protocol)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
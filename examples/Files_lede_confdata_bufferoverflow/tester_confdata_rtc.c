// COMPILE: gcc test_deposit.c -I. -Wl,--wrap=deposit -lcmocka && ./a.out 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Mandatory headers needed by CMocka                                                                                                                                                         
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include <ctype.h>

#define APR_SUCCESS 0

//File under test
#include "/home/raphael/Documentos/DoctoralFiles/Testing_Cmocka/Projects/Lede/scripts/config/confdata.c"

//mock
int __wrap_sym_lookup(const char *name, int flags){
  return APR_SUCCESS;
}

void __wrap_sym_calc_value(struct symbol *sym){
  return APR_SUCCESS;
}

char * __wrap_sym_get_string_value(struct symbol *sym){
  return "y";
}

// Test functions
static void test_printWrapper_format(void** state) {
  (void)state;  //unused variable  
  
  // char *fmt[50];
  // gets(fmt);

  char fmt[256] = "arch/$ARCH/defconfig";
   
   
  
  char *name = conf_expand_value(fmt);
  
  assert_true(1);
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
        cmocka_unit_test(test_printWrapper_format)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
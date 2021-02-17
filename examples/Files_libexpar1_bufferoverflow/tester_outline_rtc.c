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

//File under test
#include "/home/raphael/Documentos/DoctoralFiles/Testing_Cmocka/Projects/libexpat/expat/examples/outline.c"

typedef char XML_Char;

// Test functions
static void test_printWrapper_format(void** state) {
  (void)state;  //unused variable  
  
   const char **attr;
  
   char *name = "%xteste";
   
   char name2[256];
   strcpy(name2, name);
   strcat(name2, "\n");
   
   char buf[BUFSIZ];
  
   freopen("/dev/null", "a", stdout);
   setbuf(stdout, buf);
   start("teste", name, attr);
   freopen ("/dev/tty", "a", stdout);
   assert_string_equal(buf, name2);
   
   
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
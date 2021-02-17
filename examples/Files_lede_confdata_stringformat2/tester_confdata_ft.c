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
#include "/home/raphael/Documentos/DoctoralFiles/Testing_Cmocka/Projects/Lede/scripts/config/confdata.c"

//mock
void __wrap_show_textbox(int i, char *s, int x, int y){
  printf("TESTE\n");
}

// Test functions
static void test_printWrapper_format(void** state) {
  (void)state;  //unused variable  

  char *name[256];
  gets(name);
  char *fmt = "configuration written to %s";
  
  char name2[256] = "#\n# configuration written to ";
  strcat(name2, name);
  strcat(name2, "\n#\n");

  char ch = '-\n';
  strncat(name, &ch, 1);
  FILE *fileAddress;
  fileAddress = fopen("log_afl.txt", "a");

  if (fileAddress != NULL) {
       // Let us use our fputc
    fputs (name, fileAddress);
    fclose(fileAddress);    
   }

  char buf[BUFSIZ];
  
  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  conf_message(_(fmt), name);
  freopen ("/dev/tty", "a", stdout);
  printf("%s\n", buf);
  assert_string_equal(name2, buf);
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
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
#include "race_condition.c"
//#include "include/apr_dbm.h"

#define MAXCHAR 1000
#define LSIZ 128 
#define RSIZ 10

//MOCK
// int __wrap_apr_file_getc(char *ch, apr_file_t *thefile){
//     *ch = "testet";
//     return APR_SUCCESS;
// }

// Test functions
static void test_startProcess(void** state) {
  (void)state;  //unused variable  

  char *strP = "output from parent\n";
  char *strC = "output from child\n";
    
  FILE *fileW;
  fileW = freopen("file.txt", "w+", stdout);
  startProcess(strC, strP);
  freopen ("/dev/tty", "a", stdout);
  
  FILE *fileR;
  char str[MAXCHAR];
  fileR = fopen("file.txt", "r");
  if (fileR == NULL){
    printf("Could not open file");
  }
  
  int i = 0;
  char line[RSIZ][LSIZ];

  while (fgets(line[i], LSIZ, fileR)){
    line[i][strlen(line[i]) - 1] = '\0';
    i++;
  }

  int tot = i;
  char *str1;
  char *str2;
  // printf("\n The content of the file are : \n");    
    for(i = 0; i < tot; ++i){
        if(i == 0){
          str1 = line[i];
        } else if (i == 1){
          str2 = line[i];
        }
    }
  printf("\n");
  
  //strcat(str1, "\n");
  //strcat(str2, "\n");
  
  // printf("str1: %s\n", str1);
  // printf("str2: %s\n", str2);
  
  assert_string_equal("output from parent", str1);
  //assert_string_equal("output from child", str2);
  
  fclose(fileW);
  fclose(fileR);
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
        cmocka_unit_test(test_startProcess)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
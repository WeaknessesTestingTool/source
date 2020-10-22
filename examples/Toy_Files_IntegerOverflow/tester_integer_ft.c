// COMPILE: gcc test_deposit.c -I. -Wl,--wrap=deposit -lcmocka && ./a.out 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
// Mandatory headers needed by CMocka                                                                                                                                                         
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

//File under test
#include "integer.c"

int i = 0;
int sum = 0;
int cont = 0;

//This is our wrapper, for the purpose of testing only
//MAX shor 32768

int __wrap_getMonthlySales(int month){
    int number = 0;
    int first;
    ++cont;

    if(cont < 2){
      scanf("%d\n", &first);
      number = first;
    } else {
      number = first + 100; 
    }
    sum = sum + number;

    FILE *fileAddress;
    fileAddress = fopen("log_afl.txt", "a");

    if (fileAddress != NULL) {
      if(cont <= 2){
        fprintf(fileAddress, "%d,", number);    
      } else {
        fprintf(fileAddress, "%d\n", number);
      }
      fclose(fileAddress);
    }
    
    return number;
}

float __wrap_calculateRevenueForQuarter(short quarterSold){
  i = quarterSold;
  return EXIT_SUCCESS;
}

void saveFirstQuarterRevenue(float quarterRevenue){}

// Test functions
static void test_int_overflow(void** state) {
  (void)state;  //unused variable                                                                                                                                                             
  determineFirstQuarterRevenue();
  assert_int_equal(i, sum);
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
        cmocka_unit_test(test_int_overflow)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
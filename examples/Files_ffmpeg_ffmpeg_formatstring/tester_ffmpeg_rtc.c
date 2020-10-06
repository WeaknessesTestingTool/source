// COMPILE: gcc test_deposit.c -I. -Wl,--wrap=deposit -lcmocka && ./a.out 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Mandatory headers needed by CMocka                                                                                                                                                         
#include <stdbool.h>
#include <stdarg.h>
#include <setjmp.h>
#include <cmocka.h>

#include <inttypes.h>
extern int do_benchmark_all;
int do_benchmark_all  = 1;

#define AV_LOG_INFO     32

//File under test
#include "ffmpeg.c"


//char buf[BUFSIZ];
  
//Moccked functions
// void __wrap_av_log(void* avcl, int level, const char *fmt, ...){
//     va_list vl;
//     va_start(vl, fmt);
//     av_vlog(avcl, level, fmt, vl);
//     va_end(vl);
// }

int64_t av_gettime_relative(void){
    return 10;
}

static BenchmarkTimeStamps __wrap_get_benchmark_time_stamps(void){
    BenchmarkTimeStamps time_stamps = { av_gettime_relative() };
    
    time_stamps.user_usec = time_stamps.real_usec = time_stamps.sys_usec = 1;
    
    return time_stamps;
}

// Test functions
static void test_update_benchmark(void** state) {
  (void)state;  //unused variable  
  
  char buf[1024];

  //\n = \"
  char *fmt = "%xex";
  // int level = 0;
  // void *ptr = NULL;  
  // va_list vl;

  freopen("/dev/null", "a", stdout);
  setbuf(stdout, buf);
  
  update_benchmark(fmt);
  printf("buf: %s\n", buf);
  printf("fmt: %s\n", fmt);
  //assert_int_equal(1, 1);
  assert_string_equal(buf, fmt);
  freopen ("/dev/tty", "a", stdout);

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
        cmocka_unit_test(test_update_benchmark)
    };
    
    int count_fail_tests = 
    cmocka_run_group_tests (tests, setup, teardown);

    return count_fail_tests;
}
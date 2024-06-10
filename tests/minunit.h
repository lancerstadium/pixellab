#undef CONFIG_NO_DEBUG
#ifndef _Minunit_h_
#define _Minunit_h_

#include <stdio.h>
#include <stdlib.h>
#include <utils/dbg.h>
#include <time.h>

// 1e3: us, 1e6: ms, 1e9: s
#define MU_TIMESCALE 1e6

#define mu_suite_start() char *message = NULL

#define mu_time_start() \
    clock_gettime(CLOCK_MONOTONIC, &start_time); \

#define mu_time_end(scale) \
    clock_gettime(CLOCK_MONOTONIC, &end_time); \
    time_scale = (scale == 1e3) ? "us" : (scale == 1e6) ? "ms" : "s"; \
    time_taken = ((end_time.tv_sec - start_time.tv_sec) + (end_time.tv_nsec - start_time.tv_nsec) / scale); \
    time_total_taken += time_taken; \

#define mu_assert(test, message) if (!(test)) { mu_msg("assert fail: " _RED("%-25s"), #test); log_err(message); return message; }
#define mu_cnt_res(res) ((res == NULL) ? (tests_pass++) : (tests_fail++))
#define mu_run_res(res) ((res == NULL) ? _GREEN("PASS") : _RED("FAIL"))
#define mu_msg(...) \
    do {\
        char message[64]; \
        snprintf(message, 64, ARG_FIRST(__VA_ARGS__) ARG_OTHER(__VA_ARGS__)); \
        printf("│  │ " _YELLOW("msg: ") "%-38s │\n", message); \
    } while(0)

#define mu_run_test(test) \
    debug("\n──────%s", " Sub: " _BLUE(#test)); \
    mu_time_start(); \
    message = test(); \
    tests_run++; \
    mu_cnt_res(message); \
    mu_time_end(MU_TIMESCALE); \
    printf("│  ├── " _MAGENTA("%-2d ") _BLUE("%-18s") _CYAN("%12.4f %2s") " %s │\n", tests_run, #test, time_taken, time_scale, mu_run_res(message));\
    debug("total exec %.3f %2s", time_taken, time_scale); \
    if (message) return message;

#define RUN_TESTS(name) \
    int main(int, char *argv[]) {\
    debug("\n\n────── Run: " _BLUE("%s"), argv[0]);\
    printf("┌────────────────────────────────────────────────┐\n");\
    printf("│ Test: " _BLUE("%-40s") " │\n", argv[0]);\
    char *result = name();\
    printf("│ Sum: " _MAGENTA("%-2d ") "[%2d " _GREEN("PASS") " %2d " _RED("FAIL") "] " _CYAN("%12.4f %2s") " %s │\n", tests_run, tests_pass, tests_fail, time_total_taken, time_scale, mu_run_res(result));\
    printf("├────────────────────────────────────────────────┤\n");\
    exit(result != 0);\
}


static int tests_run = 0;
static int tests_fail = 0;
static int tests_pass = 0;
static struct timespec start_time;
static struct timespec end_time;
static double time_taken;
static double time_total_taken = 0;
static char* time_scale = NULL;

#endif
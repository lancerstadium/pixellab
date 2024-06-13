#ifndef _UTIL_SOB_H_
#define _UTIL_SOB_H_


// ==================================================================================== //
//                                       Include
// ==================================================================================== //

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif

// ==================================================================================== //
//                                    macro: SOB Config (SOB)
// ==================================================================================== //

// #define SOB_CL_OFF
// #define SOB_DBG_OFF
// 1e3: us, 1e6: ms, 1e9: s
#define SOB_UT_TIMESCALE 1e6
// 1: Open assert message, 0: No assert message
#define SOB_UT_ASTMSG 0


// ==================================================================================== //
//                                    macro: Platform (PF)
// ==================================================================================== //

#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

// ==================================================================================== //
//                                    macro: Func (FN)
// ==================================================================================== //


#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define REP1(M, a1) M (a1)
#define REP2(M, a1, a2) M (a1) REP_SEP M (a2)
#define REP3(M, a1, a2, a3) REP2 (M, a1, a2) REP_SEP M (a3)
#define REP4(M, a1, a2, a3, a4) REP3 (M, a1, a2, a3) REP_SEP M (a4)
#define REP5(M, a1, a2, a3, a4, a5) REP4 (M, a1, a2, a3, a4) REP_SEP M (a5)
#define REP6(M, a1, a2, a3, a4, a5, a6) REP5 (M, a1, a2, a3, a4, a5) REP_SEP M (a6)
#define REP7(M, a1, a2, a3, a4, a5, a6, a7) REP6 (M, a1, a2, a3, a4, a5, a6) REP_SEP M (a7)
#define REP8(M, a1, a2, a3, a4, a5, a6, a7, a8) REP7 (M, a1, a2, a3, a4, a5, a6, a7) REP_SEP M (a8)
#define REP_SEP ,



// ==================================================================================== //
//                                    macro: Args (VA)
// ==================================================================================== //

#define VA_NARG(args...)            VA_NARG_(0, ##args, VA_RSEQ_N())
#define VA_NARG_(args...)           VA_ARG_N(args)
#define VA_ARG_FIRST(first, ...)    first
#define VA_ARG_REST(first, ...)     , ## __VA_ARGS__
#define VA_ARG_N(_0, a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, N, ...) N
#define VA_RSEQ_N() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
#define VA_FIRST(args...)           VA_FIRST_(args)
#define VA_FIRST_(F, ...)           F
#define VA_FIRST_STR(args...)       VA_FIRST_STR_(args)
#define VA_FIRST_STR_(F, ...)       #F
#define VA_REST_(F, args...)        args
#define VA_REST(args...)            VA_REST_(args)

// ==================================================================================== //
//                                    macro: Color (CL)
// ==================================================================================== //

#ifdef SOB_CL_OFF

#define ANSI_RESET              ""
#define ANSI_BOLD               ""
#define ANSI_DIM                ""
#define ANSI_ITALIC             ""
#define ANSI_UNDERLINE          ""
#define ANSI_BLINK              ""
#define ANSI_INVERT             ""
#define ANSI_REVERSE            ""
#define ANSI_HIDDEN             ""
#define ANSI_STRIKETHROUGH      ""

#define ANSI_FG_BLACK           ""
#define ANSI_FG_RED             ""
#define ANSI_FG_GREEN           ""
#define ANSI_FG_YELLOW          ""
#define ANSI_FG_BLUE            ""
#define ANSI_FG_MAGENTA         ""
#define ANSI_FG_CYAN            ""
#define ANSI_FG_WHITE           ""
#define ANSI_FG_DEFAULT         ""

#define ANSI_BG_BLACK           ""
#define ANSI_BG_RED             ""
#define ANSI_BG_GREEN           ""
#define ANSI_BG_YELLOW          ""
#define ANSI_BG_BLUE            ""
#define ANSI_BG_MAGENTA         ""
#define ANSI_BG_CYAN            ""
#define ANSI_BG_WHITE           ""
#define ANSI_BG_DEFAULT         ""

#define ANSI_FGB_BLACK          ""
#define ANSI_FGB_RED            ""
#define ANSI_FGB_GREEN          ""
#define ANSI_FGB_YELLOW         ""
#define ANSI_FGB_BLUE           ""
#define ANSI_FGB_MAGENTA        ""
#define ANSI_FGB_CYAN           ""
#define ANSI_FGB_WHITE          ""
#define ANSI_FGB_DEFAULT        ""
#else

#define ANSI_RESET              "\x1b[0m"
#define ANSI_BOLD               "\x1b[1m"
#define ANSI_DIM                "\x1b[2m"
#define ANSI_ITALIC             "\x1b[3m"
#define ANSI_UNDERLINE          "\x1b[4m"
#define ANSI_BLINK              "\x1b[5m"
#define ANSI_INVERT             "\x1b[6m"
#define ANSI_REVERSE            "\x1b[7m"
#define ANSI_HIDDEN             "\x1b[8m"
#define ANSI_STRIKETHROUGH      "\x1b[9m"

#define ANSI_FG_BLACK           "\x1b[30m"
#define ANSI_FG_RED             "\x1b[31m"
#define ANSI_FG_GREEN           "\x1b[32m"
#define ANSI_FG_YELLOW          "\x1b[33m"
#define ANSI_FG_BLUE            "\x1b[34m"
#define ANSI_FG_MAGENTA         "\x1b[35m"
#define ANSI_FG_CYAN            "\x1b[36m"
#define ANSI_FG_WHITE           "\x1b[37m"
#define ANSI_FG_DEFAULT         "\x1b[39m"

#define ANSI_BG_BLACK           "\x1b[40m"
#define ANSI_BG_RED             "\x1b[41m"
#define ANSI_BG_GREEN           "\x1b[42m"
#define ANSI_BG_YELLOW          "\x1b[43m"
#define ANSI_BG_BLUE            "\x1b[44m"
#define ANSI_BG_MAGENTA         "\x1b[45m"
#define ANSI_BG_CYAN            "\x1b[46m"
#define ANSI_BG_WHITE           "\x1b[47m"
#define ANSI_BG_DEFAULT         "\x1b[49m"

#define ANSI_FGB_BLACK          "\x1b[90m"
#define ANSI_FGB_RED            "\x1b[91m"
#define ANSI_FGB_GREEN          "\x1b[92m"
#define ANSI_FGB_YELLOW         "\x1b[93m"
#define ANSI_FGB_BLUE           "\x1b[94m"
#define ANSI_FGB_MAGENTA        "\x1b[95m"
#define ANSI_FGB_CYAN           "\x1b[96m"
#define ANSI_FGB_WHITE          "\x1b[97m"
#define ANSI_FGB_DEFAULT        "\x1b[99m"

#endif // CONFIG_NO_COLOR

// Add Multiple ANSI FMT
#define ANSI_FMT(msg, ...) __VA_ARGS__ msg ANSI_RESET

#define _BOLD(msg)              ANSI_FMT(msg, ANSI_BOLD)
#define _DIM(msg)               ANSI_FMT(msg, ANSI_DIM)
#define _ITALIC(msg)            ANSI_FMT(msg, ANSI_ITALIC)
#define _UNDERLINE(msg)         ANSI_FMT(msg, ANSI_UNDERLINE)
#define _BLINK(msg)             ANSI_FMT(msg, ANSI_BLINK)
#define _INVERT(msg)            ANSI_FMT(msg, ANSI_INVERT)
#define _REVERSE(msg)           ANSI_FMT(msg, ANSI_REVERSE)
#define _HIDDEN(msg)            ANSI_FMT(msg, ANSI_HIDDEN)
#define _STRIKETHROUGH(msg)     ANSI_FMT(msg, ANSI_STRIKETHROUGH)

#define _RED(msg)               ANSI_FMT(msg, ANSI_FG_RED)
#define _GREEN(msg)             ANSI_FMT(msg, ANSI_FG_GREEN)
#define _YELLOW(msg)            ANSI_FMT(msg, ANSI_FG_YELLOW)
#define _BLUE(msg)              ANSI_FMT(msg, ANSI_FG_BLUE)
#define _MAGENTA(msg)           ANSI_FMT(msg, ANSI_FG_MAGENTA)
#define _CYAN(msg)              ANSI_FMT(msg, ANSI_FG_CYAN)
#define _WHITE(msg)             ANSI_FMT(msg, ANSI_FG_WHITE)
#define _GREY(msg)              ANSI_FMT(msg, ANSI_FGB_BLACK)

#define _RED_BD(msg)            ANSI_FMT(msg, ANSI_FG_RED ANSI_BOLD)
#define _GREEN_BD(msg)          ANSI_FMT(msg, ANSI_FG_GREEN ANSI_BOLD)
#define _YELLOW_BD(msg)         ANSI_FMT(msg, ANSI_FG_YELLOW ANSI_BOLD)
#define _BLUE_BD(msg)           ANSI_FMT(msg, ANSI_FG_BLUE ANSI_BOLD)
#define _MAGENTA_BD(msg)        ANSI_FMT(msg, ANSI_FG_MAGENTA ANSI_BOLD)
#define _CYAN_BD(msg)           ANSI_FMT(msg, ANSI_FG_CYAN ANSI_BOLD)
#define _WHITE_BD(msg)          ANSI_FMT(msg, ANSI_FG_WHITE ANSI_BOLD)
#define _GREY_BD(msg)           ANSI_FMT(msg, ANSI_FGB_BLACK ANSI_BOLD)

#define _RED_UL(msg)            ANSI_FMT(msg, ANSI_FG_RED ANSI_UNDERLINE)
#define _GREEN_UL(msg)          ANSI_FMT(msg, ANSI_FG_GREEN ANSI_UNDERLINE)
#define _YELLOW_UL(msg)         ANSI_FMT(msg, ANSI_FG_YELLOW ANSI_UNDERLINE)
#define _BLUE_UL(msg)           ANSI_FMT(msg, ANSI_FG_BLUE ANSI_UNDERLINE)
#define _MAGENTA_UL(msg)        ANSI_FMT(msg, ANSI_FG_MAGENTA ANSI_UNDERLINE)
#define _CYAN_UL(msg)           ANSI_FMT(msg, ANSI_FG_CYAN ANSI_UNDERLINE)
#define _WHITE_UL(msg)          ANSI_FMT(msg, ANSI_FG_WHITE ANSI_UNDERLINE)
#define _GREY_UL(msg)           ANSI_FMT(msg, ANSI_FGB_BLACK ANSI_UNDERLINE)



// ==================================================================================== //
//                                    macro: log (LOG)
// ==================================================================================== //


#ifdef SOB_DBG_OFF
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, _CYAN("[DEBU]") " (%s:%d): " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, _RED("[ERRO]") " (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, _YELLOW("[WARN]") " (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, _BLUE("[INFO]") " (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...)  { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VAmsg_ARGS__); errno=0; goto error; }

// ==================================================================================== //
//                                    macro: Unit Test (UT)
// ==================================================================================== //

typedef struct {
    int n_test;                     /* number of tests */
    int n_pass;                     /* number of tests passed */
    int n_fail;                     /* number of tests failed */
    int flag;                       
    int quiet;                      /* quiet mode */
    char* msg;                      /* test message */

    const char* t_sc;               /* test time scale */
    struct timespec t_s;            /* test start time */
    struct timespec t_e;            /* test end time */
    double t_tak;                   /* test time taken */
    double t_tot;                   /* total test time taken */
} UnitTest;

static UnitTest ut = {
    .n_fail = 0,
    .n_pass = 0,
    .n_test = 0,
    .flag = 0,
    .quiet = 0,
    .msg = NULL,

    .t_sc = (SOB_UT_TIMESCALE == 1e3) ? "us" : ((SOB_UT_TIMESCALE == 1e6) ? "ms" : "s"),
    .t_s = {0},
    .t_e = {0},
    .t_tak = 0,
    .t_tot = 0
};

#define _UT_NRES(res)               ut.n_test++; ((res == NULL) ? (ut.n_pass++) : (ut.n_fail++))
#define _UT_SRES(res)               ((res == NULL) ? _GREEN("PASS") : _RED("FAIL"))
#define _UT_TSTART()                clock_gettime(CLOCK_MONOTONIC, &ut.t_s); 
#define _UT_TEND() \
    do { \
        clock_gettime(CLOCK_MONOTONIC, &ut.t_e); \
        ut.t_tak = ((ut.t_e.tv_sec - ut.t_s.tv_sec) * 1e9 + ut.t_e.tv_nsec - ut.t_s.tv_nsec) / SOB_UT_TIMESCALE; \
        if (ut.t_e.tv_nsec < ut.t_s.tv_nsec) { \
            ut.t_tak += 1; \
        } \
        ut.t_tot += ut.t_tak; \
    } while (0)

#define ut_msg(...) \
    do {\
        char message[64]; \
        snprintf(message, 64, VA_ARG_FIRST(__VA_ARGS__) VA_ARG_REST(__VA_ARGS__)); \
        printf("│  │ " _YELLOW("msg: ") _GREY("%-38s") " │\n", message); \
    } while(0)

#define ut_ast(test, message) \
    if (!(test)) {\
        printf("│  │ " _YELLOW("ast: ") _RED("%-38s") " │\n", #test); \
        ut_msg(ut.msg); \
        return ut.msg; \
    }

#define ut_add(test) \
    do { \
        debug("\n──────%s", " Sub: " _BLUE(#test)); \
        _UT_TSTART(); \
        ut.msg = test(); \
        _UT_TEND(); \
        _UT_NRES(ut.msg); \
        printf("│  ├── " _MAGENTA("%-2d ") _BLUE("%-18s") _CYAN("%12.4f %2s") " %s │\n", ut.n_test, #test, ut.t_tak, ut.t_sc, _UT_SRES(ut.msg));\
        debug("total exec %.3f %2s", ut.t_tak, ut.t_sc); \
        if (ut.msg) return ut.msg; \
    } while(0)
    

#define ut_run(name) \
int main(int, char *argv[]) {\
    debug("\n\n────── Run: " _BLUE("%s"), argv[0]);\
    printf("┌────────────────────────────────────────────────┐\n");\
    printf("│ Test: " _BLUE("%-40s") " │\n", argv[0]);\
    char *result = name();\
    printf("│ Sum: " _MAGENTA("%-2d ") "[%2d " _GREEN("PASS") " %2d " _RED("FAIL") "] " _CYAN("%12.4f %2s") " %s │\n", ut.n_test, ut.n_pass, ut.n_fail, ut.t_tot, ut.t_sc, _UT_SRES(result));\
    printf("├────────────────────────────────────────────────┤\n");\
    if (result == NULL) { \
        printf("│ " _CYAN("%-3s ") _BLUE("%-37s ") "%s │\n", "Res" , argv[0], _GREEN("PASS")); \
    } else { \
        printf("│ " _CYAN("%-3s ") _BLUE("%-37s ") "%s │\n", "Res" , argv[0], _RED("FAIL")); \
        printf("│ " _CYAN("%-3s ") _RED("%-42s") " │\n", "Msg" , result); \
        printf("│ %-3s %-51s │\n", _CYAN("Log"), _YELLOW("test/tests.log")); \
    } \
    printf("└────────────────────────────────────────────────┘\n"); \
    exit(result != 0);\
}


#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // _UTIL_SOB_H_

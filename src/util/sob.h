/**
 * @file sob.h
 * @author lancerstadium (lancerstadium@163.com)
 * @brief Super No Build Toolkit
 * @version 0.0.4
 * @date 2024-06-13
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _UTIL_SOB_H_
#define _UTIL_SOB_H_


// ==================================================================================== //
//                                       Include
// ==================================================================================== //

#ifndef _WIN32

#define _POSIX_C_SOURCE 200809L
#define PATH_SEP "/"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

typedef pid_t Pid;
typedef int Fd;

#else

#define WIN32_MEAN_AND_LEAN
#define PATH_SEP "\\"
#include "windows.h"
#include <process.h>

typedef HANDLE Pid;
typedef HANDLE Fd;

struct dirent {
    char d_name[MAX_PATH+1];
};

typedef struct DIR DIR;
DIR *opendir(const char *dirpath);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
LPSTR GetLastErrorAsString(void);

#endif  // _WIN32


#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>


#ifdef __cplusplus
extern "C" {
#endif

// ==================================================================================== //
//                                    macro: SOB Config (SOB)
// ==================================================================================== //

// #define SOB_CL_OFF
// #define SOB_LOG_DBG_OFF
// 1e3: us, 1e6: ms, 1e9: s
#define SOB_UT_TIMESC 1e6
// 1: Open assert message, 0: No assert message
#define SOB_UT_ASTMSG 0
// Max sub command number
#define SOB_AP_MSCMD 12
#define SOB_AP_LFLAG "--"
#define SOB_AP_SFLAG "-"
#define SOB_AP_GCMD  "all"


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

#define STR(str) #str
#define CONCAT(a, b) a ## b
#define CONCAT3(a, b, c) a ## b ## c
#define CONCAT4(a, b, c, d) a ## b ## c ## d

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

#define _BLACK(msg)             ANSI_FMT(msg, ANSI_FG_BLACK)
#define _RED(msg)               ANSI_FMT(msg, ANSI_FG_RED)
#define _GREEN(msg)             ANSI_FMT(msg, ANSI_FG_GREEN)
#define _YELLOW(msg)            ANSI_FMT(msg, ANSI_FG_YELLOW)
#define _BLUE(msg)              ANSI_FMT(msg, ANSI_FG_BLUE)
#define _MAGENTA(msg)           ANSI_FMT(msg, ANSI_FG_MAGENTA)
#define _CYAN(msg)              ANSI_FMT(msg, ANSI_FG_CYAN)
#define _WHITE(msg)             ANSI_FMT(msg, ANSI_FG_WHITE)
#define _GREY(msg)              ANSI_FMT(msg, ANSI_FGB_BLACK)

#define _BLACK_BD(msg)          ANSI_FMT(msg, ANSI_FG_BLACK ANSI_BOLD)
#define _RED_BD(msg)            ANSI_FMT(msg, ANSI_FG_RED ANSI_BOLD)
#define _GREEN_BD(msg)          ANSI_FMT(msg, ANSI_FG_GREEN ANSI_BOLD)
#define _YELLOW_BD(msg)         ANSI_FMT(msg, ANSI_FG_YELLOW ANSI_BOLD)
#define _BLUE_BD(msg)           ANSI_FMT(msg, ANSI_FG_BLUE ANSI_BOLD)
#define _MAGENTA_BD(msg)        ANSI_FMT(msg, ANSI_FG_MAGENTA ANSI_BOLD)
#define _CYAN_BD(msg)           ANSI_FMT(msg, ANSI_FG_CYAN ANSI_BOLD)
#define _WHITE_BD(msg)          ANSI_FMT(msg, ANSI_FG_WHITE ANSI_BOLD)
#define _GREY_BD(msg)           ANSI_FMT(msg, ANSI_FGB_BLACK ANSI_BOLD)

#define _BLACK_UL(msg)          ANSI_FMT(msg, ANSI_FG_BLACK ANSI_UNDERLINE)
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

typedef struct {
    const char* name;
    const char* color;
} LogElem;

static LogElem sob_log_elem[] = {
    { "TRAC", ANSI_FGB_BLUE   },
    { "DEBU", ANSI_FG_CYAN    },
    { "INFO", ANSI_FGB_GREEN  },
    { "WARN", ANSI_FGB_YELLOW },
    { "ERRO", ANSI_FGB_RED    },
    { "FATA", ANSI_FGB_RED    },
    { "ASST", ANSI_FG_MAGENTA }
};

typedef struct {
    const char* filename;
    int line;
    int col;
} LogPos;

#define log_pos_init        ((LogPos){ .filename = __FILE__, .line = __LINE__, .col = 0 })
#define log_pos_fresh(pos)   

typedef struct {
    LogPos* pos;
    LogElem* elem;
} Logger;

UNUSED static Logger sob_logger = {
    &log_pos_init, 
    sob_log_elem
};

#define log_errno               (errno == 0 ? "" : strerror(errno))
#define log_msg(level, fmt, ...) \
    do { \
        time_t t = time(NULL); \
        struct tm *tm = localtime(&t); \
        fprintf(stderr, "[%02d:%02d:%02d] ", tm->tm_hour, tm->tm_min, tm->tm_sec); \
        fprintf(stderr, "%s", sob_logger.elem[level].color); \
        fprintf(stderr, "%4s " ANSI_RESET, sob_logger.elem[level].name); \
        fprintf(stderr, _BLACK("%s:%d: "), __FILE__, __LINE__); \
        fprintf(stderr, fmt, ##__VA_ARGS__); \
        fprintf(stderr, _RED("%s"), log_errno); \
        fprintf(stderr,"\n"); \
    } while(0)

#define log_trace(...)          log_msg(0, ##__VA_ARGS__)
#ifdef SOB_LOG_DBG_OFF
#define log_dbg(...)            log_msg(1, ##__VA_ARGS__)
#else
#define log_dbg(...)
#endif
#define log_info(...)           log_msg(2, ##__VA_ARGS__)
#define log_warn(...)           log_msg(3, ##__VA_ARGS__)
#define log_err(...)            log_msg(4, ##__VA_ARGS__)
#define log_fatal(...)          log_msg(5, ##__VA_ARGS__)
#define log_ast(expr, ...)      if (!(expr)) { log_msg(6, ##__VA_ARGS__); exit(-1); }
#define check(A, M, ...)        if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_mem(A)            check((A), "Out of memory.")
#define sentinel(M, ...)        { log_err(M, ##__VA_ARGS__); errno=0; goto error; }
#define check_debug(A, M, ...)  if(!(A)) { log_dbg(M, ##__VAmsg_ARGS__); errno=0; goto error; }


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

UNUSED static UnitTest sob_ut = {
    .n_fail = 0,
    .n_pass = 0,
    .n_test = 0,
    .flag = 0,
    .quiet = 0,
    .msg = NULL,

    .t_sc = (SOB_UT_TIMESC == 1e3) ? "us" : ((SOB_UT_TIMESC == 1e6) ? "ms" : "s"),
    .t_s = {0},
    .t_e = {0},
    .t_tak = 0,
    .t_tot = 0
};

#define _UT_NRES(res)               sob_ut.n_test++; ((res == NULL) ? (sob_ut.n_pass++) : (sob_ut.n_fail++))
#define _UT_SRES(res)               ((res == NULL) ? _GREEN("PASS") : _RED("FAIL"))
#define _UT_TSTART()                clock_gettime(CLOCK_MONOTONIC, &sob_ut.t_s); 
#define _UT_TEND() \
    do { \
        clock_gettime(CLOCK_MONOTONIC, &sob_ut.t_e); \
        sob_ut.t_tak = ((sob_ut.t_e.tv_sec - sob_ut.t_s.tv_sec) * 1e9 + sob_ut.t_e.tv_nsec - sob_ut.t_s.tv_nsec) / SOB_UT_TIMESC; \
        if (sob_ut.t_e.tv_nsec < sob_ut.t_s.tv_nsec) { \
            sob_ut.t_tak += 1; \
        } \
        sob_ut.t_tot += sob_ut.t_tak; \
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
        ut_msg(message); \
        log_err(message); \
        return message; \
    }

#define ut_add(test) \
    do { \
        log_dbg("\n───── Sub: %s", _BLUE(#test)); \
        _UT_TSTART(); \
        sob_ut.msg = test(); \
        _UT_TEND(); \
        _UT_NRES(sob_ut.msg); \
        printf("│  ├── " _MAGENTA("%-2d ") _BLUE("%-18s") _CYAN("%12.4f %2s") " %s │\n", sob_ut.n_test, #test, sob_ut.t_tak, sob_ut.t_sc, _UT_SRES(sob_ut.msg));\
        log_dbg("total exec %.3f %2s", sob_ut.t_tak, sob_ut.t_sc); \
        if (sob_ut.msg) return sob_ut.msg; \
    } while(0)
    

#define ut_run(name) \
int main(int, char *argv[]) {\
    log_dbg("\n\n───── Run: " _BLUE("%s"), argv[0]);\
    printf("┌────────────────────────────────────────────────┐\n");\
    printf("│ Test: " _BLUE("%-40s") " │\n", argv[0]);\
    char *result = name();\
    printf("│ Sum: " _MAGENTA("%-2d ") "[%2d " _GREEN("PASS") " %2d " _RED("FAIL") "] " _CYAN("%12.4f %2s") " %s │\n", sob_ut.n_test, sob_ut.n_pass, sob_ut.n_fail, sob_ut.t_tot, sob_ut.t_sc, _UT_SRES(result));\
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


// ==================================================================================== //
//                                    macro: argparse (AP)
// ==================================================================================== //

typedef struct {
    char *sarg;
    char *larg;
    bool has_val;
    char *val;
    char *help;

    union {
        int i;
        bool b;
        float f;
        char *s;
        void *v;
    };
} APArg;

typedef void (*AP_CMD_CALLBACK)(int argc, char *argv[], char *envp[]);

typedef struct {
    char* name;
    char* desc;
    bool  is_sub;
    APArg* args;
    int   n_args;
    AP_CMD_CALLBACK fn;
} APCmd;

typedef void (*AP_CMD_PRINT_CALLBACK)(APCmd *);

typedef struct {
    char* prog_name;
    char* prog_name_without_path;
    char* prog_desc;
    int n_cmds;
    APCmd cmds[SOB_AP_MSCMD];
    bool  has_global;
    bool  has_subcmd;
    int cur_cmd;
    AP_CMD_PRINT_CALLBACK print_cmd;
} ArgParser;



#ifdef __cplusplus
}
#endif  // __cplusplus

#endif  // _UTIL_SOB_H_

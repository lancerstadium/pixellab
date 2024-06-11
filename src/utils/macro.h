#ifndef _Utils_Macro_h_
#define _Utils_Macro_h_

#define ARG_FIRST(first, ...) first
#define ARG_OTHER(first, ...) , ## __VA_ARGS__

#define TRUE 1
#define FALSE 0

#define ANSI_RESET          "\x1b[0m"
#define ANSI_BOLD           "\x1b[1m"
#define ANSI_UNDERLINE      "\x1b[4m"
#define ANSI_REVERSE        "\x1b[7m"

#define ANSI_FG_BLACK       "\x1b[30m"
#define ANSI_FG_RED         "\x1b[31m"
#define ANSI_FG_GREEN       "\x1b[32m"
#define ANSI_FG_YELLOW      "\x1b[33m"
#define ANSI_FG_BLUE        "\x1b[34m"
#define ANSI_FG_MAGENTA     "\x1b[35m"
#define ANSI_FG_CYAN        "\x1b[36m"
#define ANSI_FG_WHITE       "\x1b[37m"
#define ANSI_FG_GREY        "\x1b[90m"

#define ANSI_BG_BLACK       "\x1b[40m"
#define ANSI_BG_RED         "\x1b[41m"
#define ANSI_BG_GREEN       "\x1b[42m"
#define ANSI_BG_YELLOW      "\x1b[43m"
#define ANSI_BG_BLUE        "\x1b[44m"
#define ANSI_BG_MAGENTA     "\x1b[45m"
#define ANSI_BG_CYAN        "\x1b[46m"
#define ANSI_BG_WHITE       "\x1b[47m"
#define ANSI_BG_GREY        "\x1b[100m"


// Add Multiple ANSI FMT
#define ANSI_FMT(str, ...) __VA_ARGS__ str ANSI_RESET

#define _RED(str) ANSI_FMT(str, ANSI_FG_RED)
#define _GREEN(str) ANSI_FMT(str, ANSI_FG_GREEN)
#define _YELLOW(str) ANSI_FMT(str, ANSI_FG_YELLOW)
#define _BLUE(str) ANSI_FMT(str, ANSI_FG_BLUE)
#define _MAGENTA(str) ANSI_FMT(str, ANSI_FG_MAGENTA)
#define _CYAN(str) ANSI_FMT(str, ANSI_FG_CYAN)
#define _WHITE(str) ANSI_FMT(str, ANSI_FG_WHITE)
#define _GREY(str) ANSI_FMT(str, ANSI_FG_GREY)
#define _DEFAULT(str) ANSI_FMT(str, ANSI_FG_DEFAULT)


#define _BOLD(str) ANSI_FMT(str, ANSI_BOLD)
#define _UNDERLINE(str) ANSI_FMT(str, ANSI_UNDERLINE)
#define _REVERSE(str) ANSI_FMT(str, ANSI_REVERSE)


#define _RED_BOLD(str) ANSI_FMT(str, ANSI_FG_RED ANSI_BOLD)
#define _GREEN_BOLD(str) ANSI_FMT(str, ANSI_FG_GREEN ANSI_BOLD)
#define _YELLOW_BOLD(str) ANSI_FMT(str, ANSI_FG_YELLOW ANSI_BOLD)
#define _BLUE_BOLD(str) ANSI_FMT(str, ANSI_FG_BLUE ANSI_BOLD)
#define _MAGENTA_BOLD(str) ANSI_FMT(str, ANSI_FG_MAGENTA ANSI_BOLD)
#define _CYAN_BOLD(str) ANSI_FMT(str, ANSI_FG_CYAN ANSI_BOLD)
#define _WHITE_BOLD(str) ANSI_FMT(str, ANSI_FG_WHITE ANSI_BOLD)
#define _GREY_BOLD(str) ANSI_FMT(str, ANSI_FG_GREY ANSI_BOLD)

#define _RED_ULINE(str) ANSI_FMT(str, ANSI_FG_RED ANSI_UNDERLINE)
#define _GREEN_ULINE(str) ANSI_FMT(str, ANSI_FG_GREEN ANSI_UNDERLINE)
#define _YELLOW_ULINE(str) ANSI_FMT(str, ANSI_FG_YELLOW ANSI_UNDERLINE)
#define _BLUE_ULINE(str) ANSI_FMT(str, ANSI_FG_BLUE ANSI_UNDERLINE)
#define _MAGENTA_ULINE(str) ANSI_FMT(str, ANSI_FG_MAGENTA ANSI_UNDERLINE)
#define _CYAN_ULINE(str) ANSI_FMT(str, ANSI_FG_CYAN ANSI_UNDERLINE)
#define _WHITE_ULINE(str) ANSI_FMT(str, ANSI_FG_WHITE ANSI_UNDERLINE)
#define _GREY_ULINE(str) ANSI_FMT(str, ANSI_FG_GREY ANSI_UNDERLINE)

#endif

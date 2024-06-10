#!/bin/bash
ANSI_RESET="\x1b[0m"
ANSI_BOLDU="\x1b[4;1m"
ANSI_RED="\x1b[31m"
ANSI_GREEN="\x1b[32m"
ANSI_YELLOW="\x1b[33m"
ANSI_BLUE="\x1b[34m"
ANSI_CYAN="\x1b[36m"
test_count=1

printf "\n${ANSI_BOLDU}Running Unit Tests:${ANSI_RESET}\n"

for i in tests/*_tests
do
    if test -f $i
    then
        if $VALGRIND ./$i 2>> tests/tests.log
        then
            printf "│ ${ANSI_CYAN}%-3d${ANSI_RESET} ${ANSI_BLUE}%-37s${ANSI_RESET} ${ANSI_GREEN}%s${ANSI_RESET} │\n" "${test_count}" "${i}" "PASS"
        else
            printf "│ ${ANSI_CYAN}%-3d${ANSI_RESET} ${ANSI_BLUE}%-37s${ANSI_RESET} ${ANSI_RED}%s${ANSI_RESET} │\n" "${test_count}" "${i}" "FAIL"
            printf "│ ${ANSI_CYAN}%-3s${ANSI_RESET} ${ANSI_YELLOW}%-42s${ANSI_RESET} │\n" "Log" "tests/tests.log"
            printf "└────────────────────────────────────────────────┘\n"
            printf "${ANSI_CYAN}[Log Info]:${ANSI_RESET}\n"
            # tail tests/tests.log
            tail -n $(($(tac tests/tests.log | grep -m 1 -n '^────── Run' | cut -d: -f1) + 1)) tests/tests.log | sed '/^$/d'
            exit 1
        fi
        printf "└────────────────────────────────────────────────┘\n"
    fi
    test_count=$((test_count+1))
done

echo ""
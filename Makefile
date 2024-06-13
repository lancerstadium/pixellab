ITEMNAME:=pixellab
INCPATH=src/
INCFLAGS=$(addprefix -I,$(INCPATH)) $(shell sdl2-config --cflags)
CFLAGS=-g -O2 -Wall -Wextra $(INCFLAGS) -rdynamic -DSOB_LOG_DBG_OFF $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard test/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/lib$(ITEMNAME).a
OS=$(shell lsb_release -si)
ifeq ($(OS),Ubuntu)
	LDLIBS=-l$(ITEMNAME) -L./build -lm -L/usr/lib/x86_64-linux-gnu/ $(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf
endif

SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# Config
CFG_REPORT=0
CFG_TEST=

# The Target Build
all: $(TARGET) tests

dev: CFLAGS=-g -Wall $(INCFLAGS) -Wall -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

# $(SO_TARGET): $(TARGET) $(OBJECTS)
# 	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: LDLIBS += $(TARGET)
tests: $(TESTS)
ifeq ($(CFG_REPORT),1)
	@echo "tests report: ./test/tests.report"
	@sh ./test/runtests.sh $(CFG_TEST) | sed 's/\x1B\[[0-9;]*[JKmsu]//g' > test/tests.report
else
	@sh ./test/runtests.sh $(CFG_TEST)
endif

test:
	@$(VALGRIND) ./test/$(SECOND_GOAL)_tests 2>> test/tests.log

valgrind:
	@echo "valgrind log: ./test/valgrind.log"
	VALGRIND="valgrind --log-file=./test/valgrind.log" $(MAKE)

log:
	@tail -n $$(($$(tac test/tests.log | grep -m 1 -n '^───── Run' | cut -d: -f1) + 1)) test/tests.log | sed '/^$$/d'

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f test/tests.log test/valgrind.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

commit:
	git add .
	git commit -m "$(shell date)"
	git push

# The Checker
# 这个正则表达式是用来匹配可能存在安全风险的函数，
# 例如strcpy，strncpy，strcat，strncat，memcpy，memmove，memset，sprintf，vsprintf等。
# 这些函数在使用不当时可能会导致缓冲区溢出和其他安全漏洞。
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

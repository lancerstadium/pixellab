ITEMNAME:=pixellab
INCDIRS=src/ 
INCFLAGS=$(addprefix -I,$(INCDIRS))
CFLAGS=-g -O2 -Wall -Wextra $(INCFLAGS) -rdynamic -DCONFIG_NO_DEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))

TARGET=build/lib$(ITEMNAME).a
OS=$(shell lsb_release -si)
ifeq ($(OS),Ubuntu)
	LDLIBS=-l$(ITEMNAME) -L./build -lm
endif

SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

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
	@sh ./tests/runtests.sh

valgrind:
	@echo "valgrind log: ./tests/valgrind.log"
	VALGRIND="valgrind --log-file=./tests/valgrind.log" $(MAKE)
	

# The Cleaner
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

# The Install
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib/

# The Checker
# 这个正则表达式是用来匹配可能存在安全风险的函数，
# 例如strcpy，strncpy，strcat，strncat，memcpy，memmove，memset，sprintf，vsprintf等。
# 这些函数在使用不当时可能会导致缓冲区溢出和其他安全漏洞。
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions.
	@egrep $(BADFUNCS) $(SOURCES) || true

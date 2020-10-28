CC=gcc
PATH_UNITY=Unity/src
PATH_CEXCEPTION=CException/lib
PATH_FFF=fff

# Compilation options
CFLAGS +=   \
	-Wall	\
	-Wdouble-promotion \
	-Wstrict-prototypes \
	-Wextra \
	-Werror \
	-Wfatal-errors \
	-Werror-implicit-function-declaration \
	-Wundef \
	-Wshadow \
	-Wwrite-strings \
	-Wsign-compare \
	-Wmissing-format-attribute \
	-Wunreachable-code
	# Unity does have a float comparison
	# -Wfloat-equal

CFLAGS +=-Wno-unused-function
CFLAGS +=-Wno-unused-parameter

# Let the source code we are testing it
CFLAGS += -DWFLASH_TEST

# Include header and source files
# TODO: Automate adding include directories
CFLAGS += -I. -I../inc -I$(PATH_UNITY) -I$(PATH_CEXCEPTION) -I$(PATH_FFF)
CFLAGS += $(PATH_UNITY)/unity.c
CFLAGS += $(PATH_CEXCEPTION)/CException.c

# Debug optimization
ifeq ($(DEBUG), 1)
    CFLAGS += -Og -ggdb
else
    CFLAGS += -Os
endif

.DEFAULT_GOAL: all
all: test_wflash

# Remove wflash_ll from the dependencies so it doesn't clash with the fake
test_wflash: test_wflash.c ../src/wflash.c # ../src/wflash_ll.c
	# Generamos un test runner con ruby
	ruby Unity/auto/generate_test_runner.rb $@.c $@.runner.c
	# Compilamos
	$(CC) $(CFLAGS) $^ -o $@_Runner.out $@.runner.c
	# Ejecutamos el Runner generado
	./$@_Runner.out

.PHONY: clean
clean:
	rm -f *.out *.runner.c

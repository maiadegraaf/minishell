CLEANUP=rm -f
MKDIR=mkdir -p
TARGET_EXTENSION=out

.PHONY: clean
.PHONY: test

PATHU = ../unity/src/
PATHI = ../includes/
PATHS = ../src/
PATHSL = ../src/lexor/
PATHSP = ../src/parser/
PATHP = ../src/pipex/
PATHT = ../test/
PATHB = ../build/
PATHD = ../build/depends/
PATHO = ../build/objs/
PATHR = ../build/results/

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

HEADER	=	$(wildcard ../includes/*.c) 

SRCT = $(wildcard $(PATHT)*.c)

COMPILE=gcc -c
LINK=gcc
DEPEND=gcc -MM -MG -MF
CFLAGS=-Wall -Werror -Wextra -I. -I$(PATHU) -I$(PATHS) -I$(PATHP) -I$(PATHI) -DTEST

RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT))

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Test%.$(TARGET_EXTENSION): $(PATHO)Test%.o $(PATHO)%.o $(PATHU)unity.o #$(PATHD)Test%.d
	$(LINK) $(CFLAGS) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

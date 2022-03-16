CLEANUP=rm -f
MKDIR=mkdir -p
TARGET_EXTENSION=out

.PHONY: clean
.PHONY: test

PATHLIBFT = ../libraries/libft
PATHU = ../unity/src/
PATHI = ../includes/
PATHS = ../src/
PATHSL = ../src/lexor/
PATHSP = ../src/parser/
PATHP = ../src/pipex/
PATHSU = ../src/utils/
PATHSB = ../src/builtins/
PATHSE = ../src/error/
PATHT = ../test/
PATHB = ../build/
PATHO = ../build/objs/
PATHR = ../build/results/

LIBFT	=	../libraries/libft/libft.a

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR)

HEADER	=	$(wildcard $(PATHI)*.h) 

SRCT = $(wildcard $(PATHT)*.c)

src	=	$(wildcard $(PATHSL)*.c) \
		$(wildcard $(PATHSP)*.c) \
		$(wildcard $(PATHSU)*.c) \
		$(wildcard $(PATHSB)*.c) \
		$(wildcard $(PATHSE)*.c)

COMPILE=gcc -c

LINK=gcc

CFLAGS= -I. -I$(PATHU) -I$(PATHLIBFT) -I$(PATHS) -I$(PATHP) -I$(PATHI)

RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt, $(SRCT))

OBJS = $(addprefix $(PATHO), $(notdir $(patsubst %.c, %.o, $(src))))

PASSED = `grep -s PASS $(PATHR)*.txt`

FAIL = `grep -s FAIL $(PATHR)*.txt`

IGNORE = `grep -s IGNORE $(PATHR)*.txt`

test: $(BUILD_PATHS) $(RESULTS)
	@echo $(PATHO)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

$(PATHR)%.txt: $(PATHO)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHO)Test%.$(TARGET_EXTENSION): $(LIBFT) $(OBJS) $(PATHO)Test%.o $(PATHO)%.o $(PATHU)unity.o 
	$(LINK) -lreadline -o  $@ $^

$(PATHO)%.o:: $(PATHT)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

# $(PATHO)%.o:: $(PATHS)%.c $(HEADERS)
# 	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSL)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSP)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSU)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSB)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHSE)%.c $(HEADERS)
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

$(LIBFT):
	$(MAKE) -C $(PATHLIBFT)

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	rm -rdf $(PATHB)
	make fclean -C $(PATHLIBFT)

re: clean test

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt

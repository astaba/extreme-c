# extreme_c/ch01-essential-features/Makefile
# Run "make -k" to ignore build errors on error test files
.PHONY: all clean
.DELETE_ON_ERROR:

CC     = gcc
STD    ?= -std=gnu17
WAR    ?= -Wall
OPT    ?= -O3 -march=native -fdata-sections -ffunction-sections
CFLAGS = ${WAR}
# Remove #line directives from preprocessed files
CPPFLAGS = -P

_SOURCES     = $(wildcard *.c)
SOURCES      = $(filter-out ExtremeC_examples1_23.c,$(_SOURCES))
PREPROCESSED = $(subst .c,.i,$(wordlist 1, 6, $(SOURCES)))
BINARIES     = $(subst .c,.out,$(SOURCES))

all: $(BINARIES)

$(wordlist 1, 6, $(BINARIES)): %.out: %.c %.i
	$(CC) $(CFLAGS) -o $@ $<

$(word 7, $(BINARIES)): %.out: %.c ExtremeC_examples1_08.h
	$(CC) $(CFLAGS) -o $@ $<

$(wordlist 8, 22, $(BINARIES)): %.out: %.c
	$(CC) $(CFLAGS) -o $@ $<

$(PREPROCESSED): %.i: %.c
	$(CC) -E $(CPPFLAGS) $(CFLAGS) -o $@ $<

# %.i: %.c
# 	$(CC) -E $(CPPFLAGS) $(CFLAGS) -o $@ $<

clean:
	@rm -vf *.out *.i


# Your program must compile with 'make'
# You must not change this file.

CC = gcc
FLAGS = -std=c99 -Wall -Werror -g -pedantic

default:
	$(CC) $(FLAGS) *.c -o rgrep

clean:
	rm -f rgrep

check: clean default
	test "`echo "a\nb\nc" | ./rgrep 'a'`" = "a"
	test "`echo "a" | ./rgrep 'a*a'`" = "a"
	test "`echo "a" | ./rgrep '...'`" = ""
	@echo "Passed sanity check."

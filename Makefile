CC := gcc
CC := ${CC}

simple_regex: simple_regex.c
	${CC} simple_regex.c -o simple_regex
	./simple_regex
	
all:
	@echo ${CC}
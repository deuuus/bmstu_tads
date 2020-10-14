@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Werror -pedantic -c main.c read.c readf.c sort.c
gcc -o app.exe main.o read.o readf.o sort.o
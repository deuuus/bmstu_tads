@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Werror -pedantic -g3 -c main.c read.c sort.c info.c help.c
gcc -o app.exe main.o read.o sort.o info.o help.o
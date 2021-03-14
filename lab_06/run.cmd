@ECHO OFF
CHCP 65001
gcc -std=c99 -Wall -Werror -pedantic -c src/menu.c -o out/menu.o
gcc -std=c99 -Wall -Werror -pedantic -c src/main.c -o out/main.o
gcc -std=c99 -Wall -Werror -pedantic -c src/tree.c -o out/tree.o
gcc -std=c99 -Wall -Werror -pedantic -c src/hash.c -o out/hash.o
gcc -std=c99 -Wall -Werror -pedantic -c src/analys.c -o out/analys.o
gcc -std=c99 -Wall -Werror -pedantic -c src/file.c -o out/file.o
gcc -o app.exe out/main.o out/menu.o out/tree.o out/hash.o out/analys.o out/file.o
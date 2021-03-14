CC = gcc
INCPATH = ./inc/
SRCPATH = ./src/
OUTPATH = ./out/
CFLAGS =-std=c99 -Wall -Werror -pedantic
LFLAGS =--coverage
.PHONY : clean dir release debug func
.NOTPARALLEL: release debug

release: CFLAGS+= -o2
release: $(OUTPATH)release.lastbuildstate app.exe

debug: CFLAGS+= --coverage
debug: LFLAGS+= -g3
debug: $(OUTPATH)debug.lastbuildstate app.exe

func: CFLAGS+= --coverage
func: LFLAGS+= -g3

OBJS = $(OUTPATH)menu.o $(OUTPATH)process.o $(OUTPATH)analys.o

app.exe: $(OUTPATH)main.o $(OBJS)
	$(CC) $(LFLAGS) -ggdb -o $@ $^

$(OUTPATH)%.o: $(SRCPATH)%.c | dir
	$(CC) $(CFLAGS) -c $^ -o $@

$(OUTPATH)release.lastbuildstate: | dir
	rm -rf *.exe $(OUTPATH)*.o $(OUTPATH)debug.lastbuildstate
	touch $(OUTPATH)release.lastbuildstate

$(OUTPATH)debug.lastbuildstate: | dir
	rm -rf *.exe $(OUTPATH)*.o $(OUTPATH)release.lastbuildstate
	touch $(OUTPATH)debug.lastbuildstate

dir:
	mkdir -p $(OUTPATH)	

clean :
	rm -fv *.exe
	rm -fv $(OUTPATH)*.o
	rm -fv $(OUTPATH)*.gcno
	rm -fv $(OUTPATH)*.gcda
	touch $(OUTPATH)*.lastbuildstate

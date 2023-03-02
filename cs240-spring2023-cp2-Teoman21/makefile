COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 2
LASTNAME = Kaman
GITUSERID = Teoman21
EXE = scheduler_cp2.cpp

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)
	.\$(BIN)/$(EXE)

$(BIN)/$(EXE): $(OBJ)/scheduler_cp2.o
	$(CC) $(FLAGS) $(OBJ)/scheduler_cp2.o -o $@

$(OBJ)/scheduler_cp2.o: scheduler_cp2.cpp 
	$(CC) $(FLAGS) -c scheduler_cp2.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz

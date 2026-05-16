BIN=main.exe
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

$(BIN):$(OBJ)
	@$(CC) $^ -o $@
	@echo "linking $^ to $@..."

%.o:%.c
	@$(CC) -c $<
	@echo "compling $< to $@..."

.PHONY:clean
clean:
	@rm -rf $(OBJ) $(BIN)

BIN=pro
CC=gcc
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

$(BIN):$(OBJ)
	@echo "链接$^..."
	@$(CC) -o $@ $^
%.o:%.c
	@echo "编译$<..."
	@$(CC) -c $<

.PHONY:clean
clean:
	@rm -f $(BIN) $(OBJ)

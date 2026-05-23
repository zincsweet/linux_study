BIN=main
CC=gcc
RSC=$(wildcard *.c)
OBJ=$(RSC:.c=.o)

$(BIN):$(OBJ)
	@$(CC) $^ -o $@
	@echo "linking $^ to $@..."

%.o:%.c
	@$(CC) -c $<
	@echo "compling $< to $@..."

.PHONY:clean
clean:
	@rm -rf $(BIN) $(OBJ)
	@echo "删除文件$(BIN);$(OBJ)"

SRC_DIR:=./src
BIN_DIR:=./bin
CFLAGS:=-std=c11 -O2 -Wall

SRC:=$(wildcard $(SRC_DIR)/*.c)
BIN:=$(patsubst ./src/%.c, ./bin/%, $(SRC))

build: $(BIN)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	gcc $^ -o $@ $(CFLAGS) 
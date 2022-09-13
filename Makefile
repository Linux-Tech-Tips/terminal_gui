CC=gcc
LN=gcc
BUILD_DIR=build

SRC=main.c
SRC+=esc_func.c
OUTFILE=output.elf

OBJ=$(SRC:%=$(BUILD_DIR)/%.o)

all: dirs compile link

$(OUTFILE): $(OBJ)
	$(CC) $^ -o $@

$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c $^ -o $@


.PHONY: dirs, compile, link, clean
dirs:
	mkdir -p $(BUILD_DIR)

compile: $(OBJ)

link: $(OUTFILE)

clean:
	rm -r $(BUILD_DIR)
	rm $(OUTFILE)
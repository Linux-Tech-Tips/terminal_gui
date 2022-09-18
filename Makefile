CC=gcc
LN=gcc
BUILD_DIR=build

SRC=main.c
SRC+=terminal_f.c

OUTFILE=output.elf
ASMFILE=code.asmdump

OBJ=$(SRC:%=$(BUILD_DIR)/%.o)

all: dirs compile link

$(OUTFILE): $(OBJ)
	$(CC) $^ -o $@ -lm

$(BUILD_DIR)/%.c.o: %.c
	$(CC) -c $^ -o $@


.PHONY: dirs, compile, link, disassemble, clean
dirs:
	mkdir -p $(BUILD_DIR)

compile: $(OBJ)

link: $(OUTFILE)

disassemble:
	objdump -d $(OUTFILE) > $(ASMFILE)

clean:
	rm -r $(BUILD_DIR)
	rm -f $(OUTFILE)
	rm -f $(ASMFILE)

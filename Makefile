CC = powerpc64-linux-gnu-gcc
AS = powerpc64-linux-gnu-as
LD = powerpc64-linux-gnu-ld
CFLAGS = -mcpu=cell -mbig -m32 -nostdlib -O1
ASFLAGS = -mregnames -mcell -be
PATCH_FILE = patch.txt

SRC_DIR = src/
BIN_DIR = bin/

C_SRCS = $(wildcard $(SRC_DIR)*.c)
S_SRCS = $(wildcard $(SRC_DIR)*.s)

C_BINS = $(C_SRCS:$(SRC_DIR)%.c=$(BIN_DIR)%.bin)
S_BINS = $(S_SRCS:$(SRC_DIR)%.s=$(BIN_DIR)%.bin)

BINS = $(C_BINS) $(S_BINS)

# target address from patch.txt
define get_addr
$(shell grep -i "bin/$1.bin" $(PATCH_FILE) | cut -d':' -f1)
endef

.PHONY: all clean test

all: clean $(BIN_DIR) $(BINS)

test: clean $(BIN_DIR) $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)%.bin: $(SRC_DIR)%.c
	@echo "Compiling $< -> $@"
	ADDR=$(call get_addr,$*) && \
	$(CC) $(CFLAGS) -Wl,--oformat=binary,-Ttext=$$ADDR -o $@ $<

$(BIN_DIR)%.bin: $(SRC_DIR)%.s
	@echo "Assembling $< -> $@"
	$(AS) $(ASFLAGS) -o $*.o $<
	$(LD) --oformat=binary -o $@ $*.o
	rm -f $*.o

clean:
	rm -rf $(BIN_DIR)

CC = arm-none-eabi-gcc
CPU = -mcpu=cortex-m4 -mthumb
LDFLAGS = -nostdlib -T linked.ld
SRC = src/main.c src/startup.c
OUT = test.elf

# Optional optimization with OPT=1
ifeq ($(OPT),1)
    CFLAGS = $(CPU) -O3 -fno-builtin
else
    CFLAGS = $(CPU)
endif

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

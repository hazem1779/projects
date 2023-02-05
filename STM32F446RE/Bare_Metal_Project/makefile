CC=arm-none-eabi-gcc
MACH=cortex-m4
CFLAGS= -c -mcpu=$(MACH) -mthumb  -Wall -std=gnu11 -O0
#LDFLAGS= -mcpu=$(MACH) --specs=nano.specs -mthumb  -mfloat-abi=soft -T stm32_ls.ld -Wl,-Map=final.map 
LDFLAGS_semi= -mcpu=$(MACH) --specs=rdimon.specs -mthumb  -mfloat-abi=soft -T stm32_ls.ld -Wl,-Map=final.map 

all:main.o Software_Delay.o stm32_startup.o syscalls.o final.elf 
semi:main.o Software_Delay.o stm32_startup.o final_sh.elf

stm32_startup.o:stm32_startup.c
	$(CC) $(CFLAGS) $^ -o $@ 

main.o:main.c
	$(CC) $(CFLAGS) $^ -o $@

Software_Delay.o:Software_Delay.c
	$(CC) $(CFLAGS) $^ -o $@

syscalls.o:syscalls.c
	$(CC) $(CFLAGS) $^ -o $@

final_sh.elf: main.o Software_Delay.o stm32_startup.o 
	$(CC) $(LDFLAGS_semi) $^ -o $@

final.elf: main.o Software_Delay.o stm32_startup.o syscalls.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf *.o *.elf
load:
	openocd -f board/st_nucleo_f4.cfg	

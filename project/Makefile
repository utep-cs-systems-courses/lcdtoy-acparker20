#Makefile config.
COMMON_OBJECTS =
CPU		= msp430g2553
CFLAGS		= -mmcu=${CPU} -I../h 
LDFLAGS		= -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)

CC		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu={CPU} -c
all: lcdToy.elf

lcdToy.elf: ${COMMON_OBJECTS} main.o p1_interrupt_handler.o switches.o buzzer.o shapemotion.o ../project/lib/libTimer.a
	${CC} $(CFLAGS) $(LDFLAGS) -o $@ $^ -lTimer -lLcd -lShape -lCircle

load: lcdToy.elf
	msp430loader.sh lcdToy.elf

clean:
	rm -f *.o *.elf

#makfile configuration

CPU			= msp430g2553
CFLAGS			= -mmcu=${CPU} -I../h
LDFLAGS 	= -L../lib -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-gcc -mmcu=${CPU} -c

all: bluzz.elf

#additional rules for files
bluzz.elf: ${COMMON_OBJECTS} main.o led.o buzzer.o switches.o stateMachines.o p1_interrupt_handler.o wdt_handler.o sMachines.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd

load: bluzz.elf
	msp430loader.sh $^

clean:
	rm -f *.o *.elf

led.o: led.c led.h

#wdInterruptHandler.o: stateMachines.h buzzer.h switches.h

stateMachines.o: led.h stateMachines.h buzzer.h

buzzer.o: buzzer.h


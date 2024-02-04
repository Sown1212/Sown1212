clear:
	rm -r "__eeprom.d"
	rm -r "__eeprom.p1"
	rm -r "Mplab.cmf"
	rm -r "Mplab.d"
	rm -r "Mplab.elf"
	rm -r "Mplab.hxl"
	rm -r "Mplab.o"
	rm -r "Mplab.p1"
	rm -r "Mplab.s"
	rm -r "Mplab.sdb"
	rm -r "Mplab.sym"
	rm -r "startup.lst"
	rm -r "startup.o"
	rm -r "startup.rlf"
	rm -r "startup.s"
build:
	xc8-cc -mcpu=16f877a -mdebugger=none Mplab.c
	make clear
	
CC=gcc
SOURCES_ENC=main_encodeChar.c common.c encoder.c decoder.c
SOURCES_DEC=main_decodeChar.c common.c encoder.c decoder.c
SOURCES_ARM=main_ARM.c extractBit.s decodeChar.s codeToBinary.s binaryToText.s decodeFile.s common.c
HEADERS=decoder.h encoder.h common.h
CFLAGS=-g -Wall -std=c99

all: encodeChar decodeChar decodeARM

encodeChar:
	$(CC) $(CFLAGS) $(SOURCES_ENC) -o encodeChar

decodeChar:
	$(CC) $(CFLAGS) $(SOURCES_DEC) -o decodeChar

decodeARM:
	$(CC) $(CFLAGS) $(SOURCES_ARM) -o decodeARM


clean:
	rm -f encodeChar decodeChar decodeARM

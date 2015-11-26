CC=gcc
SOURCES=countchars.c warmup.c
SOURCES2=reverse_endian.c warmup.c
SOURCES3=decoder.c main.c common.c
SOURCES4=main_segfault.c decoder.c common.c
SOURCES5=main_2.c decoder.c common.c
HEADERS=encoder.h decoder.h common.h warmup.h
CFLAGS=-g -Wall -std=c99

reverse:
	$(CC) $(CFLAGS) $(SOURCES2) -o reverse

countchar:
	$(CC) $(CFLAGS) $(SOURCES) -o countchar

decode:
	$(CC) $(CFLAGS) $(SOURCES3) -o decode

decode_segfault:
	$(CC) $(CFLAGS) $(SOURCES4) -o decode_segfault
decode_2:
	$(CC) $(CFLAGS) $(SOURCES5) -o decode_2



clean:
	rm -f reverse countchar decode decode_segfault decode_2

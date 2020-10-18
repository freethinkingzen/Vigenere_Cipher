#Makefile for Vigenere Cipher Program

CC = gcc
CFLAGS = -g -Wall

hw2: vigenere.c vigenere.h
	$(CC) $(CFLAGS) -o vigenere vigenere.c -lm

clean:
	-rm -f vigenere





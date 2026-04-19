// Main.h
//
// This has the include files for encrypt/decrypt
// 

#pragma once

#include <windows.h>
#include <stdio.h>
#include <io.h>

// ***** DEFINES *****
#define __err fprintf(stderr, 

// ***** PROTOTYPES *****
int sha256(char* fileName, char* dataBuffer, DWORD dataLength, unsigned char sha256sum[32]);
int encryptFile(char *inputFilename, char* password);
int decryptFile(char *inputFilename);
FILE *openInputFile(char *filename, DWORD &filesize);

// ***** GLOBALS *****
extern int gFunction;	// not specified, 1 = encrypt, 2 = decrypt
extern char gInputFilename[MAX_PATH + 4];
extern char gPassword[512];

// Encrypt.cpp
//
// this file calls the routines to encrypt a file
//

#include "Main.h"

// this function is actually the answer
int encryptFile(char *inputFilename, char* password)
{
	FILE *fptrIn, *fptrOut;
	BYTE pwdHash[32];
	DWORD passwordLength, filesize, i, tmpi;
	char* buffer;
	char outputFilename[MAX_PATH+4];
	int resulti, pwdHashIndx;

	fptrIn = openInputFile(inputFilename, filesize);

	passwordLength = (size_t)strlen(password);

	if (passwordLength == 0 || passwordLength >= 256)
	{
		fprintf(stderr, "Error - Password is too long - keep less than 256 bytes!\n\n");
		exit(-1);
	}

	resulti = sha256(NULL, password, passwordLength, pwdHash);
	if (resulti != 0)
	{
		fprintf(stderr, "Error hashing password.\n\n");
		exit(-1);
	}

	// use the password hash to encrypt
	buffer = (char*)malloc(filesize);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error - Could not allocate %d bytes of memory on the heap.\n\n", filesize);
		exit(-1);
	}

	fread(buffer, 1, filesize, fptrIn);	// should read entire file

//////////////////////////////////////////////////////////////////////////////////////////
// ENCRYPT THE FILE HERE - this is where you add code
//////////////////////////////////////////////////////////////////////////////////////////

	for (i = 0; i < filesize; i++)
	{
		buffer[i] = buffer[i] ^ 0;
	}

	strcpy(outputFilename, inputFilename);
	strcat(outputFilename, ".enc");

	fptrOut = fopen(outputFilename, "wb+");
	if (fptrOut == NULL)
	{
		fprintf(stderr, "Error - Could not open output file %s.\n\n", outputFilename);
		free(buffer);
		exit(-1);
	}

	fprintf(fptrOut, "%s\n", password);
	fwrite(buffer, 1, filesize, fptrOut);
	fclose(fptrOut);
	return 0;
} // encryptFile


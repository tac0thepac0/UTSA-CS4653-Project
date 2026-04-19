// Decrypt.cpp
//
// this file contains the routines to decrypt a file
//

#include "Main.h"


// this function calls the decryption routines
char decrypt(char databyte, BYTE pwdHash[32], DWORD idx)
{
	char dataX = databyte;

// You do not need to write the code here, but you can choose to do so for debugging purposes 
// or simply to have a complete, working program

	return dataX;
} // decrypt



int decryptFile(char *inputFilename)
{
	FILE *fptrIn, *fptrOut;
	BYTE pwdHash[32], dummy = 0;
	DWORD filesize, i, passwordLength;
	DWORD *tmpd = NULL;
	int resulti, pwdHashIndx, tmpi, idx1, idx2;
	char *buffer, outputFilename[MAX_PATH+4], prevExtension[16];

	fptrIn = openInputFile(inputFilename, filesize);
	passwordLength = 0; // handlePassword(fptrIn, pwdHash);

	// allocate space and read in the file to decrypt
	buffer = (char*)malloc(filesize);
	if (buffer == NULL)
	{
		fprintf(stderr, "Error - Could not allocate %d bytes of memory on the heap.\n\n", filesize);
		exit(-1);
	}
	fread(buffer, 1, filesize, fptrIn);	// read entire file

//////////////////////////////////////////////////////////////////////////

	for (i = 0; i < filesize - (passwordLength + 1); i++)
	{
		buffer[i] = decrypt(buffer[i], pwdHash, i);
	} // end for loop through data

//////////////////////////////////////////////////////////////////////////
// Source Code Below is OK
	strcpy(outputFilename, inputFilename);

	// try to find a previous extension
	idx1 = strlen(outputFilename);
	idx2 = idx1;
	memset(prevExtension, 0, 16);
	while(idx1 > 0)
	{
		if(outputFilename[idx1] == '.')
		{
			if(memcmp(&outputFilename[idx1], ".enc", 4) == 0)	// this is not the extension we're looking for
			{
				idx2 = idx1 - 1;
				idx1 = idx2;
				continue;
			}
			else
			{
				tmpi = idx2 - idx1 + 1;
				if(tmpi > 16) tmpi = 16;
				memcpy(prevExtension, &outputFilename[idx1], tmpi);
				prevExtension[15] = 0;
				break;
			}
		}
		idx1--;
	}

	if(prevExtension[0] == 0)
		strcat(outputFilename, ".dec");
	else
		strcat(outputFilename, prevExtension);

	fptrOut = fopen(outputFilename, "wb+");
	if (fptrOut == NULL)
	{
		fprintf(stderr, "Error - Could not open output file %s.\n\n", outputFilename);
		free(buffer);
		exit(-1);
	}

	fwrite(buffer, 1, filesize - (passwordLength + 1), fptrOut);
	fclose(fptrOut);
	return 0;
} // decrypt file

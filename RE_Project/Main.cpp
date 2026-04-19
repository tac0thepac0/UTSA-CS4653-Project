// Main.cpp
//
// This program is being used for the 2016_08 CS4953 REverse Engineering Project
// It encrypts or decrypts the input file based on the password
//
// The students are given an encrypted file that has the password embedded. The program, given an input file
// extracts the password and decrypts the file.
//
// The task is to create the code to encrypt an arbitrary file, so that this specific decryption program succeeds.
//

#include "Main.h"

int gFunction = -1;	// not specified, 1 = encrypt, 2 = decrypt
char gInputFilename[MAX_PATH + 4];
char gPassword[512];
int gNumberOfPasswords = 0;

FILE *openInputFile(char *filename, DWORD &filesize)
{
	FILE *fptr;

	fptr = fopen(filename, "rb");
	if(fptr == NULL)
	{
		fprintf(stderr, "\n\nError - Could not open input file %s!\n\n", filename);
		system("pause");
		exit(-1);
	}

	fseek(fptr, 0, SEEK_END);
	filesize = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);

	if (filesize > 0x1000000)	// 16 MB, file too large
	{
		fprintf(stderr, "Error - Input file larger than 16MB - no need to waste time on huge files!\n\n");
		system("pause");
		exit(-1);
	}

	return fptr;
} // openInputFile

// show how to run the program
void usage(char* argv[])
{
	__err "\n\nTo Encrypt: ENTER \"-e filename password\"\n\n");	// argc must equal 4
	__err "	%s -e filename password\n\n", argv[0]);
	__err "The output file will have a '.enc' extension.\n\n");

	__err "\n\n *** OPTIONAL: Write the decrypt code - for debugging OR personal satisfaction.\n\n");
	__err "\n\n +++ NOTE: The included decrypt.exe takes ONE argument: the file to decrypt. No '-d' is used.\n\n"); 
	__err "\n\nTo Decrypt: ENTER \"-d filename\"\n\n");			// argc must equal 3
	__err "	%s -d filename \n\n", argv[0]);
	__err "The output file will have a '.dec' extension.\n\n");

	system("pause");
	return;
} // usage


// interprets and vets commandline arguments
void parseCommandLine(int argc, char *argv[])
{
	if (strcmp(argv[1], "-e") == 0)	// encrypt
	{
		if (argc < 4)
		{
			usage(argv);
			exit(-1);
		}

		gFunction = 1;	
		strcpy(gInputFilename, argv[2]);
		strcpy(gPassword, argv[3]);
		return;
	}

	if (strcmp(argv[1], "-d") == 0)		// decrypt
	{
		gFunction = 2;
		strcpy(gInputFilename, argv[2]);
		return;
	}

	__err "Error - Action not specified.\n\n");
	usage(argv);
	exit(-1);

	return;
} // parseCommandLine


// main function for Encrypt/Decrypt project
void main(int argc, char *argv[])
{
	if(argc < 3)
	{
		usage(argv);
		exit(0);
	}

	parseCommandLine(argc, argv);

	if(gFunction == 1)
	{
		__err "File: '%s' will be encrypted with password: %s\n\n", gInputFilename, gPassword );
		encryptFile(gInputFilename, gPassword);
	}

	if (gFunction == 2)
	{
		__err "File: '%s' will be decrypted.\n\n", gInputFilename);
		decryptFile(gInputFilename);
	}

	return ;
} // main
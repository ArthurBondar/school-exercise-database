/*
Contains list of function used to edit array
*/

#include "stdafx.h"
#include <stdlib.h>
#include <time.h>       // for random function
#include "FileIO.h"


/* @param1	Pointer to the first element in the array of pointers to records
   @return	Size of elements uploaded from file  */
int LoadData(struct record ** _rec)
{
	struct record *_mem;

	FILE *bfile = fopen("DataBase.bin", "r");

	if (bfile != NULL)
	{
		/* Getting the number of record from the file */
		fseek(bfile, 0, SEEK_END);
		int sz = ftell(bfile) / sizeof(struct record);
		fseek(bfile, 0, SEEK_SET);

		/* Allocating memory for the records */
		for (int i = 0; i < sz; i++)	
		{
			_mem = (struct record *) malloc(sizeof(struct record));
			fread(_mem, sizeof(struct record), 1, bfile);
			_rec[i] = _mem;
		}

		fclose(bfile);
		return sz;
	}
	else
	{
		return 0;
	}
}


/* @param1	Pointer to the first element in the array of pointers to records
   @param2  Size of elements needed to be stored
   @return	0 - save succeded
			1 - cannot write into the file */
int SaveData(struct record ** _rec, int elements)
{
	FILE *bfile = fopen("DataBase.bin", "w");

	if (ferror(bfile))
	{
		return 1;
	}
	else
	{
		/* writing each record at a time in a loop */
		for (int i = 0; i < elements; i++)
		{
			fwrite(_rec[i], sizeof(struct record), 1, bfile);
		}
		/* closing the file */
		fclose(bfile);
		return 0;
	}
}



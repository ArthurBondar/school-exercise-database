/*	W0401444 Arthur Bondar
	29.03.17 Project 2
	EETG Programming I
	End of Term Project uses pointer and structures */
#include "stdafx.h"
#include "FileIO.h"
#include "StructEdit.h"

#define REC_NUM 10						// number of records

/* Displaying menu window and scanning user selection */
int menu(int*);

/*  Function flow:
	1. Loads records from DataBase.bin file
	2. Manipulates records in the program loop, calling
	functions for Creating, modifying, sorting and deleting
	3. Saves the records in DataBase.bin file          */
void main()
{
	int selection = NULL, error = 0, quit = 0;
	int rec_count = 0;					// Stores number of records
	struct record *rec[REC_NUM];

	printf("************* WELCOME! *************\n\n");
	printf("Would you like to load data from DataBase.bin? y/n\n");
	/* Pulling records from file DataBase.bin */
	rewind(stdin);
	if(getc(stdin) == 'y') 
		rec_count = LoadData(&rec);

	/* Program Loop	*/
	while (!quit)	
	{
		system("cls");
		error = menu(&selection);		// getting the desired operation

		if (!error)
		{
			switch (selection)
			{
			case 1:		// creating new record
				if (rec_count > REC_NUM) // record limit has been reached
					error = RECORDS_LIMIT;
				else
				{	// Creating a record and incrementing total record count
					error = CreateRec(&rec[rec_count], rec_count);
					if(!error) rec_count++;
				}
				break;
			case 2:		// modifing existing record
				error = ModifyRec(&rec[0], rec_count);
				break;
			case 3:		// printing records
				error = PrintRec(&rec[0], rec_count);
				break;
			case 4:		// sorting records
				error = SortArr(&rec[0], rec_count);
				break;
			case 5:		// deleting a record
				error = DeleteRec(&rec[0], rec_count);
				if(!error) rec_count--;
				break;
			case 6:		// Exiting
				quit = 1;
				break;
			default:
				break;
			}
		}

		/* Errpr Handeling */
		if (error)
		{
			printf("\nERROR:\n");
			if (error == INVALID_SELECTION)
				printf("Invalid selection has been made\n");

			if (error == ALLOCATION_ERROR)
				printf("Cannot allocate memory\n");

			if (error == RECORDS_LIMIT)
				printf("Maximum number of records has been reached\n");

			if (error == INVALID_RECORD_ACCESS)
				printf("Record does not exist\n");

			if (error == INVALID_RECORD_RANGE)
				printf("Invalid record range\n");

			printf("\n");
			system("pause");
		}
	}
	/* Re-saving all the records in a file DataBase.bin */
	error = SaveData(&rec, rec_count);

	/* De-allocating dynamically allocated memory for the array of pointer	*/
	for (int i = 0; i < rec_count; i++)
		free(rec[i]);

	if (!error) printf("\nRecords saved succesfully\n\n");
	else	printf("\nRecords cannot be saved\n\n");

	printf("Program terminated by the operator\n");
	system("pause");
}

/*  @param1 Out-Parameter - selection made by the user
	@return 0 if selection is valid
	INVALID_SELECTION if improper selection has been made	*/
int menu(int *_selection)
{
	int s;
	printf("************* Data Base *************\n\n");
	printf("Select desired operation:\n");
	printf("1 - Created new record\n");
	printf("2 - Modify existing record\n");
	printf("3 - Print records\n");
	printf("4 - Sort records\n");
	printf("5 - Delete record\n");
	printf("6 - to quit\n\n");

	rewind(stdin);
	scanf("%d", &s);

	if (s > 6 || s < 1)		
		return INVALID_SELECTION;
	else
	{
		*_selection = s;
		return 0;
	}
}







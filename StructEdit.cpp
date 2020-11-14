/*
Contains list of function used to edit array
*/

#include "stdafx.h"
#include <stdlib.h>
#include <ctype.h>		// used to convert upper and lowercase
#include "StructEdit.h"


/* This function allocates memory and fills it up with user input, and 
   assigns next available pointer in the array of pointer - rec to that memory location
   @param1	Pointer to an array of pointers to memory locations of records
   @param2  Number of records in the array
   @return	0 - created succesfully
			ALLOCATION_ERROR - cannot allocate memory */
int CreateRec(struct record** _record, int rec_count)
{
	/* Allocating the memory */
	struct record *_rec = (struct record *) malloc(sizeof(struct record));

	if (_rec == NULL)
		return ALLOCATION_ERROR;
	else
	{
		system("cls");
		printf("------ Record Creation ------\n\n");

		_rec->Rec_number = rec_count + 1;			// Saving record number

		printf("\nPlease Enter: First Name\n");
		rewind(stdin);
		scanf("%[a-zA-Z]", _rec->First_Name);

		printf("\nPlease Enter: Last Name\n");
		rewind(stdin);
		scanf("%[a-zA-Z]", _rec->Last_Name);

		printf("\nPlease Enter: Age\n");
		rewind(stdin);
		scanf("%d", &(_rec->Age));

		printf("\nPlease Enter: Gender - m/f\n");
		rewind(stdin);
		if (getc(stdin) == 'm') strcpy(_rec->Gender, "Male");
		else strcpy(_rec->Gender, "Female");

		/* Referencing the pointer in the array rec to the memory location _rec */
		*_record = _rec;

		printf("\n----------------------------------");
		printf("\nRecord number: %d has been created\n\n", rec_count + 1);
		system("pause");

		return 0;
	}

}

/* This function prints one record, or a range of records 1-XX
	@param1	Pointer to an array of pointers to memory locations of records
	@param2  Number of records in the array
	@return	0 - printed succesfully
			INVALID_RECORD_RANGE - improper range
			INVALID RECORD ACCESS - improper record number given */
int PrintRec(struct record** _rec, int rec_count)
{
	char s[10];					// string input
	memset(s, NULL, sizeof(s));
	int range[2] = { -1, -1 };	// storing range of records for printing	

	system("cls");
	printf("------ Record Printing ------\n\n");
	printf("Number of records: %d\n\n", rec_count);
	printf("Enter the record, or range of records you would like to display\n");

	/* Getting Input record number or range of records */
	rewind(stdin);
	scanf("%s", s);

	/* Cheking for range or single print selection	*/
	if (isdigit(s[0]))
	{
		if (isdigit(s[2]))		// range print selection
			sscanf(s, "%d-%d", &range[0], &range[1]);
		else					// single print selection
			sscanf(s, "%d", &range[0]);
	}

	/* Error Checking	*/
	if ((range[0] >= range[1]) && range[1] != -1)
		return INVALID_RECORD_RANGE;
	else if (range[0] > rec_count || range[0] < 1)
		return INVALID_RECORD_ACCESS;
	else
	{    /*	Printing range of records in a loop	*/
		
		int prints;				// number of prints
		if (range[1] == -1) prints = 0;	// if the secord number wasnt given, prints once
		else prints = range[1] - range[0];// otherwise prints in a loop that runs prints iterations

		/*  if range selected printing in a loop 
			if one number is entered runs the loop only once	*/
		for (int i = (range[0] - 1); i < (range[0] + prints); i++)
		{
			printf("\nRecord Number:\t%d", _rec[i]->Rec_number);
			printf("\nFirst Name:\t%s", _rec[i]->First_Name);
			printf("\nLast Name:\t%s", _rec[i]->Last_Name);
			printf("\nAge:\t\t%d", _rec[i]->Age);
			printf("\nGender:\t\t%s\n", _rec[i]->Gender);
		}

		printf("\n");
		system("pause");
		return 0;
	}
}

/* This function changes the contant of a record given by the user
	@param1	Pointer to an array of pointers to memory locations of records
	@param2  Number of records in the array
	@return	0 - modified succesfully
			INVALID RECORD ACCESS - improper record number given 
			INVALID SELECTION - improper selection */
int ModifyRec(struct record ** _rec, int rec_count)
{
	int i, select;

	system("cls");
	printf("------ Record Modification ------\n\n");
	printf("Number of records: %d\n\n", rec_count);

	printf("Enter the record number you would like to modify\n");
	/* Getting input - record number */
	rewind(stdin);
	scanf("%d", &i);

	if (i > rec_count || i < 1)
		return INVALID_RECORD_ACCESS;
	else
	{
		printf("\nEnter the field number you would like to modify:\n");
		printf("1. First Name\n");
		printf("2. Last Name\n");
		printf("3. Age\n");
		printf("4. Gender\n");
		/* Getting Input - field to modify */
		rewind(stdin);
		scanf("%d", &select);
		printf("\n");

		switch (select)	// prints the current field and saves the new information
		{
		case 1:		// modifying first name
			printf("Current First name: %s\n", _rec[i - 1]->First_Name);
			printf("New First name: ");
			rewind(stdin);
			scanf("%s", _rec[i - 1]->First_Name);
			break;
		case 2:		// modifying last name
			printf("Current Last name: %s\n", _rec[i - 1]->Last_Name);
			printf("New Last name: ");
			rewind(stdin);
			scanf("%s", _rec[i - 1]->Last_Name);
			break;
		case 3:		// modifying age
			printf("Current Age: %d\n", _rec[i - 1]->Age);
			printf("New Age: ");
			rewind(stdin);
			scanf("%d", &(_rec[i - 1]->Age));
			break;
		case 4:		// modifying gender
			printf("Current Gender: %s\n", _rec[i - 1]->Gender);
			printf("New Gender m/f: ");
			rewind(stdin);
			if (getc(stdin) == 'm') strcpy(_rec[i - 1]->Gender, "Male");
			else strcpy(_rec[i - 1]->Gender, "Female");
			break;
		default:
			return INVALID_SELECTION;
			break;
		}

		printf("\nRecord Updated Succesfully\n\n");
		system("pause");
		return 0;
	}
}

/* This function gets the crateria for sorting the records and 
	uses bubble sorting algorithm to sort the records
	@param1	Pointer to an array of pointers to memory locations of records
	@param2  Number of records in the array
	@return	0 - sorted succesfully
			INVALID SELECTION - improper selection */
int SortArr(struct record** _rec, int rec_count)
{
	int select;

	system("cls");
	printf("------ Record Sorting ------\n\n");

	printf("Enter the criteria based on which you would like to sort records:\n");
	printf("1. Record number\n");
	printf("2. First Name\n");
	printf("3. Last Name\n");
	printf("4. Age\n");
	/* Getting input - sort mode */
	rewind(stdin);
	scanf("%d", &select);

	switch (select)
	{			
	case 1:		// Sorting based on Record Number
		for (int x = 0; x < rec_count - 1; x++)			
		{
			for (int y = 0; y < (rec_count - x - 1); y++)
			{
				if (_rec[y]->Rec_number > _rec[y+1]->Rec_number)
					Swap(&_rec[y], &_rec[y + 1]);
			}
		}
		break;
	case 2:		// Sorting based on First Name
		for (int x = 0; x < rec_count - 1; x++)
		{
			for (int y = 0; y < (rec_count - x - 1); y++)
			{   /*  To make the function sort capital letter and lower case
					I converted to lower case and compared using strcmp	 */
				char temp1[15], temp2[15];
				strcpy(temp1, _rec[y]->First_Name);
				strcpy(temp2, _rec[y+1]->First_Name);
				*temp1 = tolower(*temp1); *temp2 = tolower(*temp2);//converting
				if (strcmp(temp1, temp2) > 0)	  // comparing
					Swap(&_rec[y], &_rec[y + 1]); //swaps the two records
			}
		}
		break;
	case 3:		// Sorting based on Last Name
		for (int x = 0; x < rec_count - 1; x++)
		{
			for (int y = 0; y < (rec_count - x - 1); y++)
			{
				char temp1[15], temp2[15];
				strcpy(temp1, _rec[y]->Last_Name);
				strcpy(temp2, _rec[y + 1]->Last_Name);
				*temp1 = tolower(*temp1); *temp2 = tolower(*temp2);
				if (strcmp(temp1, temp2) > 0)
					Swap(&_rec[y], &_rec[y + 1]);
			}
		}
		break;
	case 4:		// Sorting based on Age
		for (int x = 0; x < rec_count - 1; x++)
		{
			for (int y = 0; y < (rec_count - x - 1); y++)
			{
				if (_rec[y]->Age > _rec[y + 1]->Age)
					Swap(&_rec[y], &_rec[y + 1]);
			}
		}
		break;
	default:    // Improper selection
		return INVALID_SELECTION;
		break;
	}

	printf("\n\nSort Completed Succesfully\n\n");
	system("pause");

	return 0;
}

/* This function swaps two pointers to records in the 'rec' pointer array */
void Swap(struct record** rec1, struct record** rec2)
{
	struct record *temp;	// temporary pointer

	temp = *rec2;
	*rec2 = *rec1;
	*rec1 = temp;
}

/* This function sorts the records based on record number, 
	de-allocates memory for the record that user wants to delete,
	decrements all following record numbers
	@param1	Pointer to an array of pointers to memory locations of records
	@param2 Number of records in the array
	@return	0 - deleted succesfully
			INVALID RECORD ACCESS - improper record number given */
int DeleteRec(struct record ** _rec, int rec_count)
{
	int select;

	system("cls");
	printf("------ Removing Record ------\n\n");
	printf("Number of records: %d\n\n", rec_count);

	printf("Enter the record number you would like to delete:\n");
	/* Getting input - record to delete */
	rewind(stdin);
	scanf("%d", &select);

	if (select > rec_count || select < 1)
		return INVALID_RECORD_ACCESS;
	else
	{
		/* Sorting records by record number */
		for (int x = 0; x < rec_count - 1; x++)
		{
			for (int y = 0; y < (rec_count - x - 1); y++)
			{
				if (_rec[y]->Rec_number > _rec[y + 1]->Rec_number)
					Swap(&_rec[y], &_rec[y + 1]);
			}
		}

		/* De-allocating record memory space */
		free(_rec[select - 1]);

		/* Moving all records and decrementing record numbers*/
		for (int i = select-1; i < rec_count-1; i++)
		{
			_rec[i] = _rec[i + 1];
			_rec[i]->Rec_number--;
		}

		printf("\nRecord deleted succesfully\n\n");
		system("pause");
		return 0;
	}

}









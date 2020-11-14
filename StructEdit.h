#pragma once

/*
W0401444 Arthur Bondar
29.03.17 Project 2
EETG Programming I
*/

/* Creating new memory space for a record and adding it to the array of records */
int CreateRec(struct record**, int);

/* Modifying existing record in memory */
int ModifyRec(struct record**, int);

/* Prining one record or range of records from the array of records */
int PrintRec(struct record**, int);

/* Sorting the records based on crateria given by the user */
int SortArr(struct record**, int);

/* Swaps two records in the array of records, used for sorting records */
void Swap(struct record*, struct record*);

/* De-Allocating a memory for a record and moving other existing records*/
int DeleteRec(struct record **, int);


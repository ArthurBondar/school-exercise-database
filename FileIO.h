#pragma once

/*
W0401444 Arthur Bondar
29.03.17 Project 2
EETG Programming I
*/


/* Loading the array of records with data from DataBase.bin
returning the number of records uploaded, if file doesnt exist returns 0 */
int LoadData(struct record **);

/* Stores the data from array of structures to a file DataBase.bin */
int SaveData(struct record **, int);








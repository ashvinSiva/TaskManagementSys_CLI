#include <stdio.h>

typedef struct
{
    int ID;
    char description[100];
    char due_date[12]; // YYYY-MM-DD + '\0'
    char priority[7];  // Medium + '/0'
    char done[4];      // Yes or No + '\0'

} Task;

void displayTitle();
void displayTable();
void addTask();
void deleteTask();
void completeTask();


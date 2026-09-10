#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "base.h"

#define PASSWORD 1085

//------------- GLOBAL VARIABLES -------------//

Task *task;
int idx = 0;
bool taskAdded = false;

//------------------- MAIN -------------------//

int main()
{
    task = malloc(sizeof(Task));
    if (task == NULL)
    {
        return 1;
    }

    int choice;
    bool exit = false;

    while (!exit)
    {
        displayTable();
        displayTitle();
        printf("Command Choice: ");
        int s = scanf("%d", &choice);

        //-----------Handles string input error-----------//
        while (s == 0)
        {
            while (getchar() != '\n')
                ;

            printf("\nInvalid input, try again\n");
            printf("Command Choice: ");
            s = scanf("%d", &choice);
        }
        //------------------------------------------------//

        getchar(); // takes away the implicit character '\n'

        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            deleteTask();
            break;
        case 3:
            completeTask();
            break;
        case 4:
            displayTable();
            break;
        case PASSWORD:
            printf("\nExiting program...\n");
            exit = true;
            break;
        default:
            printf("\nInvalid Choice, please choose the correct one\n");
            break;
        }
    }

    free(task);
    task = NULL;

    return 0;
}

//---------------- FUNCTIONS ----------------//

void displayTitle()
{
    printf("=============================================================\n");
    printf("                   TASK MANAGEMENT SYSTEM                    \n");
    printf("=============================================================\n\n");
    printf("Enter your choice: \n");
    printf("------------------\n");
    printf("1. Add Task\n");
    printf("2. Delete Task\n");
    printf("3. Complete Task\n");
    printf("4. Display Table of Task Management\n\n");
}

void displayTable()
{
    printf("=============================================================\n");
    printf("||%s || %-22s || %s ||%s||%s||\n", "ID", "Task", "Due Date", "Priority", "Done");
    printf("=============================================================\n");

    if (taskAdded)
    {
        for (int i = 0; i < idx; i++)
        {
            printf("|| %d || %-22s ||%-10s||%-8s||%-4s||\n", task[i].ID, task[i].description, task[i].due_date, task[i].priority, task[i].done);
        }
    }
}

void addTask()
{

    task[idx].ID = idx + 1;
    char *newline = NULL;
    printf("Task: ");
    fgets((task + idx)->description, sizeof(task->description), stdin);
    newline = strchr((task + idx)->description, '\n');
    if (newline)
        *newline = '\0';

    printf("Due Date (YYYY-MM-DD): ");
    fgets((task + idx)->due_date, sizeof(task->due_date), stdin);
    newline = strchr((task + idx)->due_date, '\n');
    if (newline)
        *newline = '\0';

    printf("Priority (Low, Medium, High): ");
    fgets((task + idx)->priority, sizeof(task->priority), stdin);
    newline = strchr((task + idx)->priority, '\n');
    if (newline)
        *newline = '\0';

    strcpy(task[idx].done, "No");

    idx++;

    Task *temp = realloc(task, (idx + 1) * sizeof(Task));

    if (temp == NULL)
    {
        idx--;
        printf("Adding task was unsuccessful\n");
        return;
    }

    task = temp;

    taskAdded = true;

    if (idx != 0)
        printf("\nTask %d added!\n", task[idx - 1].ID);
}

void deleteTask()
{
    int getID = 0;
    printf("Please enter the Task ID to delete task: ");
    scanf("%d", &getID);

    if (getID <= 0 || idx < getID)
    {
        printf("Task ID = %d cannot be found\n", getID);
        return;
    }

    for (int i = getID - 1; i < idx - 1; i++)
    {
        task[i] = task[i + 1];
    }
    idx--;

    for (int i = 0; i < idx; i++)
    {
        task[i].ID = i + 1;
    }
}

void completeTask()
{
    int completeID = 0;
    printf("Enter the Task ID you have completed: ");
    scanf("%d", &completeID);

    if (completeID <= 0 || idx < completeID)
    {
        printf("Cannot find Task ID = %d", completeID);
        return;
    }

    strcpy(task[completeID - 1].done, "Yes");

    printf("\necompleting task...\n");
}

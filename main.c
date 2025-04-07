#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAX_SUBJECTS 10
#define MAX_STUDENTS 100

COORD coord = {0, 0};

void gotoxy(int x, int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

struct Student
{
    int id;
    char name[100];
    int numSubjects;
    char subjects[MAX_SUBJECTS][100];
    int scores[MAX_SUBJECTS];
};
struct Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent()
{
    system("cls");
    printf("Add Student \n");
    struct Student student;

    int isIdExist = 0;
    printf("Enter the id: ");
    scanf("%d", &student.id);

    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == student.id)
        {
            isIdExist = 1;
            break;
        }
    }

    if (isIdExist)
    {
        SetColor(12);
        printf("Error: Student with ID %d already exists!\n", student.id);
        SetColor(15);
        printf("Press any key to return to the main menu...");
        _getch();
        return;
    }

    printf("Enter the name: ");
    scanf("%s", student.name);
    printf("Enter the number of subjects: ");
    scanf("%d", &student.numSubjects);
    for (int i = 0; i < student.numSubjects; i++)
    {
        printf("Enter the name of subject %d: ", i + 1);
        scanf("%s", student.subjects[i]);
        printf("Enter the score for %s: ", student.subjects[i]);
        scanf("%d", &student.scores[i]);
    }
    students[studentCount] = student;
    studentCount++;
    printf("Student added successfully!\n");
    printf("Press any key to return to the main menu...");
    _getch();
}

void updateStudent()
{
    system("cls");
    printf("Update Student \n");
    int idToUpdate, newScore;
    printf("Enter the student id to update: ");
    scanf("%d", &idToUpdate);
    struct Student *studentToUpdate = NULL;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == idToUpdate)
        {
            studentToUpdate = &students[i];
            break;
        }
    }

    if (studentToUpdate != NULL)
    {
        printf("Student found: %s\n", studentToUpdate->name);
        for (int i = 0; i < studentToUpdate->numSubjects; i++)
        {
            printf("Enter the new score for %s: ", studentToUpdate->subjects[i]);
            scanf("%d", &newScore);
            studentToUpdate->scores[i] = newScore;
        }
        printf("Scores updated successfully!\n");
    }
    else
    {
        SetColor(12);
        printf("Student with id %d not found!\n", idToUpdate);
        SetColor(15);
    }
    printf("Press any key to return to the main menu...");
    _getch();
}

void calculateGrade()
{
    system("cls");
    printf("Calculate Grade Page\n");
    int idToSearch;
    printf("Enter the student id to calculate grade: ");
    scanf("%d", &idToSearch);

    struct Student *studentToCalculate = NULL;
    for (int i = 0; i < studentCount; i++)
    {
        if (students[i].id == idToSearch)
        {
            studentToCalculate = &students[i];
            break;
        }
    }

    if (studentToCalculate != NULL)
    {
        int totalScore = 0;
        float average;

        for (int i = 0; i < studentToCalculate->numSubjects; i++)
        {
            totalScore += studentToCalculate->scores[i];
        }

        average = (float)totalScore / studentToCalculate->numSubjects;

        char grade;
        if (average >= 90)
        {
            grade = 'A';
        }
        else if (average >= 80)
        {
            grade = 'B';
        }
        else if (average >= 70)
        {
            grade = 'C';
        }
        else if (average >= 60)
        {
            grade = 'D';
        }
        else
        {
            grade = 'F';
        }

        printf("\nStudent: %s\n", studentToCalculate->name);
        printf("Average: %.2f\n", average);
        printf("Grade: %c\n", grade);
    }
    else
    {
        SetColor(12);
        printf("Student with ID %d not found!\n", idToSearch);
        SetColor(15);
    }
    printf("Press any key to return to the main menu...");
    _getch();
}

void displayAllStudents()
{
    system("cls");
    printf("All Students\n");
    if (studentCount == 0)
    {
        printf("No students to display.\n");
    }
    else
    {
        for (int i = 0; i < studentCount; i++)
        {
            printf("ID: %d, Name: %s\n", students[i].id, students[i].name);

            int totalScore = 0;
            for (int j = 0; j < students[i].numSubjects; j++)
            {
                totalScore += students[i].scores[j];
            }
            float average = (float)totalScore / students[i].numSubjects;

            char grade;
            if (average >= 90)
            {
                grade = 'A';
            }
            else if (average >= 80)
            {
                grade = 'B';
            }
            else if (average >= 70)
            {
                grade = 'C';
            }
            else if (average >= 60)
            {
                grade = 'D';
            }
            else
            {
                grade = 'F';
            }

            char *status = (average >= 60) ? "Passed" : "Failed";

            printf("  Average Score: %.2f\n", average);
            printf("  Grade: %c\n", grade);
            printf("  Status: %s\n", status);

            for (int j = 0; j < students[i].numSubjects; j++)
            {
                printf("  Subject: %s, Score: %d\n", students[i].subjects[j], students[i].scores[j]);
            }
            printf("\n");
        }
    }
    printf("Press any key to return to the display results menu...");
    _getch();
}

void displayHighestAverage()
{
    system("cls");
    printf("Highest Average Score\n");
    if (studentCount == 0)
    {
        printf("No students available.\n");
    }
    else
    {
        float highestAverage = -1;
        struct Student *bestStudent = NULL;

        for (int i = 0; i < studentCount; i++)
        {
            int totalScore = 0;
            for (int j = 0; j < students[i].numSubjects; j++)
            {
                totalScore += students[i].scores[j];
            }
            float average = (float)totalScore / students[i].numSubjects;

            if (average > highestAverage)
            {
                highestAverage = average;
                bestStudent = &students[i];
            }
        }

        if (bestStudent != NULL)
        {
            printf("Student: %s\n", bestStudent->name);
            printf("Average: %.2f\n", highestAverage);
        }
    }
    printf("Press any key to return to the display results menu...");
    _getch();
}

void displayAverageScore()
{
    system("cls");
    printf("Average Score of All Students\n");
    if (studentCount == 0)
    {
        printf("No students available.\n");
    }
    else
    {

        for (int i = 0; i < studentCount; i++)
        {
            int totalScore = 0;
            for (int j = 0; j < students[i].numSubjects; j++)
            {
                totalScore += students[i].scores[j];
            }
            float average = (float)totalScore / students[i].numSubjects;

            printf("Student: %s, Average: %.2f\n", students[i].name, average);
        }
    }
    printf("Press any key to return to the display results menu...");
    _getch();
}

void displayPassedStudents()
{
    system("cls");
    printf("Passed Students\n");
    if (studentCount == 0)
    {
        printf("No students available.\n");
    }
    else
    {

        for (int i = 0; i < studentCount; i++)
        {
            int totalScore = 0;
            for (int j = 0; j < students[i].numSubjects; j++)
            {
                totalScore += students[i].scores[j];
            }
            float average = (float)totalScore / students[i].numSubjects;

            if (average >= 60)
            {
                printf("Student: %s, Average: %.2f\n", students[i].name, average);
            }
        }
    }
    printf("Press any key to return to the display results menu...");
    _getch();
}

void displayFailedStudents()
{
    system("cls");
    printf("Failed Students\n");
    if (studentCount == 0)
    {
        printf("No students available.\n");
    }
    else
    {

        for (int i = 0; i < studentCount; i++)
        {
            int totalScore = 0;
            for (int j = 0; j < students[i].numSubjects; j++)
            {
                totalScore += students[i].scores[j];
            }
            float average = (float)totalScore / students[i].numSubjects;

            if (average < 60)
            {
                printf("Student: %s, Average: %.2f\n", students[i].name, average);
            }
        }
    }
    printf("Press any key to return to the display results menu...");
    _getch();
}

void displayResultsMenu()
{
    int choice = 0;
    int totalOptions = 5;
    char *menuOptions[] =
    {
        "1. Display all students",
        "2. Display highest average score",
        "3. Display average score of all students",
        "4. Display students passed",
        "5. Display students failed"
    };

    while (1)
    {
        system("cls");
        printf("Display Results Menu\n");

        for (int i = 0; i < totalOptions; i++)
        {
            if (i == choice)
            {
                SetColor(12);
                printf("> %s\n", menuOptions[i]);
                SetColor(15);
            }
            else
            {
                SetColor(15);
                printf("  %s\n", menuOptions[i]);
            }
        }

        char key = _getch();
        if (key == 72)
        {
            choice = (choice - 1 + totalOptions) % totalOptions;
        }
        else if (key == 80)
        {
            choice = (choice + 1) % totalOptions;
        }
        else if (key == 13)
        {
            break;
        }
    }

    switch (choice)
    {
    case 0:
        displayAllStudents();
        break;
    case 1:
        displayHighestAverage();
        break;
    case 2:
        displayAverageScore();
        break;
    case 3:
        displayPassedStudents();
        break;
    case 4:
        displayFailedStudents();
        break;
    }
}

void displayMenu()
{
    int screenWidth = 140;
    int menuWidth = 50;
    int x = (screenWidth - menuWidth) / 2;
    int y = 8;
    int choice = 0;
    int totalOptions = 5;
    char *menuOptions[] =
    {
        "1. Add Student",
        "2. Update Student",
        "3. Calculate Grades for All Students",
        "4. Display Results",
        "5. Exit"
    };

    while (1)
    {
        system("cls");
        gotoxy(x, y);
        printf("Student Grade Management System\n");

        for (int i = 0; i < totalOptions; i++)
        {
            gotoxy(x, y + i + 1);
            if (i == choice)
            {
                SetColor(12);
                printf("> %s", menuOptions[i]);
                SetColor(15);
            }
            else
            {
                SetColor(15);
                printf("  %s", menuOptions[i]);
            }
        }

        char key = _getch();
        if (key == 72)
        {
            choice = (choice - 1 + totalOptions) % totalOptions;
        }
        else if (key == 80)
        {
            choice = (choice + 1) % totalOptions;
        }
        else if (key == 13)
        {
            break;
        }
    }

    switch (choice)
    {
    case 0:
        addStudent();
        break;
    case 1:
        updateStudent();
        break;
    case 2:
        calculateGrade();
        break;
    case 3:
        displayResultsMenu();
        break;
    case 4:
        exit(0);
        break;
    }
}

int main()
{
    while (1)
    {
        displayMenu();
    }
    return 0;
}

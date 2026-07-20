#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "student_registry.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX) {
        printf("Student list is full!\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &students[*count].id);
    clearBuffer();

    printf("Enter Name: ");
    fgets(students[*count].name, sizeof(students[*count].name), stdin);
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';

    printf("Enter Major: ");
    fgets(students[*count].major, sizeof(students[*count].major), stdin);
    students[*count].major[strcspn(students[*count].major, "\n")] = '\0';

    printf("Enter GPA: ");
    scanf("%f", &students[*count].gpa);

    printf("Enter Credits: ");
    scanf("%d", &students[*count].credits);
    clearBuffer();

 
    (*count)++;
    
    
    saveStudentsToFile(students, *count);
}

void displayStudents(Student students[], int count) {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    if (count == 0) {
        printf("--- Current Database State ---\n");
        printf("No students found. The registry is empty.\n");
        printf("------------------------------\n");
        return;
    }

    printf("--- Current Database State ---\n");
    printf("%-8s %-20s %-20s %-6s %-8s\n", "ID", "Name", "Major", "GPA", "Credits");
    printf("-----------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-8d %-20s %-20s %-6.2f %-8d\n",
               students[i].id,
               students[i].name,
               students[i].major,
               students[i].gpa,
               students[i].credits);
    }
    printf("-----------------------------------------------------------------\n");
}

void searchByID(Student students[], int count) {
    int id;
    int found = 0;

    printf("Enter Student ID: ");
    scanf("%d", &id);
    clearBuffer();

    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            printf("\nStudent Found\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Major: %s\n", students[i].major);
            printf("GPA: %.2f\n", students[i].gpa);
            printf("Credits: %d\n", students[i].credits);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");
}

void searchByGPA(Student students[], int count) {
    float limit;
    int found = 0;

    printf("Enter minimum GPA: ");
    scanf("%f", &limit);
    clearBuffer();

    printf("\nStudents with GPA = %.2f\n", limit);
    for (int i = 0; i < count; i++) {
        if (students[i].gpa == limit) {
            printf("%d | %s | %s | %.2f | %d\n",
                   students[i].id,
                   students[i].name,
                   students[i].major,
                   students[i].gpa,
                   students[i].credits);
            found = 1;
        }
    }

    if (!found)
        printf("No students found.\n");
}

void searchByMajor(Student students[], int count) {
    char major[50];
    int total = 0;

    printf("Enter Major: ");
    fgets(major, sizeof(major), stdin);
    major[strcspn(major, "\n")] = '\0';

    printf("\nStudents in %s\n", major);
    for (int i = 0; i < count; i++) {
        if (strcmp(students[i].major, major) == 0) {
            printf("%d | %s | GPA: %.2f | Credits: %d\n",
                   students[i].id,
                   students[i].name,
                   students[i].gpa,
                   students[i].credits);
            total++;
        }
    }
    printf("Total Students: %d\n", total);
}

void saveStudentsToFile(Student students[], int count) {
    FILE *file = fopen("students.dat", "w");

    if (file == NULL) {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d|%s|%s|%.2f|%d\n",
                students[i].id,
                students[i].name,
                students[i].major,
                students[i].gpa,
                students[i].credits);
    }

    fclose(file);
}

void loadStudentsFromFile(Student students[], int *count) {
    FILE *file = fopen("students.dat", "r");

    if (file == NULL) {
        *count = 0;
        return;
    }

    *count = 0;

    while (fscanf(file,
                  "%d|%99[^|]|%49[^|]|%f|%d\n",
                  &students[*count].id,
                  students[*count].name,
                  students[*count].major,
                  &students[*count].gpa,
                  &students[*count].credits) == 5) 
    {
        (*count)++;

        if (*count >= MAX)
            break;
    }
    fclose(file);
}

void deleteStudent(Student students[], int *count) {
    int id, foundIndex = -1;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    clearBuffer();

    
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf("Student ID not found.\n");
        return;
    }


    for (int i = foundIndex; i < (*count) - 1; i++) {
        students[i] = students[i + 1];
    }

    (*count)--; 
    saveStudentsToFile(students, *count);
    printf("Student deleted successfully!\n");
}

void searchByName(Student students[], int count) {
    char targetName[100];
    int found = 0;

    printf("Enter Student Name to search: ");
    fgets(targetName, sizeof(targetName), stdin);
    targetName[strcspn(targetName, "\n")] = '\0'; // Remove trailing newline

    printf("\n--- Search Results for Name: \"%s\" ---\n", targetName);
    for (int i = 0; i < count; i++) {
        // strstr checks if targetName is contained anywhere inside students[i].name (case-sensitive)
        if (strstr(students[i].name, targetName) != NULL) {
            printf("%d | %s | Major: %s | GPA: %.2f | Credits: %d\n",
                   students[i].id, students[i].name, students[i].major, 
                   students[i].gpa, students[i].credits);
            found = 1;
        }
    }

    if (!found) {
        printf("No students found matching that name.\n");
    }
    printf("----------------------------------------\n");
}

void searchByCredits(Student students[], int count) {
    int targetCredits;
    int found = 0;

    printf("Enter exact number of credits to search: ");
    scanf("%d", &targetCredits);
    clearBuffer();

    printf("\n--- Search Results for Credits: %d ---\n", targetCredits);
    for (int i = 0; i < count; i++) {
        if (students[i].credits == targetCredits) {
            printf("%d | %s | Major: %s | GPA: %.2f | Credits: %d\n",
                   students[i].id, students[i].name, students[i].major, 
                   students[i].gpa, students[i].credits);
            found = 1;
        }
    }

    if (!found) {
        printf("No students found with exactly %d credits.\n", targetCredits);
    }
    printf("----------------------------------------\n");
}
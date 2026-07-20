#include <stdio.h>
#include <sys/stat.h>
#include "student_registry.h"

long long getFileModifiedTime(const char *filename) {
    struct stat attr;
    if (stat(filename, &attr) == 0) {
        return (long long)attr.st_mtime;
    }
    return 0;
}

int main() {
    Student students[MAX];
    int count = 0;
    int choice;
    const char *filename = "students.dat";
    
    long long lastModifiedTime = getFileModifiedTime(filename);

    loadStudentsFromFile(students, &count);

    do {

        long long currentModifiedTime = getFileModifiedTime(filename);
        if (currentModifiedTime != lastModifiedTime) {
            lastModifiedTime = currentModifiedTime;
            loadStudentsFromFile(students, &count);
            displayStudents(students, count);
        }

        printf("\n===== STUDENT RECORD SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search by ID\n");
        printf("5. Search by Name\n");
        printf("6. Search by Major\n");
        printf("7. Search by GPA\n");
        printf("8. Search by Credits\n");
        printf("9. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
            continue;
        }

        
        int c;
        while ((c = getchar()) != '\n' && c != EOF); 

        if (choice == 1) {
            addStudent(students, &count);
            lastModifiedTime = getFileModifiedTime(filename); 
        }
        else if (choice == 2) {
            displayStudents(students, count);
        }
        else if (choice == 3) {
            searchByID(students, count);
        }
        else if (choice == 4) {
            searchByGPA(students, count);
        }
        else if (choice == 5) {
            searchByMajor(students, count);
        }
        
        else if (choice == 6) {
            searchByName(students, count);
        }
        else if (choice == 7) {
            searchByCredits(students, count);
        }
        else if (choice == 8) {
            deleteStudent(students, &count);
            lastModifiedTime = getFileModifiedTime(filename);
        }
        else if (choice == 9) {
            saveStudentsToFile(students, count); 
            printf("Exiting program...\n");
        }
        else {
            printf("Invalid choice!\n");
        }

    } while (choice != 9);
    return 0;
}
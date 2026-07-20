#ifndef STUDENT_REGISTRY_H
#define STUDENT_REGISTRY_H

#define MAX 50

typedef struct {
    int id;
    char name[100]; 
    char major[50];
    float gpa;
    int credits;
} Student;

void addStudent(Student students[], int *count);
void displayStudents(Student students[], int count);
void searchByID(Student students[], int count);
void searchByGPA(Student students[], int count);
void searchByMajor(Student students[], int count);

void saveStudentsToFile(Student students[], int count);
void loadStudentsFromFile(Student students[], int *count);

#endif
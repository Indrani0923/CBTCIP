#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 10
#define MAX_NAME_LENGTH 100

typedef struct {
    char name[MAX_NAME_LENGTH];
    int scores[MAX_SUBJECTS];
    int total;
    float average;
    int highest;
    int lowest;
} Student;

void inputSubjectNames(char subjects[][MAX_NAME_LENGTH], int numSubjects);
void inputStudentInfo(Student students[], int *numStudents, char subjects[][MAX_NAME_LENGTH], int numSubjects);
void calculateStudentStatistics(Student students[], int numStudents, int numSubjects);
void rankStudents(Student students[], int numStudents);
void displayStudentSummary(Student students[], int numStudents, char subjects[][MAX_NAME_LENGTH], int numSubjects);

int main() {
    int numStudents, numSubjects;
    Student students[MAX_STUDENTS];
    char subjects[MAX_SUBJECTS][MAX_NAME_LENGTH];

    printf("Enter the number of students: ");
    scanf("%d", &numStudents);
    printf("Enter the number of subjects: ");
    scanf("%d", &numSubjects);
    getchar();  // to consume the newline character left by scanf

    inputSubjectNames(subjects, numSubjects);
    inputStudentInfo(students, &numStudents, subjects, numSubjects);
    calculateStudentStatistics(students, numStudents, numSubjects);
    rankStudents(students, numStudents);
    displayStudentSummary(students, numStudents, subjects, numSubjects);

    return 0;
}

void inputSubjectNames(char subjects[][MAX_NAME_LENGTH], int numSubjects) {
    for (int i = 0; i < numSubjects; ++i) {
        printf("Enter name of subject %d: ", i + 1);
        fgets(subjects[i], MAX_NAME_LENGTH, stdin);
        subjects[i][strcspn(subjects[i], "\n")] = '\0';  // remove newline character
    }
}

void inputStudentInfo(Student students[], int *numStudents, char subjects[][MAX_NAME_LENGTH], int numSubjects) {
    for (int i = 0; i < *numStudents; ++i) {
        printf("Enter full name of student %d: ", i + 1);
        fgets(students[i].name, MAX_NAME_LENGTH, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';  // remove newline character

        for (int j = 0; j < numSubjects; ++j) {
            printf("Enter score for %s: ", subjects[j]);
            scanf("%d", &students[i].scores[j]);
        }
        getchar();  // to consume the newline character left by scanf
    }
}

void calculateStudentStatistics(Student students[], int numStudents, int numSubjects) {
    for (int i = 0; i < numStudents; ++i) {
        int sum = 0;
        students[i].highest = students[i].scores[0];
        students[i].lowest = students[i].scores[0];
        for (int j = 0; j < numSubjects; ++j) {
            sum += students[i].scores[j];
            if (students[i].scores[j] > students[i].highest) {
                students[i].highest = students[i].scores[j];
            }
            if (students[i].scores[j] < students[i].lowest) {
                students[i].lowest = students[i].scores[j];
            }
        }
        students[i].total = sum;
        students[i].average = (float)sum / numSubjects;
    }
}

void rankStudents(Student students[], int numStudents) {
    for (int i = 0; i < numStudents - 1; ++i) {
        for (int j = i + 1; j < numStudents; ++j) {
            if (students[i].total < students[j].total) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

void displayStudentSummary(Student students[], int numStudents, char subjects[][MAX_NAME_LENGTH], int numSubjects) {
    printf("\nStudent Performance Summary:\n");
    printf("%-5s %-30s %-10s %-10s %-10s %-10s", "Rank", "Name", "Total", "Average", "Highest", "Lowest");
    for (int j = 0; j < numSubjects; ++j) {
        printf(" %-10s", subjects[j]);
    }
    printf("\n");

    for (int i = 0; i < numStudents; ++i) {
        printf("%-5d %-30s %-10d %-10.2f %-10d %-10d", i + 1, students[i].name, students[i].total, students[i].average, students[i].highest, students[i].lowest);
        for (int j = 0; j < numSubjects; ++j) {
            printf(" %-10d", students[i].scores[j]);
        }
        printf("\n");
    }
}

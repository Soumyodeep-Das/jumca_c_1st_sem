#include <stdio.h>
#include <stdlib.h>

#define STUDENTS 10
#define SEMESTERS 3
#define SUBJECTS 6

void findTop4Marks(int marks[SEMESTERS][SUBJECTS], int studentId) {
    int allMarks[SEMESTERS * SUBJECTS];
    int index = 0;

    for (int semester = 0; semester < SEMESTERS; semester++) {
        for (int subject = 0; subject < SUBJECTS; subject++) {
            allMarks[index++] = marks[semester][subject];
        }
    }

    for (int i = 0; i < index - 1; i++) {
        for (int j = i + 1; j < index; j++) {
            if (allMarks[i] < allMarks[j]) {
                int temp = allMarks[i];
                allMarks[i] = allMarks[j];
                allMarks[j] = temp;
            }
        }
    }

    // Print the top 4 marks
    printf("Top 4 marks for Student %d: ", studentId + 1);
    for (int i = 0; i < 4 && i < index; i++) {
        printf("%d ", allMarks[i]);
    }
    printf("\n");
}

void findTop5Scorers(int marks[STUDENTS][SEMESTERS][SUBJECTS]) {
    for (int subject = 0; subject < SUBJECTS; subject++) {
        int scores[STUDENTS], students[STUDENTS];

        for (int student = 0; student < STUDENTS; student++) {
            int total = 0;
            for (int semester = 0; semester < SEMESTERS; semester++) {
                total += marks[student][semester][subject];
            }
            scores[student] = total;
            students[student] = student + 1; 
        }

        for (int i = 0; i < STUDENTS - 1; i++) {
            for (int j = i + 1; j < STUDENTS; j++) {
                if (scores[i] < scores[j]) {
                    int tempScore = scores[i];
                    scores[i] = scores[j];
                    scores[j] = tempScore;

                    int tempStudent = students[i];
                    students[i] = students[j];
                    students[j] = tempStudent;
                }
            }
        }

        // Print the top 5 scorers
        printf("Top 5 scorers in Subject %d:\n", subject + 1);
        for (int i = 0; i < 5 && i < STUDENTS; i++) {
            printf("  Student %d: %d marks\n", students[i], scores[i]);
        }
    }
}

void findSemesterTopScorers(int marks[STUDENTS][SEMESTERS][SUBJECTS]) {
    for (int semester = 0; semester < SEMESTERS; semester++) {
        int maxScore = 0;
        int topStudent = -1;

        for (int student = 0; student < STUDENTS; student++) {
            int total = 0;
            for (int subject = 0; subject < SUBJECTS; subject++) {
                total += marks[student][semester][subject];
            }

            if (total > maxScore) {
                maxScore = total;
                topStudent = student;
            }
        }

        // Print the top scorer for the semester
        printf("Top scorer for Semester %d: Student %d with %d marks\n",
               semester + 1, topStudent + 1, maxScore);
    }
}

// Main function
int main() {
    int marks[STUDENTS][SEMESTERS][SUBJECTS];

    // Initialize marks with random values for demonstration
    srand(42); 
    for (int student = 0; student < STUDENTS; student++) {
        for (int semester = 0; semester < SEMESTERS; semester++) {
            for (int subject = 0; subject < SUBJECTS; subject++) {
                marks[student][semester][subject] = rand() % 101; // Random marks 0-100
            }
        }
    }

    // Print all marks
    printf("Marks for all students:\n");
    for (int student = 0; student < STUDENTS; student++) {
        printf("Student %d:\n", student + 1);
        for (int semester = 0; semester < SEMESTERS; semester++) {
            printf("  Semester %d: ", semester + 1);
            for (int subject = 0; subject < SUBJECTS; subject++) {
                printf("%3d ", marks[student][semester][subject]);
            }
            printf("\n");
        }
    }

    for (int student = 0; student < STUDENTS; student++) {
        findTop4Marks(marks[student], student);
    }

    findTop5Scorers(marks);

    findSemesterTopScorers(marks);

    return 0;
}


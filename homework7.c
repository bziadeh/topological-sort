#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FILE_LENGTH 100
#define MAX_COURSE_NAME_LENGTH 30
#define MAX_FILE_NAME_LENGTH 30

// Brennan Ziadeh, 1001773667 CSE 3318, Homework #7

int main() {
    printf("\nThis program will read, from a file, a list of courses and their prerequisites and will print the list in which to take courses.\n");
    
    // Attempt to read file name from
    // user input
    FILE *file;
    char file_name[MAX_FILE_NAME_LENGTH];
    printf("Enter filename: ");
    scanf("%s", file_name);
    file = fopen(file_name, "r");
    if(!file) {
        printf("Could not open file %s, exiting program.\n\n", file_name);
        printf("Failed to read from file. Program will terminate.\n\n");
        return 0;
    }

    // File was successfully found. Time to read and store
    // all courses
    char *courses[MAX_FILE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int size = 0;
    while(fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        char* course_name = strtok(line, " \n");
        courses[size] = malloc(sizeof(char *));
        strcpy(courses[size], course_name);
        size++;
    }



    return 0;
}
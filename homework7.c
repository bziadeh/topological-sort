#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define MAX_FILE_LENGTH 100
#define MAX_COURSE_NAME_LENGTH 30
#define MAX_FILE_NAME_LENGTH 30

// Brennan Ziadeh, 1001773667 CSE 3318, Homework #7

enum Color { WHITE, GRAY, BLACK };

typedef struct {
    int size;
    int *elements;
} Result;

int get_vertex(char *course_name, char *courses[], int size);
void print_matrix(int size, int matrix[][size]);
int depth_first_search(int size, int matrix[][size], Result *result);
int dfs_visit(int size, int matrix[][size], int vertex, enum Color *colors, int *pred, Result *result);

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
    rewind(file); // so we can read again later

    printf("Number of vertices in built graph: N = %d\n", size);
    printf("Vertex - coursename correspondence\n");
    for(int i = 0; i < size; i++) {
        printf("%d - %s\n", i, courses[i]);
    }

    // Build our adjacency matrix using the
    // the information given
    int matrix[size][size];
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            matrix[i][j] = 0;
        }
    }

    for(int i = 0; i < size; i++) {
        if(fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            char* course_name = strtok(line, " \n");
            int dest = get_vertex(course_name, courses, size);

            while(course_name) {
                course_name = strtok(NULL, " \n");
                if(course_name) {
                    int from = get_vertex(course_name, courses, size);
                    matrix[from][dest] = 1;
                }
            }
        }
    }
    printf("\nAdjacency matrix:\n");
    print_matrix(size, matrix);

    Result *result = (Result *) malloc(sizeof(Result));
    result->size = 0;
    result->elements = malloc(sizeof(int) * MAX_FILE_LENGTH);
    
    int res_size = depth_first_search(size, matrix, result);
    if(res_size == -1) {
        printf("Cycle found. ending program.\n");
        return 0;
    }

    printf("\nCourses to take in order:\n");
    for(int i = 0; i < result->size; i++) {
        
        int vertex = result->elements[i];
        char *course = courses[vertex];

        printf("%d. %s\n", i, course);
    }
    return 0;
}

int get_vertex(char *course_name, char *courses[], int size) {
    for(int i = 0; i < size; i++) {
        if(strcmp(course_name, courses[i]) == 0) {
            return i;
        }
    }
    return 0;   
}

int depth_first_search(int size, int matrix[][size], Result *result) {
    enum Color colors[size];
    int pred[size];
    
    for(int i = 0; i < size; i++) {
        colors[i] = WHITE;
        pred[i] = -1;
    }

    for(int i = 0; i < size; i++) {
        if(colors[i] == WHITE) {
            return dfs_visit(size, matrix, i, colors, pred, result);
        }
    }

    return 0;
}

int dfs_visit(int size, int matrix[][size], int vertex, enum Color *colors, int *pred, Result *result) {
    colors[vertex] = GRAY;
    for(int i = 0; i < size; i++) {
        int adj = matrix[vertex][i];
        printf("adjacent node %d\n", adj);
        if(colors[adj] == WHITE) {
            pred[adj] = vertex;
            dfs_visit(size, matrix, vertex, colors, pred, result);
        }
        if(colors[adj] == GRAY) {
            return -1;
        }
    }
    colors[vertex] = BLACK;
    result->elements[result->size] = vertex;
    result->size++;
    return result->size;
}

void print_matrix(int size, int matrix[][size]) {
    printf("    | ");
    for(int i = 0; i < size; i++) {
        printf("%4d", i);
    }
    printf("\n");
    for(int i = 0; i < 6 + (4 * size); i++) {
        printf("-");   
    }
    printf("\n");
    for(int i = 0; i < size; i++) {
        printf("   %d| ", i);
        for(int j = 0; j < size; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
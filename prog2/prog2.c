#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 3   // number of records

typedef struct {
    int id;
    char name[30];
    int age;
} Student;

// Function to write array of structures to file in ASCII format
void writeRecords(Student arr[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File opening failed");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %d\n", arr[i].id, arr[i].name, arr[i].age);
    }
    fclose(fp);
}

// Function to create array of seek positions
long *createSeekPositions(const char *filename, int n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File opening failed");
        exit(1);
    }

    long *positions = (long *)malloc(n * sizeof(long));
    if (!positions) {
        perror("Memory allocation failed");
        exit(1);
    }

    char buffer[100];
    for (int i = 0; i < n; i++) {
        positions[i] = ftell(fp);   // store current file position
        fgets(buffer, sizeof(buffer), fp); // move to next line
    }

    fclose(fp);
    return positions;
}

// Function to display record given position
void displayRecord(const char *filename, long pos) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File opening failed");
        exit(1);
    }

    fseek(fp, pos, SEEK_SET);  // move to the given position
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), fp)) {
        printf("Record: %s", buffer);
    } else {
        printf("Unable to read record at position %ld\n", pos);
    }

    fclose(fp);
}

// Main function
int main() {
    Student arr[MAX] = {
        {1, "Alice", 20},
        {2, "Bob", 22},
        {3, "Charlie", 19}
    };

    const char *filename = "students.txt";

    // Step 1: Write records
    writeRecords(arr, MAX, filename);

    // Step 2: Create seek positions
    long *positions = createSeekPositions(filename, MAX);

    // Step 3: Display records using positions
    printf("Displaying records using seek positions:\n");
    for (int i = 0; i < MAX; i++) {
        displayRecord(filename, positions[i]);
    }

    free(positions);
    return 0;
}

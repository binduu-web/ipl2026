#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[30];
    float marks;
} Student;

void writeRecords(const char *filename, int n) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    Student s;
    for (int i = 0; i < n; i++) {
        printf("Enter ID, Name, Marks for student %d: ", i + 1);
        scanf("%d %s %f", &s.id, s.name, &s.marks);
        fwrite(&s, sizeof(Student), 1, fp);
    }
    fclose(fp);
}

void getRecord(const char *filename, int m) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    Student s;
    fseek(fp, (m - 1) * sizeof(Student), SEEK_SET); // move to mth record
    if (fread(&s, sizeof(Student), 1, fp) == 1) {
        printf("Record %d → ID: %d, Name: %s, Marks: %.2f\n", m, s.id, s.name, s.marks);
    } else {
        printf("Record %d not found.\n", m);
    }
    fclose(fp);
}

void deleteRecord(const char *filename, int m) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("File opening failed");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb");
    if (!temp) {
        perror("Temp file opening failed");
        fclose(fp);
        return;
    }

    Student s;
    int index = 0;
    while (fread(&s, sizeof(Student), 1, fp) == 1) {
        index++;
        if (index == m) continue; // skip the mth record
        fwrite(&s, sizeof(Student), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    // Replace original file with temp
    remove(filename);
    rename("temp.bin", filename);

    printf("Record %d deleted successfully.\n", m);
}

int main() {
    const char *filename = "students.bin";
    int n, choice, m;

    printf("Enter number of records: ");
    scanf("%d", &n);
    writeRecords(filename, n);

    while (1) {
        printf("\nMenu:\n1. Get Record\n2. Delete Record\n3. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter record number to fetch: ");
                scanf("%d", &m);
                getRecord(filename, m);
                break;
            case 2:
                printf("Enter record number to delete: ");
                scanf("%d", &m);
                deleteRecord(filename, m);
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

#include <stdio.h>

int main() {
    FILE *filePointer;
    char dataToWrite[] = "Hello, this is a simple file handling example in C!";
    char dataRead[100];

    // Writing to a file
    filePointer = fopen("example.txt", "w"); // Open file in write mode
    if (filePointer == NULL) {
        printf("Error: Unable to open file for writing.\n");
        return 1;
    }
    fprintf(filePointer, "%s\n", dataToWrite); // Write data to file
    fclose(filePointer); // Close the file

    printf("Data successfully written to 'example.txt'.\n");

    // Reading from the file
    filePointer = fopen("example.txt", "r"); // Open file in read mode
    if (filePointer == NULL) {
        printf("Error: Unable to open file for reading.\n");
        return 1;
    }
    fgets(dataRead, sizeof(dataRead), filePointer); // Read data from file
    fclose(filePointer); // Close the file

    printf("Data read from 'example.txt': %s\n", dataRead);

    return 0;
}

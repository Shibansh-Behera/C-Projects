#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store book information
struct Book {
    int serialNumber;
    char bookName[100];
    char author[50];
    char status; // 'A' for available, 'B' for borrowed
};

int main() {

    int i;
    struct Book library[100];
    int bookCount = 0;
    int choice;
    
    FILE *fptr;
    fptr=fopen("librarybooks.bin","ab+");
    printf("Enter number of books currently in library record:");
    scanf("%d",&bookCount);
    rewind(fptr);
    for(i=0;i<bookCount;i++){
        fread(&library[i],sizeof(library[0]),1,fptr);
    }
    fclose(fptr);
    

    do {
        printf("\nLibrary Book Management System\n");
        printf("1. Add New Book\n");
        printf("2. Check Book Availability\n");
        printf("3. Update Book Availability\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter book details:\n");
                printf("Serial Number: ");
                scanf("%d", &library[bookCount].serialNumber);
                printf("Book Name: ");
                scanf("%s",&library[bookCount].bookName);
                printf("Author: ");
                scanf("%s",&library[bookCount].author);
                library[bookCount].status = 'A'; // Set status as available
                bookCount++;
                break;
            case 2:
                {
                    int searchChoice;
                    printf("1. Search by Book Name\n");
                    printf("2. Search by Serial Number\n");
                    printf("Enter your choice: ");
                    scanf("%d", &searchChoice);

                    if (searchChoice == 1) {
                        char searchName[100];
                        printf("Enter book name: ");
                        scanf("%s", searchName);
                        int found = 0;
                        for (int i = 0; i < bookCount; i++) {
                            if (strcmp(library[i].bookName, searchName) == 0) {
                                printf("Book found:\n");
                                printf("%d\t%s\t%s\t%c\n", library[i].serialNumber,
                                       library[i].bookName, library[i].author, library[i].status);
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            printf("Book not found.\n");
                        }
                    } else if (searchChoice == 2) {
                        int searchSerial;
                        printf("Enter serial number: ");
                        scanf("%d", &searchSerial);
                        int found = 0;
                        for (int i = 0; i < bookCount; i++) {
                            if (library[i].serialNumber == searchSerial) {
                                printf("Book found:\n");
                                printf("%d\t%s\t%s\t%c\n", library[i].serialNumber,
                                       library[i].bookName, library[i].author, library[i].status);
                                found = 1;
                                break;
                            }
                        }
                        if (!found) {
                            printf("Book not found.\n");
                        }
                    }
                }
                break;
            case 3:
                {
                    int serial;
                    char status;
                    printf("Enter serial number of the book: ");
                    scanf("%d", &serial);
                    printf("Enter updated status (A for available, B for borrowed): ");
                    scanf(" %c", &status);
                    int found = 0;

                    for (int i = 0; i < bookCount; i++) {
                        if (library[i].serialNumber == serial) {
                            library[i].status = status;
                            printf("Status updated successfully.\n");
                            found=1;
                            break;
                        }
                    }
                    if (!found) {
                            printf("Book not found.\n");
                        }
                }
                break;
            case 4:
                fptr=fopen("G:\\folder\\librarybooks.bin","wb");
                for(i=0;i<bookCount;i++){
                    fwrite(&library[i],sizeof(library[0]),1,fptr);
                        }
                fclose(fptr);

                printf("Exiting program. Thank you!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}

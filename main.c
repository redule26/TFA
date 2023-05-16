#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100

struct Book {
    char title[100];
    char author[100];
    int year;
};

void addBook(struct Book books[], int *numBooks) {
    if (*numBooks == MAX_BOOKS) {
        printf("La bibliothèque est pleine. Impossible d'ajouter un livre.\n");
        return;
    }

    struct Book newBook;

    printf("Titre du livre : ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Auteur : ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Année de publication : ");
    scanf("%d", &newBook.year);
    getchar(); // Pour consommer le caractère de nouvelle ligne laissé dans le buffer par scanf

    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("Livre ajouté avec succès !\n");
}

void saveLibrary(struct Book books[], int numBooks) {
    FILE *file = fopen("biblio.txt", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s;%s;%d\n", books[i].title, books[i].author, books[i].year);
    }

    fclose(file);

    printf("La bibliothèque a été enregistrée avec succès dans le fichier.\n");
}

void loadLibrary(struct Book books[], int *numBooks) {
    FILE *file = fopen("biblio.txt", "r");
    if (file == NULL) {
        printf("Le fichier de bibliothèque n'existe pas.\n");
        return;
    }

    *numBooks = 0;

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token;
        token = strtok(line, ";");

        strcpy(books[*numBooks].title, token);
        token = strtok(NULL, ";");

        strcpy(books[*numBooks].author, token);
        token = strtok(NULL, ";");

        books[*numBooks].year = atoi(token);

        (*numBooks)++;
    }

    fclose(file);

    printf("La bibliothèque a été chargée avec succès à partir du fichier.\n");
}

void displayLibrary(struct Book books[], int numBooks) {
    if (numBooks == 0) {
        printf("La bibliothèque est vide.\n");
        return;
    }

    printf("Livres dans la bibliothèque :\n");
    for (int i = 0; i < numBooks; i++) {
        printf("Livre %d :\n", i + 1);
        printf("Titre : %s\n", books[i].title);
        printf("Auteur : %s\n", books[i].author);
        printf("Année de publication : %d\n", books[i].year);
        printf("--------------------------------\n");
    }
}

int main() {
    struct Book library[MAX_BOOKS];
    int numBooks = 0;
    int choice;

    loadLibrary(library, &numBooks);

    do {
    printf("\nGestion de bibliothèque\n");
    printf("1. Ajouter un livre\n");
    printf("2. Afficher la bibliothèque\n");
    printf("3. Enregistrer la bibliothèque dans un fichier\n");
    printf("4. Quitter\n");
    printf("Choix : ");
    scanf("%d", &choice);
    getchar(); // Pour consommer le caractère de nouvelle ligne laissé dans le buffer par scanf

    switch (choice) {
        case 1:
            addBook(library, &numBooks);
            break;
        case 2:
            displayLibrary(library, numBooks);
            break;
        case 3:
            saveLibrary(library, numBooks);
            break;
        case 4:
            printf("Au revoir !\n");
            break;
        default:
            printf("Choix invalide.\n");
    }
} while (choice != 4);

return 0;
}
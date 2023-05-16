#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///DEFINITIONS
#define MAX_BOOKS 100
#define MAX_USERS 100


///STRUCTURES
struct Book {
    char Title[100];
    char Author[100];
    int Year;
} typedef Book;

struct User {
    char Username[100];
    char FirstName[100];
    char LastName[100];
} typedef User;


///BOOK PROTOTYPES
void addBook(Book*, int*);
void saveLibrary(Book*, int); //will be changed in 'savefiles'
void loadFiles(Book*, int*, User*, int*);
void displayLibrary(Book*, int);
//USER PROTOTYPES
void addUser(User*, int*);
void displayUsersList(User*, int);

int main() 
{
    Book library[MAX_BOOKS];
    User users[MAX_USERS];
    int numBooks = 0, numUsers = 0;
    int choice;

    loadFiles(library, &numBooks, users, &numUsers);

    do {
        printf("\nGestion de la bibliothèque\n");
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
            case 5:
                displayUsersList(users, numUsers);
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 4);

return 0;
}


void addBook(Book *books, int *numBooks) 
{
    if (*numBooks == MAX_BOOKS) 
    {
        printf("La bibliothèque est pleine. Impossible d'ajouter un livre.\n");
        return;
    }

    struct Book newBook;

    printf("Titre du livre : ");
    fgets(newBook.Title, sizeof(newBook.Title), stdin);
    newBook.Title[strcspn(newBook.Title, "\n")] = '\0';

    printf("Auteur : ");
    fgets(newBook.Author, sizeof(newBook.Author), stdin);
    newBook.Author[strcspn(newBook.Author, "\n")] = '\0';

    printf("Année de publication : ");
    scanf("%d", &newBook.Year);
    getchar(); // Pour consommer le caractère de nouvelle ligne laissé dans le buffer par scanf

    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("Livre ajouté avec succès !\n");
}

void saveLibrary(Book *books, int numBooks) 
{
    FILE *file = fopen("livres.txt", "w");
    if (file == NULL) 
    {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    for (int i = 0; i < numBooks; i++) 
    {
        fprintf(file, "%s;%s;%d\n", books[i].Title, books[i].Author, books[i].Year);
    }

    fclose(file);

    printf("La bibliothèque a été enregistrée avec succès dans le fichier.\n");
}

void loadFiles(Book *books, int *numBooks, User *users, int *numUsers) 
{
    char bookFile[50] = "livres.txt";
    char usersFile[50] = "utilisateurs.txt";

    //Chargement du fichier livres
    FILE *ptr_bookFile = fopen(bookFile, "r");
    if (ptr_bookFile == NULL) 
    {
        printf("Le fichier '%s' n'existe pas.\n", bookFile);
        return;
    }

    *numBooks = 0;

    char line[100];
    while (fgets(line, sizeof(line), ptr_bookFile) != NULL) {
        char *token;
        token = strtok(line, ";");

        strcpy(books[*numBooks].Title, token);
        token = strtok(NULL, ";");

        strcpy(books[*numBooks].Author, token);
        token = strtok(NULL, ";");

        books[*numBooks].Year = atoi(token);

        (*numBooks)++;
    }

    fclose(ptr_bookFile);


    //Chargement du fichier des utilisateurs
    FILE *ptr_usersFile;
    ptr_usersFile = fopen(usersFile, "r");
    if (ptr_usersFile == NULL) {
        printf("Le fichier '%s' n'existe pas.\n", usersFile);
        return;
    }

    *numUsers = 0;

    //on vide le tableau line pour pouvoir le réutiliser
    line[0] = '\0';
    while (fgets(line, sizeof(line), ptr_usersFile) != NULL) {
        char *token;
        token = strtok(line, ";");

        strcpy(users[*numUsers].Username, token);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].FirstName, token);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].LastName, token);
        token = strtok(line, ";");

        (*numUsers)++;
    }

    fclose(ptr_usersFile);

    printf("Les fichiers %s et %s ont été chargée avec succès.\n", bookFile, usersFile);
}

void displayLibrary(Book *books, int numBooks) 
{
    if (numBooks == 0) 
    {
        printf("La bibliothèque est vide.\n");
        return;
    }

    printf("Livres dans la bibliothèque :\n");
    for(int i = 0; i < numBooks; i++) 
    {
        printf("Livre %d :\n", i + 1);
        printf("Titre : %s\n", books[i].Title);
        printf("Auteur : %s\n", books[i].Author);
        printf("Année de publication : %d\n", books[i].Year);
        printf("--------------------------------\n");
    }
}


void addUser(User *users, int *numUsers)
{

}

void displayUsersList(User *users, int numUsers)
{
    if(numUsers == 0) {
        printf("Le fichier des utilisateurs est vide.\n");
        return;
    }

    printf("Utilisateurs dans la bibliothèque :\n");
    for(int i = 0; i < numUsers; i++)
    {
        printf("ID : %d\n", i + 1);
        printf("Nom d'utilisateur : %s\n", users[i].Username);
        printf("Prénom : %s\n", users[i].FirstName);
        printf("Nom de famille : %s\n", users[i].LastName);
    }
}
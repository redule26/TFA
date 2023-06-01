#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///DEFINITIONS
#define MAX_LIVRES 100
#define MAX_MEMBRES 100


///STRUCTURES
struct Book {
    char BookID[100]; //par exemple : ISBN ou BOOK-132764781
    char Title[100];
    char Author[100];
    int Year;
} typedef Book;

struct User {
    char UserID[100]; //par exemple : USER-A3UIOR478146
    char Username[100];
    char LastName[100];
    char FirstName[100];
} typedef User;

struct Loan {
    char UID[100]; //par exemple : EMP-129380-13198
    char userID[100];
    char bookID[100];
} typedef Loan;

void loadData(Book*, int*, User*, int*);
void saveData(Book*, int, User*, int);

///BOOK PROTOTYPES
void addBook(Book*, int*);
void displayLibrary(Book*, int);
void showBook(Book*);
///USER PROTOTYPES
void addUser(User*, int*);
void displayUsersList(User*, int);
void showUser(User*, char[]);
///LOANS PROTOTYPES
void displayLoansList(Loan*, int);
void showLoan(Loan*, char[]);
void showUserLoans(User*, Loan*, int, int);

int main() 
{
    Book books[MAX_LIVRES];
    User users[MAX_MEMBRES];
    int numBooks = 0, numUsers = 0;
    int choice;

    loadData(books, &numBooks, users, &numUsers);

    do {
        printf("\nBienvenue sur le programme de gestion de la bibliothèque IPES Wavre, que souhaitez vous faire ?\n");
        printf("1. Ajouter un livre\n");
        printf("2. Afficher la bibliothèque\n");
        printf("3. Enregistrer la bibliothèque dans un fichier\n");
        printf("4. Quitter\n");
        printf("Choix : ");
        scanf("%i", &choice);
        fflush(stdin); // Pour consommer le caractère de nouvelle ligne laissé dans le buffer par scanf

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                displayLibrary(books, numBooks);
                break;
            case 3:
                showBook(books);
                //saveLibrary(livres, numBooks);
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            case 5:
                displayUsersList(users, numUsers);
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choice != 4);
    saveData(books, numBooks, users, numUsers);
return 0;
}


void addBook(Book *books, int *numBooks) 
{
    if (*numBooks == MAX_LIVRES) 
    {
        printf("La bibliothèque est pleine. Impossible d'ajouter un livre.\n");
        return;
    }

    Book newBook;

    printf("Titre du livre : ");
    scanf("%s", newBook.Title);
    fflush(stdin);

    printf("Auteur : ");
    scanf("%s", newBook.Author);
    fflush(stdin);

    printf("Annee de publication : ");
    scanf("%i", &newBook.Year);
    fflush(stdin);

    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("Livre ajouté avec succès !\n");
}

void showBook(Book *books)
{
    char id[100];
    printf("Quel livre voulez-vous selectionner ? : ");
    gets(id);

    int i = 0;
    while(books[i].BookID != id)
    {
        i++;
    }

    Book selectedBook = books[i];
    printf("%s", selectedBook.BookID);
}

//Fonction appelée à la fermeture du programme pour stocker le contenu des tableaux 'livres', 'membres' et 'emprunts' dans les fichiers.txt
void saveData(Book *books, int numBooks, User *users, int numUsers) 
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

//Fonction appelée au démarrage du programme pour stocker dans les tableaux de structure 'livres', 'membres' et 'emprunts' les données présents dans les fichiers .txt
void loadData(Book *books, int *numBooks, User *users, int *numUsers) 
{
    char bookFile[50] = "livres.txt";
    char usersFile[50] = "membres.txt";

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

        strcpy(users[*numUsers].UserID, token);
        //printf("%s", users[*numUsers].UserID); debug printfs
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].Username, token);
        //printf("%s", users[*numUsers].Username);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].LastName, token);
        //printf("%s", users[*numUsers].LastName);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].FirstName, token);
        //printf("%s", users[*numUsers].FirstName);
        token = strtok(NULL, ";");

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
    if (*numUsers == MAX_MEMBRES) 
    {
        printf("L'emplacement pour les membres est plein.\n");
        return;
    }

    User newUser;

    //génération du UID idGeneration(string type) return string; swi

    printf("Nom de l'utilisateur : ");
    scanf("%s", newUser.LastName);
    fflush(stdin);

    printf("Prenom de l'utilisateur : ");
    scanf("%s", newUser.FirstName);
    fflush(stdin);

    printf("Pseudo de l'utilisateur : ");
    scanf("%s", newUser.Username);



    users[*numUsers] = newUser;
    (*numUsers)++;

    printf("Livre ajouté avec succès !\n");
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
        printf("ID : %s\n", users[i].UserID);
        printf("Nom d'utilisateur : %s\n", users[i].Username);
        printf("Prénom : %s\n", users[i].FirstName);
        printf("Nom de famille : %s\n", users[i].LastName);
    }
}
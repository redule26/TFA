#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

///DEFINITIONS
#define MAX_LIVRES 100
#define MAX_MEMBRES 100
#define MAX_EMPRUNTS 100
#define UID_SIZE 20 ///USER + 20 caracters


///STRUCTURES
struct Livre {
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
    char LoanID[100]; //par exemple : EMP-129380-13198
    char userID[100];
    char bookID[100];
} typedef Loan;

//Pour la génération de l'identifiant unique
enum Type {
    BookType = 1,
    UserType = 2,
    LoanType = 3
};

//DATA PROTOTYPES
void loadData(Book*, int*, User*, int*, Loan*, int*);
void saveData(Book*, int, User*, int, Loan*, int);

///BOOK PROTOTYPES
void addBook(Book*, int*);
void displayLibrary(Book*, int);
void showBook(Book*, int);

///USER PROTOTYPES
void addUser(User*, int*);
void displayUsersList(User*, int);
void showUser(User*, int, Loan*, int);

///LOANS PROTOTYPES
void displayLoansList(Loan*, int);
void createLoan(Loan*, int *, User*, int, Book*, int);
void showLoan(User*, int, Book*, int, Loan*, int);
void showUserLoans(User*, Loan*, int, int);

///GEN ID PROTOTYPES 
void generateString(char*);
void generateId(enum Type, char*, Book*, int, User*, int, Loan*, int);
bool IsIdUsed(enum Type, char*, Book*, int, User*, int, Loan*, int);

int main() {
    srand(time(NULL));
    Book books[MAX_LIVRES];
    User users[MAX_MEMBRES];
    Loan loans[MAX_EMPRUNTS];
    int numBooks = 0, numUsers = 0, numLoans = 0;
    int choice;

    loadData(books, &numBooks, users, &numUsers, loans, &numLoans);

    do {
        choice = 0;
        printf("\nBienvenue sur le programme de gestion de la bibliothèque IPES Wavre, que souhaitez-vous faire ?\n");

        ///Gestion des livres
        printf("1. Ajouter un livre\n");
        printf("2. Afficher la bibliotheque\n");
        printf("3. Montrer un livre par son identifiant\n");

        printf("4. Ajouter un membre \n");
        printf("5. Afficher la liste des membres \n");
        printf("6. Afficher un membre et ses emprunts\n");

        printf("7. creer un emprunt\n");
        printf("8. afficher les informations d'un emprunt\n");
        printf("9. Afficher la liste des emprunts\n");

        printf("10. Quitter\n");
        printf("Choix : ");
        scanf("%i", &choice);
        getchar(); //on vide le buffer input

        switch (choice) {
            case 1:
                addBook(books, &numBooks);
                break;
            case 2:
                displayLibrary(books, numBooks);
                break;
            case 3:
                showBook(books, numBooks);
                break;

            case 4:
                addUser(users, &numUsers);
                break;
            case 5:
                displayUsersList(users, numUsers);
                break;
            case 6:
                showUser(users, numUsers, loans, numLoans);
                break;

            case 7:
                createLoan(loans, &numLoans, users, numUsers, books, numBooks);
                break;

            case 8:
                showLoan(users, numUsers, books, numBooks, loans, numLoans);
                break;

           case 9: 
                displayLoansList(loans, numLoans);
                break;

            case 10:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
                break;
        }
    } while (choice != 10);

    saveData(books, numBooks, users, numUsers, loans, numLoans);
    return 0;
}



///Fonctions de chargement et sauvegarde des données


//Fonction appelée à la fermeture du programme pour stocker le contenu des tableaux 'livres', 'membres' et 'emprunts' dans les fichiers.txt
void saveData(Book *books, int numBooks, User *users, int numUsers, Loan *loans, int numLoans)
{
    char bookFile[50] = "livres.txt";
    char userFile[50] = "membres.txt";
    char loanFile[50] = "emprunts.txt";

    FILE *bookPtr = fopen(bookFile, "w");
    if (bookPtr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", bookFile);
        return;
    }

    for (int i = 0; i < numBooks; i++)
    {
        fprintf(bookPtr, "%s;%s;%s;%d", books[i].BookID, books[i].Title, books[i].Author, books[i].Year);
        if (i != numBooks - 1)
        {
            fprintf(bookPtr, "\n");
        }
    }

    fclose(bookPtr);
    printf("Les livres ont été enregistrés avec succès dans le fichier '%s'.\n", bookFile);

    FILE *userPtr = fopen(userFile, "w");
    if (userPtr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", userFile);
        return;
    }

    for (int i = 0; i < numUsers; i++)
    {
        fprintf(userPtr, "%s;%s;%s;%s", users[i].UserID, users[i].Username, users[i].LastName, users[i].FirstName);
    }

    fclose(userPtr);
    printf("Les membres ont été enregistrés avec succès dans le fichier '%s'.\n", userFile);

    FILE *loanPtr = fopen(loanFile, "w");
    if (loanPtr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", loanFile);
        return;
    }

    for (int i = 0; i < numLoans; i++)
    {
        fprintf(loanPtr, "%s;%s;%s", loans[i].LoanID, loans[i].userID, loans[i].bookID);
    }

    fclose(loanPtr);
    printf("Les emprunts ont été enregistrés avec succès dans le fichier '%s'.\n", loanFile);
}

//Fonction appelée au démarrage du programme pour stocker dans les tableaux de structure 'livres', 'membres' et 'emprunts' les données présents dans les fichiers .txt
void loadData(Book *books, int *numBooks, User *users, int *numUsers, Loan *loans, int *numLoans)
{
    char bookFile[50] = "livres.txt";
    char usersFile[50] = "membres.txt";
    char loanFile[50] = "emprunts.txt";

    // Chargement du fichier livres
    FILE *ptr_bookFile = fopen(bookFile, "r");
    if (ptr_bookFile == NULL)
    {
        printf("Le fichier '%s' n'existe pas.\n", bookFile);
        return;
    }

    *numBooks = 0;

    char line[100];
    while (fgets(line, sizeof(line), ptr_bookFile) != NULL)
    {
        char *token;
        token = strtok(line, ";");

        strcpy(books[*numBooks].BookID, token);
        token = strtok(NULL, ";");

        strcpy(books[*numBooks].Title, token);
        token = strtok(NULL, ";");

        strcpy(books[*numBooks].Author, token);
        token = strtok(NULL, ";");

        books[*numBooks].Year = atoi(token);

        (*numBooks)++;
    }

    fclose(ptr_bookFile);


    // Chargement du fichier des utilisateurs
    FILE *ptr_usersFile = fopen(usersFile, "r");
    if (ptr_usersFile == NULL)
    {
        printf("Le fichier '%s' n'existe pas.\n", usersFile);
        return;
    }

    *numUsers = 0;

    while (fgets(line, sizeof(line), ptr_usersFile) != NULL)
    {
        char *token;
        token = strtok(line, ";");

        strcpy(users[*numUsers].UserID, token);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].Username, token);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].LastName, token);
        token = strtok(NULL, ";");

        strcpy(users[*numUsers].FirstName, token);
        token = strtok(NULL, ";");

        (*numUsers)++;
    }

    fclose(ptr_usersFile);


    // Chargement du fichier des emprunts
    FILE *ptr_loanFile = fopen(loanFile, "r");
    if (ptr_loanFile == NULL)
    {
        printf("Le fichier '%s' n'existe pas.\n", loanFile);
        return;
    }

    *numLoans = 0;

    while (fgets(line, sizeof(line), ptr_loanFile) != NULL)
    {
        char *token;
        token = strtok(line, ";");

        strcpy(loans[*numLoans].LoanID, token);
        token = strtok(NULL, ";");

        strcpy(loans[*numLoans].userID, token);
        token = strtok(NULL, ";");

        strcpy(loans[*numLoans].bookID, token);
        token = strtok(NULL, ";");

        (*numLoans)++;
    }

    fclose(ptr_loanFile);

    printf("Les fichiers %s, %s et %s ont été chargés avec succès.\n", bookFile, usersFile, loanFile);
}


///Fonctions de livres


void addBook(Book *books, int *numBooks)
{
    if (*numBooks == MAX_LIVRES)
    {
        printf("La bibliothèque est pleine. Impossible d'ajouter un livre.\n");
        return;
    }

    Book newBook;

    generateId(BookType, newBook.BookID, books, numBooks, NULL, 0, NULL, 0);

    printf("Titre du livre : ");
    fgets(newBook.Title, sizeof(newBook.Title), stdin);
    newBook.Title[strcspn(newBook.Title, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Auteur : ");
    fgets(newBook.Author, sizeof(newBook.Author), stdin);
    newBook.Author[strcspn(newBook.Author, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Année de publication : ");
    char yearInput[100];
    fgets(yearInput, sizeof(yearInput), stdin);
    sscanf(yearInput, "%i", &newBook.Year);

    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("Livre ajouté avec succès !\n");
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
        printf("UID : %s\n", books[i].BookID);
        printf("Titre : %s\n", books[i].Title);
        printf("Auteur : %s\n", books[i].Author);
        printf("Année de publication : %d\n", books[i].Year);
        printf("--------------------------------\n");
    }
}

void showBook(Book *books, int numBooks)
{
    char id[30];
    printf("Quel livre voulez-vous selectionner ? : ");
    fgets(id, 30, stdin);
    id[strcspn(id, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    Book selectedBook;
    bool found = false;

    for (int i = 0; i < numBooks; i++)
    {
        if (strncmp(books[i].BookID, id, strlen(id)) == 0)
        {
            selectedBook = books[i];
            found = true;
            break;
        }
    }

    if (found)
    {
        printf("Voici le livre dont l'id est : %s\n", selectedBook.BookID);
        printf("%s - %s - %d\n", selectedBook.Title, selectedBook.Author, selectedBook.Year);
    }
    else
    {
        printf("Livre non trouvé.\n");
    }
}


///Fonctions d'utilisateur


void addUser(User *users, int *numUsers)
{
    if (*numUsers == MAX_MEMBRES) 
    {
        printf("L'emplacement pour les membres est plein.\n");
        return;
    }

    User newUser;

    // Génération de l'ID utilisateur
    generateId(UserType, newUser.UserID, NULL, 0, users, *numUsers, NULL, 0);

    printf("Nom de famille de l'utilisateur : ");
    fgets(newUser.LastName, sizeof(newUser.LastName), stdin);
    newUser.LastName[strcspn(newUser.LastName, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Prenom de l'utilisateur : ");
    fgets(newUser.FirstName, sizeof(newUser.FirstName), stdin);
    newUser.FirstName[strcspn(newUser.FirstName, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Pseudo de l'utilisateur : ");
    fgets(newUser.Username, sizeof(newUser.Username), stdin);
    newUser.Username[strcspn(newUser.Username, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    users[*numUsers] = newUser;
    (*numUsers)++;

    printf("Utilisateur ajouté avec succès !\n");
}

void showUser(User *users, int numUsers, Loan *loans, int numLoans)
{
    char id[30];
    printf("Quel membre voulez-vous sélectionner ? : ");
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    User selectedUser;
    bool found = false;

    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].UserID, id) == 0)
        {
            selectedUser = users[i];
            found = true;
            break;
        }
    }

    if (found)
    {
        printf("Voici les informations sur le membre sélectionné :\n\n");
        printf("UID : %s\n", selectedUser.UserID);
        printf("Nom : %s\n", selectedUser.LastName);
        printf("Prénom : %s\n", selectedUser.FirstName);
        printf("Pseudo : %s\n", selectedUser.Username);
        printf("--------------------------------\n");

        printf("Liste des emprunts du membre :\n");
        bool hasLoans = false;

        for (int i = 0; i < numLoans; i++)
        {
            if (strcmp(loans[i].userID, selectedUser.UserID) == 0)
            {
                hasLoans = true;

                printf("Emprunt %d :\n", i + 1);
                printf("ID emprunt : %s\n", loans[i].LoanID);
                printf("ID membre : %s\n", loans[i].userID);
                printf("--------------------------------\n");
            }
        }

        if (!hasLoans)
        {
            printf("Le membre n'a aucun emprunt en cours.\n");
        }
    }
    else
    {
        printf("Aucun membre trouvé avec cet UID.\n");
    }
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


///Fonctions d'emprunt


void createLoan(Loan *loans, int *numLoans, User *users, int numUsers, Book *books, int numBooks)
{
    char userID[100];
    char bookID[100];

    printf("ID de l'utilisateur : ");
    fgets(userID, sizeof(userID), stdin);
    userID[strcspn(userID, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("ID du livre : ");
    fgets(bookID, sizeof(bookID), stdin);
    bookID[strcspn(bookID, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    // Vérifier si le livre est déjà emprunté
    for (int i = 0; i < *numLoans; i++)
    {
        if (strcmp(loans[i].bookID, bookID) == 0)
        {
            printf("Le livre avec l'ID '%s' est déjà emprunté.\n", bookID);
            return;
        }
    }

    // Vérifier si l'utilisateur existe
    bool userExists = false;
    for (int i = 0; i < numUsers; i++)
    {
        if (strcmp(users[i].UserID, userID) == 0)
        {
            userExists = true;
            break;
        }
    }

    if (!userExists)
    {
        printf("L'utilisateur avec l'ID '%s' n'existe pas.\n", userID);
        return;
    }

    // Vérifier si le livre existe
    bool bookExists = false;
    for (int i = 0; i < numBooks; i++)
    {
        if (strcmp(books[i].BookID, bookID) == 0)
        {
            bookExists = true;
            break;
        }
    }

    if (!bookExists)
    {
        printf("Le livre avec l'ID '%s' n'existe pas.\n", bookID);
        return;
    }

    // Créer un nouvel emprunt
    Loan newLoan;
    generateId(LoanType, newLoan.LoanID, NULL, 0, NULL, 0, loans, numLoans);
    strcpy(newLoan.userID, userID);
    strcpy(newLoan.bookID, bookID);

    loans[*numLoans] = newLoan;
    (*numLoans)++;

    printf("Emprunt créé avec succès !\n");
}

void showLoan(User *users, int numUsers, Book *books, int numBooks, Loan *loans, int numLoans)
{
    char loanID[30];
    printf("Quel emprunt voulez-vous afficher ? Entrez l'ID de l'emprunt : ");
    fgets(loanID, sizeof(loanID), stdin);
    loanID[strcspn(loanID, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    Loan selectedLoan;
    bool found = false;

    for (int i = 0; i < numLoans; i++)
    {
        if (strcmp(loans[i].LoanID, loanID) == 0)
        {
            selectedLoan = loans[i];
            found = true;
            break;
        }
    }

    if (found)
    {
        User selectedUser;
        Book selectedBook;

        // Recherche du membre correspondant à l'ID de l'emprunt
        for (int i = 0; i < numUsers; i++)
        {
            if (strcmp(users[i].UserID, selectedLoan.userID) == 0)
            {
                selectedUser = users[i];
                break;
            }
        }

        // Recherche du livre correspondant à l'ID de l'emprunt
        for (int i = 0; i < numBooks; i++)
        {
            if (strcmp(books[i].BookID, selectedLoan.bookID) == 0)
            {
                selectedBook = books[i];
                break;
            }
        }

        printf("Emprunt trouvé :\n");
        printf("ID de l'emprunt : %s\n", selectedLoan.LoanID);
        printf("Membre : %s %s\n", selectedUser.FirstName, selectedUser.LastName);
        printf("Livre emprunté : %s\n", selectedBook.Title);
    }
    else
    {
        printf("Aucun emprunt trouvé avec cet ID.\n");
    }
}

void displayLoansList(Loan *loans, int numLoans)
{
    printf("Liste des emprunts :\n");

    for (int i = 0; i < numLoans; i++)
    {
        printf("Emprunt %d :\n", i + 1);
        printf("ID emprunt : %s\n", loans[i].LoanID);
        printf("ID membre emprunteur : %s\n", loans[i].userID);
        printf("ID du livre emprunte : %s\n", loans[i].bookID);
    }
}



///Fonctions de génération d'identifiants uniques


void generateString(char *temp)
{
    // Liste de tous les caractères qui peuvent être ajoutés à l'UID
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int charactersCount = strlen(characters);

    for(int i = 0; i < UID_SIZE; i++)
    {
        temp[i] = characters[rand() % charactersCount];
    }

    temp[UID_SIZE] = '\0';
}

void generateId(enum Type type, char *location, Book *books, int numBooks, User *users, int numUsers, Loan *loans, int numLoans)
{
    char prefix[UID_SIZE + 5];

    switch (type)
    {
    case 1:
        strcpy(prefix, "BOOK-");
        break;
    
    case 2:
        strcpy(prefix, "USER-");
        break;
        
    case 3:
        strcpy(prefix, "LOAN-");
        break;
    }

    do 
    {
        generateString(location);
        char temp[UID_SIZE + 5];
        strcpy(temp, prefix);
        strcat(temp, location);
        strcpy(location, temp);
    } while (IsIdUsed(type, location, books, numBooks, users, numUsers, loans, numLoans));
}

bool IsIdUsed(enum Type type, char *idString, Book *books, int numBooks, User *users, int numUsers, Loan *loans, int numLoans) 
{
    switch (type)
    {
    case 1: // Book
        for(int i = 0; i < numBooks; i++)
        {
            if(strcmp(books[i].BookID, idString) == 0)
            {
                return true;
            }
        }
        break;

    case 2: // User
        for(int i = 0; i < numUsers; i++)
        {
            if(strcmp(users[i].UserID, idString) == 0)
            {
                return true;
            }
        }
        break;

    case 3: // Loan
        for(int i = 0; i < numLoans; i++)
        {
            if(strcmp(loans[i].LoanID, idString) == 0)
            {
                return true;
            }
        }
        break;
    }

    return false;
}
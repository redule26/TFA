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
void deleteLoan(Loan*, int*);

///GEN ID PROTOTYPES
void generateString(char*);
void generateId(enum Type, char*, Book*, int, User*, int, Loan*, int);
bool IsIdUsed(enum Type, char*, Book*, int, User*, int, Loan*, int);

int main() {

    //J'ai besoin de la fonction rand() pour générer un id unique
    srand(time(NULL));

    //création des "bases de données" chargées dans le programme
    Book books[MAX_LIVRES];
    User users[MAX_MEMBRES];
    Loan loans[MAX_EMPRUNTS];

    //on a besoin du nombre d'elements dans les bases de données
    int numBooks = 0, numUsers = 0, numLoans = 0;
    int choice;

    //Chargement des données contenues dans les fichiers dans les arrays de livres, d'utilisateur et d'emprunts.
    loadData(books, &numBooks, users, &numUsers, loans, &numLoans);

    //tant qu'on ne quitte pas le programme avec 0
    while(1) {

        //variable utilisée pour le switch
        choice = 0;
        printf("\nBienvenue sur le programme de gestion de la bibliotheque IPES Wavre, que souhaitez-vous faire ?\n");

        ///Gestion des livres
        printf("1. Ajouter un livre\n");
        printf("2. Afficher la bibliotheque\n");
        printf("3. Montrer un livre par son identifiant\n\n");

        printf("4. Ajouter un membre \n");
        printf("5. Afficher la liste des membres \n");
        printf("6. Afficher un membre et ses emprunts\n\n");

        printf("7. creer un emprunt\n");
        printf("8. afficher les informations d'un emprunt\n");
        printf("9. Afficher la liste des emprunts\n");
        printf("10. Supprimer un emprunt\n\n");

        printf("0. Quitter\n");
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
                deleteLoan(loans, &numLoans);
                break;

            case 0:
                printf("Au revoir !\n");
                saveData(books, numBooks, users, numUsers, loans, numLoans);
                return 0;
            default:
                printf("Choix invalide.\n");
                break;
        }
    }
}



///Fonctions de chargement et sauvegarde des données


//Fonction appelée à la fermeture du programme pour stocker le contenu des tableaux 'livres', 'membres' et 'emprunts' dans les fichiers.txt
void saveData(Book *books, int numBooks, User *users, int numUsers, Loan *loans, int numLoans)
{

    //nom des fichiers pour faire la sauvegarde et les codes d'erreur de manière dynamique
    char bookFile[50] = "livres.txt";
    char userFile[50] = "membres.txt";
    char loanFile[50] = "emprunts.txt";

    //ouverture du fichier livres
    FILE *bookPtr = fopen(bookFile, "w");
    if (bookPtr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", bookFile);
        return;
    }

    //on imprime les n enregistrements
    for (int i = 0; i < numBooks; i++)
    {
        fprintf(bookPtr, "%s;%s;%s;%d\n", books[i].BookID, books[i].Title, books[i].Author, books[i].Year);
    }

    fclose(bookPtr);
    printf("Les livres ont ete enregistres avec succes dans le fichier '%s'.\n", bookFile);

    FILE *userPtr = fopen(userFile, "w");
    if (userPtr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", userFile);
        return;
    }

    for (int i = 0; i < numUsers; i++)
    {
        fprintf(userPtr, "%s;%s;%s;%s\n", users[i].UserID, users[i].Username, users[i].LastName, users[i].FirstName);
    }

    fclose(userPtr);
    printf("Les membres ont ete enregistres avec succes dans le fichier '%s'.\n", userFile);

    FILE *loanPtr = fopen(loanFile, "w");
    if (loanPtr == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier '%s'.\n", loanFile);
        return;
    }

    for (int i = 0; i < numLoans; i++)
    {
        fprintf(loanPtr, "%s;%s;%s\n", loans[i].LoanID, loans[i].userID, loans[i].bookID);
    }

    fclose(loanPtr);
    printf("Les emprunts ont ete enregistres avec succes dans le fichier '%s'.\n", loanFile);
}

//Fonction appelée au démarrage du programme pour stocker dans les tableaux de structure 'livres', 'membres' et 'emprunts' les données présents dans les fichiers .txt
void loadData(Book *books, int *numBooks, User *users, int *numUsers, Loan *loans, int *numLoans)
{
    //nom des fichiers pour faire la sauvegarde et les codes d'erreur de manière dynamique
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

    //chaine de caractères qui sert de buffer
    char line[100];
    //on boucle tant que la ligne contient du texte
    while (fgets(line, sizeof(line), ptr_bookFile) != NULL)
    {
        // Supprimer le caractère de nouvelle ligne à la fin de la ligne lue
        line[strcspn(line, "\n")] = '\0';

        //strtok permet de séparer la ligne en plusieurs parties et de retirer les ";"
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

    //on boucle tant que la ligne contient du texte
    while (fgets(line, sizeof(line), ptr_usersFile) != NULL)
    {
        // Supprimer le caractère de nouvelle ligne à la fin de la ligne lue
        line[strcspn(line, "\n")] = '\0';

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

    //on boucle tant que la ligne contient du texte
    while (fgets(line, sizeof(line), ptr_loanFile) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

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

    printf("Les fichiers %s, %s et %s ont ete charges avec succes.\n", bookFile, usersFile, loanFile);
}


///Fonctions de livres

//addBook() : permet de rajouter un livre dans le array de livres et par la suite dans le fichier
void addBook(Book *books, int *numBooks)
{
    if (*numBooks == MAX_LIVRES)
    {
        printf("La bibliotheque est pleine. Impossible d'ajouter un livre.\n");
        return;
    }

    //creation d'un livre qui va être rajouté à la fin de l'enregistrement par l'utilisateur
    Book newBook;

    //fonction qui va générer un ID de type "BOOK-......"
    generateId(BookType, newBook.BookID, books, *numBooks, NULL, 0, NULL, 0);

    printf("Titre du livre : ");
    fgets(newBook.Title, sizeof(newBook.Title), stdin);
    newBook.Title[strcspn(newBook.Title, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Auteur : ");
    fgets(newBook.Author, sizeof(newBook.Author), stdin);
    newBook.Author[strcspn(newBook.Author, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Annee de publication : ");
    char yearInput[100];
    fgets(yearInput, sizeof(yearInput), stdin);
    sscanf(yearInput, "%i", &newBook.Year);

    //on rajoute le livre dans le tableau
    books[*numBooks] = newBook;
    (*numBooks)++;

    printf("Livre ajoute avec succes !\n");
}

//displayLibrary() : fonction qui permet d'afficher une liste complète des livres stockés dans le array livre
void displayLibrary(Book *books, int numBooks)
{
    if (numBooks == 0)
    {
        printf("La bibliotheque est vide.\n");
        return;
    }

    printf("Livres dans la bibliotheque :\n");
    for(int i = 0; i < numBooks; i++)
    {
        printf("Livre %d :\n", i + 1);
        printf("UID : %s\n", books[i].BookID);
        printf("Titre : %s\n", books[i].Title);
        printf("Auteur : %s\n", books[i].Author);
        printf("Annee de publication : %d\n", books[i].Year);
        printf("--------------------------------\n");
    }
}

//showBook() : Affichage des informations à propos d'un livre en particulier
void showBook(Book *books, int numBooks)
{
    char id[30];
    printf("Quel livre voulez-vous selectionner ? : ");
    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
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

    //à la fin de la boucle, si found == true, on affiche les infos du livre choisi
    if (found)
    {
        printf("Voici le livre dont l'id est : %s\n", selectedBook.BookID);
        printf("%s - %s - %d\n", selectedBook.Title, selectedBook.Author, selectedBook.Year);
    }
    else
    {
        printf("Livre non trouve.\n");
    }
}


///Fonctions d'utilisateur


//addUser() : permet de rajouter un utilisateur dans le array de membres et par la suite dans le fichier
void addUser(User *users, int *numUsers)
{
    if (*numUsers == MAX_MEMBRES)
    {
        printf("L'emplacement pour les membres est plein.\n");
        return;
    }

    User newUser;

    // Génération de l'ID utilisateur "USER-....."
    generateId(UserType, newUser.UserID, NULL, 0, users, *numUsers, NULL, 0);

    printf("Nom de famille de l'utilisateur : ");
    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
    fgets(newUser.LastName, sizeof(newUser.LastName), stdin);
    newUser.LastName[strcspn(newUser.LastName, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Prenom de l'utilisateur : ");
    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
    fgets(newUser.FirstName, sizeof(newUser.FirstName), stdin);
    newUser.FirstName[strcspn(newUser.FirstName, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    printf("Pseudo de l'utilisateur : ");
    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
    fgets(newUser.Username, sizeof(newUser.Username), stdin);
    newUser.Username[strcspn(newUser.Username, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    users[*numUsers] = newUser;
    (*numUsers)++;

    printf("Utilisateur ajoute avec succes !\n");
}

//showUser() : permet d'afficher des informations d'un utilisateur par son identifiant
void showUser(User *users, int numUsers, Loan *loans, int numLoans)
{
    char id[30];
    printf("Quel membre voulez-vous selectionner ? : ");
    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    User selectedUser;
    bool found = false;

    for (int i = 0; i < numUsers; i++)
    {
        ///cette fonction permet de comparer deux variables
        if (strcmp(users[i].UserID, id) == 0)
        {
            selectedUser = users[i];
            found = true;
            break;
        }
    }

    if (found)
    {
        printf("Voici les informations sur le membre selectionne :\n\n");
        printf("UID : %s\n", selectedUser.UserID);
        printf("Nom : %s\n", selectedUser.LastName);
        printf("Prenom : %s\n", selectedUser.FirstName);
        printf("Pseudo : %s\n", selectedUser.Username);
        printf("--------------------------------\n\n");

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
        printf("Aucun membre trouve avec cet UID.\n");
    }
}

//displayUsersList() : affiche une liste complète des membres
void displayUsersList(User *users, int numUsers)
{
    if(numUsers == 0) {
        printf("Le fichier des utilisateurs est vide.\n");
        return;
    }

    printf("Utilisateurs dans la bibliotheque :\n");
    for(int i = 0; i < numUsers; i++)
    {
        printf("ID : %s\n", users[i].UserID);
        printf("Nom d'utilisateur : %s\n", users[i].Username);
        printf("Prenom : %s\n", users[i].FirstName);
        printf("Nom de famille : %s\n\n", users[i].LastName);
    }
}


///Fonctions d'emprunt


//createLoan() : fonction qui permet de créer un nouvel emprunt (si le livre n'est pas emprunté)
void createLoan(Loan *loans, int *numLoans, User *users, int numUsers, Book *books, int numBooks)
{
    char userID[100];
    char bookID[100];

    printf("ID de l'utilisateur : ");

    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
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
            printf("Le livre avec l'ID '%s' est déjà emprunte.\n", bookID);
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
        //strcmp sert à vérifier une égalité comme ==
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
    generateId(LoanType, newLoan.LoanID, NULL, 0, NULL, 0, loans, *numLoans);
    strcpy(newLoan.userID, userID);
    strcpy(newLoan.bookID, bookID);

    loans[*numLoans] = newLoan;
    (*numLoans)++;

    printf("Emprunt cree avec succès !\n");
}

//showLoan() : affiche la l'emprunt en fonction de l'id donné, et affiche le nom du livre et du membre (même logique que User et Emprunt)
void showLoan(User *users, int numUsers, Book *books, int numBooks, Loan *loans, int numLoans)
{
    char loanID[30];
    printf("Quel emprunt voulez-vous afficher ? Entrez l'ID de l'emprunt : ");

    //gets est une fonction dangereuse selon vscode du coup j'utilise fgets
    fgets(loanID, sizeof(loanID), stdin);
    loanID[strcspn(loanID, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    Loan selectedLoan;
    bool found = false;

    for (int i = 0; i < numLoans; i++)
    {
        //si le résultat de la comparaison équivaut à 0
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

        printf("Emprunt trouve :\n");
        printf("ID de l'emprunt : %s\n", selectedLoan.LoanID);
        printf("Membre : %s %s\n", selectedUser.FirstName, selectedUser.LastName);
        printf("Livre emprunte : %s\n", selectedBook.Title);
    }
    else
    {
        printf("Aucun emprunt trouve avec cet ID.\n");
    }
}

//displayLoansList() : affiche une liste compltète des emprunts (même logique que displayUsers et displayBooks)
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

// deleteLoan() : supprimer un emprunt
void deleteLoan(Loan *loans, int *numLoans)
{
    if (*numLoans == 0)
    {
        printf("Il n'y a aucun emprunt enregistre.\n");
        return;
    }

    char loanID[30];
    printf("Entrez l'identifiant de l'emprunt à supprimer : ");
    fgets(loanID, sizeof(loanID), stdin);
    loanID[strcspn(loanID, "\n")] = '\0'; // Supprimer le caractère de nouvelle ligne

    int deleteIndex = -1;
    for (int i = 0; i < *numLoans; i++)
    {
        if (strcmp(loans[i].LoanID, loanID) == 0)
        {
            deleteIndex = i;
            break;
        }
    }

    if (deleteIndex != -1)
    {
        // Déplacer le dernier emprunt à la position de l'emprunt à supprimer
        loans[deleteIndex] = loans[*numLoans - 1];
        (*numLoans)--;
        printf("L'emprunt a ete supprime avec succes.\n");
    }
    else
    {
        printf("Emprunt non trouve.\n");
    }
}

///Fonctions de génération d'identifiants uniques


//generateString() : fonction qui génère 20 caractères aléatoires mis ensemble dans une chaine de caractères
void generateString(char *temp)
{
    // Liste de tous les caractères qui peuvent être ajoutés à l'UID
    char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    int charactersCount = strlen(characters);

    //on boucle pour remplir la chaine
    for(int i = 0; i < UID_SIZE; i++)
    {
        temp[i] = characters[rand() % charactersCount];
    }

    //je retire le \n qui est enregistré à la fin de la chaine de caractères
    temp[UID_SIZE] = '\0';
}

//generateId() : fonction qui génère un ID unique en fonction du type introduit
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

    //on boucle tant que l'id généré n'est pas unique (fonction IsIdUsed())
    do
    {
        generateString(location);
        char temp[UID_SIZE + 5];
        strcpy(temp, prefix);
        strcat(temp, location);
        strcpy(location, temp);
    } while (IsIdUsed(type, location, books, numBooks, users, numUsers, loans, numLoans));
}

//IsIdUsed() : fonction qui va déterminer si l'id est utilisé dans le type en question (livre, utilisateur, emprunts)
bool IsIdUsed(enum Type type, char *idString, Book *books, int numBooks, User *users, int numUsers, Loan *loans, int numLoans)
{
    switch (type)
    {
    case 1: // Book
        for(int i = 0; i < numBooks; i++)
        {
            ///si le resultat de la comparaison entre l'id introduit et le livre[i] sont égaux
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

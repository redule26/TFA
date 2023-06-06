# TFA
Application console de gestion de bibliothèque en langage C que j'ai du réaliser pour mon examen de Labo Logique (programmation en C) durant mon année scolaire 2022-2023 à l'IPES Bohy de Wavre

## Consignes
Créé un programme qui va permettre de gérer une bibliotheque publique

1. Stockage des livres, et de leurs données
2. Gestion des membres de la bibliothèque ainsi que de leurs emprunts
3. Bases de données en fichiers .txt

## Organisation
La base de données est séparée en 3 parties
- un fichier 'membres.txt'
- un fichier 'livres.txt'
- un fichier 'emprunts.txt'

## Structures
```
struct Book {
    char BookID[100]; //par exemple : ISBN ou BOOK-132764781
    char Title[100];
    char Author[100];
    int Year;
} typedef Book;

struct User {
    char UserID[100]; //par exemple : USER-A3UIOR478146
    char Username[100];
    char FirstName[100];
    char LastName[100];
} typedef User;

struct Loan {
    char UID[100]; //par exemple : EMP-129380fez13198
    char userID[100];
    char bookID[100];
} typedef Loan;
```
## Fonctions disponibles
Au démarrage
- Chargement des fichiers 'txt' dans les structures grâce à une fonction loadData();

Gestion des livres
- addBook()
- removeBook()
- listBooks()
- infoBook(id)

Gestion des membres
- addUser()
- showUser(id)
- displayUsersList()

Gestion des emprunts
- createLoan()
- showLoan(id)
- displayLoanList()
- deleteLoan(id)

À la fermeture
- sauvegarde des données présentes dans les tableaux de structures dans les fichiers grâce à saveData(); 

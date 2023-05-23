# TFA
Application console de gestion de bibliothèque en langage C

## Consignes
Créé un programme qui va permettre de gérer une bibliotheque publique

1. Stockage des livres, de leurs noms et de leurs maison d'édition
2. Gestion des membres de la bibliothèque ainsi que de leurs emprunts
3. Bases de données en fichier .txt

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
    char UID[100]; //par exemple : EMP-129380-13198
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
- infoBook(int id)

À la fermeture
- sauvegarde des données présentes dans les tableaux de structures dans les fichiers grâce à saveData(); 

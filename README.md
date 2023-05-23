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
struct User {
    char UID[]; (unique user id)
    char LastName[50];
    char FirstName[50];
    char Username[50];

} typedef User;
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

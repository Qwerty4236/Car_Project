#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 
          /$$$$$$                                      /$$              
         /$$__  $$                                    | $$              
        | $$  \ $$ /$$  /$$  /$$  /$$$$$$   /$$$$$$  /$$$$$$   /$$   /$$
        | $$  | $$| $$ | $$ | $$ /$$__  $$ /$$__  $$|_  $$_/  | $$  | $$
        | $$  | $$| $$ | $$ | $$| $$$$$$$$| $$  \__/  | $$    | $$  | $$
        | $$/$$ $$| $$ | $$ | $$| $$_____/| $$        | $$ /$$| $$  | $$
        |  $$$$$$/|  $$$$$/$$$$/|  $$$$$$$| $$        |  $$$$/|  $$$$$$$
        \____ $$$ \_____/\___/  \_______/|__/         \___/   \____  $$
            \__/                                             /$$  | $$
                                                            | $$$$$$/
                                                            \______/ 
*/

/*
    Bonjour, ceci est un commentaire en français pour indiquer que le code suivant gère une structure 
    de données pour des voitures. Je vais utiliser des commentaires en anglais pour le reste du code afin 
    de maintenir la cohérence avec les conventions de codage courantes. Merci de votre compréhension.
*/

/*
    Hello, this is a comment in French indicating that the following code manages a data structure for cars.
    I will use comments in English for the rest of the code to maintain consistency with common coding conventions.
    thank you for your understanding.
*/

char *stringlwr(char *str) { // Function to convert a string to lowercase
    char *orig = str;
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
    return orig;
}

struct Voiture { // Structure to represent a car
    char *marque; // brand
    char *modele; // model
    int annee; // year
    float kilometrage; // mileage in kilometers
};

void afficherVoiture(struct Voiture v) { // Function to display car details
    printf("Marque: %s\n", v.marque);
    printf("Modèle: %s\n", v.modele);
    printf("Année: %d\n", v.annee);
    printf("Kilométrage: %.2f km\n", v.kilometrage);
}

void afficherToutesVoitures(struct Voiture voitures[], int taille) { // Function to display all cars
    for (int i = 0; i < taille; i++) {
        printf("Voiture %d:\n", i + 1);
        afficherVoiture(voitures[i]);
        printf("\n");
    }
}

void ajouterVoiture(struct Voiture *voitures[], int *taille) { // Function to add a new car
    struct Voiture nouvelleVoiture;
    char buffer[100]; // maximum buffer size for input
    
    fflush(stdin);
    printf("Entrez la marque de la voiture: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    nouvelleVoiture.marque = strdup(buffer); //the strdup function allocates memory and copies the string
    // Note: strdup could be an alternative for malloc + strcpy.
    
    fflush(stdin);
    printf("Entrez le modèle de la voiture: ");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    nouvelleVoiture.modele = strdup(buffer);

    printf("Entrez l'année de la voiture: ");
    scanf("%d", &nouvelleVoiture.annee);

    printf("Entrez le kilométrage de la voiture: ");
    scanf("%f", &nouvelleVoiture.kilometrage);

    *voitures = realloc(*voitures, (*taille + 1) * sizeof(struct Voiture)); // Resize the array to hold the new car
    (*voitures)[*taille] = nouvelleVoiture; // Add the new car to the array
    (*taille)++; // Increment the size of the array
}

void modifierVoiture(struct Voiture voitures[], int taille, int index) { // Function to modify car details
    if (index < 0 || index >= taille) { // Validate index condition
        printf("Index invalide.\n");
        return;
    }

    char buffer[100]; // buffer for input

    fflush(stdin);
    printf("Entrez la nouvelle marque de la voiture (actuelle: %s): ", voitures[index].marque);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    if(buffer[0] != '\0'){ // Only update if input is not empty
        free(voitures[index].marque);
        voitures[index].marque = strdup(buffer);
    }

    
    fflush(stdin);
    printf("Entrez le nouveau modèle de la voiture (actuel: %s): ", voitures[index].modele);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = 0; // Remove newline character
    if(buffer[0] != '\0'){ // Only update if input is not empty
        free(voitures[index].modele);
        voitures[index].modele = strdup(buffer);
    }
    
    fflush(stdin);
    printf("Entrez la nouvelle année de la voiture (actuelle: %d): ", voitures[index].annee);
    scanf("%d", &voitures[index].annee);

    printf("Entrez le nouveau kilométrage de la voiture (actuel: %.2f km): ", voitures[index].kilometrage);
    scanf("%f", &voitures[index].kilometrage);
}

void suprimerVoiture(struct Voiture voitures[], int *taille, int index) { // Function to delete a car
    if (index < 0 || index >= *taille) {
        printf("Index invalide.\n");
        return;
    }
    free(voitures[index].marque); // Free allocated memory for brand
    free(voitures[index].modele); // Free allocated memory for model
    for (int i = index; i < *taille - 1; i++) {
        voitures[i] = voitures[i + 1]; // Shift cars to fill the gap
    }
    (*taille)--;
}

void rechercherVoiture(struct Voiture voitures[], int taille, char *marque) { // Function to search for cars by brand
    int trouve = 0; // Flag to indicate if a car was found
    for (int i = 0; i < taille; i++) {
        if (strcmp(stringlwr(voitures[i].marque), stringlwr(marque)) == 0) { // Case-insensitive comparison
            afficherVoiture(voitures[i]);
            trouve = 1; // Mark as found
        }
    }
    if (!trouve) { // If no car found
        printf("Aucune voiture trouvée avec la marque %s.\n", marque);
    }
}

void trierVoituresParAnnee(struct Voiture voitures[], int taille) { // Function to sort cars by year using bubble sort
    for (int i = 0; i < taille - 1; i++) { 
        for (int j = 0; j < taille - i - 1; j++) { // Last i elements are already sorted
            if (voitures[j].annee > voitures[j + 1].annee) { // Compare years
                struct Voiture temp = voitures[j];
                voitures[j] = voitures[j + 1];
                voitures[j + 1] = temp;
            }
        }
    }
}

void libererMemoire(struct Voiture voitures[], int taille) { // Function to free allocated memory
    for (int i = 0; i < taille; i++) {
        free(voitures[i].marque);
        free(voitures[i].modele);
    }
    free(voitures);
}

void afficherMenu() { // Function to display the menu
    printf("Menu:\n");
    printf("1. Afficher toutes les voitures\n");
    printf("2. Ajouter des voitures\n");
    printf("3. Modifier une voiture\n");
    printf("4. Supprimer une voiture\n");
    printf("5. Rechercher une voiture par marque\n");
    printf("6. Trier les voitures par année\n");
    printf("7. Quitter\n");
    printf("Choisissez une option: ");
}

int main() {
    struct Voiture *voitures = NULL; // Dynamic array of cars
    int taille = 0; // Current size of the array
    int choix; // User choice from the menu
    int index; // Index for various operations

    do {
        afficherMenu(); // Display the menu
        scanf("%d", &choix);// Get user choice

        switch (choix) {
            case 1:
                afficherToutesVoitures(voitures, taille);
                break;
            case 2:
                do{
                    printf("Combien de voitures voulez-vous ajouter? ");
                    scanf("%d", &index);
                } while (index <= 0);

                for (int i = 0; i < index; i++) {
                    printf("Ajout de la voiture %d:\n", i + 1);
                    ajouterVoiture(&voitures, &taille);
                }
                break;
            case 3: {
                do
                {
                    printf("Entrez l'index de la voiture à modifier (0 à %d): ", taille - 1);
                    scanf("%d", &index);
                } while (index < 0 || index >= taille);

                modifierVoiture(voitures, taille, index);
                break;
            }
            case 4: {
                do
                {
                    printf("Entrez l'index de la voiture à supprimer (0 à %d): ", taille - 1);
                    scanf("%d", &index);
                } while (index < 0 || index >= taille);

                suprimerVoiture(voitures, &taille, index);
                break;
            }
            case 5: {
                char marque[100];
                printf("Entrez la marque de la voiture à rechercher: ");
                scanf("%s", marque);
                rechercherVoiture(voitures, taille, marque);
                break;
            }
            case 6:
                trierVoituresParAnnee(voitures, taille);
                printf("Voitures triées par année.\n");
                break;
            case 7:
                printf("Quitter le programme.\n");
                break;
            default:
                printf("Option invalide. Veuillez réessayer.\n");
        }
    } while (choix != 7);

    libererMemoire(voitures, taille); // Free allocated memory before exiting
    return 0;
}

// End of main.c

/*
    Note: Due to lack of time, some functions may not have extensive error handling or input validation.
    Also, the main goal for me is to ensure that the program works correctly according to the specifications
    provided. So I couldn't add one feature that allows saving and loading data from a file.
    I hope to implement this feature in future versions of the program.
    Thank you for your understanding and reviewing my code.
*/
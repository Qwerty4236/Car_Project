#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Voiture {
    char *marque;
    char *modele;
    int annee;
    float kilometrage;
};

void afficherVoiture(struct Voiture v) { // Function to display car details
    printf("Marque: %s\n", v.marque);
    printf("Modèle: %s\n", v.modele);
    printf("Année: %d\n", v.annee);
    printf("Kilométrage: %.2f km\n", v.kilometrage);
}

void ajouterVoiture(struct Voiture *voitures[], int *taille) {
    struct Voiture nouvelleVoiture;
    char buffer[100]; // maximum buffer size for input

    printf("Entrez la marque de la voiture: ");
    scanf("%s", buffer);
    nouvelleVoiture.marque = strdup(buffer); //the strdup function allocates memory and copies the string
    // Note: strdup could be an alternative for malloc + strcpy.

    printf("Entrez le modèle de la voiture: ");
    scanf("%s", buffer);
    nouvelleVoiture.modele = strdup(buffer);

    printf("Entrez l'année de la voiture: ");
    scanf("%d", &nouvelleVoiture.annee);

    printf("Entrez le kilométrage de la voiture: ");
    scanf("%f", &nouvelleVoiture.kilometrage);

    *voitures = realloc(*voitures, (*taille + 1) * sizeof(struct Voiture));
    (*voitures)[*taille] = nouvelleVoiture;
    (*taille)++;
}
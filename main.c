#include <stdio.h>
#include <stdlib.h>

typedef struct Date{
 char jour[3];
 char mois[3];
 char annee[5];
}date;

typedef struct Produit{
char *Nom_produit;
char Reference[100];
float Montant;
date DateAchat;
struct Produit* suiv;
}produit;

typedef struct Liste{
produit cellule;
struct Liste* psuiv;
}liste;

liste* cree_liste_produits(){
    return NULL;
}

int est_vide(liste * tete){
    return tete == NULL;
}

liste* creer_produit(char *nom, char *ref, float montant, date dateAchat){
    produit* produitnv = (produit*)malloc(sizeof(produit));
    produitnv->Nom_produit = (char*)malloc(strlen(nom)+1);
    strcpy(produitnv->Nom_produit, nom);
    strcpy(produitnv->Reference, ref);
    produitnv->Montant = montant;
    produitnv->DateAchat = dateAchat;
    produitnv->suiv = NULL;

    liste* newListe = (liste*)malloc(sizeof(liste));
    newListe->cellule = *produitnv;
    newListe->psuiv = NULL;
    free(produitnv);

    return newListe;
}

void afficher_produit(liste* produit){
    printf("Nom:%s\n",produit->cellule.Nom_produit);
    printf("reference:%s\n",produit->cellule.Reference);
    printf("montant:%.2f\n",produit->cellule.Montant);
    printf("date dachat: %s/%s/%s\n",
           produit->cellule.DateAchat.jour,
           produit->cellule.DateAchat.mois,
           produit->cellule.DateAchat.annee);
}

liste* ajouter_debut(liste* tete, char *nom, char *ref, float montant, date dateAchat){
    liste* produitnv = creer_produit(nom, ref, montant, dateAchat);
    produitnv->psuiv = tete;
    return produitnv;
}

liste* ajouter_fin(liste* tete, char *nom, char *ref, float montant, date dateAchat){
    liste* produitnv = creer_produit(nom, ref, montant, dateAchat);

    if(tete == NULL){
        return produitnv;
    }

    liste* tmp = tete;
    while(tmp->psuiv != NULL){
        tmp = tmp->psuiv;
    }
    tmp->psuiv = produitnv;
    return tete;
}

void afficher_produits(liste* tete){
    liste* tmp = tete;
    while(tmp != NULL){
        afficher_produit(tmp);
        tmp = tmp->psuiv;
    }
}

int longueur(liste* tete){
    int c = 0;
    liste* tmp = tete;
    while(tmp != NULL){
        c++;
        tmp = tmp->psuiv;
    }
    return c;
}

liste* supprimer_debut(liste* tete){
    if(tete == NULL){
        printf("la liste est vide\n");
        return NULL;
    }

    liste* m = tete;
    tete = tete->psuiv;
    free(m->cellule.Nom_produit);
    free(m);
    return tete;
}

liste* supprimer_fin(liste* tete){
    if(tete == NULL){
        printf("liste vide\n");
        return NULL;
    }

    if(tete->psuiv == NULL){
        free(tete->cellule.Nom_produit);
        free(tete);
        return NULL;
    }

    liste* tmp = tete;
    while(tmp->psuiv->psuiv != NULL){
        tmp = tmp->psuiv;
    }

    free(tmp->psuiv->cellule.Nom_produit);
    free(tmp->psuiv);
    tmp->psuiv = NULL;
    return tete;
}

int main() {
    liste* maListe = cree_liste_produits();
    printf("Liste vide? %s\n", est_vide(maListe) ? "Oui" : "Non");

    date date1 = {"01", "01", "2023"};
    date date2 = {"15", "03", "2023"};
    date date3 = {"20", "12", "2023"};

    maListe = ajouter_debut(maListe, "Ordinateur", "REF123", 1200.50, date1);
    maListe = ajouter_debut(maListe, "Smartphone", "REF456", 899.99, date2);
    maListe = ajouter_fin(maListe, "Tablette", "REF789", 450.75, date3);

    printf("Tous les produits");
    afficher_produits(maListe);
    printf("Longueur de la liste: %d\n", longueur(maListe));

    printf("Suppression du premier produit");
    maListe = supprimer_debut(maListe);
    afficher_produits(maListe);

    printf("Suppression du dernier produit");
    maListe = supprimer_fin(maListe);
    afficher_produits(maListe);

    printf("\nLongueur finale: %d\n", longueur(maListe));

    return 0;
}

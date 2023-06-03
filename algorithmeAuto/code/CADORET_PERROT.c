/*
* Duncan Cadoret, Maxime Perrot
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIGNE 6
#define COLONNE 7

typedef int t_grille[LIGNE][COLONNE];

int main(int argc, char** argv);
void chargerGrille(char** argv, t_grille grille);

int chercherLigne(t_grille laGrille, int col);
bool estAligne(t_grille laGrille, int lig, int col, int taille);
void copieGrille(t_grille g1, t_grille g2);
int MAD_Algorithm(t_grille laGrille);
int alignement(t_grille laGrille, int ligne, int colonne, int pion, int taille);

const int VIDE = 0;
const int JOUEUR = 1;
const int ADVERSAIRE = 2;


// La fonction principale reçoit la grille du tour et retourne le coup choisi
// Vous n'avez pas à modifier cette fonction
int main(int argc, char** argv) 
{
    t_grille grille;

    chargerGrille(argv, grille);

    return MAD_Algorithm(grille);
}

// Charge la grille du tour actuel
// Vous n'avez pas à modifier cette fonction
void chargerGrille(char** argv, t_grille grille) 
{
    for(int i = 0; i < LIGNE; i++)
        for(int j = 0; j < COLONNE; j++)
            grille[i][j] = atoi(argv[i * COLONNE + j + 1]);
}

/***********************************
 * Fonctions pour le MAD Algorithm *
 ***********************************/
 
int chercherLigne(t_grille laGrille, int col)
{
    int ligne = -1;

    while (ligne < LIGNE - 1 && laGrille[ligne + 1][col] == VIDE)
    {
        ligne++;
    }

    return ligne;
}

bool estAligne(t_grille laGrille, int lig, int col, int taille)
{
    // consiste à regarder si une ligne de <taille> pions s'est formÃ©e autour du pion qui vient de tomber en (lig, col)
    int lePion = laGrille[lig][col];
    int cpt, i, j;

    // regarder la verticale, en comptant le nombre de pions au Sud (inutile de regarder au Nord du pion qui vient de tomber)
    i = lig;
    cpt = 0;
    while (i < LIGNE && laGrille[i][col] == lePion)
    {
        cpt++;
        i++;
    }
    if (cpt >= taille)
    {
        return true;
    }

    // regarder l'horizontale, en comptant le nombre de pions à l'Est et à l'Ouest
    j = col;
    cpt = 0;

    // on regarde à l'est
    while (j >= 0 && laGrille[lig][j] == lePion)
    {
        cpt++;
        j--;
    }
    j = col + 1;

    // on regarde à l'ouest
    while (j < COLONNE && laGrille[lig][j] == lePion)
    {
        cpt++;
        j++;
    }
    if (cpt >= taille)
    {
        return true;
    }

    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Ouest et au Sud Est
    i = lig;
    j = col;
    cpt = 0;

    // on regarde au Nord Ouest
    while (j >= 0 && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j--;
    }
    i = lig + 1;
    j = col + 1;

    // on regarde au Sud Est
    while (i < LIGNE && j < COLONNE && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j++;
    }
    if (cpt >= taille)
    {
        return true;
    }

    // regarder la diagonale descendante, en comptant le nombre de pions au Nord Est et au Sud Ouest
    i = lig;
    j = col;
    cpt = 0;

    // on regarde au Nord Est
    while (j < COLONNE && i >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i--;
        j++;
    }
    i = lig + 1;
    j = col - 1;

    // on regarde au Sud Ouest
    while (i < LIGNE && j >= 0 && laGrille[i][j] == lePion)
    {
        cpt++;
        i++;
        j--;
    }
    if (cpt >= taille)
    {
        return true;
    }

    return false;
}

void copieGrille(t_grille g1, t_grille g2)
{
    int x, y;

    for (y = 0; y < LIGNE; y++)
    {
        for (x = 0; x < COLONNE; x++)
        {
            g2[y][x] = g1[y][x];
        }
    }
}

bool aligner(t_grille laGrille, int ligne, int colonne, int pion, int taille)
{
    /*
    Si pion = ADVERSAIRE, fonction de défense
    Si pion = JOUEUR, fonction d'attaque
    Renvoie vrai si placer le pion dans la colonne permet de créer un alignement de taille donnée
    */

    t_grille grilleTemp;
    copieGrille(laGrille, grilleTemp);
    grilleTemp[ligne][colonne] = pion;
    return estAligne(grilleTemp, ligne, colonne, taille);
}

int MAD_Algorithm(t_grille laGrille)
{
	// A FAIRE : ramener tous les chercherLigne en une fois au début dans un tableau contenant les lignes pour chaque colonne
	int lignes[COLONNE];
	int milieu[COLONNE] = {3, 2, 4, 1, 5, 0, 6};
    int poubelle[COLONNE];
    int i;
    
    // LIGNES
    for (i = 0; i < COLONNE; i++)
    {
        lignes[i] = chercherLigne(laGrille, i);
    }
    
    // POUBELLE
    for (i = 0; i < COLONNE; i++)
    {
        poubelle[i] = aligner(laGrille, lignes[i]-1, i, ADVERSAIRE, 4);
        if (lignes[i] == -1)
        {poubelle[i] = true;}
    }

    // Attaque 4
    for (i = 0; i < COLONNE; i++)
    {
        if (aligner(laGrille, lignes[i], i, JOUEUR, 4) && (laGrille[lignes[i]][i]) == VIDE)
        {return i;}
	}
	
    // Défense 4
    for (i = 0; i < COLONNE; i++)
    {
        if (aligner(laGrille, lignes[i], i, ADVERSAIRE, 4) && (laGrille[lignes[i]][i]) == VIDE)
        {return i;}
    }

    // Défense 3
    for (i = 0; i < COLONNE; i++)
    {
        if (aligner(laGrille, lignes[i], i, ADVERSAIRE, 3) && !poubelle[i])
        {return i;}
    }

    // Attaque 3
    for (i = 0; i < COLONNE; i++)
    {
        if (aligner(laGrille, lignes[i], i, JOUEUR, 3) && !poubelle[i])
        {return i;}
    }

    // Attaque 2
    for (i = 0; i < COLONNE; i++)
    {
        if (aligner(laGrille, lignes[i], i, JOUEUR, 2) && !poubelle[i])
        {return i;}
    }

    // Défense 2
    for (i = 0; i < COLONNE; i++)
    {
        if (aligner(laGrille, lignes[i], i, ADVERSAIRE, 2) && !poubelle[i])
        {return i;}
    }

    // Milieu
    i = 0;
    while ( (laGrille[0][milieu[i]] != VIDE) && (i < (COLONNE-1)) )
    {
        i++;
    }
    return milieu[i];
}

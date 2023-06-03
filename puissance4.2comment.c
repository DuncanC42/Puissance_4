/**
 * \brief Programme du jeu Puissance 4 
 * 
 * \author Cadoret Duncan
 * 
 * \version 1.4
 * 
 * \date 22 novembre 2022
 * 
 * Ce programme permet a deux personnes de s'affronter afin d'affirmer
 * leur supériorité sur l'autre au travers du jeu mondialement connu qu'est le
 * PUISSANCE 4 !
 *  
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

/*=============Definition des constantes==========*/
/**
 * \def NBLIG
 * 
 * \brief Corresponds au nombre de lignes dans un tableau type Puissance 4
 * 
*/
/**
 * \def NBCOL
 * 
 * \brief Corresponds au nombre de colonnes dans un tableau type Puissance 4
 * 
*/
#define NBLIG 6
#define NBCOL 7


/**
 * \def VIDE
 * 
 * \brief constante caractère contenant un espace
 * 
*/

/**
 * 
 * \def INCONNU
 * 
 * \brief Constante carctère contenant un caractère désigannt une égalité
 *  
*/

/**
 * 
 * \def COLONNE_DEBUT
 * 
 * \brief Constante entière indiquant la colonne de positionnement 
 * d'origine du pion avant la moindre action du joueur.
 * 
*/

/**
 * 
 * \def RED
 * 
 * \brief Constante chaine de caractère se 
 * rapportant à un caractère rond plein de couleur rouge
*/

/**
 * 
 * \def YELLOW
 * 
 * \brief Constante chaine de caractère se 
 * rapportant à un caractère rond plein de couleur jaune
*/

const char PION_A = 'X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;
const char RED[18] = "\033[31m●\033[0m";
const char YELLOW[18] = "\033[33m●\033[0m";

/**
 * 
 * \typedef Grille
 * 
 * \brief type tableau à deux dimensions contenants des caractères
 * 
 * Le type Grille permet de stocker les elements de façon à simuler 
 * les différentes entrées possibles dans la grille d'un puissance 4
 * 
*/

typedef char Grille[NBLIG][NBCOL];

/**
 * 
 * \fn void afficheQuestionPion(char P1, char P2)
 * 
 * \brief Procédure qui indique le pion de chacun des joueurs
 * 
 * \param P1 : paramètre de sortie indiquant le pion du joueur 1
 * 
 * \param P2 : paramètre de sortie indiquant le pion du joueur 2
 * 
 * La procédure donne un affichage stylisé où elle demande au 
 * premier joueur de choisir avec quel pion il veut jouer tout
 * au long de la partie
 * 
*/

/**
 * 
 * \fn void initGrille(Grille g)
 * 
 * \brief procédure qui intialise le tableau du puissance 4
 * 
 * \param g : tableau à deux dimensions en entrée
 * 
 * La procédure intialise la grille en attribuant pour chacun
 * de elements du tableau la valeur VIDE
 * 
*/

/**
 * 
 * \fn void afficher(Grille g, char pion, int COLONNE_DEBUT)
 * 
 * \brief Création de l'aspect visuel du tableau à deux dimensions affiché
 * 
 * \param g : Grille représentant la grille de jeu
 * 
 * \param pion : 
*/

/***/

void afficheQuestionPion(char *P1,char *P2);
void initGrille(Grille);
void afficher(Grille, char, int);
bool grillePleine(Grille);
void jouer(Grille , char, int *, int *, bool *);
int choisirColonne(Grille, char, int, bool *);
int trouveLigne(Grille, int);
bool estVainqueur(Grille, int, int);
bool estVainqueurHoriz(Grille, int, int);
bool estVainqueurVertic(Grille, int, int);
bool estVainqueurDG(Grille, int, int);
bool estVainqueurGD(Grille, int, int);
void finDePartie(char, bool *);
void rules(); 



int main(){
    char vainqueur;
    char P1, P2; 
    int ligne, colonne;
    Grille g;
    bool recommencer;
    
    do{
        recommencer = false;

        rules();
    
        afficheQuestionPion(&P1, &P2); 
    
        initGrille(g);
        vainqueur = INCONNU;
        while(vainqueur == INCONNU && !(grillePleine(g)) && recommencer != true)
        {
            colonne = COLONNE_DEBUT;
            jouer(g,P1,&ligne,&colonne, &recommencer);
            if (recommencer != true){
                if(estVainqueur(g,ligne,colonne)){
                    vainqueur = P1;
                }
                else if(!(grillePleine(g))){
                    colonne = COLONNE_DEBUT;
                    jouer(g,P2,&ligne,&colonne, &recommencer);
                    if (recommencer !=  true){
                        if(estVainqueur(g, ligne, colonne)){
                            vainqueur = P2;
                        }
                    }
                    
                }
            }
        }
        if (recommencer != true){
            afficher(g, VIDE, COLONNE_DEBUT); 
            finDePartie(vainqueur, &recommencer);
            printf("\n");
        }

    }while(recommencer == true);
}    


void afficheQuestionPion(char *P1,char *P2){
    char a[5]; 
    int choix;
    printf("┌───────────────────────────────────────────────────────┐\n");
    for (int i = 0; i < 4; i++)
    {
        printf("│                                                       │\n");
    }
    printf("│             Joueur 1, choisissez votre pion           │\n");  
    printf("│                         (1 ou 2)                      │\n");
    printf("│                                                       │\n");
    printf("│                                                       │\n");
    printf("│                      1: %s  ou  2: %s                   │\n", RED, YELLOW);
    for (int i = 0; i < 5; i++)
    {
        printf("│                                                       │\n");
    }        
    printf("└───────────────────────────────────────────────────────┘\n");
    printf("\n");
    do
    {
        printf("Votre choix : ");
        scanf("%s",a);
        choix = atoi(a); //convertit une chaine de charactère en entier
    } while (choix != 1 && choix != 2);


    if (choix == 1)
    {
        *P1 = PION_A; 
        *P2 = PION_B; 
    }
    else
    {
        *P1 = PION_B; 
        *P2 = PION_A; 
    }
}

void initGrille(Grille g){
    int i,j;
    for (i=0;i<NBLIG;i++){
        for (j=0;j<NBCOL;j++){
            g[i][j] = VIDE;
        }
    }
}

void afficher(Grille g,char pion, int colonne){  
    int i,j;
    
    system("clear");

    for ( int x = 0; x < NBCOL; x++)
    {
        if (x == colonne){
            if (pion == PION_A){
                printf("  %s ",RED);
            }
            else if (pion == PION_B){
                printf("  %s ",YELLOW);
            }
        }
        else{
            printf("    ");
        }

    }
    
    printf("\n");
    printf(",---,---,---,---,---,---,---,\n");
    for (i = 0; i < NBLIG; i++)
    {
        for ( j = 0; j < NBCOL; j++)
        {
            if (g[i][j] == PION_A)
            {
                if (j == NBCOL-1)
                {
                    printf("| %s |", RED);
                }
                else 
                {
                    printf("| %s ", RED);
                }
            }
            else if (g[i][j] == PION_B)
            {
                if (j == NBCOL-1)
                {
                    printf("| %s |", YELLOW);
                }
                else 
                {
                    printf("| %s ", YELLOW);
                }
            }
            else 
            {
                if (j == NBCOL-1)
                {
                    printf("|   |");
                }
                else 
                {
                    printf("|   ");
                }
            }
        }
        printf("\n");
        if (i < NBLIG-1)
        {
            printf("|---|---|---|---|---|---|---|\n");
        }
        
        
    }
    printf("'---'---'---'---'---'---'---'\n");
}

bool grillePleine(Grille g){
    int i,j;
    bool resultat;
    resultat = true;
    for (i=0;i<NBLIG;i++){
        for(j=0;j<NBCOL;j++){
            if (g[i][j]== VIDE){
                resultat = false;
            }
        }
    }
    return resultat;
}

void jouer(Grille g, char pion, int *ligne, int *colonne, bool *rageQuit){
    do{
        *colonne = choisirColonne(g,pion,*colonne, rageQuit);
        if(*rageQuit != true){
            *ligne = trouveLigne(g,*colonne);
        }
        
    }while (*ligne == -1 && *rageQuit != true);    
    if(*rageQuit != true){
        g[*ligne][*colonne] = pion;
    }
}

int choisirColonne(Grille g, char pion, int colonne, bool *rageQuit){
    char x;
    do
    {
        printf("\n");
        afficher(g,pion,colonne);
        printf("Entrez une action : ");
        scanf("%c",&x);

        if (x == 'q' || x == 'Q'){
            if (colonne > 0 ){
                colonne = colonne - 1;
            }
        }
        else if (x == 'd' || x == 'D'){
            if (colonne < 6){
                colonne = colonne + 1;
            }
        }
        else if (x == 'h' || x == 'H'){
            rules(); 
        }
        else if(x == 'r' || x == 'R'){
            *rageQuit = true; 
        }
    } while (x!=VIDE && x!='S' && x!='s' && *rageQuit != true);
    return colonne;
}

int trouveLigne(Grille g, int colonne){
    int i;
    i=0;
    int resultat = -1;
    while((g[i][colonne] == VIDE)&&(i<NBLIG)){
        i++;
    }

    if(g[5][colonne] == VIDE){
        resultat = 5;
    }
    else {
        resultat = i-1;
    }

    return resultat;
     
}

bool estVainqueurHoriz(Grille tab, int ligne, int colonne){
    char pion;
    int compteur;
    bool resultat;
    int colonneSuivante;
    pion = tab[ligne][colonne];
    resultat = false;
    compteur = 1;

    colonneSuivante = colonne +1 ;
    while(compteur<4 && tab[ligne][colonneSuivante] == pion && colonneSuivante<NBCOL){
        compteur = compteur +1;
        colonneSuivante = colonneSuivante +1;
    }

    colonneSuivante = colonne -1 ;
    while(compteur<4 && tab[ligne][colonneSuivante] == pion && colonneSuivante>=0){
        compteur = compteur + 1;
        colonneSuivante = colonneSuivante - 1;
    }


    if(compteur>=4){
        resultat = true;
    }

    return resultat;
}

bool estVainqueurVertic(Grille tab, int ligne, int colonne){
    char pion;
    int ligneSuivante,compteur;
    bool resultat;
    pion = tab[ligne][colonne];
    resultat = false;
    compteur = 1;
    ligneSuivante = ligne + 1;

    while(compteur<4 && tab[ligneSuivante][colonne] == pion && ligneSuivante<NBLIG){
            compteur = compteur +1;
            ligneSuivante = ligneSuivante +1;
        }

    if (compteur>=4){
        resultat = true;
    }
    
    return resultat;

}

bool estVainqueurGD(Grille tab, int ligne, int colonne){
    char pion;
    int compteur;
    bool resultat;
    int ligneSuiv,colonneSuiv;
    pion = tab[ligne][colonne];
    resultat = false;
    compteur = 1;
    ligneSuiv = ligne +1;
    colonneSuiv = colonne +1;

    while(compteur<4 && tab[ligneSuiv][colonneSuiv]==pion && ligneSuiv<NBLIG && colonneSuiv<NBCOL){
        compteur = compteur + 1;
        ligneSuiv = ligneSuiv + 1;
        colonneSuiv = colonneSuiv +1;
    }

    ligneSuiv = ligne - 1;
    colonneSuiv = colonne - 1;
    while (compteur<4 && tab[ligneSuiv][colonneSuiv]==pion && ligneSuiv>=0 && colonneSuiv>=0){
        compteur = compteur + 1;
        ligneSuiv = ligneSuiv - 1;
        colonneSuiv = colonneSuiv - 1;
    }
    if(compteur>=4){
        resultat = true;
    }
    return resultat;

}

bool estVainqueurDG(Grille tab, int ligne, int colonne){
    char pion;
    int compteur;
    bool resultat;
    int ligneSuiv,colonneSuiv;
    pion = tab[ligne][colonne];
    resultat = false;
    compteur = 1;
    ligneSuiv = ligne + 1;
    colonneSuiv = colonne - 1;
    while (compteur<4 && tab[ligneSuiv][colonneSuiv]==pion && ligneSuiv<NBLIG && colonneSuiv>=0){
        compteur = compteur + 1;
        ligneSuiv = ligneSuiv + 1;
        colonneSuiv = colonneSuiv - 1;
    }

    ligneSuiv = ligne - 1;
    colonneSuiv = colonne + 1;
    while(compteur<4 && tab[ligneSuiv][colonneSuiv]==pion && ligneSuiv>=0 && colonneSuiv<NBCOL){
        compteur = compteur + 1;   
        ligneSuiv = ligneSuiv - 1;
        colonneSuiv = colonneSuiv + 1; 
    }
    if(compteur>=4){
        resultat = true;
    }
    return resultat;
}

bool estVainqueur(Grille tab, int ligne, int colonne){
    bool res;
    res = false;
    if(estVainqueurHoriz(tab,ligne, colonne)||estVainqueurVertic(tab,ligne,colonne)||estVainqueurGD(tab,ligne, colonne)|| estVainqueurDG(tab,ligne,colonne)){
        res = true;
    }
    return res;
}

void finDePartie( char pion, bool *recommencer){
    char reponse;
    char del; 
    scanf("%c", &del);
    if(pion==PION_A){
        printf("┌───────────────────────────────────────────────────────┐\n");
        printf("│                                                       │\n");
        printf("|          Le gagnant est le joueur au pion %s !         │\n",RED);
        printf("│                                                       │\n");
        printf("│             Appuyez sur r pour recommencer            │\n");
        printf("│                                                       │\n");
        printf("│          Pour quitter faites comme pour un man        │\n");
        printf("│                                                       │\n");
        printf("└───────────────────────────────────────────────────────┘\n");
        printf("    --> "); 
        scanf("%c", &reponse); 
        if (reponse == 'r' || reponse == 'R')
        {
            *recommencer = true;
        }
    }
    else if(pion==PION_B){
        printf("┌───────────────────────────────────────────────────────┐\n");
        printf("│                                                       │\n");
        printf("|          Le gagnant est le joueur au pion %s !         │\n",YELLOW);
        printf("│                                                       │\n");
        printf("│             Appuyez sur r pour recommencer            │\n");
        printf("│                                                       │\n");
        printf("│          Pour quitter faites comme pour un man        │\n");
        printf("│                                                       │\n");
        printf("└───────────────────────────────────────────────────────┘\n");
        printf("    --> "); 
        scanf("%c", &reponse); 
        if (reponse == 'r' || reponse == 'R')
        {
            *recommencer = true;
        }
    }
    else{
        printf("┌───────────────────────────────────────────────────────┐\n");
        printf("│                                                       │\n");
        printf("|                      Match Nul !                      │\n");
        printf("│                                                       │\n");
        printf("│             Appuyez sur r pour recommencer            │\n");
        printf("│                                                       │\n");
        printf("│          Pour quitter faites comme pour un man        │\n");
        printf("│                                                       │\n");
        printf("└───────────────────────────────────────────────────────┘\n");
        printf("    --> "); 
        scanf("%c", &reponse); 
        if (reponse == 'r' || reponse == 'R')
        {
            *recommencer = true;
        }
    }
}

void rules(){
    system("clear"); 

    printf("\n\n"); 
    printf("┌──────────────────────────────────────────────────────────┐\n");
    printf("│   Les commandes pour jouer sont les suivantes :          │\n");
    printf("│                                                          │\n");
    printf("│              q -> deplacemement du pion vers la gauche   │\n");
    printf("│                                                          │\n");
    printf("│              d -> deplacement du pion vers la droite     │\n");
    printf("│                                                          │\n");
    printf("│       s/Espace -> chute du pion                          │\n");
    printf("│                                                          │\n");
    printf("│              h -> pour revoir les commandes              │\n");
    printf("│                                                          │\n");
    printf("│              r -> quitte la partie et la recommence      │\n");
    printf("│                                                          │\n");
    printf("└──────────────────────────────────────────────────────────┘\n");

    sleep(5); 

    system("clear"); 
}

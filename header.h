# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <assert.h>

 typedef unsigned int Uint;

/* Structure d'une fonction */

 typedef struct fct {
  char * name;
  int id; /* Numero de la fonction */
  struct fct ** called ; /* Tableau de pointeurs vers les fonctions appelées */
  struct fct ** origin; /* Tableau de pointeurs vers les fonctions appelantes */
} fct_t;


/* Fonction qui lit le fichier le fichier et le place dans le tableau final */

extern char * read (char * src, char * final, Uint * finDeChaine);

/* Fonction qui indique s'il existe un chemin ou non entre deux fonctions */

extern int chemin (int dep, int arr,fct_t * fct, int nb_fct );

/* Fonction qui indique si une fonction est récursive ou non */

extern int recursif (int dep, fct_t * fct, int nb_fct);

/* Fonction qui trouve et place les ID des fonctions dans un tableau */

extern int * itineraire (int * tab, int nel, int p, int dep, int arr, fct_t * fct,int nb_fct);

/* Affiche le tableau de la fonction "itineraire" */

extern void aff_tab_iti (int * tab, fct_t * fct);

/* Saute les espaces en arrière */

extern void back_space_jump (char * tab, int * i);

/* Repère et récupère un nom de fonction dans le fichier et le place dans la structure */

extern int recup_nom (int cases,char * tab,int nb,fct_t *fct );

/* Fonction qui filtre les noms indésirables */

extern int diff (char * ch);

/* Fonction qui vérifie si les fonctions ont déjà été préalablement créées */

extern int done (char * name, int nb,fct_t *fct);

/* Fonction qui récupère les appels de fonctions */

extern int recup_appele_fct (int cases, char * tab, int nb,fct_t *fct );

/* Affiche un tableau de fct_t avec leurs appels et origines */
	
extern void aff_fct (fct_t * tab, int n);

/* Fonction qui scanne le tableau final afin d'y repèrer les déclarations de fonctions et leur(s) appel(s) */
	 
extern fct_t * recherche (char * tab, fct_t * fct , int * taille_fct, int * nb_fct);
  
/* Donne les fonctions non-connexes au Main, s'il y en a */

extern void main_connexe (fct_t * fct, int nb_fct, int * tab,int id);

/* Affiche les fonctions non-connexes s'il y en a */

extern void aff_tab_con (int * tab, fct_t * fct,int nb_fct,int id);

/* Verifie les sources du Makefile */

extern int check_src (char * ch);

extern int check_source (char * ch);

extern int check_sources (char * ch);

extern int verif_src (char * ch); 

/* Compte les espaces de la ligne SRC ( NB de Fonction(s) ) */

extern Uint count_space (char * ch, Uint j);

/* Verifie si une fonction fini bien par .c */

extern int verif_pointc (char * ch); 

/* Decode un Makefile et récupère ses sources */

extern char ** decode (char * fichier, char ** end);

/* Permet d'afficher les fonctions et leurs id */

extern void aff_fct_id (fct_t * fct, int n);


/* Choix des coordonnées */

void choix (int * dep, int * arr);

void choix2 (int * dep);

/* Permet d'afficher le resultat de chemin dans le main*/

void case_chemin (int dep, int arr,fct_t * fct, int nb_fct);

/* Fonction pour afficher le résultat de recursif dans le main */

void case_recursive (int dep, fct_t * fct, int nb_fct);

/* Fonction qui affiche les fonctions qui ne sont appelées par personne */

int non_appele (fct_t * fct, int nb_fct);
void case_non_appele (fct_t * fct, int nb_fct);
void print_non_appele (fct_t * fct, int nb_fct);
void genere_dot(fct_t *fct, int nb_fct);
void rez ( int * str, int taille);



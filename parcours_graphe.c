# include "header.h"


/* Fonction qui indique s'il existe un chemin ou non entre deux fonctions */

int chemin (int dep, int arr,fct_t * fct, int nb_fct ) {

  int i;

  if (dep-1 < 0 || arr-1 < 0 || dep-1 > nb_fct || arr-1 > nb_fct){
     fprintf(stderr,"\nIl n'y a pas de fonction assosiée a cette ID\n\n");
    return -1;
  }

  if (dep == arr)
    return 1;


  for (i=0 ; fct[dep-1].called[i] != NULL ; i++) {

    if (fct[dep-1].id == fct[dep-1].called[i]->id)
      continue;

    if (chemin (fct[dep-1].called[i]->id,arr,fct,nb_fct)==1)
      return 1;

  }

  return 0;

}

/* Fonction qui indique si une fonction est récursive ou non */

int recursif (int dep, fct_t * fct, int nb_fct) {

  int i;


  if (dep-1 < 0 || dep-1 > nb_fct) {
    return -1;
  }

  for (i=0 ; fct[dep-1].called[i] != NULL ; i++) {

    if (fct[dep-1].id == fct[dep-1].called[i]->id)
      return 1; 

  }

  return 0;

}

/* Fonction qui trouve et place les ID des fonctions dans un tableau */

int * itineraire (int * tab, int nel, int p, int dep, int arr, fct_t * fct,int nb_fct) {

  int i;


  if (dep-1 < 0 || arr-1 < 0 || dep-1 > nb_fct || arr-1 > nb_fct){
    fprintf(stderr,"\nIl n'y a pas de fonction assosiée a cette ID\n\n");
    return NULL;
  }

  if (tab == NULL) {
    tab = (int *) malloc (nel * sizeof (int));
  }

  else if (nel <= p) {
    nel *= 2;
    tab = realloc (tab, sizeof (int) * nel);
  }

  if (dep == arr) {
    tab[p] = dep;
    tab[p+1] = -1;
    return tab;
  }


  for (i=0 ; fct[dep-1].called[i] != NULL ; i++) {

    if (fct[dep-1].id == fct[dep-1].called[i]->id)
      continue;

    if (itineraire (tab, nel, p+1, fct[dep-1].called[i]->id, arr,fct, nb_fct) != NULL) {
      tab[p] = dep;
      return tab;
    
    }

  }

  return NULL;
 
}


/* Affiche le tableau de la fonction "itineraire" */

void aff_tab_iti (int * tab, fct_t * fct) {

  int i;

  if (tab==NULL) {
    fprintf(stderr,"\nIl n'y a pas de chemin\n\n");
    return;
  }

  for (i= 0 ; tab[i] != -1 ; i++)
    printf("%s\n",fct[ tab[i] -1 ].name);

  printf("\n");

}


/* Donne les fonctions non-connexes a la fonction correspondant l'ID, s'il y en a */

void main_connexe (fct_t * fct, int nb_fct, int * tab,int id) {

  int i;

  for (i = 0 ; fct[id-1].called[i] != NULL ; i++) {
 
    if (fct[id-1].id == fct[id-1].called[i]->id)
      continue;  
    main_connexe(fct,nb_fct,tab,fct[id-1].called[i]->id);
      
  }

  tab[id - 1] = 1;
 

}

/* Affiche les fonctions non-connexes s'il y en a */

void aff_tab_con (int * tab, fct_t * fct,int nb_fct,int id) {
  
  int i,test = 0;

  printf("\nCes fonctions ne sont pas dans le sous Graphe de %s :\n\n",fct[id-1].name);
  for (i= 0 ; i< nb_fct ; i++){
    if(tab[i] != 1){
         printf("%s\n",fct[ i ].name);
      test = 1;
    }
  }

  if (test == 0) {
    printf("\nLe graphe est entièrement connexe\n\n");
    return;
  }

  printf("\n");

}

/* Affiche les ID des fonctions */

void aff_fct_id (fct_t * fct, int n) {

  int i;
  printf("\n");
  for (i=0 ; i<n ; i++)
    printf("%35s  (%d)\n",fct[i].name,fct[i].id);
		
}
		
		

/* Fonction pour choisir les ID lors de la demande du programme */
		
void choix (int * dep, int * arr) {

  char tmp1 [5];
  char tmp2 [5];
	
  printf("\nVeuillez choisir un ID de fonction de départ : ");
  *dep = atoi(fgets(tmp1, 5, stdin));
  printf("\nVeuillez choisir un ID de fonction d'arrivé : ");
  *arr = atoi(fgets(tmp2, 5, stdin));
  printf("\n\n");
	
}

		
void choix2 (int * dep) {

  char tmp1 [5];
	
  printf("\nVeuillez choisir un ID de fonction : ");
  *dep = atoi(fgets(tmp1, 5, stdin));
  printf("\n\n");
	
}
	
/* Fonction pour afficher le resultat de chemin dans le main */
	
void case_chemin (int dep, int arr,fct_t * fct, int nb_fct) {

  int d = chemin(dep,arr,fct,nb_fct);

  if (d == 1) {
    printf("\nIl existe un chemin entre %s et %s\n\n",fct[dep-1].name,fct[arr-1].name);
    return;
  }
		
  if (d == 0) {
    printf("\nIl n'y a pas de chemin entre %s et %s\n\n",fct[dep-1].name,fct[arr-1].name);
    return;
  }
		
  if (d == -1) {
    printf("\nLes IDs ne correspondent à aucune fonction !\n\n");
    return;
  }

}

			

/* Fonction pour afficher le resultat de recursif dans le main */


void case_recursive (int dep, fct_t * fct, int nb_fct) {
	
  if (recursif(dep,fct,nb_fct) == 1) {
    printf("\n%s est récursive\n",fct[dep-1].name);
    return;
  }
			
  if (recursif(dep,fct,nb_fct) == 0) {
    printf("\n%s n'est pas récursive\n",fct[dep-1].name);
    return;
  }
  			
  fprintf(stderr,"\nIl n'y a pas de fonction assosiée a cette ID\n\n");
		
}		
		
int non_appele (fct_t * fct, int nb_fct) {

  int i,acc=0;
	
  for (i=0 ; i<nb_fct-1 ; i++) {
	
    if (fct[i].origin[0] == NULL  || (fct[i].id == fct[i].origin[0]->id && fct[i].origin[1] == NULL ) ) {
      acc += 1;
    }
			
  }
  return acc;
	
}

		
void print_non_appele (fct_t * fct, int nb_fct) {

  int i;
	
  for (i=0 ; i<nb_fct-1 ; i++) {
	
    if (fct[i].origin[0] == NULL  || (fct[i].id == fct[i].origin[0]->id && fct[i].origin[1] == NULL ) ) {
      printf("%s\n",fct[i].name);
    }
			
  }
	
}


void case_non_appele (fct_t * fct, int nb_fct) {

  int acc = non_appele(fct,nb_fct);

  if (acc == 0) {
    printf("\nToutes les fonctions sont appelées au moins une fois\n");
  }
	
  else {
    printf("\nIl y a %d fonctions non appelées\n",acc);
    print_non_appele(fct,nb_fct);
  }
	

}
	
			
			
void genere_dot(fct_t *fct, int nb_fct){

  int i,j = 0;
 
  // Pour compiler dot -Tps -o tr.ps tr.dot
  FILE * in;
  in = fopen("graph.dot","w");
  assert(in);
  fprintf(in,"\n\ndigraph G {\n\n");
  for (i = 0; i < nb_fct ; i++, j= 0 ){

    while(fct[i].called[j] != NULL){
      fprintf(in,"\t%s  ->  %s\n",fct[i].name, fct[i].called[j]->name );
    
      j += 1;
    }
  }
 
  fprintf(in,"\n}\n\n");
fclose(in);

in = fopen("graph.dot","r");
 char command[100];
 
   strcpy(command, "dot -Tpng graph.dot > graph1.png");
   system(command);
  fclose(in);
}	
		
			
void rez ( int * str, int taille){
 
  int i = 0;
  
 for (i = 0; i < taille ; i++ ){
   str[i] = 0;
 }

}

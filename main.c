# include "header.h"

int main (int argc, char ** argv) {


  if (argc < 2) {
    fprintf(stderr, "Usage : freydi nom_du_fichier\n");
    exit(0);
  }

  if (fopen(argv[1],"r") == NULL) {
    fprintf(stderr, "Erreur : Votre fichier n'existe pas\n");
    exit(0);
  }
  
  


 
  /* Taille de départ tableau contenant le fichier */
  Uint taille = 1024;

  /* Indice de la fin de chaine du tableau contenant le fichier */
  Uint finDeChaine = 0;

  /* Déclaration et allocation memoire du tableau Final */
 
  char * final;
  final = (char *) malloc (taille * sizeof(char));
  assert(final); 
 
 
  /* Déclaration du tableau qui accueillera la fonction itineraire */
  int * tab = NULL;
  
  /* Déclaration du tableau qui accueillera la fonction main_connexe */
  int connexe [100];
  
  /* Déclaration de l'id de la fonction de depart et d'arrivé */
  int dep ,arr ;
  
  /* Déclaration du tableau de fct_t */
  fct_t * fct = NULL;
  /* Taille du tableau de fct_t */
  int taille_fct = 200;
  
  /* Variable du nombre de fonctions dans le programme */
  int nb_fct = 0;

    int k;
    char ** tmp2 = NULL ;
  if (strcmp(argv[1],"Makefile") == 0 || strcmp(argv[1],"makefile") == 0) {

	
    tmp2 = decode(argv[1],tmp2);
	
    for (k=0 ; tmp2[k] != NULL ; k++) {
      final = read(tmp2[k],final,&finDeChaine);
    }
		
		
  } 

  else {
  
    /* Lecture du fichier .c et "remplissagge" du tableau final */

    final = read(argv[1],final,&finDeChaine);
  
  }

  fct = recherche (final,fct,&taille_fct, &nb_fct);

  /* Interface du Menu */


  int entered;
  char tmp[3];
  int nb = 50;
  printf("--------------------------------------------------------------------------\n") ;
  printf("|                                                                        |\n") ; 
  printf("|                                                                        |\n") ;
  printf("|                      Analyseur de programmes C                         |\n") ;
  printf("|                                                                        |\n") ;
  printf("|                                                                        |\n") ;
  printf("--------------------------------------------------------------------------\n") ;

  int quit = 1;

  while (quit) {

    printf("\n") ;
    printf("\t\t\t  Que voulez-vous faire ?\n\n");
    printf("\t1 = Afficher le programme\n");
    printf("\t2 = Afficher les fonctions, leurs appels et leurs origines\n");
    printf("\t3 = Afficher les IDs des fonctions\n");
    printf("\t4 = Voir s'il existe une chemin entre deux fonctions\n");
    printf("\t5 = Afficher l'itinéraire du chemin entre deux fonctions\n");
    printf("\t6 = Voir les fonctions non-presente dans le sous-graphe d'une fonction\n");
    printf("\t7 = Voir si une fonction est récursive\n");
    printf("\t8 = Afficher la liste des fonctions jamais appelées\n");
    printf("\t9 = Génere le code pour GraphViz\n");

    printf("\n\t\t\t10 = Quitter le programme\n\n");



    entered = atoi(fgets(tmp, 3, stdin));

    if (entered < 1 || entered > 10) {
      fprintf (stderr, "\nERREUR : Veuillez rentrez un des chiffre indiqué dans le menu\n\n");
    }


    switch (entered) {

    case 1 : 
      printf("%s\n",final); 
      break;
    case 2 :
      aff_fct(fct,nb_fct);
      break;
    case 3 :
      aff_fct_id(fct,nb_fct);
      break;
    case 4 :
      aff_fct_id(fct,nb_fct);
      choix(&dep,&arr);
      case_chemin (dep,arr,fct,nb_fct);
      break;
    case 5 :
      aff_fct_id(fct,nb_fct);
      choix(&dep,&arr);
      tab = itineraire(tab,nb,0,dep,arr,fct,nb_fct);
      aff_tab_iti(tab,fct);
      break; 
    case 6 :
      aff_fct_id(fct,nb_fct);
      choix2(&dep);
      main_connexe(fct,nb_fct,connexe,dep);
      aff_tab_con(connexe,fct,nb_fct,dep);
      rez(connexe,50);
      break;
    case 7 :
      aff_fct_id(fct,nb_fct); choix2(&dep);
      case_recursive (dep,fct,nb_fct);
      break;
    case 8 :
      case_non_appele(fct,nb_fct);
      break;
    case 9 :
      genere_dot(fct,nb_fct);
      break;
    case 10 :
      quit = 0;
    }
   
  
  
  
  }
  return 0;

}


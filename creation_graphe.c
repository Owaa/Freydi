# include "header.h"


void back_space_jump (char * tab, int * i) {

   while(isspace(tab[*i]))
    *i -= 1;

}
      
/* Repère et récupère un nom de fonction dans le fichier et le place dans la structure */

int recup_nom (int cases,char * tab,int nb,fct_t *fct )      {

  char temp[50];
  int i,acc = 0;

  i = cases-1;    /* -1 pour dépasser '{' */

  temp[0] = '\0';

  back_space_jump(tab,&i);

  /* Si structure */
  if(tab[i] != ')')
    return 0;

  while(tab[i] != '(')
    i -= 1;

  i -= 1; /* -1 pour dépasser '(' */

 back_space_jump(tab,&i);
  
  while(!isspace(tab[i]))
    i -= 1;  
  
  i +=1 ; /* +1 pour être sur le premier caractère */


  /* Procèdure de récuperation du nom de la fonction */

  while (!isspace(tab[i]) && tab[i] != '(' )
    temp[acc++] = tab[i++] ;
  
  temp[acc] = '\0';

  fct[nb].name = strdup(temp);
  fct[nb].id = nb+1;
 
  return 1;

}


/* Fonction qui filtre les noms indésirables */

int diff (char * ch) {

  if (strcmp(ch,"if") == 0)
    return 0;

  if (strcmp(ch,"while") == 0)
    return 0;

  if (strcmp(ch,"for") == 0)
    return 0;

  if (strcmp(ch,"return") == 0)
    return 0;

  return 1;

}


/* Fonction qui vérifie si les fonctions ont déjà été préalablement créées */

int done (char * name, int nb,fct_t *fct) {

  int i;

  for (i=0 ; i<nb+2 ; i++) {

    if (strcmp (name,fct[i].name) == 0) 
      return i;
    
  }

  return -1;

}

      


/* Fonction qui récupère les appels de fonctions */

int recup_appele_fct (int cases, char * tab, int nb,fct_t *fct ) {

  int acc_acolade = 1, acc_called = 0;
  int i= cases + 1, back, j, taille_called = 15;
  char tmp [25];
  int k;
 
  fct[nb].called = (fct_t **) malloc (taille_called * sizeof (fct_t *)); // A MODIFIER
  fct[nb].origin = (fct_t **) malloc (30 * sizeof (fct_t *)); // A MODIFIER


  fct[nb].called[0] = NULL;
  fct[nb].origin[0] = NULL;

  for (; tab[i] != '\0' ;i++) {

  
    if ( acc_acolade == 0) {
      fct[nb].called[acc_called] = NULL;
      return i;
    }
      
    // sauter les commentaires
    if ( tab[i] == '/' && tab[i+1] == '/'){
      while(tab[i] != '\n')
	i += 1;

    }
    /* Sauter les commentaires */
    else if ( tab[i] == '/' && tab[i+1] == '*'){
   
      while( ! (tab[i] == '*' &&  tab[i+1] == '/' ))
	i += 1;
    
    }

    if(tab[i] == '}')
      acc_acolade -= 1;

    else if(tab[i] == '{')      
      acc_acolade += 1;

    else if (tab[i] == '(') {

      j = 0;

      back = i-1;

      while (isspace(tab[back]))
	back -= 1;
     

      if (isalpha(tab[back]) || isdigit(tab[back]) || tab[back] == '_') {
	
	while (isalpha(tab[back]) || isdigit(tab[back]) || tab[back] == '_')
	  back -= 1;

	back += 1;

	while (isalpha(tab[back]) || isdigit(tab[back]) || tab[back] == '_')
	  tmp[j++] = tab[back++];

	tmp[j] = '\0';

	int tmp_done;

	if (diff(tmp) == 1 && ((tmp_done = done(tmp,nb-1,fct)) != -1) ) {
	
	  if(acc_called >= taille_called ){
	
	
	 
	    taille_called *= 2 ;
	    fct[nb].called = (fct_t **) realloc ( fct[nb].called  , taille_called  * sizeof (fct_t *));
	    assert(  fct[nb].called );

	  }

	  fct[nb].called[acc_called] = &fct[tmp_done];
	       

	  for (k=0 ; fct[tmp_done].origin[k] != NULL ; k++)
	    ;

	  fct[tmp_done].origin[k] = &fct[nb];
	
	  fct[tmp_done].origin[k+1] = NULL;

	  acc_called += 1;

	}
      }
    }
      
  }

  return cases;
}
      

/* Affiche un tableau de fct_t avec leurs appels et origines */
	
void aff_fct (fct_t * tab, int n) {

  int i,j=0;

  for (i=0 ; i<n ; i++) {
     
    printf("\nfct = %s (%d)\n",tab[i].name, tab[i].id);
    
    for (j=0 ; tab[i].called[j] != NULL ; j++) {
      printf("\tcalled = %s (%d)\n", tab[i].called[j]->name,tab[i].called[j]->id);
    }

    for (j=0 ; tab[i].origin[j] != NULL ; j++) {
      printf("\torigin = %s (%d) \n", tab[i].origin[j]->name,tab[i].origin[j]->id);
    }
  }

  printf("\n");

}

/* Fonction qui scanne le tableau final afin d'y repèrer les déclarations de fonctions et leur(s) appel(s) */
	 
  fct_t * recherche (char * tab, fct_t * fct , int * taille_fct, int * nb_fct) {
  
    int i;
  int acc_acolade = 0;


  if (fct == NULL) {
    fct = malloc (*taille_fct * sizeof(*fct));
    assert(fct);
  }

  for ( i = 0; tab[i] != '\0' ;i++) {
    // sauter les commentaires
    if ( tab[i] == '/' && tab[i+1] == '/'){
      while(tab[i] != '\n')
	i += 1;

    }
    /* Sauter les commentaires */
    else if ( tab[i] == '/' && tab[i+1] == '*'){  
      while( ! (tab[i] == '*' &&  tab[i+1] == '/' ))
	i += 1;
    }

    else if(tab[i] == '}')
      acc_acolade -= 1;

    else if(tab[i] == '{'){      
      acc_acolade += 1;

      if (acc_acolade == 1){
	// Si besoin realloc du tableau
	if (*taille_fct <= *nb_fct) {
	  *taille_fct *= 2;
	  fct = realloc (fct, *taille_fct * sizeof (*fct));
	  assert(fct);
	  
	}
	// Si on a bien recupere un nom de fct alors go recup tous ces appels
	if( recup_nom(i, tab, *nb_fct,fct) == 1){
	
	
	  i = recup_appele_fct(i, tab, *nb_fct ,fct);
	  *nb_fct += 1;
	  acc_acolade = 0;
	 
	}		
      }
    }    
  }
  printf("Nombre de fonction lu %d   %d\n",*nb_fct, *taille_fct);
 
  return fct;
}


# include "header.h"

 /* Taille de départ tableau contenant le fichier */
 Uint taille = 1024;

/* Fonction qui lit le fichier le fichier et le place dans le tableau final */

char * read (char * src, char * final, Uint * finDeChaine) {

  FILE * in;

  in = fopen(src,"r");
  assert(in);

  int c;

  for (c = fgetc(in) ; c!=EOF ; c=fgetc(in),(*finDeChaine)++) {

    if (*finDeChaine >= taille) {     
      taille*=2;
      final = realloc(final,taille * sizeof (*final));
      assert(final);        
    }

    final[*finDeChaine] = c;
   
  }

  final[*finDeChaine] = '\0';
  fclose(in);

  return final;
}



int check_src (char * ch) {

  int i;

  for (i=0 ; ch[i]!='\0' ; i++) {

    if (ch[i] == 's'|| ch[i] == 'S') 
      if (ch[i+1] == 'r'|| ch[i+1] == 'R')
	if (ch[i+2] == 'c'|| ch[i+2] == 'C') {
	  i += 3;
	  while (isspace(ch[i]))
	    i+=1;
	  if (ch[i] == '=')
	    return 1;
	      }
  
  }

  return 0;
}

int check_source (char * ch) {

  int i;

  for (i=0 ; ch[i]!='\0' ; i++) {

    if (ch[i] == 's'|| ch[i] == 'S') 
      if (ch[i+1] == 'o'|| ch[i+1] == 'O')
	if (ch[i+2] == 'u'|| ch[i+2] == 'U')
	  if (ch[i+3] == 'r'|| ch[i+3] == 'R')
	    if (ch[i+4] == 'c'|| ch[i+4] == 'C')
	      if (ch[i+5] == 'e'|| ch[i+5] == 'E') {
		i += 6;
		while (isspace(ch[i]))
		  i+=1;
		if (ch[i] == '=')
		  return 1;
	      }
  
  }

  return 0;
}

int check_sources (char * ch) {

  int i;

  for (i=0 ; ch[i]!='\0' ; i++) {

    if (ch[i] == 's'|| ch[i] == 'S') 
      if (ch[i+1] == 'o'|| ch[i+1] == 'O')
	if (ch[i+2] == 'u'|| ch[i+2] == 'U')
	  if (ch[i+3] == 'r'|| ch[i+3] == 'R')
	    if (ch[i+4] == 'c'|| ch[i+4] == 'C')
	      if (ch[i+5] == 'e'|| ch[i+5] == 'E')
		if (ch[i+6] == 's'|| ch[i+6] == 'S') {
		  i += 7;
		  while (isspace(ch[i]))
		    i+=1;
		  if (ch[i] == '=')
		    return 1;
		}
  
  }

  return 0;
}


int verif_src (char * ch) {

  if (check_src (ch) == 1)
    return 1;

 if (check_source (ch) == 1)
    return 1;

 if (check_sources (ch) == 1)
    return 1;

 return 0;

}

Uint count_space (char * ch, Uint j) {

  Uint i;
  Uint acc = 0;

  for (i=j ; ch[i]!='\0' ; i++) {
    
    if (isspace(ch[i]))
	acc += 1;

  }
  return acc;

}


int verif_pointc (char * ch) {

  Uint acc = strlen(ch);

  if (ch[acc-2] == '.') { 
    if (ch[acc-1] == 'c') {  
      return 1;
    }
  }

  return 0;

}





char ** decode (char * fichier, char ** end) {

  FILE * in;

  in = fopen(fichier,"r");
  assert(in);

  char * tmp;
  char * final = NULL;
  
  tmp = (char*) malloc (taille * sizeof (char));



  while (!feof(in)) {

    fgets(tmp,taille,in);

    if (verif_src(tmp) == 1) {
      final = tmp;
      break;
    }
  }

  if (!final) {
    fprintf(stderr,"ERREUR : Votre Makefile ne possède pas de SOURCES\n");
    exit(EXIT_FAILURE);
  }

  Uint i = 0;
  Uint j,k;
  Uint nbspace;
  char file [100];
  char ** tabfichier;
  tabfichier = (char **) malloc (taille * sizeof(char *));
  assert(tabfichier);

  while (final[i] != '=')
    i += 1;

  while (!isalpha(final[i]))
    i += 1;

  
  nbspace = count_space(final,i);

  end = malloc (nbspace * sizeof (*end));
  assert(end);

 for (j=0 ; j<nbspace ; j++) {

    k = 0;

    while ( !isspace(final[i]) ) {
      file[k] = final[i];
      k += 1;
      i += 1;
    }
    
    file[k] = '\0';

    
    if (verif_pointc(file) == 1) {

      tabfichier[j] = strdup(file);
 
    }  else {
      fprintf(stderr,"ERREUR : Une de vos sources n'a pas de .c\n");
      exit(EXIT_FAILURE);
    }

    
    while (!isalpha(final[i])) {
      i += 1;
    }
  
 }
 tabfichier[j]='\0';
 fclose(in);
 return tabfichier;

}


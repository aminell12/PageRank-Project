#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define N 1200000
#define V 10000

typedef struct sommet{
  int val;
  char * nom_page;
  struct sommet * suiv;
} Sommet;

typedef struct{
  Sommet * premier;
}liste;

/*------------------------------------------------*/
//initialise la structure sommet (carré)
Sommet * creer_sommet(){
  Sommet * s = malloc(5*sizeof(Sommet));
  s->nom_page = malloc(200*sizeof(char));
  if (s == NULL) return NULL;
  return s;
}
/*------------------------------------------------*/
// initialise la structure liste (carré)
liste * creer_liste(){
  liste * l = malloc(5*sizeof(liste)); // probleme de taille si on met juste sizeof il faut mettre plus grand qund il ya de grandes matrices
  if (l == NULL) return NULL;
  l->premier=NULL;
  return l;
}
/*------------------------------------------------*/
//fonction qui supprime doublon (carré)
void supp_doublons_liste_chainee(liste * adj[], int i){
  Sommet * s = adj[i]->premier;
  while(s != NULL && s->suiv != NULL ){
    Sommet * r = s;
    while(r != NULL && r->suiv != NULL ){
      if(s->val == r->suiv->val){
        Sommet * sauv = r->suiv;
        r->suiv = sauv->suiv;
        free(sauv);
      }
      r=r->suiv;
    }
    s = s->suiv;
  }
  return;
}
/*------------------------------------------------*/
//compare deux chaines de caractere (carré)
int comparechaines(char * ch1, char * ch2){
  int i = 0;
  while((ch1[i] != '\0' ) && (ch1[i] == ch2[i])){
    i++;
  }
  return ch1[i]-ch2[i];
}
/*------------------------------------------------*/
//fonction pour creer le super noeud (carré)
void ajout_super_noeud(liste * adj[], int c){
  //prend la première case du tableau adj et y insère l'adresse du premier élément de la liste chainée du super noeud
  liste * l = creer_liste();
  adj[0] = l;
  Sommet * s = creer_sommet();
  s->val = 1;
  s->suiv = NULL;
  l->premier = s;
  //met les liens du super noeud vers toutes les autres pages
  for (int i = 2; i < c; i++){
    Sommet * z = creer_sommet();
    z->val = i;
    z->suiv = NULL;
    s->suiv = z;
    s = z;
  }
  return;
}
/*------------------------------------------------*/
//fonction qui ajoute la liste chainee dans chaque case d'adj (carré)
void ajout_liste_chainee (liste * adj[], char * ligne,int i){
  //prend la case i du tableau adj et y insère l'adresse du premier élément de la liste chainée correspondant à la ligne i du fichier
  liste * l = creer_liste();
  adj[i] = l;
  Sommet * s = creer_sommet();
  s->val = 0;
  s->suiv = NULL;
  l->premier = s;

  //deux variables dont l'une (u) va permettre de parcourir la ligne pour reconnaître les valeurs de la matrice et l'autre (n) va permettre d'ajouter la
  int u = 0, n = 1;
  //parcourt toute la ligne du fichier (donc la matrice dans ce mode)
  while(ligne[u] != '\n'){
    if ( ligne[u] == '0'){
      //pour rajouter le lien entre une page et elle même
      if (n == i){
        Sommet * z = creer_sommet();
        z->val = n;
        z->suiv = NULL;
        s->suiv = z;
        s = z;
      }
      n++;
    }
    if (ligne[u] == '1'){
      //vérifie le cas où il y une 1 dans la diagonale => donc la page pointe vers elle même
      if (n == i){
        Sommet * z = creer_sommet();
        z->val = n;
        z->suiv = NULL;
        s->suiv = z;
        s = z;
      }
      else{
        Sommet * z = creer_sommet();
        z->val = n;
        z->suiv = NULL;
        s->suiv = z;
        s = z;
      }
      n++;
    }
    u++;
  }

  return;
}
/*-----------------------------------------------------------------------------*/
//permet d'ajouter une liste chainee dans chaque case d'adj pour wiki (carré)
void ajout_liste_chainee_wiki(liste * adj[], char * ligne, Sommet * pages[], int c, int i){
  //prend la case i du tableau adj et y insère l'adresse du premier élément de la liste chainée correspondant à la ligne i du fichier
  liste * l = creer_liste();
  adj[i] = l;
  Sommet * s = creer_sommet();
  char  * nom = malloc(N*sizeof(char));
  s->val = 0;
  s->suiv = NULL;
  l->premier = s;

  //prend la ligne i du fichier et initialise la page qui pointe vers elle même
  Sommet * p = creer_sommet();
  p->val = i;
  p->suiv = NULL;
  s->suiv = p;
  s = p;
  //saute la page de chaque ligne en la stockant dans name
  char * separateur = "|\n\0";
  nom = strtok(ligne, separateur);
  //boucle qui va récupérer tous les liens dans la ligne i du fichier et comparer avec le tableau de pages pour vérifier s'ils la page i possède un lien entrant vers ces derniers
  while (nom != NULL){
    nom = strtok(NULL, separateur);
    if((nom != NULL)){
      int h = 0;
      int ad = 0;
      while(h < c-1){
        if (comparechaines(nom,((pages[h])->nom_page)) == 0){
          if(h+1 != i){
            ad = (pages[h])->val;
          }
        }
        h++;
      }
      if (ad != 0){
        Sommet * z = creer_sommet();
        z->val = ad;
        z->suiv = NULL;
        s->suiv = z;
        s = z;
      }
    }
  }
  return;
}
/*-----------------------------------------------------------------------------*/
//permet d'afficher une liste chainée (carré)
void afficher_adj(liste * adj[], int c){
  printf("\nSuper-noeud: " );

  Sommet * a = creer_sommet();
  if (adj[0] == NULL) return;
  a = adj[0]->premier;
  while(a != NULL){
    printf("%d ", a->val);
    a = a->suiv;
  }
  printf("\n");
  //parcourt tout le tableau adj et l'affiche
  for(int i = 1; i < c; i++){
    printf("Page %d :     ", i);
    Sommet * a = creer_sommet();
    if (adj[i] == NULL) return;
    a = adj[i]->premier;
    while(a != NULL){
      printf("%d ", a->val);
      a = a->suiv;
    }
    printf("\n");
  }
  printf("\n");
  return;
}
/*------------------------------------------------*/
//fonction pour calculer la proba pour le mode test
void cal_prob_t(liste * adj[], int c, int k, char * ligne_res, double pourcentage){

  char * separateur = " ";
  double tab_vrai_val[c];
  char * prob = malloc(sizeof(char));
  double max = 0, maxf = 0, it_max = 0, it_maxf = 0,somme_finale = 0;

  int vss = 0;
  double c_f = c;
  double epsilon = 1 / (10*(c_f-1));
  double tab_anc[c];//va contenir les prob du tour k-1
  double tab_nouv[c];//va contenir les prob du tour k
  tab_nouv[0] = 0;//initialisation du super noeud
  prob = strtok(ligne_res,separateur);
  tab_vrai_val[0] = strtold(prob,NULL);



  //initialisation des autres probas et recupere les probas du fichier
  for (int i = 1; i < c; i++){
    tab_nouv[i] = 1 / (c_f-1);
    prob = strtok(NULL,separateur);
    tab_vrai_val[i] = strtold(prob,NULL);

  }

  for (int j = 0; j < k; j++ ){//boucle pour les k fois demandés
    somme_finale = 0;
    maxf = 0;
    it_maxf = 0;
    for (int l = 0; l < c; l++){//boucle pour copier le nouv tab dans l'ancien
    tab_anc[l] = tab_nouv[l];
  }
  for (int m = 0; m < c; m++){

    double som_prob = 0;
    for (int x = 0; x < c; x++){
      Sommet * s = adj[x]->premier;
      double nb_vs = 0;
      while(s != NULL){
        nb_vs++;
        s = s->suiv;
      }
      free(s);
      nb_vs--;
      Sommet * f = adj[x]->premier;
      while (f != NULL){
        if (f->val == m){
          if (x == 0){
            som_prob = som_prob + ((1 / (c_f-1)) * tab_anc[x]);

          }
          else if(m == 0){
            som_prob = som_prob + (epsilon * tab_anc[x]);
          }
          else{
            som_prob = som_prob + ( ((1-epsilon) / (nb_vs)) * tab_anc[x]);
          }
        }
        f = f->suiv;
      }
      free(f);
    }
    tab_nouv[m] = som_prob;
    somme_finale = somme_finale + som_prob;

    if(j == k-1){
      if(m==0){
        printf("\nLa probabilité du Super-Noeud : %f\n",som_prob );
      }
      else{
        printf("\nLa probabilité d lien %d : %f\n",m,som_prob );
      }
    }
    it_maxf = ( (fabs (tab_nouv[m]-tab_vrai_val[m]) ) / (tab_vrai_val[m]) ) * 100;
    if (maxf < it_maxf){
      maxf = it_maxf;
    }
    if(j == (k-1)){
      it_max = ( (fabs (tab_nouv[m]-tab_vrai_val[m]) ) / (tab_vrai_val[m]) ) * 100;
      if (max < it_max){
        max = it_max;
      }
    }
  }
  if ((maxf <= pourcentage) && (vss == 0)){
    vss = j;
  }
}

printf("\nLa somme des probabilités est de : %f\n", somme_finale );

if (vss == 0){
  int pl = k-1;
  double max2 = max;
  while (max2 > pourcentage){
    max2 = 0;
    //boucle pour copier le nouv tableau de proba dans l'ancien tableau
    for (int l = 0; l < c; l++){
      tab_anc[l] = tab_nouv[l];
    }
    for (int m = 0; m < c; m++){
      double som_prob = 0;
      for (int x = 0; x < c; x++){
        Sommet * s2 = adj[x]->premier;
        double nb_vs = 0;
        while(s2 != NULL){
          nb_vs++;
          s2 = s2->suiv;
        }
        free(s2);
        nb_vs--;
        Sommet * f2 = adj[x]->premier;
        while (f2 != NULL){
          if (f2->val == m){
            if (x == 0){
              som_prob = som_prob + ( (1/(c_f-1)) * tab_anc[x]);

            }
            else if(m == 0){
              som_prob = som_prob + (epsilon * tab_anc[x]);
            }
            else{
              som_prob = som_prob + ( ((1-epsilon)/(nb_vs)) * tab_anc[x]);
            }
          }
          f2 = f2->suiv;
        }
        free(f2);
      }
      tab_nouv[m] = som_prob;
      it_max = ( (fabs(tab_nouv[m]-tab_vrai_val[m])) / (tab_vrai_val[m]) ) * 100;
      if (max2 < it_max){
        max2 = it_max;
      }
    }
    pl++;
  }
  pl++;

  printf("\nLe nombre de k nécessaire pour avoir moins de  %f pourcent est : %d \n",pourcentage,pl);
  printf("\nLe pourcentage d'erreur de notre calcul est de %f \n", max);

}
else{
  vss++;
  printf("\nLe nombre de k nécessaire pour avoir moins de  %f pourcent est : %d \n",pourcentage,vss);
  printf("\nLe pourcentage d'erreur de notre calcul est de %f \n", max);
}

return ;
}
/*------------------------------------------------*/
//fonction pour calculer la proba pour le mode normal
void cal_prob_n(liste * adj[],int c, int x, Sommet * pages[],int k ){
  double c_f = c;
  double soo = 0;
  double epsilon = 1/( 10 *(c_f-1) );
  double tab_anc[c];//va contenir les prob du tour k-1
  double tab_nouv[c];//va contenir les prob du tour k
  tab_nouv[0] = 0;//initialisation du super noeud
  for (int i = 1; i<c;i++){//initialisation des autres probas
    tab_nouv[i] = 1/(c_f-1);
  }
  //partie Pagerank
  //recuperation du k
  for (int j = 0;j < k; j++ ){

    soo = 0;
    for (int l = 0; l < c; l++){//boucle pour copier le nouv tab dans l'ancien
    tab_anc[l] = tab_nouv[l];
  }
  for (int m = 0; m < c; m++){
    double som_prob = 0;
    for (int x = 0; x < c; x++){
      Sommet * s = adj[x]->premier;
      double nb_vs = 0;
      while(s != NULL){
        nb_vs++;
        s = s->suiv;
      }

      free(s);
      nb_vs--;
      Sommet * f = adj[x]->premier;
      while (f != NULL){
        if (f->val == m){
          if (x == 0){
            som_prob = som_prob + ( (1/(c_f-1)) * tab_anc[x]);
          }
          else if(m == 0){
            som_prob = som_prob + (epsilon * tab_anc[x]);
          }
          else{
            som_prob = som_prob + ( ((1-epsilon)/(nb_vs)) * tab_anc[x]);
          }
        }
        f = f->suiv;
      }
      free(f);
      free(s);
    }
    tab_nouv[m] = som_prob;
    soo = soo + som_prob;
  }
}
for (int mp1 = 0; mp1 < x; mp1++){
  int max = 0;
  for(int mp = 0 ; mp < c; mp++){
    if(tab_nouv[mp]>tab_nouv[max]){
      max = mp;
    }
  }
  printf("Rang %d : %s - Page rank = %f\n", mp1+1, pages[max-1]->nom_page, tab_nouv[max]);
  tab_nouv[max] = 0;
}
printf("\nLa somme des probabilités vaut : %f\n",soo );
return;
}
/*-----------------------------------------------------------------------------*/
//libere adj
void libere_adj(liste * adj[],int c){
  for (int i = 0; i < c; i++){
    Sommet * s = adj[i]->premier;
    while (s != NULL) {
      Sommet * temp = s;
      s = s->suiv;
      free(temp->nom_page);
      free(temp);
      temp = NULL;
    }
    free(s);
  }
}
/*-----------------------------------------------------------------------------*/
//libere pages
void libere_pages(Sommet * pages[],int c){
  for(int i = 0; i < c-1; i++){
    free(pages[i]->nom_page);
    free(pages[i]);
  }
  return;
}
/*------------------------------------------------*/
int main (int argc, char * argv[]){

  float temps_final = 0;
  clock_t t1_final = 0, t2_final = 0;

  t1_final = clock();
  //condition pour entrer dans le mode test (carré)
  if (strcmp(argv[1],"-t") == 0){

    //récupere le nom du fichier dans la ligne de commande dans la 3eme place du tableau de caractere
    FILE * fic = fopen(argv[3],"r");

    // variable qui va stocker la ligne
    char * ligne0_mat = malloc( N * sizeof(char));
    fgets(ligne0_mat,N,fic);
    //parcourir la premiere ligne de la matrice pour avoir la taille de la matrice
    int c = 0, i = 0;
    while (ligne0_mat[i] != '\0'){
      if ((ligne0_mat[i] =='1') || (ligne0_mat[i]=='0')){
        c++;
      }
      i++;
    }
    c++;

    //tableau représentant le graphe
    liste * adj[c];

    // pour le super noeud(ca marche)
    ajout_super_noeud(adj, c);
    ajout_liste_chainee(adj, ligne0_mat, 1);
    //variable qui va stocker chaque ligne de la matrice
    char * ligne_mat = malloc(N * sizeof(char));
    //boucle qui va permettre de creer le tableau de liste chainee adj
    for(int i = 2; i <= c; i++){
      fgets(ligne_mat,N, fic);
      ajout_liste_chainee(adj,ligne_mat,i);
    }

    afficher_adj(adj,c);

    char * ligne_resul = malloc(N * sizeof(char));
    fgets(ligne_resul,N,fic);//sauter la ligne vide
    fgets(ligne_resul,N,fic);

    //récupération du k
    double pourcentage = strtold(argv[4],NULL);
    int p = atoi(argv[2]);
    cal_prob_t(adj, c, p, ligne_resul,pourcentage);


    fclose(fic);
    free(ligne_mat);
    free(ligne0_mat);
    free(ligne_resul);

    libere_adj(adj,c);
  }
  //ondition pour entrer dans le mode normal (carré)
  else if (strcmp(argv[1],"-n") == 0){
    //récupère le x entrer par l'utilisateur
    int x = atoi(argv[3]);
    int k = atoi(argv[4]);
    //ouvre le fichier pour le lire
    FILE * fic = fopen(argv[2],"r");
    //variable qui va stocker les lignes
    char * ligne1_fichier = malloc( N * sizeof(char));
    //variable qui permet de stocker le nombre de ligne et sert aussi
    int c = 0;
    //creattion du tableau de sommet pages qui prend la page de chaque ligne
    Sommet ** pages = malloc( N * sizeof(Sommet));
    //boucle qui va permettre d'avoir le nombre de page wiki et de fixer la taille du tableau adj
    while(fgets(ligne1_fichier,N,fic) != NULL){
      Sommet * s = creer_sommet();
      int u = 0;
      s->val = c+1;
      //boucle qui va copier le premier lien avant le symbole  '|' ou la fin de la ligne qui va le mettre dans le tableau de structure pages
      while((ligne1_fichier[u] != '|') && (ligne1_fichier[u] != '\n') && (ligne1_fichier[u] != '\0')){
        s->nom_page[u] = ligne1_fichier[u];
        u++;
      }
      pages[c] = s;
      c++;
    }

    free(ligne1_fichier);

    //on incrémente c pour prendre en compte le super noeud
    c++;
    //replace le pointeur qui parcourt le fichier au tout début(évite de fermer et d'ouvir le fichier )
    rewind(fic);
    //créer le tableau de liste chainée adj  et ajoute le super noeud dans adj
    liste ** adj = malloc(c * sizeof(liste));
    ajout_super_noeud(adj,c);
    //stock les lignes du fichier
    char * ligne2_fichier = malloc( N * sizeof(char));

    //boucle qui va remplir adj trier chaque liste chainée dans chaque case et supprime les doublons dans chaqque liste chainée
    for (int i = 1; i < c; i++ ){
      fgets(ligne2_fichier,N,fic);
      //transforme la ligne en ligne pouis l'ajoute dans le tableau adj
      ajout_liste_chainee_wiki(adj,ligne2_fichier,pages,c,i);
      //supprime les doublons dans les listes chainées
      supp_doublons_liste_chainee(adj,i);
    }
    free(ligne2_fichier);

    afficher_adj(adj,c);

    //calcul de la proba
    cal_prob_n(adj,c,x,pages,k);

    fclose(fic);
    libere_adj(adj,c);

    libere_pages(pages,c);

    free(pages);
    free(adj);

  }
  else{
    printf("\nERREUR : nous ne possédons pas un tel mode\n" );
  }

  t2_final = clock();
  temps_final = (float)(t2_final-t1_final)/CLOCKS_PER_SEC;
  printf("\n Temps final = %f\n", temps_final);
  return 0;
}

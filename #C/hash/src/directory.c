#include <stdlib.h>
#include <stdio.h>

#include "../include/directory.h"
#include "../include/contact.h"
#include "../include/hash.h"

/*
  Crée un nouvel annuaire contenant _len_ listes vides.
*/
struct dir *dir_create(uint32_t len)
{
  struct dir* mon_dico=calloc(1,sizeof(struct dir));
  struct contact** ma_liste=calloc(len,sizeof(struct contact*));
  mon_dico->liste_de_contact=ma_liste;
  mon_dico->taille=len;
  return mon_dico;
}

/*
  Insère un nouveau contact dans l'annuaire _dir_, construit à partir des nom et
  numéro passés en paramètre. Si il existait déjà un contact du même nom, son
  numéro est remplacé et la fonction retourne une copie de l'ancien numéro.
  Sinon, la fonction retourne NULL.
*/
char *dir_insert(struct dir *dir, const char *name, const char *num)
{
  uint32_t position=hash(name)%dir->taille;
  char* res= insere_dans_ma_liste(&(dir->liste_de_contact[position]),num,name);
  float compare=(float)taille_occupee(dir)/(float)dir->taille;
  if(compare>0.75){
    reorganise_tout(dir);
  }
  return res;
}

/*
  Retourne le numéro associé au nom _name_ dans l'annuaire _dir_. Si aucun contact
  ne correspond, retourne NULL.
*/
const char *dir_lookup_num(struct dir *dir, const char *name)
{
    uint32_t position=hash(name)%dir->taille;
    return lookup_num(dir->liste_de_contact[position],name);
}

/*
  Supprime le contact de nom _name_ de l'annuaire _dir_. Si aucun contact ne
  correspond, ne fait rien.
*/
void dir_delete(struct dir *dir, const char *name)
{
    uint32_t position=hash(name)%dir->taille;
    delete(&(dir->liste_de_contact[position]),name);
}

/*
  Libère la mémoire associée à l'annuaire _dir_.
*/
void dir_free(struct dir *dir)
{
  for(uint32_t i=0;i<dir->taille;i++){
    libere(dir->liste_de_contact[i]);
  }
  free(dir->liste_de_contact);
  free(dir);
}

/*
  Affiche sur la sortie standard le contenu de l'annuaire _dir_.
*/
void dir_print(struct dir *dir)
{
  for (uint32_t i=0;i<dir->taille;i++){
    print_ma_liste(dir->liste_de_contact[i]);
  }
}


int taille_occupee(struct dir* dir){
  int taille=0;
  for (uint32_t i=0;i<dir->taille;i++){
    taille+=taille_liste(dir->liste_de_contact[i]);
  }
  return taille;
}



int reorganise_tout(struct dir* dir){
  uint32_t nouvelle_taille= 2*(dir->taille);
  int taille=taille_occupee(dir);
  const char* ma_liste_de_chaine[taille];
  const char* numero[taille];
  int ind=0;
  for (uint32_t i=0;i<dir->taille;i++){
    struct contact* current=dir->liste_de_contact[i];
    while(current!=NULL){
      ma_liste_de_chaine[ind]=current->name;
      numero[ind]=current->numero;
      dir_delete(dir,ma_liste_de_chaine[ind]);
      current=current->suivant;
      ind+=1;
    }
  }
dir->liste_de_contact=calloc(nouvelle_taille,sizeof(struct contact*));
dir->taille=nouvelle_taille;
for (int i=0;i<ind;i++){
  dir_insert(dir,ma_liste_de_chaine[i],numero[i]);  
}
return EXIT_SUCCESS;
}



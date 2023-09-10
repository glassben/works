#ifndef _CONTACT_H_
#define _CONTACT_H_

/*
  Un contact représente une association {nom, numéro}.
*/
struct contact{
const char* name;
const char* numero;
struct contact* suivant;};

extern struct contact* creation();
extern char* insere_dans_ma_liste(struct contact** ma_liste,const char* mon_numero,const char* mon_nom);
extern const char* lookup_num(struct contact* ma_liste,const char* name);
extern void delete(struct contact** ma_liste,const char* name);
extern void libere(struct contact* ma_liste);
extern void print_ma_liste(struct contact* ma_liste);
extern int taille_liste(struct contact* ma_liste);

#endif /* _CONTACT_H_ */

#include "../include/contact.h"
#include <stdlib.h>
#include <stdio.h>

struct contact* creation(){
struct contact* ma_nouvelle_liste =calloc(1,sizeof(struct contact));
return ma_nouvelle_liste;
}


char* insere_dans_ma_liste(struct contact** ma_liste,const char* mon_numero,const char* mon_nom){
    if (*ma_liste==NULL){
        *ma_liste=creation();
        (*ma_liste)->name=mon_nom;
        (*ma_liste)->numero=mon_numero;
        return NULL;
    }
    struct contact* current=*ma_liste;
    struct contact* precurrent=*ma_liste;
    while (current!=NULL){
        if (current->name==mon_nom){
            const char* mon_ancien_numero=current->numero;
            current->numero=mon_numero;
            return (char*)mon_ancien_numero;
        }
        else{
            precurrent=current;
            current=current->suivant;
        }
    }
    struct contact* ma_nouvelle_liste=creation();
    ma_nouvelle_liste->name=mon_nom;
    ma_nouvelle_liste->numero=mon_numero;
    precurrent->suivant=ma_nouvelle_liste;
    return NULL;
}


const char* lookup_num(struct contact* ma_liste,const char* name){
    struct contact* current=ma_liste;
    while(current!=NULL){
        if (current->name==name){
            return current->numero;
        }
        current=current->suivant;
    }
    return NULL;
}



void delete(struct contact** ma_liste,const char* name){
    struct contact* current=*ma_liste;
    struct contact* precurrent=*ma_liste;
    if (current==NULL){
        return;
    }
    if ((*ma_liste)->name==name){
        *ma_liste=(*ma_liste)->suivant;
        free(current);
        return;
    }
    while (current!=NULL){
        if (current->name==name){
            precurrent->suivant=current->suivant;
            free(current);
            return;
        }
        else{
            precurrent=current;
            current=current->suivant;
        }
    }
}

void libere(struct contact* ma_liste){
    if (ma_liste!=NULL){
        struct contact* suivant=ma_liste->suivant;
        free(ma_liste);
        ma_liste=suivant;
        libere(ma_liste);
    }
}

void print_ma_liste(struct contact* ma_liste){
    struct contact* current=ma_liste;
    while(current!=NULL){
        printf("(%s,%s)->",current->name,current->numero);
        current=current->suivant;
    }
    printf("\n");
}

int taille_liste(struct contact* ma_liste){
    struct contact* current=ma_liste;
    int taille=0;
    while(current!=NULL){
        taille+=1;
        current=current->suivant;
    }
    return taille;
}


/*
int main(){
    struct contact* ma_liste=NULL;
    insere_dans_ma_liste(&ma_liste,"0638580160","Benj");
    print_ma_liste(ma_liste);

}*/
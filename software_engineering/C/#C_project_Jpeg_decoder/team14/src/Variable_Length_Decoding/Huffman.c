#include "../../include/module_matriciel.h"
#include "../../include/divise.h"   



struct liste{
    struct arbre* element;
    struct liste* suiv;
};



struct arbre{
    uint8_t element;
    struct arbre* fils_gauche;
    struct arbre* fils_droit;
};



void affiche2(struct arbre* mon_arbre){
    /* affiche les éléments dans l'ordre préfixe*/
    if (mon_arbre!=NULL){
        printf("%u->",mon_arbre->element);
        affiche2(mon_arbre->fils_gauche);
        affiche2(mon_arbre->fils_droit);}
}



void affiche(struct liste* ma_liste){
    /* affiche la liste du premier au deuxième élément*/
    struct liste* current=ma_liste;
    while (current!=NULL){
        affiche2(current->element);
        current=current->suiv;
    }
}


struct liste* creer(struct arbre* elem){
    /*une fonction qui créé une liste à un seul élément*/
    struct liste* m=malloc(sizeof(struct liste));
    m->element=elem;
    return m;
}


int taille(struct liste* elem){
    /* une fonction qui calcule la taille d'une liste*/
    int s=0;
    struct liste* current=elem;
    if (current==NULL){
        return 0;
    }
    while (current!=NULL){
        current=current->suiv;
        s+=1;
    }
    return s;
}


void free_mon_arbre(struct arbre* mon_arbre){
    /*une fonction qui libère un arbre */
    if (mon_arbre!=NULL){
        struct arbre* current=mon_arbre->fils_droit;
        struct arbre* current2=mon_arbre->fils_gauche;
        free(mon_arbre);
        free_mon_arbre(current);
        free_mon_arbre(current2);}
}


void free_ma_liste(struct liste* ma_liste){
    /*une fonction qui libère une liste */
    if (ma_liste!=NULL){
        struct liste* current=ma_liste->suiv;
        free(ma_liste);
        free_ma_liste(current);
    }
}



struct arbre* recupere_element(struct liste** ma_liste){
    /*la fonction recupère le premier élément de la liste et le retourne en l'éliminant de la liste */
    if (ma_liste != NULL){
    struct liste* current=(*ma_liste);
    struct arbre* elem=current->element;
    (*ma_liste) = current->suiv;
    free(current);
    return elem;}
    else
    {
        return NULL;
    }
}



struct liste* empile_element(struct liste* ma_liste, struct arbre* elem){
    /*rajoute un élément à la fin de la file*/
    struct liste* nouvelle=calloc(1,sizeof(struct liste));
    nouvelle->element=elem;
    nouvelle->suiv=NULL;
    if (ma_liste==NULL){
        return nouvelle;
    }
    else{
    struct liste* current = ma_liste;
    struct liste* precurrent=ma_liste;
    while (current!=NULL){
        precurrent=current;
        current=current->suiv;
    }
    precurrent->suiv=nouvelle;
    return ma_liste;
    }
}

struct arbre* construit_arbre_bis(uint8_t* table){
    /*creer l'arbre de Huffman a partir de la table de Huffmann en faisant un parcours en largeur du tableau
    Attention la table de Huffmann commence par l'indice 1 et ses 16 premières valeures sont le nombre de code 
    de longeur i à l'indice i */
    int indice=1;
    /*on initialise l'indice à 1 puisque la table de Huffman contient le bit d'information sur la table en premier élément*/
    int indice_considere=17;
    /*on initialise un pointeur pointant vers le premier mot de code*/
    struct arbre* tree=calloc(1,sizeof(struct arbre));
    struct arbre* fils_droit=calloc(1,sizeof(struct arbre));
    struct arbre* fils_gauche=calloc(1,sizeof(struct arbre));
    tree->fils_droit =fils_droit;
    tree->fils_gauche=fils_gauche;
    /*on initialise un arbre contenant des fils qui seront eventuellement complétés si la table contient des mots de code de longueur 1 */
    struct liste* ma_liste=calloc(1,sizeof(struct liste));
    ma_liste->element=fils_gauche;
    ma_liste=empile_element(ma_liste,fils_droit);
    while (indice<=16){
        if (table[indice]==0){
            int ind =taille(ma_liste);
            for (int i=0;i<ind;i++){
                /*dans le cas où il n'y ait pas de mot de code longueur indice on récupère tous les noeuds de la liste et on les complète de fils droit et gauche 
                que l'on place dans la liste*/
                struct arbre* a=recupere_element(&ma_liste);
                struct arbre* fg= calloc(1,sizeof(struct arbre));
                struct arbre* fd= calloc(1,sizeof(struct arbre));
                a->fils_droit=fd;
                a->fils_gauche=fg;
                ma_liste=empile_element(ma_liste,fg);
                ma_liste=empile_element(ma_liste,fd);
            }
            indice+=1;
        }
        else{
            /*dans le cas où il y ait indice_considere mots de code de longueur indice,on prend les noeuds les plus à droite qui sont les noeuds du début de la liste
            et on leur affecte à chacun un code en incrémentant l'indice_considere.Une fois fait,on prend lereste des arbres et on leur affecte des fils gauches et fils droits 
            que l'on place dans la liste */
            int mon_stop=table[indice];
            for (int i=0;i<mon_stop;i++){
                struct arbre* a=recupere_element(&ma_liste);
                a->element=table[indice_considere];
                indice_considere+=1;
            }
            int ind=taille(ma_liste);
            for (int i=0;i<ind;i++){
                struct arbre* a=recupere_element(&ma_liste);
                struct arbre* fg= calloc(1,sizeof(struct arbre));
                struct arbre* fd= calloc(1,sizeof(struct arbre));
                a->fils_droit=fd;
                a->fils_gauche=fg;
                ma_liste=empile_element(ma_liste,fg);
                ma_liste=empile_element(ma_liste,fd);
            }
            indice+=1;
        }  
    }
    free_ma_liste(ma_liste);
return tree;}



int16_t exponentie(uint8_t nombre_a_exponentier, uint8_t exposant){
    /*une simple fonction qui exponentie un nombre entier non signé par un exposant*/
        int res=1;
        for (uint8_t i=0;i<exposant;i++){
            res= res*nombre_a_exponentier;
        }
        return res;
    }



size_t* recupere_bit(uint8_t* fichier_concerné, size_t* table_ou_on_en_est) {
    /* une fonction qui prend en argument un tableau de 4 elements: le premier etant l'indice de l'octet considere dans le bit stream
    le deuxieme element etant l'indice du prochain bit de l'octet a explorer,le troisieme element etant la valeur du bit courant explore et 
    le quatrieme bit etant l'indice du prochain bit a explorer*/
    if (table_ou_on_en_est[1] == 0) {
        if (fichier_concerné[table_ou_on_en_est[0]] == 255) /* ici on considere le cas du byte stuffing :
        si l'octet courant est egal a 0xff et si l'octet suivant est egal a 0 alors on incrementera l'octet suivant a considerer de 2 et non de 1 */
        {
            if (fichier_concerné[table_ou_on_en_est[0] + 1] == 0)
            {
                table_ou_on_en_est[1]+=1;
                int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b10000000)/128;
                table_ou_on_en_est[2]=bit_concerne;
                table_ou_on_en_est[0] = 0;
                table_ou_on_en_est[3] = 2;
                return table_ou_on_en_est;
            }

            else
            {
                printf("Erreur d'encodage de byte stuffing dans le fichier jpeg. Arrêt du programme.\n");
                exit(EXIT_FAILURE);
            }
        }

        else
        {
            table_ou_on_en_est[1]+=1;
            int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b10000000)/128;
            table_ou_on_en_est[2]=bit_concerne;
            table_ou_on_en_est[0] = 0;
            table_ou_on_en_est[3] = 1;
            return table_ou_on_en_est;
        }
    }
/*on incrémente à chaque appel de recupere_bit l'octet considéré de 1 et on récupère cet octet*/
    if (table_ou_on_en_est[1]==1){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b01000000)/64;
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1]==2){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b00100000)/32;
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1]==3){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b00010000)/16;
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1]==4){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b00001000)/8;
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1]==5){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b00000100)/4;
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1]==6){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b00000010)/2;
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1]==7){
        table_ou_on_en_est[1]+=1;
        int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b00000001);
        table_ou_on_en_est[2]=bit_concerne;
        return table_ou_on_en_est;
    }

    if (table_ou_on_en_est[1] % 8==0){
        /* dans le cas ou on ait atteint la totalite de l'octet,on affecte l'indice de l'octet suivant a l'octet courant et on incremente l'octet suivant de un*/
        table_ou_on_en_est[0] = table_ou_on_en_est[3];
        if (fichier_concerné[table_ou_on_en_est[0]] == 255)
        {
            if (fichier_concerné[table_ou_on_en_est[0] + 1] == 0)
            {
                table_ou_on_en_est[1]=1;
                int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b10000000)/128;
                table_ou_on_en_est[2] = bit_concerne;
                table_ou_on_en_est[3] = table_ou_on_en_est[0] + 2;
                return table_ou_on_en_est;
            }

            else
            {
                printf("Erreur d'encodage de byte stuffing dans le fichier jpeg. Arrêt du programme.\n");
                exit(EXIT_FAILURE);
            }
        }

        else
        {
            table_ou_on_en_est[1]=1;
            int bit_concerne=(fichier_concerné[table_ou_on_en_est[0]] & 0b10000000)/128;
            table_ou_on_en_est[2] = bit_concerne;
            table_ou_on_en_est[3] = table_ou_on_en_est[0] + 1;
            return table_ou_on_en_est;
        }
       
    }
    return NULL;
}





int16_t* lecture(uint8_t* fichier_considere, size_t* la_ou_je_suis_dans_le_bit, struct arbre* mon_arbre){
    /*renvoie un tableau contenant la classe de magnetude decode et l'indice de l'element dans la classe de magnetude qui sera decode par la fonction suivante*/
    int16_t* classe_plus_indice =calloc(2,sizeof(int16_t));
    struct arbre* current=mon_arbre;
    recupere_bit(fichier_considere,la_ou_je_suis_dans_le_bit);
    while(true){
        if (la_ou_je_suis_dans_le_bit[2]==0){ /* on parcours jusqu'a arriver a une racine qui contient un mot de code correspondant 
        a la classe de magnetude  */
            current=current->fils_gauche;
            if (current->fils_droit==NULL && current->fils_gauche==NULL){
                classe_plus_indice[0]=current->element;
                int16_t reste=0;
                int16_t nombre_de_coefficient_a_prendre= current->element;
                /*on recupere ensuite l'indice dans la classe de magnetude en prenant les nombre_de_coefficient_a_prendre bits suivants */
                for (int16_t i=nombre_de_coefficient_a_prendre-1;i>-1;i--){
                    recupere_bit(fichier_considere,la_ou_je_suis_dans_le_bit);
                    reste=reste+la_ou_je_suis_dans_le_bit[2]*exponentie(2,i);
                }
                classe_plus_indice[1]=reste;
                return classe_plus_indice;
            }
        }
        if (la_ou_je_suis_dans_le_bit[2]==1){
            current=current->fils_droit;
            if (current->fils_droit==NULL && current->fils_gauche==NULL){
                classe_plus_indice[0]=current->element;
                int16_t reste=0;
                int16_t nombre_de_coefficient_a_prendre=current->element;
                for (int16_t i=nombre_de_coefficient_a_prendre-1;i>-1;i--){
                    recupere_bit(fichier_considere,la_ou_je_suis_dans_le_bit);
                    reste=reste+la_ou_je_suis_dans_le_bit[2]*exponentie(2,i);
                }
                classe_plus_indice[1]=reste;
                return classe_plus_indice;}
            }
        recupere_bit(fichier_considere,la_ou_je_suis_dans_le_bit);
        }
    }



uint8_t lecture_sans_indice_de_magnetude(uint8_t* fichier_considere, size_t* la_ou_je_suis_dans_le_bit, struct arbre* mon_arbre){
    /*une fonction qui parcours de la même façon l'arbre de Huffmann que précédemment mais sans chercher l'indice
    de la classe de magnetude*/
    struct arbre* current=mon_arbre;
    recupere_bit(fichier_considere,la_ou_je_suis_dans_le_bit);
    while(true){
        if (la_ou_je_suis_dans_le_bit[2]==0){
            current=current->fils_gauche;
            if (current->fils_droit==NULL && current->fils_gauche==NULL){
                return current->element;
            }
        }
        if (la_ou_je_suis_dans_le_bit[2]==1){
            current=current->fils_droit;
            if (current->fils_droit==NULL && current->fils_gauche==NULL){
                return current->element;
            }
        }
        recupere_bit(fichier_considere,la_ou_je_suis_dans_le_bit);
    }
}



int16_t decodage_classe_de_magnetude(int8_t ma_classe, int16_t l_indice_dans_la_classe_de_magnetude){
    /*une fonction qui renvoie le coefficient appartenant a la classe de magnetude ma_classe et d'indice l'indice_dans_ma_classe_de_magnetude*/
    int16_t debut_premiere_partie_de_la_table_de_magnetude=-(exponentie(2,ma_classe))+1;
    int16_t fin_premiere_partie_de_la_table_de_magnetude=-(exponentie(2,ma_classe-1));
    int16_t debut_seconde_partie_de_la_table_de_magnetude=(exponentie(2,ma_classe-1));
    int16_t distance=(fin_premiere_partie_de_la_table_de_magnetude-debut_premiere_partie_de_la_table_de_magnetude)+1;
    if (l_indice_dans_la_classe_de_magnetude >= distance){
        return (debut_seconde_partie_de_la_table_de_magnetude+(l_indice_dans_la_classe_de_magnetude-distance));
    }
    else{
        return (debut_premiere_partie_de_la_table_de_magnetude+l_indice_dans_la_classe_de_magnetude);
    }

}


void decodage_RLE(uint8_t* composante_a_decoder, size_t *la_ou_j_en_suis_dans_le_flux_de_bit, int16_t* table_a_completer, struct arbre* mon_arbre_AC){
    /*une fonction qui realise le decodage des 63 coefficients AC formant un bloc avec le coefficient DC et les placent dans un tableau table_a_completer*/
    int i=1;
/*indice dans le tableau*/
    while (i<64){
        uint8_t coefficient_a_decoder=lecture_sans_indice_de_magnetude(composante_a_decoder,la_ou_j_en_suis_dans_le_flux_de_bit,mon_arbre_AC);
        int8_t  nombre_de_zero_qui_precede=(coefficient_a_decoder&0b11110000)/16;
        int8_t ma_classe=coefficient_a_decoder&0b00001111;
        int16_t mon_indice=0;
        if (coefficient_a_decoder==0x00){
            for(int j=i;j<64;j++){
                table_a_completer[j]=0;
            }
            return;
        }
        for (int8_t k=ma_classe-1;k>-1;k--){
            recupere_bit(composante_a_decoder,la_ou_j_en_suis_dans_le_flux_de_bit);
            mon_indice=mon_indice+la_ou_j_en_suis_dans_le_flux_de_bit[2]*exponentie(2,k);
        }
        for(uint8_t j=0;j<nombre_de_zero_qui_precede;j++){
            table_a_completer[i]=0;
            i+=1;
        }
        table_a_completer[i]=decodage_classe_de_magnetude(ma_classe,mon_indice);
        i+=1;
    }
}


int16_t decodage_DC_premiere_MCU(uint8_t* composante_a_decoder, size_t* la_ou_je_suis_dans_le_bit, struct arbre* mon_arbre_DC){
    /*decode le premier coefficient DC du bitstream*/
    int16_t* ma_composante_decode =lecture(composante_a_decoder,la_ou_je_suis_dans_le_bit,mon_arbre_DC);
    int16_t indice_de_magnetude=ma_composante_decode[0];
    int16_t  indice_de_l_element=ma_composante_decode[1];
    int16_t debut_premiere_partie_de_la_table_de_magnetude=-(exponentie(2,indice_de_magnetude))+1;
    int16_t fin_premiere_partie_de_la_table_de_magnetude=-(exponentie(2,indice_de_magnetude-1));
    int16_t debut_seconde_partie_de_la_table_de_magnetude=(exponentie(2,indice_de_magnetude-1));
    int16_t distance=(fin_premiere_partie_de_la_table_de_magnetude-debut_premiere_partie_de_la_table_de_magnetude)+1;
    if (indice_de_l_element >= distance){
        free(ma_composante_decode);
        return (debut_seconde_partie_de_la_table_de_magnetude+(indice_de_l_element-distance));
    }
    else{
        free(ma_composante_decode);
        return (debut_premiere_partie_de_la_table_de_magnetude+indice_de_l_element);
    }
}



int16_t decodage_DC_suivant_MCU(uint8_t* composante_a_decoder, size_t* la_ou_je_suis_dans_le_bit, struct arbre* mon_arbre_DC, int16_t valeur_de_la_precedente_composante){
    /*decode le coefficient DC d'un bloc repéré par un tableau contenant sa classe de magnétude et son indice  en décodant la difference par rapport au  coefficient DC du bloc precedent et l'ajoutant au code décodé*/
    int16_t* ma_composante_decode =lecture(composante_a_decoder,la_ou_je_suis_dans_le_bit,mon_arbre_DC);
    int16_t indice_de_magnetude=ma_composante_decode[0];
    int16_t indice_de_l_element=ma_composante_decode[1];
    int16_t debut_premiere_partie_de_la_table_de_magnetude=-(exponentie(2,indice_de_magnetude))+1;
    int16_t fin_premiere_partie_de_la_table_de_magnetude=-(exponentie(2,indice_de_magnetude-1));
    int16_t debut_seconde_partie_de_la_table_de_magnetude=(exponentie(2,indice_de_magnetude-1));
    int16_t distance=(fin_premiere_partie_de_la_table_de_magnetude-debut_premiere_partie_de_la_table_de_magnetude)+1;
    if (indice_de_l_element >= distance){
        free(ma_composante_decode);
        return (debut_seconde_partie_de_la_table_de_magnetude+(indice_de_l_element-distance))+valeur_de_la_precedente_composante;
    }
    else{
        free(ma_composante_decode);
        return (debut_premiere_partie_de_la_table_de_magnetude+indice_de_l_element)+valeur_de_la_precedente_composante;
    }
}


int16_t*** decodage_en_couleur_ordre_normale(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffmann_luminance_DC,uint8_t* table_de_huffmann_luminance_AC,uint8_t* table_de_huffmann_chrominance_DC,uint8_t* table_de_huffmann_chrominance_AC){
    /*fonction qui réalise le decodage des données brutes dans l'ordre YCbCr et qui renvoie un tableau à 3 éléments chacun contenant
    l'ensemble des blocs décodés d'une composantes*/
    int16_t*** mon_image_decode=calloc(3, sizeof(int16_t**));
    int16_t** luminance = calloc(nb_cellules_Y, sizeof(int16_t*));
    int16_t** chrominance_bleu = calloc(nb_cellules_Cb, sizeof(int16_t*));
    int16_t** chrominance_rouge = calloc(nb_cellules_Cr, sizeof(int16_t*));
    mon_image_decode[0]=luminance;
    mon_image_decode[1]=chrominance_bleu;
    mon_image_decode[2]=chrominance_rouge;
    size_t indice_dans_bloc_luminance=0;
    size_t indice_dans_bloc_chrominance_bleue=0;
    size_t indice_dans_bloc_chrominance_rouge=0;
    /* le nombre de composante dans un bloc du bitstream est donné par le produit des facteurs d'échantillonnage*/
    size_t MCU_a_parcourir_luminance=facteur_d_echantillonnage_luminence[0]*facteur_d_echantillonnage_luminence[1];
    size_t MCU_a_parcourir_chrominance_bleue=facteur_d_echantillonnage_bleu[0]*facteur_d_echantillonnage_bleu[1];
    size_t MCU_a_parcourir_chrominance_rouge=facteur_d_echantillonnage_rouge[0]*facteur_d_echantillonnage_rouge[1];
    /*initialisation d'un pointeur permettant de parcourir le bitstream bit à bit.La structure est détaillée dans la fonction recupere bit a bit*/
    size_t* la_ou_je_suis=calloc(4,sizeof(size_t));
    struct arbre* mon_arbre_luminance_AC=construit_arbre_bis(table_de_huffmann_luminance_AC);
    struct arbre* mon_arbre_luminance_DC=construit_arbre_bis(table_de_huffmann_luminance_DC);
    struct arbre* mon_arbre_chrominance_AC=construit_arbre_bis(table_de_huffmann_chrominance_AC);
    struct arbre* mon_arbre_chrominance_DC=construit_arbre_bis(table_de_huffmann_chrominance_DC);

/*initialisation du premier bloc de la composante de luminance que l'on décode et qu'on place dans la 1ère colonne de l'image decodée*/
    int16_t* premier_MCU_luminance=calloc(64,sizeof(int));
    int16_t premier_coefficient_DC_luminance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC);
    premier_MCU_luminance[0]=premier_coefficient_DC_luminance;
/*on décode les 63 coefficients suivants grâce à la fonction RLE */
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_luminance,mon_arbre_luminance_AC);
    luminance[indice_dans_bloc_luminance]=premier_MCU_luminance;
    indice_dans_bloc_luminance+=1;
/*on décode ensuite le reste des premiers blocs de luminance apparaissant au début du bit stream*/
    for (size_t i=0;i<MCU_a_parcourir_luminance-1;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}
/* on passe ensuite au décodage du premier bloc de chrominance bleue que l'on place dans la seconde colonne de l'imge decodée*/
    int16_t* premier_MCU_chrominance_bleue=calloc(64,sizeof(int16_t));
    int16_t premier_coefficient_DC_chrominance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_bleue[0]=premier_coefficient_DC_chrominance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_bleue,mon_arbre_chrominance_AC);
    chrominance_bleu[indice_dans_bloc_chrominance_bleue]=premier_MCU_chrominance_bleue;
    indice_dans_bloc_chrominance_bleue+=1;
/*on décode le reste des premiers blocs de chrominance bleue */    
    for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue-1;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}
/*on passe au décodage des premiers blocs de chrominance rouge que l'on vient placer dans la 3eme case du tableau image à decoder*/    
    int16_t* MCU_chrominance_rouge=calloc(64,sizeof(int16_t));
    int16_t coefficient_DC_chrominance_rouge=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    MCU_chrominance_rouge[0]=coefficient_DC_chrominance_rouge;
    decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge,mon_arbre_chrominance_AC);
    chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge;
    indice_dans_bloc_chrominance_rouge+=1;
/*on complète avec le reste des blocs de chrominance rouge*/
    for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge-1;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}
/*on refait la même chose jusqu'à ce qu'on ait decodé le dernier élément du bitstream*/
    while (la_ou_je_suis[0]<taille_de_l_image -1){

        for (size_t i=0;i<MCU_a_parcourir_luminance;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}
        }
   
    free_mon_arbre(mon_arbre_luminance_AC);
    free_mon_arbre(mon_arbre_luminance_DC);
    free_mon_arbre(mon_arbre_chrominance_AC);
    free_mon_arbre(mon_arbre_chrominance_DC);
    free(la_ou_je_suis);
    return mon_image_decode;
}

int16_t*** decodage_couleur_ordre_YRB(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC){
/*on réalise le même décodage mais pour un ordre pour lequel la chrominance rouge vient avant la chrominance bleue*/
    int16_t*** mon_image_decode=calloc(3, sizeof(int16_t**));
    int16_t** luminance = calloc(nb_cellules_Y, sizeof(int16_t*));
    int16_t** chrominance_bleu = calloc(nb_cellules_Cb, sizeof(int16_t*));
    int16_t** chrominance_rouge = calloc(nb_cellules_Cr, sizeof(int16_t*));
    mon_image_decode[0]=luminance;
    mon_image_decode[1]=chrominance_bleu;
    mon_image_decode[2]=chrominance_rouge;
    size_t indice_dans_bloc_luminance=0;
    size_t indice_dans_bloc_chrominance_bleue=0;
    size_t indice_dans_bloc_chrominance_rouge=0;
    size_t MCU_a_parcourir_luminance=facteur_d_echantillonnage_luminence[0]*facteur_d_echantillonnage_luminence[1];
    size_t MCU_a_parcourir_chrominance_bleue=facteur_d_echantillonnage_bleu[0]*facteur_d_echantillonnage_bleu[1];
    size_t MCU_a_parcourir_chrominance_rouge=facteur_d_echantillonnage_rouge[0]*facteur_d_echantillonnage_rouge[1];
    size_t* la_ou_je_suis=calloc(4,sizeof(size_t));
    struct arbre* mon_arbre_luminance_AC=construit_arbre_bis(table_de_huffman_luminance_AC);
    struct arbre* mon_arbre_luminance_DC=construit_arbre_bis(table_de_huffman_luminance_DC);
    struct arbre* mon_arbre_chrominance_AC=construit_arbre_bis(table_de_huffman_chrominance_AC);
    struct arbre* mon_arbre_chrominance_DC=construit_arbre_bis(table_de_huffman_chrominance_DC);


    int16_t* premier_MCU_luminance=calloc(64,sizeof(int));
    int16_t premier_coefficient_DC_luminance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC);
    premier_MCU_luminance[0]=premier_coefficient_DC_luminance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_luminance,mon_arbre_luminance_AC);
    luminance[indice_dans_bloc_luminance]=premier_MCU_luminance;
    indice_dans_bloc_luminance+=1;

    for (size_t i=0;i<MCU_a_parcourir_luminance-1;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}


    int16_t* premier_MCU_chrominance_rouge=calloc(64,sizeof(int16_t));
    int16_t premier_coefficient_DC_chrominance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_rouge[0]=premier_coefficient_DC_chrominance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_rouge,mon_arbre_chrominance_AC);
    chrominance_rouge[indice_dans_bloc_chrominance_rouge]=premier_MCU_chrominance_rouge;
    indice_dans_bloc_chrominance_rouge+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge-1;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}


    int16_t* MCU_chrominance_bleue=calloc(64,sizeof(int16_t));
    int16_t coefficient_DC_chrominance_bleue=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    MCU_chrominance_bleue[0]=coefficient_DC_chrominance_bleue;
    decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue,mon_arbre_chrominance_AC);
    chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue;
    indice_dans_bloc_chrominance_bleue+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue-1;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}


    while (la_ou_je_suis[0]<taille_de_l_image -1){
        for (size_t i=0;i<MCU_a_parcourir_luminance;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}

        }
       
    free_mon_arbre(mon_arbre_luminance_AC);
    free_mon_arbre(mon_arbre_luminance_DC);
    free_mon_arbre(mon_arbre_chrominance_AC);
    free_mon_arbre(mon_arbre_chrominance_DC);
    return mon_image_decode;
}


int16_t*** decodage_en_couleur_ordre_BYR(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC){
    /*décodage pour un ordre chrominance bleue, luminance,chrominance rouge */
    int16_t*** mon_image_decode=calloc(3, sizeof(int16_t**));
    int16_t** luminance = calloc(nb_cellules_Y, sizeof(int16_t*));
    int16_t** chrominance_bleu = calloc(nb_cellules_Cb, sizeof(int16_t*));
    int16_t** chrominance_rouge = calloc(nb_cellules_Cr, sizeof(int16_t*));
    mon_image_decode[0]=luminance;
    mon_image_decode[1]=chrominance_bleu;
    mon_image_decode[2]=chrominance_rouge;
    size_t indice_dans_bloc_luminance=0;
    size_t indice_dans_bloc_chrominance_bleue=0;
    size_t indice_dans_bloc_chrominance_rouge=0;
    size_t MCU_a_parcourir_luminance=facteur_d_echantillonnage_luminence[0]*facteur_d_echantillonnage_luminence[1];
    size_t MCU_a_parcourir_chrominance_bleue=facteur_d_echantillonnage_bleu[0]*facteur_d_echantillonnage_bleu[1];
    size_t MCU_a_parcourir_chrominance_rouge=facteur_d_echantillonnage_rouge[0]*facteur_d_echantillonnage_rouge[1];
    size_t* la_ou_je_suis=calloc(4,sizeof(size_t));
    struct arbre* mon_arbre_luminance_AC=construit_arbre_bis(table_de_huffman_luminance_AC);
    struct arbre* mon_arbre_luminance_DC=construit_arbre_bis(table_de_huffman_luminance_DC);
    struct arbre* mon_arbre_chrominance_AC=construit_arbre_bis(table_de_huffman_chrominance_AC);
    struct arbre* mon_arbre_chrominance_DC=construit_arbre_bis(table_de_huffman_chrominance_DC);


    int16_t* premier_MCU_chrominance_bleue=calloc(64,sizeof(int));
    int16_t premier_coefficient_DC_chrominance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_bleue[0]=premier_coefficient_DC_chrominance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_bleue,mon_arbre_chrominance_AC);
    chrominance_bleu[indice_dans_bloc_chrominance_bleue]=premier_MCU_chrominance_bleue;
    indice_dans_bloc_chrominance_bleue+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue-1;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}


    int16_t* premier_MCU_luminance=calloc(64,sizeof(int16_t));
    int16_t premier_coefficient_DC_luminance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC);
    premier_MCU_luminance[0]=premier_coefficient_DC_luminance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_luminance,mon_arbre_luminance_AC);
    luminance[indice_dans_bloc_luminance]=premier_MCU_luminance;
    indice_dans_bloc_luminance+=1;

    for (size_t i=0;i<MCU_a_parcourir_luminance-1;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}

    int16_t* MCU_chrominance_rouge=calloc(64,sizeof(int16_t));
    int16_t coefficient_DC_chrominance_rouge=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    MCU_chrominance_rouge[0]=coefficient_DC_chrominance_rouge;
    decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge,mon_arbre_chrominance_AC);
    chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge;
    indice_dans_bloc_chrominance_rouge+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge-1;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}


    while (la_ou_je_suis[0]<taille_de_l_image -1){
        for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}

        for (size_t i=0;i<MCU_a_parcourir_luminance;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_chrominance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}
        }
   
    free_mon_arbre(mon_arbre_luminance_AC);
    free_mon_arbre(mon_arbre_luminance_DC);
    free_mon_arbre(mon_arbre_chrominance_AC);
    free_mon_arbre(mon_arbre_chrominance_DC);
    return mon_image_decode;
}

int16_t*** decodage_en_couleur_ordre_RYB(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC){
/*fonction décodant un bit stream en couleur dont les composantes sont ordonnées dans l'ordre suivant:chrominance rouge,luminance,chrominance bleue */
    int16_t*** mon_image_decode=calloc(3, sizeof(int16_t**));
    int16_t** luminance = calloc(nb_cellules_Y, sizeof(int16_t*));
    int16_t** chrominance_bleu = calloc(nb_cellules_Cb, sizeof(int16_t*));
    int16_t** chrominance_rouge = calloc(nb_cellules_Cr, sizeof(int16_t*));
    mon_image_decode[0]=luminance;
    mon_image_decode[1]=chrominance_bleu;
    mon_image_decode[2]=chrominance_rouge;
    size_t indice_dans_bloc_luminance=0;
    size_t indice_dans_bloc_chrominance_bleue=0;
    size_t indice_dans_bloc_chrominance_rouge=0;
    size_t MCU_a_parcourir_luminance=facteur_d_echantillonnage_luminence[0]*facteur_d_echantillonnage_luminence[1];
    size_t MCU_a_parcourir_chrominance_bleue=facteur_d_echantillonnage_bleu[0]*facteur_d_echantillonnage_bleu[1];
    size_t MCU_a_parcourir_chrominance_rouge=facteur_d_echantillonnage_rouge[0]*facteur_d_echantillonnage_rouge[1];
    size_t* la_ou_je_suis=calloc(4,sizeof(size_t));
    struct arbre* mon_arbre_luminance_AC=construit_arbre_bis(table_de_huffman_luminance_AC);
    struct arbre* mon_arbre_luminance_DC=construit_arbre_bis(table_de_huffman_luminance_DC);
    struct arbre* mon_arbre_chrominance_AC=construit_arbre_bis(table_de_huffman_chrominance_AC);
    struct arbre* mon_arbre_chrominance_DC=construit_arbre_bis(table_de_huffman_chrominance_DC);


    int16_t* premier_MCU_chrominance_rouge=calloc(64,sizeof(int));
    int16_t premier_coefficient_DC_chrominance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_rouge[0]=premier_coefficient_DC_chrominance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_rouge,mon_arbre_chrominance_AC);
    chrominance_rouge[indice_dans_bloc_chrominance_rouge]=premier_MCU_chrominance_rouge;
    indice_dans_bloc_chrominance_rouge+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge-1;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}


    int16_t* premier_MCU_luminance=calloc(64,sizeof(int16_t));
    int16_t premier_coefficient_DC_luminance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC);
    premier_MCU_luminance[0]=premier_coefficient_DC_luminance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_luminance,mon_arbre_luminance_AC);
    luminance[indice_dans_bloc_luminance]=premier_MCU_luminance;
    indice_dans_bloc_luminance+=1;

    for (size_t i=0;i<MCU_a_parcourir_luminance-1;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}


    int16_t* MCU_chrominance_bleue=calloc(64,sizeof(int16_t));
    int16_t coefficient_DC_chrominance_bleue=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    MCU_chrominance_bleue[0]=coefficient_DC_chrominance_bleue;
    decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue,mon_arbre_chrominance_AC);
    chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue;
    indice_dans_bloc_chrominance_bleue+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue-1;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}

    while (la_ou_je_suis[0]<taille_de_l_image -1){

        for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}

        for (size_t i=0;i<MCU_a_parcourir_luminance;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}
        }
  
    free_mon_arbre(mon_arbre_luminance_AC);
    free_mon_arbre(mon_arbre_luminance_DC);
    free_mon_arbre(mon_arbre_chrominance_AC);
    free_mon_arbre(mon_arbre_chrominance_DC);
    return mon_image_decode;
}

int16_t*** decodage_en_couleur_ordre_RBY(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC){
    /*decode le bit stream dont les ciomposantes respecte l'ordre suivant : chrominance rouge,chrominance bleue,luminance*/
    int16_t*** mon_image_decode=calloc(3, sizeof(int16_t**));
    int16_t** luminance = calloc(nb_cellules_Y, sizeof(int16_t*));
    int16_t** chrominance_bleu = calloc(nb_cellules_Cb, sizeof(int16_t*));
    int16_t** chrominance_rouge = calloc(nb_cellules_Cr, sizeof(int16_t*));
    mon_image_decode[0]=luminance;
    mon_image_decode[1]=chrominance_bleu;
    mon_image_decode[2]=chrominance_rouge;
    size_t indice_dans_bloc_luminance=0;
    size_t indice_dans_bloc_chrominance_bleue=0;
    size_t indice_dans_bloc_chrominance_rouge=0;
    size_t MCU_a_parcourir_luminance=facteur_d_echantillonnage_luminence[0]*facteur_d_echantillonnage_luminence[1];
    size_t MCU_a_parcourir_chrominance_bleue=facteur_d_echantillonnage_bleu[0]*facteur_d_echantillonnage_bleu[1];
    size_t MCU_a_parcourir_chrominance_rouge=facteur_d_echantillonnage_rouge[0]*facteur_d_echantillonnage_rouge[1];
    size_t* la_ou_je_suis=calloc(4,sizeof(size_t));
    struct arbre* mon_arbre_luminance_AC=construit_arbre_bis(table_de_huffman_luminance_AC);
    struct arbre* mon_arbre_luminance_DC=construit_arbre_bis(table_de_huffman_luminance_DC);
    struct arbre* mon_arbre_chrominance_AC=construit_arbre_bis(table_de_huffman_chrominance_AC);
    struct arbre* mon_arbre_chrominance_DC=construit_arbre_bis(table_de_huffman_chrominance_DC);


    int16_t* premier_MCU_chrominance_rouge=calloc(64,sizeof(int));
    int16_t premier_coefficient_DC_chrominance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_rouge[0]=premier_coefficient_DC_chrominance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_rouge,mon_arbre_chrominance_AC);
    chrominance_rouge[indice_dans_bloc_chrominance_rouge]=premier_MCU_chrominance_rouge;
    indice_dans_bloc_chrominance_rouge+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge-1;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}


    int16_t* premier_MCU_chrominance_bleue=calloc(64,sizeof(int16_t));
    int16_t coefficient_DC_chrominance_bleue=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_bleue[0]=coefficient_DC_chrominance_bleue;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_bleue,mon_arbre_chrominance_AC);
    chrominance_bleu[indice_dans_bloc_chrominance_bleue]=premier_MCU_chrominance_bleue;
    indice_dans_bloc_chrominance_bleue+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue-1;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}


    int16_t* premier_MCU_luminance=calloc(64,sizeof(int16_t));
    int16_t premier_coefficient_DC_luminance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC);
    premier_MCU_luminance[0]=premier_coefficient_DC_luminance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_luminance,mon_arbre_luminance_AC);
    luminance[indice_dans_bloc_luminance]=premier_MCU_luminance;
    indice_dans_bloc_luminance+=1;

    for (size_t i=0;i<MCU_a_parcourir_luminance-1;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}


    while (la_ou_je_suis[0]<taille_de_l_image -1){
        for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}

        for (size_t i=0;i<MCU_a_parcourir_luminance;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}
        }
      
    free_mon_arbre(mon_arbre_luminance_AC);
    free_mon_arbre(mon_arbre_luminance_DC);
    free_mon_arbre(mon_arbre_chrominance_AC);
    free_mon_arbre(mon_arbre_chrominance_DC);
    return mon_image_decode;
}

int16_t*** decodage_en_couleur_ordre_BRY(uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC){
    /*decodage du bitstream dont les composantes suivent l'ordre chrominance bleue,chrominance rouge et luminance*/
    int16_t*** mon_image_decode=calloc(3, sizeof(int16_t**));
    int16_t** luminance = calloc(nb_cellules_Y, sizeof(int16_t*));
    int16_t** chrominance_bleu = calloc(nb_cellules_Cb, sizeof(int16_t*));
    int16_t** chrominance_rouge = calloc(nb_cellules_Cr, sizeof(int16_t*));
    mon_image_decode[0]=luminance;
    mon_image_decode[1]=chrominance_bleu;
    mon_image_decode[2]=chrominance_rouge;
    size_t indice_dans_bloc_luminance=0;
    size_t indice_dans_bloc_chrominance_bleue=0;
    size_t indice_dans_bloc_chrominance_rouge=0;
    size_t MCU_a_parcourir_luminance=facteur_d_echantillonnage_luminence[0]*facteur_d_echantillonnage_luminence[1];
    size_t MCU_a_parcourir_chrominance_bleue=facteur_d_echantillonnage_bleu[0]*facteur_d_echantillonnage_bleu[1];
    size_t MCU_a_parcourir_chrominance_rouge=facteur_d_echantillonnage_rouge[0]*facteur_d_echantillonnage_rouge[1];
    size_t* la_ou_je_suis=calloc(4,sizeof(size_t));
    struct arbre* mon_arbre_luminance_AC=construit_arbre_bis(table_de_huffman_luminance_AC);
    struct arbre* mon_arbre_luminance_DC=construit_arbre_bis(table_de_huffman_luminance_DC);
    struct arbre* mon_arbre_chrominance_AC=construit_arbre_bis(table_de_huffman_chrominance_AC);
    struct arbre* mon_arbre_chrominance_DC=construit_arbre_bis(table_de_huffman_chrominance_DC);


    int16_t* premier_MCU_chrominance_bleue=calloc(64,sizeof(int));
    int16_t premier_coefficient_DC_chrominance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_bleue[0]=premier_coefficient_DC_chrominance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_bleue,mon_arbre_chrominance_AC);
    chrominance_bleu[indice_dans_bloc_chrominance_bleue]=premier_MCU_chrominance_bleue;
    indice_dans_bloc_chrominance_bleue+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue-1;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}


    int16_t* premier_MCU_chrominance_rouge=calloc(64,sizeof(int16_t));
    int16_t coefficient_DC_chrominance_rouge=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC);
    premier_MCU_chrominance_rouge[0]=coefficient_DC_chrominance_rouge;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_chrominance_rouge,mon_arbre_chrominance_AC);
    chrominance_rouge[indice_dans_bloc_chrominance_rouge]=premier_MCU_chrominance_rouge;
    indice_dans_bloc_chrominance_rouge+=1;

    for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge-1;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}

    int16_t* premier_MCU_luminance=calloc(64,sizeof(int16_t));
    int16_t premier_coefficient_DC_luminance=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC);
    premier_MCU_luminance[0]=premier_coefficient_DC_luminance;
    decodage_RLE(image_a_decoder,la_ou_je_suis,premier_MCU_luminance,mon_arbre_luminance_AC);
    luminance[indice_dans_bloc_luminance]=premier_MCU_luminance;
    indice_dans_bloc_luminance+=1;

    for (size_t i=0;i<MCU_a_parcourir_luminance-1;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}


    while (la_ou_je_suis[0]<taille_de_l_image -1){
        for (size_t i=0;i<MCU_a_parcourir_chrominance_bleue;i++){
        int16_t* MCU_chrominance_bleue_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_bleue=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_bleu[indice_dans_bloc_chrominance_bleue-1][0]);
        MCU_chrominance_bleue_suiv[0]=coefficient_DC_chrominance_bleue;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_bleue_suiv,mon_arbre_chrominance_AC);
        chrominance_bleu[indice_dans_bloc_chrominance_bleue]=MCU_chrominance_bleue_suiv;
        indice_dans_bloc_chrominance_bleue+=1;}

        for (size_t i=0;i<MCU_a_parcourir_chrominance_rouge;i++){
        int16_t* MCU_chrominance_rouge_suiv=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_chrominance_rouge=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_chrominance_DC,chrominance_rouge[indice_dans_bloc_chrominance_rouge-1][0]);
        MCU_chrominance_rouge_suiv[0]=coefficient_DC_chrominance_rouge;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_chrominance_rouge_suiv,mon_arbre_chrominance_AC);
        chrominance_rouge[indice_dans_bloc_chrominance_rouge]=MCU_chrominance_rouge_suiv;
        indice_dans_bloc_chrominance_rouge+=1;}

        for (size_t i=0;i<MCU_a_parcourir_luminance;i++){
        int16_t* MCU_suivant_luminance=calloc(64,sizeof(int16_t));
        int16_t coefficient_DC_luminance_suivant=decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis,mon_arbre_luminance_DC,luminance[indice_dans_bloc_luminance-1][0]);
        MCU_suivant_luminance[0]=coefficient_DC_luminance_suivant;
        decodage_RLE(image_a_decoder,la_ou_je_suis,MCU_suivant_luminance,mon_arbre_luminance_AC);
        luminance[indice_dans_bloc_luminance]=MCU_suivant_luminance;
        indice_dans_bloc_luminance+=1;}
        }
    
    free_mon_arbre(mon_arbre_luminance_AC);
    free_mon_arbre(mon_arbre_luminance_DC);
    free_mon_arbre(mon_arbre_chrominance_AC);
    free_mon_arbre(mon_arbre_chrominance_DC);
    return mon_image_decode;
}

int16_t*** decodage_totale_couleur(char* fichier_considere,uint8_t* image_a_decoder,size_t nb_cellules_Y, size_t nb_cellules_Cb, size_t nb_cellules_Cr, size_t taille_de_l_image,size_t* facteur_d_echantillonnage_luminence,size_t* facteur_d_echantillonnage_bleu,size_t* facteur_d_echantillonnage_rouge,uint8_t* table_de_huffman_luminance_DC,uint8_t* table_de_huffman_luminance_AC,uint8_t* table_de_huffman_chrominance_DC,uint8_t* table_de_huffman_chrominance_AC){
/*une fonction qui decode des images en couleur quelque soit l'ordre des composantes Y,Cb,Cr.Pour cela on regarde l'indice ic de chacune des composantes fournies par la section SOF et l'ordre des indices dans l'image fournit par la section SOS*/
uint8_t* mon_tableau=recupere_information_sur_limage(fichier_considere);
uint8_t indice_Y = mon_tableau[6];
uint8_t indice_Cb=mon_tableau[9];
free(mon_tableau);
uint8_t* mon_autre_tableau=recupere_SOS(fichier_considere);
uint8_t premier =mon_autre_tableau[1];
uint8_t second =mon_autre_tableau[3];
free(mon_autre_tableau);
if (premier==indice_Y){
    if (second==indice_Cb){
        return decodage_en_couleur_ordre_normale(image_a_decoder,nb_cellules_Y,nb_cellules_Cb,nb_cellules_Cr,taille_de_l_image,facteur_d_echantillonnage_luminence,facteur_d_echantillonnage_bleu,facteur_d_echantillonnage_rouge,table_de_huffman_luminance_DC,table_de_huffman_luminance_AC,table_de_huffman_chrominance_DC,table_de_huffman_chrominance_AC);
    }
    else{
        return decodage_couleur_ordre_YRB(image_a_decoder,nb_cellules_Y,nb_cellules_Cb,nb_cellules_Cr,taille_de_l_image,facteur_d_echantillonnage_luminence,facteur_d_echantillonnage_bleu,facteur_d_echantillonnage_rouge,table_de_huffman_luminance_DC,table_de_huffman_luminance_AC,table_de_huffman_chrominance_DC,table_de_huffman_chrominance_AC);
    }
}
else if (premier==indice_Cb){
    if (second==indice_Y){
        return decodage_en_couleur_ordre_BYR(image_a_decoder,nb_cellules_Y,nb_cellules_Cb,nb_cellules_Cr,taille_de_l_image,facteur_d_echantillonnage_luminence,facteur_d_echantillonnage_bleu,facteur_d_echantillonnage_rouge,table_de_huffman_luminance_DC,table_de_huffman_luminance_AC,table_de_huffman_chrominance_DC,table_de_huffman_chrominance_AC);
    }
    else{
        return decodage_en_couleur_ordre_BRY(image_a_decoder,nb_cellules_Y,nb_cellules_Cb,nb_cellules_Cr,taille_de_l_image,facteur_d_echantillonnage_luminence,facteur_d_echantillonnage_bleu,facteur_d_echantillonnage_rouge,table_de_huffman_luminance_DC,table_de_huffman_luminance_AC,table_de_huffman_chrominance_DC,table_de_huffman_chrominance_AC);
    }
}
else{
    if (second==indice_Y){
        return decodage_en_couleur_ordre_RYB(image_a_decoder,nb_cellules_Y,nb_cellules_Cb,nb_cellules_Cr,taille_de_l_image,facteur_d_echantillonnage_luminence,facteur_d_echantillonnage_bleu,facteur_d_echantillonnage_rouge,table_de_huffman_luminance_DC,table_de_huffman_luminance_AC,table_de_huffman_chrominance_DC,table_de_huffman_chrominance_AC);
    }
    else{
        return decodage_en_couleur_ordre_RBY(image_a_decoder,nb_cellules_Y,nb_cellules_Cb,nb_cellules_Cr,taille_de_l_image,facteur_d_echantillonnage_luminence,facteur_d_echantillonnage_bleu,facteur_d_echantillonnage_rouge,table_de_huffman_luminance_DC,table_de_huffman_luminance_AC,table_de_huffman_chrominance_DC,table_de_huffman_chrominance_AC);
    }
}

}



int16_t** decodage_complet(uint8_t* image_a_decoder, size_t nombre_de_cellule, size_t taille_de_l_image, uint8_t* table_de_Huffman_DC, uint8_t* table_de_Huffman_AC){
    /*une fonction pour décoder n'importe quelle image en gris suivant le même principe que l'image en couleurs mais retournant un tableu contenant uniquement les differents blocs de Y*/
    size_t indice_du_bloc=0;
    size_t* la_ou_je_suis_dans_le_bit=calloc(4,sizeof(size_t));
    int16_t** mon_image_decode=calloc(nombre_de_cellule,sizeof(int16_t*));
    int16_t* mon_premier_MCU=calloc(64,sizeof(int16_t));
    struct arbre* mon_arbre_Huffman_DC=construit_arbre_bis(table_de_Huffman_DC);
    struct arbre* mon_arbre_Huffman_AC=construit_arbre_bis(table_de_Huffman_AC);

    int16_t premier_coefficient_DC_decode=decodage_DC_premiere_MCU(image_a_decoder,la_ou_je_suis_dans_le_bit,mon_arbre_Huffman_DC);
    mon_premier_MCU[0] = premier_coefficient_DC_decode;
    decodage_RLE(image_a_decoder,la_ou_je_suis_dans_le_bit,mon_premier_MCU,mon_arbre_Huffman_AC);
    mon_image_decode[0] = mon_premier_MCU;
    indice_du_bloc += 1;

    while (la_ou_je_suis_dans_le_bit[0] < taille_de_l_image - 1){
        int16_t* mon_autre_MCU=calloc(64,sizeof(int16_t));
        int16_t mon_autre_composante_DC =decodage_DC_suivant_MCU(image_a_decoder,la_ou_je_suis_dans_le_bit,mon_arbre_Huffman_DC,mon_image_decode[indice_du_bloc-1][0]);
        mon_autre_MCU[0] = mon_autre_composante_DC;
        decodage_RLE(image_a_decoder,la_ou_je_suis_dans_le_bit,mon_autre_MCU,mon_arbre_Huffman_AC);
        mon_image_decode[indice_du_bloc]=mon_autre_MCU;
        indice_du_bloc+=1;
    }
    
    free_mon_arbre(mon_arbre_Huffman_DC);
    free_mon_arbre(mon_arbre_Huffman_AC);
    free(la_ou_je_suis_dans_le_bit);
    return mon_image_decode;
}

void place_dans_le_vecteur(int16_t** vecteur_de_decodage_complet,struct data_1* mon_vecteur){
    mon_vecteur->vect_fin_rle_et_qz[0]=vecteur_de_decodage_complet;
}




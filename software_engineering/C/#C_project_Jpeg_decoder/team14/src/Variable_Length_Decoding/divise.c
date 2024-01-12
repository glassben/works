/*#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>*/
#include "../../include/module_matriciel.h"
void est_un_jpeg(char* fichier_considere){
    /* une fonction qui verifie que le fichier est bien de la forme voulue pour pouvoir être décodé*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[2];
    fread(chaine,1,2,fichier_test);
    /*on vérifie déjà qu'il s'agit bien d'une image jpeg*/
    if (chaine[0]!=0xff || chaine[1]!=0xd8){
        printf("n'est pas un fichier JPEG. Ne traite pas ce cas.Au revoir \n");
        exit(EXIT_FAILURE);
    }
    fread(chaine,1,2,fichier_test);
    fread(chaine,1,2,fichier_test);
    uint8_t tab2[5];
    fread(tab2,1,5,fichier_test);
    /*on vérifie qu'il s'agit du format JFIF*/
    if (tab2[0]!=0x4a || tab2[1]!=0x46 || tab2[2]!=0x49 || tab2[3]!=0x46 || tab2[4]!=0x00){
        printf("le fichier n'est pas un JFIF.Ne traite pas ce cas.Au revoir \n");
        fclose(fichier_test);
        exit(EXIT_FAILURE);
    }
    /*on vérifie qu'il est bien à la version 1.1*/
    fread(chaine,1,2,fichier_test);
    if (chaine[0]!=0x01 ||  chaine[1]!=0x01){
        printf("le fichier n'est pas de la bonne version.Ne traite pas ce cas.Au revoir \n");
        fclose(fichier_test);
        exit(EXIT_FAILURE);
    }
    fclose(fichier_test);
}


size_t calcule_longueur_premiere_table_de_huffman(char* fichier_considere){
    /*une fonction qui calcule la longueur de la première table de Huffmann d'une section contenant plusieurs tables*/
     FILE* fichier_test=fopen(fichier_considere,"r");
     size_t nb=0;
        uint8_t chaine[1];
        while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                fread(chaine,1,1,fichier_test);
                uint8_t tab[16];
                fread(tab,1,16,fichier_test);
                for (int i=0;i<16;i++){
                    nb+=tab[i];
                }
                fclose(fichier_test);
                return nb+17;
            }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                fclose(fichier_test);
                printf("table de Huffmann AC non trouvé");
                exit(EXIT_FAILURE);
            }
        }
    }
}

size_t calcule_longueur_seconde_table_de_huffman(char* fichier_considere){
    /*une fonction qui calcule la longueur de la seconde table de Huffmann d'une section contenant plusieurs tables*/
     FILE* fichier_test=fopen(fichier_considere,"r");
     size_t longueur=calcule_longueur_premiere_table_de_huffman(fichier_considere);
     size_t nb=0;
        uint8_t chaine[1];
        while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                uint8_t tab[longueur];
                fread(tab,1,longueur,fichier_test);

                fread(chaine,1,1,fichier_test);
                uint8_t tab2[16];
                fread(tab2,1,16,fichier_test);
                for (int i=0;i<16;i++){
                    nb+=tab2[i];
                }
                fclose(fichier_test);
                return nb+17;

            }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                printf("table de Huffmann AC non trouvé");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
            }
        }
    }
}

size_t calcule_longueur_troisième_table_Huffman(char* fichier_considere){
    /*une fonction qui calcule la longueur de la troisième table de Huffmann d'une section contennat plusieurs tables*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    size_t longueur_premiere = calcule_longueur_premiere_table_de_huffman(fichier_considere);
    size_t longueur_deuxieme = calcule_longueur_seconde_table_de_huffman(fichier_considere);
    size_t nb=0;
    uint8_t chaine[1];
    while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                uint8_t tab[longueur_premiere];
                fread(tab,1,longueur_premiere,fichier_test);

                uint8_t tab2[longueur_deuxieme];
                fread(tab2,1,longueur_deuxieme,fichier_test);

                fread(chaine,1,1,fichier_test);
                uint8_t tab3[16];
                fread(tab3,1,16,fichier_test);
                for (int i=0;i<16;i++){
                    nb+=tab3[i];
                }
                fclose(fichier_test);
                return nb+17;}
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                printf("table de Huffmann AC non trouvé");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
            }
        }
    }
}


size_t calcule_longueur_quatrième_table_Huffman(char* fichier_considere){
    /*une fonction qui calcule la longueur de la quatrième table de Huffmann contenu dans une section contenant plusieurs table de Huffmann*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    size_t longueur_premiere = calcule_longueur_premiere_table_de_huffman(fichier_considere);
    size_t longueur_deuxieme = calcule_longueur_seconde_table_de_huffman(fichier_considere);
    size_t longueur_troisième = calcule_longueur_troisième_table_Huffman(fichier_considere);
    size_t nb=0;
    uint8_t chaine[1];
    while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){

                uint8_t table[2];
                fread(table,1,2,fichier_test);
                uint8_t tab[longueur_premiere];
                fread(tab,1,longueur_premiere,fichier_test);

                uint8_t tab2[longueur_deuxieme];
                fread(tab2,1,longueur_deuxieme,fichier_test);

                uint8_t tab3[longueur_troisième];
                fread(tab3,1,longueur_troisième,fichier_test);

                fread(chaine,1,1,fichier_test);
                uint8_t tab4[16];
                fread(tab4,1,16,fichier_test);

                for (int i=0;i<16;i++){
                    nb+=tab4[i];}
                    fclose(fichier_test);
                    return 17+nb;
                }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                printf("table de Huffmann AC non trouvé");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
            }
        }
    }
}



uint8_t* recupere_huffman_DC(char* fichier_considere){
    /*recupere la table de Hauffmann des composantes AC*/
        FILE* fichier_test=fopen(fichier_considere,"r");
        uint8_t chaine[1];
        while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                size_t longueur=calcule_longueur_premiere_table_de_huffman(fichier_considere);
                uint8_t* tab=calloc(longueur,sizeof(uint8_t));
                fread(tab,1,longueur,fichier_test);
                fclose(fichier_test);
                return tab;
            }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                printf("table de Huffmann AC non trouvé");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
            }
        }
    }
}

uint8_t* recupere_huffman_AC(char* fichier_considere){
    /*recupere la table de Hauffmann pour les composantes DC*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while(true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
            uint8_t table[2];
            fread(table,1,2,fichier_test);
            int taille =(table[0]*256+table[1]-2);

            int taille1=calcule_longueur_premiere_table_de_huffman(fichier_considere);
            uint8_t table2[taille1];
            fread(table2,1,taille1,fichier_test);

            if (taille-taille1 >0){
/*ici on examine le cas où la section contient la table de hauffmann AC dans la même section */
                size_t taille2=calcule_longueur_seconde_table_de_huffman(fichier_considere);
                uint8_t* tab=calloc(taille2,sizeof(uint8_t));
                fread(tab,1,taille2,fichier_test);
                fclose(fichier_test);
                return tab;}
/* dans le cas où la section ne contient qu'une seule table on passe à la section suivante */
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xff){
                fread(chaine,1,1,fichier_test);
                if (chaine[0]==0xc4){
                        fread(table,1,2,fichier_test);
                        int taille2=(table[0]*256+table[1]-2);
                        uint8_t* tab=calloc(taille2,sizeof(uint8_t));
                        fread(tab,1,taille2,fichier_test);
                        fclose(fichier_test);
                        return tab;
                    }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                    if (chaine[0]==0xda){
                    printf("table de Huffmann AC non trouvé ou étant contenu dans la table de Huffmann précédente qu'on ne sait pas traité.FIN du programme ");
                    fclose(fichier_test);
                    exit(EXIT_FAILURE);
                    }
                }
            } 
        }
    }
}

uint8_t* recupere_huffman_DC_chrominance(char* fichier_considere){
    /*une fonction qui recupere la table de Huffmann DC des composantes de chrominance en tenant compte du cas où toutes les tanbles sont regroupés dans la même composante*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while(true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
            uint8_t table[2];
            fread(table,1,2,fichier_test);
            int taille =(table[0]*256+table[1]-2);
            size_t longueur1=calcule_longueur_premiere_table_de_huffman(fichier_considere);
            uint8_t table2[longueur1];
            fread(table2,1,longueur1,fichier_test);
/*on examine le cas où la section contient plusieurs tables*/
            if (taille-longueur1 >0){
                size_t longueur2=calcule_longueur_seconde_table_de_huffman(fichier_considere);
                uint8_t table3[longueur2];
                fread(table3,1,longueur2,fichier_test);

                if (taille-longueur1-longueur2>0){
                    size_t longueur3=calcule_longueur_troisième_table_Huffman(fichier_considere);
                    uint8_t* tab3=calloc(longueur3,sizeof(uint8_t));
                    fread(tab3,1,longueur3,fichier_test);
                    fclose(fichier_test);
                    return tab3;
                }
            }
/*dans le cas négatif,on passe à la section suivante */
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xff){
                fread(chaine,1,1,fichier_test);
                if (chaine[0]==0xc4){
                        fread(table,1,2,fichier_test);
                        int taille2=(table[0]*256+table[1]-2);
                        uint8_t* tab[taille2];
                        fread(tab,1,taille2,fichier_test);

                        fread(chaine,1,1,fichier_test);
                        if (chaine[0]==0xff){
                            fread(chaine,1,1,fichier_test);
                            if (chaine[0]==0xc4){
                                fread(table,1,2,fichier_test);
                                int taille3=(table[0]*256+table[1]-2);
                                uint8_t* tab3=calloc(taille3,sizeof(uint8_t));
                                fread(tab3,1,taille3,fichier_test);
                                fclose(fichier_test);
                                return tab3;
                            }

                            if (chaine[0]==0xda){
                                printf("table de Huffmann chrominance DC non présente ou contenu dans la table précédente que le programme ne sait pas traiter.Fin du programme");
                                fclose(fichier_test);
                                exit(EXIT_FAILURE);
                            }
                        }
                    }
                if (chaine[0]==0xda){
                    printf("table de Huffmann chrominance DC non présente ou contenu dans la table précédente que le programme ne sait pas traiter.Fin du programme");
                    fclose(fichier_test);
                    exit(EXIT_FAILURE);
                    }
                }
            } 
        }
    }
}

uint8_t* recupere_huffman_AC_chrominance(char* fichier_considere){
    /*une fonction qui récupere la table de huffmann AC de la partie chrominance en prenant en compte le cas où les tables de Huffmann sont regroupés en une seule section*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while(true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc4){
            uint8_t table[2];
            fread(table,1,2,fichier_test);
            int taille =(table[0]*256+table[1]-2);
            size_t longueur1=calcule_longueur_premiere_table_de_huffman(fichier_considere);
            uint8_t table2[longueur1];
            fread(table2,1,longueur1,fichier_test);
/*on examine le cas où la section possède plusieurs tables*/
            if (taille-longueur1>0){
                size_t longueur2=calcule_longueur_seconde_table_de_huffman(fichier_considere);
                uint8_t table3[longueur2];
                fread(table3,1,longueur2,fichier_test);

                if (taille-longueur1-longueur2>0){
                    size_t longueur3=calcule_longueur_troisième_table_Huffman(fichier_considere);
                    uint8_t table4[longueur3];
                    fread(table4,1,longueur3,fichier_test);

                    if (taille-longueur1-longueur2-longueur3>0){
                        size_t longueur4=calcule_longueur_quatrième_table_Huffman(fichier_considere);
                        uint8_t* table5=calloc(longueur4,sizeof(uint8_t));
                        fread(table5,1,longueur4,fichier_test);
                        fclose(fichier_test);
                        return table5;
                    }
                }
            }
/* dans le cas négatif on accède aux sections suivantes*/
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xff){
                fread(chaine,1,1,fichier_test);
                if (chaine[0]==0xc4){
                        fread(table,1,2,fichier_test);
                        int taille2=(table[0]*256+table[1]-2);
                        uint8_t* tab[taille2];
                        fread(tab,1,taille2,fichier_test);

                        fread(chaine,1,1,fichier_test);
                        if (chaine[0]==0xff){
                            fread(chaine,1,1,fichier_test);
                            if (chaine[0]==0xc4){
                                fread(table,1,2,fichier_test);
                                int taille3=(table[0]*256+table[1]-2);
                                uint8_t* tab3[taille3];
                                fread(tab3,1,taille3,fichier_test);

                                fread(chaine,1,1,fichier_test);
                                if (chaine[0]==0xff){
                                    fread(chaine,1,1,fichier_test);
                                    if (chaine[0]==0xc4){
                                        fread(table,1,2,fichier_test);
                                        int taille4=(table[0]*256+table[1]-2);
                                        uint8_t* tab4=calloc(taille4,sizeof(uint8_t));
                                        fread(tab4,1,taille4,fichier_test);
                                        fclose(fichier_test);
                                        return tab4;
                                    }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                                    if (chaine[0]==0xda){
                                        printf("table de Huffmann chrominance DC non présente ou contenu dans la table précédente que le programme ne sait pas traiter.Fin du programme");
                                        fclose(fichier_test);
                                        exit(EXIT_FAILURE);}
                                }
                            }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                            if (chaine[0]==0xda){
                                printf("table de Huffmann chrominance DC non présente ou contenu dans la table précédente que le programme ne sait pas traiter.Fin du programme");
                                fclose(fichier_test);
                                exit(EXIT_FAILURE);}
                        }
                    }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                    if (chaine[0]==0xda){
                        printf("table de Huffmann chrominance DC non présente ou contenu dans la table précédente que le programme ne sait pas traiter.Fin du programme");
                        fclose(fichier_test);
                        exit(EXIT_FAILURE);}
                }
            } 
        }
    }
}

uint8_t* recupere_information_sur_limage(char* fichier_considere){
    /*récupere information du Start of Frame */
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if(chaine[0]==0xc0){
                uint8_t ma_chaine[2];
                fread(ma_chaine,1,2,fichier_test);
                int taille = (256*ma_chaine[0]+ ma_chaine[1]-2);
                uint8_t* tab=calloc(taille,sizeof(uint8_t));
                fread(tab,1,taille,fichier_test);
                fclose(fichier_test);
                return tab;
                }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                 if (chaine[0]==0xda){
                    printf("section SOF non trouvé.FIN du programme");
                    fclose(fichier_test);
                    exit(EXIT_FAILURE);}
            }
        }
    }


uint8_t* recupere_quantification_luminance(char* fichier_considere){
    /* recupère la matrice de quantification pour la luminance */
    FILE* fichier_test =fopen(fichier_considere,"r");
    uint8_t chaine[1];
    uint8_t* mon_tableau=recupere_information_sur_limage(fichier_considere);
    uint8_t indice_q= mon_tableau[8];
    free(mon_tableau);
    /*on s'assure qu'il s'agit bien de la table de quantification de luminance en regardant l'indice iq de la composante Y et en la comparant
    à l'indice iq présente dans la section de la table de luminance */
    while (true){

        fread(chaine,1,1,fichier_test);

        if (chaine[0]==0xff){

            fread(chaine,1,1,fichier_test);
            if(chaine[0]==0xdb){
                uint8_t table[2];
                fread(table,1,2,fichier_test);

                int taille=table[1]+256*table[0]-3;

                fread(chaine,1,1,fichier_test);
                /*on verifie que la précision est bien de 8 bits*/
                if (chaine[1]==1){
                    printf("Précision sur 16 bits.Cas non traité par ce convertisseur");
                    fclose(fichier_test);
                    exit(EXIT_FAILURE);
                }

                if ((chaine[0]&0b00001111)==indice_q){

                uint8_t* tab=calloc(64,sizeof(uint8_t));

                fread(tab,1,64,fichier_test);

                fclose(fichier_test);

                return tab;}
            /* si la table de quantification ne correspond pas à celle de la luminance on explore les autres tables */
                else if (taille-64>0){
                    /*si la section contient plus d'une table de quantification */
                    uint8_t table2[64];
                    fread(table2,1,64,fichier_test);
                    fread(chaine,1,1,fichier_test);
                    uint8_t* tab=calloc(64,sizeof(uint8_t));
                    fread(tab,1,64,fichier_test);
                    fclose(fichier_test);
                    return tab;}
                else{
                    /*si la table suivante se trouve dans une autre section on passe à la section suivante*/
                    uint8_t table2[64];
                    fread(table2,1,64,fichier_test);
                    fread(chaine,1,1,fichier_test);
                    if (chaine[0]==0xff){
                        fread(chaine,1,1,fichier_test);
                        if (chaine[0]==0xdb){
                            fread(table,1,2,fichier_test);
                            fread(chaine,1,1,fichier_test);
                            uint8_t* tab=calloc(64,sizeof(uint8_t));
                            fread(tab,1,64,fichier_test);
                            fclose(fichier_test);
                            return tab;
                        }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                        if (chaine[0]==0xda){
                            printf("table de quantification non trouvée.FIN du programme");
                            fclose(fichier_test);
                            exit(EXIT_FAILURE);
                        }
                    }

                }
            }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                printf("table de quantification non trouvée.FIN du programme");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
        }
     }
    }
}
uint8_t* recupere_quantification_chrominance(char* fichier_considere){
    /*récupere la matrice de quantification pour la chrominance*/
    FILE* fichier_test =fopen(fichier_considere,"r");
    uint8_t chaine[1];
    uint8_t* mon_tableau=recupere_information_sur_limage(fichier_considere);
    uint8_t indice_q= mon_tableau[11];
    free(mon_tableau);
/*on s'assure également ici de bien récupérer la table de quantification de chrominance en comparant l'indice de quantification des chrominances 
avec celui de la section de la table */
    while (true){

        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xdb){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                int taille=table[1]+table[0]*256-3;
                fread(chaine,1,1,fichier_test);

                if (chaine[0]==indice_q){
                    uint8_t* tab=malloc(64*sizeof(uint8_t));
                    fread(tab,1,64,fichier_test);
                    fclose(fichier_test);
                    return tab;}

                else if (taille-64>0){
                    uint8_t* tab=calloc(64,sizeof(uint8_t));
                    fread(tab,1,64,fichier_test);
                    fread(chaine,1,1,fichier_test);
                    fread(tab,1,64,fichier_test);
                    fclose(fichier_test);
                    return tab;
                }

                else{
                uint8_t tab[64];
                fread(tab,1,64,fichier_test);     
                fread(chaine,1,1,fichier_test);
                if (chaine[0]==0xff){
                    fread(chaine,1,1,fichier_test);
                    if (chaine[0]==0xdb){
                        fread(table,1,2,fichier_test);
                        int taille2=table[1]+table[0]*256-3;
                        fread(chaine,1,1,fichier_test);
                        uint8_t* tab2=calloc(taille2,sizeof(uint8_t));
                        fread(tab2,1,taille2,fichier_test);
                        fclose(fichier_test);
                        return tab2;
                    }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
                if (chaine[0]==0xda){
                printf("table de quantification non trouvée.FIN du programme");
                fclose(fichier_test);
                exit(EXIT_FAILURE);}

                }
            }
        }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */ 
        if (chaine[0]==0xda){
            printf("table de quantification non trouvée.FIN du programme");
            fclose(fichier_test);
            exit(EXIT_FAILURE);}
        }
    }
}



uint8_t* recupere_composante(char* fichier_considere,size_t nbr_d_octet){
    /*recupere les nbr_d_octet octets des données brutes de l'image  */
    FILE* fichier_test =fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xda){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                uint8_t taille=table[0]*256+table[1]-2;
                uint8_t tab[taille];
                fread(tab,1,taille,fichier_test);
                uint8_t* tab2=calloc(nbr_d_octet,sizeof(uint8_t));
                fread(tab2,1,nbr_d_octet,fichier_test);
                fclose(fichier_test);
                return tab2;}
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
            if (chaine[0]==0xda){
                printf("les données brutes de l'image n'ont pas été trouvées.FIN du programme");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
            }
        }
    }
}

int recupere_longueur_image(char* fichier_considere){
    /* une fonction qui recupère la longueur des données brutes en la parcourant*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xda){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                uint8_t taille=table[0]*256+table[1]-2;
                uint8_t tab[taille];
                fread(tab,1,taille,fichier_test);
                int s=0;
                while(true){
                    fread(chaine,1,1,fichier_test);
                    if (chaine[0]==0xff){
                        s+=1;
                        fread(chaine,1,1,fichier_test);
                        if (chaine[0]==0xd9){
                            fclose(fichier_test);
                            return s-1;
                        }
                    }
                s+=1;
                }    
            }
        }
    }
}

size_t* recupere_hauteur_et_longueur_pixel(char* fichier_considere,size_t dim_image[2]){
    /*recupere la hauteur et la longueur en pixel de l'image et le place dans un vecteur dim_image*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while(true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xc0){
                fread(chaine,1,1,fichier_test);
                uint8_t chaine2[2];
                fread(chaine2,1,2,fichier_test);
                dim_image[0]=chaine2[0]*256+chaine2[1];
                fread(chaine2,1,2,fichier_test);
                dim_image[1]=chaine2[0]*256+chaine2[1];
                fclose(fichier_test);
                return dim_image;
            }
 /* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la section SOS qui est la dernière section avant 
les données brutes, on retourne une erreur */
        if (chaine[0]==0xda){
            printf("section contenant hauteur et longueur des pixels non trouvée.FIN du programme");
            fclose(fichier_test);
            exit(EXIT_FAILURE);
            }
        }
    }
}

void recupere_dimension_et_couleur(char* fichier_considere,struct data_1* vecteur){
    /*une fonction qui recupère la dimension et l'information sur la couleur et la stocke dans le vecteur data_1 */
    uint8_t* information=recupere_information_sur_limage(fichier_considere);
    /*uint16_t longueur = 256*information[1] + information[2];
    uint16_t largeur = 256*information[3] + information[4];*/
    /*vecteur->dim_image[0]=information[1]*256+information[2];
    vecteur->dim_image[1]=information[3]*256+information[4];*/
    uint16_t longueur = 256*information[1] + information[2];
    uint16_t largeur = 256*information[3] + information[4];
    vecteur->dim_image[0] = longueur;
    vecteur->dim_image[1] = largeur;
    if (information[5]!=1){
        vecteur->couleurs=true;    
    
    vecteur -> param_sampling[0] = (uint8_t)((information[7]&0b11110000)/16);
    vecteur -> param_sampling[1] = (uint8_t)(information[7]&0b00001111);
    vecteur -> param_sampling[2] = (uint8_t)((information[10]&0b11110000)/16);
    vecteur -> param_sampling[3] = (uint8_t)(information[10]&0b00001111);
    vecteur -> param_sampling[4] = (uint8_t)((information[13]&0b11110000)/16);
    vecteur -> param_sampling[5] = (uint8_t)(information[13]&0b00001111);
    }
    else{
        vecteur->couleurs=false;
    }
    free(information);
}



uint8_t* recupere_SOS(char* fichier_considere){
    /*une fonction qui récupère la section SOS*/
    FILE* fichier_test=fopen(fichier_considere,"r");
    uint8_t chaine[1];
    while (true){
        fread(chaine,1,1,fichier_test);
        if (chaine[0]==0xff){
            fread(chaine,1,1,fichier_test);
            if (chaine[0]==0xda){
                uint8_t table[2];
                fread(table,1,2,fichier_test);
                uint8_t taille=table[0]*256+table[1]-2;
                uint8_t* tab=calloc(taille,sizeof(uint8_t));
                fread(tab,1,taille,fichier_test);
                fclose(fichier_test);
                return tab;
            }
/* dans le cas où on ne rencontre pas la section de la table et qu'on arrive au niveau de la fin de l'image ,on retourne une erreur */
            if (chaine[0]==0xd9){
                printf("la section Section SOS n'a pas été trouvée. FIN du programme");
                fclose(fichier_test);
                exit(EXIT_FAILURE);
            }
        }
    }
}




/*
int main(int argc,char** argv){
    char* fichier_considere=argv[1];
    est_un_jpeg(fichier_considere);
    return EXIT_SUCCESS;
}
*/

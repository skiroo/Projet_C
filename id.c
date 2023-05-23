/* Fichier source avec la définition de la fonction get_next_id() */

#include "id.h"

//Fonction qui permet de récupérer l'id d'une forme
unsigned int get_next_id()
{
    unsigned int tmp = global_id;
    global_id++;
    return tmp;
}

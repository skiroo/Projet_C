/* ===============Fichier principal===============
Fichier qui devra être lancée pour que le programme fonctionne */

#include "command.h"

int main()
{
    int result = 1, width, height;
    Command* cmd;

    //Saisie de la taille de la zone de dessin
    do {
        printf("Saisir la taille de votre zone de dessin (width height) :");
        scanf("%d %d", &width, &height);
    } while((width <= 0) || (height <= 0));

    //Création de la zone de dessin
    Area* draw_zone = create_area(width, height);
    while (result != 0)
    {
        cmd = create_commande();
        printf("\n- ");
        read_from_stdin(cmd);
        result = read_exec_command(cmd, draw_zone);
        if (result != 1)
        {
            printf("Erreur lors de l'execution de la commande.\n");
        }
        free_cmd(cmd);
    }

    return 0;
}

/* Fichier source avec définition des fonctions de commande servant à utiliser le programme */

#include "command.h"

//===============Command Functions===============

//Allouer en mémoire une variable de type Command* et l'initialiser
Command* create_commande()
{
    Command* cmd = malloc(sizeof(Command));
    strcpy (cmd->name, "");
    cmd->int_size = 0;
    cmd->str_size = 0;
    return cmd;
}

//Remplie le tableau de command str_param et incrémente str_size
void add_str_param (Command* cmd, char* p)
{
    if (cmd->str_size < 100)
    {
        cmd->str_params[cmd->str_size] = malloc(strlen(p) + 1);
        strcpy (cmd->str_params[cmd->str_size], p);
        cmd->str_size++;
    }
}

//Libérer l'espace mémoire de la commande
void free_cmd (Command* cmd)
{
    for (int i = 0; i < cmd->str_size; i++)
    {
        free (cmd->str_params[i]);
    }
    free (cmd);
}

//Remplie le tableau de donnee int_param et incrémente int_size
void add_int_param (Command* cmd, int p)
{
    if (cmd->int_size < 10)
    {
        cmd->int_params[cmd->int_size] = p;
        cmd->int_size++;
    }
}

//Lire la commande inscrit par l'utilisateur et l'extraire
int read_exec_command (Command* cmd, Area * area)
{
    printf ("Commande executee: %s\n", cmd->name);

    for (int i = 0; i < cmd->int_size; i++)
    {
        printf ("Parametre entier: %d\n", cmd->int_params[i]);
    }

    for (int i = 0; i < cmd->str_size; i++)
    {
        printf ("Parametre chaine: %s\n", cmd->str_params[i]);
    }

    if (strcmp (cmd->name, "clear") == 0)
    {
        clear_screen();
    }
    else if (strcmp (cmd->name, "exit") == 0)
    {
        return exit_program();
    }
    else if (strcmp (cmd->name, "point") == 0)
    {
        if (cmd->int_size == 2)
        {
            int x = cmd->int_params[0];
            int y = cmd->int_params[1];
            Shape * shape = create_point_shape (x, y);
            add_shape_to_area (area, shape);
        }
        else
        {
            printf ("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "line") == 0)
    {
        if (cmd->int_size == 4)
        {
            int x1 = cmd->int_params[0];
            int y1 = cmd->int_params[1];
            int x2 = cmd->int_params[2];
            int y2 = cmd->int_params[3];
            Shape * shape = create_line_shape (x1, y1, x2, y2);
            add_shape_to_area (area, shape);
        }
        else
        {
            printf("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "circle") == 0)
    {
        if (cmd->int_size == 3)
        {
            int x = cmd->int_params[0];
            int y = cmd->int_params[1];
            int radius = cmd->int_params[2];
            Shape * shape = create_circle_shape (x, y, radius);
            add_shape_to_area (area, shape);
        } else {
            printf("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "square") == 0)
    {
        if (cmd->int_size == 3)
        {
            int x = cmd->int_params[0];
            int y = cmd->int_params[1];
            int length = cmd->int_params[2];
            Shape * shape = create_square_shape (x, y, length);
            add_shape_to_area (area, shape);
        }
        else
        {
            printf("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "rectangle") == 0)
    {
        if (cmd->int_size == 4)
        {
            int x = cmd->int_params[0];
            int y = cmd->int_params[1];
            int width = cmd->int_params[2];
            int height = cmd->int_params[3];
            Shape * shape = create_rectangle_shape (x, y, width, height);
            add_shape_to_area (area, shape);
        }
        else
        {
            printf("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "polygon") == 0)
    {
        if (cmd->int_size >= 6 && cmd->int_size % 2 == 0)
        {
            int nb_points = cmd->int_size / 2;
            Point* points = (Point*) malloc(nb_points * sizeof(Point));
            for (int i = 0; i < cmd->int_size; i+=2)
            {
                points[i].pos_x = cmd->int_params[i];
                points[i].pos_y = cmd->int_params[i+1];
            }
            Shape * shape = create_polygon_shape(points, nb_points);
            add_shape_to_area (area, shape);
            //printf ("\nImpossible d'inserer un polygone.\n");
        }
        else
        {
            printf ("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "plot") == 0)
    {
        draw_area (area);
        print_area (area);
    }
    else if (strcmp (cmd->name, "list") == 0)
    {
        list_shapes (area);
    }
    else if (strcmp (cmd->name, "delete") == 0)
    {
        if (cmd->int_size == 1)
        {
            int id = cmd->int_params[0];
            supprimer_forme (area, id);
            draw_area (area);
        }
        else
        {
            printf ("\nErreur: Nombre de parametres incorrect pour la commande\n");
            return -1;
        }
    }
    else if (strcmp (cmd->name, "erase") == 0)
    {
        printf ("\nSuppression de toutes les formes geometriques\n");
        erase_area (area);
        clear_area (area);
    }
    else if (strcmp (cmd->name, "help") == 0)
    {
        show_help();
    }
    else
    {
        printf ("Erreur cmd\n");
        return -1;
    }
    return 1;
}

//Supprimer une forme de la zone de dessin
void supprimer_forme(Area * area, int id)
{
    if (id < 0 || id >= area->nb_shape)
    {
        printf ("Erreur: id invalide\n");
        return;
    }

    Shape* shape = area->shapes[id];
//  Supprimer la forme de la m�moire
    delete_shape (shape);

//  Decaler les formes suivantes dans le tableau
    for (int i = id; i < area->nb_shape - 1; i++)
    {
        area->shapes[i] = area->shapes[i + 1];
    }

    // Reduire le nombre de formes dans le tableau
    area->nb_shape--;
    printf ("Forme supprimee avec succes\n");
}

//Lire les donnée inscris pour les commandes
void read_from_stdin(Command* cmd)
{
    char input[50];
    fgets (input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    char* token = strtok(input, " ");
    if (token != NULL)
    {
        strcpy(cmd->name, token);

        while ((token = strtok(NULL, " ")) != NULL)
        {
            int int_param = atoi(token);
            if (int_param != 0)
            {
                add_int_param(cmd, int_param);
            } else {
                add_str_param(cmd, token);
            }
        }
    }
}

//Effacer l'ecran
void clear_screen(void)
{
    printf("Effacement de l'ecran...\n");
    system("cls"); // pour clear la console
    // Code pour effacer l'�cran
}

//Fermer le programme
int exit_program()
{
    printf("Fermeture du programme...\n");
    return 0;
}

//Afficher la liste des formes
void list_shapes(Area * area)
{
    printf("\nListe des formes geometriques:\n");
    if (area->nb_shape == 0) printf("Aucune forme enregistree!");
    else
    {
        for(int i = 0; i < area->nb_shape; i++)
        {
            Shape* shape = area->shapes[i];
            print_shape(shape, i);
            printf("\n");
        }
    }
}

//Afficher les commandes disponibles
void show_help()
{
    printf("\nListe des commandes:");
    printf("\n- clear (Effacer l'ecran)");
    printf("\n- exit (Quitter le programme)");
    printf("\n- point x y (Ajouter un point)");
    printf("\n- line x1 y1 x2 y2 (Ajouter une ligne)");
    printf("\n- circle x y r (Ajouter un cercle de centre (x,y) et de rayon r)");
    printf("\n- square x y l (Ajouter un carre avec le point gauche superieur (x,y) et de longueur l)");
    printf("\n- rectangle x y w h (Ajouter un rectangle avec le point gauche superieur (x,y), de longueur h et de largeur w)");
    printf("\n- polygone x1 y1 x2 y2 ... (Ajouter un polygone)");
    printf("\n- plot (Rafraichir l'ecran pour afficher toutes les formes geometriques de l'image)");
    printf("\n- list (Afficher les formes textuelles)");
    printf("\n- delete id (Supprimer une forme a partir de son identifiant id)");
    printf("\n- erase (Supprimer toutes les formes de l'image)");
    printf("\n- help (Afficher la liste des commandes et leur description)\n\n");
}

#include "command.h"


Command* create_commande()
{
    Command* cmd = malloc(sizeof(Command));
    strcpy (cmd->name, "");
    cmd->int_size = 0;
    cmd->str_size = 0;
    return cmd;
}

void add_str_param (Command* cmd, char* p)
{
    if (cmd->str_size < 100)
    {
        cmd->str_params[cmd->str_size] = malloc(strlen(p) + 1);
        strcpy (cmd->str_params[cmd->str_size], p);
        cmd->str_size++;
    }
}

void free_cmd (Command* cmd)
{
    for (int i = 0; i < cmd->str_size; i++)
    {
        free (cmd->str_params[i]);
    }
    free (cmd);
}


void add_int_param (Command* cmd, int p)
{
    if (cmd->int_size < 10)
    {
        cmd->int_params[cmd->int_size] = p;
        cmd->int_size++;
    }
}

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
        exit_program();
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
            int num_points = cmd->int_size / 2;
            int points[num_points * 2];
            for (int i = 0; i < cmd->int_size; i++)
            {
                points[i] = cmd->int_params[i];
            }
//          Shape * shape = create_polygon_shape(points, num_points);
//          add_shape_to_area (area, shape);
            printf ("\nImpossible d'inserer un polygone.\n");
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
    return 0;
}

void supprimer_forme(Area * area, int id)
{
    if (id < 0 || id >= area->nb_shape)
    {
        printf ("Erreur: id invalide\n");
        return;
    }

    Shape* shape = area->shapes[id];
//  Supprimer la forme de la mémoire
    delete_shape (shape);

//  Décaler les formes suivantes dans le tableau
    for (int i = id; i < area->nb_shape - 1; i++)
    {
        area->shapes[i] = area->shapes[i + 1];
    }

    // Réduire le nombre de formes dans le tableau
    area->nb_shape--;
    printf ("Forme supprimee avec succes\n");
}


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



void clear_screen()
{
    printf("Effacement de l'ecran...\n");
    system("cls"); // pour clear la console
    // Code pour effacer l'écran
}

void exit_program()
{
    printf("Fermeture du programme...\n");
    // Code pour quitter le programme
    exit(0);
}


void list_shapes(Area * area)
{
    printf("\nListe des formes geometriques:\n");
    if (area->nb_shape == 0) printf("Aucune forme enregistrée!");
    else
    {
        for(int i = 0; i < area->nb_shape; i++)
        {
            Shape* shape = area->shapes[i];
            if (shape->shape_type == POINT)
            {
                    Point* point = shape->ptrShape;
                    printf("POINT: id:%d  x:%d  y:%d \n",i, point->pos_x, point->pos_y);
            }
            if (shape->shape_type == LINE)
            {
                    Line* line = shape->ptrShape;
                    printf("LINE: id:%d  x1:%d  y1:%d  x2:%d  y2:%d\n",i, line->p1->pos_x, line->p1->pos_y, line->p2->pos_x, line->p2->pos_y);
            }
            if (shape->shape_type == SQUARE)
            {
                    Square* carre = shape->ptrShape;
                    printf("CARRE: id:%d  x:%d  y:%d  longueur:%d \n",i, carre->p->pos_x, carre->p->pos_y, carre->length);
            }
            if (shape->shape_type == CIRCLE)
            {
                    Circle* circle = shape->ptrShape;
                    printf("CIRCLE: id:%d  x:%d  y:%d  radius:%d \n",i, circle->p->pos_x, circle->p->pos_y, circle->radius);
            }
            if (shape->shape_type == RECTANGLE)
            {
                    Rectangle* rectangle = shape->ptrShape;
                    printf("RECTANGLE: id:%d  x:%d  y:%d  width:%d  height:%d \n",i, rectangle->p->pos_x, rectangle->p->pos_y, rectangle->width, rectangle->height);
            }
            if (shape->shape_type == POLYGON)
            {
                    Polygon* polygon = shape->ptrShape;
                    printf("POLYGON:  id:%d, POLYGON ... pas fini", i);
            }
        }
    }
    return;
}

void show_help()
{
    printf("\nListe des commandes:");
    printf("\n- clear (Effacer l'ecran)");
    printf("\n- exit (Quitter le programme)");
    printf("\n- point x y (Ajouter un point)");
    printf("\n- line x1 y1 x2 y2 (Ajouter une ligne)");
    printf("\n- circle x y r (Ajouter un cercle de centre (x,y) et de rayon r)");
    printf("\n- square x y l (Ajouter un carre avec le point gauche superieur (x,y) et de longueur l)");
    printf("\n- rectangle x y w h (Ajouter un rectange avec le point gauche superieur (x,y), de longueur h et de largeur w)");
    printf("\n- polygone x1 y1 x2 y2 ... (Ajouter un polygone)");
    printf("\n- plot (Rafraichir l'ecran pour afficher toutes les formes geometriques de l'image)");
    printf("\n- list (Afficher les formes textuelles)");
    printf("\n- delete id (Supprimer une forme a partir de son identifiant id)");
    printf("\n- erase (Supprimer toutes les formes de l'image)");
    printf("\n- help (Afficher la liste des commandes et leur description)\n\n"); //
}

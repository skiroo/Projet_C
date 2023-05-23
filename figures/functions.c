#include "functions.h"

unsigned int i, j;

//=============Function point=============
Point* create_point(int px, int py)
{
    Point* p = malloc(sizeof(Point));
    p->pos_x = px;
    p->pos_y = py;
    return p;
}

void print_point (Point* p)
{
    printf ("[%d %d]", p->pos_x, p->pos_y);
}

void delete_point (Point* point)
{
    free (point);
    point = NULL;
}

//=============Function line=============
Line* create_line (Point* p1, Point* p2)
{
    Line* l = malloc(sizeof(Line));
    l->p1 = p1;
    l->p2 = p2;
    return l;
}

void print_line (Line* l)
{
    print_point (l->p1);
    printf (" ; ");
    print_point (l->p2);
}

void delete_line (Line* line)
{
    free(line);
    line = NULL;
}

//=============Function square=============
Square* create_square (Point* p, int length)
{
    Square* s = malloc(sizeof(Square));
    s->p = p;
    s->length = length;
    return s;
}

void print_square (Square* s)
{
    print_point (s->p);
    printf ("; Length = %d", s->length);
}

void delete_square (Square* square)
{
    free (square);
    square = NULL;
}

//=============Function rectangle=============
Rectangle* create_rectangle (Point* point, int width, int height)
{
    Rectangle* r = malloc(sizeof(Rectangle));
    r->p = point;
    r->width = width;
    r->height = height;
    return r;
}

void print_rectangle (Rectangle* r)
{
    print_point (r->p);
    printf ("; Width = %d, Height = %d", r->width, r->height);
}

void delete_rectangle (Rectangle* rectangle)
{
    free (rectangle);
    rectangle = NULL;
}

//=============Function circle=============
Circle* create_circle (Point* center, int radius)
{
    Circle* c = malloc(sizeof(Circle));
    c->p = center;
    c->radius = radius;
    return c;
}

void print_circle (Circle* c)
{
    print_point (c->p);
    printf ("; r = %d", c->radius);
}

void delete_circle (Circle* circle)
{
    free (circle);
    circle = NULL;
}

//=============Function polygon=============
Polygon* create_polygon (int n)
{
    Polygon* poly = malloc(sizeof(Polygon));
    poly->n = n;
    poly->points = malloc(poly->n * sizeof(Point*));
    return poly;
}

void print_polygon (Polygon* poly)
{
    for (j = 0; j < poly->n-1; j++)
    {
        print_point (poly->points[j]);
        printf ("; ");
    }
    print_point (poly->points[j]);
}

void delete_polygon (Polygon* polygon)
{
    free (polygon);
    polygon = NULL;
}

//=============Function Shape=============
Shape* create_empty_shape (SHAPE_TYPE shape_type)
{
    Shape* shp = (Shape*) malloc(sizeof(Shape));
    shp->ptrShape = NULL;
    shp->id = 1;
    shp->shape_type = shape_type;
    return shp;
}

Shape* create_point_shape (int px, int py)
{
    Shape *shp = create_empty_shape (POINT);
    Point *p = create_point (px, py);
    shp->ptrShape = p;
    return shp;
}

Shape* create_line_shape (int px1, int py1, int px2, int py2)
{
    Shape *shp = create_empty_shape (LINE);
    Line *l = create_line (create_point(px1, py1), create_point(px2, py2));
    shp->ptrShape = l;
    return shp;
}

Shape* create_square_shape (int px, int py, int length)
{
    Shape *shp = create_empty_shape (SQUARE);
    Square *s = create_square (create_point(px, py), length);
    shp->ptrShape = s;
    return shp;
}

Shape* create_rectangle_shape (int px, int py, int width, int height)
{
    Shape *shp = create_empty_shape (RECTANGLE);
    Rectangle *r = create_rectangle (create_point(px, py), width, height);
    shp->ptrShape = r;
    return shp;
}

Shape* create_circle_shape (int px, int py, int radius)
{
    Shape *shp = create_empty_shape (CIRCLE);
    Circle *c = create_circle (create_point(px, py), radius);
    shp->ptrShape = c;
    return shp;
}

Shape* create_polygon_shape (Point* lst, int n)
{
    Shape *shp = create_empty_shape (POLYGON);
    Polygon *poly = create_polygon(n);
    for (int i = 0; i < poly->n; i++)
        poly->points[i] = lst+i;

    shp->ptrShape = poly;
    return shp;
}

void print_shape (Shape* shape)
{
    switch (shape->shape_type)
    {
        case POINT:
            printf ("POINT ");
            print_point (shape->ptrShape);
            break;
        case LINE:
            printf ("LINE ");
            print_line (shape->ptrShape);
            break;
        case SQUARE:
            printf ("SQUARE ");
            print_square (shape->ptrShape);
            break;
        case RECTANGLE:
            printf ("RECTANGLE ");
            print_rectangle (shape->ptrShape);
            break;
        case CIRCLE:
            printf ("CIRCLE ");
            print_circle (shape->ptrShape);
            break;
        case POLYGON:
            printf ("POLYGON ");
            print_polygon (shape->ptrShape);
            break;
    }
}

void delete_shape (Shape* shape)
{
    free (shape);
    shape = NULL;
}

//=============Function Menu=============
void menu(bool *run)
{
    char choice;
    Shape* tab_shape[100];

    printf ("\n============MENU============\n");

    printf ("Choisir une action :\n");
    printf ("\tA - Ajouter une forme\n");
    printf ("\tB - Afficher la liste des formes\n");
    printf ("\tX - Arrêter le programme\n");

    printf ("\tC - Affichage:\n");

    printf("\n>> Votre choix: ");
    scanf (" %c", &choice);
    printf ("\n");

    switch (choice)
    {
        case 'A':
            tab_shape[global_id] = ajouter_forme();
            printf ("\n");
            break;
        case 'B':
            afficher_forme(tab_shape);
            printf ("\n");
            break;
        case 'X':
            printf ("Fermeture...");
            *run = false;
            break;
        case 'C':
            printf ("\n");
        default:
            printf ("\nCe choix n'existe pas!\n");
            menu(run);
            break;
    }
}

Shape* ajouter_forme()
{
    int choice;
    int x1, y1, x2, y2, width, height, radius, N;
    Point *points;

    printf ("============Ajouter une forme============\n");
    printf ("Choisir une action :\n");
    printf ("\t1 - Ajouter un point\n");
    printf ("\t2 - Ajouter une ligne\n");
    printf ("\t3 - Ajouter un carré\n");
    printf ("\t4 - Ajouter un rectangle\n");
    printf ("\t5 - Ajouter un cercle\n");
    printf ("\t6 - Ajouter un polygone\n");
    printf ("\t7 - RETOUR\n");
    printf ("\n>> Votre choix : ");
    scanf ("%d", &choice);
    printf ("\n");

    switch (choice)
    {
        case 1:
            global_id++;
            printf ("Saisir le point (x,y): ");
            scanf ("%d %d", &x1, &y1);
            return create_point_shape (x1, y1);
        case 2:
            global_id++;

            printf ("Saisir le 1er point (x1,y1): ");
            scanf ("%d %d", &x1, &y1);
            printf ("\nSaisir le 2e point (x2,y2): ");
            scanf ("%d %d", &x2, &y2);
            return create_line_shape (x1, y1, x2, y2);
        case 3:
            global_id++;

            printf ("Saisir le point (x,y): ");
            scanf ("%d %d", &x1, &y1);
            printf ("\nSaisir la taille du carré: ");
            scanf ("%d", &width);
            return create_square_shape(x1, y1, width);
        case 4:
            global_id++;

            printf ("Saisir le point (x,y): ");
            scanf ("%d %d", &x1, &y1);
            printf ("\nSaisir la largeur et la hauteur: ");
            scanf ("%d %d", &width, &height);
            return create_rectangle_shape (x1, y1, width, height);
        case 5:
            global_id++;

            printf ("Saisir le point (x,y): ");
            scanf ("%d %d", &x1, &y1);
            printf ("\nSaisir le rayon du cercle: ");
            scanf ("%d", &radius);
            return create_circle_shape (x1, y1, radius);
        case 6:
            global_id++;

            do {
                printf ("Saisir le nombre de points (>0): ");
                scanf ("%d", &N);
                printf ("\n");
            } while (N <= 0);
            points = (Point*) malloc(N * sizeof(Point));

            for (i = 0; i < N; i++)
            {
                printf ("Saisir les coordonnées du point (x,y): ");
                scanf ("%d %d", &x1, &y1);
                points[i].pos_x = x1;
                points[i].pos_y = y1;
                printf ("\n");
            }
            return create_polygon_shape (points, N);
        case 7:
            return NULL;
        default:
            printf ("Choix incorrect!\n\n");
            return ajouter_forme();
    }
}

void afficher_forme (Shape** tab_shape)
{
    printf("============Afficher les formes============\n");
    if (global_id == 0) printf("Aucune forme enregistrée!");
    else
    {
        for(i = 0; i < global_id; i++)
        {
            printf("%d : ", i+1);
            print_shape(tab_shape[i]);
            printf("\n");
        }
    }
    return;
}
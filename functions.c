/* Fichier source contenant les fonctions principales ainsi que les fonctions du Menu */

#include "functions.h"

static unsigned int i = 0, j = 0;

/* 3 types de fonction pour chaque forme :
 - Allouer en mémoire l'espace nécessaire pour stocker la forme
 - Afficher les données de la forme
 - Libérer l'espace mémoire allouée */
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

//Fonctions qui créer un pointeur sur les formes
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
    for (i = 0; i < poly->n; i++)
        poly->points[i] = lst+i;

    shp->ptrShape = poly;
    return shp;
}

void print_shape (Shape* shape, int id)
{
    switch (shape->shape_type)
    {
        case POINT:
            printf ("POINT : id : %d ", id);
            print_point (shape->ptrShape);
            break;
        case LINE:
            printf ("LINE : id : %d ", id);
            print_line (shape->ptrShape);
            break;
        case SQUARE:
            printf ("SQUARE : id : %d ", id);
            print_square (shape->ptrShape);
            break;
        case RECTANGLE:
            printf ("RECTANGLE : id : %d ", id);
            print_rectangle (shape->ptrShape);
            break;
        case CIRCLE:
            printf ("CIRCLE : id : %d ", id);
            print_circle (shape->ptrShape);
            break;
        case POLYGON:
            printf ("POLYGON : id : %d ", id);
            print_polygon (shape->ptrShape);
            break;
    }
}

void delete_shape (Shape* shape)
{
    switch (shape->shape_type) {
        case POINT:
            delete_point(shape->ptrShape);
            break;
        case LINE:
            delete_line(shape->ptrShape);
            break;
        case SQUARE:
            delete_square(shape->ptrShape);
            break;
        case RECTANGLE:
            delete_rectangle(shape->ptrShape);
            break;
        case CIRCLE:
            delete_circle(shape->ptrShape);
            break;
        case POLYGON:
            delete_polygon(shape->ptrShape);
            break;
    }
    free(shape);
    shape = NULL;
}

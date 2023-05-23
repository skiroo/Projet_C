/* Fichier header contenant la définition des structures de forme,
le prototype des fonctions principales et celles du Menu */

//=============Library C=============
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "id.h"

//=============Structures=============
//Structures pour chaque type de forme
typedef struct
{
    int pos_x;
    int pos_y;
} Point;

typedef struct
{
    Point* p1;
    Point* p2;
} Line;

typedef struct
{
    Point* p;
    int length;
} Square;

typedef struct
{
    Point* p;
    int width;
    int height;
} Rectangle;

typedef struct
{
    Point* p;
    int radius;
} Circle;

typedef struct
{
    int n;
    Point** points;
} Polygon;

typedef enum {POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;

typedef struct
{
    int id;
    SHAPE_TYPE shape_type;
    void* ptrShape;
} Shape;

//Prototype des fonctions pour les formes
//=============Prototype point=============
Point* create_point (int px, int py);
void print_point (Point* p);
void delete_point (Point* point);

//=============Prototype Line=============
Line* create_line (Point* p1, Point* p2);
void print_line (Line* line);
void delete_line (Line* line);

//=============Prototype Square=============
Square* create_square (Point* p, int length);
void print_square (Square* square);
void delete_square (Square* square);

//=============Prototype Rectangle=============
Rectangle* create_rectangle (Point* point, int width, int height);
void print_rectangle (Rectangle* rectangle);
void delete_rectangle (Rectangle* rectangle);

//=============Prototype Circle=============
Circle* create_circle (Point* center, int radius);
void print_circle (Circle* circle);
void delete_circle (Circle* circle);

//=============Prototype Polygon=============
Polygon* create_polygon (int n);
void print_polygon (Polygon* polygon);
void delete_polygon (Polygon* polygon);

//=============Prototype Shape=============
Shape* create_empty_shape (SHAPE_TYPE shape_type);
Shape* create_point_shape (int px, int py);
Shape* create_line_shape (int px1, int py1, int px2, int py2);
Shape* create_square_shape (int px, int py, int length);
Shape* create_rectangle_shape (int px, int py, int width, int height);
Shape* create_circle_shape (int px, int py, int radius);
Shape* create_polygon_shape (Point* lst, int n);
void print_shape (Shape* shape, int id);
void delete_shape (Shape* shape);

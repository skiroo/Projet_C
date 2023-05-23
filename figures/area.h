#define Area_h
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define SHAPE_MAX 100
#define BOOL int

struct area
{
    unsigned int width;
    unsigned int height;
    BOOL** mat;
    Shape* shapes[SHAPE_MAX];
    int nb_shape;
};
typedef struct area Area;

Area* create_area (unsigned int width, unsigned int height);
void add_shape_to_area (Area* area, Shape* shape);
void clear_area (Area* area);
void erase_area (Area* area);
void delete_area (Area* area);
void draw_area (Area* area);
void print_area (Area* area);



struct pixel
{
    int px;
    int py;
};
typedef struct pixel Pixel;
Pixel* create_pixel (int px, int py);
void delete_pixel (Pixel*pixel);

void pixel_point (Point* shape, Pixel** pixel, int* nb_pixels);
void pixel_line (Line* line, Pixel** pixel, int* nb_pixels);
void pixel_circle (Circle* cercle, Pixel** pixel, int* nb_pixels);

void pixel_square (Square* square, Pixel** pixel, int* nb_pixels);
void pixel_rectangle (Rectangle* rectangle, Pixel** pixel, int* nb_pixels);
void pixel_polygon (Polygon* polygon, Pixel** pixel, int* nb_pixels);

Pixel** create_shape_to_pixel (Shape * shape, int* nb_pixels);
void delete_pixel_shape (Pixel** pixel, int nb_pixels);

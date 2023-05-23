/* Fichier source avec definition des fonctions de tracé de formes */

#include "area.h"

Area* create_area(unsigned int width, unsigned int height)
{
    Area* area = (Area*) malloc(sizeof(Area));
    area->width = width;
    area->height = height;
    area->nb_shape = 0;
    area->mat = (BOOL**) malloc(sizeof(BOOL*)*height);

    for (int i = 0; i < height; i++)
    {
        area->mat[i] = (BOOL*) malloc(sizeof(BOOL)*width);
        for (int j = 0; j < width; j++)
        {
            area->mat[i][j] = 0;
        }
    }
    return (area);
}

void add_shape_to_area(Area* area, Shape* shape)
{
    if (area->nb_shape >= SHAPE_MAX)
    {
        printf ("Maximum de figures atteint.");
        return;
    }

    area->shapes[area->nb_shape] = shape;
    area->nb_shape++;
}

void erase_area(Area* area)
{
    for (int i = 0; i < area->nb_shape; i++)
    {
        free (area->shapes[i]);
    }

    area->nb_shape = 0;
}

void clear_area (Area* area)
{
    for(int i = 0; i < area->height; i++)
    {
        for(int j = 0; j < area->width; j++)
        {
            area->mat[i][j] = 0;
        }
    }
}

void delete_area (Area* area)
{
    erase_area (area);
    clear_area (area);
    free (area->mat);
    free (area);
}

void draw_area(Area* area)
{
    for(int i = 0; i < area->nb_shape; i++)
    {
        Shape* shape = area->shapes[i];
        int nb_pixels = 0;
        Pixel** pixels = create_shape_to_pixel(shape, &nb_pixels);

        // Parcourir les pixels et les colorier dans la matrice de l'aire
        for(int j = 0; j < nb_pixels; j++) {
            Pixel* pixel = pixels[j];
            area->mat[pixel->px][pixel->py] = 1;
        }

        delete_pixel_shape(pixels, nb_pixels);
    }
}

void print_area (Area* area)
{
    printf("\n");
    for (int i = 1; i < area->height; i++)
    {
        printf("\t\t");
        for (int j = 1; j < area->width; j++)
        {
            if (area->mat[i][j] == 0)
            {
                printf (".");
            }
            else
            {
                printf ("#");
            }
        }
        printf("\n");
    }
}

//=============Pixel Functions=============
//Allouer en mémoire une variable de type Pixel
Pixel* create_pixel (int px, int py)
{
    Pixel* pixel = (Pixel*) malloc(sizeof(Pixel));

    pixel->px = px;
    pixel->py = py;

    return pixel;
}

//Libérer la mémoire allouée
void delete_pixel (Pixel* pixel)
{
    free (pixel);
}

//Fonction stockant les pixels à colorier
void pixel_point (Point* point, Pixel** pixel, int* nb_pixels)
{
    pixel[0] = create_pixel(point->pos_x, point->pos_y);
    *nb_pixels = 1;
}

void pixel_line (Line* line, Pixel** pixel, int* nb_pixels)
{
    int dx = line->p2->pos_x - line->p1->pos_x;
    int dy = line->p2->pos_y - line->p1->pos_y;

    int dmin, dmax;

    if (abs(dx) > abs(dy))
    {
        dmax = abs(dx);
    }
    else
    {
        dmax = abs(dy);
    }
    if (abs(dx) < abs(dy))
    {
        dmin = abs(dx);
    }
    else
    {
        dmin = abs(dy);
    }

    int nb_segs = dmin + 1;
    int * segments = (int*) malloc (nb_segs * sizeof(int));
    for (int i = 0; i < nb_segs; i++)
    {
        segments[i] = (dmax+1)/(dmin+1);
    }
    int restants = (dmax+1)%(dmin+1);

    int *cumuls = (int *)malloc(nb_segs*sizeof(int));
    cumuls[0]=0;
    for (int i = 1; i < nb_segs;i++)
    {
        cumuls[i] = ((i*restants)%(dmin+1) < ((i-1)*restants)%(dmin+1));
        segments[i] = segments[i]+cumuls[i];
    }

    int x = line->p1->pos_x;
    int y = line->p1->pos_y;
    for (int i = 0; i < nb_segs; i++)
    {
        for (int j = 0; j < segments[i]; j++)
        {
            pixel[*nb_pixels] = create_pixel(x, y);
            *nb_pixels = *nb_pixels + 1;
            if (abs(dx) > abs(dy))
            {
                x += dx > 0 ? 1 : -1;
            }
            else
            {
                y += dy > 0 ? 1 : -1;
            }
        }
        if (abs(dx) > abs(dy))
        {
            y += dy > 0 ? 1 : -1;
        }
        else
        {
            x += dx > 0 ? 1 : -1;
        }
    }

    free (segments);
    free (cumuls);
}

void pixel_circle (Circle* cercle, Pixel** pixel, int* nb_pixels)
{
    int x = 0;
    int y = cercle->radius;
    int d = cercle->radius - 1;
    *nb_pixels = 0;
    int k = 0;

    while(y >= x)
    {
        pixel[k] = create_pixel (cercle->p->pos_x + x, cercle->p->pos_y + y);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x + y, cercle->p->pos_y + x);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x - x, cercle->p->pos_y + y);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x - y, cercle->p->pos_y + x);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x + x, cercle->p->pos_y - y);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x + y, cercle->p->pos_y - x);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x - x, cercle->p->pos_y - y);
        k++;
        pixel[k] = create_pixel (cercle->p->pos_x - y, cercle->p->pos_y - x);
        k++;

        if (d >= 2 * x)
        {
            d -= 2 * x + 1;
            x++;
        }
        else if (d < 2 * (cercle->radius - y))
        {
            d+= 2 * y - 1;
            y--;
        }
        else
        {
            d+=2 * (y-x-1);
            y--;
            x++;
        }
    }
    *nb_pixels = k;
}

void pixel_square (Square* square, Pixel** pixel, int* nb_pixels)
{
    Point * topRight = create_point (square->p->pos_x, square->p->pos_y + square->length);
    Point * bottomLeft = create_point (square->p->pos_x + square->length, square->p->pos_y);
    Point * bottomRight = create_point (square->p->pos_x + square->length, square->p->pos_y + square->length);

    Line * line1 = create_line (square->p, topRight);
    Line * line2 = create_line (square->p, bottomLeft);
    Line * line3 = create_line (topRight, bottomRight);
    Line * line4 = create_line (bottomLeft, bottomRight);

    pixel_line (line1, pixel, nb_pixels);
    pixel_line (line2, pixel, nb_pixels);
    pixel_line (line3, pixel, nb_pixels);
    pixel_line (line4, pixel, nb_pixels);
}

void pixel_rectangle (Rectangle* rectangle, Pixel** pixel, int* nb_pixels)
{
    Point* p = rectangle->p;
    int width = rectangle->width;
    int height = rectangle->height;

    Point* p1 = create_point (p->pos_x, p->pos_y);
    Point* p2 = create_point (p->pos_x + width, p->pos_y);
    Line* line1 = create_line (p1, p2);

    Point* p3 = create_point (p->pos_x + width, p->pos_y + height);
    Line* line2 = create_line (p2, p3);

    Point* p4 = create_point (p->pos_x, p->pos_y + height);
    Line* line3 = create_line (p3, p4);
    Line* line4 = create_line (p4, p1);

    pixel_line (line1, pixel, nb_pixels);
    pixel_line (line2, pixel, nb_pixels);
    pixel_line (line3, pixel, nb_pixels);
    pixel_line (line4, pixel, nb_pixels);
}

void pixel_polygon (Polygon* polygon, Pixel** pixel, int* nb_pixels)
{
    int num_points = polygon->n;
    Point** points = polygon->points;

    *nb_pixels = 0;

//  Tracer chaque c�t� du polygone
    for (int i = 0; i < num_points; i++)
    {
        int next_index = (i + 1) % num_points;
        Point * p = (Point*) polygon->points[i];
//      Point * p2 = (Point*) polygon->points[next_index];

/*
        int x1 = *(polygon->points)[i]->pos_x;
        int y1 = *(polygon->points)[i]->pos_y;

        int x2 = *(polygon->points)[next_index]->pos_x;
        int y2 = *(polygon->points)[next_index]->pos_y;

        Point * p1 = create_point (x1,y1);
        Point * p2 = create_point (x2,y1);


        Line* line = create_line (p, p2);
        pixel_line (line, pixel, nb_pixels);
*/
    }
}

Pixel** create_shape_to_pixel (Shape * shape, int* nb_pixels)
{
    Pixel** pixel = (Pixel**) malloc(sizeof (Pixel*));
    pixel = malloc(500 * sizeof(Pixel*));
    if (pixel == NULL)
    {
        printf ("\nErreur: Allocation de memoire echouee.\n");
        return NULL;
    }

    //Initialiser tous les pointeurs � NULL
    for (int i = 0; i < 500; i++)
    {
        pixel[i] = NULL;
    }

    if (shape->shape_type == POINT)
    {
        Point* p = (Point*) shape->ptrShape;
        pixel_point(p, pixel, nb_pixels);
    }
    else if (shape->shape_type == CIRCLE)
    {
        Circle * p = (Circle*) shape->ptrShape;
        pixel_circle(p, pixel, nb_pixels);
    }
    else if (shape->shape_type == RECTANGLE)
    {
        Rectangle * p = (Rectangle*) shape->ptrShape;
        pixel_rectangle(p, pixel, nb_pixels);
    }
    else if (shape->shape_type == SQUARE)
    {
        Square * p = (Square*) shape->ptrShape;
        pixel_square(p, pixel, nb_pixels);
    }
    else if (shape->shape_type == LINE)
    {
        Line * p = (Line*) shape->ptrShape;
        pixel_line(p, pixel, nb_pixels);
    }
    else if (shape->shape_type == POLYGON)
    {
        Polygon * p = (Polygon*) shape->ptrShape;
        pixel_polygon(p, pixel, nb_pixels);
    }
    else
    {
        printf("- Figure non reconnue");
        return NULL;
    }

    // R�duire la taille de l'allocation � la taille r�elle n�cessaire
    pixel = realloc(pixel, (*nb_pixels) * sizeof(Pixel*));
    if (pixel == NULL)
    {
        printf("\nErreur: reallocation de m�moire echouee.\n");
        return NULL;
    }
    return pixel;

}

//Fonction qui renvoie un tableau de pixels à colorier
void delete_pixel_shape (Pixel** pixel, int nb_pixels)
{
    for(int i = 0; i < nb_pixels; i++)
    {
        free(pixel[i]);
    }
    free(pixel);
}

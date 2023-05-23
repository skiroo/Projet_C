#include "area.h"

Area* create_area (unsigned int width, unsigned int height)
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

////////////////////////////////////////////////////////////
/*
void add_shape_to_area (Area* area, Shape* shape)
{
    if (area->nb_shape >= SHAPE_MAX)
    {
        printf ("Maximum de figures atteint.");
        return;
    }


    if (shape->shape_type == POINT)
    {
        Point* point1 = shape->ptrShape;
        if (point1->pos_x < area->height && point1->pos_y
            < area->width && point1->pos_x >= 0 && point1->
            pos_y >= 0)
        {
            area->mat[point1->pos_x][point1->pos_y] = 1;
            area->shapes[area->nb_shape] = shape;
            area->nb_shape += 1;
        }
        return;
    }

    if (shape->shape_type == LINE)
    {
        Line* ligne1 = shape->ptrShape;
        Point* point1 = ligne1->p1;
        Point* point2 = ligne1->p2;
        int dx = abs(point1->pos_x - point2->pos_x);
        int dy = abs(point1->pos_y - point2->pos_y);

        int sens_x = 0;
        if (point1->pos_x < point2->pos_x)
        {
            sens_x = 1;
        }
        else if (point1->pos_x > point2->pos_x)
        {
            sens_x = -1;
        }
        int sens_y = 0;
        if (point1->pos_y < point2->pos_y)
        {
            sens_y = 1;
        }
        else if (point1->pos_y > point2->pos_y)
        {
            sens_y = -1;
        }

        int x = point1->pos_x;
        int y = point1->pos_y;

        if (x < area->height && y < area->width &&
            x >= 0 && y >= 0)
        {
            area->mat[x][y] = 1;
        }
        while (x != point2->pos_x || y != point2->pos_y)
        {
            if (x == point2->pos_x)
            {
                sens_x = 0;
            }
            if (y == point2->pos_y)
            {
                sens_y = 0;
            }
            x += sens_x;
            y += sens_y;
            if (x < area->height && y < area->width &&
            x >= 0 && y >= 0)
            {
                area->mat[x][y] = 1;
            }
        }
        area->shapes[area->nb_shape] = shape;
        area->nb_shape += 1;
    }

    if (shape->shape_type == SQUARE)
    {
        Square* carre = shape->ptrShape;
        int x = carre->p->pos_x;
        int y = carre->p->pos_y;
        int longueur = carre->length;
        for (int i = x; i < x+longueur; i++)
        {
            for (int j = y; j < y+longueur; j++)
            {
                if (i < area->height && j < area->width &&
                i >= 0 && j >= 0)
                {
                    area->mat[i][j] = 1;
                }
            }
        }
        area->shapes[area->nb_shape] = shape;
        area->nb_shape += 1;
    }

    if (shape->shape_type == RECTANGLE)
    {
        Rectangle* rect = shape->ptrShape;
        int x = rect->p->pos_x;
        int y = rect->p->pos_y;
        int longueur = rect->height;
        int largeur = rect->width;
        for (int i = x; i < x+longueur; i++)
        {
            for (int j = y; j < y+largeur; j++)
            {
                if (i < area->height && j < area->width &&
                i >= 0 && j >= 0)
                {
                    area->mat[i][j] = 1;
                }
            }
        }
        area->shapes[area->nb_shape] = shape;
        area->nb_shape += 1;
    }

    //if (shape->shape_type = )
}
*/

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
////////////////////////////////////////////////////////////

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


draw_area(Area* area)
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

////////////////////////////////////////////////////////////

void print_area (Area* area)
{
    printf("\n");
    for (int i = 1; i < area->height; i++)
    {
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

////////////////////////////////////////////////////////////

Pixel* create_pixel (int px, int py)
{
    Pixel* pixel = malloc(sizeof(Pixel));
    if (pixel == NULL)
    {
        printf ("Erreur allocation");
        return;
    }

    pixel->px = px;
    pixel->py = py;

    return (pixel);
}

void delete_pixel (Pixel*pixel)
{
    free (pixel);
}

void pixel_point (Point* point, Pixel** pixel, int* nb_pixels)
{
//  Point* pt = (Point*) shape->ptrShape;
//  pixel = (Pixel**) malloc (sizeof (Pixel*));
    pixel[0] = create_pixel(point->pos_x, point->pos_y);
    *nb_pixels = 1;
}

void pixel_line (Line* line, Pixel** pixel, int* nb_pixels)
{
//  Line* ligne = (Line*) line->ptrShape;
    int dx = line->p2->pos_x - line->p1->pos_x;
    int dy = line->p2->pos_y - line->p1->pos_y;

    int dmin = 0;
    int dmax = 0;

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
//  pixel = (Pixel**) malloc (sizeof (Pixel*));
//  int nbPixel = 0;
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

void pixel_circle (Circle* cercle, Pixel** pixel, int* nb_pixels) {
//  Circle* monCercle = (Circle*) cercle->ptrShape;
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


void pixel_square (Square* square, Pixel** pixel, int* nb_pixels) {
//  Square* monsquare = (Square*) square->ptrShape;

//  calcul des autres points
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
void pixel_rectangle (Rectangle* rectangle, Pixel** pixel, int* nb_pixels) {
    Point* p = rectangle->p;
    int width = rectangle->width;
    int height = rectangle->height;

//  *nb_pixels = 2 * width + 2 * height;

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

//  Tracer chaque côté du polygone
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

    //Initialiser tous les pointeurs à NULL
    for (int i = 0; i < 500; i++)
    {
        pixel[i] = NULL;
    }

    if (shape->shape_type == POINT)
    {
        Point * p = (Point*) shape->ptrShape;
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

    // Réduire la taille de l'allocation à la taille réelle nécessaire
    pixel = realloc(pixel, (*nb_pixels) * sizeof(Pixel*));
    if (pixel == NULL)
    {
        printf("\nErreur: reallocation de mémoire echouee.\n");
        return NULL;
    }
    return pixel;

}

void delete_pixel_shape (Pixel** pixel, int nb_pixels)
{
    for(int i = 0; i < nb_pixels; i++)
    {
        free(pixel[i]);
    }
    free(pixel);
}

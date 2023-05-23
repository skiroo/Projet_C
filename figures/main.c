//#include "area.h"
#include "command.h"


int main()
{


//    bool run = true;

//    while(run == true)
//    {
//        menu(&run);
//    }

/*

    Area* draw_zone = create_area (30, 30);
    Shape* shape1 = create_line_shape (5, 5, 10, 10);
    Shape* shape2 = create_circle_shape (5, 5, 4);
    Shape* shape3 = create_square_shape (12,12,3);
    Shape* shape4 = create_rectangle_shape (13,4,3,6);


    Point * lst[3];
    lst[0] = create_point (15,15);
    lst[1] = create_point (20,20);
    lst[2] = create_point (15,20);
//  Shape * shape5 = create_polygon_shape(lst,3);
    printf("ici");
    add_shape_to_area (draw_zone, shape1);
    add_shape_to_area (draw_zone, shape2);
    add_shape_to_area (draw_zone, shape3);
    add_shape_to_area (draw_zone, shape4);
//  add_shape_to_area (draw_zone, shape5);

    printf ("apres ajout");
    draw_area (draw_zone);
    printf ("apres draw");
    print_area (draw_zone);
    erase_area (draw_zone);
    clear_area (draw_zone);
    draw_area (draw_zone);
//  print_area (draw_zone);
//  delete_area (draw_zone);

*/

Command* cmd = create_commande();
Area * area = create_area(20, 20);
while (1)
{
    printf("\n- ");
    read_from_stdin(cmd);
    int result = read_exec_command(cmd, area);
    if (result != 0)
    {
        printf("Erreur lors de l'execution de la commande.\n");
    }
    cmd = create_commande();
}

free_cmd(cmd);
return 0;
}

/* Fichier header avec définition de la structure command et prototype des fonctions de commande */

//=============Library C=============
#include "area.h"

//=============Structure=============
struct command
{
    char name[50];
    int int_size;
    int int_params[10];
    int str_size;
    char* str_params[10];
};
typedef struct command Command;

//=============Command Functions=============
Command* create_commande();
void add_str_param (Command* cmd, char* p);
void add_int_param (Command* cmd, int p);
void free_cmd (Command* cmd);
int read_exec_command (Command* cmd, Area* area);
void read_from_stdin (Command* cmd);

void show_help();
int exit_program(void);
void clear_screen(void);
void list_shapes(Area * area);
void supprimer_forme(Area * area, int id);


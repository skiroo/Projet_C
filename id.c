#include "id.h"

unsigned int get_next_id()
{
    unsigned int tmp = global_id;
    global_id++;
    return tmp;
}

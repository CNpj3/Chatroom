#include "City_Grid.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 10000
// City label, east, north

int check_grid(City *city)
{
    if (city->east->north!=NULL && city->north->east!=NULL) return 1;
    return 0;
}
int find_grid(City *city, int state[MAX])
{
    if (state[city->label]==1) return 0;
    state[city->label]=1;
    if (city->east==NULL && city->north==NULL) {
    //    state[city->label]=1;
        return 0;
    }
    else if (city->east!=NULL && city->north!=NULL){
        return check_grid(city)
             + find_grid(city->east, state)
             + find_grid(city->north, state);
 //       state[city->label]=1;
    }
    else if (city->east!=NULL) find_grid(city->east,state);
    else if (city->north!=NULL) find_grid(city->north,state);
   // state[city->label]=1;
    return 0;
}

int City_Grid(City *capital)
{
    int state[MAX]={0};
    return find_grid(capital,state);
}

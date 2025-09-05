#include <stdio.h>
#include <stdint.h>


// Types


#define MAX_EQUIP 20

typedef uint32_t Id;
typedef uint64_t Epoch;
typedef uint32_t Cargo;

typedef enum { LOAD, UNLOAD } Action;
typedef enum { LIGHT, STAND, ACCESSORY, DISPOSABLE, GEAR } Kind;
typedef enum { BROKEN, AVAILABLE, RENTED } Cond;


// Data


typedef struct {
    float lat;
    float lon;
} Loca;

typedef struct {
    char    name[MAX_EQUIP];
    Kind    kind;
    Cond    state;
} Equp;

typedef struct {
    Cargo   cargo;
    Action  mission;
    Loca    *depart;
    Epoch   depart_at;
    Loca    *arrival;
    Epoch   arrival_at;
} Trip;

typedef struct {
    Id      id;
    Trip    *current_trip;
    Trip    *next_trip;
} Vhcl;


// Logic


Vhcl v_0 =  { 0, NULL, NULL };
Vhcl v_1 =  { 1, NULL, NULL };
Vhcl v_2 =  { 2, NULL, NULL };


void schedule(Trip *trips[], size_t count) {

}


int main() {
    Loca l_0 =  { 0,    0                               };
    Loca l_1 =  { 10,   10                              };
    Loca l_2 =  { 20,   20                              };

    Equp e_0 =  { "Light zero",     LIGHT, AVAILABLE    };
    Equp e_1 =  { "Light one",      LIGHT, AVAILABLE    };
    Equp e_2 =  { "Light two",      LIGHT, AVAILABLE    };
    Equp e_3 =  { "Light three",    LIGHT, AVAILABLE    };

    Trip t_0 =  { 0x0,  LOAD,   &l_0, 0,    &l_1, 10    };
    Trip t_1 =  { 0x1,  UNLOAD, &l_1, 100,  &l_0, 110   };
    Trip t_2 =  { 0x2,  LOAD,   &l_1, 200,  &l_0, 210   };

    Trip *trips[] = { &t_0, &t_1, &t_2 };
    size_t n = sizeof(trips) / sizeof(trips[0]);
    schedule(trips, n);

    return 0;
}

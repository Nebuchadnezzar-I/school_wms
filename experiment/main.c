#include "main.h"


#define F1  (1ULL << 0)
#define F2  (1ULL << 1)
#define F3  (1ULL << 2)
#define F4  (1ULL << 3)


typedef struct {
    U64     equip;
    U64     vehic;
} WH;


void run(WH *curr, WH *next) {
    if (curr->equip & F1 && next->equip & F1) {
        printf("Hit\n");
    }

    if (curr->equip & F2) {
    }

    if (curr->equip & F3) {
    }

    if (curr->equip & F4) {
    }
}

int main() {
    U64 w1_f = 0; w1_f |= F1 | F2;
    U64 w2_f = 0; w2_f |= F3 | F4;
    WH current_state = { w1_f, w2_f };

    U64 w3_f = 0; w3_f |= F1 | F4;
    U64 w4_f = 0; w4_f |= F1 | F2;
    WH next_state = { w3_f, w4_f };

    run(&current_state, &next_state);

    return 0;
}

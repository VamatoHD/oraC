#include "rc.h"
#include <stdio.h>
#include <stdlib.h>

int main() {

    int *data = malloc(sizeof(int));
    *data = 20;

    Rc rc1 = rc_create(data, NULL);
    Rc rc2 = rc_retain(&rc1);
    Weak w1 = rc_downgrade(&rc1);
}
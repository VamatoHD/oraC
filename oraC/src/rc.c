#include "rc.h"
#include <stdlib.h>

Rc rc_create(void *data, CleanupFn cleanup) {
    ControlBlock *inner = malloc(sizeof(ControlBlock));

    if (!inner) {
        Rc empty = {.inner = NULL};
        return empty;
    }

    inner->strong_count = 1;
    inner->weak_count = 0;
    inner->data = data;
    inner->cleanup = cleanup;

    Rc new;
    new.inner = inner;
    return new;
}

Rc rc_retain(Rc *rc) {
    Rc new = {.inner = NULL};
    if (!rc || !rc->inner) {
        return new;
    }
    rc->inner->strong_count++;
    new.inner = rc->inner;
    return new;
}

void *rc_get(Rc *rc) {
    if (!rc || !rc->inner) {
        return NULL;
    }
    return rc->inner->data;
}

void rc_release(Rc *rc) {
    if (!rc || !rc->inner) {
        return;
    }

    ControlBlock *inner = rc->inner;

    inner->strong_count--;
    if (inner->strong_count == 0) {
        if (inner->cleanup && inner->data) {
            inner->cleanup(inner->data);
        }
        inner->data = NULL;

        if (inner->weak_count == 0) {
            free(inner);
        }
    }
    rc->inner = NULL;
}

Weak rc_downgrade(Rc *rc) {
    Weak new = {.inner = NULL};
    if (!rc || !rc->inner) {
        return new;
    }
    rc->inner->weak_count++;
    new.inner = rc->inner;
    return new;
}

Rc weak_upgrade(Weak *weak) {
    Rc new = {.inner = NULL};
    if (!weak || !weak->inner) {
        return new;
    }

    if (weak->inner->strong_count == 0) {
        // The data has already been freed
        return new;
    }

    weak->inner->strong_count++;
    new.inner = weak->inner;
    return new;
}

void weak_release(Weak *weak) {
    if (!weak) {
        return;
    }

    ControlBlock *inner = weak->inner;

    if (!inner) {
        return;
    }

    inner->weak_count--;
    if (inner->weak_count == 0 && inner->strong_count == 0) {
        // The data should be free already
        free(inner);
    }
    weak->inner = NULL;
}
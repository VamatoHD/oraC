#ifndef RC_H
#define RC_H

#include <stdbool.h>
#include <stddef.h>

typedef void (*CleanupFn)(void *);

typedef struct {
    int strong_count;
    int weak_count;
    CleanupFn cleanup;
    void *data;
} ControlBlock;

typedef struct {
    ControlBlock *inner;
} Rc;

typedef struct {
    ControlBlock *inner;
} Weak;

Rc rc_create(void *data, CleanupFn cleanup);
Rc rc_retain(Rc *rc);
void *rc_get(Rc *rc);
void rc_release(Rc *rc);

Weak rc_downgrade(Rc *rc);
Rc weak_upgrade(Weak *weak);
void weak_release(Weak *weak);

#endif
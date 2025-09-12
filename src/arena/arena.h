#pragma once

#include "../types/types.h"

#include <string.h>
#include <stdlib.h>

typedef struct {
    U8      *base;
    size_t  cap;
    size_t  cursor;
} Arena;

Arena* arena_new(size_t size);
void* arena_alloc(Arena* a, size_t size);

#include "arena.h"

Arena* arena_new(size_t size) {
    Arena* a = malloc(sizeof(Arena));
    if (!a) return NULL;

    a->base     = malloc(size);
    a->cap      = size;
    a->cursor   = 0;

    // Touches all pages
    memset(a->base, 0, size);

    return a;
}

void* arena_alloc(Arena* a, size_t size) {
    // TODO(Michal): Fuck overflow
    if (a->cap + size > a->cap) {
        return NULL;
    }

    void* ptr = a->base + a->cursor;
    a->cursor += size;
    return ptr;
}

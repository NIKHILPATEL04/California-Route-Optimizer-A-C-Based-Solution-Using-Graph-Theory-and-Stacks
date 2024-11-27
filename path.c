#include "path.h"

#include "graph.h"
#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct path {
    uint32_t total_weight;
    Stack *vertices;
} Path;

void path_free(Path **pp) {
    if (*pp != NULL && pp != NULL) {
        if ((*pp)->vertices) {
            free((*pp)->vertices);
            (*pp)->vertices = NULL;
        }
        free(*pp);
    }
    if (pp != NULL) {
        *pp = NULL;
    }
}

uint32_t path_vertices(const Path *p) {
    if (p == NULL) {
        return 0;
    }

    return stack_size(p->vertices);
}

Path *path_create(uint32_t capacity) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p == NULL) {
        return NULL;
    }

    p->vertices = malloc(capacity * sizeof(uint32_t));
    if (p->vertices == NULL) {
        free(p);
        return NULL;
    }
    p->total_weight = 0;
    p->vertices = stack_create(capacity);
    return p;
}

uint32_t path_distance(const Path *p) {
    return p->total_weight;
}

void path_add(Path *p, uint32_t val, const Graph *g) {
    if (g == NULL || p == NULL) {
        return;
    }

    if (stack_empty(p->vertices)) {
        stack_push(p->vertices, val);
    } else {
        uint32_t edgeCase;
        if (!stack_peek(p->vertices, &edgeCase)) {
            return;
        }

        uint32_t gastotal = graph_get_weight(g, edgeCase, val);
        p->total_weight += gastotal;
        stack_push(p->vertices, val);
    }
}

uint32_t path_remove(Path *p, const Graph *g)

{
    if (g == NULL || p == NULL || stack_empty(p->vertices)) {
        return UINT32_MAX;
    }
    uint32_t remove;
    if (!stack_pop(p->vertices, &remove)) {
        return UINT32_MAX;
    }

    if (!stack_empty(p->vertices)) {
        uint32_t stackupdate;
        stack_peek(p->vertices, &stackupdate);
        uint32_t gastotal = graph_get_weight(g, stackupdate, remove);
        if (p->total_weight >= gastotal) {
            p->total_weight -= gastotal;
        }
    }
    return remove;
}

void path_copy(Path *src, const Path *dst) {
    if (dst == NULL || src == NULL) {
        return;
    }
    stack_copy(src->vertices, dst->vertices);
    src->total_weight = dst->total_weight;
}

void path_print(const Path *p, FILE *outfile, const Graph *g) {
    stack_print(p->vertices, outfile, graph_get_names(g));
}

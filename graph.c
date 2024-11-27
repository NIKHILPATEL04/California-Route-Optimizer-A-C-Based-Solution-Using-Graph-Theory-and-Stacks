#include "graph.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct graph {
    bool directed;
    uint32_t vertices;
    bool *visited;
    char **names;
    uint32_t **weights;
} Graph;

Graph *graph_create(uint32_t vertices, bool directed) {
    Graph *g = calloc(1, sizeof(Graph));
    g->vertices = vertices;
    g->directed = directed;
    g->visited = calloc(vertices, sizeof(bool));
    g->names = calloc(vertices, sizeof(char *));
    g->weights = calloc(vertices, sizeof(g->weights[0]));
    for (uint32_t i = 0; i < vertices; ++i) {
        g->weights[i] = calloc(vertices, sizeof(g->weights[0][0]));
    }
    return g;
}

void graph_add_vertex(Graph *g, const char *name, uint32_t v) {
    if (name == NULL) {
        return;
    }
    if (g == NULL) {
        return;
    }

    if (g->names[v]) {
        free(g->names[v]);
    }

    if (v >= g->vertices) {
        return;
    }

    g->names[v] = strdup(name);
    if (g->names[v] == NULL) {
    }
}

uint32_t graph_vertices(const Graph *g) {
    return g->vertices;
}

uint32_t graph_get_weight(const Graph *g, uint32_t start, uint32_t end) {
    if (g == NULL || start >= g->vertices || end >= g->vertices) {
        return 0;
    }
    return g->weights[start][end];
}

void graph_unvisit_vertex(Graph *g, uint32_t v) {
    if (g == NULL) {
        return;
    }
    if (v >= g->vertices) {
        return;
    }
    g->visited[v] = false;
}

char **graph_get_names(const Graph *g) {
    if (g == NULL) {
        return NULL;
    }
    return g->names;
}

void graph_visit_vertex(Graph *g, uint32_t v) {
    if (g == NULL) {
        return;
    }
    if (v >= g->vertices) {
        return;
    }
    g->visited[v] = true;
}

const char *graph_get_vertex_name(const Graph *g, uint32_t v) {
    if (g == NULL) {
        return NULL;
    }
    if (v >= g->vertices) {
        return NULL;
    }
    return g->names[v];
}

void graph_add_edge(Graph *g, uint32_t start, uint32_t end, uint32_t weight) {
    if (g == NULL || start >= g->vertices || end >= g->vertices) {
        return;
    }

    g->weights[start][end] = weight;
    if (!g->directed) {
        g->weights[end][start] = weight;
    }
}

void graph_free(Graph **gp) {
    if (gp == NULL || *gp == NULL) {
        return;
    }

    for (uint32_t index = 0; index < (*gp)->vertices; ++index) {
        free((*gp)->names[index]);
    }
    free((*gp)->names);

    free((*gp)->visited);

    for (uint32_t index = 0; index < (*gp)->vertices; ++index) {
        free((*gp)->weights[index]);
    }
    free((*gp)->weights);

    free(*gp);

    *gp = NULL;
}

bool graph_visited(const Graph *g, uint32_t v) {
    if (g == NULL) {
        return false;
    }
    if (v >= g->vertices) {
        return false;
    }
    return g->visited[v];
}

void graph_print(const Graph *g) {
    if (g == NULL) {
        return;
    }
    printf("Adjacency Matrix:\n");
    printf("     ");
    for (uint32_t index = 0; index < g->vertices; ++index) {
        if (g->names && g->names[index]) {
            printf("%7s", g->names[index]);
        } else {
            printf("%7d", index);
        }
    }
    printf("\n");
    for (uint32_t index = 0; index < g->vertices; ++index) {
        if (g->names && g->names[index]) {
            printf("%s", g->names[index]);
        } else {
            printf("%d", index);
        }
        if (g->names && g->names[index]) {
            size_t time = 7 - strlen(g->names[index]);
            for (size_t times = 0; times < time; ++times) {
                printf(" ");
            }
        } else {
            printf("      ");
        }
        for (uint32_t Index = 0; Index < g->vertices; ++Index) {
            printf("%7u", g->weights[index][Index]);
        }
        printf("\n");
    }
}

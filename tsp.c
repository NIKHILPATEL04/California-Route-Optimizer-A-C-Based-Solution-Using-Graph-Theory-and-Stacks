#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define OPTIONS "d:h:i:o:"

void dfs(Graph *g, Path *smallest_route, uint32_t *gas_price);
void pathhelper(
    Graph *g, uint32_t allis, Path *checked_route, Path *smallest_route, uint32_t *gas_price);

void dfs(Graph *g, Path *smallest_route, uint32_t *gas_price) {
    *gas_price = UINT32_MAX;
    for (uint32_t index = 0; index < graph_vertices(g); ++index) {
        Path *checked_route = path_create(graph_vertices(g));
        pathhelper(g, index, checked_route, smallest_route, gas_price);
        path_free(&checked_route);
    }
}

void pathhelper(
    Graph *g, uint32_t allis, Path *checked_route, Path *smallest_route, uint32_t *gas_price) {
    graph_visit_vertex(g, allis);
    path_add(checked_route, allis, g);
    if ((path_vertices(checked_route)) == (graph_vertices(g))) {
        if (graph_get_weight(g, allis, START_VERTEX) > 0) {
            uint32_t xxweight
                = path_distance(checked_route) + graph_get_weight(g, allis, START_VERTEX);
            if (xxweight < *gas_price) {
                *gas_price = xxweight;
                path_copy(smallest_route, checked_route);
            }
        }
    } else {
        for (uint32_t vertex = 0; vertex < graph_vertices(g); ++vertex) {
            if (!graph_visited(g, vertex) && graph_get_weight(g, allis, vertex) > 0) {
                pathhelper(g, vertex, checked_route, smallest_route, gas_price);
            }
        }
    }

    path_remove(checked_route, g);
    graph_unvisit_vertex(g, allis);
}

int main(int argc, char **argv) {
    FILE *outfile = stdout;
    FILE *infile = stdin;
    int a;
    bool next_desination = false;
    while ((a = getopt(argc, argv, OPTIONS)) != -1) {
        switch (a) {
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'i': infile = fopen(optarg, "r"); break;
        case 'd': next_desination = true; break;
        case 'h':
            printf("Usage: tsp options\n");
            printf("-i infile    Specify the input file path containing the cities and edges of a "
                   "graph. If not specified, the default input is automatically set as stdin.\n");
            printf("-o outfile   Specify the output file path to print to. If not specified the "
                   "default output is stdout.\n");

            printf("-d           Specifies the graph value that is going to be directed and then "
                   "Prints out a help.\n");
            exit(0);
            break;
        }
    }

    uint32_t drive;
    char driveinfo[9999];
    fgets(driveinfo, sizeof(driveinfo), infile);
    drive = (uint32_t) strtoul(driveinfo, NULL, 10);
    Graph *graph = graph_create(drive, next_desination);
    char v_name[drive][9999];
    for (uint32_t index1 = 0; index1 < drive; index1++) {
        fgets(v_name[index1], sizeof(v_name[index1]), infile);
        v_name[index1][strcspn(v_name[index1], "\n")] = '\0';
        graph_add_vertex(graph, v_name[index1], index1);
    }
    fgets(driveinfo, sizeof(driveinfo), infile);
    driveinfo[strcspn(driveinfo, "\n")] = '\0';
    int edge;
    edge = (int) strtoul(driveinfo, NULL, 10);
    uint32_t backhome;
    uint32_t setpoint;

    uint32_t gas;

    for (int index2 = 0; index2 < edge; index2++) {
        fscanf(infile, "%u %u %u", &setpoint, &backhome, &gas);
        graph_add_edge(graph, setpoint, backhome, gas);
        if (!next_desination) {
            graph_add_edge(graph, backhome, setpoint, gas);
        }
    }
    Path *fastestpath = path_create(drive);
    uint32_t gas_price;
    dfs(graph, fastestpath, &gas_price);
    if (gas_price < UINT32_MAX) {
        fprintf(outfile, "%s", "Alissa starts at:\n");
        path_print(fastestpath, outfile, graph);
        fprintf(outfile, "%s", graph_get_vertex_name(graph, START_VERTEX));
        fprintf(outfile, "\nTotal Distance: %u\n", gas_price);
    } else {
        fprintf(outfile, "No path found! Alissa is lost!\n");
    }
    path_free(&fastestpath);
    graph_free(&graph);
    if (outfile != stdout) {
        fclose(outfile);
    }
    if (infile != stdin) {
        fclose(infile);
    }
    exit(0);
}

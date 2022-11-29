#include <stdio.h>
#include <stdlib.h>
#include "math.h"

long P = 4;

struct edge{
    long v0;
    long v1;
};

struct edge* load_graphdata(int s){
    FILE *graphfile = fopen("/home/rick/CLionProjects/ParallelAlgorithms/mis/CA-GrQc.txt", "r");
    if (graphfile == NULL){
        printf("File not found\n");
    }
    long vertices, edges;
    fscanf(graphfile, "# Nodes: %ld Edges: %ld", &vertices, &edges);
    fscanf(graphfile, "%*[^\n]"); //skip next line
    printf("Nodes: %ld Edges: %ld", vertices, edges);
    long blocksize = ceil((double)vertices/P);
    struct edge* graphdata = malloc(edges*sizeof(*graphdata));
    long edgecount = 0;
    for (long i=0; i<edges; i++){
        long v0, v1;
        fscanf(graphfile, "%ld %ld", &v0, &v1);
        if (v0 >= s*blocksize && v0 < (s+1)*blocksize){
            if (v1 > v0 || v1 <s*blocksize){
                graphdata[edgecount] = (struct edge){v0, v1};
                edgecount++;
            }

        }
    }
    graphdata = realloc(graphdata, edgecount*sizeof(*graphdata));
    return graphdata;
}

int main() {
    FILE *graphfile = NULL;
    int output = load_graphdata(0);
    return 0;
}

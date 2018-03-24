#ifndef LB_GRAPH_H
#define LB_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include "edge.h"
#include "st.h"
#include "pq.h"

typedef struct graph *Graph;

Graph GRAPHinit(int);
void GRAPHread(Graph,FILE*);
void GRAPHwrite(Graph,FILE*);
void GRAPHinsert(Graph);
void GRAPHremove(Graph);
void GRAPHprint(Graph);
void GRAPHedges(Graph,Edge*);
void GRAPHrand(Graph,int,int,int,int);
int GRAPHpath(Graph,int,int);
int GRAPHpathH(Graph,int,int);
void GRAPHbfs(Graph);
void GRAPHdfs(Graph);
int GRAPHcc(Graph);
int GRAPHscc(Graph);

#endif
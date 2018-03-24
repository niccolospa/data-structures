#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

#define MAX 20
#define MAXV 100

typedef struct node *link;
struct node { int v; int wt; link next; }
struct graph { int V; int E; link *adj; ST tab; link z; };

link NEW(int v, link next){
	link x = malloc(sizeof(*x));
	x->v = v;
	x->next = next;
	x->wt = wt;
	return x;
}

void insertE(Graph G, Edge e){
	int v = e.v, w = e.w, wt = e.wt;
	G->adj[v] = NEW(w, wt, G->adj[v]);
	G->adj[w] = NEW(v, wt, G->adj[w]);
	G->E++;
}

void removeE(Graph G, Edge e){
	int v = e.v, w = e.w;
	link x;
	if(G->adj[v]->v == w){
		G->adj[v] = G->adj[v]->next;
		G->E--;
	}
	else
		for(x=G->adj[v]; x!=G->z; x=x->next)
			if(x->next->v == w){
				x->next = x->next->next;
				G->E--;
			}
	if(G->adj[w]->v == v)
		G->adj[w] = G->adj[w]->next;
	else
		for(x=G->adj[w]; x!=G->z; x=x->next)
			if(x->next->v == v)
				x->next = x->next->next;
}

Graph GRAPHinit(int V){
	int v;
	Graph G = malloc(sizeof(*G));
	if(G == NULL)
		return NULL;
	if(V > MAXV)
		return NULL;
	G->V = V;
	G->E = 0;
	G->z = NEW(-1, NULL);
	G->adj = malloc(G->V * sizeof(link));
	for(v=0;v<G->V;v++)
		G->adj[v] = G->z;
	G->tab = STinit(STsize(V));
	if(G->tab == NULL)
		return NULL;
	return G;
}

void GRAPHread(Graph G, FILE *fp){
	char src[MAX], dst[MAX];
	int id1, id2, wt;
	while(fscanf(fp, "%s %s %d", src, dst, &wt) == 3){
		id1 = STsearch(G->tab, src);
		if(id1 == -1)
			id1 = STinsert(G->tab, src);
		id2 = STsearch(G->tab, dst);
		if(id2 == -1)
			id2 = STinsert(G->tab, dst);
		if(id1 < 0 || id2 < 0)
			continue;
		insertE(G, EDGEcreate(id1, id2, wt));
	}
	return;
}

void GRAPHwrite(Graph G, FILE *fp){
	int i;
	Edge *a = malloc(G->E * sizeof(Edge));
	GRAPHedges(G, a);
	for(i=0;i<G->E;i++)
		fprintf(fp,"%s %s %d\n", STgetitem(G->tab, a[i].v), STgetitem(G->tab, a[i].w), a[i].wt);
	return;
}
	
void GRAPHinsert(Graph G){
	char src[MAX], dst[MAX];
	int id1, id2, wt;
	printf("Insert first node = ");
	scanf("%s", src);
	printf("Insert second node = ");
	scanf("%s", dst);
	prtinf("Insert weight = ");
	scanf("%d", &wt);
	id1 = STsearch(G->tab, src);
	id2 = STsearch(G->tab, dst);
	if(id1 < 0 || id2 < 0)
		return;
	insertE(G, EDGEcreate(id1, id2, wt));
	return;
}

void GRAPHremove(Graph G){
	int id1, id2;
	char src[MAX], dst[MAX];
	printf("Insert first node = ");
	scanf("%s", src);
	printf("Insert second node = ");
	scanf("%s", dst);
	id1 = STsearch(G->tab, src);
	id2 = STsearch(G->tab, dst);
	if(id1 < 0 || id2 < 0)
		return;
	removeE(G, EDGEcreate(id1, id2, 0));
	return;
}

void GRAPHprint(Graph){
	int v;
	link t;
	printf("%d vertices, %d edges \n", G->V, G->E);
	for(v=0; v<G->V; v++){
		printf("%s:\t", STgetitem(G->tab, v));
		for(t=G->adj[v]; t!=G->z; t=t->next)
			printf("(%s %d)", STgetitem(G->tab, t->v), t->wt);
		printf("\n");
	}
}

void GRAPHedges(Graph G, Edge *a){
	int v,E=0;
	link t;
	for(v=0;v<G->V;v++)
		for(t=G->adj[v];t!=G->z;t=t->next)
			if(v < t->v)
				a[E++] = EDGEcreate(v, t->v);
}

void GRAPHrand(Graph G, int V, int E, int minWT, int maxWT){
	int i,j,id1,id2,wt,rangeWT = maxWT - minWT + 1;
	double p = 2.0 * E / (V * (V-1));
	char src[MAX] = "vertex0", dst[MAX] = "vertex0";
	for(i=0; i<v; i++){
		for(j=i+1; j<v; j++){
			if(rand() < p * RAND_MAX){
				src[6] = i;
				dst[7] = j;
				id1 = STsearch(G->tab, src);
				if(id1 < 0)
					id1 = STinsert(G->tab, src);
				id2 = STsearch(G->tab, dst);
				if(id2 < 0)
					id2 = STinsert(G->tab, dst);
				if(id1 < 0 || id2 < 0)
					continue;
				wt = ( rand() % rangeWT ) + minWT;
				insertE(G, EDGEcreate(i,j,wt));
			}
		}
	}
	return;
}

int pathR(Graph G, int v, int w, int *visited){
	int i;
	link t;
	if(v==w)
		return 1;
	visited[v] = 1;
	for(t=G->adj[v]; t!=G->z; t=t->next){
		if(visited[t->w] == 0){
			if(pathR(G, t->w, w, visited)){
				printf("(%s, %s) in path\n", STgetitem(G->tab, v), STgetitem(G->tab, t->w));
				return 1;
			}
		}
	}
	return 0;
}

int GRAPHpath(Graph G, int start, int end){
	int t, found, *visited;
	visited = malloc(G->V * sizeof(int));
	for(t=0; t<G->V; t++)
		visited[t] = 0;
	found = pathR(G, start, end, visited);
	free(visited);
	return found;
}

int pathRH(Graph G, int v, int w, int d, int *visited){
	link t;
	if (v == w){
		if(d == 0)
			return 1;
		return 0;
	}
	visited[v] = 1;
	for(t=G->adj[v]; t!=G->z; t=t->next){
		if(visited[t->w] == 0){
			if(pathRH(G, t->w, w, d-1, visited)){
				printf("(%s, %s) in path\n", STgetitem(G->tab, v), STgetitem(G->tab, t->w));
				return 1;
			}
		}
	}
	
int GRAPHpathH(Graph, int start, int end){
	int t, found, *visited;
	visited = malloc(G->V * sizeof(int));
	for(t=0; t<G->V; t++)
		visited[t] = 0;
	found = pathRH(G, start, end, G->V, visited);
	free(visited);
	return found;
}

void bfs(Graph G, Edge e, int *time, int *pre, int *st){
	int v;
	link t
	PQ pq = PQinit();
	PQinsert(q,e);
	while(!PQempty(q)){
		if(pre[(e = Qget(q)).w] == -1){
			pre[e.w] = (*time)++;
			st[e.w] = e.v;
			for(t=G->adj[e.w]; t!=G->z; t=t->next)
				if(pre[v] == -1)
					PQinsert(q,EDGEcreate(e.w,v));
		}
	}
}

void GRAPHbfs(Graph G){
	int v, time=0, *pre, *st;
	pre = malloc(G->V * sizeof(int));
	st = malloc(G->V * sizeof(int));
	for(v=0; v<G->V; v++){
		pre[v] = -1;
		st[v] = -1;
	}
	bfs(G, EDGEcreate(0,0), &time, pre, st);
	printf("Resulting BFS tree\n");
	for(v=0; v<G->V; v++)
		if(st[v] != -1)
			printf("%s's parent is: %s\n", STgetitem(G->tab,v), STgetitem(G->tab,st[v]));
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st){
	link t;
	int v, w = e.w;
	Edge x;
	if(e.v != e.w)
		printf("(%s, %s): T\n",STgetitem(G->tab,e.v),STgetitem(G->tab,e.w));
	st[e.w] = e.v;
	pre[w] = (*time)++;
	for(t=G->adj[w]; t!=G->z; t=t->next){
		if(pre[t->v] == -1)
			dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
		else{
			v = t->v;
			x = EDGEcreate(w,v);
			if(pre[w] < pre[v])
				printf("(%s, %s): B\n", STgetitem(G->tab, x.v), STgetitem(G->tab, x.w));
		}
	}
	post[w] = (*time)++;
}

void GRAPHdfs(Graph G){
	int v, time=0, *pre, *post, *st;
	pre = malloc(G->V * sizeof(int));
	post = malloc(G->V * sizeof(int));
	st = malloc(G->V * sizeof(int));
	for(v=0; v<G->V; v++)
		if(pre[v] == -1)
			dfsR(G, EDGEcreate(v,v), &time, pre, post, st);
	printf("Discovery/Endprocessing time labels\n");
	for(v=0; v<G->V; v++)
		printf("%s: %d/%d\n", STgetitem(G->tab,v), pre[v], post[v]);
	printf("Resulting DFS tree\n");
	for(v=0; v<G->V; v++)
		printf("%s's parent: %s\n", STgetitem(G->tab,v), STgetitem(G->tab,st[v]));
}

void dfsRcc(Graph G, int v, int id, int *cc){
	link t;
	cc[v] = id;
	for(t=G->adj[v]; t!=G->z; t=t->next)
		if(cc[t->v] == -1)
			dfsRcc(G, t->v, id, cc);
}

int GRAPHcc(Graph G){
	int v, id = 0, *cc;
	cc = malloc(G->V * sizeof(int));
	for(v=0; v<G->V; v++) cc[v] = -1;
	for(v=0; v<G->V; v++)
		if(cc[v] == -1) dfsRcc(G, v, id++, cc);
	printf("Connected component(s) \n");
	for(v=0; v<G->V; v++)
		printf("node %s in cc %d\n", STgetitem(G->tab,v),cc[v]);
	return id;
}

Graph reverse(Graph G){
	int v;
	link t;
	Graph R = GRAPHinit(G->V);
	for(v=0; v<G->V; v++)
		for(t=G->adj[v]; t!=G->z; t=t->next)
			insertE(R, EDGEcreate(t->v, v));
	return R;
}

void SCCdfsR(Graph F, int w, int *scc, int *time0, int time1, int *post){
	link t;
	scc[w] = time1;
	for(t=G->adj[w]; t!=G->z; t=t->next)
		if(scc[t->v] == -1)
			SCCdfsR(G, t->v, scc, time0, time1, post);
	post[(*time0)++] = w;
}

int GRAPHscc(Graph G){
	int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
	Graph R = GRAPHreverse(G);
	sccG = malloc(G->V * sizeof(int));
	sccR = malloc(G->V * sizeof(int));
	postG = malloc(G->V * sizeof(int));
	postR = malloc(G->V * sizeof(int));
	for(v=0; v<G->V; v++){
		sccG[v] = -1;
		sccR[v] = -1;
		postG[v] = -1;
		postR[v] = -1;
	}
	for(v=0; v<G->V; v++)
		if(sccR[v] == -1)
			SCCdfsR(R, v, sccR, &time0, time1, postR);
	time0 = 0;
	time1 = 0;
	for(v=G->V-1; v>=0; v--)
		if(sccG[postR[v]] == -1){
			SCCdfsR(G, postR[v], sccG, &time0, time1, postG);
			time1++;
		}
	printf("Strongly connected components\n");
	for(v=0; v<G->V; v++)
		printf("Node %d in scc %d\n",v,sccG[v]);
	return time1;
}
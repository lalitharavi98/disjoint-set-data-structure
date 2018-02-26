#include<stdio.h>
#include<stdlib.h>

struct Subset
{
    int rank;
    int parent;
};
struct Edge
{
    int src;
    int dest;
};
struct Graph
{
    int v;
    int e;
    struct Edge *edges;
};
struct Graph *create_Graph(int v,int e);
void makeset(struct Graph*,struct Subset*);
int uos(struct Subset subsets[],int x,int y);
void printset(struct Subset subsets[],int v,struct Graph* graph);
main()
{
    int v,e;
    printf("enter the number of vertices and edges:\n");
    scanf("%d %d",&v,&e);
    struct Graph *graph=create_Graph(v,e);
    struct Subset *subsets=(struct Subset*)malloc(v*sizeof(struct Subset));
    makeset(graph,subsets);
   printset(subsets,v,graph); 

}
struct Graph* create_Graph(int v,int e)
{
    int i;
    struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));
    graph->v=v;
    graph->e=e;
    graph->edges=(struct Edge*)malloc(graph->e*sizeof(struct Edge));
    printf("enter the edges:(src and dest)");
    for(i=0;i<graph->e;i++)
    {
        scanf("%d %d",&(graph->edges[i].src),&(graph->edges[i].dest));
    }
    return graph;
}
void makeset(struct Graph* graph,struct Subset* subsets)
{
    int i;
    
    for(i=0;i<graph->v;i++)
    {
        subsets[i].rank=0;
        subsets[i].parent=i;
    }
   
}
int findset(struct Subset subsets[],int i)
{
    if(subsets[i].parent!=i)
    {
        subsets[i].parent=findset(subsets,subsets[i].parent);
    }
    return subsets[i].parent;
}
int uos(struct Subset subsets[],int x,int y)
{
    int px=findset(subsets,x);
    int py=findset(subsets,y);
    int rpx=subsets[px].rank;
    int rpy=subsets[py].rank;
    if(rpx>rpy)
    {
        subsets[py].parent=px;
    }
    else if(rpy>rpx)
        {
            subsets[px].parent=py;
        }
    else
    {
        subsets[px].parent=py;
        subsets[py].rank=subsets[py].rank+1;
    }
}
void printset(struct Subset subsets[],int v,struct Graph* graph)
{
	
	int i;
	printf("%%%%%%%%%%%%%%%%%%%%%%%%");
	for(i=0;i<graph->e;i++)
	{
		uos(subsets,graph->edges[i].src,graph->edges[i].dest);
	}
	for(i=0;i<graph->v;i++)
	{
		printf("%d ------ %d-------%d\n",i,subsets[i].parent,subsets[i].rank);
	}
}

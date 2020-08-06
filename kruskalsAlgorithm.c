/*Implementation of Kruskal's ALgorithm
Reading data from file assuming first line of file contains no of vertices and vertices have continuous numerical names.
Foreg if there are total 6 vertices then vertices names should be 1,2,3,4,5,6.*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include"quickSort.h"
#define fileName "kruskal.txt"

//TO print the minimum spanning tree
void printMinimumSpanTree(int **spanTree,int sizeOfSpanTree)
{
	int i;
	printf("Minimum Spanning Tree is:\nSource\tDestination\tWeight\n");
	for(i=0;i<sizeOfSpanTree;i++)
	{
		printf("%5d%10d%10d\n",spanTree[i][0],spanTree[i][1],spanTree[i][2]);
	}
}

//To find the minimum spanning tree
void findMinimumSpanTree(int **edgeList,int *component,int **spanTree,int sizeOfEdgeList,int noOfVertices)
{
	int i,sizeOfSpanTree=0,j,tempComponent;
	//Initializing spanning tree and component since first edge is always a part of spanning tree
	spanTree[0][0]=edgeList[0][0];
	spanTree[0][1]=edgeList[0][1];
	spanTree[0][2]=edgeList[0][2];
	sizeOfSpanTree++;						//TO keep track of size of spanning tree
	component[edgeList[0][0]-1]=-1;
	component[edgeList[0][1]-1]=-1;

	for(i=1;i<sizeOfEdgeList;i++)
	{
		//If component of both vertices of an edge is same then discard it(Avoid cycles)
		if(component[edgeList[i][0]-1]==component[edgeList[i][1]-1])
		{
			continue;
		}
		//If one of the vertex is already a component of span tree add other vertex also as component of span tree
		else if((component[edgeList[i][0]-1]==-1 && component[edgeList[i][1]-1]!=-1 )|| (component[edgeList[i][1]-1]==-1 && component[edgeList[i][0]-1]!=-1))
		{
			spanTree[sizeOfSpanTree][0]=edgeList[i][0];
			spanTree[sizeOfSpanTree][1]=edgeList[i][1];
			spanTree[sizeOfSpanTree][2]=edgeList[i][2];
			sizeOfSpanTree++;

			//Making the newly added edge/component a part of same component as of spanning tree
			if(component[edgeList[i][1]-1]!=-1)
				tempComponent=component[edgeList[i][1]-1];
			else
				tempComponent=component[edgeList[i][0]-1];
			for(j=0;j<noOfVertices;j++)
			{
					if(tempComponent==component[j])
						component[j]=-1	;
			}
		}
		//if Both vertex are of different component make component of both same but not same as span tree
		else if(component[edgeList[i][0]-1]!=component[edgeList[i][1]-1])
		{
		
			spanTree[sizeOfSpanTree][0]=edgeList[i][0];
			spanTree[sizeOfSpanTree][1]=edgeList[i][1];
			spanTree[sizeOfSpanTree][2]=edgeList[i][2];

			//Making the newly added edge a parto of same component 
			component[edgeList[i][0]-1]=edgeList[i][0];
			component[edgeList[i][1]-1]=edgeList[i][0];
			sizeOfSpanTree++;
		}	
	}

	//Checking if all the vertices are of same component to check all the vertices are covered in span tree
	for(i=0;i<noOfVertices;i++)
	{
		if(component[i]!=-1)
		{
			printf("The graph is a disconneted graph and it cannot have a minimum spanning tree\n");
			exit(0);
		}	
	}
	//If all the vertices are covered in span tree print the span tree
	printMinimumSpanTree(spanTree,sizeOfSpanTree);
	
}

int main()
{
	FILE *fp;
	int sizeOfEdgeList,noOfVertices,token[3],j,i;
	
	//Openeing file
	
	if((fp=fopen(fileName,"r"))==NULL)
	{
		printf("Unable to open the file!!");
		exit(0);
	}
	
	//Reading size of file for total no of edges
	fseek(fp,0L,SEEK_END);
	sizeOfEdgeList=ftell(fp);
	rewind(fp);
	
	//Memory allocation of edge list
	int **edgeList=(int**)malloc(sizeOfEdgeList*sizeof(int*));
	for(i=0;i<sizeOfEdgeList;i++)
		edgeList[i]=(int*)malloc(3*sizeof(int));

	//Memory allocation of span tree
	int **spanTree=(int**)malloc(sizeOfEdgeList*sizeof(int *));
	for(i=0;i<sizeOfEdgeList;i++)
		spanTree[i]=(int*)malloc(3*sizeof(int));
	
	//Reading no of vertices from file(first line)
	fscanf(fp,"%d",&noOfVertices);
	
	//Memory allocation of component of each vertex
	int *component=(int*)malloc(noOfVertices*sizeof(int));
	
	//Initializing each vertex with a unique component
	for(i=0;i<noOfVertices;i++)
		component[i]=i+1;
	
	//Reading edge list from file
	i=0;
	while(fscanf(fp,"%d %d %d",&token[0],&token[1],&token[2])!=EOF)
	{
		for(j=0;j<3;j++)
			edgeList[i][j]=token[j];
		i++;
	}
	sizeOfEdgeList=i;
	fclose(fp);
	
	//Sorting the edge list on the basis of weight
	quickSort(edgeList,0,sizeOfEdgeList-1);
	
	//Finding minimum spanning tree
	findMinimumSpanTree(edgeList,component,spanTree,sizeOfEdgeList,noOfVertices);
	
	return 0;
}

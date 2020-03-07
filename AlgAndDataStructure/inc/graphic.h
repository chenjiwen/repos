#ifndef __GRAPHIC_H__
#define  __GRAPHIC_H__
#pragma once

#include "common.h"
#include "stack.h"
#include <bitset>
using std::bitset;

#define BITSET_NUM 32

typedef enum
{
	GPATH_BFS,
	GPATH_DFS,
	GPATH_DIJK
}GraphPathType;

typedef struct
{
	int nodeKey;
	llist_t list;//out degree list
	llist_t weight_list;
#ifndef USE_BITSET
	llist_t adjlist;//in degree list
#else
	bitset<BITSET_NUM> bitvec;
#endif
	void* data;
}GADTNode;

typedef struct
{
	int nodeKey;
	llist_t list;
	int weight;
}GWeight;

class GADJTable
{
public:
	GADJTable(int num = 0);
	~GADJTable();
	void GAdjtAdd(int toAdd, int nodeKey);
	int NodeOutDegree(int nodeKey);
	int NodeInDegree(int nodeKey);
	GADTNode* TransferGADJT();
	int PathNum(int from, int to);
	GADJTable* SquareG();
	GADTNode* GetVertexNode(int i);

private:
	int nodeNum;
	GADTNode* table;
};

typedef struct
{
	bool  visited;
	int   dist;
	int   path;
}TableEntry, GPATHTable;

class Graph
{
public:
	Graph(int vertexNum);
	Graph();
	~Graph();
	void GraphBuildADJTable(vector<vector<int>> &vec);
	void GraphBuildWeightTable(int weight, int from, int to);
	int GrapGetWeight(int from, int to);
	int* GraphTopSort();
	int* GraphTopSortByStack();
	void GraphBFS(int start_vertex);
	void* GraphDijkstra(int start_vetx);
	void PathPrint(GraphPathType pathType, int start_vtex);
	void PathPrint(GPATHTable* pathTable, int start_vtex);

private:
	GADJTable *pGAdjTable;
	int* TopTable;
	int VNum;
	GPATHTable* pBFSTable;
	bool has_loop;
	int  loop_vertex;
	int  start_vertex;
	int  dijk_vtex;
	vector<vector<int>> weightVec;

};




#endif

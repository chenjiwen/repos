#include "common.h"
#include "graphic.h"
#include "queue.h"
#include "binary_heap.h"
#include <iostream>
using namespace std;


GADJTable::GADJTable(int num) :nodeNum(num), table(NULL)
{
	if (nodeNum) {
		table = new GADTNode[nodeNum];
		for (int i = 0; i < nodeNum; i++)
		{
			table[i].nodeKey = i + 1;
		}
	}
}

GADJTable::~GADJTable()
{
	llist_t* plist = NULL, *next = NULL;
	int i = 0;
	GADTNode* pNode = NULL;
	for (i = 0; i < nodeNum; i++)
	{
		//free the pnode linked to table[i].list
		plist = table[i].list.next;
		while (plist)
		{   
			next = plist->next;
			pNode = container_of(plist, GADTNode, list);
			delete pNode;
			plist = next;
		}
#ifndef USE_BITSET	
		//free the pnode linked to table[i].adjlist
		plist = table[i].adjlist.next;
		while (plist)
		{
			next = plist->next;
			pNode = container_of(plist, GADTNode, adjlist);
			delete pNode;
			plist = next;
		}
#else

#endif
	}
	
	delete[] table;
}

/*
 * Add one Edge information into the Adj table
 *
 *
 */

void GADJTable::GAdjtAdd(int toAdd, int nodeKey)
{
	llist_t* plist = NULL;
	GADTNode* pNode = NULL;

	pNode = new GADTNode();
	pNode->nodeKey = nodeKey;
	//node key need transfer to index of table
	plist = &table[toAdd - 1].list;
	while (plist->next)
	{
		plist = plist->next;
	}

	llist_add(plist, &pNode->list);

#ifndef USE_BITSET
	plist = &table[nodeKey - 1].adjlist;
	pNode = new GADTNode();
	pNode->nodeKey = toAdd;
	while (plist->next)
	{
		plist = plist->next;
	}
	llist_add(plist, &pNode->adjlist);
#else
	pNode = &table[toAdd - 1];
	pNode->bitvec.set(toAdd - 1);
#endif
}

int GADJTable::NodeOutDegree(int nodeKey)
{
	int count = 0;
	llist_t* plist = NULL;

	plist = table[nodeKey - 1].list.next;
	while (plist)
	{
		count++;
		plist = plist->next;
	}

	return count;
}

int GADJTable::NodeInDegree(int nodeKey)
{
	int i = 0;
	int count = 0;
	llist_t* plist = NULL;
	GADTNode* node = NULL;

	for (int i = 0; i < nodeNum; i++)
	{
		plist = table[i].list.next;
		while (plist)
		{
			node = container_of(plist, GADTNode, list);
			if (node->nodeKey == nodeKey)
			{
				count++;
			}
			plist = plist->next;
		}
	}

	return count;
}

GADTNode* GADJTable::TransferGADJT()
{
	GADTNode* trans = NULL, *pNode = NULL;
	int i = 0;
	llist_t* plist = NULL;


	trans = new GADTNode[nodeNum];
	for (int i = 0; i < nodeNum; i++)
	{
		//trans[i].nodeKey = i;
		plist = table[i].list.next;
		while (plist)
		{
			pNode = container_of(plist, GADTNode, list);
			trans[pNode->nodeKey - 1].nodeKey = pNode->nodeKey;
			llist_add(&trans[pNode->nodeKey - 1].list, &pNode->list);
		}
	}

	return trans;
}

int GADJTable::PathNum(int from, int to) 
{
	pllist_t plist = NULL;
	GADTNode* pNode = NULL;
	int num = 0;

	plist = table[from - 1].list.next;
	while (plist)
	{
		pNode = container_of(plist, GADTNode, list);
		if (pNode->nodeKey == to)
		{
			num += 1;
		}
		else
		{
			num += PathNum(pNode->nodeKey, to);
		}

		plist = plist->next;
	}

	return num;
}

GADJTable* GADJTable::SquareG() {
	llist_t* plist = NULL;
	GADTNode* pNode = NULL;
	GADJTable *Adjtable = NULL;
	int i = 0;

	Adjtable = new GADJTable(nodeNum);
	for (i = 0; i < nodeNum; i++)
	{
		plist = table[i].list.next;
		while (plist)
		{
			pNode = container_of(plist, GADTNode, list);
			if (PathNum(table[i].nodeKey, pNode->nodeKey) <= 2)
			{
				Adjtable->GAdjtAdd(table[i].nodeKey, pNode->nodeKey);
			}
			plist = plist->next;
		}
	}

	return Adjtable;
}

GADTNode* GADJTable::GetVertexNode(int i)
{
	return table + i;
}

void graphic_test()
{
	GADJTable GAdjT(4);
	GADJTable *pGSquare;
	int inDgree = 0;
	int outDegree = 0;
	int pathNum = 0;

	GAdjT.GAdjtAdd(1, 2);
	GAdjT.GAdjtAdd(1, 3);
	GAdjT.GAdjtAdd(3, 4);
	GAdjT.GAdjtAdd(3, 2);
	GAdjT.GAdjtAdd(4, 2);

	inDgree = GAdjT.NodeInDegree(1);
	outDegree = GAdjT.NodeOutDegree(1);

	inDgree = GAdjT.NodeInDegree(2);
	outDegree = GAdjT.NodeOutDegree(2);

	pathNum = GAdjT.PathNum(1, 2);

	pGSquare = GAdjT.SquareG();
}

Graph::Graph():VNum(0), pGAdjTable(NULL), TopTable(NULL), pBFSTable(NULL), pDijTable(NULL)
{

}

Graph::Graph(int num) :VNum(num)
{
	pGAdjTable = new GADJTable(num);
	TopTable = new int[num];
	memset(TopTable, 0, sizeof(*TopTable) * num);
	pBFSTable = new GPATHTable[num];
	memset(pBFSTable, 0, sizeof(*pBFSTable)*num);
}

Graph::~Graph()
{
	delete pGAdjTable;
	if (TopTable)
	{
		delete[] TopTable;
	}
	
	if (pBFSTable)
	{
		delete []pBFSTable;
	}

	if(pDijTable)
	{
		delete []pDijTable;
	}
}

void Graph::GraphBuildADJTable(vector<vector<int>>& vec)
{
	int vertexId = 1;
	vector<vector<int>>::iterator iter = vec.begin();

	while (iter != vec.end())
	{
		vector<int> vect = *iter;
		for (size_t i = 0; i < vect.size(); i++)
		{
			pGAdjTable->GAdjtAdd(vertexId, vect[i]);
		}
		vertexId++;
		iter++;
	}
}

void Graph::GraphBuildWeightTable(int weight, int from, int to)
{
	GWeight* pNode = NULL;
	pNode = new GWeight;

	pNode->nodeKey = to;
	pNode->weight = weight;
	llist_add(&pGAdjTable->GetVertexNode(from - 1)->weight_list, &pNode->list);
}

int Graph::GrapGetWeight(int from, int to)
{
	llist_t* plist = NULL;
	GWeight* wNode = NULL;

	plist = (pGAdjTable->GetVertexNode(from - 1))->weight_list.next;
	while (plist)
	{
		wNode = container_of(plist, GWeight, list);
		if (wNode->nodeKey == to)
		{
			return wNode->weight;
		}
		plist = plist->next;
	}

	return -1;
}

int* Graph::GraphTopSort()
{
	int* InDegTbl = NULL;
	LinearQue LQue(VNum);
	int i = 0;
	int counter = 0;
	llist_t* plist = NULL;
	GADTNode* V, * W;

	InDegTbl = new int[VNum];
	memset(InDegTbl, 0, sizeof(int) * VNum);

	for (i = 0; i < VNum; i++)
	{
		InDegTbl[i] = pGAdjTable->NodeInDegree(i + 1);
		if (InDegTbl[i] == 0)
		{
			LQue.Enqueue(pGAdjTable->GetVertexNode(i));
		}
	}

	while (!LQue.QueEmpty())
	{
		V = (GADTNode*)LQue.Dequeue();
		TopTable[counter++] = V->nodeKey;
		if (counter >= VNum) {
			has_loop = true;
			loop_vertex = V->nodeKey;
			break;
		}

		plist = V->list.next;
		while (plist)
		{
			W = container_of(plist, GADTNode, list);
			plist = plist->next;
			
			if (--InDegTbl[W->nodeKey - 1] == 0)
			{
				LQue.Enqueue(pGAdjTable->GetVertexNode(W->nodeKey - 1));
			}
		}
	}

	if (!has_loop && counter < VNum)
	{
		has_loop = true;
	}

	delete InDegTbl;

	return TopTable;
}

int* Graph::GraphTopSortByStack()
{
	int* OutDegTbl = NULL;
	stack stack(VNum);
	int i = 0;
	int counter = 0;
	llist_t* plist = NULL;
	GADTNode* V, * W;

	OutDegTbl = new int[VNum];
	memset(OutDegTbl, 0, sizeof(int) * VNum);

	for (i = 0; i < VNum; i++)
	{
		OutDegTbl[i] = pGAdjTable->NodeOutDegree(i + 1);
		if (OutDegTbl[i] == 0)
		{
			stack.push(pGAdjTable->GetVertexNode(i));
		}
	}

	while (!stack.stack_empty())
	{
		V = (GADTNode*)stack.pop();
		TopTable[counter++] = V->nodeKey;

		plist = V->adjlist.next;
		while (plist)
		{
			W = container_of(plist, GADTNode, adjlist);
			plist = plist->next;

			if (--OutDegTbl[W->nodeKey - 1] == 0)
			{
				stack.push(pGAdjTable->GetVertexNode(W->nodeKey - 1));
			}
		}
	}

	delete OutDegTbl;

	return TopTable;
}



GADTNode* Graph::GraphGetTableNode(int node_id)
{
	return pGAdjTable->GetVertexNode(node_id);
}

GPATHTable test_table[20];

void* Graph::GraphDijkstra(int start_vetx)
{
	FibHeap fibHeap;
	GPATHTable* pGPATHDijkTable = NULL;
	int i = 0, nodeKey;
	//pGPATHDijkTable = new GPATHTable[VNum];
	pGPATHDijkTable = test_table;
	FibHeapNode* pMinNode = NULL, *pFibTNode = NULL;
	GADTNode* pNodeV = NULL, *pNodeW = NULL;
	llist_t* plist = NULL;
	int weight = 0;

	for (i = 0; i < VNum; i++)
	{
		pGPATHDijkTable[i].visited = false;
		pGPATHDijkTable[i].dist = INT_MAX;
		pGPATHDijkTable[i].path = -1;
	}


	//dist is the key of FibHeap
	pGPATHDijkTable[start_vetx - 1].dist = 0;
	pGPATHDijkTable[i].path = 0;

	dijk_vtex = start_vetx;

	//pNodeV = pGAdjTable->GetVertexNode(start_vetx - 1);
	//derive the node table list for start vertex
	pNodeV = GraphGetTableNode(start_vetx - 1);

	//since the dist is the key of FibHeap, need map the between dist and node
	//store the fibHeap node in the table[nodeKey]->data for the nodeKey so that we can decrease key
	//else need find/search the fibNode when decrease the key
	pNodeV->data = fibHeap.FibHeapInsert(pGPATHDijkTable[start_vetx - 1].dist, pNodeV);

	for (;;)
	{
		//get the min dist from FibHeap
		pMinNode = fibHeap.FibHeapExtractMin();
		
		if (!pMinNode)
		{
			break;
		}

		//get the table Node/node key from the minNode of fibHeap
		pNodeV = static_cast<GADTNode*>(pMinNode->priv);

		//update the Dijkstra table for the node
		pGPATHDijkTable[pNodeV->nodeKey - 1].visited = true;

		//remember delete/release the pMinNode here
		delete pMinNode;

		//deriver the adjcent table of NodeV
		plist = pNodeV->list.next;
		while (plist)
		{
			//node adjcent to nodeV
			pNodeW = container_of(plist, GADTNode, list);
			nodeKey = pNodeW->nodeKey;
			if (!pGPATHDijkTable[nodeKey - 1].visited)
			{
				//weight = weightVec[pNodeV->nodeKey - 1][pNodeW->nodeKey - 1];
				weight = GrapGetWeight(pNodeV->nodeKey, pNodeW->nodeKey);
				if (pGPATHDijkTable[nodeKey - 1].dist == INT_MAX)
				{
					//update the dist of the node adjcent to NodeV for the first time and add the dist into FibHeap
					pGPATHDijkTable[nodeKey - 1].dist = pGPATHDijkTable[pNodeV->nodeKey - 1].dist + weight;
					pGPATHDijkTable[nodeKey - 1].path = pNodeV->nodeKey;
					//pNodeW = pGAdjTable->GetVertexNode(pNodeW->nodeKey - 1);
					pNodeW = GraphGetTableNode(nodeKey - 1);
					pNodeW->data = fibHeap.FibHeapInsert(pGPATHDijkTable[nodeKey - 1].dist, pNodeW);
				}
				else if (pGPATHDijkTable[pNodeV->nodeKey - 1].dist + weight < pGPATHDijkTable[pNodeW->nodeKey - 1].dist)
				{
					//update the dist of the Dijkstra table and decrease the key of the FibHeapNode
					pGPATHDijkTable[nodeKey - 1].dist = pGPATHDijkTable[pNodeV->nodeKey - 1].dist + weight;
					pGPATHDijkTable[nodeKey - 1].path = pNodeV->nodeKey;
					pNodeW = GraphGetTableNode(nodeKey - 1);
					fibHeap.FibHeapDecreseKey((FibHeapNode*)pNodeW->data, pGPATHDijkTable[nodeKey - 1].dist);
				}
			}
			plist = plist->next;
		}
	}

	return pGPATHDijkTable;
}

void Graph::GraphBFS(int start_vertex)
{
	LinearQue linearQue;
	GADTNode* pNode = NULL, *pTemp = NULL;
	llist_t* plist = NULL;
	int i = 0;

	for (i = 0; i < VNum; i++)
	{
		pBFSTable[i].dist = INT_MAX;
	}
	pBFSTable[start_vertex - 1].dist = 0;
	this->start_vertex = start_vertex;
	linearQue.Enqueue(pGAdjTable->GetVertexNode(start_vertex - 1));
	while (!linearQue.QueEmpty())
	{
		pNode = static_cast<GADTNode*>(linearQue.Dequeue());
		plist = pNode->list.next;
		while (plist)
		{
			pTemp = container_of(plist, GADTNode, list);
			//只有没有处理过的时候，才需要更新，如果处理过，例如图中有环，节点处理过就不要再处理
			if (pBFSTable[pTemp->nodeKey - 1].dist == INT_MAX)
			{
				pBFSTable[pTemp->nodeKey - 1].dist = pBFSTable[pNode->nodeKey - 1].dist + 1;
				pBFSTable[pTemp->nodeKey - 1].path = pNode->nodeKey;
				linearQue.Enqueue(pGAdjTable->GetVertexNode(pTemp->nodeKey - 1));
			}

			plist = plist->next;
		}
	}
}

int time = 0;

GDFSTable* Graph::GraphDFS()
{
	GDFSTable* pGDFSTbl = NULL;
	pGDFSTbl = new GDFSNode[VNum];
	int i = 0;

	for (i = 0; i < VNum; i++)
	{
		pGDFSTbl[i].color = GNODE_WHITE;
		pGDFSTbl[i].discover = 0;
		pGDFSTbl[i].finish = 0;
		pGDFSTbl[i].prev = -1;
	}
	time = 0;
	for (i = 0; i < VNum; i++)
	{
		if (pGDFSTbl[i].color == GNODE_WHITE)
		{
			GraphDFSVisit(pGDFSTbl, pGAdjTable, i + 1);
		}
	}
	return pGDFSTbl;
}

void Graph::GraphDFSVisit(GDFSTable* pGDFSTbl, GADJTable* pGadjTbl, int vertex)
{
	int i = 0;
	pllist_t plist = NULL;
	GADTNode* pNode = NULL, *pTblEntry = NULL;

	time++;
	pGDFSTbl[vertex - 1].discover = time;
	pGDFSTbl[vertex - 1].color = GNODE_GRAY;

	pTblEntry = GraphGetTableNode(vertex);
	plist = pTblEntry->list.next;
	while (plist)
	{
		pNode = container_of(plist, GADTNode, list);
		if (pGDFSTbl[pNode->nodeKey - 1].color == GNODE_WHITE)
		{
			pGDFSTbl[pNode->nodeKey - 1].prev = vertex;
			GraphDFSVisit(pGDFSTbl, pGadjTbl, pNode->nodeKey);
		}
		plist = plist->next;
	}
	time++;
	pGDFSTbl[vertex - 1].finish = time;
	pGDFSTbl[vertex - 1].color = GNODE_BLACK;
}

int degree[10];
bool visited[10];

void Graph::GraphVisitEdgeTwice(int vertex)
{
	stack Stack;
	LinearQue LQue;
	int i = 0;
	pllist_t plist = NULL;
	GADTNode* pNode = NULL, *pNodeW = NULL, *pNodeV;
	int count = 0;
	bool first = true;

	for (i = 0; i < VNum; i++)
	{
		degree[i] = GrapNodeInOutDegree(i + 1);
		visited[i] = false;
	}
	cout << "\n \t GraphVisitEdgeTwice:" << endl;
	pNode = GraphGetTableNode(vertex - 1);

	Stack.push(pNode);
	count++;
	while (!Stack.stack_empty())
	{
		if (count >= VNum)
		{
			break;
		}
		pNode = static_cast<GADTNode*>(Stack.get_top());
		pNode = GraphGetTableNode(pNode->nodeKey - 1);
		plist = pNode->list.next;
		while (plist)
		{
			pNodeW = container_of(plist, GADTNode, list);
			if (!visited[pNodeW->nodeKey - 1])
			{
				LQue.Enqueue(pNodeW);
				degree[pNode->nodeKey - 1]--;
				degree[pNodeW->nodeKey - 1]--;
			}

			plist = plist->next;
		}

		while(!LQue.QueEmpty())
		{
			pNodeW = static_cast<GADTNode*>(LQue.Dequeue());
			if (!LQue.QueEmpty())
			{
				cout << pNode->nodeKey << "->" << pNodeW->nodeKey << endl;
				cout << pNodeW->nodeKey << "->" << pNode->nodeKey << endl;
				degree[pNodeW->nodeKey - 1]--;
				degree[pNode->nodeKey - 1]--;
			}
			else
			{
				cout << pNode->nodeKey << "->" << pNodeW->nodeKey << endl;
				Stack.push(pNodeW);
				count++;
				visited[pNode->nodeKey - 1] = true;
				//degree[pNode->nodeKey - 1]--;
				//degree[pNodeW->nodeKey - 1]--;
			}
		}
	}

	pNodeW = (GADTNode*)Stack.pop();
	while (!Stack.stack_empty())
	{
		pNodeV = (GADTNode*)Stack.pop();
		degree[pNodeV->nodeKey - 1]--;
		degree[pNodeW->nodeKey - 1]--;
		cout << pNodeW->nodeKey << "->" << pNodeV->nodeKey << endl;
		pNodeW = pNodeV;
	}
}

int Graph::GraphNodeOutDegree(int vertex)
{
	return pGAdjTable->NodeOutDegree(vertex);
}

int Graph::GrapNodeInDegree(int vertex)
{
	return pGAdjTable->NodeInDegree(vertex);
}

int Graph::GrapNodeInOutDegree(int vertex)
{
	return GraphNodeOutDegree(vertex) + GrapNodeInDegree(vertex);
}

void Graph::PathPrint(GPATHTable* pathTable, int to_vtex)
{
	cout << to_vtex;
	while(pathTable && pathTable[to_vtex - 1].path)
	{
		cout << "<-" <<pathTable[to_vtex - 1].path;
		to_vtex = pathTable[to_vtex - 1].path;
	}
	cout << endl;
}

void Graph::PathPrint(GraphPathType pathType, int start_vtex)
{
	GPATHTable* pathTable = pBFSTable;

	cout << "Path print:" << endl;
	for (int i = 1; i <= VNum; i++)
	{
		PathPrint(pathTable, i);
		if (i != VNum)
		{
			cout << "Next path:" << endl;
		}	    
	}
}

void graph_test()
{
	Graph graph(7);
	int* ptable = NULL;
	vector<int> vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8;
	vector<vector<int>> adj_vec;
	vector<int> wt1, wt2, wt3, wt4, wt5, wt6, wt7;
	int i = 0;
/*
	vec1.push_back(2);
	vec1.push_back(4);
	//vec1.push_back(3);

	vec2.push_back(4);
	vec2.push_back(5);

	vec3.push_back(6);
	vec3.push_back(1);

	vec4.push_back(3);
	vec4.push_back(7);
	vec4.push_back(5);
	vec4.push_back(6);

	//vec5.push_back(4);
	vec5.push_back(7);

	//vec6.push_back(4);
	
	vec7.push_back(6);

	adj_vec.push_back(vec1);
	adj_vec.push_back(vec2);
	adj_vec.push_back(vec3);
	adj_vec.push_back(vec4);
	adj_vec.push_back(vec5);
	adj_vec.push_back(vec6);
	adj_vec.push_back(vec7);

	graph.GraphBuildWeightTable(2, 1, 2);
	graph.GraphBuildWeightTable(1, 1, 4);

	graph.GraphBuildWeightTable(10, 2, 5);
	graph.GraphBuildWeightTable(3, 2, 4);

	graph.GraphBuildWeightTable(4, 3, 1);
	graph.GraphBuildWeightTable(5, 3, 6);

	graph.GraphBuildWeightTable(2, 4, 3);
	graph.GraphBuildWeightTable(8, 4, 6);
	graph.GraphBuildWeightTable(4, 4, 7);
	graph.GraphBuildWeightTable(2, 4, 5);

	graph.GraphBuildWeightTable(6, 5, 7);

	graph.GraphBuildWeightTable(1, 7, 6);


	//graph.GraphBuildADJTable(adj_vec);
	//ptable = graph.GraphTopSort();
	//ptable = graph.GraphTopSortByStack();
	//graph.GraphBFS(3);
	//graph.GraphDijkstra(1);
	//cout << "\n Topsort order:" << endl;
	//for (i = 0; i < 7; i++)
	//{
	//	cout << " " << ptable[i] <<" ";
	//}
	//cout << endl;

	//graph.PathPrint(GPATH_BFS, 3);
*/

/*
	vec1.push_back(2);
	vec1.push_back(7);
	vec1.push_back(6);

	vec2.push_back(1);
	vec2.push_back(7);
	vec2.push_back(3);

	vec3.push_back(2);
	vec3.push_back(7);
	vec3.push_back(4);

	vec4.push_back(3);
	vec4.push_back(7);
	vec4.push_back(5);

	vec5.push_back(4);
	vec5.push_back(7);
	vec5.push_back(6);

	vec6.push_back(1);
	vec6.push_back(7);
	vec6.push_back(5);

	vec7.push_back(1);
	vec7.push_back(2);
	vec7.push_back(3);
	vec7.push_back(4);
	vec7.push_back(5);
	vec7.push_back(6);
*/


	adj_vec.push_back(vec1);
	adj_vec.push_back(vec2);
	adj_vec.push_back(vec3);
	adj_vec.push_back(vec4);
	adj_vec.push_back(vec5);
	adj_vec.push_back(vec6);
	adj_vec.push_back(vec7);

	graph.GraphBuildADJTable(adj_vec);
	graph.GraphVisitEdgeTwice(1);
}
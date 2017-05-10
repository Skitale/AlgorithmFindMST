#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
using namespace std;

struct edge_s {    /* структура, представляющая одно ребро*/
	int v;
	int u;
	int weight;
};


struct u_node {/* Система непересекающихся множеств*/
	u_node * parent;
	int depth;

	u_node(){
		parent = NULL;
		depth = 0;
	};
};


int n;    // Количество вершин в графе 
int m;       // Количество ребер в плотном графе
int sm;  // Количество ребер в разреженном графе

edge_s * edges;     // Массив ребер(плотный)
edge_s * s_edges; // Массив ребер(разреженный)

edge_s * resultPrim;
edge_s * resultKruskal;

u_node * uf_set; /* Массив, указывающий, какая вершина какому множеству принадлежит. */


void print_edges() {
	if (n < 10){
		printf("Edges of the dense graph:\n");
		for (int i = 0; i < m; i++) {
			printf("(%d,%d) = %d\n", edges[i].v, edges[i].u, edges[i].weight);
		}

		printf("Edges of the rare graph:\n");
		for (int i = 0; i < sm; i++) {
			printf("(%d,%d) = %d\n", s_edges[i].v, s_edges[i].u, s_edges[i].weight);
		}
	}
	else{
		printf("Show edges of the graph with %d vertices ?\n", n);
		printf("(Y/N)\n");
		char simb;
		cin >> simb;
		if (simb == 'Y'){
			printf("Edges of the dense graph:\n");
			for (int i = 0; i < m; i++) {
				printf("(%d,%d) = %d\n", edges[i].v, edges[i].u, edges[i].weight);
			}

			printf("Edges of the rare graph:\n");
			for (int i = 0; i < sm; i++) {
				printf("(%d,%d) = %d\n", s_edges[i].v, s_edges[i].u, s_edges[i].weight);
			}
		}
	}
}

int EdgeInGraph(int A, int B, int end, edge_s * ed)//есть ли уже такое ребро в графе
{

	for (int i = 0; i<end; i++)
		if (ed[i].v == A && ed[i].u == B || ed[i].v == B && ed[i].u == A)
			return i;
	return -1;
}

//генерация ребер в графе (самого графа)
void GenerateGraph(int n, int &m)
{
	m = n*2;
	int weight, v1, v2, fl;
	bool flag;

	if (edges == NULL){
		edges = new edge_s[m];
	}
	else {
		delete[]edges;
		edges = new edge_s[m];
	}

	//делаем граф связным
	for (int i = 0; i<n - 1; i++)
	{
		weight = rand() % n + 1;
		edges[i] = { i, i + 1, weight };
	}
	for (int i = n - 1; i<m; i++)
	{
		int sl = 0;
		v1 = rand() % n;
		flag = false;
		while (flag == false)
		{
			v2 = v1;
			while (v2 == v1)
				v2 = rand() % n;
			weight = rand() % n + 1;
			fl = EdgeInGraph(v1, v2, i, edges);
			if (fl == -1) flag = true;
			else sl++;
			if (sl>2)
			{
				sl = 0;
				v1 = rand() % n;
			}
		}
		edges[i] = { v1, v2, weight };
	}
}

void GenerateSparseGraph(int n, int &m){
	m = n;
	int weight, v1, v2, fl;
	bool flag;

	if (s_edges == NULL){
		s_edges = new edge_s[m];
	}
	else {
		delete[]s_edges;
		s_edges = new edge_s[m];
	}

	//делаем граф связным
	for (int i = 0; i<n - 1; i++)
	{
		weight = rand() % n + 1;
		s_edges[i] = { i, i + 1, weight };
	}
	for (int i = n - 1; i<m; i++)
	{
		int sl = 0;
		v1 = rand() % n;
		flag = false;
		while (flag == false)
		{
			v2 = v1;
			while (v2 == v1)
				v2 = rand() % n;
			weight = rand() % n + 1;
			fl = EdgeInGraph(v1, v2, i, s_edges);
			if (fl == -1) flag = true;
			else sl++;
			if (sl>1)
			{
				sl = 0;
				v1 = rand() % n;
			}
		}
		s_edges[i] = { v1, v2, weight };
	}
}


void finalize() {
	delete[]uf_set;
	delete[]edges;
	delete[]s_edges;
}
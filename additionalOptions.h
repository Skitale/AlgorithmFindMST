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




edge_s * resultPrim;
edge_s * resultKruskal;

edge_s * s_edges; // Массив ребер(разреженный)
int ** s_weightMatr;
bool ** s_connectivityMatr; // матрица смежности

edge_s * edges;     // Массив ребер(плотный)
int ** weightMatr;
bool ** connectivityMatr; // матрица смежности

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
		printf("Show edges of the graph with %d vertices ? (Y/N)\n", n);
		char simb;
		cin >> simb;
		if (simb == 'Y' || simb == 'y'){
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

//генерация ребер в графе
void generateDenseGraph(int n, int &m){
	int activ_m = 0;
	int weight = 0;
	int const kf = n*(n - 1) / 2;

	weightMatr = new int*[n];
	connectivityMatr = new bool*[n];

	for (int i = 0; i < n; i++){
		connectivityMatr[i] = new bool[n];
		weightMatr[i] = new int[n];
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			connectivityMatr[i][j] = false;
			weightMatr[i][j] = -1;
		}
	}


	for (int i = 1; i < n; i++){
		weight = rand() % kf;
		connectivityMatr[0][i] = true;
		weightMatr[0][i] = weight;
		activ_m++;
	}

	int val = 0;

	for (int i = 1; i < n; i++){
		for (int j = i + 1; j < n; j++){
			val = rand() % 3;
			weight = rand() % kf;
			if ((bool)val){
				connectivityMatr[i][j] = true;
				weightMatr[i][j] = weight;
				activ_m++;
			}
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			weightMatr[j][i] = weightMatr[i][j];
			connectivityMatr[j][i] = connectivityMatr[i][j];
		}
	}

	for (int i = 0; i < n; i++){
		weightMatr[i][i] = -1;
		connectivityMatr[i][i] = false;
	}


	m = activ_m;
	//for (int i = 0; i < n; i++){
	//	for (int j = 0; j < n; j++){
	//		cout << connectivityMatr[i][j];
	//	}
	//	cout << endl;
	//}

	//for (int i = 0; i < n; i++){
	//	for (int j = 0; j < n; j++){
	//		cout << weightMatr[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	if (edges == NULL){
		edges = new edge_s[m];
	}
	else {
		delete[]edges;
		edges = new edge_s[m];
	}

	int k = 0;
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			if (connectivityMatr[i][j]){
				edges[k++] = { i, j, weightMatr[i][j] };
			}
		}
	}

}

void generateRareGraph(int n, int &m){
	int activ_m = 0;
	int weight = 0;
	int const kf = n*(n - 1) / 2;

	s_weightMatr = new int*[n];
	s_connectivityMatr = new bool*[n];

	for (int i = 0; i < n; i++){
		s_connectivityMatr[i] = new bool[n];
		s_weightMatr[i] = new int[n];
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			s_connectivityMatr[i][j] = false;
			s_weightMatr[i][j] = -1;
		}
	}


	for (int i = 1; i < n; i++){
		weight = rand() % kf;
		s_connectivityMatr[0][i] = true;
		s_weightMatr[0][i] = weight;
		activ_m++;
	}

	int val = 0;
	for (int i = 1; i < n; i++){
		for (int j = i + 1; j < n; j++){
			val = rand() % 150;
			weight = rand() % kf;
			if (!((bool)val)){
				s_connectivityMatr[i][j] = true;
				s_weightMatr[i][j] = weight;
				activ_m++;
			}
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			s_weightMatr[j][i] = s_weightMatr[i][j];
			s_connectivityMatr[j][i] = s_connectivityMatr[i][j];
		}
	}

	for (int i = 0; i < n; i++){
		s_weightMatr[i][i] = -1;
		s_connectivityMatr[i][i] = false;
	}


	m = activ_m;
	//for (int i = 0; i < n; i++){
	//	for (int j = 0; j < n; j++){
	//		cout << s_connectivityMatr[i][j];
	//	}
	//	cout << endl;
	//}

	//for (int i = 0; i < n; i++){
	//	for (int j = 0; j < n; j++){
	//		cout << s_weightMatr[i][j] << " ";
	//	}
	//	cout << endl;
	//}

	if (s_edges == NULL){
		s_edges = new edge_s[m];
	}
	else {
		delete[]s_edges;
		s_edges = new edge_s[m];
	}

	int k = 0;
	for (int i = 0; i < n; i++){
		for (int j = i + 1; j < n; j++){
			if (s_connectivityMatr[i][j]){
				s_edges[k++] = { i, j, s_weightMatr[i][j] };
			}
		}
	}

	//for (int i = 0; i < k; i++) {
	//	printf("(%d,%d) = %d\n", s_edges[i].v, s_edges[i].u, s_edges[i].weight);
	//}

}

void generateSparseGraph(int n, int &m){ // function has become outdated
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
	for (int i = 0; i < m; i++) {
		printf("(%d,%d) = %d\n", s_edges[i].v, s_edges[i].u, s_edges[i].weight);
	}
}


void finalize() {
	delete[]edges;
	delete[]s_edges;
}
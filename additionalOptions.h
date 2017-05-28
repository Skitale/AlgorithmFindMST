#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
using namespace std;

struct edge_s {  // Structure representing a edge
	int v;
	int u;
	int weight;
};


struct u_node { // disjoint-set
 	u_node * parent;
	int depth;

	u_node(){
		parent = NULL;
		depth = 0;
	};
};


int n;   // Number of vertices in the main graph 
int m;   //Number of edges in the dense graph
int sm;  //Number of edges in the rare graph

edge_s * resultPrim; 
edge_s * resultKruskal;
edge_s * resultBoruvka;


edge_s * s_edges; // Array of edges(Rarefied)
int ** s_weightMatr; // Array of wight
bool ** s_connectivityMatr; // Adjacency matrix

edge_s * edges;     // Array of edges(Dense)
int ** weightMatr; // Array of wight
bool ** connectivityMatr; // Adjacency matrix

u_node * uf_set; // Array of node for disjoint-set 

//uf
void uf_make() {
	int size = n;// + (number_of_vertices - 1);
	uf_set = new u_node[size];
	memset(uf_set, 0, size * sizeof(u_node));
}

u_node * uf_find(u_node * a) {
	if (a->parent == NULL) return a;
	else return (a->parent = uf_find(a->parent));
}

void uf_union(u_node * a, u_node * b) {
	if (a->depth > b->depth) {
		b->parent = a;
	}
	else if (a->depth<b->depth) {
		a->parent = b;
	}
	else {
		a->parent = b;
		a->depth += 1;
	}
}

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

int EdgeInGraph(int A, int B, int end, edge_s * ed)//is Exits of edge
{

	for (int i = 0; i<end; i++)
		if (ed[i].v == A && ed[i].u == B || ed[i].v == B && ed[i].u == A)
			return i;
	return -1;
}

//generate edges of graph
void generateDenseGraph(int n, int &m){
	double nf = n;
	int activ_m = 0;
	int weight = 0;									// (n^2)*(8/18)
	double kf = (nf / (nf - 1))*(8.0 / 9.0); // The ratio of the number of edges in a dense graph to the number of edges in a complete graph of "n" vertices
	int const weightKf = n*(n - 1) / 2; 

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
		weight = rand() % weightKf;
		connectivityMatr[0][i] = true;
		weightMatr[0][i] = weight;
		activ_m++;
	}

	int val = 0;
	kf *= 100;
	for (int i = 1; i < n; i++){
		for (int j = i + 1; j < n; j++){
			val = rand() % 100 + 1;
			weight = rand() % weightKf;
			if (val <= kf){
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
	printf("The number of generated edges in the dense graph: %u\n", m);
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
	double nf = n;
	int activ_m = 0;
	int weight = 0;				// 125*n
	double kf = 250 / (nf - 1); // The ratio of the number of edges in a dense graph to the number of edges in a complete graph of "n" vertices
	int const weightKf = n*(n - 1) / 2;

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
		weight = rand() % weightKf;
		s_connectivityMatr[0][i] = true;
		s_weightMatr[0][i] = weight;
		activ_m++;
	}

	int val = 0;
	kf *= 100;
	for (int i = 1; i < n; i++){
		for (int j = i + 1; j < n; j++){
			val = rand() % 100 + 1;
			weight = rand() % weightKf;
			if (val <= kf){
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
	printf("The number of generated edges in the rare graph: %u\n", m);
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

	//הוכאול דנאפ סגÿחםûל
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


void finalizeArray(int *** weightMatr, bool *** connectivityMatr){
	for (int i = 0; i < n; i++){
		delete[](*weightMatr)[i];
		delete[](*connectivityMatr)[i];
	}
	delete[]*weightMatr;
	delete[]*connectivityMatr;
}
void finalize() {
	delete[]edges;
	delete[]s_edges;
}


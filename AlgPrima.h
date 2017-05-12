#pragma once
#include "additionalOptions.h"

int msf_edge_count_pr;  /* Количество ребер в массиве ребер MSF Prim*/

inline bool check_label(int *label, int size)
{
	for (int i = 0; i < size; i++)
		if(label[i] == 0) return true;
	return false;
}

void print_msf_edges_prim() {
	printf("Prim MSF edges:\n");
	for (int i = 0; i < msf_edge_count_pr; i++) {
		printf("(%d,%d) = %d\n", resultPrim[i].v, resultPrim[i].u, resultPrim[i].weight);
	}
}

void find_msf_Prim(edge_s * edges, int m, double &finTime) {

	resultPrim = new edge_s[n - 1];
	msf_edge_count_pr = 0;

	int a, b = 0;
	int* label = new int[n];
	for (int i = 1; i<n; i++)
		label[i] = 0;
	label[0] = 1;//начинаем с 0 вершины
	int index = 0;
	while (check_label(label, n))
	{
		int minWeight = INT_MAX;
		for (int i = 0; i<m; i++)
		{
			a = edges[i].v;
			b = edges[i].u;
			if ((label[a] == 1 && label[b] == 0) || (label[a] == 0 && label[b] == 1))
				if (edges[i].weight < minWeight)
				{
					index = i;
					minWeight = edges[i].weight;
				}
		}
		label[edges[index].v] = 1;
		label[edges[index].u] = 1;
		resultPrim[msf_edge_count_pr++] = { edges[index].v, edges[index].u, edges[index].weight };
	}

	finTime = clock();
	
	std::qsort(resultPrim, n - 1, sizeof(edge_s), compare_edges);
	print_msf_edges_prim();
	delete[]resultPrim;
}


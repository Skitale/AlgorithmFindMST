#pragma once
#include "additionalOptions.h"

int msf_edge_count_pr;  /* Количество ребер в массиве ребер MSF Prim*/

bool Metka(int *m, int n)
{
	for(int i=0; i<n; i++)
		if(m[i]==0) return true;
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
	int* mlin = new int[n];
	for (int i = 1; i<n; i++)
		mlin[i] = 0;
	mlin[0] = 1;//начинаем с 0 вершины
	int index = 0;
	while (Metka(mlin, n))
	{
		int minWeight = INT_MAX;
		for (int i = 0; i<m; i++)
		{
			a = edges[i].v;
			b = edges[i].u;
			if ((mlin[a] == 1 && mlin[b] == 0) || (mlin[a] == 0 && mlin[b] == 1))
				if (edges[i].weight < minWeight)
				{
					index = i;
					minWeight = edges[i].weight;
				}

		}
		mlin[edges[index].v] = 1;
		mlin[edges[index].u] = 1;
		resultPrim[msf_edge_count_pr++] = { edges[index].v, edges[index].u, edges[index].weight };
	}

	finTime = clock();

	print_msf_edges_prim();
	delete[]resultPrim;
}


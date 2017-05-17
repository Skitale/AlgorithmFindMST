#pragma once
#include "additionalOptions.h"

int msf_edge_count_bor;


void print_msf_edges_Boruvka() {
	printf("Boruvka MSF edges:\n");
	for (int i = 0; i < msf_edge_count_bor; i++) {
		printf("(%d,%d) = %d\n", resultBoruvka[i].v, resultBoruvka[i].u, resultBoruvka[i].weight);
	}
}

void find_msf_Boruvka(edge_s * edges, const int m, double &finTime) {
	msf_edge_count_bor = 0;
	resultBoruvka = new edge_s[n - 1];
	
	uf_make();

	int * min_edges_weight = new int[m];
	for (size_t i = 0; i < m; i++)
	{
		min_edges_weight[i] = INT_MAX;
	}

	while (msf_edge_count_bor < n - 1)
	{
		for (size_t i = 0; i < m; i++)
		{
			if (min_edges_weight[i] > edges[i].weight) 
			{
				min_edges_weight[i] = edges[i].weight;

				int v = edges[i].v;
				int u = edges[i].u;
				u_node * v_node = uf_find(uf_set + v);
				u_node * u_node = uf_find(uf_set + u);

				if (v_node != u_node) 
				{
					resultBoruvka[msf_edge_count_bor++] = edges[i];
					uf_union(v_node, u_node);
				}
			}
		}
	}

	finTime = clock();
	printf("done! ");
#ifdef DEBUG
	print_msf_edges_Boruvka();
#endif
	delete[]resultBoruvka;
	delete[]uf_set;
}


#pragma once
#include"additionalOptions.h"



void find_msf_Boruvka(edge_s * edges, int m, double &finTime) {
	int msf_edge_count_kr = 0;
	resultBoruvka = new edge_s[n - 1];
	
	uf_make();

	int * min_edges_weight = new int[m];
	for (size_t i = 0; i < m; i++)
	{
		min_edges_weight[i] = INT_MAX;
	}

	while (msf_edge_count_kr < n - 1) 
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
					resultBoruvka[msf_edge_count_kr++] = edges[i];
					uf_union(v_node, u_node);
				}
			}
		}
	}
	
	

}


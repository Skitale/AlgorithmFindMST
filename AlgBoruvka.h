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
	//cout << "--------\n";
	//for (int i = 0; i < m; i++) {
	//	printf("(%d,%d) = %d\n", edges[i].v, edges[i].u, edges[i].weight);
	//}
	//cout << "--------\n";
	
	uf_make();
	int k = 0;
	edge_s * min_edges_weight = new edge_s[n];
	
	while (msf_edge_count_bor < n - 1)
	{
		for (int i = 0; i < n; i++){
			min_edges_weight[i] = { -1, -1, INT_MAX };
		}

		for (size_t i = 0; i < m; i++)
		{
			int v = edges[i].v;
			int u = edges[i].u;
			u_node * v_node = uf_find(uf_set + v);
			u_node * u_node = uf_find(uf_set + u);
			if (v_node == u_node) continue;

			int comp = v_node - uf_set;
			if (min_edges_weight[comp].weight > edges[i].weight){
				min_edges_weight[comp] = edges[i];
			}

			comp = u_node - uf_set;
			if (min_edges_weight[comp].weight > edges[i].weight){
				min_edges_weight[comp] = edges[i];
			}		
		}
		/*cout << "\n";
		for (int i = 0; i < m; i++) {
			printf("(%d,%d) = %d\n", edges[i].v, edges[i].u, edges[i].weight);
		}*/

		//for (int i = 0; i < n; i++){
		//	cout << " i="<< i << " v=" << min_edges_weight[i].v << "  u=" << min_edges_weight[i].u << "  w=" << min_edges_weight[i].weight << endl;
		//}
		//cout << "\n";

		for (int k = 0; k < n; k++){
			if (min_edges_weight[k].weight != INT_MAX){
				int v = min_edges_weight[k].v;
				int u = min_edges_weight[k].u;
				u_node * v_node = uf_find(uf_set + v);
				u_node * u_node = uf_find(uf_set + u);

				if (v_node != u_node){
					uf_union(v_node, u_node);
					resultBoruvka[msf_edge_count_bor++] = min_edges_weight[k];
				}
			}
		}
	}
	
	finTime = clock();
	printf("done! ");
#ifdef DEBUG
	print_msf_edges_Boruvka();
#endif
	delete[]min_edges_weight;
	delete[]uf_set;
	delete[]resultBoruvka;
}


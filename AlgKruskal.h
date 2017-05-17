#pragma once
#include "additionalOptions.h"

int msf_edge_count_kr;  /*  оличество ребер в массиве ребер MSF Kruskal*/



int compare_edges(const void *a, const void *b) {
	edge_s *ea = (edge_s *)a;
	edge_s *eb = (edge_s *)b;

	if (ea->weight < eb->weight) {
		return -1;
	}
	else if (ea->weight > eb->weight) {
		return 1;
	}

	//Ќикогда не происходит, если веса различны
	return 0;
}


void print_msf_edges_kruskal() {
	printf("Kruskal MSF edges:\n");
	for (int i = 0; i < msf_edge_count_kr; i++) {
		printf("(%d,%d) = %d\n", resultKruskal[i].v, resultKruskal[i].u, resultKruskal[i].weight);
	}
}

void find_msf_Kruskal(edge_s * edges, int m, double &finTime) {

	resultKruskal = new edge_s[n - 1];
	msf_edge_count_kr = 0;

	/*—ортировка ребер принадлежащих каждому процессу*/
	std::qsort(edges, m, sizeof(edge_s), compare_edges);

	uf_make();

	int used_edge_index = 0;
	for (int i = 1; i <= m; i++) {

		edge_s * min_edge = &edges[used_edge_index++];

		int v = (*min_edge).v;
		int u = (*min_edge).u;
		u_node * v_node = uf_find(uf_set + v);
		u_node * u_node = uf_find(uf_set + u);

		/* добавл€ем ребро к MSF, если оно не образует цикла*/
		if (v_node != u_node) {
			resultKruskal[msf_edge_count_kr++] = *min_edge;
			uf_union(v_node, u_node);
		}
	}

	finTime = clock();
	printf("done! ");
	//print_msf_edges_kruskal();
	delete[]resultKruskal;
	delete[]uf_set;
}




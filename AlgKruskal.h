#pragma once
#include "additionalOptions.h"

int msf_edge_count_kr;  /* ���������� ����� � ������� ����� MSF Kruskal*/


void uf_make(){
	int size = n;// + (number_of_vertices - 1);
	uf_set = new u_node[size];
	memset(uf_set, 0, size * sizeof(u_node));
}
u_node * uf_find(u_node * a){
	if (a->parent == NULL) return a;
	else return (a->parent = uf_find(a->parent));
}
void uf_union(u_node * a, u_node * b){
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




int compare_edges(const void *a, const void *b) {
	edge_s *ea = (edge_s *)a;
	edge_s *eb = (edge_s *)b;

	if (ea->weight < eb->weight) {
		return -1;
	}
	else if (ea->weight > eb->weight) {
		return 1;
	}

	//������� �� ����������, ���� ���� ��������
	return 0;
}


void print_msf_edges_kruskal() {
	if (n < 15){
		printf("Kruskal MSF edges:\n");
		for (int i = 0; i < msf_edge_count_kr; i++) {
			printf("(%d,%d) = %d\n", resultKruskal[i].v, resultKruskal[i].u, resultKruskal[i].weight);
		}
	}
}

void find_msf_Kruskal() {

	msf_edge_count_kr = 0;


	/*���������� ����� ������������� ������� ��������*/
	std::qsort(edges, m, sizeof(edge_s), compare_edges);

	uf_make();

	int used_edge_index = 0;
	for (int i = 1; i <= m; i++) {

		edge_s * min_edge = &edges[used_edge_index++];

		int v = (*min_edge).v;
		int u = (*min_edge).u;
		u_node * v_node = uf_find(uf_set + v);
		u_node * u_node = uf_find(uf_set + u);

		/* ��������� ����� � MSF, ���� ��� �� �������� �����*/
		if (v_node != u_node) {
			resultKruskal[msf_edge_count_kr++] = *min_edge;
			uf_union(v_node, u_node);
		}
	}

	print_msf_edges_kruskal();
}




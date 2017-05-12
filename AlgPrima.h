#pragma once
#include "additionalOptions.h"

int msf_edge_count_pr;  /* ���������� ����� � ������� ����� MSF Prim*/

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
	label[0] = 1;//�������� � 0 �������
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

void __test_find_msf_Prim(int ** weightMatr, bool ** connectivityMatr, double &finTime) {

	resultPrim = new edge_s[n - 1];
	msf_edge_count_pr = 0;

	int* label = new int[n];
	int* dist = new int[n];
	int* S = new int[n];

	for (int i = 1; i < n; i++){
		label[i] = 0;
		S[i] = INT_MIN;
	}
	S[0] = INT_MIN;
	label[0] = 1;

	for (int j = 1; j < n; j++){
		if (connectivityMatr[0][j]){
			dist[j] = weightMatr[0][j];
			S[j] = 0;
		}
	}

	for (int i = 1; i < n; i++){
		for (int j = i + 1; j < n; j++){
			if (connectivityMatr[i][j] && S[j]!=0){
				dist[j] = INT_MAX;
				S[j] = n;
			}
		}
	}


	while (check_label(label, n))
	{
		int indMin = INT_MAX;
		int distMin = INT_MAX;
		for (int i = 1; i < n; i++){
			if ( (label[i]==0) && (dist[i] < distMin) ){
				indMin = i;
				distMin = dist[i];
			}
		}
		label[indMin] = 1;
		resultPrim[msf_edge_count_pr++] = { S[indMin], indMin , distMin };

		for (int i = 1; i < n; i++){
			if (connectivityMatr[indMin][i] && (label[i]==0)){
				if (weightMatr[indMin][i] < dist[i]){
					dist[i] = weightMatr[indMin][i];
					S[i] = indMin;
				}
			}
		}	
	}

	finTime = clock();

	std::qsort(resultPrim, msf_edge_count_pr, sizeof(edge_s), compare_edges);
	printf("done! ");
	//print_msf_edges_prim();
	delete[]resultPrim;
	delete[]label;
	delete[]dist;
	delete[]S;
}


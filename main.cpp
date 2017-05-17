#pragma once
#include "AlgKruskal.h"
#include "AlgPrima.h"
#include"AlgBoruvka.h"
#include <ctime>

int main() {
	srand(time(0));
	printf("Enter number of vertices of Graph: ");
	cin >> n;



	double tGenDenseG1, tGenGenseG2, tGenRareG1, tGenRareG2;
	double tDensePrim1, tDensePrim2, tDenseKruskal1, tDenseKruskal2;
	double tRarePrim1, tRarePrim2, tRareKruskal1, tRareKruskal2, tRareBoruvka1, tRareBoruvka2;
	
	double dGenDense, dGenRare, dDensePrim, dDenseKruskal, dRarePrim, dRareKruskal;

	tGenRareG1 = clock();
	generateRareGraph(n, sm);
	tGenRareG2 = clock();

	tGenDenseG1 = clock();
	generateDenseGraph(n, m);
	tGenGenseG2 = clock();
	//tGenDenseG1 = clock();
	//GenerateGraph(n, m);
	//tGenGenseG2 = clock();


	print_edges();

	printf("\n");
	printf("Search MST Edges of Graph from the dense graph is ");

	tDensePrim1 = clock();
	//find_msf_Prim(edges, m, tDensePrim2);
	__test_find_msf_Prim(weightMatr, connectivityMatr, tDensePrim2);

	tDenseKruskal1 = clock();
	find_msf_Kruskal(edges, m, tDenseKruskal2);


	printf("\n");
	printf("Search MST Edges of Graph from the dense graph is ");

	tRarePrim1 = clock();
	//find_msf_Prim(s_edges, sm, tRarePrim2);
	__test_find_msf_Prim(s_weightMatr, s_connectivityMatr, tRarePrim2);

	//generateSparseGraph(n, sm);
	tRareKruskal1 = clock();
	find_msf_Kruskal(s_edges, sm, tRareKruskal2);


	find_msf_Boruvka(edges,sm,tRareBoruvka2);

	dGenDense = (tGenGenseG2 - tGenDenseG1); dGenRare = (tGenRareG2 - tGenRareG1);
	dDensePrim = (tDensePrim2 - tDensePrim1); dDenseKruskal = (tDenseKruskal2 - tDenseKruskal1);
	dRarePrim = (tRarePrim2 - tRarePrim1); dRareKruskal = (tRareKruskal2 - tRareKruskal1);

	printf("\nTime of generation the dense graph %f ms.\nTime of generation the rare graph %f ms.\n", dGenDense, dGenRare);

	printf("Search time MST using alg Prima for the dense graph %f ms.\nSearch time MST using alg kruskal for the dense graph %f ms.\n", dDensePrim, dDenseKruskal);
	printf("Search time MST using alg Prima for the rare graph %f ms.\nSearch time MST using alg kruskal for the rare graph %f ms.\n", dRarePrim, dRareKruskal);


	finalize();
	system("pause");
	return 0;
}
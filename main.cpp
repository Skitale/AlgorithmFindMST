#pragma once
//#define DEBUG
#include "AlgKruskal.h"
#include "AlgPrima.h"
#include"AlgBoruvka.h"
#include <ctime>

int main() {
	srand(time(0));
	printf("Enter number of vertices of Graph: ");
	cin >> n;
	_heapchk();
	double tGenDenseG1, tGenGenseG2, tGenRareG1, tGenRareG2;
	double tDensePrim1, tDensePrim2, tDenseKruskal1=0, tDenseKruskal2=0, tDenseBoruvka1=0, tDenseBoruvka2=0;
	double tRarePrim1, tRarePrim2, tRareKruskal1, tRareKruskal2, tRareBoruvka1, tRareBoruvka2;
	
	double dGenDense, dGenRare, dDensePrim, dDenseKruskal, dDenseBoruvka, dRarePrim, dRareKruskal, dRareBoruvka;


	tGenDenseG1 = clock();
	generateDenseGraph(n, m);
	tGenGenseG2 = clock();


	//print_edges();

	printf("\n");
	printf("Search MST Edges of Graph from the dense graph is ");

	// Working Prim alg at Dense Graph
	tDensePrim1 = clock();
	find_msf_Prim(weightMatr, connectivityMatr, tDensePrim2);

	// Working Boruvka alg at Dense Graph
	tDenseBoruvka1 = clock();
	find_msf_Boruvka(edges, m, tDenseBoruvka2);

	////// Working Kruskal alg at Dense Graph
	//tDenseKruskal1 = clock();
	//find_msf_Kruskal(edges, m, tDenseKruskal2);

	finalizeArray(&weightMatr, &connectivityMatr);
	delete[]edges;

	printf("\n");

	tGenRareG1 = clock();
	generateRareGraph(n, sm);
	tGenRareG2 = clock();

	printf("\n");
	printf("Search MST Edges of Graph from the dense graph is ");

	// Working Prim alg at Rare Graph
	tRarePrim1 = clock();
	find_msf_Prim(s_weightMatr, s_connectivityMatr, tRarePrim2);

	// Working Boruvka alg at Rare Graph
	tRareBoruvka1 = clock();
	find_msf_Boruvka(s_edges, sm, tRareBoruvka2);

	// Working Kruskal alg at Rare Graph
	tRareKruskal1 = clock();
	find_msf_Kruskal(s_edges, sm, tRareKruskal2);

	finalizeArray(&s_weightMatr, &s_connectivityMatr);
	delete[]s_edges;

	dGenDense = (tGenGenseG2 - tGenDenseG1); dGenRare = (tGenRareG2 - tGenRareG1);
	dDensePrim = (tDensePrim2 - tDensePrim1); dDenseKruskal = (tDenseKruskal2 - tDenseKruskal1); dDenseBoruvka = (tDenseBoruvka2 - tDenseBoruvka1);
	dRarePrim = (tRarePrim2 - tRarePrim1); dRareKruskal = (tRareKruskal2 - tRareKruskal1); dRareBoruvka = (tRareBoruvka2 - tRareBoruvka1);

	printf("\nTime of generation the dense graph %f ms.\nTime of generation the rare graph %f ms.\n", dGenDense, dGenRare);

	printf("Search time MST using alg Prima for the dense graph %f ms.\nSearch time MST using alg Kruskal for the dense graph %f ms.\nSearch time MST using alg Boruvka for the dense graph %f ms.\n", dDensePrim, dDenseKruskal, dDenseBoruvka);
	printf("Search time MST using alg Prima for the rare graph %f ms.\nSearch time MST using alg Kruskal for the rare graph %f ms.\nSearch time MST using alg Boruvka for the rare graph %f ms.\n", dRarePrim, dRareKruskal, dRareBoruvka);

	//finalize();
	system("pause");
	return 0;
}
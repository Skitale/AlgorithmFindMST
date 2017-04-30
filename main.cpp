#pragma once
#include "AlgKruskal.h"
#include "AlgPrima.h"

int main(){
	cin >> n;
	m = 2 * n;
	double tlin1, tlin2, dtlin;


	resultPrim = new edge_s[n - 1];
	resultKruskal = new edge_s[n - 1];

	GenerateGraph(n, m);

	print_edges();


	find_msf_Prim();
	find_msf_Kruskal();

	finalize();
	system("pause");
	return 0;
}
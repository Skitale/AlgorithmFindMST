#pragma once
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>
using namespace std;

struct edge_s {    /* ���������, �������������� ���� �����*/
	int v;
	int u;
	int weight;
};


struct u_node {/* ������� ���������������� ��������*/
	u_node * parent;
	int depth;

	u_node(){
		parent = NULL;
		depth = 0;
	};
};


int n;    // ���������� ������ � ����� 
int m;       // ���������� �����
edge_s * edges;     // ������ �����

edge_s * resultPrim;
edge_s * resultKruskal;

u_node * uf_set; /* ������, �����������, ����� ������� ������ ��������� �����������. */


void print_edges() {
	if (n < 10){
		printf("Edges:\n");
		for (int i = 0; i < m; i++) {
			printf("(%d,%d) = %d\n", edges[i].v, edges[i].u, edges[i].weight);
		}
	}
}

int EdgeInGraph(int A, int B, int end, edge_s * ed)//���� �� ��� ����� ����� � �����
{

	for (int i = 0; i<end; i++)
		if (ed[i].v == A && ed[i].u == B || ed[i].v == B && ed[i].u == A)
			return i;
	return -1;
}

//��������� ����� � ����� (������ �����)
void GenerateGraph(int n, int m)
{
	int weight, v1, v2, fl;
	bool flag;

	edges = new edge_s[m];

	//������ ���� �������
	for (int i = 0; i<n - 1; i++)
	{
		weight = rand() % 50 + 1;
		edges[i] = { i, i + 1, weight };
	}
	for (int i = n - 1; i<m; i++)
	{
		int sl = 0;
		v1 = rand() % n;
		flag = false;
		while (flag == false)
		{
			v2 = v1;
			while (v2 == v1)
				v2 = rand() % n;
			weight = rand() % 50 + 1;
			fl = EdgeInGraph(v1, v2, i, edges);
			if (fl == -1) flag = true;
			else sl++;
			if (sl>5)
			{
				sl = 0;
				v1 = rand() % n + 1;
			}
		}
		edges[i] = { v1, v2, weight };
	}
}

void finalize() {
	delete[]uf_set;
	delete[]edges;
	delete[]resultPrim;
	delete[]resultKruskal;
}
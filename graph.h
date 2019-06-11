#ifndef graph_h
#define graph_h
#include<iostream>
#include <fstream>
#include"list.h"
#include"vertex.h"
#include"node.h"

class Graph{

	int V;
	List *lista;

public:

	Graph(int tmp){ //konstruktor
		V = tmp;
		lista = new List[tmp];
	}

	void RandomGraph(int D);

	void AddEdge(int u, int v, int weight){ //dodawanie krawedzie
		lista[u].Add(u, v, weight);	//lista krawedzi, tworzona w konstruktorze
	}

	int getVQuant(){ return V; } //wez ilosc wierzcholkow, wywolywana jesli chcesz otrzymac ilosc wierzcholkow, ktora jest przetrzymywana w sekcji private

	List getList(int i){ return lista[i]; } //bierzesz ktorys obiekt z listy

	void DijkstraLista(int D);
	void DijkstraTablica(int D);

};
std::ostream &operator << (std::ostream &strOut, Graph *test_graph);

#endif
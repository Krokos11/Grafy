#include <iostream>
#include<fstream>
#include"graph.h"


using namespace std;

void ZapisCzasu(double lista[], double macierz[]){ //zapisywanie czasu do plikow

	ofstream plik, plik2;

	plik.open("Czasy lista.txt");
	plik2.open("Czasy macierz.txt");

	for (int i = 0; i < 20; ++i)
	{
		plik<<lista[i]<<"\n";
		plik2<<macierz[i]<<"\n";
	}

}

void Wczytywanko(){ //wczytuja dane z pilku

	ifstream plik;

	plik.open("dane2.txt");

	int E, V, start, u, v, w; //E-ilosc krawedzi, V-ilosc wierzcholkow, start-wierzcholek startowy, u-wierzcholek poczatkowy, v-wierzcholek koncowy, w-waga

	plik >> E;
	plik >> V;
	plik >> start;

	float D = (200*E)/(V*(V-1));//gestosc grafu

	Graph *wczyt = new Graph(V); //tworzenie pustych obiektow (szablonu do grafu)

	cout<< "\nVertexes = " << V << ", Edges = " << E << ", Density = " << D << "\n\n"; 

	for(int i = 0; i < E; i++){
    	plik >> u;
        plik >> v;
        plik >> w;

    	wczyt->AddEdge(u, v, w);
    	wczyt->AddEdge(v, u, w);
	}

	cout<<wczyt;

	wczyt->DijkstraLista(D);

	wczyt->DijkstraTablica(D);
}

void test(){

	int V[5] = { 50,100,300,500,1000 };//liczby wierzcholkow
	int D[4] = { 25,50,75,100 };//gestosc

	clock_t begin;
	clock_t end;
	double elapsed_secs, elapsed_secs_2;
	double czas1[20], czas2[20];
	int q=0;

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 5; j++){

			Graph *test_graph = new Graph(V[j]); //tworzenie wierzcholkow

			
			test_graph->RandomGraph(D[i]);
			elapsed_secs = 0;
			//cout<<test_graph;

			for(int c=0; c<100; c++){
				begin = clock();
				test_graph->DijkstraLista(D[i]);
				end = clock();
				elapsed_secs += double(end - begin) / CLOCKS_PER_SEC;
			}
			
			cout<< "Czas wykonywania algorytmu: " <<elapsed_secs/100<< " s" << endl;
			
			czas1[q] = elapsed_secs/100;

			elapsed_secs_2 = 0;

			for(int k=0; k<100; k++){
				begin = clock();
				test_graph->DijkstraTablica(D[i]);
				end = clock();
				elapsed_secs_2 += double(end - begin) / CLOCKS_PER_SEC;
			}
			
			cout<< "Czas wykonywania algorytmu: " <<elapsed_secs/100<< " s" << endl;
			czas2[q] = elapsed_secs_2/100;

			q++;
		}

	ZapisCzasu(czas1, czas2);
}


int main(){

	/*cout<<"Podaj liczbe wierzcholkow: ";
	cin>>V;

	cout << "Podaj procent gestosci: ";
    cin >> D;*/
   cout<<"1. Wczytaj graf z pliku \n2. Wczytaj losowy graf \n";

   int wybor;
   cin>>wybor;

   switch(wybor){
   	case 1:
   		Wczytywanko();
   	break;
   	case 2:
   		test();
    break;
   }
}
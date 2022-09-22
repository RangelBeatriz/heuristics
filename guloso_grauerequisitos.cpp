#include <stdio.h>
#pragma warning(disable: 4996)
#pragma warning(disable: 4661)
#pragma warning(disable: 4267)

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <array>
#include <unordered_map>
#include <list>
#include <queue>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>
#include <climits>
#include <chrono>
#include <atomic>
#include <thread>
#include <sstream>
#include <functional>
#include <iostream>
#include <fstream> 
#include <condition_variable>
#include <mutex>
#include<iomanip>
#include<stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <chrono>
#include <thread>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <chrono>

#include "BibGrafos/BibGrafos.h"

#ifndef DATADIR
#ifdef ILO_WINDOWS
#define DIRSEP "\\"
#else
#define DIRSEP "/"
#endif
#define DATADIR ".." DIRSEP ".."  DIRSEP ".." DIRSEP ".." DIRSEP "opl" DIRSEP
#endif

using namespace std;
using namespace std::chrono;
using namespace BibGrafos;

double calc_fator(double requisito, int grau, int n){

	double value;

    value = (requisito*requisito)/(n-grau);

    return value;
}

int main()
{


	Grafo G = BibGrafos::Grafo::ConstruirDeArquivoBinario("n8p25_G1.gbin");

    int k = G.ObterGrauMinimo();
	VetorRequisitos R = VetorRequisitos::GerarConstante(&G,k);
	VetorRequisitos Raux = R; //Criar uma cópia de trabalho para preservar R
	
	set<Vertice> faltaDominar(G.Vertices.begin(), G.Vertices.end());
	set<Vertice> S;


	int grau[G.N()];
    double fator[G.N()];

	for (Vertice v: faltaDominar){
		grau[v.Indice()] = G.Grau(v);
	}

    for (Vertice v: faltaDominar){
        fator[v.Indice()] = calc_fator(Raux[v], grau[v.Indice()], faltaDominar.size());
    }

	string aux = G.ObterStringListaAdjacencias();
	int a = G.ObterGrauMaximo();
	cout << aux << endl;

	auto start = high_resolution_clock::now();
	while (faltaDominar.size() > 0)
	{
		Vertice v = *faltaDominar.begin();
		for(Vertice w: faltaDominar){
			if(fator[w.Indice()] > fator[v.Indice()]){
				v = w;
			}
		}

		S.insert(v);

		for(Vertice u : G.Adjacentes(v))
		{
			Raux[u] = Raux[u] - 1;
			grau[u.Indice()] = grau[u.Indice()] - 1;
            fator[u.Indice()] = calc_fator(Raux[u], grau[u.Indice()], faltaDominar.size());

			cout << "\n";
			cout << "Dominado: " << u.Id();
			cout << "\n";
			
            if(Raux[u] == 0){
				faltaDominar.erase(u);
			}
		}

		faltaDominar.erase(v);
	}
	auto stop = high_resolution_clock::now();

	auto duration = duration_cast<microseconds>(stop-start);
	
	cout << "Tempo em microsegundos: " << duration.count() << endl;
	cout << "Tamanho:" << S.size() << endl;

	//G.SalvarArquivoBinario(arq);

	//}

	return 0;	
}

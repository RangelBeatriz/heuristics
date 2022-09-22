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
#include <string.h>

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

int main()
{
	
	Grafo G = BibGrafos::Grafo::ConstruirDeArquivoBinario("n8p25_G1.gbin");

	int k = G.ObterGrauMinimo()/2;
	VetorRequisitos R = VetorRequisitos::GerarConstante(&G,k);
	VetorRequisitos Raux = R; 

	set<Vertice> faltaDominar(G.Vertices.begin(), G.Vertices.end());
	set<Vertice> S;
	int grau[G.N()];

	for (Vertice v: faltaDominar){
		grau[v.Indice()] = G.Grau(v);
	}

	while (faltaDominar.size() > 0)
	{
		Vertice v = *faltaDominar.begin();
		for(Vertice w: faltaDominar){
			if(Raux[v] < Raux[w]){
				v = w;
			}

			else if(Raux[v] == Raux[w]){
				if(grau[v.Indice()] < grau[w.Indice()]){
					v = w;
				}
			}
		}
		
		S.insert(v);

		for(Vertice u : G.Adjacentes(v))
		{
			Raux[u] = Raux[u] - 1;
			grau[u.Indice()] = grau[u.Indice()] - 1;
			if(Raux[u] == 0){
				faltaDominar.erase(u);
			}
		}

		faltaDominar.erase(v);
		//G->RemoverVertice(v);		
	}

	
	cout << "Tamanho:" << S.size() << endl;

	
	
	return 0;	
}

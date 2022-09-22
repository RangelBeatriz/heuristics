#include <stdio.h>
#include <stdlib.h>
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

#include "BibGrafos/BibGrafos.h"

using namespace BibGrafos;


int main()
{
	Grafo G = BibGrafos::Grafo::ConstruirDeArquivoBinario("n8p25_G1.gbin");

    int k = G.ObterGrauMinimo()/2;
	VetorRequisitos R = VetorRequisitos::GerarConstante(&G,k);
	VetorRequisitos Raux = R;
	
	set<Vertice> faltaDominar(G.Vertices.begin(), G.Vertices.end());
	set<Vertice> S;
	
	while (faltaDominar.size() > 0){
		
		Vertice v = *faltaDominar.begin();
		for(Vertice w: faltaDominar){
			if(Raux[v] < Raux[w]){
				v = w;
			}
		}

		S.insert(v);

		for(Vertice u : G.Adjacentes(v))
		{
			Raux[u] = Raux[u] - 1;
			
            if(Raux[u] <= 0){
				faltaDominar.erase(u);
			}
		}

		faltaDominar.erase(v);
	}
	
	cout << "Tamanho:" << endl;
	cout << S.size() << endl;
	
	return 0;	
}
#ifndef __BRUIJN_H
#define __BRUIJN_H

#include <vector>
#include <map>
#include <queue>
#include <string>
#include "graaf.h"

template <class T>
class DeBruijnreeks : public std::string {
private:
	std::string shift_string(const std::string& v, T data);
public:
	DeBruijnreeks(int N,int M); // N= orde , M=alfabet
	
};


/**
 * Genereert een DeBruijnreeks
 * @param N orde van DeBruijnreeks
 * @param M alfabet
 */
template <class T>
DeBruijnreeks<T>::DeBruijnreeks(int N,int M){ // N= orde , M=alfabet
    // initialisatie
    // graaf aanmaken aan de hand van orde N en alfabet M
	GraafMetKnoopEnTakdata<GERICHT,std::string,T> g;
	std::string beginknoopdata;
    beginknoopdata.resize(N);
	std::map<std::string,int> knoopnrs; // data => knoopnr
	std::queue<int> knopen;
	int begin = g.voegKnoopToe(beginknoopdata);
	knoopnrs[beginknoopdata]=begin;
	knopen.push(begin);
	while(!knopen.empty()){
		int van = knopen.front();
		knopen.pop();
		for(T i=0;i<M;i++){
			std::string new_v=shift_string(beginknoopdata,i);
			if( knoopnrs.count(new_v) > 0 ){ // knoop bestaat al
				int naar = g.voegVerbindingToe(van,knoopnrs[new_v],i);
			} 
			else{
				int naar = g.voegKnoopToe(new_v);
				g.voegVerbindingToe(van,naar,i);
				knopen.push(naar);
				knoopnrs[new_v]=naar;
			}
		
		}
	}
    // eulercircuit uit graaf halen
    
    // starten met eerste knoop
    // verbindingen overlopen tot je terug bij dezelfde knoop aankomt
    // volgende verbinding van knoop overlopen.
    // als alle verbindingen van een knoop overlopen zijn, knoop markeren als behandeld
    // volgende niet-behandelde knoop (waarvan verbindingen nog niet bezocht zijn) nemen en herhalen.
    
    // initialisatie
    bool knoop_behandeld[g.aantalKnopen()];
    for(int i = 0; i < g.aantalKnopen(); i++){
        knoop_behandeld[i] = false;
    }
    /*bool verbinding_bezocht[g.aantalVerbindingen()];
    for(int i = 0; i < g.aantalVerbindingen(); i++){
        verbinding_bezocht[i] = false;
    }*/
    std::map<int, bool> verbinding_bezocht;
    
    // knopen overlopen
    for(int i = 0; i < g.aantalKnopen(); i++){
        if(!knoop_behandeld[i]){
            // alle verbindingen van knoop i overlopen.
            std::map<int, int> knoop = g[i]; // knoop: sleutel buurnr ; value: verbindingsnummer
            for(std::map<int, int>::const_iterator it = knoop.begin(); it != knoop.end(); it++){
                if (verbinding_bezocht.count(it->second) == 0){ // als verbinding al bezocht is zal count groter zijn dan 0
                    // verbinding behandelen: lus maken
                    
                    
                    // als we terug bij startknoop zitten: lus gevonden
                    
                    verbinding_bezocht[it->second] = true;
                }
            }
            // alle verbindingen van knoop behandeld
            knoop_behandeld[i] = false;
        }
    }
    
    
    // resultaat opslaan in this[];
    

}

template <class T>
std::string DeBruijnreeks<T>::shift_string(const std::string &v, T data){
	std::string new_v(v);
	for(int i=0;i<v.size()-1;i++){
		new_v[i]=new_v[i+1];
	}
	new_v[v.size()-1]=data;
	return new_v;
}



#endif 
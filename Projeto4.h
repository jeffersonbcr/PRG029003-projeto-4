#define PROJETO4_H
#ifdef PROJETO4_H


#include <prglib.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace prglib;

struct Verbete{
    string palavra;
    string classe;
    lista<string> significado;
    bool operator < (const Verbete & outra){
        return palavra < outra.palavra;
    }
    bool operator == (const Verbete & outra){
        return palavra == outra.palavra;
    }
};


arvore <Verbete> * Add_verbete(arvore <Verbete> * arv, string Palavra, string Classe, string Significado);
//ela adiciona o verbete na arvore


lista<string> separa(const string & texto, const string & sep);
// ela separa a string pelo parametro informado


lista<Verbete> lista_de_verbetes(string arq_verbete);
// coloca os verbetes lidos numa lista

arvore<Verbete> *inicia_arvore(string arq_verbete,string arq_dicionario);
//coloca os verbetes lidos numa arvore

Verbete obtem_verbete(string verb_desejado,arvore<Verbete> * arv);
// Ele mostra o verbete solcitado pela palavra como parametro

lista <Verbete> obtem_muitos_verbetes(lista<string> lista_verbs_desejados,arvore <Verbete> * arv);
// ele captura todos os verbetes que estão na lista e mostra o siginicado de cada um

lista<Verbete> Palavras_prefixo(arvore <Verbete> * arv, string prefixo);
//mostra a palavra com o prefixo solicitado

void mostrar_um_verbete(Verbete verb);
//imprime na tela um verbete.
void mostrar_n_verbetes(lista<Verbete> lista_verbetes);
//imprime na tela muitos vervetes.
void gravar_no_arquivo(arvore<Verbete> * arv,string arq_dicionario);
//grava no arquivo a topologia da arvore.
#endif
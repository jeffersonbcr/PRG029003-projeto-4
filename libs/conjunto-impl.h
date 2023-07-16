//
// Created by aluno on 17/12/2019.
//

#ifndef CONJUNTO_IMPL_H
#define CONJUNTO_IMPL_H

#include "conjunto.h"

namespace prglib {

    template<typename T> conjunto<T>::conjunto(const T &algo) { //construtor do conjunto, cria um conjunto a partir do dado passado por parâmetro esse dado será a raiz da árvore que conjunto armazena.
    arv = new arvore<T>(algo); //chama método construtor a partir de um dado da árvore.
    }

    template<typename T>
    conjunto<T>::conjunto(lista <T> &dados) { //construtor do conjunto, cria um conjunto a partir de uma lista passada por parâmetro, árvore será criada pela lista e o conjunto irá armazenar a árvore.
        arv= new arvore<T>(dados); //chama método construtor a partir de uma lista da árvore.
    }

    template<typename T>
    T conjunto<T>::remover(const T &algo) { //remove um dado do conjunto e retorna o dado;
    arv->remove(algo); //chama método remove da árvore.
    }

    template<typename T>
    void conjunto<T>::adicionar(const T &algo) { //adiciona um dado ao conjunto.
        arv->adiciona(algo); //chama método adiciona da árvore.
    }


    template<typename T>
    bool conjunto <T>::existe(const T & algo) const { //retorna um booleano , se existe o dado passado por parâmetro no conjunto.
        try{ //tenta chamar método obtem da árvore, se não gerar exceção retorna true.
            arv->obtem(algo);
            return true;
        }catch (...){ //se gerar exceção retorna false.
            return false;
        }
    }


    template<typename T>
    void conjunto<T>::eXtrair(lista<T> & lista_dados) const { //extrai todos os dados do conjunto e os armazena dentro de uma lista.
        arv->listeInOrder(lista_dados); //chama método listeInorder da árvore e armazena dados na lista.
    }

    template<typename T>
    bool conjunto<T>::subconjunto(const conjunto<T> *outra) const { //retorna um booleano, se conjunto passado por parâmetro é um subconjunto do atual.
       return arv->contem(outra->arv); //chama método contem da árvore e verifica se a árvore do conjunto atual contem a árvore do conjunto outra.
    }

    template<typename T>
    conjunto<T> * conjunto<T>::interseccao(const conjunto<T> *outra)  { //cria um conjunto a partir da intersecção de dois conjuntos o atual e o passado por parâmetro.
        auto arv_aux = arv->dados_iguais(outra->arv); //chama método dados_iguais da árvore e cria uma árvore com dados iguais da árvore do conjunto atual e da árvore do conjunto outra.
        lista<T> l_aux;
        arv_aux->listeInOrder(l_aux);
        auto conjunto_aux = new conjunto<T>(l_aux);
        return conjunto_aux;
    }

    template<typename T>
    conjunto<T> *conjunto<T>::uniao(const conjunto<T> *outra)  { //cria um conjunto que é a união de dois conjuntos, o atual e passado por parãmetro outra.
     auto arv_aux2 = arv->unir(outra->arv); //chama método unir, cria uma árvore com dados da árvore do conjunto atual e da árvore do conjunto outra.
     lista<T> l_aux2;
     arv_aux2->listeInOrder(l_aux2);
     auto conjunto_aux2 = new conjunto<T>(l_aux2);
     return conjunto_aux2;
    }




}

#endif //PRGLIB_CONJUNTO_IMPL_H

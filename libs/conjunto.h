//
// Created by aluno on 17/12/2019.
//

#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <libs/arvore.h>
#include <libs/lista.h>
using std::string;
using std::istream;
namespace  prglib {
    template<typename T>
    class conjunto { //Classe conjunto
    public:
        conjunto(const T &algo); //construtor: precisa de um dado passdo por referência para construir o conjunto.

        conjunto(lista<T> & dados); //cria conjunto a partir de uma lista.

        void adicionar(const T & algo); //adiciona um dado ao conjunto.

        T remover(const T &algo); //remove um dado do conjunto.

        bool existe(const T &algo) const; //retorna true se dado existe no conjunto.

        void eXtrair(lista <T> & lista_dados) const; //extrai todos os dados do conjunto e coloca os dados em uma lista.

        bool subconjunto(const conjunto<T> * outra) const; //retorna true se o parâmetro passado for subconjunto do conjunto.

        conjunto<T> * interseccao(const conjunto<T> * outra) ; //retorna um conjunto com os dados que são comuns entre os dois conjuntos.

        conjunto<T> * uniao(const conjunto<T> * outra) ; //retorna um conjunto com os dados dos dois conjuntos.


    protected:
        arvore<T> * arv;

    };



}

#include <libs/conjunto-impl.h>
#endif
#ifndef PILHA_H
#define    PILHA_H

#include <cstdlib>

namespace prglib {

    template<typename T>
    class pilha {
    public:
        // construtor: deve-se informar a capacidade da pilha
        pilha(unsigned int umaCapacidade);

        // construtor de cópia: cria uma pilha que é cópia de outra
        pilha(const pilha<T> &outra);

        // destrutor da pilha
        ~pilha();

        // operador de atribuição: torna esta pilha uma cópia de outra pilha
        pilha<T> &operator=(const pilha<T> &outra);

        // operações da pilha

        virtual void push(const T &dado); // empilha um dado

        T pop(); // desempilha um dado

        virtual const T &top() const; // retorna o dado do topo da pilha, sem retirá-lo

        bool vazia() const;

        bool cheia() const;

        unsigned int comprimento() const;

        void esvazia();

        unsigned int capacidade() const;

    private:
        unsigned int cap, topo;
        T *buffer;
    };

} // fim do namespace

#include <libs/pilha-impl.h>

#endif    /* PILHA_H */
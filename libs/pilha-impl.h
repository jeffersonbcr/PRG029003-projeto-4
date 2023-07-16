#ifndef PILHA_IMPL_H
#define PILHA_IMPL_H

#include "pilha.h"


namespace prglib {

    template<typename T>
    pilha<T>::pilha(unsigned int umaCapacidade) {
        if (umaCapacidade == 0) throw -1; //caso capacidade passada por parâmetro,dispara exeção.
        cap = umaCapacidade; //capacidade da pilha recebe valor passado por parâmetro.
        buffer = new T[cap]; //criando número de buffers.
        topo = 0; //posição do topo recebe zero.
    }

    template<typename T>
    pilha<T>::pilha(const pilha &outra) {
        cap = outra.cap;
        topo = outra.topo; //Cria uma pilha a partir de uma outra pilha.
        buffer = new T[cap]; //recebe os mesmo valores da outra pilha , de topo , capacidade e cria o mesmo número de buffers.
        for (int i = 0; i < (outra.topo); i++) {
            buffer[i] = outra.buffer[i];   //empilhando dados na fila atual.
        }
    }

    template<typename T>
    pilha<T>::~pilha() {
        delete[]buffer; //destroi a fila, deletando os buffers.
    }

    template<typename T>
    pilha<T> &pilha<T>::operator=(const pilha<T> &outra) {
        cap = outra.cap; //recebendo capacidade e topo da outra pilha.
        topo = outra.topo;
        delete[] buffer; //deletando buffers da pilha atual.
        buffer = new T[cap]; //criando buffers de acordo com informações da outra pilha.
        for (int i = topo - 1; i >= 0; i--) {
            buffer[i] = outra.buffer[i]; //pilha criada com o mesmo formato.
        }

    }

    template<typename T>
    void pilha<T>::esvazia() {
        topo = 0; //topo recebe zero, esvaziando a fila.
    }

    template<typename T>
    void pilha<T>::push(const T &dado) {
        if (topo == cap)throw -1; //caso topo igual a capacidade , dispara exeção.
        buffer[topo] = dado; //buffer da posição topo recebe dado.
        topo++; //incrementa posição do topo.
    }

    template<typename T>
    T pilha<T>::pop() {
        if (topo == 0)throw -1; //caso topo igual zero, dispara exeção.
        else {
            auto aux = buffer[topo - 1]; //recebendo dado do topo.
            topo--; //decrementando posição do topo.
            return aux; //retorna dado do topo.
        }
    }

    template<typename T>
    const T &pilha<T>::top() const {
        if (topo == 0)throw -1;
        return buffer[topo - 1]; //retorna dado do topo da pilha.


    }

    template<typename T>
    unsigned int pilha<T>::capacidade() const {
        return cap; //retorna capacidade da pilha.
    }

    template<typename T>
    bool pilha<T>::cheia() const {

        return (topo == cap); //retorna comparação de igualdade entre topo e capacidade da pilha.
    }

    template<typename T>
    bool pilha<T>::vazia() const {
        return topo == 0;  //retorna comparação de igualdade entre topo e valor zero.

    }

    template<typename T>
    unsigned int pilha<T>::comprimento() const {
        return topo; //topo indica quantidade de dados empilhados.
    }

}

#endif    /* PILHA_IMPL_H */


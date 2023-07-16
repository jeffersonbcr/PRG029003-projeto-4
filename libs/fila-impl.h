#ifndef FILA_IMP_H
#define FILA_IMP_H

namespace prglib {

    template<typename T>
    fila<T>::fila(unsigned int max_itens) { //cria uma fila de acordo com um tamanho.
        N = 0; //número de dados da fila inicialemnte zero.
        cap = max_itens; //capacidade recebe valor passado por parâmetro.
        inicio = 0; //inicio e fim recebem zero.
        fim = 0;
        buffer = new T[max_itens]; //criando buffers.
    }

    template<typename T>
    fila<T>::fila(const fila &orig) {
        cap = orig.cap; //recebendo mesma capacidade da fila passada por parâmetro.
        inicio = orig.inicio; //recebendo mesmo incio da fila passada por parâmetro.
        fim = orig.fim; //recebendo mesmo fim da fila passada por parâmetro.
        N = orig.N; //recebendo mesma quantidade de dados da fila passada por parâmetro.
        buffer = new T[orig.cap]; //criando o mesmo número de buffers da fila passada por parâmetro.
        for (int ct = 0; ct < orig.cap; ct++) {
            buffer[ct] = orig.buffer[ct]; //recebendo dados da outra fila.
        }

    }

    template<typename T>
    fila<T>::~fila() {
        delete[] buffer; //destroi a fila, deletando o buffer.
    }

    template<typename T>
    fila <T> &fila<T>::operator=(const fila &outra) {
        delete[]buffer; //deleta a quantidade de buffers da fila atual.
        buffer = new T[outra.cap]; //criando quantidade de buffers de acordo com a capacidade da fila outra.
        for (int ct = 0; ct < outra.cap; ct++) {
            buffer[ct] = outra.buffer[ct];
        }
        cap = outra.cap; //recebendo mesma capacidade da fila passada por parâmetro.
        inicio = outra.inicio; //recebendo mesmo incio da fila passada por parâmetro.
        fim = outra.fim; //recebendo mesmo fim da fila passada por parâmetro.
        N = outra.N; //recebendo mesma quantidade de dados da fila passada por parâmetro.
    }

    template<typename T>
    void fila<T>::enfileira(const T &algo) {
        if (cheia()) throw -1; //caso fila cheia, dispara exeção.
        buffer[fim] = algo; //posiciona dado no buffer da posição fim.
        fim++; //incrementa fim.
        if (fim == cap)fim = 0; //caso posição fim igual capacidade, fim recebe zero.
        N++; //incrementa quantidade da dados na fila.
    }

    template<typename T>
    T fila<T>::desenfileira() {
        if (vazia())throw -1; //caso fila vazia, dispara exeção.
        int ant = inicio; //variável ant recebe posição inicio.
        inicio++; //incrementa posição do inicio.
        if (inicio == cap)inicio = 0; //caso posição inicio igual capacidade, inicio recebe zero.
        N--; //decrementa número de dados.
        return buffer[ant]; //retorna dado da posição ant.
    }

    template<typename T>
    T &fila<T>::frente() {
        return buffer[inicio]; //retorna o dado que está na frente da fila.
    }

    template<typename T>
    void fila<T>::esvazia() {
        N = 0;
        inicio = 0; //esvazia a fila. Quantidade de dados,inicio e fim recebem zero.
        fim = 0;
    }

    template<typename T>
    bool fila<T>::vazia() const {
        return N == 0; //retorna comparação de igualdade do número de dados da lista com zero.
    }

    template<typename T>
    bool fila<T>::cheia() const {
        return N == cap; //retorna se a fila está cheia, se quantidade de dados é igual a capacidade.
    }

    template<typename T>
    unsigned int fila<T>::capacidade() const {
        return cap; //retorna capacidade da fila.
    }

    template<typename T>
    unsigned int fila<T>::comprimento() const {
        return N; //retorna número de dados na fila.
    }

    template<typename T>
    T fila<T>::desenfileiraDoFim() {
        if (N == 0) throw -1;
        fim--;
        int ant = fim;
        if (fim == 0) fim = cap;
        N--;
        return buffer[ant];


    }

} // fim namespace

#endif /* FILA_IMP_H */
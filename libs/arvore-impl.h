#ifndef ARVORE_IMPL_H
#define ARVORE_IMPL_H

#include "arvore.h"

namespace prglib {

    template<typename T>
    arvore<T>::~arvore() {
        //vazio.
    }

    template<typename T>
    arvore<T>::arvore() {
        //vazio.
    }

    template<typename T>
    arvore<T>::arvore(const T &dado) { //cria árvore, tendo a raiz passada por parâmetro.
        data = dado; //data recebendo dado.
        esq = nullptr; // ponteiros esq e dir recebendo nullptr, e ponteiro pai recebendo this.
        dir = nullptr;
        pai = this;
    }

    template<typename T>
    arvore<T>::arvore(istream &inp) {

    }

    template<typename T>
    arvore<T>::arvore(prglib::lista<T> &dados) { //cria árvore a partir de uma lista.
        if (dados.vazia())throw -1; //gera execão se fila estiver vazia.
        data = dados.remove(0); //removendo posição zero da lista para criar a raiz da árvore.
        pai = this;  // ponteiros esq e dir recebendo nullptr, e ponteiro pai recebendo this.
        esq = nullptr;
        dir = nullptr;
        dados.inicia(); //inicia iteração da lista para receber os dados e criar a árvore.
        while (!dados.fim()) {
            adiciona(dados.proximo()); //recebendo dado da lista e adicionando na árvore.
        }

    }

    template<typename T>
    void arvore<T>::adiciona(const T &algo) { //função adiciona um dado na árvore.
        auto atual = this; //recebendo raiz da árvore.
        while (true) {  //loop infinito
            if (algo == atual->data) { //caso de algo ter o mesmo valor da raíz.
                atual->data = algo;
                return;
            }
            if (algo < atual->data) { //caso de algo ser menor que o valor da raíz.
                if (atual->esq != nullptr)
                    atual = atual->esq; //verifica se o ponteiro esq for diferente de nullptr,caso seja atualiza ponteiro atual.
                else { //se for igual a nullptr, o nodo será adicionado ao lado esq da raíz.
                    atual->esq = new arvore<T>(algo); //colocando valor no nodo esq.
                    atual->esq->pai = atual; //atualizando ponteiro pai.
                    return;
                }
            } else { //caso se algo for maior que o valor da raíz.
                if (atual->dir != nullptr)
                    atual = atual->dir; //verifica se o ponteiro dir for diferente de nullptr,caso seja atualiza ponteiro atual.
                else { // se for igual a nullptr, o nodo será adicionado ao lado dir da raíz.
                    atual->dir = new arvore<T>(algo);  //colocando valor no nodo dir.
                    atual->dir->pai = atual; //atualizando ponteiro pai.
                    return;
                }
            }
        }
    }

    template<typename T>
    const T &
    arvore<T>::obtem(const T &algo) const { //obtem um dado da árvore que seja igual ao dado passado por parâmetro.
        auto atual = this; //recebendo ponteiro ráiz.
        while (atual != nullptr) { //loop ocorre enquando nodo for diferente de nullptr.
            if (atual->data == algo) {  //se o data do nodo for igual ao valor passado por parâmetro.
                return atual->data; //retorna o valor do nodo.
            }
            if (algo < atual->data)
                atual = atual->esq; //se o valor passado por parâmetro for menor que o valor do nodo atual, atualizan ponteiro atual para esq.
            else atual = atual->dir; //se o valor passado por parâmetro for maior que o valor do nodo atual, atualiza ponteiro atual para dir.
        }
        throw -1; //gera execão caso não encontre na árvore.
    }

    template<typename T>
    const T &arvore<T>::obtem() const { // retorna o valor da raíz da árvore.
        return this->data; //retornano valor da ráiz da árvore.
    }

    template<typename T>
    void arvore<T>::listeEmLargura(lista <T> &result) { //lista em largura os dados da árvore em uma lista.
        auto atual = this; //recebendo ponteiro da raiz.
        lista < arvore < T > * > p_stackaux; //criando uma lista de ponteiros.
        p_stackaux.anexa(atual); //anexa ponteiro atual.
        while (!p_stackaux.vazia()) { //loop acontece enquando lista não estiver vazia.
            auto nodo_aux = p_stackaux.remove(
                    0); //removendo o primeiro dado da lista de ponteiros e armazenando esse ponteiro em um ponteiro auxiliar.
            if (nodo_aux->esq) p_stackaux.anexa(nodo_aux->esq); //realiza operação recursiva para o nodo da esq.
            if (nodo_aux->dir) p_stackaux.anexa(nodo_aux->dir); //realiza operação recursiva para o nodo da dir.
            result.anexa(nodo_aux->data); //anexa o valor do nodo na lista result.
        }
    }

    template<typename T>
    void arvore<T>::listeInOrder(lista <T> &result) { //lista em ordem crescente os dados da árvore em uma lista.
        auto atual = this; //recebendo ponteiro da raiz da árvore.
        if (atual->esq != nullptr)
            atual->esq->listeInOrder(
                    result); //operação recursiva do lado esq, para capturar os menores dados da árvore.
        result.anexa(atual->data); //anexa valor do nodo.
        if (atual->dir != nullptr)
            atual->dir->listeInOrder(
                    result); //operação recursiva do lado dir, para capturar os maiores dados da árvore.
    }

    template<typename T>
    void arvore<T>::listePreOrder(lista <T> &result) { //lista a ordem da topologia dos dados da árvore em uma lista.
        auto atual = this; //recebendo ponteiro da raiz da árvore.
        result.anexa(atual->data); //anexa ráiz da árvore.
        if (atual->esq != nullptr)
            atual->esq->listePreOrder(
                    result); //operação recursiva para o lado esq, para capturar todos os dados de menor valor.
        if (atual->dir != nullptr)
            atual->dir->listePreOrder(
                    result); //operação recursiva para o lado dir, para capturar todos os dados de maior valor.
    }

    template<typename T>
    void arvore<T>::listePostOrder(lista <T> &result) { //lista em ordem descresente os dados da árvore em uma lista.
        auto atual = this; //recebendo ponteiro da raiz da árvore.
        if (atual->esq != nullptr)
            atual->esq->listePostOrder(
                    result); // operação recursiva para o lado esq, para capturar os dados maiores do lado esq.
        if (atual->dir != nullptr)
            atual->dir->listePostOrder(
                    result); //operação recursiva para o lado dir, para capturar os dados maiores do lado dir..
        result.anexa(atual->data); //anexa na lista
    }

    template<typename T>
    unsigned int arvore<T>::tamanho() const { // retorna o valor correspondente ao tamanho da árvore.
        unsigned int ct = 0; // inicia contador para identificar tamanho da árvore.
        if (esq) ct = ct + esq->tamanho(); //realiza operação recursiva no lado esq, caso esq existir.
        if (dir) ct = ct + dir->tamanho(); //realiza operação recursiva no lado dir, caso dir existir.
        ct++; //incrementa contador.
        return ct; //retorna valor do contador.
    }

    template<typename T>
    int arvore<T>::fatorB() { // retorna o fator de balanceamento da árvore.
        int altura_esq = 0, altura_dir = 0; //variáveis representam altura do lado esq, altura do lado dir.
        if (esq)
            altura_esq = 1 +
                         esq->altura(); //operação recursiva do lado esq , caso ele exista. a altura do lado esq é incrementada recursivamente caso exista esq.
        if (dir)
            altura_dir = 1 +
                         dir->altura(); //operação recursiva do lado dir , caso ele exista. a altura do lado dir é incrementada recursivamente caso exista dir.

        return altura_esq - altura_dir; //retorna diferença entre altura do lado esq e lado dir.
    }

    template<typename T>
    unsigned int arvore<T>::altura() { //retorna altura da árvore.
        unsigned int h_esq = 0, h_dir = 0; //alturar do lado esq e dir, inicialmente sendo de valor zero.
        if (esq != nullptr)
            h_esq = 1 +
                    esq->altura(); //operação recursiva do lado esq, caso ele exista. altura recebe incremnto das alturas das sub-arvores da esq.
        if (dir != nullptr)
            h_dir = 1 +
                    dir->altura(); //operação recursiva do lado dir, caso ele exista. altura recebe incremnto das alturas dos sub-arvores da dir.
        if (h_esq < h_dir) return h_dir; // caso altura do lado dir maior, retorna valor da altura do lado dir.
        return h_esq; //senão retorna valor da altura do lado esq.
    }

    template<typename T>
    arvore <T> *arvore<T>::rotacionaL() {
        arvore <T> *arv1 = this; //capturando raiz da árvore.
        arvore <T> *arv2 = arv1->dir; //capturando sub-árvore do lado dir.
        arvore <T> *arvb = arv2->esq; //capturando sub-árvore do lado esq.
        arv1->dir = arvb; //ponteiro dir da raiz recebe sub-árvore arvb.
        arv2->esq = arv1; //ponteiro esq da raiz da sub-árvore arv2 recebe sub-árvore arv1.
        if (arvb != nullptr) { //se sub-árvore arvb diferente de nullptr,rotaciona para esquerda.
            arvb->pai = arv1; //ponteiro pai da sub-árvore arvb recebe sub-árvore arv1.
            arv2->pai = arv2; //ponteiro pai da sub-árvore arv2 recebe sub-árvore arv2.
            arv1->pai = arv2; //ponteiro pai da sub-árvore arv1 recebe sub-árvore arv2.
        }
        return arv2; //retorna árvore rotacionada para esquerda.
    }

    template<typename T>
    arvore <T> *arvore<T>::rotacionaR() {
        arvore <T> *arv2 = this; //capturando raiz da árvore.
        arvore <T> *arv1 = arv2->esq; //capturando sub-árvore do lado dir.
        arvore <T> *arvb = arv1->dir; //capturando sub-árvore do lado esq.
        arv1->dir = arv2; //ponteiro dir da raiz recebe sub-árvore arv2.
        arv2->esq = arvb; //ponteiro esq da raiz da sub-árvore arv2 recebe sub-árvore arvb.
        if (arvb != nullptr) { //se sub-árvore arvb diferente de nullptr,rotaciona para esquerda.
            arvb->pai = arv2; //ponteiro pai da sub-árvore arvb recebe sub-árvore arv2.
            arv2->pai = arv1; //ponteiro pai da sub-árvore arv2 recebe sub-árvore arv1.
            arv1->pai = arv1; //ponteiro pai da sub-árvore arv1 recebe sub-árvore arv1.
        }
        return arv1; //retorna arvore rotacionada para direita.
    }

    template<typename T>
    arvore <T> *arvore<T>::balanceia() { //retorna árvore balanceada.
        if (esq != nullptr)
            esq = esq->balanceia(); //chama recursivamente para que todos do lado esq, para árvore se tornar balanceada.
        if (dir != nullptr)
            dir = dir->balanceia(); //chama recursivamente para que todos do lado dir, para árvore se tornar balanceada.
        arvore <T> *ndaux = this; //recebendo raiz da árvore.
        while (ndaux->fatorB() < -1) { //enquando fator de balanceamento da ráiz for menor que -1:
            if (ndaux->dir->fatorB() >
                0) { //verifica se o lado fator de balanceamento da sub-árvore da direita é maior que zero.
                ndaux->dir = ndaux->dir->rotacionaR(); //se for verdadeiro, rotaciona para direita.
            }
            ndaux = ndaux->rotacionaL(); //caso falso, rotaciona para esquerda.
        }
        while (ndaux->fatorB() > 1) { //enquando fator de balanceamento da ráiz for menor que 1:
            if (ndaux->esq->fatorB() <
                0) { //verifica se o lado fator de balanceamento da sub-árvore da esquerda é menor que zero.
                ndaux->esq = ndaux->esq->rotacionaL(); //se for verdadeiro, rotaciona para esquerda.
            }
            ndaux = ndaux->rotacionaR();  //caso falso, rotaciona para direita.
        }
        return ndaux;
    }

    template<typename T>
    arvore <T> *arvore<T>::balanceia(bool otimo) { // balanceia a árvore da melhor maneira possível.

        if (otimo == true) { //caso booleano verdadeiro:
            arvore <T> *nodo = this;
            while (true) { //loop acontece até que altura de antes e altura de depois, tenham mesmo valor.
                nodo = nodo->balanceia();
                int h_antes = nodo->altura(); //balanceia a árvore, armazena altura da árvore balanceada.
                nodo = nodo->balanceia(); //balanceia a árvore novamento, armazena altura da árvore balanceada novamente.
                int h_depois = nodo->altura();
                if (h_antes == h_depois) return nodo; //faz verificação das alturas e retorna raiz da árvore.
            }
        } else return balanceia(); //caso booleano falso chama balanceia.

    }

    template<typename T>
    void arvore<T>::inicia() {
        if (p_stack == nullptr)
            p_stack = new lista < arvore < T > * >; //caso fila de ponteiros for nullptr, cria uma lista de ponteiros.
        else p_stack->esvazia(); //senão esvazia a lista de ponteiros.
        p_stack->insere(this); //insere na lista a raiz da árvore.

    }

    template<typename T>
    T &arvore<T>::proximo() {
        if (fim()) throw -1;  //se pilha estiver vazia, dispara exeção.
        arvore <T> *nodo = p_stack->remove(0); //remove primeiro dado da lista de ponteiros.
        if (nodo->dir != nullptr) p_stack->insere(nodo->dir); //operação recursiva para dir.
        if (nodo->esq != nullptr) p_stack->insere(nodo->esq); //operação recursiva para esq.

        return nodo->data; //retorna dado do nodo.
    }

    template<typename T>
    bool arvore<T>::fim() {
        return p_stack->vazia(); //retorna se a lista de ponteiras esta vazia.
    }

    template<typename T>
    T &arvore<T>::obtemMenor() { //retorna o menor dado da árvore.
        arvore <T> *nodo = this; //recebendo raiz da árvore.
        while (nodo->esq) nodo = nodo->esq; //loop percorre árvore até o ultimo nodo da esquerda.
        return nodo->data; //retorna valor do nodo.
    }

    template<typename T>
    T &arvore<T>::obtemMaior() { //retorna o maior dado da árvore.
        arvore <T> *nodo = this; //recebendo raiz da árvore.
        while (nodo->dir) nodo = nodo->dir; //loop percorre árvore até o ultimo nodo da direita.
        return nodo->data; //retorna valor do nodo.
    }

    template<typename T>
    void arvore<T>::obtemMenoresQue(lista <T> &result, const T &algo) {
        arvore <T> *arv = this; //recebendo raiz da árvore.
        arv->inicia();
        while (!arv->fim()) { //iteração da árvore, quando dado for menor ou igual ao dado algo ele anexa na lista result.
            T dado = arv->proximo();
            if (dado <= algo) {
                result.anexa(dado);
            }
        }
    }

    template<typename T>
    void arvore<T>::obtemMaioresQue(lista <T> &result, const T &algo) {
        arvore <T> *arv = this; //recebendo raiz da árvore.
        arv->inicia();
        while (!arv->fim()) { //iteração da árvore, quando dado for maiorr ou igual ao dado algo ele anexa na lista result.
            T dado = arv->proximo();
            if (dado >= algo) {
                result.anexa(dado);
            }
        }
    }

    template<typename T>
    void arvore<T>::obtemIntervalo(lista <T> &result, const T &start,
                                   const T &end) { //obtem dados da árvore a partir de um intervalo.
        arvore <T> *arv = this; //recebendo raiz da árvore.
        T dado = arv->data;
        if (arv->data >= start && arv->data <=
                                  end) { //verifica se o data da raiz é menor igual ao start e menor igual ao end, e anexa na lista.
            result.anexa(dado);
            if (arv->esq != nullptr) { //caso lado esq for diferente de nullptr.
                arv->esq->obtemIntervalo(result, start, end); //chama recursivamente para lado esq.
            }
            if (arv->dir != nullptr) { //caso lado dir for diferente de nullptr
                arv->dir->obtemIntervalo(result, start, end); //chama recursivamente para lado dir.
            }
        } else if (arv->data < start) { //caso data da raiz menor que start.
            if (arv->dir != nullptr) { //caso lado dir for diferente de nullptr
                arv->dir->obtemIntervalo(result, start, end); //chama recursivamente para lado dir.
            }
        } else if (arv->data > end) { //caso da raiz for maior que end
            if (arv->esq != nullptr) { //caso lado esq for diferente de nullptr.
                arv->esq->obtemIntervalo(result, start, end); //chama recursivamente para lado esq.
            }
        }
    }

    template<typename T>
    T arvore<T>::obtem_sucessor(const T &algo) { //obtem o sucessor de um dado da árvore.
        if (algo >= obtemMaior())throw -1; //caso dado algo for maior igual ao maior dado da árvore, dispara exeção.
        T aux = obtemMaior(); //obtendo maior dado da árvore.
        arvore <T> *ptr = this; // recebendo raiz da árvore.
        while (true) { //loop infinito.
            if (ptr->data > algo) { // caso data da raiz for maior que algo.
                if (ptr->data < aux)
                    aux = ptr->data;  //se data do ponteiro ptr for menor que o maior dado da árvore, aux recebe data da raiz.
                if (ptr->esq == nullptr) { //caso ponteiro da esq do ponteiro ptr for nullptr, retorna valor de aux.
                    return aux;
                }
                ptr = ptr->esq; //atualizando ponteiro ptr.
            } else { //senão
                if (ptr->dir == nullptr) { //caso dir do ponteiro ptr for igual a nullptr retorna aux.
                    return aux;
                }
                ptr = ptr->dir; //atualiza ponteiro.
            }
        }
    }

    template<typename T>
    arvore<T>::arvore(const arvore <T> &outra) { //cria uma árvore a partir de outra.
        if (outra == nullptr) throw -1; //caso raiz da árvore passada por parâmetro for nullptr , dispara exeção.
        data = outra->data; //recebendo raiz da outra árvore.
        if (outra->esq != nullptr)
            esq = new arvore <T>(
                    outra->esq); //caso ponteiro esq da outra árvore for diferente esq recebe nodo da esq da outra árvore.
        else esq = nullptr;
        if (outra->dir != nullptr)
            dir = new arvore <T>(
                    outra->dir); //caso ponteiro dir da outra árvore for diferente esq recebe nodo da dir da outra árvore.
        else dir = nullptr;
    }

    template <typename T> bool arvore<T>::folha() const {
        return dir == nullptr && esq == nullptr;
    }

    template<typename T>
    bool arvore<T>::contem(arvore <T> *outra) {
        if(outra == nullptr) throw -1;
        auto atual = this;
        while(true) {
            if(atual->data == outra->data)break;
            else if(outra->data < atual->data) {
                if(atual->esq == nullptr) return false;
                atual = atual->esq;
            } else {
                if(atual->dir == nullptr) return false;
                atual = atual->dir;
            }
        }
        lista<T> l_atual;
        lista<T> l_outra;
        atual->listePreOrder(l_atual);
        outra->listePreOrder(l_outra);
        l_atual.inicia();
        l_outra.inicia();
        while(! l_atual.fim()) {
            T & dado1 = l_atual.proximo();
            T & dado2 = l_outra.proximo();
            if(dado1 != dado2)return false;
            if(l_outra.fim())return true;
        }
    }

    template<typename T>
    T arvore<T>::remove(const T &algo) {
        auto atual = this;
        while(true) {  //procurando o nodo desejado.
            if(atual->data == algo) break;
            else if(algo < atual->data) {
                if(atual->esq == nullptr) throw -1;
                atual = atual->esq;
            } else {
                if(atual->dir == nullptr) throw -1;
                atual = atual->dir;
            }
        }
        //verifica se é uma folha.
        T dado = atual->data;
        if(atual->folha()) {  //se for folha ele faz o pai e atual apontar para nullptr , e deleta nodo.
            atual->pai->dir= nullptr;
            atual = nullptr; //deleta e nullptr o ponteiro do nodo
            delete atual;
            return dado;
        }
        //verifica ponteiro, pelo fatorb.
        if(atual->fatorB() > 0){
            T algo = atual->esq->obtemMaior(); // obtem o dado do nodo da esquerda maior.
            atual->data = algo;
            if(atual->esq->folha()) {
                delete atual->esq;
                atual->esq = nullptr;
            } else {
                atual->esq->remove(algo);
            }
        } else {
            T algo = atual->dir->obtemMenor();
            atual->data = algo;
            if(atual->dir->folha()) {
                delete atual->dir;
                atual->dir = nullptr;
            } else {
                atual->dir->remove(algo);
            }
        }
        return dado;
    }

    template<typename T>
    arvore <T> *arvore<T>::dados_iguais(arvore <T> *outra) {
        if(outra == nullptr) throw -1;
        lista<T> l_dados_iguais;
        outra->inicia();
        while(!outra->fim()){
            T & dado = outra->proximo();
            try{
                obtem(dado);
                l_dados_iguais.anexa(dado);
            }catch (...){}
        }
        if(l_dados_iguais.comprimento() > 0) {
            auto aux = new arvore<T>(l_dados_iguais);
            return aux;
        }
        throw -1;
    }

    template<typename T>
    arvore <T> *arvore<T>::unir(arvore <T> *outra) {
        if(outra== nullptr) throw -1;
        lista<T> l_todos_dados;
        listeInOrder(l_todos_dados);
        outra->listeInOrder(l_todos_dados);
        auto arv = new arvore<T> (l_todos_dados);
        return arv;
    }


};

#endif /* ARVORE_IMPL_H */
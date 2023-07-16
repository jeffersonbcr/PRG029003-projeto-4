#ifndef    LISTA2_IMPL_H
#define    LISTA2_IMPL_H

namespace prglib {


    template<typename T>
    lista<T>::
            lista() { //cria lista com comprimento 0 e ponteiro atual recebendo endereço de guarda.
        len = 0;
        atual = &guarda;

    }

    template<typename T>
    lista<T>::lista(const lista <T> &outra) { //cria uma lista a partir de outra lista.
        len = 0; //inicialmente comprimento igual a zero.
        Nodo *aux; //criando nodo auxiliar.
        for (aux = outra.guarda.proximo;
             aux != &outra.guarda; aux = aux->proximo) { //percorrendo os ponteiros lista passada por parâmetro.
            anexa(aux->dado); //anexa dado do ponteiro na lista sendo criada.
        }
    }

    template<typename T>
    lista<T>::lista(std::istream &inp) {

    }

    template<typename T>
    lista<T>::~lista() { //destroi a lista.
        esvazia(); //esvazia lista.
    }

    template<typename T>
    void lista<T>::insere(const T &algo) { //conecta um dado ao começo da lista.

        auto nodo = new Nodo(algo); //cria um nodo com dado algo.
        nodo->conecta(guarda.proximo); //conecta nodo na lista sendo seu sucessor o nodo proximo do guarda.
        len++; //incrementa comprimento.
    }

    template<typename T>
    void lista<T>::anexa(const T &algo) { //conecta um dado ao final da lista.
        auto nodo = new Nodo(algo); //cria um nodo com dado algo.
        nodo->conecta(&guarda); //conecta nodo na lista sendo seu sucessor o guarda.
        len++;  //incrementa comprimento.
    }

    template<typename T>
    int lista<T>::comprimento() const { //retorna valor do comprimento da lista.
        return len;  // retorna len.
    }

    template<typename T>
    void lista<T>::esvazia() { // esvazia a lista.
        while (len != 0) remove(0); //enquando len for diferente de zero chama função remove.
    }

    template<typename T>
    void lista<T>::insere(const T &algo, int posicao) { //conecta um dado a lista de acordo com uma posição.
        if (posicao >= len)
            anexa(algo); //caso posição passada por parâmetro for maior ou igual ao tamanho da lista, chaam função anexa.
        else { //senão
            auto nodo = new Nodo(algo); //cria nodo a partir do dado algo.
            Nodo *ptr = obtem_nodo(posicao); //recebe o nodo que esta na posição passada por parâmetro.
            nodo->conecta(
                    ptr); //conecta o nodo criado a partir do dado algo na frente do nodo que esta na posição passada por parâmetro.
            len++; //incrementa contador.
        }
    }

    template<typename T>
    T &lista<T>::obtem(int posicao) const { //obtem um dado da lista a partir de uma posição passada por parâmetro.
        if (posicao >= len) throw -1; //caso posição maior igual a len,dispara exeção.
        Nodo *ptr = obtem_nodo(posicao); //obtem nodo da posição.

        return ptr->dado; //retorna dado do nodo.
    }

    template<typename T>
    T &lista<T>::operator[](int pos) const {
        return obtem(pos); //chama obtem.
    }

    template<typename T>
    void lista<T>::escrevaSe(std::ostream &out) const {
        escrevaSe(out, "\n"); //chama escrevase com delimitador de quebra de linha.

    }

    template<typename T>
    void lista<T>::escrevaSe(std::ostream &out,const std::string &delim) const { //Imprime na tela dados da lista de acordo com um delimitador.
        if (vazia()) return; //caso vazia não retorna nada.
        Nodo *aux; //criando nodo auxiliar.
        for (aux = guarda.proximo;aux != guarda.anterior; aux = aux->proximo) { //percorrendo nodos da lista até o penultimo nodo.
            out << aux->dado << delim; //imprime na tela dado do nodo e delimitador.
        }
        out << guarda.anterior->dado; //imprime dado do ultimo nodo.
    }

    template<typename T>
    T lista<T>::remove(int posicao) { //remove um dado da lista de acordo com uma posição.
        if (posicao >= len) throw -1; //caso posição maior igual a len, dispara exeção.
        Nodo *ptr = obtem_nodo(posicao); //encontrando nodo desejado.
        ptr->desconecta(); //desconectando nodo.
        T dado = ptr->dado; //recebendo dado do nodo desejado.
        delete ptr; //deleta nodo.
        len--; //decrementa tamanho da lista.
        return dado; //retorna dado.
    }

    template<typename T>
    void lista<T>::retira(const T &algo) { //retira um dado da lista.
        Nodo *nodoaux;
        Nodo *ptr;
        for (nodoaux = guarda; nodoaux !=
                               guarda.anterior; nodoaux = nodoaux->proximo) { //percorre nodos da lista até encontrar o dado desejado, em seguida desconecta nodo da lista.
            ptr = ptr->proximo;
            T dado = ptr->dado;
            if (dado == algo) {
                ptr->desconecta();
                len--;
            }
        }
    }

    template<typename T>
    bool lista<T>::vazia() const {
        return len == 0; //retorna booleano caso comprimento da lista for igual a zero.
    }

    template<typename T>
    void lista<T>::insereOrdenado(const T &algo) { //insere um dado na lista ordenadamente.
        anexa(algo); //anexa dado na lista.
        ordena(); //em seguida ordena a lista.
    }

    template<typename T>
    void lista<T>::ordena() { //ordena dados da lista.
        if (len < 2) return;
        Nodo *ptr;
        Nodo *aux;
        for (ptr = guarda.proximo; ptr != guarda.anterior; ptr = ptr->proximo) { //loop percorre nodos de começo ao fim.
            Nodo *menor = ptr; //recebendo nodo menor.
            for (aux = ptr->proximo; aux != &guarda; aux = aux->proximo) { //loop percorre nodos que estão a frente do nodo menor.
                if (aux->dado < menor->dado) menor = aux; //caso dado do nodo aux menor que dado do nodo menor, menor recebe aux.
            }
            if (menor != ptr) { //se nodos diferentes.
                T dado = ptr->dado; //recebe dado do nodo ptr.
                ptr->dado = menor->dado; //dado de ptr recebe dado do nodo menor.
                menor->dado = dado; //dado do nodo menor recebe dado.
            }
        }

    }

    template<typename T>
    T &lista<T>::procura(const T &algo) const { //procura um dado na lista.
        Nodo *ptr;
        for (ptr = guarda.proximo; ptr !=
                                   &guarda; ptr = ptr->proximo) { //percorre os nodos da lista até encontrar o dado desejado, em seguida retorna ele.
            if (ptr->dado == algo) {
                T &dado = ptr->dado;
                return dado;
            }
        }
        throw -1;

    }

    template<typename T>
    lista <T> &lista<T>::procuraMuitos(const T &algo,
                                       lista <T> &outra) const { //procura todos os dados igual ao dado algo e anexa ele na lista.
        Nodo *ptr;
        for (ptr = guarda.proximo; ptr !=
                                   &guarda; ptr = ptr->proximo) { //percorre os nodos da lista, quando dado for igual ao algo , dado é anexado na lista.
            if (ptr->dado == algo) {
                outra.anexa(ptr->dado);
            }
        }
        return outra; //retorna lista.
        if (outra.vazia())throw -1; //caso lista passada por parâmetro for vazia, dispara exceção.
    }

    template<typename T>
    std::shared_ptr <lista<T>> lista<T>::procuraMuitos(
            const T &algo) const { //procura todos os dados igual ao dado algo e cria uma lista com todos os dados igual a algo.
        lista <T> outra;
        Nodo *ptr;
        for (ptr = guarda.proximo; ptr !=
                                   &guarda; ptr = ptr->proximo) { //percorre os nodos da lista, quando dado for igual ao algo , dado é anexado na lista.
            if (ptr->dado == algo) {
                outra.anexa(ptr->dado);
            }
        }
        return outra; //retorna lista.
        if (outra.vazia())throw -1; //caso lista outra for vazia, dispara exceção.
    }

    template<typename T>
    lista <T> &lista<T>::operator=(const lista <T> &outra) {
        if (!vazia()) esvazia(); //se lista atual não estiver vazia, esvazia lsita atual.
        Nodo *aux;
        for (aux = outra.guarda.proximo;
             aux != &outra.guarda; aux = aux->proximo) { //percorre nodos da lista outra e anexa na lista atual.
            anexa(aux->dado);
        }
    }

    template<typename T>
    bool lista<T>::operator==(const lista <T> &outra) const {
        if (len == outra.len) { //caso comprimento da lista atual for igual da lista outra.
            Nodo *aux;
            Nodo *aux_outra = outra.guarda.proximo;
            for (aux = guarda.proximo; aux != &guarda; aux = aux->proximo) { //percorre nodos da lista atual.
                if (aux->dado != aux_outra->dado)
                    return false; //caso dado da lista atual for diferente do dado da outra lista, retorna false.
                aux_outra = aux_outra->proximo; //atualiza nodo da lista outra.

            }
        } else return false; //caso comprimentos da lista atual e lista outra for diferentes retorna false.
        return true; //retorna true.

    }

    template<typename T>
    void lista<T>::inverte() { //inverte a ordem dos dados da lista..
        if (len < 2) return;

        Nodo *ptr = &guarda; //recebendo endereço de  guarda.
        do {
            Nodo *aux = ptr->proximo; //invertendo ponteiros.
            ptr->proximo = ptr->anterior; //invertendo ponteiros.
            ptr->anterior = aux; //invertendo ponteiros.
            ptr = aux; //atualiza nodo.
        } while (ptr != &guarda); //loop ocorre enquando for diferente do endereço de guarda.



    }

    template<typename T>
    bool lista<T>::inicio() const {
        return atual == &guarda; //retorna se atual igual ao endereço do guarda.
    }

    template<typename T>
    bool lista<T>::fim() const {
        return atual == &guarda; //retorna se atual igual ao endereço do guarda.
    }

    template<typename T>
    void lista<T>::inicia() {
        atual = guarda.proximo;  //atual recebe o nodo seguinte ao guarda.
    }

    template<typename T>
    void lista<T>::iniciaPeloFim() {
        atual = guarda.anterior; //atual recebe o nodo anterior ao guarda.
    }

    template<typename T>
    T &lista<T>::proximo() {
        if (atual == &guarda) throw -1; //se nodo atual for igual endereço de guarda, dispara exeção.
        T &dado = atual->dado; //recebendo dado do nodo.
        atual = atual->proximo; //atualizando nodo para o nodo seguinte.
        return dado; //retorna dado do nodo.
    }

    template<typename T>
    T &lista<T>::anterior() {
        if (atual == &guarda) throw -1;  //se nodo atual for igual endereço de guarda, dispara exeção.
        T &dado = atual->dado; //recebendo dado do nodo.
        atual = atual->anterior; //atualizando nodo para o nodo anterior..
        return dado; //retorna dado do nodo.
    }

    template<typename T>
    lista <T> &lista<T>::sublista(unsigned int pos1, unsigned int pos2, lista <T> &outra) const {
        if (pos1 < 0 || pos2 > len || pos1 > pos2)throw -1;
        else {
            if (!outra.vazia()) outra.esvazia();
            for (int ct = pos1; ct <= pos2; ct++) {
                Nodo *pos_um = obtem_nodo(ct);
                outra.anexa(pos_um->dado);


            }
        }
        return outra;
    }

    template<typename T>
    lista <T> *lista<T>::sublista(unsigned int pos1, unsigned int pos2) const {
        lista <T> outra;
        sublista(pos1, pos2, outra);
        return outra;
    }

    template<class T>
    void lista<T>::embaralha() {
        if (len < 2)return;// para len menor que 2 não faz nada.
        for (int ct = len - 1; ct > 0; ct--) {
            int j = rand() % (ct + 1); //embaralhamento ocorre de acordo com uma posição gerada aleatória
            if (ct != j) { //se contador diferente de posição gerada aleatoriamente.
                T &dado1 = obtem(ct); //recebe dados da posições ct e j e troca seus valores.
                T &dado2 = obtem(j); //recebe dados da posições ct e j e troca seus valores.
                T aux = dado1;
                dado1 = dado2;
                dado2 = aux;
            }
        }
    }

    template<typename T>
    typename lista<T>::Nodo *lista<T>::obtem_nodo(int posicao) const { //obtem um nodo apartir de uma posição.
        Nodo *ptr = guarda.proximo; //recebendo primeiro nodo da lista.
        while (posicao-- > 0) ptr = ptr->proximo; //atualizando nodo até encontrar a posição correta.
        return ptr; //retorna nodo.
    }

    template<typename T>
    int lista<T>::trunca(int posicao) { //remove todos dados de acordo com uma posição.
        if (len == 0) return 0; //caso tamanho da lista for igual a zero, retorna zero.
        if (posicao > len) return 0; // caso posição maior que o tamanho da lista, retorna zero.
        Nodo *aux = obtem_nodo(posicao - 1); //obtem nodo da posição anterior a desejada.
        int tam = len; //recebendo tamanho da lista.
        while (aux->proximo != &guarda) { //loop desconecta os nodos seguintes ao nodo da posição anterior do desejado.
            aux->proximo->desconecta(); //desconecta nodo da lista.
            len--; //decrementa comprimento.
        }
        return tam - posicao; //retorna número de nodos retirados.
    }

    template<typename T>
    void lista<T>::anexa(const lista <T> &dados) { //anexa todos dados de uma lista, a lista atual.
        if (dados.len == 0) return; //caso comprimento da lista passada por parâmetro igual a zero, não faz nada.
        Nodo *aux;
        for (aux = dados.guarda.proximo; aux != &dados.guarda; aux = aux->proximo) { //loop percorre nodos da lista passada por parãmetro e anexa na lista atual.
            anexa(aux->dado);
        }
    }

} // fim namespace
#endif
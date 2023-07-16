#include "Projeto4.h"
#include <prglib.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace prglib;

lista<string> separa(const string & texto, const string & sep){ //Função realiza separação de substrings de uma string de acordo com um separador e anexa em uma lista.
    int pos = 0; //Declaração de variável.
    int pos0 = 0; //Declaração de variável.
    lista<string> l; //Declaração de variável.
    string palavra; //Declaração de variável.
    if (texto.size() > 0) //Se a variável possuir tamanho maior que zero faça:
    {
        do { //Faça:
            pos = texto.find_first_not_of(sep,pos); //Inteiro de nome pos recebe posição da string.
            pos0 = texto.find_first_of(sep,pos); //Inteiro de nome pos0 recebe posição da string.
            palavra = texto.substr(pos,pos0 - pos); //Gerando uma substring de acordo com as posições obtidas pelos inteiros pos e pos0.
            l.anexa(palavra); //Anexa na lista a substring gerado.
            if(texto.find_first_not_of(sep,pos) == string::npos) break; //Se condicional estiver no fim da string, para o loop que está em execução.
            pos = texto.find_first_not_of(sep,pos0); //Inteiro de nome pos recebe nova posição da string.
        } while (pos != string::npos); //Enquanto não estiver no fim da string.
    }
    return l; //Retorna a lista de nome l.
}


lista<Verbete> lista_de_verbetes(string arq_verbete){ //Função retorna uma lista de verbetes.
    ifstream arq(arq_verbete);
    lista<Verbete> lista_verbetes; //Declaração de variável.
    lista<string> linhas_arq,aux;
    string line,verb;
    if(arq.is_open()){
        while(getline(arq,line)){  //Recebendo dados do arquivo
            if(line.empty()){ //Caso string vazia manipula dados da lista.
                string algo = linhas_arq.obtem(0);
                aux = separa( algo ,"*");
                aux.inverte();
                Verbete verbet;
                verbet.palavra = aux.obtem(1);
                aux.esvazia();
                verbet.classe = linhas_arq.obtem(1);
                int cont = 0;
                linhas_arq.iniciaPeloFim();
                while(linhas_arq.inicio() || linhas_arq.comprimento() -2 != cont) {
                    string aux = linhas_arq.anterior();
                    verbet.significado.anexa(aux);
                    cont++;
                }
                lista_verbetes.anexa(verbet);
                linhas_arq.esvazia();
            }
            else{ //Caso string não vazia, adiciona na lista
                linhas_arq.anexa(line);
            }
        }
        return lista_verbetes; //retorna lista contendo dados do tipo verbete
    }
}


arvore <Verbete> * Add_verbete(arvore <Verbete> * arv, string Palavra, string Classe, string Significado){ //função adiciona um verbete a arvore.
    Verbete Nodo;
    Nodo.palavra=Palavra;
    Nodo.classe=Classe;
    lista<string> l;
    l.anexa(Significado);
    Nodo.significado=l;
    arv->adiciona(Nodo);
    return arv;
}

arvore<Verbete> * inicia_arvore(string verbetet,string dicionariot){ //Função retorna uma arvore de struct do tipo verbete.
    ifstream arq_dicionario(dicionariot);
    ifstream arq_verbete(verbetet);
    string line; //Declaração de variável.
    lista<Verbete> l1; //Declaração de variável.
    lista<string> l; //Declaração de variável.
    int ct =0; //Declaração de variável.
    if(arq_dicionario){ //Se o arquivo estiver.
        if(arq_dicionario.is_open()){ //Verifica se o arquivo está aberto.
            while(getline(arq_dicionario,line)){ //Loop ocorre enquanto ler linhas do arquivo.
                if(line.empty()){ //Se string estiver vazia.
                    Verbete verb; //Declaração de variável.
                    l.inicia(); //Inicia iteração da lista.
                    while(! l.fim()){ //Loop ocorre enquanto não estiver no fim da lista.
                        if(ct == 0) { //Se contador igual a zero.
                            verb.palavra = l.proximo(); //Recebendo dado da lista.
                            ct++; //Incrimento do contador.
                        }
                        else if (ct == 1){ //Se contador igual a um.
                            verb.classe = l.proximo();  //Recebendo dado da lista.
                            ct++; //Incrimento do contador.
                        }
                        else{
                            if(ct == 2){
                                lista<string> laux;
                                laux.anexa(l.proximo());
                                verb.significado = laux;
                            }
                            else verb.significado.anexa(l.proximo());  //Recebendo dado da lista.
                            ct++; //Incrimento do contador.
                        }
                    }
                    l1.anexa(verb); //Anexa verb na lista.
                    l.esvazia(); //Esvazia lista.
                    ct=0;
                }
                else{
                    l.anexa(line); //Anexa line na lista.
                }
            }
        }
        l1.embaralha();
        l1.inicia();
        auto arv = new arvore<Verbete> (l1.proximo());
        while(!l1.fim())arv->adiciona(l1.proximo());
        arv = arv->balanceia();
        return arv;
    }
    else{
        ofstream arq_out(dicionariot);
        lista<Verbete> ls; //Declaração de variável.
        lista<string> l; //Declaração de variável.
        ls = lista_de_verbetes(verbetet); //Ls recebe resultado da função lista_de_verebetes.
        ls.embaralha();
        ls.inicia(); //Inicia iteração da lista.
        auto arv = new arvore <Verbete> (ls.proximo()); //Criando arvore de structs.
        while(! ls.fim()){ //Loop ocorre enquanto não estiver no fim da lista.
            arv->adiciona(ls.proximo()); //Arvore adiciona conteudo da lista.
        }
        arv = arv->balanceia();
        ls.esvazia(); //Esvazia lista ls.
        arv->listePreOrder(ls); //Chama função que retorna uma lista com a topologia da arvore.
        ls.inicia(); //Inicia itereção da lista.
        while(! ls.fim()){ //Loop ocorre enquanto não estiver no fim da lista.
            Verbete verb_aux = ls.proximo(); //Recebendo dado da lista.
            arq_out << verb_aux.palavra << endl; //Escrevendo no arquivo o nome do verbete.
            arq_out << verb_aux.classe << endl; //Escrevendo no arquivo o tipo do verbete.
            l = verb_aux.significado;
            l.inicia();
            while(! l.fim()){
                arq_out << l.proximo() << endl; //Escrevendo no arquivo o conceito do verbete.
            }
            arq_out << endl;
        }
        return arv;
    }
}


Verbete obtem_verbete(string verb_desejado,arvore<Verbete> * arv){ //Função retorna um verbete buscando em uma arvore de struct do tipo verbete.
    Verbete aux,verb;
    aux.palavra = verb_desejado;
    try { //tente obter um verbete da arvore.
        verb = arv->obtem(aux);
        return verb; //retorna verbete.
    } catch (...) { //caso mensagem de erro, exceção.
        throw -1;
    }
}

lista <Verbete> obtem_muitos_verbetes(lista<string> lista_verbs_desejados,arvore <Verbete> * arv){ //Função retorna muitos verbetes de procura.
    lista<Verbete> l_verbetes;
    lista_verbs_desejados.inicia(); //Inicia iteração da lista.
    while(! lista_verbs_desejados.fim()){ //Loop ocorre enquanto não estiver no fim da lista.
        string aux = lista_verbs_desejados.proximo(); //Recebendo dado da lista.
        Verbete verb_aux,verb;
        verb_aux.palavra = aux;
        try{
            verb =arv->obtem(verb_aux);
            l_verbetes.anexa(verb);
        }catch (...){}
    }
    return l_verbetes; //Retorna lista com os verbetes desejados.

}
void mostrar_um_verbete(Verbete verb){ //função mostra um verbete.
    cout <<"palavra: " << verb.palavra << endl; //Imprime na tela a palavra do verbete.
    cout <<"classe da palavra: " << verb.classe << endl; //Imprime na tela a classe da palavra.
    cout << "significado da palavra: ";
    verb.significado.escrevaSe(cout); //Imprime os significados da palavra.
    cout << endl;
}
void mostrar_n_verbetes(lista<Verbete> l_verbetes){ //função mostra n verbetes.
    l_verbetes.inicia(); //inicia iteração da lista de verbetes.
    while(!l_verbetes.fim()){ //loop ocorre enquanto não estiver no fim da lista.
        Verbete verb = l_verbetes.proximo();
        mostrar_um_verbete(verb); //chama função mostra_um_verbete.
        cout << endl;
    }
}
lista<Verbete> Palavras_prefixo(arvore <Verbete> * arv, string prefixo){//função que retorna uma lista com os verbetes de prefixos
    lista<Verbete> L_Verbetes_prefixos;//lista de verbetes que vai ser retornados
    Verbete verb_min;//essa vai ser o paramentro baixo, a partir dessa ordem que vai buscar
    verb_min.palavra=prefixo;//o prefixo que foi dado como parametro inicial
    Verbete verb_max;// Verbete que limitara até aonde desejamos
    verb_max.palavra=prefixo+"zzzz";// foi adicionado zzzz pelo fato que nenhuma palavra vai ser com esse prefixo vai ser seguido de zzzz sendo inferior e entrando dentro do padrão
    arv->obtemIntervalo(L_Verbetes_prefixos,verb_min,verb_max);// ele retorna na lista todos valores com esse prefixo
    if(L_Verbetes_prefixos.vazia()){// só anuncia que caso a lista esteja vazia não contem nenhuma palavra
        cout<<"Nenhum palavra com esse prefixo"<<endl;
    }
    return L_Verbetes_prefixos;//retorna a lista de prefixo como solicitado
}

void gravar_no_arquivo(arvore<Verbete> * arv,string arq_dicionario){
    lista<Verbete> ls;
    lista<string> l;
    ofstream arq_out(arq_dicionario);
    arv = arv->balanceia();
    arv->listePreOrder(ls); //Chama função que retorna uma lista com a topologia da arvore.
    ls.inicia(); //Inicia itereção da lista.
    while(! ls.fim()){ //Loop ocorre enquanto não estiver no fim da lista.
        Verbete verb_aux = ls.proximo(); //Recebendo dado da lista.
        arq_out << verb_aux.palavra << endl; //Escrevendo no arquivo o nome do verbete.
        arq_out << verb_aux.classe << endl; //Escrevendo no arquivo o tipo do verbete.
        l = verb_aux.significado;
        l.inicia();
        while(! l.fim()){
            arq_out << l.proximo() << endl; //Escrevendo no arquivo o conceito do verbete.
        }
        arq_out << endl; //escrevendo no arquivo quebra de linha.
    }
}
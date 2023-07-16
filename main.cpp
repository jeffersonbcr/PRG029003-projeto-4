#include "Projeto4.h"
#include <prglib.h>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using namespace prglib;

int main() {
    string verebetetxt, dicionariotxt;
    verebetetxt = "../verbetes.txt";
    dicionariotxt = "../dicionario.txt";
    arvore<Verbete> * arv_exemplo = inicia_arvore(verebetetxt, dicionariotxt); //inicialização do dicionário
    cout << "Menu de aplicações um dicionário de português..." << endl;
    cout << "[1]...Procurar um verbete" <<endl;
    cout << "[2]...Procurar um lote de verbetes" <<endl;
    cout << "[3]...Adicionar um verbete" <<endl;
    cout << "[4]...Procurar verbetes por prefixo" <<endl;
    cout << "Qual quer outra opção diferentes aos de cima resultará no encerramento do programa..." << endl;
    int opcao = 1;
    while(opcao){
        cout << "Digite o número de aplicação desejado..." << endl;
        cin >> opcao;
        cin.ignore();
        switch(opcao) {
            case 1: { //Opção procura um verbete.
                string palavra;
                cout << "Digite a palavra do verbete..." << endl;
                getline(cin, palavra);
                palavra[0] = toupper(palavra.front());
                getchar();
                Verbete verbete_aux = obtem_verbete(palavra, arv_exemplo);
                mostrar_um_verbete(verbete_aux);
                break;
            }
            case 2:{ //opção procura um lote de verbetes.
                string teclado;
                lista<string> lista_verbetes;
                do {
                    cout << "Digite a palavra verbete a ser procurado..." << endl;
                    getline(cin, teclado);
                    teclado[0] = toupper(teclado.front());
                    getchar();
                    lista_verbetes.anexa(teclado);
                } while (!teclado.empty());
                lista<Verbete> l_verbetes = obtem_muitos_verbetes(lista_verbetes, arv_exemplo);
                mostrar_n_verbetes(l_verbetes);
            }
            case 3: { //opção adiciona adicionar um verbete ao dicionário.
                string palavra, classe, significados;
                lista<string> lista_significados;
                cout << "Digite o verbete para ser adicionado ao dicionário..." << endl;
                cout << "Digite a palavra do verbete: " << endl;
                getline(cin, palavra);
                palavra[0] = toupper(palavra.front());
                getchar();
                cout << "Digite a classe do verbete: " << endl;
                getline(cin, classe);
                classe[0] = toupper(classe.front());
                getchar();
                cout << "Digite os significados do verbete em uma frase: " << endl;
                getline(cin, significados);
                significados[0] = toupper(significados.front());
                getchar();
                arv_exemplo = Add_verbete(arv_exemplo, palavra, classe, significados);
                gravar_no_arquivo(arv_exemplo, dicionariotxt);
            }
            case 4: { //opção procura verbetes por prefixo.
                string palavra;
                lista<Verbete> lista_verbete;
                cout << "Digite o prefixo desejado: " << endl;
                getline(cin, palavra);
                palavra[0] = toupper(palavra.front());
                lista_verbete = Palavras_prefixo(arv_exemplo, palavra);
                mostrar_n_verbetes(lista_verbete);
            }
            default:
                cout << "Programa finalizado..." << endl;
                opcao=0;
                break;
        }
    }
}
/*
o programa é destinado ao uso de um dicionário criado a partir de um arquivo denominado de verbetes.txt, após ser criado
as opções de operação de utilidade já estão disponivel para o usuário.
O programa na linha 14 é responsável por iniciar o dicionário realizando duas verificações a primeira: verifica se o ar-
quivo dicionário já existe, neste caso a função retorna uma arvore de acordo com as informações do arquivo existente.
A segunda verificação: é o caso do arquivo não existir , contudo a arvore será criada e balanceada a partir do arquivo
verbetes.txt e depois será gravado em um arquivo denominado dicionario.txt.
Estrutura do verbete:
palavra = nome do verbete.
classe = classe(s) gramaticáis do verbete.
significados = significados do verbete.
opção de número 1: procura um verbete recebendo por parâmetro um termo (palavra) e retorna uma estrutura de dado do tipo
verbete,para mostrar o conteúdo do verbete chame a função mostra_um_verbete e passar por parâmetro o dado do tipo verbete.
opção de número 2: procura um lote de verbetes recebendo por parâmetro uma lista de strings contendo termos(palavras)
para obter o lote de verbetes, a função retorna uma lista de estrutura do tipo verbete, para mostrar o conteúdo da lista
chame a função mostrar_n_verbetes e passar por parâmetro o nome da lista contendo os dados do tipo verbete.
opção de número 3: adicionar um verbete recebendo por parâmetro palavra,classe,significados criando um verbete por esses
parâmetros e adicionando na arvore já existente e finalizando com a gravação no arquivo dicionario.txt.
opção de número 4:
*/
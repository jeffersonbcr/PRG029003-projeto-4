# Prglib: biblioteca de estruturas de dados elementares

A [Prglib](https://wiki.sj.ifsc.edu.br/wiki/index.php/PRG29003:_Etapa_2:_A_constru%C3%A7%C3%A3o_da_prglib) é uma pequena biblioteca contendo estruturas de dados para fins didáticos. Ela foi escrita para a disciplina de [Programação II](https://wiki.sj.ifsc.edu.br/wiki/index.php/PRG29003:_Introdu%C3%A7%C3%A3o_a_C%2B%2B) da [Engenharia de Telecomunicações](https://wiki.sj.ifsc.edu.br/wiki/index.php/Curso_de_Engenharia_de_Telecomunica%C3%A7%C3%B5es) do [IFSC Câmpus São José](http://www.sj.ifsc.edu.br/). E contém as seguintes estruturas de dados:
* __Fila__: uma fila circular com capacidade definido no momento de sua criação
* __Pilha__: uma pilha cuja capacidade também é definida no instante de sua criação
* __Lista__: uma lista duplamente encadeada, e possivelmente circular (depende da implementação do estudante)
* __Tabela hash__: uma tabela hash com quantidade de linhas (buckets) definida no instante de sua criação. Além disso, por simplicidade as chaves são do tipo string
* __Árvore de pesquisa binária__: uma árvore com operações de balanceamento com algoritmo [AVL](https://en.wikipedia.org/wiki/AVL_tree)

# Projeto 4

O código em questão é um sistema de manipulação de verbetes de um dicionário, contendo várias funções que permitem adicionar, buscar e exibir verbetes.

## Estrutura do Código
O código está organizado em diversas funções, cada uma responsável por uma tarefa específica. A seguir, serão descritas as principais funções e sua finalidade:
```cpp
separa(const string &texto, const string &sep) // Realiza a separação de substrings de uma string, de acordo com um separador, e as anexa em uma lista.

lista_de_verbetes(string arq_verbete)// Lê um arquivo de verbetes e retorna uma lista de verbetes.

Add_verbete(arvore<Verbete> *arv, string Palavra, string Classe, string Significado)// Adiciona um novo verbete a uma árvore de verbetes.

inicia_arvore(string verbetet, string dicionariot)// Inicia uma árvore de verbetes a partir de um arquivo, preenchendo-a com os dados do arquivo de verbetes. Caso o arquivo do dicionário não exista, ele é criado e preenchido.

obtem_verbete(string verb_desejado, arvore<Verbete> *arv)// Busca e retorna um verbete em uma árvore de verbetes.

obtem_muitos_verbetes(lista<string> lista_verbs_desejados, arvore<Verbete> *arv)// Busca e retorna vários verbetes em uma árvore de verbetes.

mostrar_um_verbete(Verbete verb)// Imprime na tela as informações de um único verbete.

mostrar_n_verbetes(lista<Verbete> l_verbetes)// Imprime na tela as informações de vários verbetes.

Palavras_prefixo(arvore<Verbete> *arv, string prefixo)// Retorna uma lista de verbetes que possuem um determinado prefixo.

gravar_no_arquivo(arvore<Verbete> *arv, string arq_dicionario)// Grava os dados de uma árvore de verbetes em um arquivo.
```
## Conclusão
O código analisado apresenta um sistema de manipulação de verbetes de um dicionário, permitindo adicionar, buscar e exibir verbetes. As funções e estruturas de dados utilizadas proporcionam uma organização eficiente dos verbetes, permitindo uma fácil busca e manipulação dos mesmos.

Espero que este relatório tenha fornecido uma visão clara das principais características e funcionalidades do código analisado. Para mais detalhes e implementações específicas, é recomendado verificar o próprio código fonte.
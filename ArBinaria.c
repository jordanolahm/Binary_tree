#include "ArBinaria.h"

ArBinaria* Cria_Arbinaria() //aloca dinamicamente uma arvore na memoria
{
    ArBinaria* raiz = (ArBinaria*) malloc(sizeof(ArBinaria));
    return raiz;
}

void libera_NO(struct NO* no) //libera o no da memoria
{
    if(no == NULL)
        return;

    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
}

int insere_ArBinaria(ArBinaria *raiz, int dado){
    if(raiz == NULL)
        return 0;

    struct NO* novo;//cria um nó, atribui os dados ao nó
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->dado = dado;
    novo->dir = NULL;
    novo->esq = NULL;

    if(raiz == NULL) //se a raiz estiver vazia, coloca esse novo nó na raiz
        raiz = novo;
    else{
        struct NO* atual = raiz;
        struct NO* ant = NULL;

        while (atual != NULL){
            ant = atual;
            if(dado == atual->dado){ //se o dado já existir no nó atual, ele libera o novo nó e sai da função
                free(novo);
                return 0;
            }
            if(dado > atual->dado) //se o dado for maior que o dado que está sendo verificado, ele coloca o dado que está sendo comparado como filho direito do dado novo
                atual = atual->dir;
            else // se for menor, vai ser o filho esquerdo
                atual = atual->esq;
        }

        if(dado > ant->dado) //se o dado for maior que o dado anterior, o novo nó vai ser filho direito do nó anterior
            ant->dir = novo;
        else // do contrário, vai ser filho esquerdo
            ant->esq = novo;

    }

    return 1;
}
struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){ //se o nó da esquerda for nulo, então o nó auxiliar2 vai receber o filho direito do nó atual e o nó atual é liberado
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    no1 = atual;
    no2 = atual;
    while(no2->dir != NULL){ //verifica se o nó auxiliar2 é diferente de nulo e atribui o valor do auxilir2 ao auxiliar1 e o auxiliar2 recebe o filho direito dele mesmo
        no1 = no2;
        no2=no2->dir;
    }

    if(no1 != atual){ //se o nó auxiliar1 for difernte do nó atual, o filho direito do nó auxiliar1 recebe o filho esquerdo do nó auxiliar2 e o filho esquerdo do nó auxiliar2 recebe o filho esquerdo do nó atual
        no1->dir = no2->esq;
        no2->esq = atual->esq;

    }
    no2->dir = atual->dir; //filho direito de nó auxiliar2 recebe o filho direito do nó atual e o nó atual é liberado
    free(atual);

    return no2;

}

int remove_ArBinaria(ArBinaria *raiz, int dado){ //função que remove a árvore toda
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = raiz;

    while(atual != NULL){ //enquanto o nó atual for diferente de nulo ele realizará as ações abaixo
        if(dado == atual->dado){ //se o dado do paramentro for igual ao do nó atual
            if(atual == raiz) //verifica-se se o nó atual é igual a raiz, se verdadeiro, remove o nó atual e atribui o nó resultante a raiz
                raiz = remove_atual(atual);
            else{//caso falso,
                if(ant->dir == atual)//verifica-se se o filho direito do nó anterior é igual ao atual, se verdadeiro, remove o atual e atribui o nó resultante ao filho direito do nó anterior
                    ant->dir = remove_atual(atual);
                else//verifica-se se o filho direito do nó anterior é diferente do nó atual, se verdadeiro, remove o atual e atribui o nó resultante ao filho esquerdo do nó anterior
                    ant->esq = remove_atual(atual);

            }
            return 1;

        }
        ant = atual;
        if(dado > atual->dado) //se o dado for maior que o dado atual, atribui o filho direito do nó atual
            atual = atual->dir;
        else //se o dado for menor que o dado atual, atribui o filho esquerdo do nó atual ao nó atual
            atual = atual->esq;
    }
    return 0;


}

int insere_Rec(ArBinaria *raiz, int dado){
    if(raiz == NULL){ //se a raiz for nula, cria-se um novo nó, atribui os dados a ele e coloca ele como raiz
        struct NO *novo;
        novo = (struct NO*) malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;
        novo->dado = dado;
        novo->esq = NULL;
        novo->dir = NULL;
        raiz = novo;
        return 1;
    }
    else{//se a raiz não for nula,
        if(dado < raiz->dado) //verifica-se se o dado é menor que a raiz e chama a função recursivamente passando o filho esquerdo da raiz como paramentro
            return insere_Rec(raiz->esq, dado);
        else{//caso a condição acima for falsa
            if(dado > raiz->dado)//verifica se o dado é maior que o dado da raiz e chama a função recursivamente passando o filho direito da raiz como parametro
                return insere_Rec(raiz->dir, dado);
            else //caso o dado for igual ao dado da raiz, não faz nada
                return 0;
        }


    }

}

int consulta_rec(ArBinaria *raiz, int dado){
    if(raiz == NULL)
        return 0;
    if(dado < raiz->dado) //se o dado for menor que o dado da raiz, procura-se pelo dado a partir do filho esquerdo da raiz
        consulta_rec(raiz->esq,dado);
    else //se o dado for maior
        if(dado<raiz->dado)//se o dado for maior, procura-se pelo dado a partir do filho esquerdo da raiz
            consulta_rec(raiz->esq,dado);
        else //quando o dado é encontrado
            return 1;

}

struct NO* consultaNO(ArBinaria *raiz, int dado){ //faz as mesmas coisas que a consulta acima, porém quando o dado é encontrado, o nó do dado é retornado
    if(raiz == NULL)
        return 0;
    if(dado < raiz->dado)
        consultaNO(raiz->esq,dado);
    else
        if(dado<raiz->dado)
            consultaNO(raiz->esq,dado);
        else{
            struct NO *aux = raiz;
            return aux;
        }

}

struct NO* ED(ArBinaria *raiz){
    if(raiz->dir != NULL) //vai chamar a função recursivamente até encontrar um nó nulo
        return ED(raiz->dir);
    else{ //quando o filho direito da raiz for nulo, atribui o valor da raiz ao nó auxiliar
        struct NO *aux = raiz;
        if(raiz->esq !=NULL) //se o filho esquerdo da raiz for diferente de nulo, atribui o filho esquerdo da raiz a raiz
            raiz = raiz->esq;
        else{ //caso o filho esquerdo da raiz for nulo, a raiz é nula e retorna o valor do nó auxiliar
            raiz = NULL;
            return aux;
        }
    }

}

struct NO* DE(ArBinaria *raiz){ //mesma coisa que a função acima só que com inversão de lados
    if(raiz->esq != NULL)
        return DE(raiz->esq);
    else{
        struct NO *aux = raiz;
        if(raiz->dir !=NULL)
            raiz = raiz->dir;
        else{
            raiz = NULL;
        return aux;
        }
    }
}

int remover_rec(ArBinaria *raiz, int dado){
    if(raiz == NULL)
        return 0;
    if(dado < raiz->dado) //se o dado for menor que o dado da raiz, chama a função recursivamente utilizando o filho esquerdo da raiz como parametro
        remover_rec(raiz->esq,dado);
    if(dado > raiz->dado) //se o dado for maior que o dado da raiz, chama a função recursivemente utilizando o filho direito da raiz como parametro
        remover_rec(raiz->dir,dado);
    else{ //se o dado for igual a raiz
        struct NO *ptAux = raiz;
        if((raiz->esq == NULL) && (raiz->dir == NULL) ){//verifica se os filhos da raiz são nulos, se forem nulos, atribui a raiz como nula
            free(ptAux);
            raiz = NULL;
            return 1;
        }
        else{//se os filhos da raiz não forem nulos

            if(raiz->esq == NULL){//filho a direita //se o filho da esquerda da raiz for nulo, a raiz recebe seu filho direito
                raiz = raiz->dir;
                ptAux->dir = NULL;
                free(ptAux);
                return 1;

            }

            else{
                if(raiz->dir == NULL){//filho a esquerda //se o filho da direita da raiz for nulo, a raiz recebe seu filho esquerdo
                    raiz = raiz->esq;
                    ptAux->esq = NULL;
                    free(ptAux);
                    ptAux = NULL;
                    return 1;
                }
                else{ //se o filho da direita não for nulo, chama a função ED passando o filho esquerdo da raiz como parametro, atribui os filhos da raiz ao nó auxilir, depois atribui o nó auxiliar a raiz
                    ptAux = ED(raiz->esq);
                   // ptAux = DE(&(*raiz)->dir);
                    ptAux->esq = raiz->esq;
                    ptAux->dir = raiz->dir;
                    raiz->esq = NULL;
                    raiz->dir = NULL;
                    free(raiz);
                    raiz = ptAux;
                    ptAux = NULL;
                    return 1;

                }
            }
        }
    }
}

void preOrdem(ArBinaria *raiz){ //lê a arvore em pré-ordem
    if(raiz = NULL)
        return;
    if(raiz != NULL){
        printf("%d\n",raiz->dado);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}
int vazia_ArBinaria(ArBinaria *raiz){ //verifica se a árvore está vazia
    if(raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArBinaria(ArBinaria *raiz){ //retorna o número de nós da árvore
    if(raiz == NULL)
        return 1;
    int alt_esq = totalNO_ArBinaria(raiz->esq);
    int alt_dir = totalNO_ArBinaria(raiz->dir);
    return (alt_esq + alt_dir + 1);
}

int altura_ArBinaria(ArBinaria *raiz) //calcula a altura da árvore
{ //vai contando cada nível da árvore até chegar ao último, verifica qual nível de cada lado que é maior e retorna o maior
    if( !raiz )
        return 0;

	int h_esq = altura_ArBinaria(raiz->esq);
	int h_dir = altura_ArBinaria(raiz->dir);

	return h_esq>h_dir ? h_esq+1 : h_dir+1;
	/*if(h_esq > h_dir)
        return h_esq+1
    else
        return h_dir+1;*/
}

void emOrdem(ArBinaria *raiz);
void posOrdem(ArBinaria *raiz);

// Arvore AVL
// implementação

int CalculaFB(ArBinaria* raiz) //calcula o fator de balanceamento daquele nó
{
    if( !raiz )
        return 0;

    return altura_ArBinaria(raiz->esq) - altura_ArBinaria(raiz->dir);
}

int SetaFB(ArBinaria *raiz) //atribui o fator de balanceamenta ao nó
{
    if( !raiz )
        return 0;

	int h_esq = SetaFB(raiz->esq);
	int h_dir = SetaFB(raiz->dir);

	raiz->FB = h_esq - h_dir;

	return h_esq>h_dir ? h_esq+1 : h_dir+1;
}

ArBinaria* RotacaoDireitaSimples(ArBinaria *raiz)
{
    ArBinaria *NoAux = raiz->esq;


    if ( NoAux->dir )
        raiz->esq = NoAux->dir;
    else
        raiz->esq = NULL;

    NoAux->dir = raiz;
    return NoAux;
}

ArBinaria* RotacaoDireitaDupla(ArBinaria *raiz)
{
    ArBinaria *NoAux1 = raiz->esq,
             *NoAux2 = NoAux1->dir;

    if ( NoAux2->esq )
        NoAux1->dir = NoAux2->esq;
    else
        NoAux1->dir = NULL;

    if ( NoAux2->dir )
        raiz->esq = NoAux2->dir;
    else
        raiz->esq = NULL;

    NoAux2->esq = NoAux1;
    NoAux2->dir = raiz;

    return NoAux2;
}

ArBinaria* RotacaoEsquerdaSimples(ArBinaria *raiz)
{
    ArBinaria *NoAux = raiz->dir;

    if ( NoAux->esq )
        raiz->dir = NoAux->esq;
    else
        raiz->dir = NULL;

    NoAux->esq = raiz;

    return NoAux;
}
ArBinaria* RotacaoEsquerdaDupla(ArBinaria *raiz)
{
    ArBinaria *NoAux1 = raiz->dir,
             *NoAux2 = NoAux1->esq;

    if ( NoAux2->esq )
        raiz->dir = NoAux2->esq;
    else
        raiz->dir = NULL;

    if ( NoAux2->dir )
        NoAux1->esq = NoAux2->dir;
    else
        NoAux1->esq = NULL;

    NoAux2->esq = raiz;
    NoAux2->dir = NoAux1;

    return NoAux2;
}
ArBinaria* BalanceiaAVL(ArBinaria *raiz) // igual ao SetaFB...
{
    if ( raiz )
    {
        raiz->esq = BalanceiaAVL( raiz->esq );
        raiz->dir = BalanceiaAVL( raiz->dir );



        SetaFB( raiz );
        if (raiz->FB == 2)
        {
            if(raiz->esq->FB > 0)
                raiz = RotacaoDireitaSimples( raiz );
            else
                raiz = RotacaoDireitaDupla( raiz );
        }

        else
            if (raiz->FB == -2)
            {
                if(raiz->dir->FB < 0)
                    raiz = RotacaoEsquerdaSimples(raiz) ;
                else
                    raiz = RotacaoEsquerdaDupla (raiz);
            }
    }

    return raiz;
}

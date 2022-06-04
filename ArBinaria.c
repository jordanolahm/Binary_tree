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

    struct NO* novo;//cria um n�, atribui os dados ao n�
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->dado = dado;
    novo->dir = NULL;
    novo->esq = NULL;

    if(raiz == NULL) //se a raiz estiver vazia, coloca esse novo n� na raiz
        raiz = novo;
    else{
        struct NO* atual = raiz;
        struct NO* ant = NULL;

        while (atual != NULL){
            ant = atual;
            if(dado == atual->dado){ //se o dado j� existir no n� atual, ele libera o novo n� e sai da fun��o
                free(novo);
                return 0;
            }
            if(dado > atual->dado) //se o dado for maior que o dado que est� sendo verificado, ele coloca o dado que est� sendo comparado como filho direito do dado novo
                atual = atual->dir;
            else // se for menor, vai ser o filho esquerdo
                atual = atual->esq;
        }

        if(dado > ant->dado) //se o dado for maior que o dado anterior, o novo n� vai ser filho direito do n� anterior
            ant->dir = novo;
        else // do contr�rio, vai ser filho esquerdo
            ant->esq = novo;

    }

    return 1;
}
struct NO* remove_atual(struct NO* atual){
    struct NO *no1, *no2;
    if(atual->esq == NULL){ //se o n� da esquerda for nulo, ent�o o n� auxiliar2 vai receber o filho direito do n� atual e o n� atual � liberado
        no2 = atual->dir;
        free(atual);
        return no2;
    }

    no1 = atual;
    no2 = atual;
    while(no2->dir != NULL){ //verifica se o n� auxiliar2 � diferente de nulo e atribui o valor do auxilir2 ao auxiliar1 e o auxiliar2 recebe o filho direito dele mesmo
        no1 = no2;
        no2=no2->dir;
    }

    if(no1 != atual){ //se o n� auxiliar1 for difernte do n� atual, o filho direito do n� auxiliar1 recebe o filho esquerdo do n� auxiliar2 e o filho esquerdo do n� auxiliar2 recebe o filho esquerdo do n� atual
        no1->dir = no2->esq;
        no2->esq = atual->esq;

    }
    no2->dir = atual->dir; //filho direito de n� auxiliar2 recebe o filho direito do n� atual e o n� atual � liberado
    free(atual);

    return no2;

}

int remove_ArBinaria(ArBinaria *raiz, int dado){ //fun��o que remove a �rvore toda
    if(raiz == NULL)
        return 0;
    struct NO* ant = NULL;
    struct NO* atual = raiz;

    while(atual != NULL){ //enquanto o n� atual for diferente de nulo ele realizar� as a��es abaixo
        if(dado == atual->dado){ //se o dado do paramentro for igual ao do n� atual
            if(atual == raiz) //verifica-se se o n� atual � igual a raiz, se verdadeiro, remove o n� atual e atribui o n� resultante a raiz
                raiz = remove_atual(atual);
            else{//caso falso,
                if(ant->dir == atual)//verifica-se se o filho direito do n� anterior � igual ao atual, se verdadeiro, remove o atual e atribui o n� resultante ao filho direito do n� anterior
                    ant->dir = remove_atual(atual);
                else//verifica-se se o filho direito do n� anterior � diferente do n� atual, se verdadeiro, remove o atual e atribui o n� resultante ao filho esquerdo do n� anterior
                    ant->esq = remove_atual(atual);

            }
            return 1;

        }
        ant = atual;
        if(dado > atual->dado) //se o dado for maior que o dado atual, atribui o filho direito do n� atual
            atual = atual->dir;
        else //se o dado for menor que o dado atual, atribui o filho esquerdo do n� atual ao n� atual
            atual = atual->esq;
    }
    return 0;


}

int insere_Rec(ArBinaria *raiz, int dado){
    if(raiz == NULL){ //se a raiz for nula, cria-se um novo n�, atribui os dados a ele e coloca ele como raiz
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
    else{//se a raiz n�o for nula,
        if(dado < raiz->dado) //verifica-se se o dado � menor que a raiz e chama a fun��o recursivamente passando o filho esquerdo da raiz como paramentro
            return insere_Rec(raiz->esq, dado);
        else{//caso a condi��o acima for falsa
            if(dado > raiz->dado)//verifica se o dado � maior que o dado da raiz e chama a fun��o recursivamente passando o filho direito da raiz como parametro
                return insere_Rec(raiz->dir, dado);
            else //caso o dado for igual ao dado da raiz, n�o faz nada
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
        else //quando o dado � encontrado
            return 1;

}

struct NO* consultaNO(ArBinaria *raiz, int dado){ //faz as mesmas coisas que a consulta acima, por�m quando o dado � encontrado, o n� do dado � retornado
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
    if(raiz->dir != NULL) //vai chamar a fun��o recursivamente at� encontrar um n� nulo
        return ED(raiz->dir);
    else{ //quando o filho direito da raiz for nulo, atribui o valor da raiz ao n� auxiliar
        struct NO *aux = raiz;
        if(raiz->esq !=NULL) //se o filho esquerdo da raiz for diferente de nulo, atribui o filho esquerdo da raiz a raiz
            raiz = raiz->esq;
        else{ //caso o filho esquerdo da raiz for nulo, a raiz � nula e retorna o valor do n� auxiliar
            raiz = NULL;
            return aux;
        }
    }

}

struct NO* DE(ArBinaria *raiz){ //mesma coisa que a fun��o acima s� que com invers�o de lados
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
    if(dado < raiz->dado) //se o dado for menor que o dado da raiz, chama a fun��o recursivamente utilizando o filho esquerdo da raiz como parametro
        remover_rec(raiz->esq,dado);
    if(dado > raiz->dado) //se o dado for maior que o dado da raiz, chama a fun��o recursivemente utilizando o filho direito da raiz como parametro
        remover_rec(raiz->dir,dado);
    else{ //se o dado for igual a raiz
        struct NO *ptAux = raiz;
        if((raiz->esq == NULL) && (raiz->dir == NULL) ){//verifica se os filhos da raiz s�o nulos, se forem nulos, atribui a raiz como nula
            free(ptAux);
            raiz = NULL;
            return 1;
        }
        else{//se os filhos da raiz n�o forem nulos

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
                else{ //se o filho da direita n�o for nulo, chama a fun��o ED passando o filho esquerdo da raiz como parametro, atribui os filhos da raiz ao n� auxilir, depois atribui o n� auxiliar a raiz
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

void preOrdem(ArBinaria *raiz){ //l� a arvore em pr�-ordem
    if(raiz = NULL)
        return;
    if(raiz != NULL){
        printf("%d\n",raiz->dado);
        preOrdem(raiz->esq);
        preOrdem(raiz->dir);
    }
}
int vazia_ArBinaria(ArBinaria *raiz){ //verifica se a �rvore est� vazia
    if(raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArBinaria(ArBinaria *raiz){ //retorna o n�mero de n�s da �rvore
    if(raiz == NULL)
        return 1;
    int alt_esq = totalNO_ArBinaria(raiz->esq);
    int alt_dir = totalNO_ArBinaria(raiz->dir);
    return (alt_esq + alt_dir + 1);
}

int altura_ArBinaria(ArBinaria *raiz) //calcula a altura da �rvore
{ //vai contando cada n�vel da �rvore at� chegar ao �ltimo, verifica qual n�vel de cada lado que � maior e retorna o maior
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
// implementa��o

int CalculaFB(ArBinaria* raiz) //calcula o fator de balanceamento daquele n�
{
    if( !raiz )
        return 0;

    return altura_ArBinaria(raiz->esq) - altura_ArBinaria(raiz->dir);
}

int SetaFB(ArBinaria *raiz) //atribui o fator de balanceamenta ao n�
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

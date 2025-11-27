#include <stdio.h>
#include <stdlib.h>
#include "listaLigada.h"
#include <string.h>

struct no{
    CLIENTE dados;
    struct no *prox;
};


Lista *criarLista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}


void liberaLista(Lista *li){
    if(li != NULL){
        struct no *ptrNo;
        while(*li!= NULL){
            ptrNo = *li;
            *li = (*li)->prox;
            free(ptrNo);
        }
        free(li);
    }
}


void inserirCliente(Lista *li, CLIENTE cli){
    system("cls");

    struct no *ant, *atual = *li;

    if(li == NULL){
        printf("Verifique a criacao da lista!");
        return;
    }

    struct no *noNovoCliente = (struct no*) malloc(sizeof(struct no));

    if(noNovoCliente == NULL){
        printf("Erro ao alocar memoria");
        return;
    }

    noNovoCliente->dados = cli;

    //LISTA VAZIA
    if(*li == NULL){
        noNovoCliente->prox = *li;
        *li = noNovoCliente;
        return;
    }

    while(atual != NULL && atual->dados.cod < cli.cod){
        ant = atual;
        atual = atual->prox;
    }

    if(*li == atual){
        noNovoCliente->prox = *li;
        *li = noNovoCliente;
        return;
    }

    if(atual == NULL){
        ant->prox = noNovoCliente;
        noNovoCliente->prox = NULL;
        return;
    }

    noNovoCliente->prox = ant->prox;
    ant->prox = noNovoCliente;
}

int buscaDados(Lista *li, int codigo){
    struct no *ant, *atual = *li;

    while(atual != NULL && atual->dados.cod < codigo){
        ant = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->dados.cod == codigo){
        return 1;
    } else {
        return 0;
    }
}


int capturaCodigoColeta(Lista *li){
    system("cls");

    int codigo;

    printf("Codigo: ");
    scanf("%d", &codigo);
    while(getchar() != '\n');

    while(buscaDados(li, codigo)){
        system("cls");
        printf("Codigo ja existe!\n");
        printf("Digite outro codigo: ");
        scanf("%d", &codigo);
        while(getchar() != '\n');
    }

    return codigo;

}

CLIENTE coletaDados(int cod){
    CLIENTE novoCliente;

    novoCliente.cod = cod;

    printf("Nome: ");
    fgets(novoCliente.nome, 80, stdin);

    printf("Empresa: ");
    fgets(novoCliente.empresa, 80, stdin);

    printf("Departamento: ");
    fgets(novoCliente.departamento, 30, stdin);

    printf("Telefone: ");
    fgets(novoCliente.telefone, 14, stdin);

    printf("Celular: ");
    fgets(novoCliente.celular, 15, stdin);

    printf("Email: ");
    fgets(novoCliente.email, 80, stdin);

    return novoCliente;
}


void imprimirTodosClientes(Lista *li){
    system("cls");
    if(li != NULL){
        struct no *ptrNo = *li;

        if(ptrNo == NULL){
            printf("A lista esta vazia!\n\n");
        }

        while(ptrNo != NULL){
            imprimirRegistro(ptrNo);
            ptrNo = ptrNo->prox;
        }
    }
}


void salvarLista(Lista *li, FILE *arq){
    Lista ptrNo = *li;
    while(ptrNo != NULL){
        fwrite(&(ptrNo->dados), sizeof(CLIENTE), 1, arq);
        ptrNo = ptrNo->prox;
    }
}


void recuperarDados(Lista *li, FILE *arq){
    CLIENTE registroTemp;

    int itemLido = fread(&registroTemp, sizeof(CLIENTE), 1, arq);

    while(itemLido){
        inserirCliente(li, registroTemp);
        itemLido = fread(&registroTemp, sizeof(CLIENTE), 1, arq);
    }
}


void buscarClienteCodigo(Lista *li){
    system("cls");

    int codigo;

    printf("Buscar codigo: ");
    scanf("%d", &codigo);

    Lista ant, atual = *li;

    if(li != NULL){
        while(atual != NULL && atual->dados.cod < codigo){
            ant = atual;
            atual = atual->prox;
        }
        if(atual != NULL && atual->dados.cod == codigo){
            imprimirRegistro(atual);
        } else {
            printf("\nCliente nao encontrado!\n\n");
        }
    }
}

void imprimirRegistro(Lista ptrNo){

    Lista ptrTemp = ptrNo;

    printf("--------------------------------------------------\n\n");
    printf("Codigo: %d\n\n",ptrTemp->dados.cod);
    printf("Nome: %s",ptrTemp->dados.nome);
    printf("Empresa: %s",ptrTemp->dados.empresa);
    printf("Departamento: %s",ptrTemp->dados.departamento);
    printf("Telefone: %s",ptrTemp->dados.telefone);
    printf("Celular: %s",ptrTemp->dados.celular);
    printf("Email: %s\n",ptrTemp->dados.email);
    printf("--------------------------------------------------\n");

}


void buscarClienteNome(Lista *li){
    system("cls");

    char nome[80];

    printf("Nome: ");
    fgets(nome, sizeof(nome), stdin);

    if(li == NULL){
        printf("Lista não encontrada!");
        return;
    }

    Lista atual = *li;

    int flag = 0;

    while(atual != NULL){

        char nomeRegistro[50];

        strcpy(nomeRegistro, atual->dados.nome);
        strcpy(nomeRegistro, strupr(nomeRegistro));

        char nomeConsulta[50];
        strcpy(nomeConsulta, strupr(nome));

        if(strcmp(nomeRegistro, nomeConsulta) == 0){
            imprimirRegistro(atual);
            flag = 1;
        }

        atual = atual->prox;
    }

    if(flag != 1){
        printf("\nNenhum cliente encontrado!\n\n");
    }

}

void removerClienteCodigo(Lista *li){
    system("cls");

    int codigo;

    printf("Digite o codigo:");
    scanf("%d", &codigo);

    if(li == NULL){
        printf("A lista não existe!");
        return;
    }

    Lista ant, atual = *li;

    while(atual != NULL && atual->dados.cod != codigo){
        ant = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->dados.cod == codigo){
        if(atual == *li){
            *li = atual->prox;
        } else {
            ant->prox = atual->prox;
        }
        printf("\nCliente excluido!\n\n");
        free(atual);
    } else {
        printf("\nCliente nao encontrado!\n\n");
    }
}

buscaNo(Lista *li, int codigo){
    struct no *ant, *atual = *li;

    while(atual != NULL && atual->dados.cod < codigo){
        ant = atual;
        atual = atual->prox;
    }

    if(atual != NULL && atual->dados.cod == codigo){
        return atual;
    }
}

void editarDados(Lista *li){

    system("cls");

    int codigo;
    CLIENTE cli;
    Lista ptrNo;

    printf("Codigo: ");
    scanf("%d", &codigo);
    while(getchar() != '\n');

    while(!buscaDados(li, codigo)){
        printf("Codigo nao cadastrado, digite outro: ");
        scanf("%d", &codigo);
        while(getchar() != '\n');
    }

    ptrNo = buscaNo(li, codigo);

    system("cls");
    imprimirRegistro(ptrNo);

    printf("\n");

    cli = coletaDados(codigo);

    ptrNo->dados = cli;

    printf("\n\nCliente atualizado com sucesso!\n\n\n");


}


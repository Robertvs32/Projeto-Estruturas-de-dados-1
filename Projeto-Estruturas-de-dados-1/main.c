#include <stdio.h>
#include <stdlib.h>
#include "listaLigada.h"

int main()
{
    Lista *li = criarLista();
    CLIENTE cli, cli2;
    int codInserir;

    FILE *arqLeitura = fopen("clientes.txt", "rb");
    recuperarDados(li, arqLeitura);
    fclose(arqLeitura);

    int escolha = 1;

    while(escolha != 7){
        system("cls");
        printf("ACME S.A - BANCO DE CLIENTES\n\n");

        printf("1 - Inserir novo cliente\n");
        printf("2 - Relatorio completo de clientes\n");
        printf("3 - Buscar cliente por codigo\n");
        printf("4 - Buscar cliente(s) por nome\n");
        printf("5 - Editar dados de cliente\n");
        printf("6 - Remove cliente\n");
        printf("7 - Salvar e sair\n\n");

        scanf("%d", &escolha);
        getchar();

        switch(escolha){
        case 1:
            codInserir = capturaCodigoColeta(li);
            system("cls");
            cli = coletaDados(codInserir);
            inserirCliente(li, cli);
            break;
        case 2:
            imprimirTodosClientes(li);
            system("pause");
            break;
        case 3:
            buscarClienteCodigo(li);
            system("pause");
            break;
        case 4:
            buscarClienteNome(li);
            system("pause");
            break;
        case 5:
            editarDados(li);
            system("pause");
            break;
        case 6:
            removerClienteCodigo(li);
            system("pause");
            break;
            }
        }

    system("cls");
    FILE *arqEscrita = fopen("clientes.txt", "wb");
    salvarLista(li, arqEscrita);
    fclose(arqEscrita);

    liberaLista(li);
    printf("Programa finalizado!\n");

    return 0;
}

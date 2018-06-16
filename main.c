#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <locale.h>
struct campo{
    double valor;
    int linha;
    int coluna;
    struct campo *ant;
};
struct matriz{
        int it;
        int jt;
        struct campo *p;
    };
#include "funcoes.h"
int main()
{
printf("\t\t\t##     ##    ###   ######## ########  #### ########   \n");
printf("\t\t\t###   ###   ## ##     ##    ##     ##  ##       ##    \n");
printf("\t\t\t#### ####  ##   ##    ##    ##     ##  ##      ##     \n");
printf("\t\t\t## ### ## ##     ##   ##    ########   ##     ##      \n");
printf("\t\t\t##     ## #########   ##    ##   ##    ##    ##       \n");
printf("\t\t\t##     ## ##     ##   ##    ##    ##   ##   ##        \n");
printf("\t\t\t##     ## ##     ##   ##    ##     ## #### ########   \n \n");
printf("\t\t\t########  ######  ########     ###    ########   ######     ###    \n");
printf("\t\t\t##       ##    ## ##     ##   ## ##   ##     ## ##    ##   ## ##   \n");
printf("\t\t\t##       ##       ##     ##  ##   ##  ##     ## ##        ##   ##  \n");
printf("\t\t\t######    ######  ########  ##     ## ########   ######  ##     ## \n");
printf("\t\t\t##             ## ##        ######### ##   ##         ## ######### \n");
printf("\t\t\t##       ##    ## ##        ##     ## ##    ##  ##    ## ##     ## \n");
printf("\t\t\t########  ######  ##        ##     ## ##     ##  ######  ##     ## \n \n \n");
system("pause");
    do{
    struct matriz *matriz = malloc(sizeof(struct matriz));
    if(matriz == NULL){
        printf("Erro de alocacao dinâmica.");
        exit(1);
    }
    matriz->p = NULL;
    setlocale(LC_ALL,"Portuguese");
    int correto =1;
    do{
        setbuf(stdin, NULL);
        system("cls");
        printf("Digite a quantidade de linhas da matriz \n");
        scanf("%d", &matriz->it);
        if(matriz->it<=0){
            printf("Entrada inválida. Digite novamente. \n");
            Sleep(700);
        }else{
            setbuf(stdin, NULL);
            printf("Digite a quantidade de colunas da matriz \n");
            scanf("%d", &matriz->jt);
            if(matriz->jt<=0){
                printf("Entrada inválida. Digite novamente. \n");
                Sleep(700);
            }else
                correto=0;
        }
    }while(correto);
    matriz->it-=1;
    matriz->jt-=1;
    menu(matriz);
    }while(1);
    return 0;
}
void menu(struct matriz *matriz){
    int sair_menu = 1;
    double det;
    do{
        setbuf(stdin, NULL);
        system("cls");
        printf("1 -- Inserir valor\n");
        printf("2 -- Calcular soma de uma linha\n");
        printf("3 -- Calcular soma de uma coluna\n");
        printf("4 -- Consultar campo\n");
        printf("5 -- Calcular Determinante e encerrar\n");
        printf("6 -- Excluir matriz\n");
        int opcao;
        scanf("%d",&opcao);
        setbuf(stdin, NULL);
        switch(opcao){
            case 1:
                inserir(matriz);
                break;
            case 2:
                somar_linha(matriz);
                break;
            case 3:
                somar_coluna(matriz);
                break;
            case 4:
                consultar(matriz);
                break;
            case 5:
                if(matriz->it == matriz->jt){
                    det = calcula_determinante(matriz);
                    printf("O valor do determinante é: %.3lf \n",det);
                    sair_menu = 0;
                }else
                    printf("A matriz não é quadrada, impossível calcular determinante \n");
                break;
            case 6:
                excluir_matriz(matriz);
                sair_menu = 0;
                break;
            default:
                printf("\n Digite uma entrada correta. \n");
                Sleep(700);
                break;
        }
        system("pause");
    }while(sair_menu);
}
double consulta(int i, int j, struct matriz *matriz){
    int a =1;
    struct campo *busca = matriz->p;
    if(matriz->p!=NULL){
        while(a){
            if(busca->linha==i&&busca->coluna==j){
                return busca->valor;
            }else{
                if(busca->ant == NULL){
                    a = 0;
                }else{
                    busca = busca->ant;
                }
            }
        }
    }
    return 0;
}
void consultar(struct matriz *matriz){
    int correto = 1;
    do{
        setbuf(stdin, NULL);
        system("cls");
        int i,j;
        double valor;
        printf("Digite a linha do elemento :\n");
        scanf("%d", &i);
        setbuf(stdin, NULL);
        if(!(i>=0&&i<=matriz->it)){
            printf("Valor incorreto. Digite novamente");
            Sleep(700);
        }else{
            printf("Digite a coluna do elemento:\n");
            scanf("%d", &j);
            setbuf(stdin, NULL);
            if(!(j>=0&&j<=matriz->jt)){
                printf("Valor incorreto. Digite novamente");
                Sleep(700);
            }else{
                valor = consulta(i,j, matriz);
                printf("O valor do campo %dx%d é : %.3lf \n",i,j,valor);
                 correto = 0;
            }
        }
    }while(correto);
}
void insere_campo(double valor, int linha, int coluna, struct matriz *matriz){
        if(valor !=0){
            struct campo *p_novo = malloc(sizeof(struct campo));
            if(p_novo == NULL){
                printf("ERRO DE ALOCACAO!");
                exit(1);
            }
            p_novo->valor = valor;
            p_novo->linha = linha;
            p_novo->coluna = coluna;
            p_novo->ant = matriz->p;
            matriz->p = p_novo;
        }
}
void inserir(struct matriz *matriz){
    int correto = 1;
    int escolha;
    do{
        setbuf(stdin, NULL);
        system("cls");
        int linha,coluna;
        double valor;
        printf("Digite o valor:\n");
        scanf("%lf", &valor);
        setbuf(stdin, NULL);
        printf("Digite a linha:\n");
        scanf("%d", &linha);
        setbuf(stdin, NULL);
        if(!(linha>=0&&linha<=matriz->it)){
            printf("Valor incorreto. Digite novamente.");
            Sleep(700);
        }else{
            printf("Digite a coluna:\n");
            scanf("%d", &coluna);
            if(!(coluna>=0&&coluna<=matriz->jt)){
                printf("Valor incorreto. Digite novamente.");
                Sleep(700);
            }else{
                if(consulta(linha,coluna,matriz)){
                    printf("Campo já cadastrado, deseja sobrescrever? \n");
                    printf("1              - SIM \n");
                    printf("QUALQUER VALOR - NAO \n");
                    scanf("%d", &escolha);
                    if(escolha == 1)
                        muda_valor(linha,coluna,valor,matriz);
                    Sleep(700);
                }else{
                    insere_campo(valor, linha, coluna, matriz);
                    printf("Cadastrado com sucesso! \n");
                }
                correto = 0;
            }
        }
    }while(correto);
}
void somar_linha(struct matriz *matriz){
    int correto = 1;
    do{
        setbuf(stdin, NULL);
        system("cls");
        printf("Digite a linha:");
        int linha;
        scanf("%d", &linha);
        if(!(linha>=0&&linha<=matriz->it)){
            printf("\n valor inválido. Digite novamente. \n");
            Sleep(700);
        }else{
            double soma = soma_linha(linha, matriz);
            printf("\n soma da linha: %.3lf \n",soma);
            correto = 0;
        }
    }while(correto);
}
void somar_coluna(struct matriz *matriz){
    int correto = 1;
    do{
        setbuf(stdin, NULL);
        system("cls");
        printf("Digite a coluna: \n");
        int coluna;
        scanf("%d", &coluna);
        if(!(coluna>=0&&coluna<=matriz->jt)){
            printf("\n valor inválido. Digite novamente. \n");
            Sleep(700);
        }else{
            double soma = soma_coluna(coluna, matriz);
            printf("\n soma da coluna: %.3lf \n",soma);
            correto = 0;
        }
    }while(correto);
}
double soma_linha(int linha,struct matriz *matriz){
    double soma = 0;
    struct campo *campo = matriz->p;
    int a=1;
    if(matriz->p!=NULL){
        while(a){
            if(campo->linha == linha){
                soma+= campo->valor;
            }
            if(campo->ant == NULL){
                a = 0;
            }else{
                campo = campo->ant;
            }
        }
    }
    return soma;
}
double soma_coluna(int coluna, struct matriz *matriz){
    double soma = 0;
    struct campo *campo = matriz->p;
    int a = 1;
    if(matriz->p!=NULL){
        while(a){
            if(campo->coluna == coluna){
                soma+= campo->valor;
            }
            if(campo->ant == NULL){
                a = 0;
            }else{
                campo = campo->ant;
            }
        }
    }
    return soma;
}
void excluir_matriz(struct matriz *matriz){
    struct campo *temp;
    if(matriz->p!=NULL){
        while(matriz->p->ant!=NULL){
            temp = matriz->p->ant;
            free(matriz->p);
            matriz->p = temp;
        }
    }
    free(matriz);
    printf("Matriz excluída com sucesso! \n \n");
    Sleep(700);
}
double calcula_determinante(struct matriz *matriz){
    int tamanho = matriz->it+1;
    double fator;
    int inverte_sinal=0;
    for(int i = 0; i <tamanho-1;i++){
        if(consulta(i,i,matriz) == 0){
            for(int d = i;d<tamanho;d++){
                if(consulta(d,i,matriz) !=0){
                    troca_linha(d,i,matriz);
                    d = tamanho;
                }
                inverte_sinal+=1;
            }
        }
        if(consulta(i,i,matriz)!=0){
            for(int k = i+1; k<tamanho;k++){
                fator =(double)(-1.0*consulta(k,i,matriz))/(consulta(i,i,matriz));
                for(int j = i;j<tamanho;j++){
                    muda_valor(k,j,consulta(k,j,matriz)+fator*consulta(i,j,matriz),matriz);
                }
            }
        }
    }
    double resultado = 1;
    for(int i = 0; i<tamanho;i++){
        resultado*=consulta(i,i,matriz);
    }
    if(inverte_sinal%2==1){
        return -1*resultado;
    }else{
        return resultado;
    }
}
void troca_linha(int i1, int i2, struct matriz *matriz){
    double temp;
    if(matriz->p!=NULL){
        for(int j = 0;j<=matriz->it;j++){
            temp = consulta(i1,j,matriz);
            muda_valor(i1,j,consulta(i2,j,matriz),matriz);
            muda_valor(i2,j,temp,matriz);
        }
        }
}
void muda_valor(int i, int j, double valor, struct matriz *matriz){
    int a =1;
    struct campo *busca = matriz->p;
    if(matriz->p!=NULL){
        while(a){
            if(busca->linha==i&&busca->coluna==j){
                busca->valor=valor;
                a=0;
            }else{
                if(busca->ant == NULL){
                    insere_campo(valor,i,j,matriz);
                    a =0;
                }else{
                    busca = busca->ant;
                }
            }
        }
    }else{
        insere_campo(valor,i,j,matriz);
    }
}

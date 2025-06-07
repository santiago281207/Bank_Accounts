#define CRT_SECURE_NO_WARNINGS
#define MAX 500
#define NAME 20
#define PASS_LENGHT 30

#include <stdio.h>
#include <stdlib.h>
#include <search.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

struct ContaBancaria {
    char nome[20];
    char pass[30];
    char contacto[9];
    double saldo;
};

void Menu(int contas_criadas);    //Funcao de menu
int EntreAB(int n, int min, int max);     //Verificar um intervalo de numeros inteiros ou chars
int Password_Strength(char* password);  //Verificar forca da password 1-forte 0-fraca
int NameCheck(struct ContaBancaria contas[], char name[], int size);    //Verificar se o nome e valido ou se ja esta  atribuido
int ContactoVerif(char contacto[]);      //Contacto e valido?
int IsInString(char string[], char value);      //Verifica se um caracter esta numa string
int ComparaContas(const void* a, const void* b);

int main()
{
    struct ContaBancaria Contas[MAX];   //Array de structs dinamico
    int qtd_contas = 0, contas_criadas = 0;
    char tarefa_menu = ' ';   //Escolha do menu
    char tarefa_criador;    //Criar contas uma a uma ou criar varias de uma so vez?
    system("color B");      //Mudar a cor para azul clarinho

    while (1)    //Ciclo que roda o banco
    {
        Menu(contas_criadas);

        do
        {
            scanf_s("%c", &tarefa_menu,1);
            getchar();
            if (EntreAB(tarefa_menu, '1', '7') == 0)
            {
                puts("Indique uma opcao valida!");
            }
        } while (EntreAB(tarefa_menu, '1', '7') == 0);

        if (tarefa_menu == '7')  //Verificar se tarefa escolhida e sair
        {
            printf("Saindo...\n");
            break;
        }

        switch (tarefa_menu)    //Encontrar qual tarefa escolheu 
        {
        case '1':       //Adicionar novas contas
            if (contas_criadas >= MAX)
            {
                puts("Numero de maximo de contas atingido!");
                break;
            }
            puts("  === CRIADOR DE CONTAS BANANARIAS ===  ");
            puts("1. Criador de contas em serie");  //Indicar quantidade de contas
            puts("2. Criador de conta singular (recomendado)");  //Criar apenas uma conta
            puts("3. Sair");


            do
            {
                scanf_s("%c", &tarefa_criador,1);
                getchar();

                if (EntreAB(tarefa_criador, '1', '3') == 0)
                {
                    printf("Selecione uma opcao valida.");
                }
            } while (EntreAB(tarefa_criador, '1', '3') == 0);
            if (tarefa_criador == '3')
            {
                printf("Saindo...\n");
                break;
            }


            switch (tarefa_criador)
            {
            case '1':   //Criador em serie
                printf(" === CRIADOR DE CONTAS EM SERIE === \n");
                do
                {
                    printf("Indique a quantidade de contas que pretende criar: ");
                    scanf_s("%d", &qtd_contas);    //Quantidade de contas
                    getchar();
                    if (EntreAB(qtd_contas, 1, MAX) == 0)
                    {
                        printf("Os nossos servidores so suportam ate %d contas.\n", MAX);
                    }
                } while (EntreAB(qtd_contas, 1, MAX) == 0);


                for (;contas_criadas < qtd_contas;) //Criar contas ate a quantidade de contas pretendida
                {
                    do
                    {
                        printf("Indique o nome do proprietario desta conta: ");
                        fgets(Contas[contas_criadas].nome, NAME, stdin);    //Ler nome da conta
                        Contas[contas_criadas].nome[strcspn(Contas[contas_criadas].nome, "\n")] = '\0';     //Retirar o "\n" da string do nome
                        
                        if (NameCheck(Contas, Contas[contas_criadas].nome, contas_criadas) == 0)    //Verficar se o nome e valido
                        {
                            printf("Nome invalido!\n");
                        }
                    } while (NameCheck(Contas, Contas[contas_criadas].nome, contas_criadas) == 0);    //Verificar se o nome e valido

                    do
                    {
                        printf("Indique a password para a conta (minimo 8 caracteres): ");
                        fgets(Contas[contas_criadas].pass, PASS_LENGHT, stdin);
                        Contas[contas_criadas].pass[strcspn(Contas[contas_criadas].pass, "\n")] = '\0';     //Retirar o "\n" da string

                        if (Password_Strength(Contas[contas_criadas].pass) != 1)
                        {
                            printf("Password muito fraca!\nTente novamente.\n");
                        }
                    } while (Password_Strength(Contas[contas_criadas].pass) != 1);

                    
                    do
                    {
                        printf("Indique o seu numero de contacto:+351");
                        scanf_s("%s", &Contas[contas_criadas].contacto, 10);  //Ler numero de telemovel
                        getchar();
                        if (ContactoVerif(Contas[contas_criadas].contacto) == 0)   //Verificar se numero e valido
                        {
                            printf("Numero invalido!\n");
                        }
                    } while (ContactoVerif(Contas[contas_criadas].contacto) == 0);  //Verificar se o numero de contacto e valido

                    printf("\nConta de %s criada com sucesso!\n", Contas[contas_criadas].nome);
                    contas_criadas++;
                }
                break;  //FIM DE CRIADOR DE CONTAS EM SERIE

            case '2':   //Criador singular
                do
                {
                    printf("Indique o nome do proprietario desta conta: ");
                    fgets(Contas[contas_criadas].nome, NAME, stdin);    //Ler nome da conta
                    Contas[contas_criadas].nome[strcspn(Contas[contas_criadas].nome, "\n")] = '\0';     //Retirar o "\n" da string
                 
                    if (NameCheck(Contas, Contas[contas_criadas].nome, contas_criadas) == 0)    //Verficar se o nome e valido
                    {
                        printf("Nome invalido!\n");
                    }
                } while (NameCheck(Contas, Contas[contas_criadas].nome, contas_criadas) == 0);    //Verificar se o nome e valido

                do
                {
                    printf("Indique a password para a conta (minimo 8 caracteres): ");
                    fgets(Contas[contas_criadas].pass, PASS_LENGHT, stdin);
                    Contas[contas_criadas].pass[strcspn(Contas[contas_criadas].pass, "\n")] = '\0';     //Retirar o "\n" da string

                    if (Password_Strength(Contas[contas_criadas].pass) != 1)
                    {
                        printf("Password muito fraca!\nTente novamente.\n");
                    }
                } while (Password_Strength(Contas[contas_criadas].pass) != 1);      //Verificar se a password passa nos requisitos pedidos

                do
                {
                    printf("Indique o seu numero de contacto:+351");
                    scanf_s("%s", &Contas[contas_criadas].contacto,10);  //Ler numero de telemovel
                    getchar();

                    if (ContactoVerif(Contas[contas_criadas].contacto) == 0)   //Verificar se numero e valido
                    {
                        printf("Numero invalido!\n");
                    }
                } while (ContactoVerif(Contas[contas_criadas].contacto) == 0);  //Verificar se o numero de contacto e valido

                printf("\nConta de %s criada com sucesso!\n", Contas[contas_criadas].nome);
                contas_criadas++;

                break;      //FIM DO CRIADOR SINGULAR
            }
            break;      

        case '2':       //Consultar saldo password necessaria
            break;      //FIM CONSULTAR SALDO

        case '3':       //Levantar dinheiro password necessaria
            break;      //FIM LEVANTAR DINHEIRO

        case '4':       //Depositar dinheiro password necessaria
            break;      //FIM DEPOSITAR DINHEIRO

        case '5':       //Transferencia de dinheiro password necessaria
            break;      //FIM TRANSFERENCIA DINHEIRO

        case '6':       /*Mudar pass precisa pass atual. se nao a souber perguntar o contacto de telemovel*/
            break;      //FIM ALTERAR PASSWORD
        }
        qsort(Contas,contas_criadas,sizeof(Contas[0].nome),ComparaContas);        //Ordenar os nomes das contas por ordem alfabetica
    }
    return 0;
}

void Menu(int contas_criadas)
{
    puts(" === BEM VINDO AO BANCO DAS BANANAS === ");
    puts("----------------------------------------");
    puts("|Selecione uma opcao das abaixo:       |");
    printf("|1. Adicionar contas bananarias(%d/%d) |\n",contas_criadas,MAX);   //1 Adicionar conta
    puts("|2. Consultar bananas                  |");   //2 Consultar saldo
    puts("|3. Levantar bananas                   |");   //3 Levantar dinheiro
    puts("|4. Depositar bananas                  |");   //4 Depositar dinheiro
    puts("|5. Transferencia bananaria            |");   //5 Transferencia de dinheiro
    puts("|6. Alterar password                   |");   //6 Sair
    puts("|7. Sair                               |");   //6 Sair
    puts("----------------------------------------");
}

int EntreAB(int n, int min, int max)
{
    return n >= min && n <= max;
}

int Password_Strength(char* password)
{
    /*Esta funcao ira avaliar a forca de uma palavra passe e se a password e valida.
    CRITERIOS:
                Minimo 8 caracteres
                Letra maiscula
                Letra minuscula
                Numeros
                Caracteres especiais
                Sem espacos
                Sem repeticoes faceis
                sem passwords comuns*/
    int i = 0;
    int letras_upper_count = 0, letras_lower_count = 0, special_count = 0, numbers_count = 0, total = 0;   //Contadores de caracteres
    int tamanho_check = 0;
    char letras_lower[] = { "abcdefghijklmnopqrstuvwxyz" };
    char letras_upper[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    char special[] = { "@!$_-#" };
    char numbers[] = { "0123456789" };
    size_t tamanho = strlen(password);

    if (tamanho < 8)
    {
        return 0;
    }
    else
    {
        for (i = 0;i < tamanho;i++)
        {
            if (IsInString(letras_lower, password[i]) == 1) //Verificar se o caracter atual e minuscula
                letras_lower_count = 1;
            else if (IsInString(letras_upper, password[i]) == 1)   //Verificar se o caracter atual e maiscula
                letras_upper_count = 1;
            else if (IsInString(special, password[i]) == 1)     //Verificar se o caracter atual e especial
                special_count = 1;
            else if (IsInString(numbers, password[i]) == 1)     //Verificar se o caracter atual e um numero
                numbers_count = 1;
        }
        tamanho_check = 1;
        total = numbers_count + special_count + letras_upper_count + letras_lower_count + tamanho_check;       //Calcular a quantas regras obedece
    }
    if (total != 5)     //Se nao obedecer a todas as regras
    {
        return 0;
    }
    return 1;
}

int NameCheck(struct ContaBancaria contas[], char name[], int size)
{
    //Funcao verifica se o nome ja esta sendo usado por outro utilizador

    int i = 0;

    for (i = 0;i < size;i++)
    {
        if (_stricmp(contas[i].nome, name) == 0)    //Verificar se o nome introduzido ja existe na base de dados case-insensitive
        {
            return 0;
        }
    }
    return 1;
}

int ContactoVerif(char contacto[])
{
    int i = 0;
    char nums[] = { "0123456789" };
    for (i = 0;contacto[i] != '\0';i++)
    {
        if (IsInString(nums, contacto[i]) == 0)
        {
            return 0;
        }
    }
    
    return i == 9;
}

int IsInString(char string[], char value)
{
    size_t i = 0;

    for (i = 0;string[i] != '\0';i++)
    {
        if (string[i] == value)
        {
            return 1;
        }
    }
    return 0;
}

int ComparaContas(const void* a, const void* b)
{
    // Converter os ponteiros void* para ponteiros do tipo struct ContaBancaria*
    const struct ContaBancaria* contaA = (const struct ContaBancaria*)a;
    const struct ContaBancaria* contaB = (const struct ContaBancaria*)b;

    // Usar strcmp() para comparar os nomes das contas
    // strcmp() devolve:
    //   <0 se contaA->nome vem antes de contaB->nome
    //   0 se são iguais
    //   >0 se contaA->nome vem depois de contaB->nome
    return strcmp(contaA->nome, contaB->nome);
}
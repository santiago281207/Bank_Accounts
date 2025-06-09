#define _CRT_SECURE_NO_WARNINGS
#define MAX 500
#define NAME 20
#define PASS_LENGHT 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>

struct ContaBancaria {
	char nome[20];
	char pass[30];
	char contacto[9];
	double saldo;
};

void ResetSaldos(struct ContaBancaria contas[], int size);		//Colocar os saldos todos a 0
void RemoveInvalid(char word[]);
void Menu(int contas_criadas);    //Funcao de menu
int EntreAB(int n, int min, int max);     //Verificar um intervalo de numeros inteiros ou chars
int Password_Strength(char* password);  //Verificar forca da password 1-forte 0-fraca
int NameCheck(struct ContaBancaria contas[], char name[], int size);    //Verificar se o nome e valido ou se ja esta  atribuido
int ContactoVerif(char contacto[]);      //Contacto e valido?
int ContactoConfirm(struct ContaBancaria contas[], char number[], int conta);
int IsInString(char string[], char value);      //Verifica se um carac,ter esta numa string
int ContaFinder(struct ContaBancaria contas[], char name[], int size);      //Encontra a conta com o nome que o user introduzir
int PasswordCheck(struct ContaBancaria contas[], char pass[], int conta);	//Verificar se password esta correta
int QtdEnviarValid(double saldo, double quantia_enviar);	//Verifica se a quantidade a enviar e valida

int main()
{
	struct ContaBancaria Contas[MAX];
	int contador_password_change = 0, contacto_check = 0;	//Contar quantas tentativas de mudar a password ja aconteceram
	int qtd_contas = 0, contas_criadas = 0;
	int pos_conta = 0;
	int qtd_enviar_check, pass_change_check;	//Mostra se a quantidade a enviar e valida
	double quantia_levantar, quantia_depositar;	//Quantias do deposito
	double quantia_enviar;
	int remetente, destinatario, passcheck;	//Quantia de envio e posicoes das contas e verificacao de password certa
	char nome_remetente[NAME], pass_remetente[PASS_LENGHT], nome_destinatario[NAME];
	char tarefa_menu = ' ';   //Escolha do menu
	char tarefa_criador;    //Criar contas uma a uma ou criar varias de uma so vez?
	char nome_conta_saldo[NAME], pass_conta_saldo[PASS_LENGHT];  //Nome da conta para verificar saldo e password
	char nome_conta_change[NAME], pass_conta_change[PASS_LENGHT], choice_maker = ' ', contacto_confirm[10];	//Nome da conta que vai mudar a password decidir mudar para confirmacao por contacto e se contacto esta certo
	system("color B");      //Mudar a cor para azul clarinho

	ResetSaldos(Contas, MAX);

	while (1)    //Ciclo que roda o banco
	{
		Menu(contas_criadas);

		do
		{
			scanf_s("%c", &tarefa_menu, 1);
			getchar();
			if (EntreAB(tarefa_menu, '1', '7') == 0)
			{
				puts("Indique uma opcao valida!");
			}
		} while (EntreAB(tarefa_menu, '1', '7') == 0);

		if (tarefa_menu == '7')  //Verificar se tarefa escolhida e sair
		{
			printf("Saindo...\n");
			Sleep(1000);
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
				scanf_s("%c", &tarefa_criador, 1);
				getchar();

				if (EntreAB(tarefa_criador, '1', '3') == 0)
				{
					printf("Selecione uma opcao valida.");
				}
			} while (EntreAB(tarefa_criador, '1', '3') == 0);
			if (tarefa_criador == '3')
			{
				printf("Saindo...\n");
				Sleep(1000);
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


				for (; contas_criadas < qtd_contas;) //Criar contas ate a quantidade de contas pretendida
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
						scanf_s("%s", Contas[contas_criadas].contacto, 10);  //Ler numero de telemovel
						getchar();
						if (ContactoVerif(Contas[contas_criadas].contacto) == 0)   //Verificar se numero e valido
						{
							printf("Numero invalido!\n");
						}
					} while (ContactoVerif(Contas[contas_criadas].contacto) == 0);  //Verificar se o numero de contacto e valido

					printf("Conta de %s criada com sucesso!\n\n", Contas[contas_criadas].nome);
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
					scanf_s("%s", &Contas[contas_criadas].contacto, 10);  //Ler numero de telemovel
					getchar();

					if (ContactoVerif(Contas[contas_criadas].contacto) == 0)   //Verificar se numero e valido
					{
						printf("Numero invalido!\n");
					}
				} while (ContactoVerif(Contas[contas_criadas].contacto) == 0);  //Verificar se o numero de contacto e valido

				printf("Conta de %s criada com sucesso!\n\n", Contas[contas_criadas].nome);
				contas_criadas++;

				break;      //FIM DO CRIADOR SINGULAR
			}
			break;

		case '2':       //Consultar saldo password necessaria
			printf(" === CONSULTADOR DE BANANAS === \n");
			do
			{
				printf("Digite quit para sair.\n");
				printf("Nome da conta: ");
				fgets(nome_conta_saldo, NAME, stdin);
				RemoveInvalid(nome_conta_saldo);

				if (_stricmp(nome_conta_saldo, "quit") == 0)
				{
					break;
				}
				else if (ContaFinder(Contas, nome_conta_saldo, contas_criadas) == -1)
				{
					printf("Conta nao existe. Tente outro nome\n");
				}
			} while (ContaFinder(Contas, nome_conta_saldo, contas_criadas) == -1);  //Repetir ate encontrar conta

			if (_stricmp(nome_conta_saldo, "quit") == 0)
			{
				printf("Saindo...\n");
				Sleep(1000);
				break;
			}

			pos_conta = ContaFinder(Contas, nome_conta_saldo, contas_criadas);

			do
			{
				printf("Digite a sua password: ");
				fgets(pass_conta_saldo, PASS_LENGHT, stdin);
				RemoveInvalid(pass_conta_saldo);		//Remover o \n no fim da string

				if (_stricmp(pass_conta_saldo, "quit") == 0)
				{
					break;
				}
				else if (PasswordCheck(Contas, pass_conta_saldo, pos_conta) == 0)		//Se a password estiver errada
				{
					printf("Password incorreta. Tente novamente.\n");
				}
			} while (PasswordCheck(Contas, pass_conta_saldo, pos_conta) == 0);		//Repetir ate estar certa

			if (_stricmp(pass_conta_saldo, "sair") == 0)
			{
				printf("Saindo...\n");
				Sleep(1000);
				break;
			}
			else
			{
				printf("As suas bananas: %.2lf\n\n", Contas[pos_conta].saldo);
			}
			break;      //FIM CONSULTAR SALDO

		case '3':       //Levantar dinheiro password necessaria
			printf(" === LEVANTAR BANANAS === \n");
			do
			{
				printf("\nDigite quit para sair.\n");
				printf("Nome da conta: ");
				fgets(nome_conta_saldo, NAME, stdin);
				RemoveInvalid(nome_conta_saldo);	//Remover o \n do fim da string

				if (_stricmp(nome_conta_saldo, "quit") == 0)
				{
					break;
				}
				else if (ContaFinder(Contas, nome_conta_saldo, contas_criadas) == -1)
				{
					printf("Conta nao existe. Tente outro nome\n");
				}
			} while (ContaFinder(Contas, nome_conta_saldo, contas_criadas) == -1);  //Repetir ate encontrar conta

			if (_stricmp(nome_conta_saldo, "quit") == 0)
			{
				printf("Saindo...\n");
				Sleep(1000);
				break;
			}

			pos_conta = ContaFinder(Contas, nome_conta_saldo, contas_criadas);

			do
			{
				printf("Digite a sua password: ");
				fgets(pass_conta_saldo, PASS_LENGHT, stdin);
				RemoveInvalid(pass_conta_saldo);		//Remover o \n no fim da string

				if (_stricmp(pass_conta_saldo, "sair") == 0)
				{
					break;
				}
				else if (PasswordCheck(Contas, pass_conta_saldo, pos_conta) == 0)		//Se a password estiver errada
				{
					printf("Password incorreta. Tente novamente.\n");
				}
			} while (PasswordCheck(Contas, pass_conta_saldo, pos_conta) == 0);		//Repetir ate estar certa

			if (_stricmp(pass_conta_saldo, "sair") == 0)	//Saindo da tarefa
			{
				printf("Saindo...\n");
				Sleep(1000);
				break;
			}

			if (Contas[pos_conta].saldo <= 0)	//Nao tem saldo para levantar
			{
				printf("Nao tem saldo suficiente para levantar qualquer quantia!\n");
				printf("Saindo...\n");
				Sleep(1000);
			}
			else
			{
				do
				{
					printf("Indique quanto quer levantar: $");
					scanf("%lf", &quantia_levantar);
					if (quantia_levantar <= 0)
					{
						printf("Quantia invalida!\n");
					}
					else if (quantia_levantar > Contas[pos_conta].saldo)
					{
						printf("Saldo insuficiente.\n");
					}
					else
					{
						Contas[pos_conta].saldo -= quantia_levantar;	//Reduzir saldo
						printf("%.2lf foi retirado da sua conta!\n", quantia_levantar);
						printf("Saldo atual: %.2lf\n\n", Contas[contas_criadas].saldo);	//Mostrar o saldo depois do levantamento
						Sleep(2000);
					}
				} while (quantia_levantar <= 0);	//Repetir ate ler um valor valido
			}
			break;      //FIM LEVANTAR DINHEIRO

		case '4':       //Depositar dinheiro password necessaria
			printf(" === DEPOSITAR BANANAS === \n");
			do
			{
				printf("Digite quit para sair.\n");
				printf("Nome da conta: ");
				fgets(nome_conta_saldo, NAME, stdin);
				RemoveInvalid(nome_conta_saldo);	//Remover \n

				if (_stricmp(nome_conta_saldo, "quit") == 0)	//Verificar se é para sair da tarefa
				{
					break;
				}
				else if (ContaFinder(Contas, nome_conta_saldo, contas_criadas) == -1)	//Verificar se conta existe
				{
					printf("Conta nao existe. Tente outro nome");
				}
			} while (ContaFinder(Contas, nome_conta_saldo, contas_criadas) == -1);  //Repetir ate encontrar conta

			if (_stricmp(nome_conta_saldo, "quit") == 0)	//Saindo
			{
				printf("Saindo...\n\n");
				Sleep(1000);
				break;
			}

			pos_conta = ContaFinder(Contas, nome_conta_saldo, contas_criadas);	//Encontrar a posicao da conta

			do
			{
				printf("Digite a sua password: ");
				fgets(pass_conta_saldo, PASS_LENGHT, stdin);
				RemoveInvalid(pass_conta_saldo);		//Remover o \n no fim da string

				if (_stricmp(pass_conta_saldo, "quit") == 0)	//Verificar se e para sair da tarefa
				{
					break;
				}
				else if (PasswordCheck(Contas, pass_conta_saldo, pos_conta) == 0)		//Se a password estiver errada
				{
					printf("Password incorreta. Tente novamente.\n");
				}
			} while (PasswordCheck(Contas, pass_conta_saldo, pos_conta) == 0);		//Repetir ate estar certa

			if (_stricmp(pass_conta_saldo, "sair") == 0)	//Saindo da tarefa
			{
				printf("Saindo...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Indique quanto quer depositar: $");
				scanf("%lf", &quantia_depositar);
				if (quantia_depositar <= 0)
				{
					printf("Quantia invalida!\n");
				}
				else
				{
					Contas[pos_conta].saldo += quantia_depositar;		//Adicionar o deposito ao saldo
					printf("%.2lf foi depositado da sua conta!\n", quantia_depositar);
					printf("Saldo atual: %.2lf\n\n", Contas[pos_conta].saldo);	//Mostrar saldo depois do deposito
					getchar();
					Sleep(1000);
				}
			} while (quantia_depositar < 0);

			break;      //FIM DEPOSITAR DINHEIRO

		case '5':       //Transferencia de dinheiro password necessaria
			printf(" === TRANSFERENCIA BANANARIA === \n");
			puts("Digitar quit para sair.");
			do
			{
				printf("Nome do remetente: ");
				fgets(nome_remetente, NAME, stdin);
				RemoveInvalid(nome_remetente);	//Remover "\n" do fim da string

				remetente = ContaFinder(Contas, nome_remetente, contas_criadas);
				if (_stricmp(nome_remetente, "quit") == 0)
				{
					break;
				}
				else if (remetente == -1)	//Encontrar conta
				{
					puts("Conta nao existe. Tente novamente.");
				}
			} while (remetente == -1);		//Repetir ate encontrar conta

			if (_stricmp(nome_remetente, "quit") == 0)	//Sair da tarefa
			{
				printf("Saindo...\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Password: ");
				fgets(pass_remetente, PASS_LENGHT, stdin);
				RemoveInvalid(pass_remetente);	//Remover /n da string

				passcheck = PasswordCheck(Contas, pass_remetente, remetente);	//Encontrar conta do remetente

				if (_stricmp(pass_remetente, "quit") == 0)	//Verificar se é para sair da tarefa
				{
					printf("Saindo...\n\n");
					Sleep(1000);
					break;
				}
				else if (passcheck == 0)	//Se password for incorreta
				{
					puts("Password incorreta!");
				}
			} while (passcheck == 0);	//Ate password esta correta

			if (_stricmp(pass_remetente, "quit") == 0)	//Sair da tarefa
			{
				printf("Saindo...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Nome do destinatario: ");
				fgets(nome_destinatario, NAME, stdin);
				RemoveInvalid(nome_destinatario);	//Remover \n da string

				destinatario = ContaFinder(Contas, nome_destinatario, contas_criadas);	//Encontrar conta do destinatario

				if (destinatario == remetente)
				{
					printf("Nao podes transferir para ti proprio.\n");
					continue;
				}
				else if (_stricmp(nome_destinatario, "quit") == 0)	//Verificar se e para sair da tarefa
				{
					break;
				}
				else if (destinatario == -1)
				{
					printf("Conta nao existe. Tente novamente.\n");
				}
			} while (destinatario == -1);

			if (_stricmp(nome_destinatario, "quit") == 0)
			{
				printf("Saindo...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				if (Contas[remetente].saldo <= 0)	//Nao tem saldo suficiente
				{
					printf("Nao tem dinheiro suficiente para efetuar uma transacao.\n");
					printf("Saindo...\n\n");
					Sleep(1000);
					break;
				}
				else
				{
					printf("Introduza quanto quer enviar para %s: $", Contas[destinatario].nome);
					scanf("%lf", &quantia_enviar);
					qtd_enviar_check = QtdEnviarValid(Contas[remetente].saldo, quantia_enviar);

					if (qtd_enviar_check == 0)
					{
						printf("Quantidade  invalida!\n");
					}
					else if (qtd_enviar_check == -1)
					{
						printf("Saldo insuficiente!\n");
					}
					else if(qtd_enviar_check == 1)
					{
						printf("%.2lf foi enviado para %s.\n", quantia_enviar,Contas[destinatario].nome);
						Contas[remetente].saldo -= quantia_enviar;	//Retirar quantia enviada ao remetente
						Contas[destinatario].saldo += quantia_enviar;	//Adicionar quantia enviada ao desstinatario
						printf("Saldo atual: %.2lf\n\n", Contas[remetente].saldo);
					}
				}
			} while (qtd_enviar_check == 0 || qtd_enviar_check == -1);

			if (Contas[remetente].saldo <= 0)	//Sair da tarefa
			{
				break;
			}

			printf("Saindo...\n\n");
			Sleep(1000);
			printf("\n\n");
			getchar();
			break;      //FIM TRANSFERENCIA DINHEIRO

		case '6':       /*Mudar pass precisa pass atual. se nao a souber perguntar o contacto de telemovel*/
			printf(" === ALTERAR PASSWORD === \n");
			printf("Digite quit para sair.\n");
			do
			{
				printf("Nome da conta: ");
				fgets(nome_conta_change, NAME, stdin);
				RemoveInvalid(nome_conta_change);		//Remover \n no fim da string

				pos_conta = ContaFinder(Contas, nome_conta_change, contas_criadas);	//Encontrar pos da conta

				if (_stricmp(nome_conta_change, "quit") == 0)	//Sair da tarefa
				{
					break;
				}
				else if (pos_conta == -1)	//Nao encontrou a conta
				{
					printf("Conta nao existe. Tente novamente.\n");
				}
			} while (pos_conta == -1);	//Repetir ate encontrar conta

			if (_stricmp(nome_conta_change, "quit") == 0)	//Sair da tarefa
			{
				printf("Saindo...\n\n");
				Sleep(1000);
				break;
			}

			do
			{
				printf("Password: ");
				fgets(pass_conta_change, PASS_LENGHT, stdin);
				RemoveInvalid(pass_conta_change);	//Remover \n da string

				pass_change_check = PasswordCheck(Contas, pass_conta_change, pos_conta);	//Ver se password esta certa

				if (_stricmp(pass_conta_change, "quit") == 0)	//Sair da tarefa
				{
					break;
				}
				else if (pass_change_check == 0)
				{
					printf("Password incorreta. Tente novamente.\n");
				}
				else if (pass_change_check == 1)
				{
					break;
				}
				contador_password_change++;

				if (contador_password_change % 3 == 0)
				{
					do
					{
						printf("Deseja verificar o perfil pelo numero de contacto?\n[S/N] ");
						scanf("%c", &choice_maker);	//Ler a escolha
						getchar();
						if (toupper(choice_maker) == 'S' || toupper(choice_maker) == 'N')	//Quer mudar
						{
							break;
						}
						else		//Introduziu decisao errada
						{
							printf("Introduza uma decisao valida [S/N].\n");
						}
						if (toupper(choice_maker) == 'S')
						{
							break;
						}
					} while (toupper(choice_maker) != 'S' || toupper(choice_maker) != 'N');

					if (toupper(choice_maker) == 'S')
					{
						break;
					}
					else if (toupper(choice_maker) == 'N')
					{
						continue;
					}
				}

			} while (pass_change_check == 0);
				


			if (_stricmp(pass_conta_change, "quit") == 0)	//Sair da tarefa
			{
				printf("Saindo...\n");
				Sleep(1000);
				break;
			}
			else if (toupper(choice_maker) == 'S')		//Verificacao por numero de contacto
			{
				printf("Digite quit para sair.\n");
				do
				{
					printf("Numero de contacto:+351");
					fgets(contacto_confirm, 10, stdin);
					RemoveInvalid(contacto_confirm);	//Remover o \n no fim da string
					contacto_check = ContactoConfirm(Contas, contacto_confirm, pos_conta);

					if (_stricmp(contacto_confirm, "quit") == 0)
					{
						break;
					}
					else if (contacto_check == 0)
					{
						printf("Numero de contacto errado. Tente novamente.\n");
					}
				} while (contacto_check == 0);		//Enquanto falhar o numero de contacto

				if (_stricmp(contacto_confirm, "quit") == 0)
				{
					printf("Saindo...\n");
					Sleep(1000);
				}
			}
			else if (pass_change_check == 1)	//Acertou password
			{
				do
				{
					printf("Nova password (minimo 8 caracteres): ");
					fgets(Contas[pos_conta].pass, PASS_LENGHT, stdin);
					RemoveInvalid(Contas[pos_conta].pass);		//Remover \n da string

					if (Password_Strength(Contas[pos_conta].pass) != 1)
					{
						printf("Password muito fraca!\nTente novamente.\n");
					}
				} while (Password_Strength(Contas[pos_conta].pass) != 1);      //Verificar se a password passa nos requisitos pedidos
			}

			if (contacto_check == 1)	//Acertou numero de contacto
			{
				do
				{
					getchar();
					printf("Nova password (minimo 8 caracteres): ");
					fgets(Contas[pos_conta].pass, PASS_LENGHT, stdin);
					RemoveInvalid(Contas[pos_conta].pass);		//Remover \n da string

					if (Password_Strength(Contas[pos_conta].pass) != 1)
					{
						printf("Password muito fraca!\nTente novamente.\n");
					}
				} while (Password_Strength(Contas[pos_conta].pass) != 1);      //Verificar se a password passa nos requisitos pedidos
			}

			printf("\n");
			contador_password_change = 0;
			break;      //FIM ALTERAR PASSWORD
		}
	}
	return 0;
}

void Menu(int contas_criadas)
{
	puts(" === BEM VINDO AO BANCO DAS BANANAS === ");
	puts("----------------------------------------");
	puts("|Selecione uma opcao das abaixo:       |");
	printf("|1. Adicionar contas bananarias(%d/%d) |\n", contas_criadas, MAX);   //1 Adicionar conta
	puts("|2. Consultar bananas                  |");   //2 Consultar saldo
	puts("|3. Levantar bananas                   |");   //3 Levantar dinheiro
	puts("|4. Depositar bananas                  |");   //4 Depositar dinheiro
	puts("|5. Transferencia bananaria            |");   //5 Transferencia de dinheiro
	puts("|6. Alterar password                   |");   //6 Alterar password
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
		for (i = 0; i < tamanho; i++)
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

	for (i = 0; i < size; i++)
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
	for (i = 0; contacto[i] != '\0'; i++)
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

	for (i = 0; string[i] != '\0'; i++)
	{
		if (string[i] == value)
		{
			return 1;
		}
	}
	return 0;
}

int ContaFinder(struct ContaBancaria contas[], char name[], int size)	//-1 se nao encontrar
{
	//Encontrar o nome do utilizador
	int i = 0;

	for (i = 0; i < size; i++)
	{
		if (strcmp(contas[i].nome, name) == 0)
		{
			return i;
		}
	}
	return -1;
}

int PasswordCheck(struct ContaBancaria contas[], char pass[], int conta)
{
	//Verifica se a password esta correta
	if (strcmp(contas[conta].pass, pass) == 0)
	{
		return 1;
	}
	return 0;
}

void RemoveInvalid(char word[])
{
	int i = 0;

	for (i = 0; word[i] != '\0'; i++)
	{
		if (word[i] == '\n')
		{
			word[i] = '\0';
		}
	}
}

int QtdEnviarValid(double saldo, double quantia_enviar)
{
	//Verifica se a quantia de dinheiro a enviar e valida

	if (quantia_enviar < 0)
	{
		return 0;	//Se a quantia for negativa
	}
	else if (quantia_enviar > saldo)
	{
		return -1;	//Se nao tiver saldo suficiente
	}
	else
	{
		return 1;	//Se for valido
	}
}

void ResetSaldos(struct ContaBancaria contas[], int size)
{
	int i = 0;

	for (i = 0; i < size; i++)
	{
		contas[i].saldo = 0;
	}
}

int ContactoConfirm(struct ContaBancaria contas[], char number[], int conta)
{
	//Verifica se o numero de contacto esta correto
	if (strcmp(contas[conta].contacto, number) == 0)
	{
		return 1;
	}
	return 0;
}

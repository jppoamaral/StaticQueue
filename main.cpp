//Nome: João Pedro de Paula Oliveira do Amaral
//TIA: 32049390
#pragma warning(disable : 4996)
#include <iostream>
#include "StaticQueue.h"
#include <ctime>
#include <string>

using namespace std;

//função que pula linha
void jumpLine()
{
	cout << "\n";
}

//função que otimisa os comandos de cin e cout
string outIn(string question)
{
	string answer;
	cout << question;
	cin >> answer;
	return answer;
}

//função que calcula o tempo total em segundos
int calculateSeconds(int hour, int minutes, int seconds)
{
	int totalSec, aux1, aux2;
	aux1 = hour * 3600;
	aux2 = minutes * 60;
	totalSec = aux1 + aux2 + seconds;
	return totalSec;
}

//função que registra os produtos do estoque e retorna um "codigo" contendo todas as informações do produto
string registerWater(StaticQueue& queue)
{
	jumpLine();
	string water;
	int numEstan = 0, numPrat = 0, numGav = 0, i;
	cout << "MackWater -- Menu de Registro \n";
	jumpLine();
	cout << "------------------------------------\n";
	time_t t = time(nullptr);
	cout << "Data e Hora do registro: " << asctime(localtime(&t)) << "\n";
	string aux = asctime(localtime(&t));
	int idxhora[]{ 11 , 12 , 14 , 15 , 17 , 18 };

	for (i = 0; i < 6; i++)
	{
		string numero(1, aux[idxhora[i]]);
		water.append(numero);
	}

	jumpLine();
	water.append(outIn("Digite o número da estante onde o recipiente será armazenado (Apenas 1 dígito): ")); //numero da estante - index 6
	water.append(outIn("Digite o número da prateleira onde o recipiente será armazenado (Apenas 1 dígito): ")); //numero da prateleira - index 7
	water.append(outIn("Digite o número da gaveta onde o recipiente será armazenado (Apenas 1 dígito): ")); //numero da gaveta - index 8
	cout << "------------------------------------\n";
	cout << "Água registrada com sucesso!\n";
	cout << "------------------------------------\n";
	jumpLine();

	return water;
}

//função que verifica e mostra os itens no estoque
void storage(StaticQueue& queueA, StaticQueue& queueB)
{
	string a = "";
	while (a == "")
	{
		time_t t = time(nullptr);
		cout << "MackWater -- Storage Menu\n";
		jumpLine();
		cout << "------------------------------------\n";
		cout << "Marca A -- Info:\n";
		jumpLine();
		cout << "Quantidade Disponível: " << Count(queueA) << "\n";
		cout << "Capacidade Total: " << Size(queueA) << "\n";
		cout << "------------------------------------\n";
		cout << "Marca B -- Info:\n";
		jumpLine();
		cout << "Quantidade Disponível: " << Count(queueB) << "\n";
		cout << "Capacidade Total: " << Size(queueB) << "\n";
		cout << "------------------------------------\n";
		jumpLine();
		cout << "Acesso feito em: " << asctime(localtime(&t)) << "\n";
		cout << "------------------------------------\n";
		a = outIn("0 - BACK:  ");
		jumpLine();
	}
}

//função que mostra as informações dos produtos que estão na lista de compras
void printInfo(StaticQueue& shopLst)
{
	if (!IsEmpty(shopLst))
	{
		for (int i = 0; i < Count(shopLst); i++)
		{
			cout << i + 1 << ". Agua da marca: " << shopLst.values[i][9] << "		Localizada na:\n";
			jumpLine();
			cout << "				Estante: " << shopLst.values[i][6] << "\n";
			cout << "				Prateleira: " << shopLst.values[i][7] << "\n";
			cout << "				Gaveta: " << shopLst.values[i][8] << "\n";
			cout << "				Horário de registro: " << shopLst.values[i][0] << shopLst.values[i][1] << ":" << shopLst.values[i][2] << shopLst.values[i][3] << ":" << shopLst.values[i][4] << shopLst.values[i][5] << "\n";
			jumpLine();
		}
	}
	else {
		cout << "Sua lista de compras está vazia!\n";
	}
}

//função que imprime o recibo da compra e finaliza o pedido
bool checkout(StaticQueue& shLst, bool continuar)
{

	int countA = 0, countB = 0, i = 0, num;
	for (i; i < Count(shLst); i++)
		if (shLst.values[i][9] == 'A')
			countA++;
		else if (shLst.values[i][9] == 'B')
			countB++;
	jumpLine();
	
	cout << "CHECKOUT\n";
	jumpLine();
	cout << "------------------------------------\n";
	cout << "Unidades (u.n.)	- Marca";
	jumpLine();
	cout << countA << "u.n.		- Marca A\n";
	cout << countB << "u.n.		- Marca B\n";
	cout << "------------------------------------\n";
	cout << "INFORMAÇÕES DOS PRODUTOS\n";
	jumpLine();
	printInfo(shLst);
	cout << "------------------------------------\n";
	cout << "0 - Deseja finalizar a compra\n";
	cout << "1 - Adicionar mais produtos\n";
	jumpLine();
	num = stoi(outIn("Comando:  "));
	jumpLine();
	switch (num)
	{
		case 0:
			return continuar == false;
			break;
		case 1:
			return continuar == true;
			break;
	}
}

//função que realiza o processo de venda
void purchase(StaticQueue& queueA, StaticQueue& queueB)
{
	bool continuar = true;
	int num;
	StaticQueue shoppingLst = Create();
	while (continuar)
	{
		string aux;
		cout << "MackWater -- Shopping Menu \n";
		jumpLine();
		cout << "------------------------------------\n";
		cout << "Qual Produto desenha comprar?\n";
		jumpLine();
		cout << "1 - Marca A\n";
		cout << "2 - Marca B\n";
		cout << "3 - Tanto Faz a Marca!\n";
		cout << "0 - EXIT/BACK";
		jumpLine();
		cout << "Digite o número do produto que deseja: ";
		cin >> num;
		cout << "------------------------------------\n";
		switch (num)
		{
			case 0:
				break;
			case 1: 
				if (!IsEmpty(queueA))
				{
					aux = Dequeue(queueA);
					Enqueue(shoppingLst, aux.append("A"));
					cout << "Produto comprado com sucesso!\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				else
				{
					cout << "Estoque do produto de Marca A está esgotado :(\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				break;

			case 2:
				if (!IsEmpty(queueB))
				{
					aux = Dequeue(queueB);
					Enqueue(shoppingLst, aux.append("B"));
					cout << "Produto comprado com sucesso!\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				else 
				{
					cout << "Estoque do produto de Marca B está esgotado :(\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				break;

			case 3:
				int hourA, hourB, minA, minB, secA, secB, totalSecA = 0, totalSecB = 0; //variaveis do tempo
				string tempA[9], tempB[9], shourA, shourB, sminA, sminB, ssecA, ssecB; //variaveis auxiliares usadas para transformar string em int

				if (!IsEmpty(queueA)) 
				{
					for (int i = 0; i < 9; i++) //transfere as informações de front para um array de strings
						tempA[i] = Front(queueA)[i];

					shourA = tempA[0] + tempA[1]; //neste bloco é feita a separacao do tempo(string) em hora minuto e segundo					
					sminA = tempA[2] + tempA[3];
					ssecA = tempA[4] + tempA[5];
					
					hourA = stoi(shourA); //neste bloco é feita a conversão de string para int					
					minA = stoi(sminA);					
					secA = stoi(ssecA);
					
					totalSecA = calculateSeconds(hourA, minA, secA);				
				}

				if (!IsEmpty(queueB))
				{
					for (int i = 0; i < 9; i++)
						tempB[i] = Front(queueB)[i];

					shourB = tempB[0] + tempB[1]; 
					sminB = tempB[2] + tempB[3];
					ssecB = tempB[4] + tempB[5];

					hourB = stoi(shourB);
					minB = stoi(sminB);
					secB = stoi(ssecB);

					totalSecB = calculateSeconds(hourB, minB, secB);
				}
				
				if ((totalSecA < totalSecB || totalSecB == 0) && !IsEmpty(queueA) && (Count(shoppingLst) != Size(shoppingLst))) //aqui é comparado o tempo de compra de A e B (a comparação leva em consideração as possibilidades: uma das filas está vazia; 
				{																																																				//  as duas tem pelo menos 1 elem	
					Enqueue(shoppingLst, Dequeue(queueA).append("A"));																																							//  a lista de compras esta cheia ou com espaço sobrando
					cout << "Produto comprado com sucesso!\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				else if ((totalSecB < totalSecA || totalSecA == 0) && !IsEmpty(queueB) && (Count(shoppingLst) != Size(shoppingLst)))
				{
					Enqueue(shoppingLst, Dequeue(queueB).append("B"));
					cout << "Produto comprado com sucesso!\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				else
				{
					cout << "Estoque dos produtos de qualquer Marca estão esgotados ou Lista de compras cheia!  :(\n";
					cout << "------------------------------------\n";
					jumpLine();
				}
				break;
		}

		if (!num)
			continuar = checkout(shoppingLst, continuar);
	}
}

//função que cria a interface principal para interação com o usuario
int menu()
{
	int num;
	cout << "MackWater -- Main Menu \n";
	jumpLine();
	cout << "------------------------------------\n";
	cout << "1 - REGISTER (Employees Only!)\n";
	cout << "2 - STORAGE\n";
	cout << "3 - SHOP (Clients)\n";
	cout << "0 - EXIT\n";
	jumpLine();
	cout << "Digite um número para executar uma ação: ";
	cin >> num;
	cout << "------------------------------------\n";
	jumpLine();
	return num;
}

int main()
{
	setlocale(LC_ALL, "pt_BR");

	StaticQueue waterA = Create();
	StaticQueue waterB = Create();

	bool continuar = true;
	while (continuar)
	{
		int num = menu();
		if (num == 0)
			continuar = false;
		else if (num == 1)
		{
			string brand = outIn("Digite a marca da água que deseja registrar: ");
			jumpLine();
			cout << "------------------------------------\n";
			if ((brand == "a" || brand == "A") && Count(waterA) != Size(waterA)) //coloca o "codigo" dentro da fila
				Enqueue(waterA, registerWater(waterA));
			else if ((brand == "b" || brand == "B") && Count(waterB) != Size(waterB))
				Enqueue(waterB, registerWater(waterB));
			else
			{
				cout << "Estoque Cheio! ou Comando Inválido!\n";
				cout << "------------------------------------\n";
				jumpLine();
			}		
		}
		else if (num == 2)
			storage(waterA, waterB);
		else if (num == 3)
			purchase(waterA, waterB);
	}
}
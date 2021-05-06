#include "StaticQueue.h"
#include <string>

//Create()
//Cria e retorna uma fila vazia.
//
//Pré - condição: N / A.
//Pós - condição : Uma nova fila vazia é criada.
StaticQueue Create()
{

	StaticQueue queue =
	{
		0, // int front;
		0, // int rear;
		0, // int count;
		{ "" } // char values[STATIC_QUEUE_CAPACITY];
	};

	return queue;
}

//Enqueue(queue, elem)
//Insere o elemento elem no fim da fila queue, se a fila não estiver cheia.
//
//Pré - condição: A fila queue é válida.
//Pós - condição : O final da fila contém o elemento elem OU erro se a fila estiver cheia.
bool Enqueue(StaticQueue& queue, std::string elem)
{
	// Verifica se a fila está cheia.
	if (queue.count == Size(queue))
	{
		return false;
	}

	// Insere elem no final da fila (vetor da queue).
	queue.values[queue.rear] = elem;

	// "Vetor circular": se chegou no final do vetor (no limite/capacidade do vetor),
	// a variável rear, que é usada para indicar o índice correto para um novo elemento da fila,
	// volta pro início do vetor.
	queue.rear = (queue.rear + 1) % Size(queue); // Mantém queue.rear no intervalo 0 <= queue.rear < Size(queue).

	// A linha acima equivale à:
	// ++queue.rear;
	// if (queue.rear == Size(queue))
	// {
	// 	queue.rear = 0;
	// }

	++queue.count;

	return true;
}

//Dequeue(queue)
//Remove e retorna o primeiro elemento da fila queue, se a fila não estiver vazia.
//
//Pré - condição: A fila queue é válida.
//Pós - condição : Remove e retorna o primeiro elemento da fila OU erro se a fila estiver vazia.
std::string Dequeue(StaticQueue& queue)
{
	if (IsEmpty(queue))
	{
		return "\0";
	}

	// Como remover e retornar o primeiro elemento da fila?
	std::string value = queue.values[queue.front];
	queue.values[queue.front] = '\0';

	// "Vetor circular": se chegou no final do vetor (no limite/capacidade do vetor),
	// a variável front, que é usada para indicar o índice correto do primeiro elemento da fila,
	// volta pro início do vetor.
	queue.front = (queue.front + 1) % Size(queue); // Mantém queue.front no intervalo 0 <= queue.front < Size(queue).

	// A linha acima equivale à:
	// ++queue.front;
	// if (queue.front == Size(queue))
	// {
	// 	queue.front = 0;
	// }

	--queue.count;

	return value;
}

std::string Front(const StaticQueue& queue)
{
	return IsEmpty(queue) ? "\0" : queue.values[queue.front];
}

int Size(const StaticQueue& queue)
{
	return sizeof(queue.values) / sizeof(queue.values[0]); 
}

int Count(const StaticQueue& queue)
{
	return queue.count;
}

bool IsEmpty(const StaticQueue& queue)
{
	return queue.count == 0;
}

bool Clear(StaticQueue& queue)
{
	while (!IsEmpty(queue))
	{
		Dequeue(queue);
	}

	return IsEmpty(queue);
}
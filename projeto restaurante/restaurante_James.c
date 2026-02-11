/*********** SISTEM DE RESERVA DE RESTAURANTE **************


* TÍLULO: SISTEM DE RESERVA DE RESTAURANTE
*AUTOR: [JAMES_ALCON]
*DATA: 2026-02-06
*DESCRIÇÂO: Algoritmo para gerenciar reservas de um restaurante.
*CONCEITOS: Operadores Logicos ,Estrururas condicionais, Estruturas de repetição, Estruturas de dados, Funções, Vetores, Matrizes, Strings.
*/



#include <stdio.h>
#include <string.h>

#define reserva_cliente 100
#define nome_cliente 50

// Estrutura para armazenar informação do cliente
typedef struct {
    int id_Cliente;
    char nome[nome_cliente];
} Cliente;

// Estrutura para armazenar uma reserva
typedef struct {
    int id_Cliente;
    int dia;
    int mes;
    int hora;
    int min;
} Reserva;

// Arrays para armazenar clientes e reservas
Cliente clientes[reserva_cliente];
Reserva reservas[reserva_cliente];

int totalClientes = 0;
int totalReservas = 0;

// Função para procurar cliente pelo ID, retorna índice ou -1 se não encontrado
int procurarCliente(int id) {
    for (int i = 0; i < totalClientes; i++) {
        if (clientes[i].id_Cliente == id) {
            return i;
        }
    }
    return -1;
}

// Função para ler inteiro com validação usando fgets e sscanf
int lerInteiro(const char* mensagem) {
    char buffer[100];
    int valor;
    char extra;

    while (1) {
        printf("%s", mensagem);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Valor inválido. Tente novamente.\n");
            continue;
        }
        // Verifica se a entrada é um inteiro válido e não tem caracteres extras
        if (sscanf(buffer, "%d %c", &valor, &extra) == 1) {
            return valor;
        } else {
            printf("Entrada inválida. Por favor, digite um número inteiro válido.\n");
        }
    }
}

// Função para criar uma reserva
void criarReserva() {
    if (totalReservas >= reserva_cliente) {
        printf("Limite de reservas atingido.\n");
        return;
    }

    int id, dia, mes, hora, min;
    char nome[nome_cliente];

    id = lerInteiro("ID do Cliente: ");

    int idxCliente = procurarCliente(id);
    if (idxCliente == -1) {
        // Cliente não existe, pedir nome e adicionar
        printf("Nome do Cliente: ");
        if (fgets(nome, sizeof(nome), stdin) == NULL) {
            printf("Erro na leitura do nome.\n");
            return;
        }
        // Remove o '\n' do final da string, se existir
        nome[strcspn(nome, "\n")] = 0;

        clientes[totalClientes].id_Cliente = id;
        strncpy(clientes[totalClientes].nome, nome, nome_cliente);
        totalClientes++;
    } else {
        // Cliente já existe, usar nome existente
        strncpy(nome, clientes[idxCliente].nome, nome_cliente);
    }

    dia = lerInteiro("Dia da reserva (1-31): ");
    mes = lerInteiro("Mês da reserva (1-12): ");
    hora = lerInteiro("Hora da reserva (0-23): ");
    min = lerInteiro("Minuto da reserva (0-59): ");

    reservas[totalReservas].id_Cliente = id;
    reservas[totalReservas].dia = dia;
    reservas[totalReservas].mes = mes;
    reservas[totalReservas].hora = hora;
    reservas[totalReservas].min = min;
    totalReservas++;

    printf("Reserva criada para %s no dia %02d/%02d às %02d:%02d.\n", nome, dia, mes, hora, min);
}

// Função para listar todas as reservas
void listarReservas() {
    if (totalReservas == 0) {
        printf("Nenhuma reserva registada.\n");
        return;
    }

    printf("Lista de Reservas:\n");
    for (int i = 0; i < totalReservas; i++) {
        int idxCliente = procurarCliente(reservas[i].id_Cliente);
        if (idxCliente != -1) {
            printf("Cliente: %s (ID %d) - Data: %02d/%02d - Hora: %02d:%02d\n",
                   clientes[idxCliente].nome,
                   reservas[i].id_Cliente,
                   reservas[i].dia,
                   reservas[i].mes,
                   reservas[i].hora,
                   reservas[i].min);
        }
    }
}

// Função para mostrar reservas por utilizador (ID)
void reservasPorUtilizador() {
    int id = lerInteiro("ID do Cliente para listar reservas: ");

    int idxCliente = procurarCliente(id);
    if (idxCliente == -1) {
        printf("Cliente com ID %d não encontrado.\n", id);
        return;
    }

    printf("Reservas do cliente %s (ID %d):\n", clientes[idxCliente].nome, id);
    int encontrou = 0;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].id_Cliente == id) {
            printf("Data: %02d/%02d - Hora: %02d:%02d\n",
                   reservas[i].dia,
                   reservas[i].mes,
                   reservas[i].hora,
                   reservas[i].min);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para este cliente.\n");
    }
}

// Função para mostrar reservas por data
void reservasPorData() {
    int dia = lerInteiro("Dia da reserva para listar: ");
    int mes = lerInteiro("Mês da reserva para listar: ");

    printf("Reservas para o dia %02d/%02d:\n", dia, mes);
    int encontrou = 0;
    for (int i = 0; i < totalReservas; i++) {
        if (reservas[i].dia == dia && reservas[i].mes == mes) {
            int idxCliente = procurarCliente(reservas[i].id_Cliente);
            if (idxCliente != -1) {
                printf("Cliente: %s (ID %d) - Hora: %02d:%02d\n",
                       clientes[idxCliente].nome,
                       reservas[i].id_Cliente,
                       reservas[i].hora,
                       reservas[i].min);
                encontrou = 1;
            }
        }
    }
    if (!encontrou) {
        printf("Nenhuma reserva encontrada para esta data.\n");
    }
}

// Menu do Utilizador 
int main() {
    int opcao;

    do {
        printf("\n--- Sistema de Reservas Sabor em Loop ---\n");
        printf("1 - Criar reserva\n");
        printf("2 - Listar reservas\n");
        printf("3 - Reservas por utilizador\n");
        printf("4 - Reservas por data\n");
        printf("0 - Sair\n");
        opcao = lerInteiro("Escolha uma opção: ");

        switch (opcao) {
            case 1:
                criarReserva();
                break;
            case 2:
                listarReservas();
                break;
            case 3:
                reservasPorUtilizador();
                break;
            case 4:
                reservasPorData();
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

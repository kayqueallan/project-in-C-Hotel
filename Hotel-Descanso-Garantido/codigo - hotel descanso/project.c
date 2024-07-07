#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 200
#define MAX_FUNCIONARIOS 100
#define MAX_ESTADIAS 200
#define MAX_QUARTOS 100

typedef struct QUARTO
{
    int numeroQuarto;
    int qntdHospedes;
    float valorDiaria;
    char status[10];
} Quarto;

typedef struct CLIENTE
{
    int codigo;
    char nome[100];
    char endereco[200];
    char telefone[15];
} Cliente;

typedef struct FUNCIONARIO
{
    int codigo;
    char nome[100];
    char telefone[15];
    char cargo[50];
    float salario;
} Funcionario;

typedef struct ESTADIA
{
    int codigo;
    Cliente cliente;
    Quarto quarto;
    char dataEntrada[11];
    char dataSaida[11];
    int qntdDiarias;
} Estadia;

Funcionario funcionarios[MAX_FUNCIONARIOS];
int numFuncionarios = 0;

Cliente clientes[MAX_CLIENTES];
int numClientes = 0;

Quarto quartos[MAX_QUARTOS];
int numQuartos = 0;

Estadia estadias[MAX_ESTADIAS];
int numEstadias = 0;

int diasMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int validarData(const char *dataStr)
{
    int dia, mes, ano;
    char data[11];
    strcpy(data, dataStr);
    char *token = strtok(data, "/");

    if (token == NULL)
        return 0;
    dia = atoi(token);

    token = strtok(NULL, "/");
    if (token == NULL)
        return 0;
    mes = atoi(token);

    token = strtok(NULL, "/");
    if (token == NULL)
        return 0;
    ano = atoi(token);

    if (ano < 2000 || ano > 2099)
    {
        return 0;
    }

    if (mes < 1 || mes > 12)
    {
        return 0;
    }

    if (dia < 1 || dia > diasMes[mes - 1])
    {
        return 0;
    }
    return 1;
}

void cadastrarCliente()
{
    Cliente cliente;
    printf("\n\n----------------------------------------\n");
    printf("\tCADASTRO DE CLIENTE");
    printf("\n----------------------------------------\n\n");

    printf("Codigo do cliente: ");
    scanf("%d", &cliente.codigo);

    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].codigo == cliente.codigo)
        {
            printf("\n\nErro: Codigo de funcionario ja existente. Tente novamente.\n\n");
            return;
        }
    }

    while (getchar() != '\n')
        ;

    printf("Nome do cliente: ");
    scanf(" %[^\n]s", cliente.nome);

    printf("Endereco do cliente: ");
    scanf(" %[^\n]", cliente.endereco);

    printf("Informe seu telefone: ");
    scanf(" %[^\n]s", cliente.telefone);

    clientes[numClientes++] = cliente;

    printf("\n\n----------------------------------------\n");
    printf("\tCLIENTE CADASTRADO COM SUCESSO");
    printf("\n----------------------------------------\n\n");

    printf("Codigo do cliente: %d\n\n", cliente.codigo);
}

void cadastrarFuncionario()
{
    Funcionario funcionario;

    printf("\n\n----------------------------------------\n");
    printf("\tCADASTRO DE FUNCIONARIO");
    printf("\n----------------------------------------\n\n");

    while (getchar() != '\n')
        ;

    printf("Codigo do funcionario: ");
    scanf("%d", &funcionario.codigo);

    for (int i = 0; i < numFuncionarios; i++)
    {
        if (funcionarios[i].codigo == funcionario.codigo)
        {
            printf("\n\nErro: Codigo de funcionario ja existente. Tente novamente.\n\n");
            return;
        }
    }

    while (getchar() != '\n')
        ;

    printf("Informe seu nome: ");
    scanf(" %[^\n]s", funcionario.nome);

    printf("Informe seu telefone: ");
    scanf(" %[^\n]s", funcionario.telefone);

    printf("Informe seu Cargo: ");
    scanf(" %[^\n]s", funcionario.cargo);

    printf("Informe seu Salario: ");
    scanf(" %f", &funcionario.salario);
    while (getchar() != '\n')
        ;

    if (funcionario.salario < 0)
    {
        printf("\n\nERRO: Salario nao pode ser negativo. Cadastro cancelado.\n\n");
        return;
    }

    printf("\n\n----------------------------------------\n");
    printf("\tFUNCIONARIO CADASTRADO COM SUCESSO");
    printf("\n----------------------------------------\n\n");

    printf("Codigo do funcionario: %d\n\n", funcionario.codigo);

    funcionarios[numFuncionarios++] = funcionario;
}

int calcularQuantidadeDiarias(const char *dataEntrada, const char *dataSaida)
{
    int diaEntrada, mesEntrada, anoEntrada;
    int diaSaida, mesSaida, anoSaida;

    sscanf(dataEntrada, "%d/%d/%d", &diaEntrada, &mesEntrada, &anoEntrada);
    sscanf(dataSaida, "%d/%d/%d", &diaSaida, &mesSaida, &anoSaida);

    int qntdDiarias = 0;

    while (!(diaEntrada == diaSaida && mesEntrada == mesSaida && anoEntrada == anoSaida))
    {
        qntdDiarias++;
        diaEntrada++;
        if (diaEntrada > diasMes[mesEntrada - 1])
        {
            diaEntrada = 1;
            mesEntrada++;
            if (mesEntrada > 12)
            {
                mesEntrada = 1;
                anoEntrada++;
            }
        }
    }

    return qntdDiarias + 1;
}

void cadastrarEstadia()
{
    Estadia estadia;
    int codigo_cliente;
    int qntdHospedes;
    char dataEntrada[11];
    char dataSaida[11];

    printf("\n\n----------------------------------------\n");
    printf("\tCADASTRO DE ESTADIA");
    printf("\n----------------------------------------\n\n");

    printf("Codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    int cliente_encontrado = 0;
    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].codigo == codigo_cliente)
        {
            cliente_encontrado = 1;
            estadia.cliente = clientes[i];
            break;
        }
    }
    if (!cliente_encontrado)
    {
        printf("\n\nERRO: Cliente nao encontrado.\n\n");
        return;
    }

    printf("Codigo da estadia: ");
    scanf(" %d", &estadia.codigo);

    for (int i = 0; i < numEstadias; i++)
    {
        if (estadias[i].codigo == estadia.codigo)
        {
            printf("\n\nErro: Codigo de funcionario ja existente. Tente novamente.\n\n");
            return;
        }
    }

    printf("Quantidade de hospedes: ");
    scanf("%d", &qntdHospedes);

    if (qntdHospedes <= 0)
    {
        printf("\n\nERRO: A quantidade de hospedes deve ser maior que zero.\n\n");
        return;
    }

    printf("Data de entrada (dd/mm/aaaa): ");
    scanf(" %[^\n]s", dataEntrada);

    printf("Data de saida (dd/mm/aaaa): ");
    scanf(" %[^\n]s", dataSaida);

    if (!validarData(dataEntrada) || !validarData(dataSaida))
    {
        printf("\n\nERRO: Data de entrada ou saida invalida.\n\n");
        return;
    }

    int diaEntrada, mesEntrada, anoEntrada;
    int diaSaida, mesSaida, anoSaida;

    sscanf(dataEntrada, "%d/%d/%d", &diaEntrada, &mesEntrada, &anoEntrada);
    sscanf(dataSaida, "%d/%d/%d", &diaSaida, &mesSaida, &anoSaida);

    if (anoEntrada > anoSaida || (anoEntrada == anoSaida && (mesEntrada > mesSaida || (mesEntrada == mesSaida && diaEntrada >= diaSaida))))
    {
        printf("\n\nERRO: Data de entrada deve ser anterior a data de saida.\n\n");
        return;
    }

    int quarto_encontrado = 0;
    for (int i = 0; i < numQuartos; i++)
    {
        if (quartos[i].qntdHospedes >= qntdHospedes && strcmp(quartos[i].status, "desocupado") == 0)
        {
            estadia.quarto = quartos[i];
            quarto_encontrado = 1;
            strcpy(quartos[i].status, "ocupado");
            break;
        }
    }

    if (!quarto_encontrado)
    {
        printf("\n\nERRO: Nenhum quarto disponivel.\n\n");
        return;
    }

    strcpy(estadia.dataEntrada, dataEntrada);
    strcpy(estadia.dataSaida, dataSaida);

    estadia.qntdDiarias = calcularQuantidadeDiarias(dataEntrada, dataSaida);

    estadias[numEstadias++] = estadia;

    printf("\n\n----------------------------------------\n");
    printf("\tESTADIA CADASTRADA COM SUCESSO");
    printf("\n----------------------------------------\n");
    printf("Codigo da Estadia: %d\n\n", estadia.codigo);
}

void cadastrarQuarto()
{
    Quarto quarto;
    printf("\n\n----------------------------------------\n");
    printf("\tCADASTRO DE QUARTO");
    printf("\n----------------------------------------\n\n");

    printf("Numero do quarto: ");
    scanf("%d", &quarto.numeroQuarto);

    for (int i = 0; i < numQuartos; i++)
    {
        if (quartos[i].numeroQuarto == quarto.numeroQuarto)
        {
            printf("\n\nERRO: Numero do quarto ja existente.\n\n");
            return;
        }
    }

    printf("Quantidade de hospedes: ");
    scanf("%d", &quarto.qntdHospedes);

    if (quarto.qntdHospedes <= 0)
    {
        printf("\n\nERRO: A quantidade de hospedes deve ser maior que zero.\n\n");
        return;
    }

    printf("Valor da diaria: ");
    scanf("%f", &quarto.valorDiaria);

    if (quarto.valorDiaria <= 0)
    {
        printf("\n\nERRO: O valor da diaria deve ser maior que zero.\n\n");
        return;
    }

    if (quarto.numeroQuarto < 0)
    {
        printf("\n\nERRO: O numero do quarto deve ser maior que zero\n\n");
        return;
    }

    strcpy(quarto.status, "desocupado");

    quartos[numQuartos++] = quarto;
    printf("\n\n----------------------------------------\n");
    printf("\tQUARTO CADASTRADO COM SUCESSO");
    printf("\n----------------------------------------\n\n");
}

void finalizarEstadia()
{
    int codigoEstadia;
    printf("\n\n----------------------------------------\n");
    printf("\tFINALIZAR ESTADIA");
    printf("\n----------------------------------------\n\n");

    printf("Informe o codigo da estadia: ");
    scanf("%d", &codigoEstadia);

    int estadia_encontrada = 0;
    for (int i = 0; i < numEstadias; i++)
    {
        if (estadias[i].codigo == codigoEstadia)
        {
            estadia_encontrada = 1;
            int codigoQuarto = estadias[i].quarto.numeroQuarto;
            for (int j = 0; j < numQuartos; j++)
            {
                if (quartos[j].numeroQuarto == codigoQuarto)
                {
                    strcpy(quartos[j].status, "desocupado");
                    break;
                }
            }

            float valorTotal = estadias[i].quarto.valorDiaria * estadias[i].qntdDiarias;
            printf("\n\n----------------------------------------\n");
            printf("\tESTADIA FINALIZADA COM SUCESSO");
            printf("\n----------------------------------------\n\n");
            printf("Cliente: %s\n", estadias[i].cliente.nome);
            printf("Quarto: %d\n", estadias[i].quarto.numeroQuarto);
            printf("Data de entrada: %s\n", estadias[i].dataEntrada);
            printf("Data de saida: %s\n", estadias[i].dataSaida);
            printf("Codigo da estadia: %d\n", estadias[i].codigo);
            printf("Quantidade de diarias: %d\n", estadias[i].qntdDiarias);
            printf("\nValor total da estadia: R$%.2f\n", valorTotal);

            for (int k = i; k < numEstadias - 1; k++)
            {
                estadias[k] = estadias[k + 1];
            }
            numEstadias--;
            break;
        }
    }

    if (!estadia_encontrada)
    {
        printf("\n\nERRO: Estadia nao encontrada.\n\n");
    }
}

void exibirQuartosDisponiveis()
{
    printf("\n\n----------------------------------------\n");
    printf("\tQUARTOS DISPONIVEIS");
    printf("\n----------------------------------------\n\n");

    int disponiveis = 0;
    for (int i = 0; i < numQuartos; i++)
    {
        if (strcmp(quartos[i].status, "desocupado") == 0)
        {
            disponiveis++;
            printf("Quarto %d: acomoda %d hospedes, diaria de R$%.2f\n", quartos[i].numeroQuarto, quartos[i].qntdHospedes, quartos[i].valorDiaria);
        }
    }

    if (disponiveis == 0)
    {
        printf("\n\nNao ha quartos disponiveis no momento.\n\n");
    }
}

void pesquisarCliente()
{
    char nome_cliente[100];
    int opcao;
    int codigo_cliente;

    printf("\n\n----------------------------------------\n");
    printf("\tPESQUISA DE CLIENTE");
    printf("\n----------------------------------------\n\n");
    printf("\n1. Pesquisar por nome\n");
    printf("2. Pesquisar por codigo\n");
    printf("Selecione a opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:

        printf("Nome do cliente: ");
        scanf(" %[^\n]", nome_cliente);

        for (int i = 0; i < numClientes; i++)
        {
            if (strcmp(clientes[i].nome, nome_cliente) == 0)
            {
                printf("\n\n----------------------------------------\n");
                printf("\tCLIENTE ENCONTRADO");
                printf("\n----------------------------------------\n\n");
                printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n",
                       clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
                return;
            }
        }
        printf("\n\nERRO: Cliente nao encontrado!\n\n");
        break;

    case 2:

        printf("Codigo do cliente: ");
        scanf("%d", &codigo_cliente);

        for (int i = 0; i < numClientes; i++)
        {
            if (clientes[i].codigo == codigo_cliente)
            {
                printf("\n\n----------------------------------------\n");
                printf("\tCLIENTE ENCONTRADO");
                printf("\n----------------------------------------\n\n");
                printf("Codigo: %d\nNome: %s\nEndereco: %s\nTelefone: %s\n",
                       clientes[i].codigo, clientes[i].nome, clientes[i].endereco, clientes[i].telefone);
                return;
            }
        }
        printf("\n\nERRO: Cliente nao encontrado!\n\n");
        break;

    default:
        printf("\n\nOpcao invalida!\n\n");
        break;
    }
}

void pesquisarFuncionario()
{
    char nome_funcionario[100];
    int codigo_funcionario, opcao;
    printf("\n\n----------------------------------------\n");
    printf("\tPESQUISA DE FUNCIONARIO");
    printf("\n----------------------------------------\n\n");

    printf("\n1. Pesquisar por Nome\n");
    printf("2. Pesquisar por Codigo de Funcionario\n");
    printf("Selecione a opcao: ");
    scanf("%d", &opcao);

    while (getchar() != '\n');

    switch (opcao)
    {
    case 1:
        printf("Nome do Funcionario: ");
        scanf(" %[^\n]", nome_funcionario);

        for (int i = 0; i < numFuncionarios; i++)
        {
            if (strcmp(funcionarios[i].nome, nome_funcionario) == 0)

            {
                printf("\n\n----------------------------------------\n");
                printf("\tFUNCIONARIO ENCONTRADO");
                printf("\n----------------------------------------\n\n");
                printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                       funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
                return;
            }
        }
        printf("\n\nERRO: Funcionario nao encontrado!\n\n");
        break;

    case 2:

        printf("Codigo do Funcionario: ");
        scanf("%d", &codigo_funcionario);

        for (int i = 0; i < numFuncionarios; i++)
        {
            if (funcionarios[i].codigo == codigo_funcionario)
            {
                printf("\n\n----------------------------------------\n");
                printf("\tFUNCIONARIO ENCONTRADO");
                printf("\n----------------------------------------\n\n");
                printf("Codigo: %d\nNome: %s\nTelefone: %s\nCargo: %s\nSalario: %.2f\n",
                       funcionarios[i].codigo, funcionarios[i].nome, funcionarios[i].telefone, funcionarios[i].cargo, funcionarios[i].salario);
                return;
            }
        }
        printf("\n\nERRO: Funcionario nao encontrado!\n\n");
        break;
    default:
        printf("\n\nOpcao invalida! Tente novamente.\n\n");
        break;
    }
}

void mostrarEstadiasCliente()
{
    int codigo_cliente;
    printf("\n\n----------------------------------------\n");
    printf("\tMOSTRAR ESTADIAS DO CLIENTE");
    printf("\n----------------------------------------\n\n");

    printf("Codigo do cliente: ");
    scanf("%d", &codigo_cliente);

    for (int i = 0; i < numEstadias; i++)
    {
        if (estadias[i].cliente.codigo == codigo_cliente)
        {
            printf("\n\n----------------------------------------\n");
            printf("\tDADOS DA ESTADIA");
            printf("\n----------------------------------------\n\n");

            printf("Codigo da Estadia: %d\nData de Entrada: %s\nData de Saida: %s\nQuantidade de Diarias: %d\nNumero do Quarto: %d\n",
                   estadias[i].codigo, estadias[i].dataEntrada, estadias[i].dataSaida, estadias[i].qntdDiarias, estadias[i].quarto.numeroQuarto);
            return;
        }
    }
    printf("\n\nErro: Nenhuma estadia encontrada para o cliente.\n\n");
}

void salvarDados()
{
    FILE *arquivo;
    arquivo = fopen("hotel_dados.txt", "w");

    if (arquivo == NULL)
    {
        printf("\n\nErro ao abrir arquivo para escrita.\n\n");
        return;
    }

    // Salvar clientes
    fprintf(arquivo, "================ CLIENTES ================\n");
    for (int i = 0; i < numClientes; i++)
    {
        fprintf(arquivo, "Código: %d\n", clientes[i].codigo);
        fprintf(arquivo, "Nome: %s\n", clientes[i].nome);
        fprintf(arquivo, "Endereço: %s\n", clientes[i].endereco);
        fprintf(arquivo, "Telefone: %s\n", clientes[i].telefone);
        fprintf(arquivo, "-----------------------------------------\n");
    }
    fprintf(arquivo, "\n");

    // Salvar funcionários
    fprintf(arquivo, "================ FUNCIONÁRIOS ================\n");
    for (int i = 0; i < numFuncionarios; i++)
    {
        fprintf(arquivo, "Código: %d\n", funcionarios[i].codigo);
        fprintf(arquivo, "Nome: %s\n", funcionarios[i].nome);
        fprintf(arquivo, "Telefone: %s\n", funcionarios[i].telefone);
        fprintf(arquivo, "Cargo: %s\n", funcionarios[i].cargo);
        fprintf(arquivo, "Salário: R$ %.2f\n", funcionarios[i].salario);
        fprintf(arquivo, "---------------------------------------------\n");
    }
    fprintf(arquivo, "\n");

    // Salvar estadias
    fprintf(arquivo, "================ ESTADIAS ================\n");
    for (int i = 0; i < numEstadias; i++)
    {
        fprintf(arquivo, "Código da Estadia: %d\n", estadias[i].codigo);
        fprintf(arquivo, "Código do Cliente: %d\n", estadias[i].cliente.codigo);
        fprintf(arquivo, "Número do Quarto: %d\n", estadias[i].quarto.numeroQuarto);
        fprintf(arquivo, "Data de Entrada: %s\n", estadias[i].dataEntrada);
        fprintf(arquivo, "Data de Saída: %s\n", estadias[i].dataSaida);
        fprintf(arquivo, "Quantidade de Diárias: %d\n", estadias[i].qntdDiarias);
        fprintf(arquivo, "------------------------------------------\n");
    }
    fprintf(arquivo, "\n");

    // Salvar quartos
    fprintf(arquivo, "================ QUARTOS ================\n");
    for (int i = 0; i < numQuartos; i++)
    {
        fprintf(arquivo, "Número do Quarto: %d\n", quartos[i].numeroQuarto);
        fprintf(arquivo, "Quantidade de Hóspedes: %d\n", quartos[i].qntdHospedes);
        fprintf(arquivo, "Valor da Diária: R$ %.2f\n", quartos[i].valorDiaria);
        fprintf(arquivo, "Status: %s\n", quartos[i].status);
        fprintf(arquivo, "-----------------------------------------\n");
    }

    fclose(arquivo);
    printf("\n\nDados salvos com sucesso no arquivo 'hotel_dados.txt'!\n\n");
}

void carregarDados()
{
    FILE *arquivo;
    arquivo = fopen("hotel_dados.txt", "r");

    if (arquivo == NULL)
    {
        printf("Arquivo 'hotel_dados.txt' não encontrado. Iniciando com dados vazios.\n\n");
        return;
    }

    char linha[3000];

    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strstr(linha, "================ CLIENTES ================") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && linha[0] != '\n' && linha[0] != '=')
            {
                int codigo;
                char nome[100];
                char endereco[200];
                char telefone[15];
                sscanf(linha, "Código: %d\n", &codigo);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Nome: %[^\n]\n", nome);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Endereço: %[^\n]\n", endereco);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Telefone: %[^\n]\n", telefone);

                clientes[numClientes].codigo = codigo;
                strcpy(clientes[numClientes].nome, nome);
                strcpy(clientes[numClientes].endereco, endereco);
                strcpy(clientes[numClientes].telefone, telefone);
                numClientes++;
                fgets(linha, sizeof(linha), arquivo); // Ler linha de separação
            }
        }
        else if (strstr(linha, "================ FUNCIONÁRIOS ================") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && linha[0] != '\n' && linha[0] != '=')
            {
                int codigo;
                char nome[100];
                char telefone[15];
                char cargo[50];
                float salario;
                sscanf(linha, "Código: %d\n", &codigo);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Nome: %[^\n]\n", nome);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Telefone: %[^\n]\n", telefone);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Cargo: %[^\n]\n", cargo);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Salário: R$ %f\n", &salario);

                funcionarios[numFuncionarios].codigo = codigo;
                strcpy(funcionarios[numFuncionarios].nome, nome);
                strcpy(funcionarios[numFuncionarios].telefone, telefone);
                strcpy(funcionarios[numFuncionarios].cargo, cargo);
                funcionarios[numFuncionarios].salario = salario;
                numFuncionarios++;
                fgets(linha, sizeof(linha), arquivo); // Ler linha de separação
            }
        }
        else if (strstr(linha, "================ ESTADIAS ================") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && linha[0] != '\n' && linha[0] != '=')
            {
                int codigo, codigoCliente, numeroQuarto, qntdDiarias;
                char dataEntrada[11], dataSaida[11];
                sscanf(linha, "Código da Estadia: %d\n", &codigo);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Código do Cliente: %d\n", &codigoCliente);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Número do Quarto: %d\n", &numeroQuarto);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Data de Entrada: %[^\n]\n", dataEntrada);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Data de Saída: %[^\n]\n", dataSaida);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Quantidade de Diárias: %d\n", &qntdDiarias);

                // Encontrar o cliente correspondente
                for (int i = 0; i < numClientes; i++)
                {
                    if (clientes[i].codigo == codigoCliente)
                    {
                        estadias[numEstadias].cliente = clientes[i];
                        break;
                    }
                }

                // Encontrar o quarto correspondente
                for (int i = 0; i < numQuartos; i++)
                {
                    if (quartos[i].numeroQuarto == numeroQuarto)
                    {
                        estadias[numEstadias].quarto = quartos[i];
                        strcpy(quartos[i].status, "ocupado"); // Definir o status do quarto como ocupado
                        break;
                    }
                }

                estadias[numEstadias].codigo = codigo;
                strcpy(estadias[numEstadias].dataEntrada, dataEntrada);
                strcpy(estadias[numEstadias].dataSaida, dataSaida);
                estadias[numEstadias].qntdDiarias = qntdDiarias;
                numEstadias++;
                fgets(linha, sizeof(linha), arquivo); // Ler linha de separação
            }
        }
        else if (strstr(linha, "================ QUARTOS ================") != NULL)
        {
            while (fgets(linha, sizeof(linha), arquivo) != NULL && linha[0] != '\n' && linha[0] != '=')
            {
                int numeroQuarto, qntdHospedes;
                float valorDiaria;
                char status[10];
                sscanf(linha, "Número do Quarto: %d\n", &numeroQuarto);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Quantidade de Hóspedes: %d\n", &qntdHospedes);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Valor da Diária: R$ %f\n", &valorDiaria);
                fgets(linha, sizeof(linha), arquivo);
                sscanf(linha, "Status: %[^\n]\n", status);

                quartos[numQuartos].numeroQuarto = numeroQuarto;
                quartos[numQuartos].qntdHospedes = qntdHospedes;
                quartos[numQuartos].valorDiaria = valorDiaria;
                strcpy(quartos[numQuartos].status, status);
                numQuartos++;
                fgets(linha, sizeof(linha), arquivo); // Ler linha de separação
            }
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso do arquivo 'hotel_dados.txt'!\n\n");
}

int main()
{
    int resp = -1;

    carregarDados();
    while (resp != 0)
    {
        printf("----------------------------------------\n");
        printf("\tHOTEL DESCANSO GARANTIDO");
        printf("\n----------------------------------------");

        printf("\n\n1. Cadastro de Cliente\n");
        printf("2. Cadastro de Funcionario\n");
        printf("3. Cadastro de Estadia\n");
        printf("4. Cadastro de Quarto\n");
        printf("5. Finalizar Estadia\n");
        printf("6. Pesquisar Cliente\n");
        printf("7. Pesquisar Funcionario\n");
        printf("8. Mostrar Estadia de Cliente\n");
        printf("9. Mostrar Quartos Disponiveis\n");
        printf("0. Sair\n");
        printf("\n\nSelecione uma opcao : ");
        scanf("%d", &resp);

        switch (resp)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            cadastrarFuncionario();
            break;
        case 3:
            cadastrarEstadia();
            break;
        case 4:
            cadastrarQuarto();
            break;
        case 5:
            finalizarEstadia();
            break;
        case 6:
            pesquisarCliente();
            break;
        case 7:
            pesquisarFuncionario();
            break;
        case 8:
            mostrarEstadiasCliente();
            break;
        case 9:
            exibirQuartosDisponiveis();
            break;
        case 0:
            salvarDados();
            printf("\n\nENCERRANDO...\n\n");
            break;
        default:
            printf("\n\nOpcao invalida! Tente novamente.\n\n");
            break;
        }
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 15
#define LOBBY 100
#define MENUTAM 50

typedef struct
{
  float salarioDevs;
  float horasExtra;
  float deslocamentos;
  float outrosGastos;
} Despesas;

typedef struct
{
  int day;
  int month;
  int year;
} Data;

typedef struct Projeto
{
  int codigoProjeto;
  char gerente[50];
  char cliente[50];
  Despesas despesas;
  Data dataPrevista;
  float receitaTotal;
  struct Projeto *proximo;
} Projeto;

int getDadosProjetos(Projeto *cabeca);
int menuOpcoes();
float somaGastos(Despesas gastos);
char *toLowercase(char *str, size_t len);
void projetosLucroTotal(Projeto *cabeca);
void projetosAtrasados(Projeto *cabeca);
void imprimirDadosProjetos(Projeto *cabeca);
void projetoMaiorGasto(Projeto *cabeca);
void projetoMaiorGastoHorasExtras(Projeto *cabeca);
void projetoPorGerente(Projeto *cabeca);
void projetoPorCliente(Projeto *cabeca);
void criaLinhaMenu(int tipo, int tamanho);

int main()
{
  //setlocale (LC_ALL, "");
  Projeto *cabeca;
  cabeca = (Projeto *)malloc(sizeof(Projeto));
  int opcao = -1;

  printf("\n\n");
  criaLinhaMenu(1, LOBBY);
  getDadosProjetos(cabeca);
  imprimirDadosProjetos(cabeca);
  criaLinhaMenu(2, LOBBY);
  printf("\n\n");


  while (opcao != 0)
  {
    opcao = menuOpcoes();

    switch (opcao)
    {
    case 1:
      projetosLucroTotal(cabeca);
      break;

    case 2:
      projetosAtrasados(cabeca);
      break;

    case 3:
      projetoMaiorGastoHorasExtras(cabeca);
      break;

    case 4:
      projetoMaiorGasto(cabeca);
      break;

    case 5:
      projetoPorGerente(cabeca);
      break;

    case 6:
      projetoPorCliente(cabeca);
      break;

    case 7:
      imprimirDadosProjetos(cabeca);
      break;

    case 0:
    default:
      printf("Que pena =(\n\nOBRIGADO POR USAR ESTE PROGRAMA!\n");
    }
  }

  return 0;
}

//=================================== < Informa��es dos Projetos executados no Menu  > =======================================
void criaLinhaMenu(int tipo, int tamanho){
  // Tipo 1 = linha superior.
  // Tipo 2 = linha no rodap�.
    int i;

    if (tipo == 1) {
    printf("%c",201);
    for(i=0;i<tamanho;i++)
        printf("%c",205);
    printf("%c\n",187);
    }

    if (tipo == 2) {
          printf("%c",200);
    for(i=0;i<tamanho;i++)
        printf("%c",205);
    printf("%c\n",188);
    }
}

void imprimirDadosProjetos(Projeto *cabeca)
{
  Projeto *projeto = cabeca;
  while (projeto != NULL)
  {
    printf("  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .\n");
    printf("  %d %s, %s, R$ %.2f, R$ %.2f, R$ %.2f, R$ %.2f, %02d/%02d/%d, R$ %.2f\n",
           projeto->codigoProjeto,
           projeto->gerente,
           projeto->cliente,
           projeto->despesas.salarioDevs,
           projeto->despesas.horasExtra,
           projeto->despesas.deslocamentos,
           projeto->despesas.outrosGastos,
           projeto->dataPrevista.day,
           projeto->dataPrevista.month,
           projeto->dataPrevista.year,
           projeto->receitaTotal);

    projeto = projeto->proximo;
  }
  printf("  . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .\n");
}

//=================================== < Projetos Atrasados ou Andamento > =======================================

int getDadosProjetos(Projeto *cabeca)
{
  // Example line: 01 Gerente Cliente 150.00  160.00  170.00  180.00  05/12/2023  190.00 -> Separados por tab.
  FILE *fin = fopen("projeto2.txt", "r");
  Projeto *projeto = cabeca;
  Projeto projetoTemp;

  int i = 0;
  while (fscanf(fin, "%d\t%s\t%s\t%f\t%f\t%f\t%f\t%d/%d/%d\t%f", &projetoTemp.codigoProjeto, projetoTemp.gerente, projetoTemp.cliente, &projetoTemp.despesas.salarioDevs, &projetoTemp.despesas.horasExtra, &projetoTemp.despesas.deslocamentos, &projetoTemp.despesas.outrosGastos, &projetoTemp.dataPrevista.day, &projetoTemp.dataPrevista.month, &projetoTemp.dataPrevista.year, &projetoTemp.receitaTotal) == 11 && i < MAX_SIZE)
  {

    if (i == 0)
    {
      projeto->codigoProjeto = projetoTemp.codigoProjeto;
      strcpy(projeto->gerente, projetoTemp.gerente);
      strcpy(projeto->cliente, projetoTemp.cliente);
      projeto->despesas.salarioDevs = projetoTemp.despesas.salarioDevs;
      projeto->despesas.horasExtra = projetoTemp.despesas.horasExtra;
      projeto->despesas.deslocamentos = projetoTemp.despesas.deslocamentos;
      projeto->despesas.outrosGastos = projetoTemp.despesas.outrosGastos;
      projeto->dataPrevista.day = projetoTemp.dataPrevista.day;
      projeto->dataPrevista.month = projetoTemp.dataPrevista.month;
      projeto->dataPrevista.year = projetoTemp.dataPrevista.year;
      projeto->receitaTotal = projetoTemp.receitaTotal;
      projeto->proximo = NULL;
    }
    else
    {
      projeto->proximo = (Projeto *)malloc(sizeof(Projeto));
      projeto->proximo->codigoProjeto = projetoTemp.codigoProjeto;
      strcpy(projeto->proximo->gerente, projetoTemp.gerente);
      strcpy(projeto->proximo->cliente, projetoTemp.cliente);
      projeto->proximo->despesas.salarioDevs = projetoTemp.despesas.salarioDevs;
      projeto->proximo->despesas.horasExtra = projetoTemp.despesas.horasExtra;
      projeto->proximo->despesas.deslocamentos = projetoTemp.despesas.deslocamentos;
      projeto->proximo->despesas.outrosGastos = projetoTemp.despesas.outrosGastos;
      projeto->proximo->dataPrevista.day = projetoTemp.dataPrevista.day;
      projeto->proximo->dataPrevista.month = projetoTemp.dataPrevista.month;
      projeto->proximo->dataPrevista.year = projetoTemp.dataPrevista.year;
      projeto->proximo->receitaTotal = projetoTemp.receitaTotal;
      projeto->proximo->proximo = NULL;
      projeto = projeto->proximo;
    }
    ++i;
  }

  fclose(fin);
  return i;
}

char *toLowercase(char *str, size_t len)
{
  // https://www.delftstack.com/howto/c/lower-in-c/
  char *str_l = calloc(len + 1, sizeof(char));

  for (size_t i = 0; i < len; ++i)
  {
    str_l[i] = tolower((unsigned char)str[i]);
  }
  return str_l;
}
//============================= < Design do Menu > ==================================
void criaMenuItem(int tamX , char str[]){
    int ContaLetras=0;
    int i;

    for(i=0;i<tamX;i++)
    {
        if(str[i]=='\0')
            break;
        else
            ContaLetras++;
    }
    printf("%c",186);
    printf("%s",str);

    while(ContaLetras<tamX)
    {
        printf("%c",32);
        ContaLetras++;
    }
    printf("%c\n",186);

}

//=================================== < Menu > =======================================

int menuOpcoes(){
    int menu = 0;
    do
    {
        printf("\n");
      criaLinhaMenu(1, MENUTAM);
      criaMenuItem(MENUTAM,"Selecione a opcao desejada:");
      criaMenuItem(MENUTAM,"0 - Sair");
      criaMenuItem(MENUTAM,"1 - O lucro Total");
      criaMenuItem(MENUTAM,"2 - Projetos atrasados");
      criaMenuItem(MENUTAM,"3 - Projeto com maior gasto com horas extras");
      criaMenuItem(MENUTAM,"4 - Projeto com maior gasto total");
      criaMenuItem(MENUTAM,"5 - Projeto por Gerente");
      criaMenuItem(MENUTAM,"6 - Projeto por Cliente");
      criaMenuItem(MENUTAM,"7 - Listar os dados do sistema");
      criaLinhaMenu(2, MENUTAM);

        printf("\n");
        printf("Opcao :");
        fflush(stdout);

        scanf("%d", &menu);
        fflush(stdin);

    }while ((menu != 0 && menu > 7) || menu < 0);
  return menu;

}

//=================================== < Lucros Totais > =======================================

void projetosLucroTotal(Projeto *cabeca)
{
  Projeto *projeto = cabeca;
  Data atual;
  float somaTotal = 0;
  int repeti;

  repeti=0;

do
{
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
    printf("Digite a data para verificacao (dd/mm/aaaa): "); // Na digita��o da data , tem que colocar a data com /
    fflush(stdout);
    scanf("%d/%d/%d", &atual.day, &atual.month, &atual.year);
    fflush(stdin);
    repeti++;

    if (atual.day > 31 || atual.day < 1 || atual.month > 12 || atual.month < 1 || atual.year >9999 || atual.year < 1)
    {
        printf("\nDigite uma Data valida...!\n");
    }

}while(atual.day > 31 || atual.day < 1 || atual.month > 12 || atual.month < 1 || atual.year >9999 || atual.year < 1);

  while (projeto != NULL)
  {
    if (projeto->dataPrevista.year > atual.year)
      somaTotal += projeto->receitaTotal;
    else {
        if (projeto->dataPrevista.year == atual.year) {
            if (projeto->dataPrevista.month > atual.month) somaTotal += projeto->receitaTotal;
            else if (projeto->dataPrevista.month == atual.month && projeto->dataPrevista.day >= atual.day) somaTotal += projeto->receitaTotal;
        }
    }

    projeto = projeto->proximo;
  }

  printf(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
  printf("\nA soma de lucro total dos projetos: R$ %.2f.\n", somaTotal);
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
  fflush(stdout);
}


float somaGastos(Despesas gastos)
{
  float soma = 0;

  soma += gastos.deslocamentos;
  soma += gastos.horasExtra;
  soma += gastos.outrosGastos;
  soma += gastos.salarioDevs;

  return soma;
}

//=================================== < Projetos Atrasados > =======================================

void projetosAtrasados(Projeto *cabeca)
{
  Projeto *projeto = cabeca;
  Data atual;
  int atrasados = 0;
  int repeti=0;

do
{
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
  printf("Digite a data para verificacao (dd/mm/aaaa): ");
  fflush(stdout);
  scanf("%d/%d/%d", &atual.day, &atual.month, &atual.year);
  fflush(stdin);
  printf("\n");
  repeti++;

    if (atual.day > 31 || atual.day < 1 || atual.month > 12 || atual.month < 1 || atual.year >9999 || atual.year < 1)
    {
        printf("\nDigite uma Data valida. Tente Novamente!...\n");
    }

}while(atual.day > 31 || atual.day < 1 || atual.month > 12 || atual.month < 1 || atual.year >9999 || atual.year < 1);


  while (projeto != NULL)
  {
    if (projeto->dataPrevista.year < atual.year) {
      atrasados++;
    } else {
        if (projeto->dataPrevista.year == atual.year) {
            if (projeto->dataPrevista.month < atual.month) atrasados++;
            else if (projeto->dataPrevista.month == atual.month && projeto->dataPrevista.day < atual.day) atrasados++;
        }
    }

    projeto = projeto->proximo;
  }

  printf(". . . . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
  printf("\nPara a data: %02d/%02d/%d, constam %d projetos atrasados.\n\n", atual.day, atual.month, atual.year, atrasados);
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n\n");
  fflush(stdout);
}

//=================================== < Projetos + Gastos > =======================================

void projetoMaiorGasto(Projeto *cabeca)
{
  // Deve imprimir o nome c�digo do projeto, e o nome do gerente do projeto com maior gasto total.
  Projeto *projeto = cabeca;

  char gerente[50];
  float maior = 0;
  float gastos = 0;
  int idProjeto = 0;

  while (projeto != NULL)
  {
    gastos = somaGastos(projeto->despesas);
    if (gastos > maior)
    {
      maior = gastos;
      idProjeto = projeto->codigoProjeto;
      strcpy(gerente, projeto->gerente);
    }

    projeto = projeto->proximo;
  }

  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  printf("\nO projeto com maior gasto total:\n");
  printf("\nCodigo do Projeto:....... %d\n", idProjeto);
  printf("\nGerente do Projeto:...... %s\n\n", gerente);
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  fflush(stdout);
}

//=================================== < Projetos + Gastos com Horas Extras > =======================================

void projetoMaiorGastoHorasExtras(Projeto *cabeca)
{
  // Deve imprimir o nome c�digo do projeto, e o nome do gerente do projeto com maior gasto em horas extras.
  Projeto *projeto = cabeca;

  char gerente[50];
  float maior = 0;
  int idProjeto = 0;
  float gastos = 0;

  while (projeto != NULL)
  {
    gastos = projeto->despesas.horasExtra;
    if (gastos > maior)
    {
      maior = gastos;
      idProjeto = projeto->codigoProjeto;
      strcpy(gerente, projeto->gerente);
    }
    projeto = projeto->proximo;
  }
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  printf("\nO projeto com maior gasto com horas extras:\n");
  printf("\nCodigo do Projeto:....... %d\n", idProjeto);
  printf("\nGerente do Projeto:...... %s\n\n", gerente);
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  fflush(stdout);
}

//=================================== < Projeto por Gerentes > =======================================

void projetoPorGerente(Projeto *cabeca)
{
  char gerente[50];
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  printf("\nDigite o nome do gerente: ");
  fflush(stdout);
  gets(gerente);
  fflush(stdin);
  int existe = 0;

  Projeto *projeto = cabeca;

  while (projeto != NULL)
  {
    if (strcmp(toLowercase(projeto->gerente, strlen(projeto->gerente)), toLowercase(gerente, strlen(gerente))) == 0)
    {
      printf("\nCodigo do Projeto:...... %d\n", projeto->codigoProjeto);
      printf("\nCliente:................ %s\n", projeto->cliente);
      printf("\nData:................... %d/%d/%d\n", projeto->dataPrevista.day, projeto->dataPrevista.month, projeto->dataPrevista.year);
      printf("\nLucro:.................. %.2f\n\n", projeto->receitaTotal - somaGastos(projeto->despesas));
      printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
      fflush(stdout);
      existe++;
    }
    projeto = projeto->proximo;
  }

  if (existe == 0) {
    printf("\nNao existe projeto para o gerente: %s.\n\n", gerente);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
    fflush(stdout);
  }
}

//=================================== < Projetos por Cliente > =======================================

void projetoPorCliente(Projeto *cabeca)
{
  char cliente[50];
  printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
  printf("\nDigite o nome do cliente: ");
  fflush(stdout);
  gets(cliente);
  fflush(stdin);
  int existe = 0;

  Projeto *projeto = cabeca;

  while (projeto != NULL)
  {
    if (strcmp(toLowercase(projeto->cliente, strlen(projeto->cliente)), toLowercase(cliente, strlen(cliente))) == 0)
    {
      printf("\nCodigo do Projeto:...... %d\n", projeto->codigoProjeto);
      printf("Gerente:................ %s\n", projeto->gerente);
      printf("Data:................... %d/%d/%d\n", projeto->dataPrevista.day, projeto->dataPrevista.month, projeto->dataPrevista.year);
      printf("Custo Total:............ %.2f\n\n", somaGastos(projeto->despesas));
      printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
      fflush(stdout);
    }
    projeto = projeto->proximo;
  }

  if (existe == 0) {
    printf("\nNao existe projeto para o cliente: %s.\n", cliente);
    printf("_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
    fflush(stdout);
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Diretivas de pre-processamento para função que limpa o console */
#if defined(__MINGW32__) || defined(_MSC_VER)
#define limpar_tela() system("cls")
#else
#define limpar_tela() system("clear")
#endif

/* Macros dos tamanhos da matriz e dos nomes dos jogadores*/
#define TAM_MAPA 15
#define TAM_NOME 30
#define GANHOU 25

void montar_mapas(char[][TAM_MAPA], char[][TAM_MAPA], char[][TAM_MAPA], char[][TAM_MAPA]);
void posicionar_navio(char[][TAM_MAPA], short int, char, unsigned int);
void imprimir_instrucoes(void);
void obter_nomes(char[], char[]);
void imprimir_mapa(char[][TAM_MAPA]);
void jogada_ant_p1(short int *, short int *, short int *, int);
void jogada_ant_p2(short int *, short int *, short int *, int);
int jogada(char[][TAM_MAPA], char[][TAM_MAPA], char[TAM_NOME],int *, short int *, short int *, short int *);

int main(void)
{
    char mostrar_mapa_p1[TAM_MAPA][TAM_MAPA], mostrar_mapa_p2[TAM_MAPA][TAM_MAPA]; /* Mapas que serão mostrados aos dos jogadores */
    char nav_mapa_p1[TAM_MAPA][TAM_MAPA], nav_mapa_p2[TAM_MAPA][TAM_MAPA]; /* Mapas que contem os navios */
    short int resultado_p1, resultado_p2; /* Variaveis usadas para armazenar o valor que indica se o jogador acertou ou errou a jogada */
    short int x_p1 = -1, y_p1 = -1, x_p2 = -1, y_p2 = -1; /* Variaveis que armazenam as coordenadas fornecidas pelos jogadores a cada jogada para serem informadas na proxima jogada */
    int seed1, pontos_p1 = 0, pontos_p2 = 0; /* Pontos dos jogadores */
    short int acertos_p1 = 0, acertos_p2 = 0; /* Quantidade de navios destruidos por cada jogador */
    char nome_p1[TAM_NOME], nome_p2[TAM_NOME]; /* Nome dos jogadores */

    srand((unsigned)time(NULL));

    montar_mapas(mostrar_mapa_p1, mostrar_mapa_p2, nav_mapa_p1, nav_mapa_p2);

    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 5, 'P', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 4, 'E', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 4, 'E', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 3, 'C', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 3, 'C', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 2, 'S', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 2, 'S', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p1, 2, 'S', seed1);

    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 5, 'P', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 4, 'E', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 4, 'E', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 3, 'C', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 3, 'C', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 2, 'S', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 2, 'S', seed1);
    seed1 = rand();
    posicionar_navio(nav_mapa_p2, 2, 'S', seed1);

    imprimir_mapa(nav_mapa_p1);
    imprimir_mapa(nav_mapa_p2);
    
    imprimir_instrucoes();

    obter_nomes(nome_p1, nome_p2);

    do{
        jogada_ant_p1(&x_p1, &y_p1, &resultado_p1, pontos_p1);
        resultado_p1 = jogada(mostrar_mapa_p1, nav_mapa_p1, nome_p1, &pontos_p1, &acertos_p1, &x_p1, &y_p1); /* Vez do p1 */
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
        limpar_tela();

        jogada_ant_p2(&x_p2, &y_p2, &resultado_p2, pontos_p2);
        resultado_p2 = jogada(mostrar_mapa_p2, nav_mapa_p2, nome_p2, &pontos_p2, &acertos_p2, &x_p2, &y_p2); /* Vez do p2 */
        printf("Pressione ENTER para continuar...");
        getchar();
        getchar();
        limpar_tela();
    }while(acertos_p1 < GANHOU && acertos_p2 < GANHOU);

    if(acertos_p1 > acertos_p2)
        printf("Parabens Almirante %s, o senhor destruiu a esquadra inimiga!\nPONTUACAO FINAL: %d", nome_p1, pontos_p1);
    else if(acertos_p1 < acertos_p2)
        printf("Parabens Almirante %s, o senhor destruiu a esquadra inimiga!\nPONTUACAO FINAL: %d", nome_p2, pontos_p2);
    else
        printf("EMPATE! Ambas esquadras foram destruidas.");
    return(0);
}

void montar_mapas(char mostrar_mapa_p1[][TAM_MAPA], char mostrar_mapa_p2[][TAM_MAPA], char nav_mapa_p1[][TAM_MAPA], char nav_mapa_p2[][TAM_MAPA])
{
    short int i, j;

    for(i = 0; i < TAM_MAPA; ++i)
        for(j = 0; j < TAM_MAPA; ++j)
        {
            mostrar_mapa_p1[i][j] = '~';
            mostrar_mapa_p2[i][j] = '~';
            nav_mapa_p1[i][j] = '~';
            nav_mapa_p2[i][j] = '~';
        }
}

void posicionar_navio(char mapa[][TAM_MAPA], short int tam_navio, char navio, unsigned int seed2)
{
    /* Randomizacao */
    srand((unsigned)seed2);
    short int j, ran_x, ran_y, ran_direcao,check;

    do{
        check = 0;
        ran_direcao = rand() % 2;
        if(ran_direcao == 0)
        {
          ran_x = rand() % (TAM_MAPA - tam_navio);
          ran_y = rand() % TAM_MAPA;
          for(j = 0; j < tam_navio && mapa[ran_y][j + ran_x] == '~'; ++j, ++check)
              mapa[ran_y][j + ran_x] = navio;
        }
        else
        {
          ran_x = rand() % TAM_MAPA;
          ran_y = rand() % (TAM_MAPA - tam_navio);
          for(j = 0; j < tam_navio && mapa[ran_y + j][ran_x] == '~'; ++j, ++check)
              mapa[ran_y + j][ran_x] = navio;
        }
    }while(check != tam_navio);
}

void imprimir_instrucoes(void)
{
    printf("\nBem vindo ao jogo Batalha Naval!");
    printf("\nO campo de batalha tem dimensao de %d X %d unidades.", TAM_MAPA, TAM_MAPA);
    printf("\nCada jogador tem um de cada dos seguintes navios:\nPorta-aviao - 5 espacos\nEncouracado - 4 espacos\nContratorpedeiro - 3 espacos\nSubmarino - 2 espacos\n");
    printf("\nVence quem derrubar todos os navios inimigos primeiro");
}

void obter_nomes(char nome_p1[TAM_NOME], char nome_p2[TAM_NOME])
{
    printf("\n\nNome do jogador 1 (max 30 caracteres): ");
    scanf("%[^\n]", nome_p1);
    getchar();
    printf("Nome do jogador 2 (max 30 caracteres): ");
    scanf("%[^\n]", nome_p2);
    getchar();
    printf("\n\n");
}

void imprimir_mapa(char mapa[][TAM_MAPA])
{
    short int i, j;

    for(j = 0; j < TAM_MAPA; ++j)
        printf("%d\t", j);
    printf("\n\n");
    for(i = 0; i < TAM_MAPA; ++i)
    {
        for(j = 0; j < TAM_MAPA; ++j)
            printf("%c\t", mapa[i][j]);
        printf("%d\n\n", i);
    }
}

void jogada_ant_p1(short int *x, short int *y, short int *resultado, int pontos)
{
    if(*x != -1 && *y != -1)
    {
        printf("Sua pontuacao: %d\n", pontos);
        if(*resultado == 0)
            printf("Jogada anterior: Acerto na coordenada (%d, %d)\n\n", *x, *y);
        else
            printf("Jogada anterior: Tiro ao mar na coordenada (%d, %d)\n\n", *x, *y);
    }

}

void jogada_ant_p2(short int *x, short int *y, short int *resultado, int pontos)
{
    if(*x != -1 && *y != -1)
    {
        printf("Sua pontuacao: %d\n", pontos);
        if(*resultado == 0)
            printf("Jogada anterior: Acerto na coordenada (%d, %d)\n\n", *x, *y);
        else
            printf("Jogada anterior: Tiro ao mar na coordenada (%d, %d)\n\n", *x, *y);
    }
}

int jogada(char mostrar_mapa[][TAM_MAPA], char nav_mapa[][TAM_MAPA], char nome[TAM_NOME],int *pontos, short int *acertos, short int *x_p, short int *y_p)
{
    int x, y;

    imprimir_mapa(mostrar_mapa);

    do{
        printf("\nAlmirante %s, escolha uma coordenada (X, Y) para atacar!\n", nome);
        printf("X: ");
        scanf("%d", &x);
        printf("Y: ");
        scanf("%d", &y);
        if(x < 0 || x >= TAM_MAPA || y < 0 || y >= TAM_MAPA)
            printf("\nCoordenada invalida!\n\n");
        if(nav_mapa[x][y] == '*')
            printf("\nEsta coordenada ja recebeu um ataque!\n\n");
    }while(x < 0 || x >= TAM_MAPA || y < 0 || y >= TAM_MAPA || nav_mapa[x][y] == '*');

    *x_p = x;
    *y_p = y;

    if(nav_mapa[x][y] != '~')
    {
        printf("\nACERTO!\n\n");
        mostrar_mapa[x][y] = nav_mapa[x][y];
        nav_mapa[x][y] = '*';
        *pontos += 1000;
        *acertos += 1;
        return(0);
    }
    else
    {
        printf("\nTiro ao mar...\n\n");
        nav_mapa[x][y] = '*';
        mostrar_mapa[x][y] = '*';
        *pontos -= 100;
        return(1);
    }
}

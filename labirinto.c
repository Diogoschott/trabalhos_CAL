#include <stdio.h>
#include <stdlib.h>


#define N 61




int isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 0);
}




void printMaze(int maze[N][N]){
    printf("Caminho no labirinto:\n");
    printf("%c ",'#');
    for (int j = 1; j < N+1; j++) {
        printf("%c",'#');
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%c",'#');
        for (int j = 0; j < N; j++) {
            if(maze[i][j] == 1){
                printf("%c",'#');
            }else if(maze[i][j] == 2){
                printf("%c", 'O');
            }else{
                printf(" ");
            }
            //printf("%d ", maze[i][j]);
        }
        printf("%c\n",'#');
    }
    for (int j = 0; j < N; j++) {
        printf("%c",'#');
    }
    printf(" %c\n",'#');
}

int solveMazeUtil(int maze[N][N], int x, int y) {
    // Caso Base: Se x e y chegarem no destino (N-1, N-1)
    if (x == N - 1 && y == N - 1 && maze[x][y] == 0) {
        maze[x][y] = 2; // Marca a saída como parte do caminho
        return 1;
    }

    // Verifica se a célula atual (x, y) é válida
    if (isSafe(maze, x, y)) {
        // Marca a célula atual como visitada (faz parte do caminho)
        maze[x][y] = 2;

        // Tentar mover para BAIXO
        if (solveMazeUtil(maze, x + 1, y)) return 1;

        // Tentar mover para a DIREITA
        if (solveMazeUtil(maze, x, y + 1)) return 1;

        // Tentar mover para CIMA
        if (solveMazeUtil(maze, x - 1, y)) return 1;

        // Tentar mover para a ESQUERDA
        if (solveMazeUtil(maze, x, y - 1)) return 1;

        // BACKTRACKING: Se nenhum movimento deu certo, 
        // desmarca a célula (volta para 0)
        maze[x][y] = 0;
        return 0;
    }

    return 0;
}

int solveMaze(int maze[N][N]) {
    // Iniciar a busca a partir do ponto de partida (0, 0)
    if (solveMazeUtil(maze, 0, 0) == 0) {
        printf("Nao ha solucao para o labirinto.\n");
        return 0;
    }

    // Imprimir o labirinto com o caminho '2' (pontinhos)
    printMaze(maze);
    return 1;
}






void loadMaze(int maze[N][N], char *fname){
    //gere um nesse site, cole no arquivo lab.txt ou outro
    //https://www.dcode.fr/maze-generator
    //veja quantas linhas e colunas tem e altere o valor de N
    //uma diferen�a de 1 na quantia de colunas geralmente n�o causa problema
    //pois o algoritmo aqui inclui uma borda extra
    FILE *f;
    int i, lineN = 0;
    char line[N+10];
    f = fopen(fname, "r");
    while(fgets(line, sizeof(line), f) != NULL){
        i = 0;
        if(line[0]=='0' || line[0] == '1'){
            while(line[i] != '\0'){
                maze[lineN][i] = line[i] - '0';
                i++;
                if(i>=N) break;
            }
            lineN++;
            if(lineN>=N){ break;}
        }
    }

    printf("i: %d, LineN: %d\n", i, lineN);

}

int main() {
    /*
    //1 = parede
    //0 = vazio
    //2 = caminho
    int maze[N][N] = {
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {1, 1, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
        {0, 1, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 1, 1, 1, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}
    };
    */
    int maze[N][N];

    loadMaze(maze, "lab.txt");

    if (solveMaze(maze)) {
        printf("Labirinto resolvido!\n");
    } else {
        printf("N�o foi poss�vel encontrar uma solu��o.\n");
    }

    return 0;
}


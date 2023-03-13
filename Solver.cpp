#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

typedef enum {
    ALL_STATES,
    IS_WINNING,
    SOLVE_GAME,
};
typedef struct Point {
    int player;
    int x;
    int y;
};

class Vector {
    Point* solutionsTable;
    int capacity;
    int current;
    int sizeX;
    int sizeY;
    bool isWinningSolution;
public:
    Vector(int sizeX, int sizeY) :sizeX(sizeX), sizeY(sizeY) {
        this->solutionsTable = new Point[1];
        this->capacity = 1;
        this->current = 0;
        this->isWinningSolution = false;
    }
    bool getIsWinningSolution() {
        return isWinningSolution;
    }
    void setIsWinningSolution(bool flag) {
        this->isWinningSolution = flag;
    }
    void addElement(Point* object) {
        if (current == capacity) {
            Point* temp = new Point[4 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = solutionsTable[i];
            }
            capacity *= 2;
            this->solutionsTable = temp;
        }
        solutionsTable[current] = *object;
        current++;
    }
    void printOnlyWinning(int** table) {
        printf("1\n");
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if (solutionsTable[current - 1].x == j && solutionsTable[current - 1].y == i) printf("%d ", solutionsTable[current - 1].player);
                else printf("%d ", table[j][i]);
            }
            printf("\n");
        }
        printf("\n");

    }
    void printAllStates(int** table) {
        printf("%d\n", this->current);
        for (int k = 0; k < current; k++) {
            for (int i = 0; i < sizeY; i++) {
                for (int j = 0; j < sizeX; j++) {
                    if (solutionsTable[k].x == j && solutionsTable[k].y == i) printf("%d ", solutionsTable[k].player);
                    else printf("%d ", table[j][i]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    ~Vector() {
        delete[] solutionsTable;
    }
};

int compareCharTables(const char commands[][35], char command[35]) {
    for (int i = 0; i < 3; i++) {
        if (strcmp(commands[i], command) == 0) return i;
    }
    return -1;
}

int** readInputTable(int sizeX, int sizeY) {
    int** table = new int* [sizeX];
    for (int k = 0; k < sizeX; k++) {
        table[k] = new int[sizeY];
    }
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            scanf("%d", &table[j][i]);
        }
    }
    return table;
}
int checkWinColumns(int** board, int winningNumber, int sizeX, int sizeY) {
    int number1 = 0, number2 = 0;
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (board[i][j] == 1)  number1++;
            else number1 = 0;

            if (board[i][j] == 2)  number2++;
            else number2 = 0;

            if (number1 == winningNumber) return 1;
            if (number2 == winningNumber) return 2;
        }
        number1 = 0; number2 = 0;
    }
    return 0;
}
int checkWinRows(int** board, int winningNumber, int sizeX, int sizeY) {
    int number1 = 0, number2 = 0;
    for (int i = 0; i < sizeY; i++) {
        for (int j = 0; j < sizeX; j++) {
            if (board[j][i] == 1)  number1++;
            else number1 = 0;

            if (board[j][i] == 2)  number2++;
            else number2 = 0;

            if (number1 == winningNumber) return 1;
            if (number2 == winningNumber) return 2;
        }
        number1 = 0; number2 = 0;
    }
    return 0;
}
int checkWinDiagonal(int** board, int winningNumber, int sizeX, int sizeY) {
    int number1 = 0, number2 = 0;
    for (int i = 0; i <= sizeY - winningNumber; i++) {
        for (int j = 0; j <= sizeX - winningNumber; j++) {
            for (int k = 0; k < winningNumber; k++) {
                if (board[j + k][i + k] == 1) number1++;
                else number1 = 0;

                if (board[j + k][i + k] == 2) number2++;
                else number2 = 0;

                if (number1 == winningNumber) return 1;
                if (number2 == winningNumber) return 2;
            }
            number1 = 0; number2 = 0;
        }
        number1 = 0; number2 = 0;
    }
    return 0;
}
int checkWinAntiDiagonal(int** board, int winningNumber, int sizeX, int sizeY) {
    int number1 = 0, number2 = 0;
    for (int i = sizeY - winningNumber; i >= 0; i--) {
        for (int j = winningNumber - 1; j < sizeX; j++) {
            for (int k = 0; k < winningNumber; k++) {
                if (board[j - k][i + k] == 1) number1++;
                else number1 = 0;

                if (board[j - k][i + k] == 2) number2++;
                else number2 = 0;

                if (number1 == winningNumber) return 1;
                if (number2 == winningNumber) return 2;
            }
            number1 = 0; number2 = 0;
        }
        number1 = 0; number2 = 0;}
    return 0;
}
int isPositionWinning(int** board, int winningNumber, int sizeX, int sizeY) {
    int columns = checkWinColumns(board, winningNumber, sizeX, sizeY);
    int rows = checkWinRows(board, winningNumber, sizeX, sizeY);
    int diagonal = checkWinDiagonal(board, winningNumber, sizeX, sizeY);
    int antiDiagonal = checkWinAntiDiagonal(board, winningNumber, sizeX, sizeY);
    if (columns == 1 || rows == 1 || diagonal == 1 || antiDiagonal == 1) return 20;
    if (columns == 2 || rows == 2 || diagonal == 2 || antiDiagonal == 2) return -20;
    return 0;
}
void findAllStates(int sizeX, int sizeY, int player, int winningNumber, int** table, Vector* vector, bool cut) {
    int x = isPositionWinning(table, winningNumber, sizeX, sizeY);
    if (x == 20 || x == -20);
    else {
        bool flag = false;
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                if (table[j][i] == 0) {
                    Point point = { player,j,i};
                    vector->addElement(&point);
                    if (cut) {
                        table[j][i] = player;
                        int y = isPositionWinning(table, winningNumber, sizeX, sizeY);
                        table[j][i] = 0;
                        if ((y == 20 && player == 1) || (y == -20 && player == 2)) {
                            flag = true;
                            vector->setIsWinningSolution(true);
                        }
                    }
                }
                if (flag) break;
            }
            if (flag) break;
        }
    }
}

int max(int a, int b) {
    if (a >= b) return a;
    else return b;
}
int min(int a, int b) {
    if (a > b) return b;
    else return a;
}
bool isDraw(int** board, int sizeX, int sizeY) {
    for (int i = 0; i < sizeX; i++) {
        for (int j = 0; j < sizeY; j++) {
            if (board[i][j] == 0) return false;
        }
    }
    return true;
}
int minimax(int** board, int sizeX, int sizeY, int winningNumber, int depth, bool isMax, bool* bonus1) {
    int score = isPositionWinning(board, winningNumber, sizeX, sizeY);

    if (score == 20) return score;
    if (score == -20) return score;
    if (isDraw(board, sizeX, sizeY)) return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                if (board[i][j] == 0) {
                    board[i][j] = 1;
                    best = max(best, minimax(board, sizeX, sizeY, winningNumber, depth + 1, !isMax, bonus1));
                    board[i][j] = 0;
                    if (best == 20) return best;
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;
        for (int i = 0; i < sizeX; i++) {
            for (int j = 0; j < sizeY; j++) {
                if (board[i][j] == 0) {

                    board[i][j] = 2;
                    best = min(best, minimax(board, sizeX, sizeY, winningNumber, depth + 1, !isMax, bonus1));
                    board[i][j] = 0;
                    if (best == -20) return best;
                }
            }
        }
        return best;
    }
    return 0;
}

void solveTheGame(int** board, int winningNumber, int sizeX, int sizeY, int player) {
    if (isPositionWinning(board, winningNumber, sizeX, sizeY) == 20) printf("FIRST_PLAYER_WINS\n");
    else if (isPositionWinning(board, winningNumber, sizeX, sizeY) == -20) printf("SECOND_PLAYER_WINS\n");
    else if (isDraw(board, sizeX, sizeY)) printf("BOTH_PLAYERS_TIE\n");
    else {
        int bestVal = -1000;
        int moveVal = 0;
        bool bonus1 = false;

        if (player == 2) moveVal = minimax(board, sizeX, sizeY, winningNumber, 0, false, &bonus1);
        else moveVal = minimax(board, sizeX, sizeY, winningNumber, 0, true, &bonus1);

        if (moveVal > bestVal) {
            bestVal = moveVal;
        }
        if (bestVal > 0) printf("FIRST_PLAYER_WINS\n");
        else if (bestVal < 0) printf("SECOND_PLAYER_WINS\n");
        else printf("BOTH_PLAYERS_TIE\n");
    }
}

void makeAction(int sizeX, int sizeY, int winningNumber, int player, int commandNumber, int** array) {
    Vector* vector = new Vector(sizeX, sizeY);
    switch (commandNumber) {
    case 0:
        findAllStates(sizeX, sizeY, player, winningNumber, array, vector, false);
        vector->printAllStates(array);
        vector->~Vector();
        break;
    case 1:
        findAllStates(sizeX, sizeY, player, winningNumber, array, vector, true);

        if (vector->getIsWinningSolution()) vector->printOnlyWinning(array);
        else vector->printAllStates(array);
        vector->~Vector();
        break;
    case 2:
        solveTheGame(array, winningNumber, sizeX, sizeY, player);
        break;
    }
}
bool readInput(int* sizeX, int* sizeY, int* winningNumber, int* player, int* commandNumber) {
    const char commands[][35] = { "GEN_ALL_POS_MOV","GEN_ALL_POS_MOV_CUT_IF_GAME_OVER","SOLVE_GAME_STATE"};
    char command[35];

    scanf("%s", command);
    if (feof(stdin) != 0) return false;

    *commandNumber = compareCharTables(commands, command);
    scanf("%d %d %d %d", sizeY, sizeX, winningNumber, player);
    return true;
}

int main() {
    int sizeX = 0, sizeY = 0, winningNumber = 0, player = 0, commandNumber = 0;
    while (readInput(&sizeX, &sizeY, &winningNumber, &player, &commandNumber)) {
        int** array = readInputTable(sizeX, sizeY);
        makeAction(sizeX, sizeY, winningNumber, player, commandNumber, array);
    }
    return 0;
}
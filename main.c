#include <stdbool.h>
#include <stdio.h>

typedef enum { BLANK = ' ', X = 'X', O = 'O' } State;
typedef State Board_t[3][3];
typedef struct {
    int x;
    int y;
} Tuple;

#define BOT O
#define PLAYER X

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
inline int bool_to_int(bool a) { return a ? 1 : -1; }

void print_board(Board_t board) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            printf("%c", board[x][y]);
            if (x < 2) {
                printf(" | ");
            }
        }
        if (y < 2) {
            printf("\n--+---+--\n");
        }
    }
    printf("\n\n");
}

void get_input(int *x, int *y, const Board_t *board) {
    *x = -1;
    *y = -1;
    printf("Enter x and y (0-2):\n");
    while (true) {
        printf(">>");
        if (scanf("%d %d", x, y) != 2) {
            while (getchar() != '\n')
                ;
            continue;
        }
        if (!(*x >= 0 && *x < 3 && *y >= 0 && *y < 3)) {
            printf("Invalid input invalid.\n");
        } else if (board && (*board)[*x][*y] != BLANK) {
            printf("Cell already in use. \n");
        } else {
            printf("\n");
            return;
        }
    }
}

bool is_full(Board_t board) {
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[x][y] == BLANK) {
                return false;
            }
        }
    }
    return true;
}

State winner(Board_t board) {
    // horizontal
    for (int y = 0; y < 3; y++) {
        if (board[0][y] != BLANK && board[0][y] == board[1][y] &&
            board[1][y] == board[2][y]) {
            return board[1][y];
        }
    }

    // vertical
    for (int x = 0; x < 3; x++) {
        if (board[x][0] != BLANK && board[x][0] == board[x][1] &&
            board[x][1] == board[x][2]) {
            return board[x][1];
        }
    }

    // diagonal
    if (board[1][1] != BLANK && board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        return board[1][1];
    }
    if (board[1][1] != BLANK && board[2][0] == board[1][1] &&
        board[1][1] == board[0][2]) {
        return board[1][1];
    }

    return BLANK;
}

int available_moves(const Board_t board, Tuple result[9]) {
    int count = 0;
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            if (board[x][y] == BLANK) {
                result[count] = (Tuple){.x = x, .y = y};
                count++;
            }
        }
    }
    if (count < 9) {
        result[count] = (Tuple){.x = -1, .y = -1};
    }
    return count;
}

int minimax(Board_t board, int depth, bool maximizing) {
    State won = winner(board);

    if (won == BOT)
        return 15 + depth;
    if (won == PLAYER)
        return -15 - depth;
    if (is_full(board) || depth == 0)
        return 0;

    Tuple moves[9];
    available_moves(board, moves);

    if (maximizing) {
        int value = -1000;

        for (int i = 0; i < 9 && moves[i].x != -1; i++) {
            Tuple move = moves[i];
            board[move.x][move.y] = BOT;
            value = max(value, minimax(board, depth - 1, false));
            board[move.x][move.y] = BLANK; // I hope it was blank
        }
        return value;
    } else {
        int value = 1000;
        for (int i = 0; i < 9 && moves[i].x != -1; i++) {
            Tuple move = moves[i];
            board[move.x][move.y] = PLAYER;
            value = min(value, minimax(board, depth - 1, true));
            board[move.x][move.y] = BLANK; // I hope it was blank
        }
        return value;
    }
}

Tuple bot_play(Board_t board) {
    Tuple moves[9];
    int available = available_moves(board, moves);

    Tuple best = moves[0];
    int best_score = -10000;

    for (int i = 0; i < 9 && moves[i].x != -1; i++) {
        Tuple move = moves[i];
        board[move.x][move.y] = BOT;
        int score = minimax(board, 10, false);
        board[move.x][move.y] = BLANK;

        if (score > best_score) {
            best_score = score;
            best = moves[i];
        }
    }

    return best;
}

int main() {
    State player = X;
    State board[3][3];

    for (size_t x = 0; x < 3; x++) {
        for (size_t y = 0; y < 3; y++) {
            board[x][y] = BLANK;
        }
    }

    int x;
    int y;
    print_board(board);
    while (true) {
        if (player == PLAYER) {
            get_input(&x, &y, &board);
            board[x][y] = PLAYER;
            player = BOT;
        } else {
            Tuple play = bot_play(board);
            board[play.x][play.y] = BOT;
            player = PLAYER;
        }

        print_board(board);
        State won = winner(board);

        if (won != BLANK) {
            printf("%c won!!\n", won);
            return 0;
        } else if (is_full(board)) {
            printf("It's a tie...\n");
            return 0;
        }
    }

    return 0;
}
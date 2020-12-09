// # Program which implements a chess game
// # Written by Ahmet Karatas
// # In 2020/2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "chess.h" // The reason we need this is because 
// we need to put the function declarations at the top. However
// it needs to 
// The size of the starting grid

bool isValidMove(int row1, int col1, int row2, int col2) {
    int piece = chessboard[row1][col1].piece;
    if (piece == PAWN) {
        return canPawnMove(row1, col1, row2, col2);
    }
    return false;
    // } else if (piece == ROOK) {
    //     return canRookMove();
    // } else if (piece == 3) {
    //     return canKnightMove();
    // } else if (piece == 4) {
    //     return canBishopMove();
    // } else if (piece == 5) {
    //     return canQueenMove();
    // } else if (piece == 6) {
    //     return canKingMove();
    // } else {
    //     return 0;
    // }
}

bool canPawnMove(int row1, int col1, int row2, int col2) {
    // if the pawn 
    int colour = chessboard[row1][col1].colour;
    int hasPieceMoved = chessboard[row1][col1].hasPieceMoved;
    int i = 0;
    if (colour == WHITE) i = 1;
    else if (colour == BLACK) i = -1;

    // if dest is empty and it's the same column
    if (chessboard[row1][col1].canEmpassant) {                      // if it can empassant
        // for black
        if (row2 == row1 + i) {
            if (col2 == col1 + i || col2 == col1 - i) {
                return true;
            }
        }
        return false;
    } else if (chessboard[row2][col2].piece == NONE && col1 == col2) { 
        if (abs(row2 - row1) == 1) {                                 // if the pawn wants to move up 1 position
            chessboard[row1][col1].canEmpassant = NO;
            return true;
        } else if (abs(row2 - row1) == 2 && !hasPieceMoved) {       // if the pawn wnats to move up 2 positions
            if (chessboard[row1 + i][col1].piece == NONE) {
                // check if it's adjacent squares are pawns which can empassant
                // if the piece to its right is a pawn of the opposite colour
                if (colour == WHITE) {
                    if (col2 < SIZE - 1 && chessboard[row2][col2 + 1].colour == BLACK) {
                        chessboard[row2][col2 + 1].canEmpassant = YES;
                    } else if (col2 > 0 && chessboard[row2][col2 - 1].colour == BLACK) {
                        chessboard[row2][col2 - 1].canEmpassant = YES;
                    }
                } else if (colour == BLACK) {
                    if (col2 < SIZE - 1 && chessboard[row2][col2 + 1].colour == WHITE) {
                        chessboard[row2][col2 + 1].canEmpassant = YES;
                    } else if (col2 > 0 && chessboard[row2][col2 - 1].colour == WHITE) {
                        chessboard[row2][col2 - 1].canEmpassant = YES;
                    }
                }
                // if the piece to its left is a pawn of the opposite colour
                return true;
            }
        }
        return false;
    } else if (row2 == row1 + i && col2 == col1 + i) {             // if it wants to kill an opponent
        return true;
    } else if (row2 == row1 + i && col2 == col1 - i) {             // if it wants to kill an opponent
        return true;
    } else {
        return false;
    }
    return false;
}
bool canRookMove(int row1, int col1, int row2, int col2) {
    // if the rook wants to travel vertically
    int row, col;
    if (col1 == col2) {     // if vertical
        if (row2 > row1) {
            for (row = row1; row < row2; row++) {
                if (chessboard[row][col1].piece != NONE) {                        // if any of the positions before destination 
                    return false;                                           // is not empty, then return false
                }       
            }
            return true;
        } else if (row2 < row1) {
            for (row = row2; row > row1; row--) {
                if (chessboard[row][col1].piece != NONE) {                        // if any of the positions before destination 
                    return false;                                           // is not empty, then return false
                }       
            }
            return true;
        }
    } else if (row1 == row2) {  // if horizontal
        if (col2 > col1) {
            for (col = col1; col < col2; col++) {
                if (chessboard[row1][col].piece != NONE) {
                    return false;
                }
            }
            return true;
        } else if (col2 < col1) {
            for (col = col1; col > col2; col++) {
                if (chessboard[row1][col].piece != NONE) {
                    return false;
                }
            }
            return true;
        }
    } else if (chessboard[row2][col2].piece == KING && chessboard[row2][col2].piece) {
        return true;
    }
    return true;
}
// Initialise the entire board positions to zero's and the rest of the struct
void initialiseBoard() {
    printf("Position: %d\n", chessboard[0][0].piece);
    int matrix[SIZE][SIZE] = {
        {2,3,4,5,6,4,3,2},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
    };
    
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            chessboard[row][col].piece = matrix[row][col];
            if (row == 0 || row == 1) {
                chessboard[row][col].colour = WHITE;
            } else if (row == SIZE - 2 || row == SIZE - 1) {
                chessboard[row][col].colour = BLACK;
            } else {
                chessboard[row][col].colour = ZERO;
            }
            chessboard[row][col].hasPieceMoved = NO;
            chessboard[row][col].canEmpassant = NO;
        }
    }
    // memcpy(chessboard, initial_board, SIZE * SIZE * sizeof(struct board));
}
// prints chessboard for debug
void print_debug_chessboard() {
    int row, col;
    printf("    A    B    C    D    E    F    G    H\n");
    printf("   ---------------------------------------\n");
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (col == 0) {
                printf("%d| ", row + 1);
            }
            printf("%d->%d ", chessboard[row][col].colour, chessboard[row][col].piece);
        }
        printf("\n");
    }
}
// void diagonal(int row, int col) {
//     int i, topRight = 0, topLeft = 0, bottomRight = 0, bottomLeft = 0;
//     // top left
//     printf("Row, col: %d %d\n", row, col);
//     for (i = 1; row - i >= 0 && col - i >= 0; i++) {
//         if (chessboard[row - i][col - i].piece != 0) {
//             printf("Row, col: %d %d\n", row - i, col - i);        
//             topLeft = 1;
//            printf("topLeft: %d\n", topLeft);
//            break;
//         }
//     }
//     // top right
//     for (i = 1; row - i >= 0 && col + i >= 0; i++) {
//         if (chessboard[row - i][col + i].piece != 0) {
//             // bottom right diagonal can attack a piece
//             topRight = 1;
//             printf("topRight: %d\n", topRight);
//             break;

//         }
//     }
//     // bottom left
//     for (i = 1; row + i >= 0 && col - i >= 0; i++) {
//         if (chessboard[row + i][col - i].piece != 0) { 
//             // bottom right diagonal can attack a piece
//             bottomLeft = 1;
//             printf("bottomLeft: %d\n", bottomLeft);
//             break;

//         }
//     }
//     // bottom right
//     for (i = 1; row + i >= 0 && col + i >= 0; i++) {
//         if (chessboard[row + i][col + i].piece != 0) {
//             // bottom right diagonal can attack a piece
//             bottomRight = 1;
//             printf("bottomRight: %d\n", bottomRight);
//             break;
//         }
//     }

// }

char* findPiece(int num) {
    if (num == 0) {
        return "none";
    } else if (num == 1) {
        return "pawn";
    } else if (num == 2) {
        return "rook";
    } else if (num == 3) {
        return "knight";
    } else if (num == 4) {
        return "bishop";
    } else if (num == 5) {
        return "queen";
    } else if (num == 6) {
        return "king";
    }
    return "none";
}

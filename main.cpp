#include <cstdlib>
#include <stdlib.h>
#include <math.h>
#include <random>
#include "vexa/vexa.hpp"

int fps = 60;
float frametime = 1000.0f / fps;

typedef enum {I, L, J, O, T, S, Z} PieceType;

typedef struct {
        int column;
        int row;
    } Block;

typedef struct {
    PieceType type;
    Block blocks[4];
    int rot;
    bool active;
} Piece;

Piece current_piece;

void place_piece(PieceType piece_type, char grid[20][10]){
    if(piece_type == I){
        Block block1;
        block1.row = 0;
        block1.column = 3;
        
        Block block2;
        block2.row = 0;
        block2.column = 4;
        
        Block block3;
        block3.row = 0;
        block3.column = 5;
        
        Block block4;
        block4.row = 0;
        block4.column = 6;

        current_piece.type = I;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;
    }

    else if(piece_type == L){
        Block block1;
        block1.row = 0;
        block1.column = 4;
        
        Block block2;
        block2.row = 0;
        block2.column = 5;
        
        Block block3;
        block3.row = 0;
        block3.column = 6;
        
        Block block4;
        block4.row = 1;
        block4.column = 4;

        current_piece.type = L;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;
    }

    else if(piece_type == J){
        Block block1;
        block1.row = 0;
        block1.column = 4;
        
        Block block2;
        block2.row = 0;
        block2.column = 5;
        
        Block block3;
        block3.row = 0;
        block3.column = 6;
        
        Block block4;
        block4.row = 1;
        block4.column = 6;

        current_piece.type = J;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;
    }

    else if(piece_type == O){
        Block block1;
        block1.row = 0;
        block1.column = 4;
        
        Block block2;
        block2.row = 0;
        block2.column = 5;
        
        Block block3;
        block3.row = 1;
        block3.column = 4;
        
        Block block4;
        block4.row = 1;
        block4.column = 5;

        current_piece.type = O;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;
    }

    else if(piece_type == T){
        Block block1;
        block1.row = 0;
        block1.column = 4;
        
        Block block2;
        block2.row = 0;
        block2.column = 5;
        
        Block block3;
        block3.row = 0;
        block3.column = 6;
        
        Block block4;
        block4.row = 1;
        block4.column = 5;

        current_piece.type = T;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;
    }

    else if(piece_type == S){
        Block block1;
        block1.row = 0;
        block1.column = 5;
        
        Block block2;
        block2.row = 0;
        block2.column = 6;
        
        Block block3;
        block3.row = 1;
        block3.column = 4;
        
        Block block4;
        block4.row = 1;
        block4.column = 5;

        current_piece.type = S;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;
    }

    else if(piece_type == Z){
        Block block1;
        block1.row = 0;
        block1.column = 4;
        
        Block block2;
        block2.row = 0;
        block2.column = 5;
        
        Block block3;
        block3.row = 1;
        block3.column = 5;
        
        Block block4;
        block4.row = 1;
        block4.column = 6;

        current_piece.type = Z;
        current_piece.rot = 0;
        current_piece.blocks[0] = block1;
        current_piece.blocks[1] = block2;
        current_piece.blocks[2] = block3;
        current_piece.blocks[3] = block4;

    }

    current_piece.active = true;

    for (int block = 0; block < 4; block++){
        if (grid[current_piece.blocks[block].row][current_piece.blocks[block].column] == 1){
            vexa::Engine::Close();
            exit(0);
        }
        grid[current_piece.blocks[block].row][current_piece.blocks[block].column] = 1;
    }
}

void rotate(char grid[20][10], bool clockwise){
    if (!current_piece.active){return;}
    bool success = false;
    int rot = current_piece.rot;
    int target_rot;
    int degrees;
    PieceType type = current_piece.type;
    if (type == I || type == S || type == Z){degrees = 180;}
    else {degrees = 90;}

    if (clockwise){target_rot = rot + degrees;}
    else {target_rot = rot - degrees;}

    if (target_rot == -90){target_rot = 270;}
    else if (target_rot == -180){target_rot = 180;}
    else if (target_rot == 360){target_rot = 0;}
    
    if (current_piece.type == I){
        if (target_rot == 180 && current_piece.blocks[0].row > 1 && current_piece.blocks[3].row < 19){
            if (grid[current_piece.blocks[2].row + 1][current_piece.blocks[2].column] == 0 && grid[current_piece.blocks[2].row - 1][current_piece.blocks[2].column] == 0 && grid[current_piece.blocks[2].row - 2][current_piece.blocks[2].column] == 0){
                
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                current_piece.blocks[3].row += 1; current_piece.blocks[3].column -= 1;
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 0;
                current_piece.blocks[1].row -= 1; current_piece.blocks[1].column += 1;
                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 1;

                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                current_piece.blocks[0].row -= 2; current_piece.blocks[0].column += 2;
                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;
                
                success = true;
            }
        }
        else if (target_rot == 0 && current_piece.blocks[0].column < 9 && current_piece.blocks[0].column > 1){
            if (grid[current_piece.blocks[2].row][current_piece.blocks[2].column + 1] == 0 && grid[current_piece.blocks[2].row][current_piece.blocks[2].column - 1] == 0 && grid[current_piece.blocks[2].row][current_piece.blocks[2].column - 2] == 0){
                
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                current_piece.blocks[3].row -= 1; current_piece.blocks[3].column += 1;
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 0;
                current_piece.blocks[1].row += 1; current_piece.blocks[1].column -= 1;
                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 1;

                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                current_piece.blocks[0].row += 2; current_piece.blocks[0].column -= 2;
                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;
                
                success = true;
            }
        }
    }
    else if (current_piece.type == S){
        if (target_rot == 180){
            if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column] == 0){
                
                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                current_piece.blocks[2].column += 2;
                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 0;
                current_piece.blocks[1].row -= 1; current_piece.blocks[1].column -= 1;
                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 1;

                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                current_piece.blocks[3].row -= 1; current_piece.blocks[3].column += 1;
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;
                
                success = true;
            }
        }
        else if (target_rot == 0 && current_piece.blocks[1].column > 0){
            if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0){
                
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                current_piece.blocks[3].row += 1; current_piece.blocks[3].column -= 1;
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 0;
                current_piece.blocks[1].row += 1; current_piece.blocks[1].column += 1;
                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 1;

                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                current_piece.blocks[2].column -= 2;
                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                success = true;
            }
        }
    }

    else if (current_piece.type == Z){
        if (target_rot == 180){
            if (grid[current_piece.blocks[0].row][current_piece.blocks[0].column + 2] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 2] == 0){
                
                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 2;
                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 0;
                current_piece.blocks[1].column += 1;
                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 1;

                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                current_piece.blocks[2].row -= 1;
                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                current_piece.blocks[3].column -= 1;
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;
                
                success = true;
            }
        }
        else if (target_rot == 0 && current_piece.blocks[2].column > 0){
            if (grid[current_piece.blocks[2].row][current_piece.blocks[2].column - 1] == 0 && grid[current_piece.blocks[2].row + 1][current_piece.blocks[2].column + 1] == 0){
                
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                current_piece.blocks[3].column += 1;
                grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                current_piece.blocks[2].row += 1;
                grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 0;
                current_piece.blocks[1].column -= 1;
                grid[current_piece.blocks[1].row][current_piece.blocks[1].column] = 1;

                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 2;
                grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                success = true;
            }
        }
    }

    else if (current_piece.type == T){
        if (clockwise){
            if (target_rot == 90 && current_piece.blocks[2].row > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 1; current_piece.blocks[3].column -= 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;
                    
                    success = true;
                }
            }

            else if (target_rot == 180 && current_piece.blocks[2].column < 9){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 1; current_piece.blocks[3].column += 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 270 && current_piece.blocks[2].row < 19){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 1; current_piece.blocks[3].column += 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 0 && current_piece.blocks[2].column > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 1; current_piece.blocks[3].column -= 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }
        }

        else if (!clockwise){
            if (target_rot == 90 && current_piece.blocks[2].row < 19){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 1; current_piece.blocks[3].column -= 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;
                    
                    success = true;
                }
            }

            else if (target_rot == 180 && current_piece.blocks[2].column > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 1; current_piece.blocks[3].column -= 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 270 && current_piece.blocks[2].row > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 1; current_piece.blocks[3].column += 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 0 && current_piece.blocks[2].column < 9){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 1; current_piece.blocks[3].column += 1;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    success = true;
                }
            }
        }
    }

    else if (current_piece.type == L){
        if (clockwise){
            if (target_rot == 90 && current_piece.blocks[2].row > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;
                    
                    success = true;
                }
            }

            else if (target_rot == 180 && current_piece.blocks[2].column < 9 && current_piece.blocks[2].column > 0){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 270 && current_piece.blocks[0].row < 19){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 0 && current_piece.blocks[2].column > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }
        }

        else if (!clockwise){
            if (target_rot == 90 && current_piece.blocks[3].row < 18){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 2] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;
                    
                    success = true;
                }
            }

            else if (target_rot == 180 && current_piece.blocks[2].column > 0){
                if (grid[current_piece.blocks[0].row - 2][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 270){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 2] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 0 && current_piece.blocks[2].column < 9){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 2][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }
        }   
    }


    else if (current_piece.type == J){
        if (clockwise){
            if (target_rot == 90 && current_piece.blocks[2].row > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;
                    
                    success = true;
                }
            }

            else if (target_rot == 180 && current_piece.blocks[0].column < 9){
                if (grid[current_piece.blocks[0].row][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 270 && current_piece.blocks[0].row < 19){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 0 && current_piece.blocks[2].column > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }
        }

        else if (!clockwise){
            if (target_rot == 90 && current_piece.blocks[2].row < 19){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 2] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;
                    
                    success = true;
                }
            }

            else if (target_rot == 180 && current_piece.blocks[0].column > 0){
                if (grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row - 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row - 2][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row -= 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row += 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 270 && current_piece.blocks[0].row > 0){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 2][current_piece.blocks[0].column - 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column += 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].row -= 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column -= 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }

            else if (target_rot == 0 && current_piece.blocks[2].column < 9){
                if (grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column - 1] == 0 && grid[current_piece.blocks[0].row + 1][current_piece.blocks[0].column + 1] == 0 && grid[current_piece.blocks[0].row + 2][current_piece.blocks[0].column + 1] == 0){
                    
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 0;
                    current_piece.blocks[0].row += 1; current_piece.blocks[0].column -= 1;
                    grid[current_piece.blocks[0].row][current_piece.blocks[0].column] = 1;

                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 0;
                    current_piece.blocks[3].column += 2;
                    grid[current_piece.blocks[3].row][current_piece.blocks[3].column] = 1;

                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 0;
                    current_piece.blocks[2].row -= 1; current_piece.blocks[2].column += 1;
                    grid[current_piece.blocks[2].row][current_piece.blocks[2].column] = 1;

                    success = true;
                }
            }
        }
    }


    if (success){current_piece.rot = target_rot;}
}

void physics(char grid[20][10]){
    if (current_piece.active == false){return;}
    for (int block = 0; block < 4; block++){
        // if touches floor
        if (current_piece.blocks[block].row == 19){
            current_piece.active = false;
            return;}
        // if touches another block
        else if (grid[current_piece.blocks[block].row + 1][current_piece.blocks[block].column] == 1){
            bool sibling = false;
            for (int inner_block = 0; inner_block < 4; inner_block++){
                if (current_piece.blocks[block].row + 1 == current_piece.blocks[inner_block].row && current_piece.blocks[block].column == current_piece.blocks[inner_block].column){
                    sibling = true;
                }
            }
            if (!sibling){
                current_piece.active = false;
                return;
            }
        }
    }
    for (int block = 0; block < 4; block++){
        current_piece.blocks[block].row += 1;
        grid[current_piece.blocks[block].row][current_piece.blocks[block].column] = 1;

        bool sibling = false;
        for (int inner_block = 0; inner_block < 4; inner_block++){
            if (current_piece.blocks[block].row > 0){
                if (current_piece.blocks[block].row - 1 == current_piece.blocks[inner_block].row && current_piece.blocks[block].column == current_piece.blocks[inner_block].column){
                    sibling = true;
                }
            }
        }
        if (!sibling){
        grid[current_piece.blocks[block].row - 1][current_piece.blocks[block].column] = 0;
        }
        
    }
}

void right(char grid[20][10]){
    if (current_piece.active == false){return;}
    for (int block = 0; block < 4; block++){
        // if touches wall
        if (current_piece.blocks[block].column == 9){
            return;}
        // if touches another block
        else if (grid[current_piece.blocks[block].row][current_piece.blocks[block].column + 1] == 1){
            bool sibling = false;
            for (int inner_block = 0; inner_block < 4; inner_block++){
                if (current_piece.blocks[block].row == current_piece.blocks[inner_block].row && current_piece.blocks[block].column + 1 == current_piece.blocks[inner_block].column){
                    sibling = true;
                }
            }
            if (!sibling){
                return;
            }
        }
    }
    for (int block = 0; block < 4; block++){
        current_piece.blocks[block].column += 1;
        grid[current_piece.blocks[block].row][current_piece.blocks[block].column] = 1;

        bool sibling = false;
        for (int inner_block = 0; inner_block < 4; inner_block++){
            if (current_piece.blocks[block].column > 0){
                if (current_piece.blocks[block].row == current_piece.blocks[inner_block].row && current_piece.blocks[block].column - 1 == current_piece.blocks[inner_block].column){
                    sibling = true;
                }
            }
        }
        if (!sibling){
        grid[current_piece.blocks[block].row][current_piece.blocks[block].column - 1] = 0;
        }
        
    }
}

void left(char grid[20][10]){
    if (current_piece.active == false){return;}
    for (int block = 0; block < 4; block++){
        // if touches wall
        if (current_piece.blocks[block].column == 0){
            return;}
        // if touches another block
        else if (grid[current_piece.blocks[block].row][current_piece.blocks[block].column - 1] == 1){
            bool sibling = false;
            for (int inner_block = 0; inner_block < 4; inner_block++){
                if (current_piece.blocks[block].row == current_piece.blocks[inner_block].row && current_piece.blocks[block].column - 1 == current_piece.blocks[inner_block].column){
                    sibling = true;
                }
            }
            if (!sibling){
                return;
            }
        }
    }
    for (int block = 0; block < 4; block++){
        current_piece.blocks[block].column -= 1;
        grid[current_piece.blocks[block].row][current_piece.blocks[block].column] = 1;

        bool sibling = false;
        for (int inner_block = 0; inner_block < 4; inner_block++){
            if (current_piece.blocks[block].column < 9){
                if (current_piece.blocks[block].row == current_piece.blocks[inner_block].row && current_piece.blocks[block].column + 1 == current_piece.blocks[inner_block].column){
                    sibling = true;
                }
            }
        }
        if (!sibling){
        grid[current_piece.blocks[block].row][current_piece.blocks[block].column + 1] = 0;
        }
        
    }
}

void clear_row(char grid[20][10], float *clear_row_timer, float clear_row_timer_interval){
    bool already_added = false;
    bool placed = false;
    for (int row = 0; row < 20; row++){
        bool cleared = true;
        for (int block = 0; block < 10; block++){
            if (grid[row][block] == 0){
                cleared = false;
                break;
            }
        }
        if (cleared){
            if (!already_added){
            *clear_row_timer += frametime;
            already_added = true;
            }
            if (*clear_row_timer >= clear_row_timer_interval){
                for (int block = 0; block < 10; block++){
                    grid[row][block] = 0;
                }
                for (int dropped_row = row; dropped_row > 0; dropped_row--){
                    for (int block = 0; block < 10; block++){
                            grid[dropped_row][block] = grid[dropped_row - 1][block];
                            grid[dropped_row - 1][block] = 0;
                            placed = true;
                    }
                }
            }
        }
    }
    if (placed){
        *clear_row_timer = 0.0f;
    }
}


/*
int main(void){
    
    SetWindowSize(window_width - block_margin, window_height - block_margin);
    */

int random(int start, int end){
    static thread_local std::mt19937 prng{std::random_device{}()};
    std::uniform_int_distribution<int> range(start, end);
    return range(prng);
}

using namespace vexa;
int main()
{
    int real_y = 720;
    int real_x = real_y / 2;
    float block_length = real_x / 10.0f;
    float block_margin = block_length / 15.0f;
    float gravity_timer = 0.0f;
    float gravity_timer_interval = 500.0f;
    float fast_gravity_interval = gravity_timer_interval/8;
    float clear_row_timer = 0.0f;
    const float clear_row_timer_interval = 200.0f;
    float spawn_timer = 0.0f;
    const float spawn_timer_interval = 250.0f;

    char grid[20][10] = {0};
    PieceType random_piece = static_cast<PieceType>(random(0, 6));
    place_piece(random_piece, grid);

    // Initialize Vexa
    Engine::Init(Engine::VIDEO);

    // create a window with 720x720 size and default renderer
    int x = real_x - block_margin;
    int y = real_y - block_margin;
    auto window = Window{}
        .setSize(Vec2i(x, y))
        .setTitle("Tarsis")
        .setRenderer(Renderer::Cfg{})
        .create();
    
    window.setResizable(true);
    window.setAspectRatio(0.5, 0.5);

    auto& gfx = window.renderer();

    Vec2i old_size = window.size();
    bool released = true;
    bool running = true;
    while (running)
    {
        block_length = window.size().x / 10.0f;
        block_margin = block_length / 15.0f;


        // poll events
        while (auto event = Event::Poll()) {
            switch (event->type()) {
                case Event::QUIT: { running = false; break; }
                case Event::KEY_DOWN: {
                    //down
                    if (event->kb().key == Key::S || event->kb().key == Key::DOWN) {
                        gravity_timer_interval = fast_gravity_interval;
                    }

                    if (event->kb().key == Key::ESC) { running = false; }
                    
                    if ((event->kb().key == Key::X || event->kb().key == Key::UP || event->kb().key == Key::W) && !event->kb().repeated) {
                        rotate(grid, true);
                    }
                    if (event->kb().key == Key::Z && !event->kb().repeated) {
                        rotate(grid, false);
                    }
                    if (event->kb().key == Key::S || event->kb().key == Key::DOWN) {
                        physics(grid);
                    }
                    if (event->kb().key == Key::D || event->kb().key == Key::RIGHT) {
                        right(grid);                    }

                    if (event->kb().key == Key::A || event->kb().key == Key::LEFT) {
                        left(grid);
                    }
                }
                case Event::KEY_UP: {
                    if (event->kb().key == Key::S || event->kb().key == Key::DOWN) {
                        gravity_timer_interval = 500.0f;
                    }
                }
                default: { break; }
            }
        }
        
        gravity_timer += frametime;
        if (gravity_timer >= gravity_timer_interval){
            gravity_timer -= gravity_timer_interval;
            physics(grid);
        }
        
        if (!current_piece.active) {
            clear_row(grid, &clear_row_timer, clear_row_timer_interval);
        }

        if (!current_piece.active){
            spawn_timer += frametime;
            if (spawn_timer >= spawn_timer_interval){
                spawn_timer = 0;
                random_piece = static_cast<PieceType>(random(0, 6));
                place_piece(random_piece, grid);
            }
        }

        gfx.start(ColorU8::BLACK);

        for (int row = 0; row < 20 ;row++){
            for (int column = 0; column < 10 ;column++){
                if (grid[row][column] == 1){
                    gfx.rectFill(
                        Rect{
                            static_cast<float>(column * block_length),
                            static_cast<float>(row * block_length),
                            static_cast<float>(block_length - block_margin),
                            static_cast<float>(block_length - block_margin)
                        },
                        ColorU8::WHITE
                    );
                }
            }
        }

        gfx.finish();
        time::sleep(time::Millis(frametime));

    }

    Engine::Close();
}
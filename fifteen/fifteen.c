/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

// blank tile's location
int* blank;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(void)
{
    // stores the total amount of tiles used on the board
    int counter = d * d - 1;
    // assigns the tiles to the two dimensional array
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // stores counter in the board
            board[i][j] = counter;
            
            // if the amount of tiles on the board is odd, swap 2 with 1 and vice versa
            if (d % 2 == 0 && board[i][j] == 2)
            {
                board[i][j] = 1;
            }
            else if (d % 2 == 0 && board[i][j] == 1)
            {
                board[i][j] = 2;
            }
            counter--;
        }   
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // print the row
    for (int i = 0; i < d; i++)
    {
        // print the column
        for (int j = 0; j < d; j++)
        {
            // if the tile is 0, print _
            if (board[i][j] == 0)
            {
                printf(" _  ");
                // store location of 0 at a pointer
                blank = &board[i][j];
            }
            
            // if the tile has a number below 10, add a space before the number
            else if (board[i][j] < 10)
            {
                printf(" %i  ", board[i][j]);
            }
            
            // if none of these conditions arise, just print the number
            else
            {
                printf("%i  ", board[i][j]);
            }
        }
        // print onto a new row
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // check to make sure program doesn't break
    if (tile <= 0 || tile > d*d-1)
    {
        return false;
    }
        
    // search for tile in row
    for (int i = 0; i < d; i++)
    {
        // search for tile in column
        
        for (int j = 0; j < d; j++)
        {
            // if tile is there and is adjacent, swap the tile
            if (board[i][j] == tile)
                {
                    // check if tile is on top of blank
                    if(&board[i-1][j] == blank)
                    {
                        blank = &board[i-1][j];
                        board[i-1][j] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    // check if tiles is right to blank
                    else if(&board[i][j+1] == blank)
                    {
                        blank = &board[i][j+1];
                        board[i][j+1] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    // check if tile is left to blank
                    else if(&board[i][j-1] == blank)
                    {
                        blank = &board[i][j-1];
                        board[i][j-1] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    // check if tile is downwards to blank
                    else if(&board[i+1][j] == blank)
                    {
                        blank = &board[i+1][j];
                        board[i+1][j] = tile;
                        board[i][j] = 0;
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                    
            }    
        }
            
     }  
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // winning code: ./fifteen 3 < ~cs50/pset3/3x3.txt
    // stores the winning number (the total amount of tiles used on the board) and the counter
    int counter = 1;
    int win = d * d - 1;
    
    
    // check the row
    for (int i = 0; i < d; i++)
    {
        // check the column
        for (int j = 0; j < d; j++)
        {
            // if it's equal to the current counter number, continue
            if (board[i][j] == counter)
            {
                if (board[i][j] == win)
                {
                    return true;
                }
                counter++;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}

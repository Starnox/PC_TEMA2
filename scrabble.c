#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/scrabble.h"
#include "util/print_board.h"

int main()
{
    int cerinta;
    fscanf(stdin,"%d",&cerinta);

    initialise_board();

    switch (cerinta)
    {
    case 0:
        solve0();
        break;
    case 1:
        solve1();
        break;
    case 2:
        solve2();
        break;
    case 3:
        solve3();
        break;
    case 4:
        solve4();
        break;
    
    default:
        break;
    }
    
}

void solve0()
{
    print_board(playing_board);
}

void solve1()
{
    int n, i, x, y, direction;
    char word[BOARD_SIZE+1];

    fscanf(stdin,"%d",&n);
    for(i = 0; i < n; ++i)
    {
        fscanf(stdin,"%d %d %d %s",&y,&x,&direction,word);
        insert_word(y,x,direction,word);
    }
    print_board(playing_board);
}

void solve2()
{
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0;
    char word[BOARD_SIZE+1];

    fscanf(stdin,"%d",&n);
    for(i = 0; i < n; ++i)
    {
        fscanf(stdin,"%d %d %d %s",&y,&x,&direction,word);
        insert_word(y,x,direction,word);
        
        // if i is even then it is player 1's turn
        if(i % 2 == 0)
        {
            score_player1 += calculate_score(word);
        }
        // if i is odd then it is player 2's turn
        else
        {
            score_player2 += calculate_score(word);
        }
    }

    // Print the scores of the two players
    print_score(score_player1,score_player2);
}

void solve3()
{
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0, multiply;
    int has_xx, has_yy;
    char word[BOARD_SIZE+1], XX[3], YY[3];


    fscanf(stdin,"%s %s",XX,YY);
    fscanf(stdin,"%d",&n);

    for(i = 0; i < n; ++i)
    {
        fscanf(stdin,"%d %d %d %s",&y,&x,&direction,word);
        insert_word(y,x,direction,word);
        has_xx = check_substring(word,XX);
        has_yy = check_substring(word,YY);

        multiply = calculate_multiplier(y,x,direction,word,has_xx,has_yy);
        
        // if i is even then it is player 1's turn
        if(i % 2 == 0)
        {
            score_player1 += (calculate_score(word) * multiply);
        }
        // if i is odd then it is player 2's turn
        else
        {
            score_player2 += (calculate_score(word) * multiply);
        }
    }
    print_score(score_player1,score_player2);
}

void solve4()
{
    // Declaring and reading the input
    int n, i, x, y, direction;
    
    char word[BOARD_SIZE+1], XX[3], YY[3];

    fscanf(stdin,"%s %s",XX,YY);
    fscanf(stdin,"%d",&n);

    // Placing the words in the board and marking them down
    for(i = 0; i < n; ++i)
    {
        fscanf(stdin,"%d %d %d %s",&y,&x,&direction,word);

        insert_word(y,x,direction,word);
        mark_word(word);
    }

    for(i = 0; i< NUM_WORDS ; ++i)
    {
        if(try_place_word(i) == 1)
        {
            break;
        }
    }

    print_board(playing_board);

}

// insert the word in the playing board
void insert_word(int y, int x, int direction, char word[])
{
    int i,j, length = strlen(word);
    // the word is horizontal
    if(direction == 0)
    {
        for(j = 0; j < length; ++j)
        {
            playing_board[y][j+x] = word[j];

        }
    }
    // vertical
    else
    {
        for(i = 0; i < length; ++i)
        {
            playing_board[i+y][x] = word[i];
        }
    }
}
int calculate_multiplier(int y, int x, int direction, char word[], int has_xx, int has_yy)
{
    int i,j, length = strlen(word), multiply = 1;
    // the word is horizontal
    if(direction == 0)
    {
        for(j = 0; j < length; ++j)
        {
            if(bonus_board[y][j+x] == 1 && has_xx)
                multiply*=2;
            if(bonus_board[y][j+x] == 2 && has_yy)
                multiply*=3;
        }
    }
    // vertical
    else
    {
        for(i = 0; i < length; ++i)
        {
            if(bonus_board[i+y][x] == 1 && has_xx)
                multiply*=2;
            if(bonus_board[i+y][x] == 2 && has_yy)
                multiply*=3;
        }
    }
    return multiply;
}

int calculate_score(char word[])
{
    int i, length = strlen(word), score = 0;
    for(i = 0; i < length; ++i)
    {
        score += points_for_letter[word[i] - 'A'];
    }
    return score;
}

int check_substring(char word[], char XX[])
{
    if(strstr(word,XX) != NULL)
    {
        return 1;
    }
    return 0;
}

void print_score(int score_player1, int score_player2)
{
    fprintf(stdout, "Player 1: %d Points\n", score_player1);
    fprintf(stdout, "Player 2: %d Points\n", score_player2);
}

void mark_word(char word[])
{
    for(int i = 0; i < NUM_WORDS; ++i)
    {
        // if the words are equal
        if(strcmp(word,words[i]) == 0)
        {
            // mark the word as used
            used_words[i] = 1;
        }
    }
}

int try_place_word(int word_index)
{
    int x, y, j;

    if(used_words[word_index] == 1)
        return 0;

    for(y = 0; y < BOARD_SIZE; ++y)
    {
        for(x = 0; x < BOARD_SIZE; ++x)
        {
            // if the first letter matches
            if(words[word_index][0] == playing_board[y][x])
            {
                int length = strlen(words[word_index]);
                int found = 1; // presumes we can place the word

                // try to place it horizontly
                    // if it fits
                if(x + length <= BOARD_SIZE)
                {
                    // check if there is another word in the way
                    for(j = x+1; j < x + length; ++j)
                    {

                        // if we find a bad letter we can't place the word
                        if(playing_board[y][j] != '.')
                        {
                            found = 0;
                            break;
                        }
                    }
                }
                else
                    found = 0;
                

                // we found the word and we place it signaling the function succeded
                if(found == 1)
                {
                    insert_word(y,x,0,words[word_index]);
                    used_words[word_index] = 1;
                    return 1;
                }

                // presumes again we can place the word
                found = 1;

                // try ty place it verically
                if(y + length <= BOARD_SIZE)
                {
                    // check if there is another word in the way
                    for(j = y+1; j < y + length; ++j)
                    {
                        //if we find a bad letter we can't place the word
                        if(playing_board[j][x] != '.')
                        {
                            found = 0;
                            break;
                        }
                    }
                }
                else
                    found = 0;
                

                // we found the word and we place it, signaling the function succeded
                if(found == 1)
                {
                    insert_word(y,x,1,words[word_index]);
                    used_words[word_index] = 1;
                    return 1;
                }
            }
        }
    }

    return 0;
}

void print_line_delimiter()
{
    for(int i = 0; i< BOARD_SIZE; ++i)
    {
        fprintf(stdout,":---");
    }
    fprintf(stdout,":\n");
}

void print_board(char board[PRINT_BOARD_SIZE][PRINT_BOARD_SIZE])
{
    int i,j;
    for(i = 0; i < BOARD_SIZE; ++i)
    {
        print_line_delimiter();

        for(j = 0; j < BOARD_SIZE; ++j)
        {
            if(board[i][j] == '.')
                fprintf(stdout,"|   ");
            else
                fprintf(stdout,"| %c ",board[i][j]);
        }

        fprintf(stdout,"|\n");
    }

    print_line_delimiter();
}

void initialise_board()
{
    memset(playing_board, (int) '.', sizeof(playing_board));
}


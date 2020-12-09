#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/scrabble.h"
#include "util/print_board.h"

#define LINE_LENGTH  100


// Prototypes for the functions
void solve0();
void solve1();
void solve2();
void solve3();
void solve4();
void solve5();
void solve6();

void initialise_board();
void insert_word(int y, int x, int direction, char word[]);
int calculate_score();
void print_score(int score_player1, int score_player2);
int check_substring(char word[], char XX[]);
int check_substring_ending(char word[], char XX[]);
int calculate_multiplier(int y, int x, int direction, char word[], int has_xx, int ends_yy);
void mark_word(char word[]);
int try_place_word(int word_index);
void calculate_optimal_placement(int word_index, int has_xx, int ends_yy,
                             int *aux_score, int *aux_y, int *aux_x, int *aux_direction);
void read_word(int *y, int *x, int *direction, char *word);
void read_n(int *n);
void read_XX(char *XX);


char playing_board[BOARD_SIZE][BOARD_SIZE];
int points_for_letter[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
int used_words[NUM_WORDS];

int main()
{
    int cerinta;
    
    // Reading and initialising
    read_n(&cerinta);
    initialise_board();

    // Decide which task to solve
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
    case 5:
        solve5();
        break;
    case 6:
        solve6();
        break;

    default:
        break;
    }
    
}

// The program uses fgets to read the input
// Reads the necessary info to store the word corectly
void read_word(int *y, int *x, int *direction, char *word)
{
    // read the line
    char line[LINE_LENGTH];

    fgets(line, LINE_LENGTH, stdin);
    if(line[strlen(line)-1] == '\n')
        line[strlen(line)-1] = '\0';

    // split the line
    char delim[] = " ";
    char words[LINE_LENGTH][LINE_LENGTH];

    int k  = 0;

    char *ptr = strtok(line,delim);
    while(ptr != NULL)
    {
        // storing the words in a matrix 
        strcpy(words[k++],ptr);
        ptr = strtok(NULL,delim);
    }

    // Delivering the results by changing the value at the specified
    // location in memory
    *y = atoi(words[0]);
    *x = atoi(words[1]);
    *direction = atoi(words[2]);
    strcpy(word,(words[3])); 
}

// Reads n
void read_n(int *n)
{
    char line[LINE_LENGTH];
    fgets(line,LINE_LENGTH,stdin);
    if(line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';    
    
    *n = atoi((const char *) line);
}

// Reads the substring used for the bonus
void read_XX(char *XX)
{
    fgets(XX,LINE_LENGTH,stdin);
    if(XX[strlen(XX) - 1] == '\n')
        XX[strlen(XX) - 1] = '\0';
}


void solve0()
{
    print_board(playing_board);
    
}

void solve1()
{
    int n, i, x, y, direction;
    char word[LINE_LENGTH];
    read_n(&n);
    // Reads every word and insert it into the board
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word);
        insert_word(y,x,direction,word);
    }
    print_board(playing_board);
}

void solve2()
{
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0;
    char word[LINE_LENGTH];

    read_n(&n);
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word);
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
    // Initialisation and reading
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0, multiply;
    int has_xx, ends_yy;
    char word[LINE_LENGTH], XX[LINE_LENGTH], YY[LINE_LENGTH];

    read_XX(XX);
    read_XX(YY);
    read_n(&n);

    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word);
        insert_word(y,x,direction,word);

        // checks if the conditions for the 2 bonuses are met
        has_xx = check_substring(word,XX);
        ends_yy = check_substring_ending(word,YY);

        multiply = calculate_multiplier(y,x,direction,word,has_xx,ends_yy);
        
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
    char word[LINE_LENGTH], XX[LINE_LENGTH], YY[LINE_LENGTH];
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n);

    // Placing the words in the board and marking them down
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word);
        insert_word(y,x,direction,word);
        mark_word(word);
    }

    for(i = 0; i< NUM_WORDS ; ++i)
    {
        // try to place the word and place it -> returns 1 if the operation was succesful
        if(try_place_word(i) == 1)
        {
            break;
        }
    }

    print_board(playing_board);

}

void solve5()
{
    // Initialisation and reading
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0, multiply;
    int has_xx, ends_yy;
    char word[LINE_LENGTH], XX[LINE_LENGTH], YY[LINE_LENGTH];
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n);

    // calculate initial scores
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word);
        insert_word(y,x,direction,word);
        mark_word(word);

        has_xx = check_substring(word,XX);
        ends_yy = check_substring_ending(word,YY);

        multiply = calculate_multiplier(y,x,direction,word,has_xx,ends_yy);
        
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

    int maximum_score = 0, selected_word, aux_score = 0, aux_x = 0, aux_y = 0, aux_direction = 0;
    // Iterating through every word of the list
    for(i = 0; i< NUM_WORDS ; ++i)
    {
        has_xx = check_substring(words[i], XX);
        ends_yy = check_substring_ending(words[i], YY);

        aux_score = 0;

        // calculate the maximum score we can obtain by placing every unmarked word
        // in the playing board
        calculate_optimal_placement(i, has_xx, ends_yy, &aux_score, &aux_y, &aux_x, &aux_direction);
        int to_change = 0;

        // if it is the best score so far, we update
        if(aux_score > maximum_score)
        {
            maximum_score = aux_score;
            y = aux_y;
            x = aux_x;
            direction = aux_direction;
            selected_word = i;
        }
        // if the current score and maximum are equal
        // verify if we can place it at a smaller position
        else if(aux_score == maximum_score)
            {
                if(aux_y < y)
                {
                    to_change = 1;
                }
                else if(aux_y == y)
                {
                    if(aux_x < x)
                    {
                        to_change = 1;
                    }
                }
                if(to_change == 1)
                {
                    maximum_score = aux_score;
                    y = aux_y;
                    x = aux_x;
                    direction = aux_direction;
                    selected_word = i;
                }

            }
    }

    // if we can score higher than player one, we insert the word and print the result
    if(score_player2 + maximum_score >= score_player1)
    {
        insert_word(y,x,direction,words[selected_word]);
        print_board(playing_board);
    }
    else
    {
        // in case we can't win
        fprintf(stdout,"Fail!");
    }
}

void solve6()
{
    // Initialisation and reading
    int n, i, word_index, x, y, direction,
                score_player1 = 0, score_player2 = 0, multiply;

    int has_xx, ends_yy;
    char word[LINE_LENGTH], XX[LINE_LENGTH], YY[LINE_LENGTH];
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n);

    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word);
        insert_word(y,x,direction,word);
        mark_word(word);

        has_xx = check_substring(word,XX);
        ends_yy = check_substring_ending(word,YY);

        multiply = calculate_multiplier(y,x,direction,word,has_xx,ends_yy);
        
        // the score for player1
        score_player1 += (calculate_score(word) * multiply);

        // Calculate the best move for player2

        int maximum_score = 0, selected_word, aux_score = 0, 
                            aux_x = 0, aux_y = 0, aux_direction = 0;


        for(word_index = 0; word_index< NUM_WORDS ; ++word_index)
        {
            has_xx = check_substring(words[word_index], XX);
            ends_yy = check_substring_ending(words[word_index], YY);

            aux_score = 0;

            int to_change = 0;
            // calculate the maximum score we can obtain by placing the word at index i
            calculate_optimal_placement(word_index, has_xx, ends_yy, &aux_score, 
                                        &aux_y, &aux_x, &aux_direction);
            // if it is the best score so far, we update (the same code as in task5)
            if(aux_score > maximum_score)
            {
                maximum_score = aux_score;
                y = aux_y;
                x = aux_x;
                direction = aux_direction;
                selected_word = word_index;
            }
            else if(aux_score == maximum_score)
            {
                if(aux_y < y)
                {
                    to_change = 1;
                }
                else if(aux_y == y)
                {
                    if(aux_x < x)
                    {
                        to_change = 1;
                    }
                }
                if(to_change == 1)
                {
                    maximum_score = aux_score;
                    y = aux_y;
                    x = aux_x;
                    direction = aux_direction;
                    selected_word = word_index;
                }

            }

        }
        // We found the best word, we place it and update the score
        insert_word(y,x,direction,words[selected_word]);
        mark_word(words[selected_word]);
        score_player2+=maximum_score;
    }

    // Printing the results
    print_board(playing_board);
    int winner = 0;
    if(score_player1 > score_player2)
        winner = 1;
    else
        winner = 2;
    
    fprintf(stdout,"Player %d Won!",winner);

}

// insert the word in the playing board
void insert_word(int y, int x, int direction, char word[])
{
    int i,j, length = strlen(word);
    // the word is horizontal
    if(direction == 0)
    {
        // iterating through the characters of the word
        // and placing them at the desired location
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
int calculate_multiplier(int y, int x, int direction, char word[], int has_xx, int ends_yy)
{
    int i,j, length = strlen(word), multiply = 1;
    // the word is horizontal
    if(direction == 0)
    {
        for(j = 0; j < length; ++j)
        {
            // checking the conditions of the bonuses
            if(bonus_board[y][j+x] == 1 && has_xx)
                multiply*=2;
            if(bonus_board[y][j+x] == 2 && ends_yy)
                multiply*=3;
        }
    }
    // vertical
    else
    {
        for(i = 0; i < length; ++i)
        {
             // checking the conditions of the bonuses
            if(bonus_board[i+y][x] == 1 && has_xx)
                multiply*=2;
            if(bonus_board[i+y][x] == 2 && ends_yy)
                multiply*=3;
        }
    }
    return multiply;
}

int calculate_score(char word[])
{
    int i, length = strlen(word), score = 0;
    // Go through every character and add the coresponding
    // points for each of them
    for(i = 0; i < length; ++i)
    {
        score += points_for_letter[word[i] - 'A'];
    }
    return score;
}

// checks if the word contains substring xx
int check_substring(char word[], char XX[])
{
    if(strstr(word,XX) != NULL)
    {
        return 1;
    }
    return 0;
}

// checks if the word ends in substring xx
int check_substring_ending(char word[], char XX[])
{
    // the substring is made up of only 2 letters
    // so we only check for those 2
    int length = strlen(word);
    if(length < 2)
        return 0;
    if(word[length - 1] == XX[1] && word[length - 2] == XX[0])
        return 1;
    return 0;
}

void print_score(int score_player1, int score_player2)
{
    fprintf(stdout, "Player 1: %d Points\n", score_player1);
    fprintf(stdout, "Player 2: %d Points\n", score_player2);
}

void mark_word(char word[])
{
    // iterate through every word of the list
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
    int x, y, j, found, length = strlen(words[word_index]);;

    if(used_words[word_index] == 1)
        return 0;

    for(y = 0; y < BOARD_SIZE; ++y)
    {
        for(x = 0; x < BOARD_SIZE; ++x)
        {
            // if the first letter matches
            if(words[word_index][0] == playing_board[y][x])
            {
                found = 1; // presumes we can place the word

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

void calculate_optimal_placement(int word_index, int has_xx, int ends_yy, int *aux_score,
 int *aux_y, int *aux_x, int *aux_direction)
{
    int x, y, j, score, multiplier, found, length = strlen(words[word_index]);

    if(used_words[word_index] == 1)
        return;

    // Go through every cell of the board
    for(y = 0; y < BOARD_SIZE; ++y)
    {
        for(x = 0; x < BOARD_SIZE; ++x)
        {
            // if the first letter matches
            if(words[word_index][0] == playing_board[y][x])
            {
                found = 1; // presumes we can place the word

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
                
                // we found a good placement and we calculate the current score
                if(found == 1)
                {
                    score = calculate_score(words[word_index]);
                    multiplier = calculate_multiplier(y,x,0,words[word_index],has_xx,ends_yy);

                    // if it is the best so far
                    if(score * multiplier > *aux_score)
                    {
                        *aux_score = score * multiplier;
                        *aux_y = y;
                        *aux_x = x;
                        *aux_direction = 0;
                    }
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
                

                // we found a good placement and we calculate the current score
                if(found == 1)
                {
                    score = calculate_score(words[word_index]);
                    multiplier = calculate_multiplier(y,x,1,words[word_index],has_xx,ends_yy);
                    // if it is the best so far
                    if(score * multiplier > *aux_score)
                    {
                        *aux_score = score * multiplier;
                        *aux_y = y;
                        *aux_x = x;
                        *aux_direction = 1;
                    }
                }
            }
        }
    }
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


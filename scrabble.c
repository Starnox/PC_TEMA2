#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util/scrabble.h"
#include "util/print_board.h"

#define LINE_LENGTH  200

int main()
{
    int cerinta;
    
    char *line = (char *) initialise_reader();
    read_n(&cerinta,line);
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

const char* initialise_reader()
{
    const char * line = malloc(LINE_LENGTH * sizeof(char));
    return line;
}

const char** split_line(char *line)
{
    int k = 0;
    char *delim = " ";
    char **words = malloc(LINE_LENGTH * LINE_LENGTH * sizeof(char));   

    char *ptr = strtok(line,delim);

    while(ptr != NULL)
    {
        *(words+k) = ptr; 
        k++;
        ptr = strtok(NULL, delim);
    } 
    return (const char**) words;
}

void read_word(int *y, int *x, int *direction, char *word, char *line)
{
    fgets(line, LINE_LENGTH, stdin);
    if(line[strlen(line)-1] == '\n')
        line[strlen(line)-1] = '\0';

    const char **words = split_line(line);
    *y = atoi(*words);
    *x = atoi(*(words + 1));
    *direction = atoi(*(words + 2));
    strcpy(word,*(words+3)); 
}

void read_n(int *n, char *line)
{
    fgets(line,LINE_LENGTH,stdin);
    if(line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';    
    
    *n = atoi((const char *) line);
}

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
    char *word, *line = (char *)initialise_reader();

    if(line == NULL)
    {
        return;
    }

    word = malloc(LINE_LENGTH * sizeof(char));
    if(word == NULL)
        return;

    read_n(&n,line);

    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word,line);
        insert_word(y,x,direction,word);
    }
    print_board(playing_board);
}

void solve2()
{
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0;
    char *word, *line = (char *)initialise_reader();

    if(line == NULL)
        return;

    word = malloc(LINE_LENGTH * sizeof(char));
    if(word == NULL)
        return;
        
    read_n(&n,line);
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word,line);
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
    // Initialisation and memory allocation
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0, multiply;
    int has_xx, ends_yy;
    char *word, *XX, *YY, *line = (char *)initialise_reader();

    word = malloc(LINE_LENGTH * sizeof(char));
    if(word == NULL)
        return;
    
    XX = malloc(LINE_LENGTH * sizeof(char));
    if(XX == NULL)
        return;
    
    YY = malloc(LINE_LENGTH * sizeof(char));
    if(YY == NULL)
        return;
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n,line);

    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word,line);
        insert_word(y,x,direction,word);
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
    char *word, *XX, *YY, *line = (char *) initialise_reader();

    word = malloc(LINE_LENGTH * sizeof(char));
    if(word == NULL)
        return;
    
    XX = malloc(LINE_LENGTH * sizeof(char));
    if(XX == NULL)
        return;
    
    YY = malloc(LINE_LENGTH * sizeof(char));
    if(YY == NULL)
        return;
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n,line);

    // Placing the words in the board and marking them down
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word,line);
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

void solve5()
{
    int n, i, x, y, direction, score_player1 = 0, score_player2 = 0, multiply;
    int has_xx, ends_yy;
    char *word, *XX, *YY, *line = (char *) initialise_reader();

    word = malloc(LINE_LENGTH * sizeof(char));
    if(word == NULL)
        return;
    
    XX = malloc(LINE_LENGTH * sizeof(char));
    if(XX == NULL)
        return;
    
    YY = malloc(LINE_LENGTH * sizeof(char));
    if(YY == NULL)
        return;
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n,line);

    // calculate initial scores
    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word,line);
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
    for(i = 0; i< NUM_WORDS ; ++i)
    {
        has_xx = check_substring(words[i], XX);
        ends_yy = check_substring_ending(words[i], YY);

        aux_score = 0;

        // calculate the maximum score we can obtain by placing the word at index i
        calculate_optimal_placement(i, has_xx, ends_yy, &aux_score, &aux_y, &aux_x, &aux_direction);
 
        // if it is the best score so far, we update
        if(aux_score > maximum_score)
        {
            maximum_score = aux_score;
            y = aux_y;
            x = aux_x;
            direction = aux_direction;
            selected_word = i;
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
    
    int n, i, word_index, x, y, direction, score_player1 = 0, score_player2 = 0, multiply;
    int has_xx, ends_yy;
    char *word, *XX, *YY, *line = (char *) initialise_reader();

    word = malloc(LINE_LENGTH * sizeof(char));
    if(word == NULL)
        return;
    
    XX = malloc(LINE_LENGTH * sizeof(char));
    if(XX == NULL)
        return;
    
    YY = malloc(LINE_LENGTH * sizeof(char));
    if(YY == NULL)
        return;
        
    read_XX(XX);
    read_XX(YY);
    read_n(&n,line);

    for(i = 0; i < n; ++i)
    {
        read_word(&y,&x,&direction,word,line);
        insert_word(y,x,direction,word);
        mark_word(word);
        
        has_xx = check_substring(word,XX);
        ends_yy = check_substring_ending(word,YY);

        multiply = calculate_multiplier(y,x,direction,word,has_xx,ends_yy);
        
        score_player1 += (calculate_score(word) * multiply);

        // Calculate the best move for player2

        int maximum_score = 0, selected_word, aux_score = 0, aux_x = 0, aux_y = 0, aux_direction = 0;
        for(word_index = 0; word_index< NUM_WORDS ; ++word_index)
        {
            has_xx = check_substring(words[word_index], XX);
            ends_yy = check_substring_ending(words[word_index], YY);

            aux_score = 0;

            // calculate the maximum score we can obtain by placing the word at index i
            calculate_optimal_placement(word_index, has_xx, ends_yy, &aux_score, &aux_y, &aux_x, &aux_direction);
    
            // if it is the best score so far, we update
            if(aux_score > maximum_score)
            {
                maximum_score = aux_score;
                y = aux_y;
                x = aux_x;
                direction = aux_direction;
                selected_word = word_index;
            }
        }
        insert_word(y,x,direction,words[selected_word]);
        mark_word(words[selected_word]);
        score_player2+=maximum_score;
    }

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

int check_substring_ending(char word[], char XX[])
{
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

void calculate_optimal_placement(int word_index, int has_xx, int ends_yy, int *aux_score, int *aux_y, int *aux_x, int *aux_direction)
{
    int x, y, j, score, multiplier, found, length = strlen(words[word_index]);

    if(used_words[word_index] == 1)
        return;

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
                
                
                if(found == 1)
                {
                    score = calculate_score(words[word_index]);
                    multiplier = calculate_multiplier(y,x,0,words[word_index],has_xx,ends_yy);

                    if(score * multiplier > *aux_score)
                    {
                        *aux_score = score * multiplier;
                        *aux_y = y;
                        *aux_x = x;
                        *aux_direction = 0;
                        return;
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
                

                // we found the word and we place it, signaling the function succeded
                if(found == 1)
                {
                    score = calculate_score(words[word_index]);
                    multiplier = calculate_multiplier(y,x,1,words[word_index],has_xx,ends_yy);

                    if(score * multiplier > *aux_score)
                    {
                        *aux_score = score * multiplier;
                        *aux_y = y;
                        *aux_x = x;
                        *aux_direction = 1;
                        return;
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


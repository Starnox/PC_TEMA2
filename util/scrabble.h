#ifndef _SCRABBLE_HEADER
#define _SCRABBLE_HEADER

#define BOARD_SIZE	15
#define NUM_WORDS	100
#define PHI 26

void solve0();
void solve1();
void solve2();
void solve3();
void solve4();

void initialise_board();
void insert_word(int y, int x, int direction, char word[]);
int calculate_score();
void print_score(int score_player1, int score_player2);
int check_substring(char word[], char XX[]);
int calculate_multiplier(int y, int x, int direction, char word[], int has_xx, int has_yy);
void mark_word(char word[]);
int try_place_word(int word_index);

static char playing_board[BOARD_SIZE][BOARD_SIZE];

static int points_for_letter[PHI] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};

static int used_words[NUM_WORDS];

char bonus_board[BOARD_SIZE][BOARD_SIZE] = {
        {0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0},
        {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0},
        {1, 2, 0, 0, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0},
        {0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1},
        {0, 0, 1, 2, 0, 0, 2, 0, 0, 0, 1, 0, 2, 0, 1},
        {0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0},
        {0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0},
        {0, 0, 1, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0}};

char words[][NUM_WORDS] = {
	"AIRPLANE",
	"COMMUNITY",
	"INCLUDE",
	"INFORMATION",
	"SOCIAL",
	"HEALTH",
	"PERSON",
	"SCHOOL",
	"HISTORY",
	"PARTY",
	"OPEN",
	"REASON",
	"TEACHER",
	"OFFER",
	"EDUCATION",
	"REMEMBER",
	"LEADER",
	"DECISION",
	"REPORT",
	"DIRECTOR",
	"PAPER",
	"CENTER",
	"PROJECT",
	"UNIVERSITY",
	"MUSIC",
	"TABLE",
	"FACE",
	"DATA",
	"PHONE",
	"PRODUCT",
	"WALL",
	"WORKER",
	"MOVIE",
	"OPEN",
	"STEP",
	"FILM",
	"CENTURY",
	"POINT",
	"WINDOW",
	"BROTHER",
	"SUMMER",
	"PLANT",
	"PLACE",
	"POPULATION",
	"ECONOMY",
	"FIRE",
	"FUTURE",
	"INCREASE",
	"SECURITY",
	"DEAL",
	"BEHAVIOUR",
	"FIGHT",
	"GOAL",
	"BED",
	"ORDER",
	"PLAN",
	"NATURE",
	"COLOR",
	"STORE",
	"LANGUAGE",
	"ARTICLE",
	"SEVEN",
	"ARTIST",
	"EIGHT",
	"ONE",
	"HAPPY",
	"CAT",
	"DOG",
	"FISH",
	"SIGN",
	"CUP",
	"WONDER",
	"TRAINING",
	"MACHINE",
	"ELECTION",
	"MESSAGE",
	"ANALYSIS",
	"NAME",
	"FAIL",
	"GLASS",
	"ANSWER",
	"SKILL",
	"FINANCIAL",
	"SORT",
	"ACT",
	"TEN",
	"KNOWLEDGE",
	"BLUE",
	"LITTLE",
	"DARK",
	"LIGHT",
	"STUDY",
	"SCIENCE",
	"GREEN",
	"MEMORY",
	"EXPERT",
	"SPRING",
	"RADIO",
	"MANAGEMENT",
	"THEORY"
};

#endif

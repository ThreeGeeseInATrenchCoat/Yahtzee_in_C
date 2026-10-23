#include "header.h"

int main(VOID) {
	srand(time(NULL));
	int rolls[6] = { 2, 2, 2, 2, 2 }, how_many[6] = { 0, 0, 0, 0, 0, 0 }, scores_earned[6] = { 0, 0, 0, 0, 0, 0 }, choice, player_point_total[2] = { 0, 0 };
	//-1 is used as a faux NULL value, if score is not NULL, cannot have points put into it
	int scorecard[15] = {
		-1,		//sum of 1
		-1,		//sum of 2
		-1,		//sum of 3
		-1,		//sum of 4
		-1,		//sum of 5
		-1,		//sum of 6
		 0,		//bonus

		-1,		//three-of-a-kind
		-1,		//four-of-a-kind
		-1,		//full house
		-1,		//short straight
		-1,		//long straight
		-1,		//yahtzee
		-1,		//chance
		 0		//yahtzee bonus
	};


	do {
		choice = welcome_script();

		switch (choice) {
		case 1:
			system("cls");
			print_rules();
			break;
		case 2:
			system("cls");
			break;
		case 3:
			printf("EXIT\n");
			return 0;
		}
	} while (choice == 1);

	//game loop

	for (int i = 0; i < 2; i++){
		printf("PLAYER %d\n", i + 1);

		for (int j = 1; j <= 13; j++) {

			printf("turn %d\n", j);

			press_1_to_roll();
			roll_dice(rolls);

			printf("rolled: ");
			print_array(rolls, 5);

			count_rolls(rolls, how_many);
			what_kind_of_score(how_many, scores_earned, scorecard);

			//count rolls and what kind of score are in reroll, no need to include in main
			reroll(rolls, how_many, scores_earned, scorecard);

			add_to_card(scorecard, scores_earned, rolls, how_many);

			system("cls");
			print_scorecard(scorecard);

			system("pause");
			system("cls");
		}
		player_point_total[i] = add_array(scorecard, 15);
		reset_scorecard(scorecard);
	}

	//who won?
	if (player_point_total[0] > player_point_total[1]) {
		printf("PLAYER 1 WINS\n");
	}
	else if (player_point_total[1] > player_point_total[0]) {
		printf("PLAYER 2 WINS\n");
	}
	else {
		printf("IT'S A TIE!\n");
	}
}
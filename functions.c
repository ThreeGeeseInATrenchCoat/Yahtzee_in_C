#include "header.h"

//the sort functions

/*
	function name: swap_elements
	function description: swaps 2 elements in an array, for use in sorting algorithms
	preconditions: an array of at least 2 elements
	date created: 10/19/2026
*/

void swap_elements(int* a, int* b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

/*
	function name: bubble_sort
	function description: sorts elements in an array
	preconditions: an array of at least 2 elements
	postconditions: the array is sorted smallest to largest
	date created: 10/19/2026
	time complexities:
		worst case: O(n^2)
		best case: O(n)
		average case: O(n^2)
	space complexity: O(1)
*/

void bubble_sort(int arr[], int size) {			//i should only need this one, the array is 5 elements big

	int swapped;

	for (int i = 0; i < size; i++) {
		swapped = 0;
		for (int j = 0; j < size - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap_elements(&arr[j], &arr[j + 1]);

				swapped = 1;
			}
		}
		// Small optimization. If no two elements were swapped by the inner loop, the array is already sorted, break early
		if (swapped == 0) {
			break;
		}
	}
}

//the search functions

/*
	function name: sequential_search
	function description: searches an array for a target and returns the index
	preconditions: an array of at least 2 elements
	date created: 10/19/2026
	time complexities:
		worst case: O(n)
		best case: O(1)
		average case: O(n)
	changelog:
		10/21/16:
			changed arr[i] = target to arr[i] == target
*/

int sequential_search(int arr[], int size, int target) {
	for (int i = 0; i < size; i++) {
		if (arr[i] == target) {
			return 1;
		}
	}
	return 0;
}

/*
	function name: binary_search
	function description: searches an array for a target and returns the index
	preconditions: a sorted array of at least 2 elements
	date created: 10/19/2026
	time complexities:
		worst case: O(nlogn)
		best case: O(1)
		average case: O(nlogn)
*/

int binary_search(int arr[], int left, int right, int target) {
	int mid = left + (right - left) / 2;

	if (left > right) {
		printf("ERROR!\n Target %d not found in list", target);
		return -1;
	}

	if (arr[mid] == target) {
		return mid;
	}
	else if (arr[mid] > target) {
		//printf("not %d\n", arr[mid]);
		return binary_search(arr, left, mid - 1, target);
	}
	else {
		//printf("not %d\n", arr[mid]);
		return binary_search(arr, mid + 1, right, target);
	}
}

//the game functions

/*
	function name: roll_dice
	function description: rolls a die 5 times, saving each roll to an array
	preconditions: an array of 6 elements
	date created: 10/20/2026
*/

void roll_dice(int arr[]) {
	for (int i = 0; i < 5; i++) {
		arr[i] = (rand() % 6) + 1;
	}
	bubble_sort(arr, 5);
}

/*
	function name: press_1_to_roll
	function description: waits for the player to press 1, without waiting for enter to be pressed
	preconditions: a working input stream
	date created: 10/20/2026
*/

void press_1_to_roll() {
	char ch = NULL;

	printf("Press 1 to roll dice: ");
	
	do {
		// Read the character instantly
		ch = _getch();
	} while (ch != '1');
	printf("\n");
}

/*
	function name: count_rolls
	function description: counts how many of what the player rolled
	preconditions: rolled dice
	date created: 10/20/2026
*/

void count_rolls(int arr[], int how_many[]) {
	
	for (int i = 0; i < 6; i++) {
		how_many[i] = 0;
	}

	for (int i = 0; i < 5; i++) {
		how_many[arr[i] - 1]++;				//EVIL EVIL EVIL EVIL EVIL EVIL EIVL
		//for array {1, 3, 4, 4, 3}
		//how_many = {1, 0, 2, 2, 0, 0}
	}
}

//redundant, mushed into one function, i just dont like deleting things

//int reroll_or_not() {
//	char huh = NULL;
//	do {
//		printf("reroll dice? (y/n): ");
//		scanf(" %c", &huh);
//	} while (huh != 'y' && huh != 'n');
//
//	if (huh == 'y') {
//		return 1;
//	}
//	else {
//		return 0;
//	}
//}
//
//void reroll(int arr[]) {
//	int how_many, what;
//	printf("how many dice to reroll: ");
//	scanf("%d", &how_many);
//
//	for (int i = 0; i < how_many; i++) {
//		printf("input a die to reroll (1-5): ");
//		scanf("%d", &what);
//		arr[what - 1] = (rand() % 6) + 1;
//	}
//}

/*
	function name: reroll
	function description: allows the player 3 rerolls
	preconditions: rolled dice
	date created: 10/21/2026
*/

void reroll(int arr[], int arr2[], int scores_earned[]) {
	char ch = NULL, how_many = NULL;

	//the 2 rerolls
	for (int i = 0; i < 2; i++) {
		printf("reroll dice? (y/n): \n");

		do {
			ch = _getch();
		} while (ch != 'y' && ch != 'n');

		if (ch == 'y') {

			//how many dice to reroll
			printf("how many dice to reroll: \n");
			//scanf("%d", &how_many);

			do {
				how_many = _getch() - '0';
			} while (how_many < 1 || how_many > 5);

			//for how many dice, prompt one at a time, hiding result to prevent exploits
			for (int i = 0; i < how_many; i++) {

				printf("input a die to reroll (1-5): \n");
				
				do {
					ch = _getch() - '0';
				} while (ch < 1 || ch > 5);

				arr[(ch - 1)] = (rand() % 6) + 1;
			}
			//print new rolls
			print_array(arr, 5);

			if (i != 1 && ch == 'y') {
				count_rolls(arr, arr2);
				what_kind_of_score(arr2, scores_earned);
			}
		}
		//if player said no
		else {
			break;
		}
	}
}

/*
	function name: what_kind_of_score
	function description: checks what kind of score the player rolled
	preconditions: rolled dice
	date created: 10/21/2026
*/

void what_kind_of_score(int arr[], int got_what[]) {
	
	//reset got_what
	for (int i = 0; i < 6; i++) {
		got_what[i] = 0;
	}

	int long_straight_low[] = { 0, 1, 1, 1, 1, 1 }, long_straight_high[] = { 1, 1, 1, 1, 1, 0 };
	//3 of a kind
	if (sequential_search(arr, 6, 3)) {
		printf("you have three-of-a-kind\n");
		got_what[0] = 1;
	}
	if (sequential_search(arr, 6, 4)) {
		//so that if theyve already rolled 4oak, they can get the points for something else
		printf("you have three-of-a-kind\n");
		printf("you have four-of-a-kind\n");
		got_what[0] = 1;
		got_what[1] = 1;
	}
	if (sequential_search(arr, 6, 3) && sequential_search(arr, 6, 2)) {
		printf("you have a full house\n");
		got_what[2] = 1;
	}
	//too hard, brute force the straights
	if ((arr[0] >= 1 && arr[1] >= 1 && arr[2] >= 1 && arr[3] >= 1) ||  // 1-2-3-4
		(arr[1] >= 1 && arr[2] >= 1 && arr[3] >= 1 && arr[4] >= 1) ||  // 2-3-4-5
		(arr[2] >= 1 && arr[3] >= 1 && arr[4] >= 1 && arr[5] >= 1)) {  // 3-4-5-6
		printf("you have a small straight\n");
		got_what[3] = 1;
	}
	if (memcmp(arr, long_straight_low, 6 * sizeof(int)) == 0 || memcmp(arr, long_straight_high, 6 * sizeof(int)) == 0) {
		printf("you have a large straight\n");
		got_what[4] = 1;
	}
	//back to easy
	if (sequential_search(arr, 6, 5)) {
		//so that if theyve already rolled yahtzee, they can get the points for something else
		printf("you have three-of-a-kind\n");
		printf("you have four-of-a-kind\n");
		printf("you have yahtzee!!!\n");
		got_what[0] = 1;
		got_what[1] = 1;
		got_what[5] = 1;

	}
}

/*
	function name: print_array
	function description: prints an array of integers
	preconditions: an array of integers
	date created: 10/22/2026
*/
void print_array(int arr[], int size) {
	for (int i = 0; i < size; i++) {
		printf("%d", arr[i]);
	}
	printf("\n");
}

/*
	function name: welcome_script
	function description: prints the welcome script and returns the player's choice
	preconditions: a working iostream
	date created: 10/22/2026
*/

int welcome_script() {
	char ch = NULL;

	printf("welcome to yahtzee!\n"
		"press 1 to view rules\n"
		"press 2 to play game\n"
		"press 3 to exit\n");

	do {
		// Read the character instantly
		ch = _getch();
	} while (ch != '1' && ch != '2' && ch != '3');

	//ascii bullshit
	ch -= '0';
	return ch;
}

/*
	function name: add_array
	function description: adds the elements of an array together and returns the sum
	preconditions: an array of integers
	date created: 10/22/2026
*/

int add_array(int arr[], int size) {
	int result = 0;
	for (int i = 0; i < size; i++) {
		if (arr[i] != -1) {					//for the scorecard, -1 is used as a faux NULL value, so we dont want to add it to the total, shouldnt interfere with other arrays, but we'll see
			result += arr[i];
		}
	}
	return result;
}

/*
	function name: add_to_card
	function description: adds the player's score to the scorecard
	preconditions: a scorecard, an array of scores earned, an array of rolls, and an array of how many of each die was rolled
	date created: 10/22/2026
*/

void add_to_card(int scorecard[], int scores_earned[], int rolls[], int how_many[]) {
	char booboobaba = NULL;
	int choice = 0;

	//yahtzee bonus
	if (scorecard[12] == 50 && scores_earned[5]) {
		printf("earned yahtzee bonus\n");
		scorecard[14] += 100;
	}

	//sum of bonus
	if (scorecard[6] == 0) {
		if (scorecard[0] + scorecard[1] + scorecard[2] + scorecard[3] + scorecard[4] + scorecard[5] >= 63) {
			printf("earned sum of bonus\n");
			scorecard[6] = 35;
		}
	}

	do {
		//sum of 1s-6s
		if (scorecard[0] == -1) {
			printf("count as sum of 1s(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[0] = how_many[0] * 1;
				choice = 1;
			}
		}

		if (scorecard[1] == -1 && choice == 0) {
			printf("count as sum of 2s(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[1] = how_many[1] * 2;
				choice = 1;
			}
		}

		if (scorecard[2] == -1 && choice == 0) {
			printf("count as sum of 3s(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[2] = how_many[2] * 3;
				choice = 1;
			}
		}

		if (scorecard[3] == -1 && choice == 0) {
			printf("count as sum of 4s(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[3] = how_many[3] * 4;
				choice = 1;
			}
		}

		if (scorecard[4] == -1 && choice == 0) {
			printf("count as sum of 5s(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[4] = how_many[4] * 5;
				choice = 1;
			}
		}

		if (scorecard[5] == -1 && choice == 0) {
			printf("count as sum of 6s(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[5] = how_many[5] * 6;
				choice = 1;
			}
		}


		//the rest of the scorecard
		if (scorecard[7] == -1 && choice == 0) {
			printf("count as three-of-a-kind(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				if (scores_earned[0]) {
					scorecard[7] = add_array(rolls, 5);
				}
				else {
					scorecard[7] = 0;
				}
				choice = 1;
			}
		}
		if (scorecard[8] == -1 && choice == 0) {
			printf("count as four-of-a-kind(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				if (scores_earned[1]) {
					scorecard[8] = add_array(rolls, 5);
				}
				else {
					scorecard[8] = 0;
				}
				choice = 1;
			}
		}
		if (scorecard[9] == -1 && choice == 0) {
			printf("count as full house(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				if (scores_earned[2]) {
					scorecard[9] = 25;
				}
				else {
					scorecard[9] = 0;
				}
				choice = 1;
			}
		}
		if (scorecard[10] == -1 && choice == 0) {
			printf("count as small straight(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				if (scores_earned[3]) {
					scorecard[10] = 30;
				}
				else {
					scorecard[10] = 0;
				}
				choice = 1;
			}
		}
		if (scorecard[11] == -1 && choice == 0) {
			printf("count as large straight(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				if (scores_earned[4]) {
					scorecard[11] = 40;
				}
				else {
					scorecard[11] = 0;
				}
				choice = 1;
			}
		}
		if (scorecard[12] == -1 && choice == 0) {
			printf("count as yahtzee(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				if (scores_earned[5]) {
					scorecard[12] = 50;
				}
				else {
					scorecard[12] = 0;
				}
				choice = 1;
			}
		}
		if (scorecard[13] == -1 && choice == 0) {
			printf("count as chance(y/n)\n");

			do {
				booboobaba = _getch();
			} while (booboobaba != 'y' && booboobaba != 'n');

			if (booboobaba == 'y') {
				scorecard[13] = add_array(rolls, 5);
				choice = 1;
			}
		}
	} while (choice == 0);
}

/*
	function name: print_scorecard
	function description: prints the scorecard
	preconditions: a scorecard
	date created: 10/22/2026
*/

void print_scorecard(int scorecard[]) {

	printf("SCORECARD\n"
		"-------------------\n"
		"points		category\n"
		"-------------------\n");

	if (scorecard[0] == -1) {
		printf("no value	sum of 1s\n", scorecard[0]);
	}
	else {
		printf("%d		sum of 1s\n", scorecard[0]);
	}

	if (scorecard[1] == -1) {
		printf("no value	sum of 2s\n", scorecard[1]);
	}
	else {
		printf("%d		sum of 2s\n", scorecard[1]);
	}

	if (scorecard[2] == -1) {
		printf("no value	sum of 3s\n", scorecard[2]);
	}
	else {
		printf("%d		sum of 3s\n", scorecard[2]);
	}

	if (scorecard[3] == -1) {
		printf("no value	sum of 4s\n", scorecard[3]);
	}
	else {
		printf("%d		sum of 4s\n", scorecard[3]);
	}

	if (scorecard[4] == -1) {
		printf("no value	sum of 5s\n", scorecard[4]);
	}
	else {
		printf("%d		sum of 5s\n", scorecard[4]);
	}

	if (scorecard[5] == -1) {
		printf("no value	sum of 6s\n", scorecard[5]);
	}
	else {
		printf("%d		sum of 6s\n", scorecard[5]);
	}

	printf("%d		sum of bonus\n", scorecard[6]);

	if (scorecard[7] == -1) {
		printf("no value	three-of-a-kind\n", scorecard[7]);
	}
	else {
		printf("%d		three-of-a-kind\n", scorecard[7]);
	}
	
	if (scorecard[8] == -1) {
		printf("no value	four-of-a-kind\n", scorecard[8]);
	}
	else {
		printf("%d		four-of-a-kind\n", scorecard[8]);
	}
	
	if (scorecard[9] == -1) {
		printf("no value	full house\n", scorecard[9]);
	}
	else {
		printf("%d		full house\n", scorecard[9]);
	}

	if (scorecard[10] == -1) {
		printf("no value	small straight\n", scorecard[10]);
	}
	else {
		printf("%d		small straight\n", scorecard[10]);
	}
	
	if (scorecard[11] == -1) {
		printf("no value	large straight\n", scorecard[11]);
	}
	else {
		printf("%d		large straight\n", scorecard[11]);
	}
	
	if (scorecard[12] == -1) {
		printf("no value	yahtzee\n", scorecard[12]);
	}
	else {
		printf("%d		yahtzee\n", scorecard[12]);
	}

	if (scorecard[13] == -1) {
		printf("no value	chance\n", scorecard[13]);
	}
	else {
		printf("%d		chance\n", scorecard[13]);
	}
	
	printf("%d		yahtzee bonus\n", scorecard[14]);

	printf("%d		total score\n", add_array(scorecard, 15));
}


/*
	function name: reset_scorecard
	function description: resets the scorecard to its initial state for use by player 2
	preconditions: a scorecard
	date created: 10/22/2026
*/

void reset_scorecard(int scorecard[]) {
	for (int i = 0; i < 6; i++) {
		scorecard[i] = -1;
	}

	scorecard[6] = 0;

	for (int i = 7; i < 14; i++) {
		scorecard[i] = -1;
	}

	scorecard[14] = 0;
}

/*
	function name: print_rules
	function description: prints the rules of yahtzee
	preconditions: a working output stream
	date created: 10/22/2026
*/

void print_rules() {
	printf("RULES\n"
		"-------------------\n"
		"yahtzee is a game played with 5 dice\n"
		"the goal is to score the most points\n"
		"there are 13 turns per player, and each turn consists of 3 rolls of the dice\n"
		"after rolling, you may choose to reroll any number of dice up to 2 times\n"
		"after your rolls, you must choose a category to score your roll in\n"
		"each category can only be scored once per game\n"
		"the player with the most points at the end of the game wins!\n\n");

	int ch = NULL;

	do {
		printf("press 1 to return");
		ch = _getch();
	} while (ch != '1');
	system("cls");
}

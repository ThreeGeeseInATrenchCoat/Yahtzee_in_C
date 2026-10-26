#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  // needed for press_1_to_roll and welcome_script
#include <string.h> //easiest way to calculate a straight because fuck me

//sort functions
void swap_elements(int* a, int* b);
void bubble_sort(int arr[], int size);

//search functions
int sequential_search(int arr[], int size, int target);
int binary_search(int arr[], int left, int right, int target);

//game functions
void roll_dice(int arr[]);
void press_1_to_roll();
void count_rolls(int arr[], int how_many[]);
void reroll(int arr[], int arr2[], int scores_earned[], int scorecard[]);
void what_kind_of_score(int arr[], int got_what[], int scorecard[]);
void print_array(int arr[], int size);
int welcome_script();
int add_array(int arr[], int size);
void add_to_card(int scorecard[], int scores_earned[], int rolls[], int how_many[]);
void print_scorecard(int scorecard[]);
void reset_scorecard(int scorecard[]);
void print_rules();
//To run this program firstly enter "make" in terminal after that enter "./exe".
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void initialize_board(int board[][9], int problem_size); //The function that initialize the board. 
void print_board(int board[][9], int problem_size); //The function that prints the board.
int number_of_inversion(int board[][9], int problem_size); //The function that finds the number of inversion for the check solvability of board.
int find_position_of_empty_cell(int board[][9], int size); //The function that finds the position of empty cell for the check solvability of board.
int is_solvable(int board[][9], int problem_size); //The function that returns the 1 if board is solvable.
int is_game_over(int board[][9], int problem_size); //The function that checks if the game is over.
int move_function(int board[][9], int problem_size, char move, int controller); //The function that makes the movements.
void playing_game(int board[][9],int problem_size); //The function that plays the game.
int find_total_distance(int board[][9], int problem_size); //The distance of numbers from the positions to which they should be is calculated.
void create_distance_controller_array(int board[][9], int problem_size, int distance_control_array[][9]); //Array copy function.
char intelligent_move(int board[][9], int problem_size); //The function that selects the intelligent move.

int main(){

	int problem_size, solvable = 1, solvable_controller = 1, board[9][9], is_valid = 1, finish_controller = 1;

	while(is_valid){ //Checking the validity of user problem size.
		cout << "Please enter the problem size" << endl;
		cin >> problem_size;
		if(problem_size >= 3 && problem_size <= 9)  //Problem_size should be range of 3 and 9.
			is_valid = 0;
		else
			is_valid = 1;
	}
	srand(time(NULL));

	while(solvable){ //A new board is created unless the board is resolvable and finished.
		initialize_board(board, problem_size);	
		solvable_controller = is_solvable(board, problem_size);	
		finish_controller = is_game_over(board, problem_size);
		if(solvable_controller == 1 && finish_controller == 0)
			solvable = 0;
	}
	playing_game(board,problem_size);

	return 0;
}
void playing_game(int board[][9],int problem_size){

	int random, game_over, controller = 1, number_of_moves = 0;
	int control = 1, finish = 1, print_control = 1, is_move;
	char move;
	
	cout << "Your initial random board is" << endl;

	print_board(board, problem_size); //Prints the board.

	//Moves until the game is over and Q is selected. 
	//Move function is called according to the selected direction and movement is performed.
	//As the movement is made, the number of movements is increased.
	while(finish){

		cout << "Your move : ";
		cin >> move;

		if(control == 1){

			if(move != 'R' || move != 'L' || move != 'U' || move != 'D' || move != 'S'|| move != 'I')
				print_control = 0;
			if(move == 'R'){
				is_move = move_function(board, problem_size, move, controller);
				if(is_move)
					number_of_moves++;
				control = 0;
				print_control = 1;
			}
			else if(move == 'L'){
				is_move = move_function(board, problem_size, move, controller);
				if(is_move)
					number_of_moves++;
				control = 0;
				print_control = 1;
			}
			else if(move == 'U'){
				is_move = move_function(board, problem_size, move, controller);
				if(is_move)
					number_of_moves++;
				control = 0;
				print_control = 1;
			}
			else if(move == 'D'){
				is_move = move_function(board, problem_size, move, controller);
				if(is_move)
					number_of_moves++;
				control = 0;
				print_control = 1;
			}
			else if(move == 'S'){ //If S motion is selected, final solution is displayed and size * size random movement is done. 
				int i=0, j=0, k;

				for(k=1; k <= (problem_size * problem_size); k++){
					if(k == (problem_size * problem_size)){
						board[problem_size-1][problem_size-1] = -1;
					}
					else{
						if(k % (problem_size) == 0){
							board[i][j] = k;
							i++;
							j=0;
						}
						else{
							board[i][j] = k;
							j++;
						}
					}	
				}
				int random_moves = 0;
				while(random_moves < problem_size * problem_size){ //size * size random movements are performed according to the numbers 1, 2, 3 and 4.

					int move_controller;
					random = 1 + rand() % ((problem_size * problem_size));

					if(random == 1){ 
						move_controller = move_function(board, problem_size,'R',controller);
						if(move_controller == 1)
							random_moves++;
					}
					else if(random == 2){ 
						move_controller = move_function(board, problem_size, 'L', controller);
						if(move_controller == 1)
							random_moves++;
					}
					else if(random == 3){ 
						move_controller = move_function(board, problem_size, 'U', controller);
						if(move_controller == 1)
							random_moves++;
					}
					else if(random == 4){ 
						move_controller = move_function(board, problem_size, 'D', controller);
						if(move_controller == 1)
							random_moves++;
					}
				}
				print_board(board, problem_size);
				print_control = 0;
				control = 0;
				number_of_moves++; 
			}
			else if(move == 'I'){ 
				char direction;
				direction = intelligent_move(board, problem_size);
				if(direction == 'R')
					move_function(board, problem_size, 'R', controller);
				else if(direction == 'L')
					move_function(board, problem_size, 'L', controller);
				else if(direction == 'U')
					move_function(board, problem_size, 'U', controller);
				else if(direction == 'D')
					move_function(board, problem_size, 'D', controller);
				cout << "Intelligent move chooses " << direction << endl;
				control = 0;
				print_control = 1;
				number_of_moves++;
			}
			else if(move == 'Q') //If the user enters Q, the program ends.
				finish = 0;
		}		
		game_over = is_game_over(board, problem_size); //After each move, it is checked whether the game is over or not.
		//If the game is finished the board and the necessary information is suppressed. Then the program ends.
		if(game_over == 1){ 
			print_board(board, problem_size);
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout << "Total number of moves " << number_of_moves << endl;
			print_control = 0;
			finish = 0;
		}
		control = 1;

		if(print_control == 1) //The board is printed after each move.
			print_board(board, problem_size);
		print_control = 1;
	}
}
//size * size random number is generated
//When creating a random board, it is controlled to use a number once.
//When the number size * size is created, -1 is assigned to be used as spaces.
void initialize_board(int board[][9], int problem_size){

	int i, j, k, l=0, controller = 0, controller_array[82], flag = 1, random;

	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			flag = 1;
			random = 1 + rand() % ((problem_size * problem_size));
			for(k=0; k < controller; k++){
				if(random == controller_array[k])
					flag = 0;	
			}
			if(flag == 1){
				controller_array[l] = random;
				board[i][j] = random;
				controller++;
				l++;	
			}
			else if(flag == 0){
				if (j == 0){
					i--;
					j = (problem_size-1);		
				}
				else
					j--;
			}
		}
	}	
	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			if(board[i][j] == (problem_size * problem_size))
				board[i][j] = -1;
		}
	}
}
void print_board(int board[][9], int problem_size){ //The board is printed. The cell with -1 is printed as a space.

	int i, j;

	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			if(board[i][j] == -1)
				cout << " \t";
			else
				cout << board[i][j] << "\t" ;	
		}
		cout << endl ;
	}
	cout << endl;
}
//The number of inversion is checked for the solvable control.
//Inversion is how many smaller numbers after the current number.
//While the inversion number is found, the index with -1 is ignored.
//If the number of inversion even returns 1 else returns 0. 
int number_of_inversion(int board[][9], int problem_size){ 

	int i, j, k=0, control = 0, inversion_controller_array[82], inversion = 0;

	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			inversion_controller_array[k] = board[i][j];
			k++;
		}
	}
	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			if(board[i][j] != -1){
				for(k=control+1; k < (problem_size * problem_size); k++){
					if(inversion_controller_array[k] != -1 && board[i][j] > inversion_controller_array[k])
						inversion++;
				}
			}
			control++;
		}
	}
	if(inversion % 2 == 0)
		return 1;
	else
		return 0;
}
//For solvable control, the position of the empty cell relative to the bottom row is checked.
//If the empty cell is on an odd-numbered line from the bottom, 1 is returned, and 0 on the even-numbered line.
int find_position_of_empty_cell(int board[][9], int problem_size){ 

	int i, j;

	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			if(board[i][j] == -1){
				if(i % 2 == 0) //çift satırdaysa
					return 0;
				else
					return 1;
			}
		}
	}
}
//If the board is solvable return 1.
int is_solvable(int board[][9], int problem_size){ 

	int controller_1, controller_2;

	controller_1 = find_position_of_empty_cell(board, problem_size);
	controller_2 = number_of_inversion(board, problem_size);

	if(problem_size % 2 == 0){ //If the problem_size is even
		if(controller_1 == 0 && controller_2 == 0) //The empty cell must be in even row and the inversion number must be odd.
			return 1;
		if(controller_1 == 1 && controller_2 == 1) //The empty cell must be in odd row and the inversion number must be even.
			return 1;
		else
			return 0;
	}
	else{ //if the problem_size is odd
		if(controller_2 == 1) //The number of inversion should be even.
			return 1;
		else
			return 0;
	}
}
int is_game_over(int board[][9], int problem_size){ //Check whether the game is over or not.For indexes where numbers must be present, 1 is returned.

	int temp_array[82], i, j, k = 0, game_over = 0;

	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			temp_array[k] = board[i][j];
			k++;
		}
	}
	for(i=0; i < (problem_size * problem_size) - 2; i++){
		if(temp_array[i] < temp_array[i+1])
			game_over++;
	}
	if(game_over == ((problem_size * problem_size) - 2) && temp_array[(problem_size * problem_size) - 1] == -1)
		return 1;
	else
		return 0 ;
}
int move_function(int board[][9], int problem_size, char move, int controller){ //It is the function where movements are made.

	int i, j;

	if(move == 'R'){ //The empty cell is moved in the right direction.
		for(i=0; i < problem_size && controller == 1; i++){
			for(j=0; j < problem_size && controller == 1; j++){
				if(board[i][j] == -1){		
					if(j != (problem_size - 1)){ //If the right side does not exceed the board limit, movement is made.
						int right_temp_number;

						right_temp_number = board[i][j+1];
						board[i][j+1] = -1;
						board[i][j] = right_temp_number;
						controller = 0;

						return 1;
					}
				}
			}
		}
	}
	else if(move == 'L'){ //The empty cell is moved in the left direction.
		for(i=0; i < problem_size; i++){
			for(j=0; j < problem_size; j++){
				if(board[i][j] == -1){
					if(j != 0){ //If the left side does not exceed the board limit, movement is made.
						int left_temp_number;

						left_temp_number = board[i][j-1];
						board[i][j-1] = -1;
						board[i][j] = left_temp_number;

						return 1;
					}
				}
			}
		}
	}
	else if(move == 'U'){ //The empty cell is moved in the up.
		for(i=0; i < problem_size; i++){
			for(j=0; j < problem_size; j++){
				if(board[i][j] == -1){
					if(i != 0){ //If the up side does not exceed the board limit, movement is made.
						int up_temp_number;

						up_temp_number = board[i-1][j];
						board[i-1][j] = -1;
						board[i][j] = up_temp_number;

						return 1;
					}
				}
			}
		}
	}
	else if(move == 'D'){ //The empty cell is moved in the down.
		for(i=0; i < problem_size && controller == 1; i++){
			for(j=0; j < problem_size && controller == 1; j++){
				if(board[i][j] == -1){			
					if(i != (problem_size - 1)){ //If the down side does not exceed the board limit, movement is made.
						int down_temp_number;

						down_temp_number = board[i+1][j];
						board[i+1][j] = -1;
						board[i][j] = down_temp_number;
						controller = 0;

						return 1;
					}
				}
			}
		}
	}
	return 0;
}
int find_total_distance(int board[][9], int problem_size){

	int i, j, my_number = 1, final_position_i=0, final_position_j=0, division, total_distance = 0;

	while (my_number <= problem_size * problem_size){ //The distance of all numbers on the map to the required positions is calculated.
		for(i=0; i < problem_size; i++){
			for(j=0; j < problem_size; j++){
				if(board[i][j] == my_number){					
					if(my_number % problem_size == 0){
						final_position_j = problem_size - 1; 
						division = my_number / problem_size;
						final_position_i = division - 1;
					}
					else{
						final_position_i = my_number / problem_size;
						final_position_j = (my_number % problem_size) - 1;
					}
					total_distance = total_distance + abs(i - final_position_i) + abs(j - final_position_j);//Distance from numbers to locations

					my_number++;
				}
				//The distance of the empty cell to the position it should be located is calculated.
				else if(board[i][j] == -1 && my_number == problem_size * problem_size){
					final_position_i = problem_size - 1; 
					final_position_j = problem_size - 1;

					total_distance = total_distance + abs(i - final_position_i) + abs(j - final_position_j);
					my_number++;
				}
			}
		}
	}
	return total_distance;
}
void create_distance_controller_array(int board[][9], int problem_size, int distance_control_array[][9]){ //Array copy operation is performed.

	int i, j;

	for(i=0; i < problem_size; i++){
		for(j=0; j < problem_size; j++){
			distance_control_array[i][j] = board[i][j];
		}
	}
}
//The copied array is used to determine which of the actions is more intelligent.
//The total distance after each movement is kept in a temp_arr for each movement.
//Whichever of these actions is more profitable is chosen as intelligent move.
//If a non-available direction is selected, a large number is assigned to the temp_arr index and that direction is ignored.
char intelligent_move(int board[][9], int problem_size){

	int controller = 1, temp_arr[4] ={1, 2 ,3,4}, i, min_total_distance = 0, choose_direction = 0;
	int distance_control_array[9][9], available, large_number = 10000;

	create_distance_controller_array(board, problem_size,distance_control_array);
	available = move_function(distance_control_array, problem_size, 'R', controller );
	if(available)
		temp_arr[0] = find_total_distance(distance_control_array, problem_size);
	else
		temp_arr[0] = large_number;

	create_distance_controller_array(board, problem_size,distance_control_array);
	available = move_function(distance_control_array, problem_size, 'L', controller );
	if(available)
		temp_arr[1] = find_total_distance(distance_control_array, problem_size);
	else
		temp_arr[1] = large_number;
	
	create_distance_controller_array(board, problem_size,distance_control_array);
	available = move_function(distance_control_array, problem_size, 'U', controller );
	if(available)
		temp_arr[2] = find_total_distance(distance_control_array, problem_size);
	else
		temp_arr[2] = large_number;
	
	create_distance_controller_array(board, problem_size,distance_control_array);
	available = move_function(distance_control_array, problem_size, 'D', controller );
	if(available)
		temp_arr[3] = find_total_distance(distance_control_array, problem_size);
	else
		temp_arr[3] = large_number;
	
	min_total_distance = temp_arr[0];

	for(i=0; i < 4; i++){
		if(temp_arr[i] < min_total_distance){
			min_total_distance = temp_arr[i];
			choose_direction = i;
		}
	}
	if(choose_direction == 0)
		return 'R';
	else if(choose_direction == 1)
		return 'L';
	else if(choose_direction == 2)
		return 'U';
	else if(choose_direction == 3)
		return 'D';
}

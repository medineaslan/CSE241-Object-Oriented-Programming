//To run this program firstly enter "make" in terminal after that enter "./exe".
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

const int array_size = 9;
const int max_board_size = 82;

void initialize_board(int board[][array_size], int problem_size); //The function that initialize the board. 
int number_of_inversion(int board[][array_size], int problem_size); //The function that finds the number of inversion for the check solvability of board.
int find_position_of_empty_cell(int board[][array_size], int size); //The function that finds the position of empty cell for the check solvability of board.
int is_solvable(int board[][array_size], int problem_size); //The function that returns the 1 if board is solvable.
int is_game_over(int board[][array_size], int problem_size, int line_number, int total_space_number, int file_board_control); //The function that checks if the game is over.
int move_function(int board[][array_size], int problem_size, char move, int controller, int line_number, int total_space_number, int file_board_control); //The function that makes the movements.
void playing_game(int board[][array_size],int problem_size, int line_number, int total_space_number, int file_control); //The function that plays the game.
int find_total_distance(int board[][array_size], int problem_size, int line_number, int total_space_number, int file_board_control); //The distance of numbers from the positions to which they should be is calculated.
void create_distance_controller_array(int board[][array_size], int problem_size, int distance_control_array[][array_size],int line_number, int total_space_number, int file_board_control); //Array copy function.
char intelligent_move(int board[][array_size], int problem_size, int line_number, int total_space_number, int file_board_control); //The function that selects the intelligent move.
inline void print_board_from_the_file(int board[][array_size], int line_number, int total_space_number); //The function that prints the board that came from file.
inline void print_board(int board[][array_size], int problem_size); //The function that prints the board.
inline int calculate_digit_number(int number);

int main(const int argc, const char* argv[]){

	int problem_size, board[array_size][array_size];
	auto solvable = 1, solvable_controller = 1,  is_valid = 1, finish_controller = 1;
	auto line_number = 1, total_space_number = 1, file_board_control = 1, my_line_number = 0, my_total_space = 0, file_control = 1;

	if(argv[1] == NULL){ // There is no command line argument.
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
			finish_controller = is_game_over(board, problem_size, line_number, total_space_number, file_board_control);
			if(solvable_controller == 1 && finish_controller == 0)
				solvable = 0;
		}
		cout << "Your initial random board is" << endl;
		file_control = 1;
		playing_game(board, problem_size, line_number, total_space_number, file_control);
	}
	else{ //If there is  command line argument.
		ifstream input_file;
		string line, load_file;
		load_file = argv[1];
		input_file.open(load_file.c_str());

		while(getline(input_file,line)){ //Read lines from file
			my_line_number++; // Calculate line number.
			for(int i = 0; i < line.size(); ++i){
				if(line.at(i) == ' ')
					my_total_space++; //Calculate all spaces in the file.
			}
		}
		input_file.close();

		line_number = my_line_number;
		total_space_number = my_total_space;

		input_file.open(load_file.c_str());

		int i, j;
		char temp_ch_array[line_number][(total_space_number/line_number)*2 + 2];

		for(i=0; i < line_number; i++){ //Read elements from the file.
			for(j=0; j < (total_space_number / line_number) * 2 + 2; j++){
				input_file >> temp_ch_array[i][j];
			}
		}
		input_file.close();

		for(i=0; i < line_number; i++){ //Convert string to integer.
			for(j=0; j < (total_space_number / line_number) * 2 + 2; j=j+2){
				char  first_index, second_index;
				string str_1, str_2, string_number;
				int number;

				first_index = temp_ch_array[i][j];
				second_index = temp_ch_array[i][j + 1];
				if(first_index == 'b') //Assign -1 for space.
					number = -1;
				else{
					str_1 = str_1 + first_index; 
					str_2 = str_2 + second_index;
					string_number = str_1 + str_2;

					number = stoi(string_number);
				}
				board[i][j/2] = number;
			}
		}
		file_control = 0;
		playing_game(board,problem_size,line_number,total_space_number, file_control);		
	}
	return 0;
}
void playing_game(int board[][array_size],int problem_size, int line_number, int total_space_number, int file_control){

	int random, game_over, is_move;
	auto controller = 1, number_of_moves = 0;
	auto control = 1, finish = 1, print_control = 1;
	auto file_board_control = 1, print_board_controller = 1;
	auto my_line_number=0, my_total_space = 0;
	char move;

	if(file_control == 1)
		print_board(board, problem_size); //Prints the board.
	else{
		print_board_from_the_file(board,line_number,total_space_number);
		file_board_control = 0;
	}
	//Moves until the game is over and Q is selected. 
	//Move function is called according to the selected direction and movement is performed.
	//As the movement is made, the number of movements is increased.
	while(finish){

		cout << "Your move : ";
		cin >> move;

		if(control == 1){
			if(move != 'R' || move != 'L' || move != 'U' || move != 'D' || move != 'S'|| move != 'I' || move != 'Y' || move != 'T' || move != 'E' || move != 'V')
				print_control = 0;
			if(move == 'R'){
				if(file_board_control == 0){
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 0;
					print_board_from_the_file(board, line_number, total_space_number);
					print_board_controller = 0;
				}
				else{
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 1;
				}
			}
			else if(move == 'L'){
				if(file_board_control == 0){
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 0;
					print_board_from_the_file(board, line_number, total_space_number);
					print_board_controller = 0;
				}
				else{
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 1;
				}
			}
			else if(move == 'U'){
				if(file_board_control == 0){
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 0;
					print_board_from_the_file(board, line_number, total_space_number);
					print_board_controller = 0;
				}
				else{
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 1;
				}
			}
			else if(move == 'D'){
				if(file_board_control == 0){
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 0;
					print_board_from_the_file(board, line_number, total_space_number);
					print_board_controller = 0;
				}
				else{
					is_move = move_function(board, problem_size, move, controller, line_number, total_space_number, file_board_control);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = 1;
				}
			}
			else if(move == 'S'){ //If S motion is selected, final solution is displayed and size * size random movement is done. 
				if(file_board_control == 1){ //If board is randomly formed. 
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
					print_board(board, problem_size);
					int random_moves = 0;
					while(random_moves < problem_size * problem_size){ //size * size random movements are performed according to the numbers 1, 2, 3 and 4.

						int move_controller;
						random = 1 + rand() % 4;

						if(random == 1){ 
							move_controller = move_function(board, problem_size,'R',controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves++;
						}
						else if(random == 2){ 
							move_controller = move_function(board, problem_size, 'L', controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves++;
						}
						else if(random == 3){ 
							move_controller = move_function(board, problem_size, 'U', controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves++;
						}
						else if(random == 4){ 
							move_controller = move_function(board, problem_size, 'D', controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves++;
						}
					}
					print_board(board, problem_size);
					print_control = 0;
					control = 0;
					number_of_moves++;
				}

				else{ //If board read from file.
					int my_number = 1, i, j;

					for(i=0; i < line_number; i++){ //Takes final board.
						for(j=0; j < (total_space_number / line_number) +  1; j++){
							if(board[i][j] != 0){
								board[i][j] = my_number; 
								my_number++;
							}
							if(i == line_number - 1 && j == (total_space_number / line_number))
								board[i][j] = -1;
						}
					}
					print_board_from_the_file(board, line_number, total_space_number);

					int random_moves_file = 0;
					int move_number = (line_number) * ((total_space_number / line_number) +  1);

					while(random_moves_file < move_number){ //Make size * size random move.
						int move_controller;
						random = 1 + rand() % 4;

						if(random == 1){ 
							move_controller = move_function(board, problem_size,'R',controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves_file++;
						}
						else if(random == 2){ 
							move_controller = move_function(board, problem_size, 'L', controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves_file++;
						}
						else if(random == 3){ 
							move_controller = move_function(board, problem_size, 'U', controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves_file++;
						}
						else if(random == 4){ 
							move_controller = move_function(board, problem_size, 'D', controller, line_number, total_space_number, file_board_control);
							if(move_controller == 1)
								random_moves_file++;
						}
					}
					print_board_from_the_file(board, line_number, total_space_number);
					print_board_controller = 0;
					print_control = 0;
					control = 0;
					number_of_moves++;
				}
			}
			else if(move == 'I'){ //Choose intelligent move.
				char my_direction;

				my_direction = intelligent_move(board, problem_size, line_number, total_space_number, file_board_control);
				if(my_direction == 'R')
					move_function(board, problem_size, 'R', controller, line_number, total_space_number, file_board_control);
				else if(my_direction == 'L')
					move_function(board, problem_size, 'L', controller, line_number, total_space_number, file_board_control);
				else if(my_direction == 'U')
					move_function(board, problem_size, 'U', controller, line_number, total_space_number, file_board_control);
				else if(my_direction == 'D')
					move_function(board, problem_size, 'D', controller, line_number, total_space_number, file_board_control);
				cout << "Intelligent move chooses " << my_direction << endl;
				control = 0;
				number_of_moves++;
				if(file_board_control == 1)
					print_control = 1;
				else{
					print_board_from_the_file(board, line_number, total_space_number);
					print_board_controller = 0;
				}
			}
			else if(move == 'T'){ //Number of moves printed.
				number_of_moves++;
				cout << number_of_moves << " moves have been done." << endl ;
				cout << "Solution is not found." << endl;
				cout << endl;
				if(file_board_control == 1)
					print_control = 1;
				else{
					print_board_from_the_file(board, line_number, total_space_number);
					print_control = 0;
				}
			}
			else if(move == 'E'){ //Asks a file name and saves board in the file.
				ofstream save_file;
				string save;
				cout << "File name: ";
				cin >> save;
				save_file.open(save.c_str());
				int i, j;
				if(file_board_control == 0){ //If board comes from file.
					for (i=0; i < line_number; ++i){
						for (j=0; j < (total_space_number/line_number) + 1; ++j){
							if(board[i][j] != -1){
								int digit = calculate_digit_number(board[i][j]);
								if(digit < 2){
									save_file << "0" << board[i][j];
									if(j != (total_space_number/line_number))
										save_file << " ";
								}
								else{
									save_file << board[i][j] ;
									if(j != (total_space_number/line_number))
										save_file << " ";
								}
							}
							else{
								save_file << "bb" ;
								if(j != (total_space_number/line_number))
									save_file << " ";
							}
						}
						save_file << endl;
					}
					number_of_moves++;
					print_control = 0;
					print_board_from_the_file(board, line_number, total_space_number);
				}
				else{ //If board comes randomly. 
					for(i=0; i < problem_size; i++){
						for(j=0; j < problem_size; j++){
							if(board[i][j] == -1 ){
								save_file << "bb";
								if(j != problem_size - 1)
									save_file << " ";
							}
							else{
								if(board[i][j] != -1){
									if(board[i][j] <= 9){
										save_file << "0" << board[i][j];
									}
									else{
										save_file << board[i][j];
									}
									if(j != (problem_size-1))
										save_file << " ";	
								}
							}
						}
						if(i != problem_size - 1){
							save_file << endl ;
						}
					}
					save_file << endl;
					number_of_moves++;
					print_board(board, problem_size);
					problem_size = 0;
				}
				save_file.close();
			}
			else if(move == 'Y'){ //Asks a file name and load board from the file.
				
				ifstream input_file;
				string line, load_file;
				cout << "File name: ";
				cin >> load_file;
				input_file.open(load_file.c_str());

				while(getline(input_file,line)){
					my_line_number++;
					for(int i = 0; i < line.size(); ++i){
						if(line.at(i) == ' ')
							my_total_space++;
					}
				}
				input_file.close();

				line_number = my_line_number;
				total_space_number = my_total_space;

				input_file.open(load_file.c_str());

				int i, j;
				char temp_ch_array [line_number][(total_space_number/line_number)*2 + 2];

				for(i=0; i < line_number; i++){
					for(j=0; j < (total_space_number / line_number) * 2 + 2; j++){
						input_file >> temp_ch_array[i][j];
					}
				}
				input_file.close();

				for(i=0; i < line_number; i++){
					for(j=0; j < (total_space_number / line_number) * 2 + 2; j=j+2){
						char  first_index, second_index;
						string str_1, str_2, string_number;
						int number;

						first_index = temp_ch_array[i][j];
						second_index = temp_ch_array[i][j + 1];
						if(first_index == 'b')
							number = -1;
						else{
							str_1 = str_1 + first_index; // char to string
							str_2 = str_2 + second_index;
							string_number = str_1 + str_2; // string toplama

							number = stoi(string_number);
						}
						board[i][j/2] = number;
					}
				}
				control = 0;
				print_control = 0;
				file_board_control = 0;
				number_of_moves++;
				print_board_from_the_file(board, line_number, total_space_number);
			}
			else if(move == 'V'){ //Solves problem using the new intelligent algorithm.
				int solution_control = 1, i, random_move, escape_stuck = 1;
				char old_one, next_one;

				if(file_board_control == 0){ //The board came from file.
					while(solution_control){
						for(i=0; escape_stuck && solution_control == 1; i++){
							next_one = intelligent_move(board,problem_size,line_number, total_space_number, file_board_control);
							if(next_one == 'R' && old_one == 'L') //If there is a stuck.
								escape_stuck = 0;
							else if(next_one == 'L' && old_one == 'R')
								escape_stuck = 0;
							else if(next_one == 'U' && old_one == 'D')
								escape_stuck = 0;
							else if(next_one == 'D' && old_one == 'U')
								escape_stuck = 0;

							if(escape_stuck == 1){ //If there is no stuck, it makes intelligent move.
								move_function(board,problem_size,next_one,controller, line_number, total_space_number, file_board_control);
								number_of_moves++;
								old_one = next_one;
								cout << "Intelligent move chooses " << next_one << endl;
								print_board_from_the_file(board, line_number, total_space_number);
							}
							if(is_game_over(board, problem_size, line_number, total_space_number, file_board_control))
								solution_control = 0;
						}
						escape_stuck = 1;
						for(i=0; i < 3 && solution_control == 1; i++){ //In the stuck it moves 3 times randomly.
							random_move = 1 + rand() % 4;
							if(random_move == 1){
								move_function(board,problem_size,'R', controller, line_number, total_space_number, file_board_control);
								number_of_moves++;
								print_board_from_the_file(board, line_number, total_space_number);
							}
							else if(random_move == 2){
								move_function(board,problem_size,'L', controller, line_number, total_space_number, file_board_control);
								number_of_moves++;
								print_board_from_the_file(board, line_number, total_space_number);
							}
							else if(random_move == 3){
								move_function(board,problem_size,'U', controller, line_number, total_space_number, file_board_control);
								number_of_moves++;
								print_board_from_the_file(board, line_number, total_space_number);
							}
							else if(random_move == 4){
								move_function(board,problem_size,'D', controller, line_number, total_space_number, file_board_control);
								number_of_moves++;
								print_board_from_the_file(board, line_number, total_space_number);
							}
							if(is_game_over(board, problem_size, line_number, total_space_number, file_board_control))
								solution_control = 0;
						}
					}
				}
				else{ //If board came raandomly.
					int solution_control = 1, i, random_move, escape_stuck = 1,is_valid_way =1;
					char old_one, next_one;
					while(solution_control){
						escape_stuck = 1;
						for(i=0; escape_stuck && solution_control == 1; i++){
							next_one = intelligent_move(board, problem_size, line_number, total_space_number, file_board_control);
							if(next_one == 'R' && old_one == 'L')
								escape_stuck = 0;
							else if(next_one == 'L' && old_one == 'R')
								escape_stuck = 0;
							else if(next_one == 'U' && old_one == 'D')
								escape_stuck = 0;
							else if(next_one == 'D' && old_one == 'U')
								escape_stuck = 0;

							if(escape_stuck == 1){
								move_function(board,problem_size,next_one,controller, line_number, total_space_number, file_board_control);
								number_of_moves++;
								old_one = next_one;
								print_board(board, problem_size);
							}
							if(is_game_over(board, problem_size, line_number, total_space_number, file_board_control))
								solution_control = 0;
						}
						i=0;
						while( i < 3 && solution_control == 1){
							random_move = 1 + rand() % 4;
							if(random_move == 1){
								is_valid_way = move_function(board,problem_size,'R', controller, line_number, total_space_number, file_board_control);
								if(is_valid_way){ //If there is a valid direction, the number of movements is increased.
									number_of_moves++;
									print_board(board, problem_size);
									i++;
								}
							}
							else if(random_move == 2){
								is_valid_way = move_function(board,problem_size,'L', controller, line_number, total_space_number, file_board_control);
								if(is_valid_way){
									number_of_moves++;
									print_board(board, problem_size);
									i++;
								}
							}
							else if(random_move == 3){
								is_valid_way = move_function(board,problem_size,'U', controller, line_number,total_space_number, file_board_control);
								if(is_valid_way){
									number_of_moves++;
									print_board(board, problem_size);
									i++;
								}
							}
							else if(random_move == 4){
								is_valid_way = move_function(board,problem_size,'D', controller,line_number, total_space_number, file_board_control);
								if(is_valid_way){
									number_of_moves++;
									print_board(board, problem_size);
									i++;
								}
							}
							if(is_game_over(board, problem_size, line_number, total_space_number, file_board_control))
								solution_control = 0;
						}
					}
				}
				number_of_moves++;
			}
			else if(move == 'Q') //If the user enters Q, the program ends.
				finish = 0;
		}
		/*After each move, it is checked whether the game is over or not.
		If the game is finished the board and the necessary information is suppressed. Then the program ends.*/
		if(file_board_control == 0)
			game_over = is_game_over(board, problem_size, line_number, total_space_number, file_board_control);
		else
			game_over = is_game_over(board, problem_size, line_number, total_space_number, file_board_control);
		
		if(game_over == 1 && file_board_control == 1){ 
			print_board(board, problem_size);
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout << "Total number of moves " << number_of_moves << endl;
			print_control = 0;
			finish = 0;
		}
		else if(game_over == 1 && file_board_control == 0){
			if(print_board_controller == 1){
				print_board_from_the_file(board, line_number, total_space_number);
			}
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout << "Total number of moves " << number_of_moves << endl;
			print_control = 0;
			finish = 0;
		}
		control = 1;
		my_line_number = 0;
		my_total_space = 0;

		if(print_control == 1)//The board is printed after each move.
			print_board(board, problem_size);
		print_control = 1;
	}
}
//size * size random number is generated
//When creating a random board, it is controlled to use a number once.
//When the number size * size is created, -1 is assigned to be used as spaces.
void initialize_board(int board[][array_size], int problem_size){

	int i, j, k, controller_array[max_board_size];
	decltype(i) random;
	auto l=0,flag = 1,controller = 0;
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
inline void print_board(int board[][array_size], int problem_size){ //The board is printed. The cell with -1 is printed as a space.

	int i;
	decltype(i) j;

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
int number_of_inversion(int board[][array_size], int problem_size){ 

	int i, inversion_controller_array[max_board_size];
	decltype(i) j; 
	auto k=0, control = 0, inversion = 0;

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
int find_position_of_empty_cell(int board[][array_size], int problem_size){ 

	int i;
	decltype(i) j;

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
int is_solvable(int board[][array_size], int problem_size){ 

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
int is_game_over(int board[][array_size], int problem_size, int line_number, int total_space_number, int file_board_control){ //Check whether the game is over or not.For indexes where numbers must be present, 1 is returned.

	int temp_array[max_board_size], i, j, size1;
	decltype(size1) size2;
	auto k = 0, game_over = 0,controller = 0;
	if(file_board_control == 1){
		size1 = problem_size;
		size2 = problem_size;
	}
	else{
		size1 = line_number;
		size2 = (total_space_number / line_number) + 1;
	}
	if(file_board_control == 1){
		for(i=0; i < size1; i++){
			for(j=0; j < size2; j++){
				temp_array[k] = board[i][j];
				k++;
			}
		}
		for(i=0; i < (size1 * size2) - 2; i++){
			if(temp_array[i] < temp_array[i+1])
				game_over++;
		}
		if(game_over == ((size1 * size2) - 2) && temp_array[(size1 * size2) - 1] == -1)
			return 1;
		else
			return 0 ;
	}
	else{
		k=0;
		game_over = 0;
		for(i=0; i < size1; i++){
			for(j=0; j < size2; j++){
				if(board[i][j] != 0){
					temp_array[k] = board[i][j];
					k++;
					controller++;
				}
			}
		}
		for(i=0; i < controller-2; i++){
			if(temp_array[i] < temp_array[i+1]){
				game_over++;
			}
		}
		if(game_over == (controller - 2) && temp_array[controller - 1] == -1)
			return 1;
		else
			return 0 ;
	}
}
int move_function(int board[][array_size], int problem_size, char move, int controller, int line_number, int total_space_number, int file_board_control){ //It is the function where movements are made.

	int i, j, row_num;
	decltype(i) column_num;

	if(file_board_control == 1){
		row_num = problem_size;
		column_num = problem_size;
	}
	else{
		row_num = line_number;
		column_num = (total_space_number / line_number) + 1;
	}
	if(move == 'R'){ //The empty cell is moved in the right direction.
		for(i=0; i < row_num; i++){
			for(j=0; j < column_num && controller == 1; j++){
				if(board[i][j] == -1){	
					if(j != (column_num - 1) && board[i][j+1] != 0){ //If the right side does not exceed the board limit, movement is made.
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
		for(i=0; i < row_num; i++){
			for(j=0; j < column_num; j++){
				if(board[i][j] == -1){
					if(j != 0 && board[i][j-1] != 0){ //If the left side does not exceed the board limit, movement is made.
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
		for(i=0; i < row_num; i++){
			for(j=0; j < column_num; j++){
				if(board[i][j] == -1){
					if(i != 0 && board[i-1][j] != 0){ //If the up side does not exceed the board limit, movement is made.
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
		for(i=0; i < row_num && controller == 1; i++){
			for(j=0; j < column_num && controller == 1; j++){
				if(board[i][j] == -1){			
					if(i != (row_num - 1) && board[i+1][j] != 0){ //If the down side does not exceed the board limit, movement is made.
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
int find_total_distance(int board[][array_size], int problem_size, int line_number, int total_space_number, int file_board_control){

	if(file_board_control == 1){
		int i, j;
		decltype(i) division; 
		auto my_number = 1, final_position_i=0, final_position_j=0, total_distance = 0;
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
	else{ //The distance of all numbers on the map to the required positions is calculated for board came from the file.
		int i, j,k=0,a=0, number_of_elements = 0, my_number = 1;
		int column = (total_space_number / line_number) + 1;
		int find_position_i[line_number*column], find_position_j[line_number*column], control=1, total_distance = 0;

		for(i=0; i < line_number; i++){
			for(j=0; j < column; j++){
				if(board[i][j] != 0)
					number_of_elements++;
			}
		}
		for(i=0; i < line_number; i++){
			for(j=0; j < column; j++){
				if(board[i][j] != 0){
					find_position_i[k] = i;
					find_position_j[k] = j;
					k++;
				}
			}
		}
		while(my_number <= number_of_elements){
			for(i=0; i < line_number; i++){
				for(j=0; j < column; j++){
					if(board[i][j] == my_number){
						total_distance += abs(i - find_position_i[a]) + abs(j - find_position_j[a]);
						a++;
						my_number++;
					}
					else if(board[i][j] == -1 && my_number == number_of_elements){
						total_distance += abs(i - find_position_i[number_of_elements - 1]) + abs(j- find_position_j[number_of_elements - 1]);
						my_number++;

					}
				}
			}
		}
		return total_distance;
	}
}
//Array copy operation is performed.
void create_distance_controller_array(int board[][array_size], int problem_size, int distance_control_array[][array_size],int line_number, int total_space_number, int file_board_control){ 

	int i, j, size1, size2;

	if(file_board_control == 1){
		size1 = problem_size;
		size2 = problem_size;
	}
	else{
		size1 = line_number;
		size2 = (total_space_number / line_number) + 1;
	}
	for(i=0; i < size1; i++){
		for(j=0; j < size2; j++){
			distance_control_array[i][j] = board[i][j];
		}
	}
}
//The copied array is used to determine which of the actions is more intelligent.
//The total distance after each movement is kept in a temp_arr for each movement.
//Whichever of these actions is more profitable is chosen as intelligent move.
//If a non-available direction is selected, a large number is assigned to the temp_arr index and that direction is ignored.
char intelligent_move(int board[][array_size], int problem_size, int line_number, int total_space_number, int file_board_control){

	int controller = 1, temp_arr[4] ={1, 2 ,3,4}, i, min_total_distance = 0, choose_direction = 0;
	int distance_control_array[array_size][array_size], available, large_number = 10000, my_controller_array[array_size][array_size];

	create_distance_controller_array(board, problem_size, distance_control_array, line_number, total_space_number, file_board_control);
	available = move_function(distance_control_array, problem_size, 'R', controller, line_number, total_space_number, file_board_control);
	if(available)
		temp_arr[0] = find_total_distance(distance_control_array, problem_size, line_number, total_space_number, file_board_control);
	else
		temp_arr[0] = large_number;

	create_distance_controller_array(board, problem_size, distance_control_array, line_number, total_space_number, file_board_control);
	available = move_function(distance_control_array, problem_size, 'L', controller, line_number, total_space_number, file_board_control);
	if(available)
		temp_arr[1] = find_total_distance(distance_control_array, problem_size, line_number, total_space_number, file_board_control);
	else
		temp_arr[1] = large_number;
	
	create_distance_controller_array(board, problem_size, distance_control_array, line_number, total_space_number, file_board_control);
	available = move_function(distance_control_array, problem_size, 'U', controller, line_number, total_space_number, file_board_control);
	if(available)
		temp_arr[2] = find_total_distance(distance_control_array, problem_size, line_number, total_space_number, file_board_control);
	else
		temp_arr[2] = large_number;
	
	create_distance_controller_array(board, problem_size, distance_control_array, line_number, total_space_number, file_board_control);
	available = move_function(distance_control_array, problem_size, 'D', controller, line_number, total_space_number, file_board_control);
	if(available)
		temp_arr[3] = find_total_distance(distance_control_array, problem_size, line_number, total_space_number, file_board_control);
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
inline int calculate_digit_number(int number){

	int count = 0;

	while(number > 0){
		number = number / 10;
		count++;
	}
	return count;
}
inline void print_board_from_the_file(int board[][array_size], int line_number, int total_space_number){//The function that prints the board that came from file.

	int i, j;

	for (i=0; i < line_number; ++i) {
		for (j=0; j < (total_space_number/line_number) + 1; ++j) {
			if(board[i][j] != -1){
				int digit = calculate_digit_number(board[i][j]);
				if(digit < 2)
					cout << "0" << board[i][j] << " ";
				else
					cout << board[i][j] << " ";
			}
			else
				cout << "bb" << " ";	
		}
		cout << endl;
	}
	cout << endl;
}
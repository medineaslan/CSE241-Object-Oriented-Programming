#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

class NPuzzle
{
public:
	inline void print(){myBoard.print();} //Prints the current configuration on the screen by sending it to cout.
	inline void printReport(int numberOfMovesValue){myBoard.printReport(numberOfMovesValue);} //Prints a report about how many moves have been done.
	inline void readFromFile(const string fileName){myBoard.readFromFile(fileName);} //Reading from file.
	inline void writeToFile(const string fileName){myBoard.writeToFile(fileName);} //Writing to file.
	inline void shuffle(const int N){myBoard.shuffle(N);} //Makes N random move.
	inline void reset(){myBoard.reset();} //Reset the board.
	inline bool setsize(int rowValue, int columnValue){myBoard.setSize(rowValue, columnValue);} //Set the board size given values.
	inline void moveRandom(){myBoard.moveRandom();} //Makes random move.
	inline char moveIntelligent(){myBoard.moveIntelligent();} //Makes intelligent move.
	inline bool moveForIntelligent(int tempArr[][9], char move, int controller){myBoard.moveForIntelligent(tempArr, move, controller);} //This functions works for intelligent move.
	inline bool move(const char move, int controller){myBoard.move(move, controller);} //Makes a move.
	inline int solvePuzzle(){myBoard.solvePuzzle();} //Makes an attempt to solve the puzzle.
	inline bool issolved()const{myBoard.isSolved();} //Game over control.
	inline bool isSolvable(){myBoard.isSolvable();} //Check the boards solvability.
	inline void playGame(){myBoard.playGame();} //Playing game.
private:
	class Board
	{
	public:
		void print();
		void readFromFile(const string fileName);
		void writeToFile(const string fileName);
		void reset();
		bool setSize(int rowValue, int columnValue);
		bool move(const char move, int controller);
		bool isSolved()const;
		void setFileBoardControl(bool file_board_control_value); //Setting false when reading from file.
		void playGame();
		void printReport(int numberOfMovesValue);
		void moveRandom();
		void shuffle(const int N);
		char moveIntelligent();
		bool moveForIntelligent(int tempArr[][9], char move, int controller);
		bool isSolvable();
		int solvePuzzle();
	private:
		void initializeBoard();
		int calculate_digit_number(int number);
		void create_distance_controller_array(int distance_control_array[][9]);
		int find_total_distance(int distance_control_array[][9]);
		bool number_of_inversion();
		bool find_position_of_empty_cell();
		int board[9][9];
		int row;
		int column;
		bool file_board_control = true;
		bool printFinishControl = true;
	};
	Board myBoard;
};
int NPuzzle :: Board :: solvePuzzle()
{
	int solution_control = 1, i, random_move, escape_stuck = 1, controller = 1, moveNumber = 0;
	char old_one, next_one;

	if(file_board_control == 0){ //Came from file.
		while(solution_control){
			for(i=0; escape_stuck && solution_control == 1; i++){
				next_one = moveIntelligent();
				if(next_one == 'R' && old_one == 'L') //If there is a stuck.
					escape_stuck = 0;
				else if(next_one == 'L' && old_one == 'R')
					escape_stuck = 0;
				else if(next_one == 'U' && old_one == 'D')
					escape_stuck = 0;
				else if(next_one == 'D' && old_one == 'U')
					escape_stuck = 0;

				if(escape_stuck == 1){ //If there is no stuck, it makes intelligent move.
					move(next_one,controller);
					moveNumber++;
					old_one = next_one;
					print();
				}
				if(isSolved()){
					solution_control = 0;
					printFinishControl = false;
				}
			}
			escape_stuck = 1;
			for(i=0; i < 3 && solution_control == 1; i++){ //In the stuck it moves 3 times randomly.
				moveRandom();
				moveNumber++;
				print();
				if(isSolved()){
					solution_control = 0;
					printFinishControl = false;
				}
			}
		}
	}
	else{ //If board came raandomly.
		int solution_control = 1, i, random_move, escape_stuck = 1,is_valid_way =1;
		char old_one, next_one;
		while(solution_control){
			escape_stuck = 1;
			for(i=0; escape_stuck && solution_control == 1; i++){
				next_one = moveIntelligent();
				if(next_one == 'R' && old_one == 'L')
					escape_stuck = 0;
				else if(next_one == 'L' && old_one == 'R')
					escape_stuck = 0;
				else if(next_one == 'U' && old_one == 'D')
					escape_stuck = 0;
				else if(next_one == 'D' && old_one == 'U')
					escape_stuck = 0;

				if(escape_stuck == 1){
					move(next_one,controller);
					moveNumber++;
					old_one = next_one;
					print();
				}
				if(isSolved()){
					solution_control = 0;
					printFinishControl = false;
				}
			}
			i=0;
			while( i < 3 && solution_control == 1){
				moveRandom();
				moveNumber++;
				i++;
				print();
				if(isSolved()){
					solution_control = 0;
					printFinishControl = false;
				}
			}
		}
	}
	return moveNumber;
}
bool NPuzzle :: Board :: moveForIntelligent(int tempArr[][9], char move, int controller)
{
	int i, j, row_num;
	decltype(i) column_num;

	row_num = row;
	column_num = column;

	if(move == 'R'){ //The empty cell is moved in the right direction.
		for(i=0; i < row_num; i++){
			for(j=0; j < column_num && controller == 1; j++){
				if(tempArr[i][j] == -1){	
					if(j != (column_num - 1) && tempArr[i][j+1] != 0){ //If the right side does not exceed the board limit, movement is made.
						int right_temp_number;

						right_temp_number = tempArr[i][j+1];
						tempArr[i][j+1] = -1;
						tempArr[i][j] = right_temp_number;
						controller = 0;

						return true;
					}
				}
			}
		}
	}
	else if(move == 'L'){ //The empty cell is moved in the left direction.
		for(i=0; i < row_num; i++){
			for(j=0; j < column_num; j++){
				if(tempArr[i][j] == -1){
					if(j != 0 && tempArr[i][j-1] != 0){ //If the left side does not exceed the board limit, movement is made.
						int left_temp_number;

						left_temp_number = tempArr[i][j-1];
						tempArr[i][j-1] = -1;
						tempArr[i][j] = left_temp_number;

						return true;
					}
				}
			}
		}
	}
	else if(move == 'U'){ //The empty cell is moved in the up.
		for(i=0; i < row_num; i++){
			for(j=0; j < column_num; j++){
				if(tempArr[i][j] == -1){
					if(i != 0 && tempArr[i-1][j] != 0){ //If the up side does not exceed the board limit, movement is made.
						int up_temp_number;

						up_temp_number = tempArr[i-1][j];
						tempArr[i-1][j] = -1;
						tempArr[i][j] = up_temp_number;

						return true;
					}
				}
			}
		}
	}
	else if(move == 'D'){ //The empty cell is moved in the down.
		for(i=0; i < row_num && controller == 1; i++){
			for(j=0; j < column_num && controller == 1; j++){
				if(tempArr[i][j] == -1){			
					if(i != (row_num - 1) && tempArr[i+1][j] != 0){ //If the down side does not exceed the board limit, movement is made.
						int down_temp_number;

						down_temp_number = tempArr[i+1][j];
						tempArr[i+1][j] = -1;
						tempArr[i][j] = down_temp_number;
						controller = 0;

						return true;
					}
				}
			}
		}
	}
	return false;
}
void NPuzzle :: Board :: shuffle(const int N) //Makes N times random move.
{
	int i;
	for(i = 0; i < N; i++){
		moveRandom();
	}
}
bool NPuzzle :: Board :: isSolvable() //Checking board solvability.
{
	int controller_1, controller_2;

	controller_1 = find_position_of_empty_cell();
	controller_2 = number_of_inversion();

	if(row % 2 == 0){ //If the problem_size is even
		if(controller_1 == 0 && controller_2 == 0) //The empty cell must be in even row and the inversion number must be odd.
			return true;
		if(controller_1 == 1 && controller_2 == 1) //The empty cell must be in odd row and the inversion number must be even.
			return true;
		else
			return false;
	}
	else{ //if the problem_size is odd
		if(controller_2 == 1) //The number of inversion should be even.
			return true;
		else
			return false;
	}
}
bool NPuzzle :: Board :: number_of_inversion() //For check board solvability.
{
	int i, inversion_controller_array[82];
	decltype(i) j; 
	auto k=0, control = 0, inversion = 0;

	for(i=0; i < row; i++){
		for(j=0; j < column; j++){
			inversion_controller_array[k] = board[i][j];
			k++;
		}
	}
	for(i=0; i < row; i++){
		for(j=0; j < column; j++){
			if(board[i][j] != -1){
				for(k=control+1; k < (row * column); k++){
					if(inversion_controller_array[k] != -1 && board[i][j] > inversion_controller_array[k])
						inversion++;
				}
			}
			control++;
		}
	}
	if(inversion % 2 == 0)
		return true;
	else
		return false;
}
bool NPuzzle :: Board :: find_position_of_empty_cell() //For check board solvability.
{

	int i;
	decltype(i) j;

	for(i=0; i < row; i++){
		for(j=0; j < column; j++){
			if(board[i][j] == -1){
				if(i % 2 == 0) //even row
					return false;
				else
					return true;
			}
		}
	}
}
char NPuzzle :: Board :: moveIntelligent() //Makes intelligent move.
{
	int controller = 1, temp_arr[4] ={1, 2 ,3,4}, i, min_total_distance = 0, choose_direction = 0;
	int distance_control_array[9][9], available, large_number = 10000, my_controller_array[9][9];
	char my_direction;

	create_distance_controller_array(distance_control_array);
	available = moveForIntelligent(distance_control_array, 'R', controller);
	if(available)
		temp_arr[0] = find_total_distance(distance_control_array);
	else
		temp_arr[0] = large_number;

	create_distance_controller_array(distance_control_array);
	available = moveForIntelligent(distance_control_array, 'L', controller);
	if(available)
		temp_arr[1] = find_total_distance(distance_control_array);
	else
		temp_arr[1] = large_number;
	
	create_distance_controller_array(distance_control_array);
	available = moveForIntelligent(distance_control_array, 'U', controller);
	if(available)
		temp_arr[2] = find_total_distance(distance_control_array);
	else
		temp_arr[2] = large_number;
	
	create_distance_controller_array(distance_control_array);
	available = moveForIntelligent(distance_control_array, 'D', controller);
	if(available)
		temp_arr[3] = find_total_distance(distance_control_array);
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
int NPuzzle :: Board :: find_total_distance(int distance_control_array[][9])
{
	if(file_board_control == 1){ 
		int i, j;
		decltype(i) division; 
		auto my_number = 1, final_position_i=0, final_position_j=0, total_distance = 0;
		while (my_number <= row * column){ //The distance of all numbers on the map to the required positions is calculated.
			for(i=0; i < row; i++){
				for(j=0; j < column; j++){
					if(distance_control_array[i][j] == my_number){					
						if(my_number % row == 0){
							final_position_j = row - 1; 
							division = my_number / row;
							final_position_i = division - 1;
						}
						else{
							final_position_i = my_number / row;
							final_position_j = (my_number % column) - 1;
						}
						total_distance = total_distance + abs(i - final_position_i) + abs(j - final_position_j);//Distance from numbers to locations

						my_number++;
					}
					//The distance of the empty cell to the position it should be located is calculated.
					else if(distance_control_array[i][j] == -1 && my_number == row * column){
						final_position_i = row - 1; 
						final_position_j = column - 1;

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
		int find_position_i[row*column], find_position_j[row*column], control=1, total_distance = 0;

		for(i=0; i < row; i++){
			for(j=0; j < column; j++){
				if(distance_control_array[i][j] != 0)
					number_of_elements++;
			}
		}
		for(i=0; i < row; i++){
			for(j=0; j < column; j++){
				if(distance_control_array[i][j] != 0){
					find_position_i[k] = i;
					find_position_j[k] = j;
					k++;
				}
			}
		}
		while(my_number <= number_of_elements){
			for(i=0; i < row; i++){
				for(j=0; j < column; j++){
					if(distance_control_array[i][j] == my_number){
						total_distance += abs(i - find_position_i[a]) + abs(j - find_position_j[a]);
						a++;
						my_number++;
					}
					else if(distance_control_array[i][j] == -1 && my_number == number_of_elements){
						total_distance += abs(i - find_position_i[number_of_elements - 1]) + abs(j- find_position_j[number_of_elements - 1]);
						my_number++;
					}
				}
			}
		}
		return total_distance;
	}
}
void NPuzzle :: Board :: create_distance_controller_array(int distance_control_array[][9])
{
	int i, j;
	for(i=0; i < row; i++){
		for(j=0; j < column; j++){
			distance_control_array[i][j] = board[i][j];
		}
	}
}
void NPuzzle :: Board :: moveRandom() //Makes random move.
{
	bool random_moves = true;
	int random;
	do{ 
		bool move_controller;
		random = 1 + rand() % 4;

		if(random == 1){ 
			move_controller = move('R', 1);
			if(move_controller)
				random_moves = false;
		}
		else if(random == 2){ 
			move_controller = move('L', 1);
			if(move_controller)
				random_moves = false;			
		}
		else if(random == 3){ 
			move_controller = move('U', 1);
			if(move_controller)
				random_moves = false;			
		}
		else if(random == 4){ 
			move_controller = move('D', 1);
			if(move_controller)
				random_moves = false;		
		}
	}while(random_moves);
}
void NPuzzle :: Board :: printReport(int numberOfMovesValue)
{
	cout << numberOfMovesValue << " moves have been done." << endl ;
	cout << "Solution is not found." << endl;
	cout << endl;
	print();
}
void NPuzzle :: Board :: reset()
{
	if(file_board_control){ 
		int i=0, j=0, k;

		for(k=1; k <= (row * column); k++){
			if(k == (row * column)){
				board[row-1][column-1] = -1;
			}
			else{
				if(k % (row) == 0){
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
	}
	else{ //Came from file.
		int my_number = 1, i, j;
		for(i=0; i < row; i++){ //Takes final board.
			for(j=0; j < column; j++){
				if(board[i][j] != 0){
					board[i][j] = my_number; 
					my_number++;
				}
				if(i == row - 1 && j == column - 1)
					board[i][j] = -1;
			}
		}
	}
	print();
}
void NPuzzle :: Board :: playGame()
{
	int moveNumber = 0;
	auto control = 1, number_of_moves = 0, controller = 1;
	bool finish = true, print_control = true, is_move, game_over;
	char moveCh;

	//Moves until the game is over and Q is selected. 
	//Move function is called according to the selected direction and movement is performed.
	//As the movement is made, the number of movements is increased.
	while(finish){

		cout << "Your move : ";
		cin >> moveCh;

		if(control == 1){
			if(moveCh != 'R' || moveCh != 'L' || moveCh != 'U' || moveCh != 'D' || moveCh != 'S'|| moveCh != 'I' || moveCh != 'O' || moveCh != 'T' || moveCh != 'E' || moveCh != 'V')
				print_control = false;
			if(moveCh == 'R'){
				if(!file_board_control){
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = false;
					print();
				}
				else{
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = true;
				}
			}
			else if(moveCh == 'L'){
				if(file_board_control == 0){
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = false;
					print();
				}
				else{
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = true;
				}
			}
			else if(moveCh == 'U'){
				if(file_board_control == 0){
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = false;
					print();
				}
				else{
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = true;
				}
			}
			else if(moveCh == 'D'){
				if(file_board_control == 0){
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = false;
					print();
				}
				else{
					is_move = move(moveCh, controller);
					if(is_move)
						number_of_moves++;
					control = 0;
					print_control = true;
				}
			}
			else if(moveCh == 'S'){ //If S motion is selected, final solution is displayed and size * size random movement is done.
				int i;
				reset();
				int N = row*column; 
				shuffle(N);
				print();
				print_control = false;
				control = 0;
				number_of_moves++;
			}
			else if(moveCh == 'I'){ //Choose intelligent move.
				char my_direction = moveIntelligent();
				cout << "Intelligent move chooses " << my_direction << endl;
				move(my_direction, controller);
				control = 0;
				number_of_moves++;
				print_control = true;
			}
			else if(moveCh == 'T'){ //Number of moves printed.
				number_of_moves++;
				printReport(number_of_moves);
			}
			else if(moveCh == 'E'){ //Asks a file name and saves board in the file.
				string save;
				cout << "File name: ";
				cin >> save;
				writeToFile(save);
				number_of_moves++;
				print_control = false;
			}
			else if(moveCh == 'O'){ //Asks a file name and load board from the file.
				string line, load_file;
				cout << "File name: ";
				cin >> load_file;
				readFromFile(load_file);
				control = 0;
				number_of_moves++;
				print_control = false;
			}
			else if(moveCh == 'V'){ //Solves problem using the new intelligent algorithm.
				moveNumber = solvePuzzle();
				number_of_moves = number_of_moves + moveNumber;
				number_of_moves++;
			}
			else if(moveCh == 'Q') //If the user enters Q, the program ends.
				finish = false;
		}
		/*After each move, it is checked whether the game is over or not.
		If the game is finished the board and the necessary information is suppressed. Then the program ends.*/
		game_over = isSolved();
		
		if(game_over == true && file_board_control == true && printFinishControl == true){ 
			print();
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout << "Total number of moves " << number_of_moves << endl;
			print_control = false;
			finish = false;
		}
		else if(game_over == true && file_board_control == false && printFinishControl == true){
			if(print_control){
				print();
			}
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout << "Total number of moves " << number_of_moves << endl;
			print_control = false;
			finish = false;
		}
		if(game_over == true && printFinishControl == false){
			cout << endl;
			cout << "Problem Solved!" << endl;
			cout << "Total number of moves " << number_of_moves << endl;
			finish = false;
		}
		control = 1;
		if(print_control)//The board is printed after each move.
			print();
		print_control = true;
	}
}
void NPuzzle :: Board :: writeToFile (const string fileName)
{
	int i, j;
	ofstream save_file;
	save_file.open(fileName.c_str());

	if(file_board_control){ 
		for(i=0; i < row; i++){
			for(j=0; j < column; j++){
				if(board[i][j] == -1 ){
					save_file << "bb";
					if(j != column - 1)
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
						if(j != (column-1))
							save_file << " ";	
					}
				}
			}
			if(i != row - 1){
				save_file << endl ;
			}
		}
		save_file << endl;
	}
	else{ //Came from file.
		for (i=0; i < row; ++i){
			for (j=0; j < column; ++j){
				if(board[i][j] != -1){
					int digit = calculate_digit_number(board[i][j]);
					if(digit < 2){
						save_file << "0" << board[i][j];
						if(j != column - 1)
							save_file << " ";
					}
					else{
						save_file << board[i][j] ;
						if(j != column - 1)
							save_file << " ";
					}
				}
				else{
					save_file << "bb" ;
					if(j != column - 1)
						save_file << " ";
				}
			}
			save_file << endl;
		}
	}
	print();
	save_file.close();
}
void NPuzzle :: Board :: readFromFile(const string fileName)
{
	int my_line_number = 0, my_total_space = 0;
	ifstream input_file;
	string line, load_file;
	load_file = fileName;
	input_file.open(load_file.c_str());

	while(getline(input_file,line)){ //Read lines from file
		my_line_number++; // Calculate line number.
		for(int i = 0; i < line.size(); ++i){
			if(line.at(i) == ' ')
				my_total_space++; //Calculate all spaces in the file.
		}
	}
	input_file.close();

	row = my_line_number;
	column = (my_total_space / row) + 1;

	input_file.open(load_file.c_str());

	int i, j;
	char temp_ch_array[row][column * 2];

	for(i=0; i < row; i++){ //Read elements from the file.
		for(j=0; j < column * 2; j++){
			input_file >> temp_ch_array[i][j];
		}
	}
	input_file.close();

	for(i=0; i < row; i++){ //Convert string to integer.
		for(j=0; j < column * 2; j=j+2){
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
	setFileBoardControl(false); //file_board_control setting to false.
	print();
}
int NPuzzle :: Board :: calculate_digit_number(int number)
{
	int count = 0;

	while(number > 0){
		number = number / 10;
		count++;
	}
	return count;
}
void NPuzzle :: Board :: setFileBoardControl(bool file_board_control_value)
{
	file_board_control = file_board_control_value;
}
bool NPuzzle :: Board :: isSolved()const //Controlling game over.
{
	int temp_array[82], i, j, size1;
	decltype(size1) size2;
	auto k = 0, game_over = 0,controller = 0;

	size1 = row;
	size2 = column;

	if(file_board_control == true){
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
			return true;
		else
			return false ;
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
			return true;
		else
			return false ;
	}
}
bool NPuzzle:: Board :: move(const char move, int controller)
{
	///File board control false ise dosyadan okudum.
	int i, j, row_num;
	decltype(i) column_num;

	row_num = row;
	column_num = column;

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

						return true;
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

						return true;
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

						return true;
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

						return true;
					}
				}
			}
		}
	}
	return false;
}
void NPuzzle :: Board :: print()
{
	int i;
	decltype(i) j;

	if(file_board_control){
		for(i=0; i < row; i++){
			for(j=0; j < column; j++){
				if(board[i][j] == -1)
					cout << " \t";
				else
					cout << board[i][j] << "\t" ;	
			}
			cout << endl ;
		}
		cout << endl;
	}
	else{
		for (i=0; i < row; ++i) {
			for (j=0; j < column; ++j) {
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
}
bool NPuzzle :: Board :: setSize(int rowValue, int columnValue)
{
	bool returnValue = false;

	if(rowValue >= 3 && rowValue <= 9) //Problem_size should be range of 3 and 9.
	{
		row = rowValue;
		column = columnValue;
		initializeBoard();

		returnValue = true;
	} 
	return returnValue;
}
void NPuzzle :: Board :: initializeBoard()
{
	int distance_control_array[9][9];

	create_distance_controller_array(distance_control_array);

	int i, j, k, controller_array[82];
	decltype(i) random;
	auto l=0,flag = 1,controller = 0;
	for(i=0; i < row; i++){
		for(j=0; j < column; j++){
			flag = 1;
			random = 1 + rand() % ((row * column));
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
					j = (column-1);		
				}
				else
					j--;
			}
		}
	}	
	for(i=0; i < row; i++){
		for(j=0; j < column; j++){
			if(board[i][j] == (row * column))
				board[i][j] = -1;
		}
	}
}
int main(const int argc, const char* argv[])
{
	NPuzzle myPuzzle;
	bool is_finish = true, solvable = true, solvable_controller = true, finish_controller = true;
	int size;
	char move_ch;

	srand(time(NULL));

	if(argv[1] == NULL){
		do{
			cout << "Please enter the problem size" << endl;
			cin >> size;
		}while(!myPuzzle.setsize(size, size));

		while(solvable){ //A new board is created unless the board is resolvable and finished.
			myPuzzle.setsize(size, size);	
			solvable_controller = myPuzzle.isSolvable();	
			finish_controller = myPuzzle.issolved();
			if(solvable_controller == 1 && finish_controller == 0)
				solvable = 0;
		}
		cout << "Your initial random board is" << endl;
		myPuzzle.print();
		myPuzzle.playGame();
	}
	else{
		myPuzzle.readFromFile(argv[1]);
		myPuzzle.playGame();
	}
	return 0;
}
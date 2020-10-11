#include <iostream>

#include "boardarray1d.h"

using std :: cout;
using std :: endl;

namespace NPuzzleGame
{
	BoardArray1D :: BoardArray1D(){}

	bool BoardArray1D :: setSize(int rowValue, int columnValue)
	{
		bool returnValue = true;

		size1 = rowValue;
		size2 = columnValue;

		board1D = new int[size1*size2];		

		initialize1DBoard();

		return returnValue;
	}
	void BoardArray1D :: readFromFile(const string fileName)
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

		size1 = my_line_number;
		size2 = (my_total_space / size1) + 1;

		setSize(size1,size2);

		input_file.open(load_file.c_str());

		int i, j,a=0;
		char temp_ch_array[size1][size2 * 2];

		for(i=0; i < size1; i++){ //Read elements from the file.
			for(j=0; j < size2 * 2; j++){
				input_file >> temp_ch_array[i][j];
			}
		}
		input_file.close();

		for(i=0; i < size1; i++){ //Convert string to integer.
			for(j=0; j < size2 * 2; j=j+2){
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
				board1D[a] = number;
				a++;
			}
		}
		setFileBoardControl(false); //file_board_control setting to false.
		print();
	}
	BoardArray1D :: BoardArray1D(const BoardArray1D& other)
		:size1(other.size1), size2(other.size2)
	{
		board1D = new int[size1*size2];
		for(int i=0; i < size1*size2; i++)
			board1D[i] = other.board1D[i];
	}
	bool BoardArray1D :: operator == (const AbstractBoard& other)
	{
		BoardArray1D* newBoard = (BoardArray1D*)&other;

		for(int i=0; i < (size1 * size2); i++){
			if(board1D[i] != newBoard->board1D[i])
				return false;
		}
		return true;
	}
	bool BoardArray1D :: isSolved()
	{
		int temp_array[size1*size2], i, j, temp_size1;
		decltype(temp_size1) temp_size2;
		auto k = 0, game_over = 0,controller = 0;

		temp_size1 = size1;
		temp_size2 = size2;

		if(getFileBoardControl() == true){
			for(i=0; i < (size1 * size2)-2; i++){
				if(board1D[i] < board1D[i+1])
					game_over++;
			}
			if(game_over == ((size1 * size2) - 2) && board1D[(size1 * size2) - 1] == -1)
				return true;
			else
				return false ;
		}
		else{
			k=0;
			game_over = 0;
			for(i=0; i < (size1 * size2); i++){
				if(board1D[i] != 0){
					temp_array[k] = board1D[i];
					k++;
					controller++;
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
	int BoardArray1D :: operator () (int index_i, int index_j)
	{
	}
	bool BoardArray1D :: move(const char move, int controller)
	{
		///File board control false ise dosyadan okudum.
		int i, row_num;
		decltype(i) column_num;

		row_num = size1;
		column_num = size2;

		if(move == 'R'){ //The empty cell is moved in the right direction.
			for(i=0; i < row_num * column_num && controller == 1; i++){
				if(board1D[i] == -1){	
					if((!((i + 1) % column_num == 0)) && board1D[i+1] != 0){ //If the right side does not exceed the board limit, movement is made.
						int right_temp_number;

						right_temp_number = board1D[i+1];
						board1D[i+1] = -1;
						board1D[i] = right_temp_number;
						controller = 0;

						return true;
					}
				}	
			}
		}
		else if(move == 'L'){ //The empty cell is moved in the left direction.
			for(i=0; i < row_num * column_num; i++){
				if(board1D[i] == -1){
					if(((i % column_num) != 0) && board1D[i-1] != 0){ //If the left side does not exceed the board limit, movement is made.
						int left_temp_number;

						left_temp_number = board1D[i-1];
						board1D[i-1] = -1;
						board1D[i] = left_temp_number;

						return true;
					}
				}
			}
		}
		else if(move == 'U'){ //The empty cell is moved in the up.
			for(i=0; i < row_num * column_num; i++){
				if(board1D[i] == -1){
					if((i > size1) && board1D[i-size2] != 0){ //If the up side does not exceed the board limit, movement is made.
						int up_temp_number;

						up_temp_number = board1D[i-size2];
						board1D[i-size2] = -1;
						board1D[i] = up_temp_number;

						return true;
					}
				}
			}
		}
		else if(move == 'D'){ //The empty cell is moved in the down.
			for(i=0; i < row_num * column_num && controller == 1; i++){
				if(board1D[i] == -1){			
					if(i < (size2 * (size1-1)) && board1D[i + size2] != 0){ //If the down side does not exceed the board limit, movement is made.
						int down_temp_number;

						down_temp_number = board1D[i + size2];
						board1D[i + size2] = -1;
						board1D[i] = down_temp_number;
						controller = 0;

						return true;
					}
				}
			}
		}
		return false;
	}
	void BoardArray1D :: writeToFile(const string fileName)
	{
		int i, j;
		ofstream save_file;
		save_file.open(fileName.c_str());

		if(getFileBoardControl()){ 
			for(i=0; i < (size1 * size2); i++){
				if(board1D[i] == -1){
					save_file << "bb";
					if(i != (size1 * size2)- 1)
						save_file << " ";
				}
				else{
					if(board1D[i] != -1){
						if(board1D[i] <= 9){
							save_file << "0" << board1D[i];
						}
						else{
							save_file << board1D[i];
						}
						if(i != (size1 * size2) - 1){
							save_file << " ";
						}
					}
				}
				if(((i % size1) + 1) % size1 == 0)
					save_file << endl;
			}
		}
		else{
			for(i=0; i < (size1 * size2); i++){
				if(board1D[i] != -1){
					int digit = calculate_digit_number(board1D[i]);
					if(digit < 2){
						save_file << "0" << board1D[i];
						if(i != (size1 * size2) - 1)
							save_file << " ";

					}
					else{
						save_file << board1D[i];
						if(i != (size1 * size2) - 1)
							save_file << " ";
					}
				}
				else{
					save_file << "bb";
					if(i != (size1 * size2) - 1)
						save_file << " ";
				}
				if(((i % size1) + 1) % size1 == 0)
					save_file << endl;
			}
		}
		print();
		save_file.close();
	}
	void BoardArray1D :: reset()
	{
		if(getFileBoardControl()){ 
			for(int i = 0; i < (size1 * size2); i++)
			{
				if(i == (size1 * size2) - 1 )
				{
					board1D[(size1* size2) - 1] = -1;
				}
				else
				{
					board1D[i] = i + 1;
				}
			}
		}
		else{ //Came from file.
			int my_number = 1;
			for(int i=0; i < (size1 * size2); i++){
				if(board1D[i] != 0){
					board1D[i] = my_number;
					my_number++;
				}
				if(i == (size1 * size2) - 1)
					board1D[i] = -1;
			}
		}
		print();
	}
	void BoardArray1D :: print() ////DOSYA İÇİN BAK
	{
		int i;
		if(getFileBoardControl()){
			for(i=0; i < size1*size2; i++){
				if( !(((i % size1) + 1) % size1 == 0)){
					if(board1D[i] == -1)
						cout << " \t";
					else
						cout << board1D[i] << "\t";
				}
				else{
					if(board1D[i] == -1)
						cout << " \t" << endl;
					else
						cout << board1D[i] << endl;
				}
			}
		}
		else{
			for (i=0; i < size1 * size2; ++i) {
				if(board1D[i] != -1){
					int digit = calculate_digit_number(board1D[i]);
					if(digit < 2)
						cout << "0" << board1D[i] << " ";
					else
						cout << board1D[i] << " ";
				}
				else 
					cout << "bb" << " ";	
				if( ((i % size1) + 1) % size1 == 0)
					cout << endl;
			}
		}
		cout << endl;
	}
	void BoardArray1D :: initialize1DBoard()
	{
		int i,j, random, controller_array[size1*size2], controller=0,flag = 1,l=0;

		for(i=0; i < size1*size2; i++){
			flag = 1;
			random = 1 + rand() % ((size1 * size2));
			for(j=0; j < controller; j++){
				if(random == controller_array[j]){
					flag=0;
				}
			}
			if(flag == 1){
				controller_array[l] = random;
				board1D[i] = random;
				controller++;
				l++;
			}
			else if(flag == 0){
				i--;
			}
		}
		for(i=0; i < size1*size2; i++){
			if(board1D[i] == (size1*size2)){
				board1D[i] = -1;
			}
		}

	}
	
	BoardArray1D& BoardArray1D :: operator = (const BoardArray1D& other)
	{
		size1 = other.size1;
		size2 = other.size2;

		delete [] board1D;

		board1D = new int[size1*size2];

		for(int i=0; i < size1*size2; i++)
			board1D[i] = other.board1D[i];

		return *this;
	}
	BoardArray1D :: ~BoardArray1D ( )
	{
		delete [] board1D;
	}
}
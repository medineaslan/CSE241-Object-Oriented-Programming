#include <iostream>

#include "boardvector.h"

using std :: cout;
using std :: endl;

namespace NPuzzleGame
{
	BoardVector :: BoardVector(int rowValue, int columnValue)
	{
		int i, j;

		board.resize(rowValue);

		for(i=0; i < rowValue; i++){
			for(j=0; j < columnValue; j++){
				board[i].push_back(0);
			}
		}
	}
	bool BoardVector :: operator == (const AbstractBoard& other)
	{
		BoardVector* newBoard = (BoardVector*)&other;

		for(int i=0; i < board.size(); i++){
			for(int j=0; j < board[0].size(); j++){
				if(board[i][j] != newBoard->board[i][j])
					return false;
			}
		}
		return true;
	}
	int BoardVector :: operator () (int index_i, int index_j)
	{
		return board[index_i][index_j];
	}
	void BoardVector ::  writeToFile(const string fileName)
	{
		int i, j;
		ofstream save_file;
		save_file.open(fileName.c_str());

		if(getFileBoardControl()){ 
			for(i=0; i < board.size(); i++){
				for(j=0; j < board[0].size(); j++){
					if(board[i][j] == -1 ){
						save_file << "bb";
						if(j != board[0].size() - 1)
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
							if(j != (board[0].size()-1))
								save_file << " ";   
						}
					}
				}
				if(i != board.size() - 1){
					save_file << endl ;
				}
			}
			save_file << endl;
		}
	    else{ //Came from file.
	    	for (i=0; i < board.size(); ++i){
	    		for (j=0; j < board[0].size(); ++j){
	    			if(board[i][j] != -1){
	    				int digit = calculate_digit_number(board[i][j]);
	    				if(digit < 2){
	    					save_file << "0" << board[i][j];
	    					if(j != board[0].size() - 1)
	    						save_file << " ";
	    				}
	    				else{
	    					save_file << board[i][j] ;
	    					if(j != board[0].size() - 1)
	    						save_file << " ";
	    				}
	    			}
	    			else{
	    				save_file << "bb" ;
	    				if(j != board[0].size() - 1)
	    					save_file << " ";
	    			}
	    		}
	    		save_file << endl;
	    	}
	    }
	    print();
	    save_file.close();
	}
	void BoardVector :: readFromFile(const string fileName)
	{
		int my_line_number = 0, my_total_space = 0,row,column;
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

	    int i;
	    board.resize(row);
	    for(i=0; i<row; ++i){
	    	board[i].resize(column);
	    }
	    input_file.open(load_file.c_str());

	    int j;
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
	    setFileBoardControl(false); //getFileBoardControl() setting to false.
	    print();
	}
	bool BoardVector :: isSolved()
	{
		int temp_array[1000], i, j;
		auto k = 0, game_over = 0,controller = 0;

		if(getFileBoardControl() == true){
			for(i=0; i < board.size(); i++){
				for(j=0; j < board[0].size(); j++){
					temp_array[k] = board[i][j];
					k++;
				}
			}
			for(i=0; i < (board.size() * board[0].size()) - 2; i++){
				if(temp_array[i] < temp_array[i+1])
					game_over++;
			}
			if(game_over == ((board.size() * board[0].size()) - 2) && temp_array[(board.size() * board[0].size()) - 1] == -1)
				return true;
			else
				return false ;
		}
		else{
			k=0;
			game_over = 0;
			for(i=0; i < board.size(); i++){
				for(j=0; j < board[0].size(); j++){
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
	void BoardVector :: reset()
	{
		if(getFileBoardControl()){ 
			int i=0, j=0, k;

			for(k=1; k <= (board.size() * board[0].size()); k++){
				if(k == (board.size() * board[0].size())){
					board[board.size()-1][board[0].size()-1] = -1;
				}
				else{
					if(k % (board.size()) == 0){
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
	        for(i=0; i < board.size(); i++){ //Takes final board.
	        	for(j=0; j < board[0].size(); j++){
	        		if(board[i][j] != 0){
	        			board[i][j] = my_number; 
	        			my_number++;
	        		}
	        		if(i == board.size() - 1 && j == board[0].size() - 1)
	        			board[i][j] = -1;
	        	}
	        }
	    }
	    print();
	}
	bool BoardVector :: move(const char move, int controller)
	{
		int i, j;

	    if(move == 'R'){ //The empty cell is moved in the right direction.
	    	for(i=0; i < board.size(); i++){
	    		for(j=0; j < board[0].size() && controller == 1; j++){
	    			if(board[i][j] == -1){  
	                    if(j != (board[0].size() - 1) && board[i][j+1] != 0){ //If the right side does not exceed the board limit, movement is made.
	                    	int right_temp_number;

	                    	right_temp_number = board[i][j+1];
	                    	board[i][j+1] = -1;
	                    	board[i][j] = right_temp_number;
	                    	controller = 0;
	                    	lastMove('R');
	                    	return true;
	                    }
	                }
	            }
	        }
	    }
	    else if(move == 'L'){ //The empty cell is moved in the left direction.
	    	for(i=0; i < board.size(); i++){
	    		for(j=0; j < board[0].size(); j++){
	    			if(board[i][j] == -1){
	                    if(j != 0 && board[i][j-1] != 0){ //If the left side does not exceed the board limit, movement is made.
	                    	int left_temp_number;

	                    	left_temp_number = board[i][j-1];
	                    	board[i][j-1] = -1;
	                    	board[i][j] = left_temp_number;
	                    	lastMove('L');
	                    	return true;
	                    }
	                }
	            }
	        }
	    }
	    else if(move == 'U'){ //The empty cell is moved in the up.
	    	for(i=0; i < board.size(); i++){
	    		for(j=0; j < board[0].size(); j++){
	    			if(board[i][j] == -1){
	                    if(i != 0 && board[i-1][j] != 0){ //If the up side does not exceed the board limit, movement is made.
	                    	int up_temp_number;

	                    	up_temp_number = board[i-1][j];
	                    	board[i-1][j] = -1;
	                    	board[i][j] = up_temp_number;
	                    	lastMove('U');
	                    	return true;
	                    }
	                }
	            }
	        }
	    }
	    else if(move == 'D'){ //The empty cell is moved in the down.
	    	for(i=0; i < board.size() && controller == 1; i++){
	    		for(j=0; j < board[0].size() && controller == 1; j++){
	    			if(board[i][j] == -1){          
	                    if(i != (board.size() - 1) && board[i+1][j] != 0){ //If the down side does not exceed the board limit, movement is made.
	                    	int down_temp_number;

	                    	down_temp_number = board[i+1][j];
	                    	board[i+1][j] = -1;
	                    	board[i][j] = down_temp_number;
	                    	controller = 0;
	                    	lastMove('D');
	                    	return true;
	                    }
	                }
	            }
	        }
	    }
	    return false;
	}
	void BoardVector :: initializeBoard (int rowValue, int columnValue)
	{
		int i, j, k, controller_array[1000];
		decltype(i) random;
		auto l=0,flag = 1,controller = 0;
		for(i=0; i < rowValue; i++){
			for(j=0; j < columnValue; j++){
				flag = 1;
				random = 1 + rand() % ((rowValue * columnValue));
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
						j = (columnValue-1);     
					}
					else
						j--;
				}
			}
		}   
		for(i=0; i < rowValue; i++){
			for(j=0; j < columnValue; j++){
				if(board[i][j] == (rowValue * columnValue))
					board[i][j] = -1;
			}
		}
	}
	bool BoardVector :: setSize(int rowValue, int columnValue)
	{
		bool returnValue = false;
	   
    	initializeBoard(rowValue, columnValue);

    	returnValue = true;
    	
	    return returnValue;
	}
	void BoardVector :: print()
	{
		int i;
		decltype(i) j;
		if(getFileBoardControl()){
			for(i=0; i < board.size(); i++){
				for(j=0; j < board[i].size(); j++){
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
			for (i=0; i < board.size(); ++i) {
				for (j=0; j < board[i].size(); ++j) {
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
	
}
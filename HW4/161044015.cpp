#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

class NPuzzle
{
public:
	inline void print()const{myBoard.back().print();} //Prints the current configuration on the screen by sending it to cout.
    void printReport(int numberOfMovesValue); //Prints a report about how many moves have been done.
	inline void readFromFile(const string fileName){myBoard.back().readFromFile(fileName);} //Reading from file.
	inline void writeToFile(const string fileName){myBoard.back().writeToFile(fileName);} //Writing to file.
	void shuffle(const int N); //Makes N random move.
	inline void reset(){myBoard.back().reset();} //Reset the board.
	inline bool setsize(int rowValue, int columnValue){myBoard.back().setSize(rowValue, columnValue);} //Set the board size given values.
	void moveRandom(); //Makes random move.
	inline bool move(const char move, int controller){myBoard.back().move(move, controller);} //Makes a move.
	int solvePuzzle();//Makes an attempt to solve the puzzle.
	inline bool isSolvable(){myBoard.back().isSolvable();} //Check the boards solvability.
	void playGame();//Playing game.
    void create(int rowValue, int columnValue);
    friend istream& operator>>(istream& myIstream, NPuzzle& myNpuzzle);
    friend ostream& operator<<(ostream& myOstream, const NPuzzle& myNpuzzle);
    bool get_file_board_control(){myBoard.back().get_file_board_control();}
    bool get_print_finish_control(){myBoard.back().get_print_finish_control();}
    bool get_isMove(){myBoard.back().get_isMove();}
    vector<vector<int>> get_board(){myBoard.back().get_board();}
    char getlastmove(){myBoard.back().getlastmove();}
    int getMyNumberOfMoves(){myBoard.back().getMyNumberOfMoves();}

private:
	class Board
	{
	public:
        Board(int rowValue, int columnValue);
        void print()const;
        char getlastmove();
        void readFromFile(const string fileName);
        void writeToFile(const string fileName);
        void reset();
        bool setSize(int rowValue, int columnValue);
        bool move(const char move, int controller);
        Board& moveForSolvePuzzle(Board& tempBoard, char move, int controller);
        bool isSolved()const;
		void setFileBoardControl(bool file_board_control_value); //Setting false when reading from file.
		bool isSolvable();
        bool get_file_board_control();
        bool get_print_finish_control();
        bool get_isMove();
        int getMyNumberOfMoves();
        vector<vector<int>> get_board();
        int operator () (int index_i, int index_j);
        bool operator == (const Board& other);
        bool operator = (const Board& other);
        static int NumberOfBoards(); 
        static char lastMove(char myMove);
        static int numberOfMoves(int solveControl);
        friend istream& operator>>(istream& myIstream, Board& b)
        {

            int my_line_number = 0, my_total_space = 0,row,column;
            istream &input_file = myIstream;

            string line, load_file;

            while(getline(input_file,line)){ //Read lines from file
                my_line_number++; // Calculate line number.
                for(int i = 0; i < line.size(); ++i){
                    if(line.at(i) == ' ')
                        my_total_space++; //Calculate all spaces in the file.
                }
            }
            row = my_line_number;
            column = (my_total_space / row) + 1;

            int i;
            b.board.resize(row);
            for(i=0; i<row; ++i){
                b.board[i].resize(column);
            }

            input_file.clear();
            input_file.seekg(0, ios::beg);

            int j;
            char temp_ch_array[row][column * 2];

            for(i=0; i < row; i++){ //Read elements from the file.
                for(j=0; j < column * 2; j++){
                    input_file >> temp_ch_array[i][j];
                }
            }
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
                    b.board[i][j/2] = number;
                }
            }
            b.setFileBoardControl(false); //file_board_control setting to false.
            b.print();
        }
        friend ostream& operator<<(ostream& myOstream, const Board& b)
        {
            int i;
            decltype(i) j;
            if(b.file_board_control){
                for(i=0; i < b.board.size(); i++){
                    for(j=0; j < b.board[i].size(); j++){
                        if(b.board[i][j] == -1)
                            myOstream << " \t";
                        else
                            myOstream << b.board[i][j] << "\t" ;   
                    }
                    myOstream << endl ;
                }
                myOstream << endl;
            }
            else{
                for (i=0; i < b.board.size(); ++i) {
                    for (j=0; j < b.board[i].size(); ++j) {
                        if(b.board[i][j] != -1){
                            int digit = b.calculate_digit_number(b.board[i][j]);
                            if(digit < 2)
                                myOstream << "0" << b.board[i][j] << " ";
                            else
                                myOstream << b.board[i][j] << " ";
                        }
                        else
                            myOstream << "bb" << " ";    
                    }
                    myOstream << endl;
                }
                myOstream << endl;
            }
            return myOstream;
        }
    private:
      void initializeBoard(int rowValue, int columnValue);
      int calculate_digit_number(int number)const;
      bool number_of_inversion();
      bool find_position_of_empty_cell();
      bool file_board_control = true;
      bool printFinishControl = true;
      bool isMove = false;
      vector<vector<int>> board;
      static char myLastMove; 
      static int myNumberOfMoves; 
      static int numberOfBoards;
  };
  vector <Board> myBoard; 
public:
    vector<Board> get_myBoard(){return myBoard;}
    Board& moveForSolvePuzzle(Board& tempBoard, char move, int controller){myBoard.back().moveForSolvePuzzle(tempBoard, move, controller);}
    bool isSame(Board other);
};

char NPuzzle :: Board :: myLastMove = 'S';
int NPuzzle :: Board :: myNumberOfMoves = 0;
int NPuzzle :: Board :: numberOfBoards = 0;

int NPuzzle :: Board :: getMyNumberOfMoves()
{
    return myNumberOfMoves;
}
char NPuzzle :: Board :: getlastmove()
{
    return myLastMove;
} 
bool NPuzzle :: Board :: get_isMove()
{
    return isMove;
}
NPuzzle :: Board& NPuzzle :: Board :: moveForSolvePuzzle(Board& tempBoard, char move, int controller)
{
    ///File board control false ise dosyadan okudum.
    int i, j;

    if(move == 'R'){ //The empty cell is moved in the right direction.
        for(i=0; i < tempBoard.board.size(); i++){
            for(j=0; j < tempBoard.board[0].size() && controller == 1; j++){
                if(tempBoard.board[i][j] == -1){  
                    if(j != (tempBoard.board[0].size() - 1) && tempBoard.board[i][j+1] != 0){ //If the right side does not exceed the board limit, movement is made.
                        int right_temp_number;

                        right_temp_number = tempBoard.board[i][j+1];
                        tempBoard.board[i][j+1] = -1;
                        tempBoard.board[i][j] = right_temp_number;
                        controller = 0;
                        lastMove('R');
                        isMove = true;
                    }
                    else
                        isMove = false;
                }
            }
        }
    }
    else if(move == 'L'){ //The empty cell is moved in the left direction.
        for(i=0; i < tempBoard.board.size(); i++){
            for(j=0; j < tempBoard.board[0].size(); j++){
                if(tempBoard.board[i][j] == -1){
                    if(j != 0 && tempBoard.board[i][j-1] != 0){ //If the left side does not exceed the board limit, movement is made.
                        int left_temp_number;

                        left_temp_number = tempBoard.board[i][j-1];
                        tempBoard.board[i][j-1] = -1;
                        tempBoard.board[i][j] = left_temp_number;
                        lastMove('L');
                        isMove = true;
                    }
                    else
                        isMove = false;
                }
            }
        }
    }
    else if(move == 'U'){ //The empty cell is moved in the up.
        for(i=0; i < tempBoard.board.size(); i++){
            for(j=0; j < tempBoard.board[0].size(); j++){
                if(tempBoard.board[i][j] == -1){
                    if(i != 0 && tempBoard.board[i-1][j] != 0){ //If the up side does not exceed the board limit, movement is made.
                        int up_temp_number;

                        up_temp_number = tempBoard.board[i-1][j];
                        tempBoard.board[i-1][j] = -1;
                        tempBoard.board[i][j] = up_temp_number;
                        lastMove('U');
                        isMove = true;
                    }
                    else
                        isMove = false;
                }
            }
        }
    }
    else if(move == 'D'){ //The empty cell is moved in the down.
        for(i=0; i < tempBoard.board.size() && controller == 1; i++){
            for(j=0; j < tempBoard.board[0].size() && controller == 1; j++){
                if(tempBoard.board[i][j] == -1){          
                    if(i != (tempBoard.board.size() - 1) && tempBoard.board[i+1][j] != 0){ //If the down side does not exceed the board limit, movement is made.
                        int down_temp_number;

                        down_temp_number = tempBoard.board[i+1][j];
                        tempBoard.board[i+1][j] = -1;
                        tempBoard.board[i][j] = down_temp_number;
                        controller = 0;
                        lastMove('D');
                        isMove = true;
                    }
                    else
                        isMove = false;
                }
            }
        }
    }
    return tempBoard;
}

int NPuzzle :: Board :: NumberOfBoards()
{
    numberOfBoards++;
    return numberOfBoards;
}

char NPuzzle :: Board :: lastMove(char myMove)
{
    myLastMove = myMove;

    return myLastMove;
}

int NPuzzle :: Board :: numberOfMoves(int solveControl)
{
    if(solveControl == 1){
        myNumberOfMoves++;
    }
    else if(solveControl == -1){
       return myNumberOfMoves;
   }
   else{
    myNumberOfMoves = 0;
}
return myNumberOfMoves;
}
bool NPuzzle :: Board :: get_file_board_control()
{
    return file_board_control;
}
bool NPuzzle :: Board :: get_print_finish_control()
{
    return printFinishControl;
}
vector<vector<int>> NPuzzle :: Board :: get_board()
{
    return board;
}
bool NPuzzle :: isSame(Board other)
{
    int i;

    for(i=0; i < myBoard.size(); i++){
        if(other == myBoard[i]){
            return false;
        }
    }
    return true;
}
int NPuzzle :: solvePuzzle()
{
    myBoard.back().print();

    int i=0, l=1;
    while(1)
    {
        auto temp = myBoard[i];

        auto isBoard = moveForSolvePuzzle(temp, 'R', 1);
        if(get_isMove()){
            if(isSame(isBoard)){
                Board :: numberOfMoves(1);
                myBoard.push_back(isBoard);

                myBoard.back().print();

                if(myBoard.back().isSolved() == true){
                    cout << "Problem Solved!" << endl;
                    cout << "Total number of moves " << myBoard.back().getMyNumberOfMoves() << endl;
                    exit(1);
                }
            }
        }
        temp = myBoard[i];

        isBoard = moveForSolvePuzzle(temp, 'L', 1);
        if(get_isMove()){
            if(isSame(isBoard)){
                Board :: numberOfMoves(1);
                myBoard.push_back(temp);

                myBoard.back().print();

                if(myBoard.back().isSolved() == true){
                    cout << "Problem Solved!" << endl;
                    cout << "Total number of moves " << myBoard.back().getMyNumberOfMoves()  << endl;
                    exit(1);
                }
            }
        }
        temp = myBoard[i];

        isBoard = moveForSolvePuzzle(temp, 'U', 1);
        if(get_isMove()){
            if(isSame(isBoard)){
                Board :: numberOfMoves(1);
                myBoard.push_back(temp);

                myBoard.back().print();

                if(myBoard.back().isSolved() == true){
                    cout << "Problem Solved!" << endl;
                    cout << "Total number of moves " << myBoard.back().getMyNumberOfMoves()  << endl;
                    exit(1);
                }
            }
        }
        temp = myBoard[i];

        isBoard = moveForSolvePuzzle(temp, 'D', 1);
        if(get_isMove()){
            if(isSame(isBoard)){
                Board :: numberOfMoves(1);
                myBoard.push_back(temp);

                myBoard.back().print();

                if(myBoard.back().isSolved() == true){
                    cout << "Problem Solved!" << endl;
                    cout << "Total number of moves " << myBoard.back().getMyNumberOfMoves()  << endl;
                    exit(1);
                }
            }
        }
        i++;
    }
}
ostream& operator<<(ostream& myOstream, const NPuzzle& myNpuzzle)
{
    myOstream << myNpuzzle.myBoard.back();
    return myOstream;
}

istream& operator>>(istream& myIstream, NPuzzle& myNpuzzle)
{
    myIstream >> myNpuzzle.myBoard.back();
    return myIstream;
}
int NPuzzle :: Board :: operator () (int index_i, int index_j)
{
    return board[index_i][index_j];
}
bool NPuzzle :: Board :: operator =(const Board & other)
{
    for(int i=0; i < other.board.size(); i++){
        for(int j=0; j < other.board[0].size(); j++){
            board[i][j] = other.board[i][j];
        }
    }
    file_board_control = other.file_board_control;
    printFinishControl = other.printFinishControl;
    myLastMove = other.myLastMove;
    myNumberOfMoves = other.myNumberOfMoves;
}
bool NPuzzle :: Board :: operator ==(const Board & other)
{
    for(int i=0; i < board.size(); i++){
        for(int j=0; j < board[0].size(); j++){
            if(board[i][j] != other.board[i][j])
                return false;
        }
    }
    return true;
}

void NPuzzle :: moveRandom() //Makes random move.
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

void NPuzzle :: shuffle(const int N) //Makes N times random move.
{
    int i;
    for(i = 0; i < N; i++){
        moveRandom();
    }
}
void NPuzzle :: Board :: reset()
{
    if(file_board_control){ 
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
    get_board().resize(0);

}
void NPuzzle :: printReport(int numberOfMovesValue)
{
    cout << numberOfMovesValue << " moves have been done." << endl ;
    cout << "Solution is not found." << endl;
    cout << endl;
    print();
}

void NPuzzle :: playGame()
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
            if(moveCh != 'R' || moveCh != 'L' || moveCh != 'U' || moveCh != 'D' || moveCh != 'S' || moveCh != 'O' || moveCh != 'T' || moveCh != 'E' || moveCh != 'V')
                print_control = false;
            if(moveCh == 'R'){
                if(!get_file_board_control()){
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = false;
                    cout << myBoard.back(); ////Operator overloading "<<"
                }
                else{
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = true;
                }
            }
            else if(moveCh == 'L'){
                if(get_file_board_control() == false){
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = false;
                    print();
                }
                else{
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = true;
                }
            }
            else if(moveCh == 'U'){
                if(get_file_board_control() == false){
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = false;
                    print();
                }
                else{
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = true;
                }
            }
            else if(moveCh == 'D'){
                if(get_file_board_control() == false){
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = false;
                    print();
                }
                else{
                    is_move = move(moveCh, controller);
                    if(is_move)
                        Board :: numberOfMoves(1);
                    control = 0;
                    print_control = true;
                }
            }
            else if(moveCh == 'S'){ //If S motion is selected, final solution is displayed and size * size random movement is done.
                int i;
                reset();
                int row = get_myBoard().back().get_board().size();
                int column = get_myBoard().back().get_board()[0].size(); 
                int N = row * column;
                shuffle(N);
                print();
                print_control = false;
                control = 0;
                Board :: numberOfMoves(1);
            }
            else if(moveCh == 'T'){ //Number of moves printed.
                Board :: numberOfMoves(1);
                printReport( Board :: numberOfMoves(-1));
            }
            else if(moveCh == 'E'){ //Asks a file name and saves board in the file.
                string save;
                cout << "File name: ";
                cin >> save;
                writeToFile(save);
                Board :: numberOfMoves(1);
                print_control = false;
            }
            else if(moveCh == 'O'){ //Asks a file name and load board from the file.
                string line, load_file;
                cout << "File name: ";
                cin >> load_file;
                readFromFile(load_file);
                control = 0;
                Board :: numberOfMoves(1);
                print_control = false;
            }
            else if(moveCh == 'V'){ //Solves problem using the new intelligent algorithm.
                Board :: lastMove('S');
                solvePuzzle();
                Board :: numberOfMoves(2);
            }
            else if(moveCh == 'Q') //If the user enters Q, the program ends.
                finish = false;
        }
        /*After each move, it is checked whether the game is over or not.
        If the game is finished the board and the necessary information is suppressed. Then the program ends.*/
        game_over = get_myBoard().back().isSolved();
        
        if(game_over == true && get_file_board_control() == true && get_print_finish_control() == true){ 
            print();
            cout << endl;
            cout << "Problem Solved!" << endl;
            cout << "Total number of moves " << Board :: numberOfMoves(-1) << endl;
            print_control = false;
            finish = false;
        }
        else if(game_over == true && get_file_board_control() == false && get_print_finish_control() == true){
            if(print_control){
                print();
            }
            cout << endl;
            cout << "Problem Solved!" << endl;
            cout << "Total number of moves " << Board :: numberOfMoves(-1) << endl;
            print_control = false;
            finish = false;
        }
        if(game_over == true && get_print_finish_control() == false){
            cout << endl;
            cout << "Problem Solved!" << endl;
            cout << "Total number of moves " << Board :: numberOfMoves(-1) << endl;
            finish = false;
        }
        control = 1;
        if(print_control)//The board is printed after each move.
            print();
        print_control = true;
    }
}
bool NPuzzle :: Board :: isSolvable() //Checking board solvability.
{
    int controller_1, controller_2;

    controller_1 = find_position_of_empty_cell();
    controller_2 = number_of_inversion();

    if(board.size() % 2 == 0){ //If the problem_size is even
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

    for(i=0; i < board.size(); i++){
        for(j=0; j < board[0].size(); j++){
            inversion_controller_array[k] = board[i][j];
            k++;
        }
    }
    for(i=0; i < board.size(); i++){
        for(j=0; j < board[0].size(); j++){
            if(board[i][j] != -1){
                for(k=control+1; k < (board.size() * board[0].size()); k++){
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

    for(i=0; i < board.size(); i++){
        for(j=0; j < board[0].size(); j++){
            if(board[i][j] == -1){
                if(i % 2 == 0) //even row
                    return false;
                else
                    return true;
            }
        }
    }
}

void NPuzzle :: Board :: writeToFile (const string fileName)
{
    int i, j;
    ofstream save_file;
    save_file.open(fileName.c_str());

    if(file_board_control){ 
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

void NPuzzle :: Board :: readFromFile(const string fileName)
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
    setFileBoardControl(false); //file_board_control setting to false.
    print();
}
void NPuzzle :: Board :: setFileBoardControl(bool file_board_control_value)
{
    file_board_control = file_board_control_value;
}
bool NPuzzle :: Board :: isSolved()const //Controlling game over.
{
    int temp_array[82], i, j;
    auto k = 0, game_over = 0,controller = 0;

    if(file_board_control == true){
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
bool NPuzzle:: Board :: move(const char move, int controller)
{
    ///File board control false ise dosyadan okudum.
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

int NPuzzle :: Board :: calculate_digit_number(int number)const
{
    int count = 0;

    while(number > 0){
        number = number / 10;
        count++;
    }
    return count;
}

void NPuzzle :: Board :: print()const
{
    int i;
    decltype(i) j;
    if(file_board_control){
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

void NPuzzle :: Board :: initializeBoard(int rowValue, int columnValue)
{
    int i, j, k, controller_array[82];
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

bool NPuzzle :: Board :: setSize(int rowValue, int columnValue)
{
    bool returnValue = false;

    if(rowValue >= 3 && rowValue <= 9) //Problem_size should be range of 3 and 9.
    {
        initializeBoard(rowValue, columnValue);

        returnValue = true;
    } 
    return returnValue;
}

void NPuzzle :: create(int rowValue, int columnValue)
{
    Board myB(rowValue, columnValue);
    myBoard.push_back(myB);
}

NPuzzle :: Board :: Board(int rowValue, int columnValue)
{
    int i, j;

    board.resize(rowValue);

    for(i=0; i < rowValue; i++){
        for(j=0; j < columnValue; j++){
            board[i].push_back(0);
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
            myPuzzle.create(size, size);
        }while(!myPuzzle.setsize(size, size));

        while(solvable){ //A new board is created unless the board is resolvable and finished.
            myPuzzle.setsize(size, size);   
            solvable_controller = myPuzzle.isSolvable();    
            finish_controller = myPuzzle.get_myBoard().back().isSolved();
            if(solvable_controller == 1 && finish_controller == 0)
                solvable = 0;
        }
        cout << "Your initial random board is" << endl;
        myPuzzle.print();
        myPuzzle.playGame();
    }
    else{
        myPuzzle.create(9, 9);
        ifstream input_file;
        string load_file = argv[1];
        input_file.open(load_file.c_str());
        input_file >> myPuzzle; ///Operator overloading ">>"
        input_file.close();
        myPuzzle.playGame();
    }
    return 0;
}


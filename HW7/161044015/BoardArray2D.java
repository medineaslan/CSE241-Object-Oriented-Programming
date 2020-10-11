import java.io.*;
import java.io.FileWriter;
import java.io.IOException;

/**
 * BoardArray2D class with some methods
 * @author Medine ASLAN
 */
public class BoardArray2D extends AbstractBoard{

    private int[][] board2D;
    private int row;
    private int column;

    /**
     * Find empty cell's index j for global function.
     * @return index j.
     */
    public int findEmptyCellIndexJ()
    {
        for(int i=0; i < row; i++)
        {
            for(int j=0; j < column; j++){
                if(this.board2D[i][j] == -1)
                    return j;
            }
        }
        return 0;
    }
    /**
     * Find empty cell's index i for global function.
     * @return index i.
     */
    public int findEmptyCellIndexI()
    {
        for(int i=0; i < row; i++)
        {
            for(int j=0; j < column; j++){
                if(this.board2D[i][j] == -1)
                    return i;
            }
        }

        return 0;
    }

    /**
     * Constructor for BoardArray2D
     */
    public BoardArray2D()
    {
        row = 3;
        column = 3;
        board2D = new int[row][column];
        NumberOfBoards();
    }
    /**
     * Two boards are equal, if the boards are the same.
     * @param other is the board for comparing.
     * @return true if boards are equal else return false.
     */
    @Override
    public boolean Equals(AbstractBoard other)
    {
        if(this.row !=((BoardArray2D)other).row || this.column !=((BoardArray2D)other).column )
        {
            return false;
        }
        for(int i=0; i < row; i++){
            for(int j=0; j < column; j++){
                if(this.board2D[i][j] != ((BoardArray2D)other).board2D[i][j] )
                    return false;
            }
        }
        return true;
    }
    /**
     * Takes two indexes and returns the corresponding cell content.
     * @param index1 correspond coord x.
     * @param index2 correspond coord y.
     * @return corresponding cell content.
     */
    @Override
    public int cell(int index1, int index2)
    {
        if(index1 < 0 || index1 > row || index2 < 0 || index2 > column)
            System.exit(1);
        return board2D[index1][index2];
    }
    /**
     *Writes the board to the file given as function parameter.
     * @param fileName is the filename for writing file.
     */
    @Override
    public void  writeToFile(String fileName)
    {
        int i, j;

        try{
            FileWriter myWriter = new FileWriter(fileName);

            if(getFileBoardControl()){

                for(i=0; i < row; i++){
                    for(j=0; j < column; j++){

                        if(board2D[i][j] == -1 ){
                            myWriter.write("bb");
                            if(j != column - 1)
                                myWriter.write(" ");
                        }
                        else{
                            if(board2D[i][j] != -1){
                                if(board2D[i][j] <= 9){
                                    myWriter.write("0");
                                    myWriter.write(String.valueOf(board2D[i][j]) );
                                }
                                else{
                                    myWriter.write(String.valueOf(board2D[i][j]));
                                }
                                if(j != (column-1))
                                    myWriter.write(" ");
                            }
                        }
                    }
                    if(i != row - 1){
                        myWriter.write("\n");
                    }
                }
                myWriter.write("\n");
            }
            else{ //Came from file.
                for (i=0; i < row; ++i){
                    for (j=0; j < column; ++j){
                        if(board2D[i][j] != -1){
                            int digit = calculate_digit_number(board2D[i][j]);
                            if(digit < 2){
                                myWriter.write("0");
                                myWriter.write(String.valueOf(board2D[i][j]) );
                                if(j != column - 1)
                                    myWriter.write(" ");

                            }
                            else{
                                myWriter.write(String.valueOf(board2D[i][j]) );
                                if(j != column - 1)
                                    myWriter.write(" ");
                            }
                        }
                        else{
                            myWriter.write("bb");
                            if(j != column - 1)
                                myWriter.write(" ");
                        }
                    }
                    myWriter.write("\n");
                }
            }
            myWriter.close();
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }

    }
    /**
     * Reads the board from the file given as function parameter.
     * @param fileName is the filename for reading file.
     */
    @Override
    public void readFromFile(String fileName)
    {
        int my_line_number = 0, my_total_space = 0;
        String line;
        int i=0,j=0;
        try{
            File file = new File(fileName);
            BufferedReader br = new BufferedReader(new FileReader(file));
            while((line = br.readLine()) != null){
                my_line_number++; // Calculate line number.
                for(i = 0; i < line.length(); ++i){
                    if(line.charAt(i) == ' ')
                        my_total_space++; //Calculate all spaces in the file.
                }
            }

            br.close();

            row = my_line_number;
            column = (my_total_space / row) + 1;

            setSize(row,column);

            br = new BufferedReader(new FileReader(file));

            char [][]  temp_ch_array = new char [row][((column * 2) + (column - 1))];

            j = 0;
            while((line = br.readLine()) != null){
                for(i = 0; i < ((column * 2) + (column - 1)); ++i){
                    if(line.charAt(i) != ' ') {
                        temp_ch_array[j][i] = line.charAt(i);
                    }
                }
                j++;
            }

            br.close();

            for(int k=0; k < row; k++){ //Convert string to integer.
                for(int l=0; l < ((column * 2) + (column - 1)); l=l+3){
                    char  first_index, second_index;
                    String str_1 = "", str_2 = "", string_number;
                    int number;

                    first_index = temp_ch_array[k][l];
                    second_index = temp_ch_array[k][l + 1];
                    if(first_index == 'b'){
                        number = -1;
                        board2D[k][l/3] = number;
                    }
                    else{
                        str_1 = str_1 + first_index;
                        str_2 = str_2 + second_index;
                        string_number = str_1 + str_2;

                        try {
                            number = Integer.valueOf(string_number);
                            board2D[k][l/3] = number;

                        } catch (NumberFormatException nfe) {
                        }
                    }
                }
            }
        }
        catch (IOException E){
            E.getStackTrace();
        }
        setFileBoardControl(false); //file_board_control setting to false.
    }
    /**
     * Checks the board is a solution.
     * @return true if solution is found else return false.
     */
    @Override
    public boolean isSolved()
    {
        int [] temp_array = new int[row*column];
        int i, j, size1, size2;
        int k = 0, game_over = 0,controller = 0;

        size1 = row;
        size2 = column;

        if(getFileBoardControl() == true){
            for(i=0; i < size1; i++){
                for(j=0; j < size2; j++){
                    temp_array[k] = board2D[i][j];
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
                    if(board2D[i][j] != 0){
                        temp_array[k] = board2D[i][j];
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
    /**
     * Resets the board to the solution.
     */
    @Override
    public void reset()
    {
        if(getFileBoardControl()){
            int i=0, j=0, k;

            for(k=1; k <= (row * column); k++){
                if(k == (row * column)){
                    board2D[row-1][column-1] = -1;
                }
                else{
                    if(k % (row) == 0){
                        board2D[i][j] = k;
                        i++;
                        j=0;
                    }
                    else{
                        board2D[i][j] = k;
                        j++;
                    }
                }
            }
        }
        else{ //Came from file.
            int my_number = 1, i, j;
            for(i=0; i < row; i++){ //Takes final board.
                for(j=0; j < column; j++){
                    if(board2D[i][j] != 0){
                        board2D[i][j] = my_number;
                        my_number++;
                    }
                    if(i == row - 1 && j == column - 1)
                        board2D[i][j] = -1;
                }
            }
        }
        toString();
    }
    /**
     * Makes a move according to the given char parameter.
     * @param move if move is 'R'. Empty blank moves right.
     * @param controller checks that the movement has already taken place.
     * @return true if move is valid else return false.
     */
    @Override
    public boolean move(char move, int controller)
    {
        int i, j, row_num, column_num;

        row_num = row;
        column_num = column;

        if(move == 'R'){ //The empty cell is moved in the right direction.
            for(i=0; i < row_num; i++){
                for(j=0; j < column_num && controller == 1; j++){
                    if(board2D[i][j] == -1){
                        if(j != (column_num - 1) && board2D[i][j+1] != 0){ //If the right side does not exceed the board limit, movement is made.
                            int right_temp_number;

                            right_temp_number = board2D[i][j+1];
                            board2D[i][j+1] = -1;
                            board2D[i][j] = right_temp_number;
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
                    if(board2D[i][j] == -1){
                        if(j != 0 && board2D[i][j-1] != 0){ //If the left side does not exceed the board limit, movement is made.
                            int left_temp_number;

                            left_temp_number = board2D[i][j-1];
                            board2D[i][j-1] = -1;
                            board2D[i][j] = left_temp_number;

                            return true;
                        }
                    }
                }
            }
        }
        else if(move == 'U'){ //The empty cell is moved in the up.
            for(i=0; i < row_num; i++){
                for(j=0; j < column_num; j++){
                    if(board2D[i][j] == -1){
                        if(i != 0 && board2D[i-1][j] != 0){ //If the up side does not exceed the board limit, movement is made.
                            int up_temp_number;

                            up_temp_number = board2D[i-1][j];
                            board2D[i-1][j] = -1;
                            board2D[i][j] = up_temp_number;

                            return true;
                        }
                    }
                }
            }
        }
        else if(move == 'D'){ //The empty cell is moved in the down.
            for(i=0; i < row_num && controller == 1; i++){
                for(j=0; j < column_num && controller == 1; j++){
                    if(board2D[i][j] == -1){
                        if(i != (row_num - 1) && board2D[i+1][j] != 0){ //If the down side does not exceed the board limit, movement is made.
                            int down_temp_number;

                            down_temp_number = board2D[i+1][j];
                            board2D[i+1][j] = -1;
                            board2D[i][j] = down_temp_number;
                            controller = 0;

                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
    /**
     * Initialize the board1D array randomly.
     */
    public void initialize2DBoard()
    {
        int [] controller_array = new int[row*column];
        int i, j, k;
        int random;
        int l=0,flag = 1,controller = 0;

        for(i=0; i < row; i++){
            for(j=0; j < column; j++){
                flag = 1;
                random = (int)(1 + Math.random() * ((row * column)));
                for(k=0; k < controller; k++){
                    if(random == controller_array[k])
                        flag = 0;
                }
                if(flag == 1){
                    controller_array[l] = random;
                    board2D[i][j] = random;
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
                if(board2D[i][j] == (row * column))
                    board2D[i][j] = -1;
            }
        }
    }
    /**
     * This method produces the board as string.
     * @return Returns formatted string version of the board.
     */
    @Override
    public String toString() {

        String result = "";
        String temp = "";
        String temp0 ="";

        if(getFileBoardControl()){
            for(int i = 0; i < row; ++i)
            {
                for(int j = 0; j < column; ++j)
                {
                    if(board2D[i][j] == -1){
                        temp = " ";
                        temp = temp + "\t";
                        result = result + temp;
                    }
                    else{
                        temp = String.valueOf(board2D[i][j]);
                        temp = temp + "\t";
                        result = result + temp;
                    }

                }
                temp = "";
                temp = temp + "\n";
                result = result + temp;
            }
        }
        else{
            int i ,j;
            for (i=0; i < row; ++i) {
                for (j=0; j < column; ++j) {
                    if(board2D[i][j] != -1){
                        int digit = calculate_digit_number(board2D[i][j]);
                        if(digit < 2){
                            temp0 = "0";
                            temp = String.valueOf(board2D[i][j]);
                            temp = temp0 + temp;
                            temp = temp + "\t";
                            result = result + temp;
                        }
                        else{
                            temp = String.valueOf(board2D[i][j]);
                            temp =  temp + "\t";
                            result = result + temp;
                        }
                    }
                    else{
                        temp = "bb";
                        temp = temp + "\t";
                        result = result + temp;
                    }
                }
                temp = "";
                temp = temp + "\n";
                result = result + temp;
            }
        }
        return  result;
    }
    /**
     * Sets the board size to given values.
     * @param rowValue is the number of rows of board.
     * @param columnValue is the number of columns of board.
     */
    @Override
    public void setSize(int rowValue, int columnValue)
    {
        row = rowValue;
        column = columnValue;

        board2D = new int[row][column];

        initialize2DBoard();
    }

}

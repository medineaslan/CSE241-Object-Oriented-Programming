import java.io.*;
import java.io.FileWriter;
import java.io.IOException;

/**
 * BoardArray1D class with some methods
 * @author Medine ASLAN
 */

public class BoardArray1D extends AbstractBoard
{
    private int [] board1D;
    private int size1;
    private int size2;

    /**
     * Find empty cell's index i for global function.
     * @return index i.
     */
    public int findEmptyCellIndexI()
    {
        for(int i = 0; i < size1*size2; i++){
            if(this.board1D[i] == -1){
                return (i/size2);
            }
        }
        return 0;
    }
    /**
     * Find empty cell's index j for global function.
     * @return index j.
     */
    public int findEmptyCellIndexJ()
    {
        for(int i = 0; i < size1*size2; i++){
            if(this.board1D[i] == -1){
                return i % (size2);
            }
        }
        return 0;
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
        if(index1 < 0 || index1 > size1 || index2 < 0 || index2 > size2)
            System.exit(1);

        return board1D[(index1*size2) + index2];
    }
    /**
     * Two boards are equal, if the boards are the same.
     * @param other is the board for comparing.
     * @return true if boards are equal else return false.
     */
    @Override
    public boolean Equals(AbstractBoard other)
    {
        if(this.size1 !=((BoardArray1D)other).size1 || this.size2 !=((BoardArray1D)other).size2 )
        {
            return false;
        }
        for(int i = 0; i < (size1 * size2); i++){
            if(this.board1D[i] != ((BoardArray1D)other).board1D[i])
                return false;
        }
        return true;
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

                for(i=0; i < (size1 * size2); i++){
                        if(board1D[i] == -1 ){
                            myWriter.write("bb");
                            if(i != (size1 * size2)- 1)
                                myWriter.write(" ");
                        }
                        else{
                            if(board1D[i] != -1){
                                if(board1D[i] <= 9){
                                    myWriter.write("0");
                                    myWriter.write(String.valueOf(board1D[i]) );
                                }
                                else{
                                    myWriter.write(String.valueOf(board1D[i]));
                                }
                                if(i != (size1 * size2) - 1)
                                    myWriter.write(" ");
                            }
                        }

                    if(((i % size1) + 1) % size1 == 0 && (i != (size1*size2)-1)){
                        myWriter.write("\n");
                    }
                }
                myWriter.write("\n");
            }
            else{ //Came from file.
                for (i=0; i < (size1 * size2); i++){
                        if(board1D[i] != -1){
                            int digit = calculate_digit_number(board1D[i]);
                            if(digit < 2){
                                myWriter.write("0");
                                myWriter.write(String.valueOf(board1D[i]) );
                                if(i != (size1 * size2) - 1)
                                    myWriter.write(" ");

                            }
                            else{
                                myWriter.write(String.valueOf(board1D[i]) );
                                if(i != (size1 * size2) - 1)
                                    myWriter.write(" ");
                            }
                        }
                        else{
                            myWriter.write("bb");
                            if(i != (size1 * size2) - 1)
                                myWriter.write(" ");
                        }
                    if(((i % size1) + 1) % size1 == 0 && (i != (size1*size2)-1))
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

            size1 = my_line_number;
            size2 = (my_total_space / size1) + 1;

            setSize(size1,size2);

            br = new BufferedReader(new FileReader(file));

            int a = 0;
            char [][]  temp_ch_array = new char [size1][((size2 * 2) + (size2 - 1))];

            j = 0;
            while((line = br.readLine()) != null){
                for(i = 0; i < ((size2 * 2) + (size2 - 1)); ++i){
                    if(line.charAt(i) != ' ') {
                        temp_ch_array[j][i] = line.charAt(i);
                    }
                }
                j++;
            }

            br.close();

            for(int k=0; k < size1; k++){ //Convert string to integer.
                for(int l=0; l < ((size2 * 2) + (size2 - 1)); l=l+3){
                    char  first_index, second_index;
                    String str_1 = "", str_2 = "", string_number;
                    int number;

                    first_index = temp_ch_array[k][l];
                    second_index = temp_ch_array[k][l + 1];
                    if(first_index == 'b'){
                        number = -1;
                        board1D[a] = number;
                        a++;
                    }
                    else{
                        str_1 = str_1 + first_index;
                        str_2 = str_2 + second_index;
                        string_number = str_1 + str_2;

                        try {
                            number = Integer.valueOf(string_number);
                            board1D[a] = number;
                            a++;

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
        int [] temp_array = new int [size1*size2];
        int i, j, temp_size1, temp_size2;
        int k = 0, game_over = 0,controller = 0;

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
    /**
     * Resets the board to the solution.
     */
    @Override
    public void reset()
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
        int i, row_num;
        int column_num;

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
    /**
     * This method produces the board as string.
     * @return Returns formatted string version of the board.
     */
    @Override
    public String toString()
    {
        String result = "";
        String temp = "";
        String temp0 = "";

        int i;
        if(getFileBoardControl()){
            for(i=0; i < size1*size2; i++){
                if( !(((i % size2) + 1) % size2 == 0)){
                    if(board1D[i] == -1){
                        temp = " ";
                        temp = temp + "\t";
                        result = result + temp;
                    }
                    else{
                        temp = String.valueOf(board1D[i]);
                        temp = temp + "\t";
                        result = result + temp;
                    }
                }
                else{
                    if(board1D[i] == -1){
                        temp = " ";
                        temp0 = "\n";
                        temp = temp + temp0;
                        result = result + temp;
                    }
                    else{
                        temp = String.valueOf(board1D[i]);
                        temp = temp + "\n";
                        result = result + temp;
                    }
                }
            }
        }
        else{
            for (i=0; i < size1 * size2; ++i) {
                if(board1D[i] != -1){
                    int digit = calculate_digit_number(board1D[i]);
                    if(digit < 2){
                        temp0 = "0";
                        temp = String.valueOf(board1D[i]);
                        temp = temp0 + temp;
                        temp = temp + "\t";
                        result = result + temp;
                    }
                    else{
                        temp = String.valueOf(board1D[i]);
                        temp = temp + "\t";
                        result = result + temp;
                    }
                }
                else{
                    temp = "bb";
                    temp = temp + "\t";
                    result = result + temp;
                }
                if( ((i % size1) + 1) % size1 == 0){
                    temp = "";
                    temp = temp + "\n";
                    result = result + temp;
                }
            }
        }
        temp = "";
        temp = temp + "\n";
        result = result + temp;

        return result;
    }

    /**
     * Initialize the board1D array randomly.
     */
    public void initialize1DBoard()
    {
        int i,j, random;
        int [] controller_array = new int [size1*size2];
        int controller=0, flag = 1, l=0;

        for(i=0; i < size1*size2; i++){
            flag = 1;
            random = (int)(1 + Math.random() * ((size1 * size2)));
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
    /**
     * Sets the board size to given values.
     * @param rowValue is the number of rows of board.
     * @param columnValue is the number of columns of board.
     */
    @Override
    public void setSize(int rowValue, int columnValue)
    {
        size1 = rowValue;
        size2 = columnValue;

        board1D = new int[size1*size2];

        initialize1DBoard();
    }

}

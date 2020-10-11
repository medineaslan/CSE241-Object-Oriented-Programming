/**
 * AbstractBoard abstract class with definition of some methods.
 * @author Medine ASLAN
 */
public abstract class AbstractBoard {

    private int numberOfBoards = 0;
    private char myLastMove = 'S';
    private int myNumberOfMoves = 0;
    private boolean file_board_control = true;

    /**
     * This method produces the board as string.
     * @return Returns formatted string version of the board.
     */
    @Override
    public abstract String toString();

    /**
     * Reads the board from the file given as function parameter.
     * @param fileName is the filename for reading file.
     */
    public abstract void readFromFile(String fileName);

    /**
     *Writes the board to the file given as function parameter.
     * @param fileName is the filename for writing file.
     */
    public abstract void writeToFile(String fileName);

    /**
     * Resets the board to the solution.
     */
    public abstract void reset();

    /**
     * Sets the board size to given values.
     * @param rowValue is the number of rows of board.
     * @param columnValue is the number of columns of board.
     */
    public abstract void setSize(int rowValue, int columnValue);

    /**
     * Makes a move according to the given char parameter.
     * @param move if move is 'R'. Empty blank moves right.
     * @param controller checks that the movement has already taken place.
     * @return true if move is valid else return false.
     */
    public abstract boolean move(char move, int controller);

    /**
     * Checks the board is a solution.
     * @return true if solution is found else return false.
     */
    public abstract boolean isSolved();

    /**
     * Takes two indexes and returns the corresponding cell content.
     * @param index1 correspond coord x.
     * @param index2 correspond coord y.
     * @return corresponding cell content.
     */
    public abstract int cell(int index1, int index2);

    /**
     * Two boards are equal, if the boards are the same.
     * @param other is the board for comparing.
     * @return true if boards are equal else return false.
     */
    public abstract boolean Equals(AbstractBoard other);

    /**
     * Find empty cell's index i for global function.
     * @return index i.
     */
    public abstract int findEmptyCellIndexI();

    /**
     * Find empty cell's index j for global function.
     * @return index j.
     */
    public abstract int findEmptyCellIndexJ();

    /**
     *
     * @return numberOfBoards
     */
    public int getNumberOfBoards()
    {
        return numberOfBoards;
    }

    /**
     *
     * @return myNumberOfMoves
     */
    public int getMyNumberOfMoves()
    {
        return myNumberOfMoves;
    }

    /**
     *
     * @return myLastMove
     */
    public char getMyLastMove()
    {
        return myLastMove;
    }

    /**
     * If move is valid then increase and return numberOfMoves
     * @param solveControl controls the is move is valid.
     * @return current number of moves.
     */
    public int numberOfMoves(boolean solveControl){
        if(solveControl){
            myNumberOfMoves++;
        }
        return myNumberOfMoves;
    }

    /**
     * When a object created, this function calls and increase the number of board.
     * @return current number of boards.
     */
    public int NumberOfBoards(){
        return numberOfBoards++;
    }

    /**
     * Change the last move .
     * @param myMove is the last move as parameter.
     * @return current last move.
     */
    public char lastMove(char myMove){
        myLastMove = myMove;

        return myLastMove;
    }

    /**
     * Getter for file board control
     * @return file_board_control
     */
    public boolean getFileBoardControl()
    {
        return file_board_control;
    }

    /**
     * Calculating digit number
     * @param number is the number for finding digit number.
     * @return digit number.
     */
    public int calculate_digit_number(int number){
        int count = 0;

        while(number > 0){
            number = number / 10;
            count++;
        }
        return count;
    }

    /**
     * Sets the file board control
     * @param file_board_control_value changes the file_board_control
     */
    public void setFileBoardControl(boolean file_board_control_value)
    {
        file_board_control = file_board_control_value;
    }
}

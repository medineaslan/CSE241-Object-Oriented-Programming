import java.util.Scanner;
/**
 * Driver class that tests AbstractBoard, BoardArray1D, BoardArray2D.
 * @author Medine ASLAN
 */
public class Test {

    /**
     * Driver code for global function.Move sequence is valid or not.
     * @param arr Keep the AbstractBoard objects.
     * @param size Size of the arr
     * @return true if move sequence is valid.
     */
    public static boolean driverGlobalFunction(AbstractBoard [] arr, int size)
    {
        boolean flagForMove = false;
        for(int i = 0 ; i < size; ++i)
        {
            System.out.println(arr[i].toString());
        }

        for(int i = 0; i < size-1; ++i)
        {
            flagForMove = false;
            if(arr[i].findEmptyCellIndexI() == arr[i+1].findEmptyCellIndexI())
            {
                int abs = arr[i].findEmptyCellIndexJ() - arr[i+1].findEmptyCellIndexJ();
                if( abs == 1 || abs == -1){
                    flagForMove = true;
                }
            }
            else if(arr[i].findEmptyCellIndexJ() == arr[i+1].findEmptyCellIndexJ())
            {
                int abs = arr[i].findEmptyCellIndexI() - arr[i+1].findEmptyCellIndexI();
                if( abs == 1 || abs == -1){
                    flagForMove = true;
                }
            }
        }

        return flagForMove;
    }

    /**
     * Initialize different AbstractBoard array.
     * @param i test cases.
     * @return true if move sequence is valid.
     */
    public static boolean initializeBoardsForGlobalFunc(int i)
    {
        if(i == 0) ///2li valid 1D
        {
            BoardArray1D arr1 = new BoardArray1D();
            arr1.setSize(4,4);
            BoardArray1D arr2 = new BoardArray1D();
            arr2.setSize(4,4);

            arr1.reset();
            arr2.reset();

            arr2.move('L',1);

            AbstractBoard [] abstractBoard = new AbstractBoard[2];

            abstractBoard[0] = arr1;
            abstractBoard[1] = arr2;

            return driverGlobalFunction(abstractBoard,2);
        }
        if(i == 1) //2 li not valid 1D
        {
            BoardArray1D arr1 = new BoardArray1D();
            arr1.setSize(4,4);
            BoardArray1D arr2 = new BoardArray1D();
            arr2.setSize(4,4);

            arr1.reset();
            arr2.reset();

            arr2.move('U',1);
            arr2.move('U',1);

            AbstractBoard [] abstractBoard = new AbstractBoard[2];

            abstractBoard[0] = arr1;
            abstractBoard[1] = arr2;

            return driverGlobalFunction(abstractBoard,2);

        }
        if(i == 2) //3 lü valid 2D
        {
            BoardArray2D arr1 = new BoardArray2D();
            arr1.setSize(4,4);
            BoardArray2D arr2 = new BoardArray2D();
            arr2.setSize(4,4);
            BoardArray2D arr3 = new BoardArray2D();
            arr3.setSize(4,4);

            arr1.reset();
            arr2.reset();
            arr3.reset();

            arr2.move('U',1);
            arr3.move('U',1);
            arr3.move('L',1);


            AbstractBoard [] abstractBoard = new AbstractBoard[3];

            abstractBoard[0] = arr1;
            abstractBoard[1] = arr2;
            abstractBoard[2] = arr3;

            return driverGlobalFunction(abstractBoard,3);
        }
        if(i == 3) //3 lü not valid 2D
        {
            BoardArray2D arr1 = new BoardArray2D();
            arr1.setSize(3,3);
            BoardArray2D arr2 = new BoardArray2D();
            arr2.setSize(3,3);
            BoardArray2D arr3 = new BoardArray2D();
            arr3.setSize(3,3);

            arr1.reset();
            arr2.reset();
            arr3.reset();

            arr2.move('U',1);
            arr3.move('L',1);

            AbstractBoard [] abstractBoard = new AbstractBoard[3];

            abstractBoard[0] = arr1;
            abstractBoard[1] = arr2;
            abstractBoard[2] = arr3;

            return driverGlobalFunction(abstractBoard,3);
        }
        if(i == 4) //3lü valid 1D
        {
            BoardArray1D arr1 = new BoardArray1D();
            arr1.setSize(3,3);
            BoardArray1D arr2 = new BoardArray1D();
            arr2.setSize(3,3);
            BoardArray1D arr3 = new BoardArray1D();
            arr3.setSize(3,3);

            arr1.reset();
            arr2.reset();
            arr3.reset();

            arr2.move('U',1);
            arr3.move('U',1);
            arr3.move('L',1);

            AbstractBoard [] abstractBoard = new AbstractBoard[3];

            abstractBoard[0] = arr1;
            abstractBoard[1] = arr2;
            abstractBoard[2] = arr3;

            return driverGlobalFunction(abstractBoard,3);
        }

        return true;

    }

    /**
     * Driver code for BoardArray2D
     */
    public static void driverBoardArray2D()
    {
        System.out.println("BOARDARRAY2D CLASS");

        Scanner inputObj = new Scanner(System.in);

        System.out.println( "Please enter the problem size");

        int size1D = inputObj.nextInt();

        BoardArray2D boardArr2D = new BoardArray2D();

        boardArr2D.setSize(size1D,size1D);
        System.out.println(boardArr2D.toString());

        System.out.println("Move:R");
        boardArr2D.lastMove('R');

        boolean control = boardArr2D.move('R',1);

        boardArr2D.numberOfMoves(control);

        System.out.println(boardArr2D.toString());

        System.out.println("Move:L");
        boardArr2D.lastMove('L');
        control = boardArr2D.move('L',1);
        boardArr2D.numberOfMoves(control);

        System.out.println(boardArr2D.toString());

        System.out.println("Move:U");
        boardArr2D.lastMove('U');
        control = boardArr2D.move('U',1);
        boardArr2D.numberOfMoves(control);

        System.out.println(boardArr2D.toString());

        System.out.println("Move:D");
        boardArr2D.lastMove('D');
        control = boardArr2D.move('D',1);
        boardArr2D.numberOfMoves(control);

        System.out.println(boardArr2D.toString());

        System.out.println("Please enter file name for writing file");

        Scanner inputObj2 = new Scanner(System.in);

        String fileName1D = inputObj2.nextLine();

        boardArr2D.writeToFile(fileName1D);

        System.out.println("Please enter file name for reading file");

        fileName1D = inputObj2.nextLine();

        boardArr2D.readFromFile(fileName1D);

        System.out.println(boardArr2D.toString());

        System.out.println("Move:R");
        control = boardArr2D.move('R',1);
        boardArr2D.lastMove('R');
        boardArr2D.numberOfMoves(control);

        System.out.println(boardArr2D.toString());

        System.out.println("Move:L");
        boardArr2D.lastMove('L');

        control = boardArr2D.move('L',1);
        boardArr2D.numberOfMoves(control);

        System.out.println(boardArr2D.toString());

        System.out.println("Reset");
        boardArr2D.reset();

        System.out.println(boardArr2D.toString());

        System.out.println("isSolved : " + boardArr2D.isSolved() );
        System.out.println("Last Move : " + boardArr2D.getMyLastMove() );
        System.out.println("Number of Moves : " + boardArr2D.getMyNumberOfMoves() );
        System.out.println("Number of Boards : " + boardArr2D.getNumberOfBoards() );

    }
    /**
     * Driver code for BoardArray1D
     */
    public static void driverBoardArray1D()
    {
        System.out.println("BOARDARRAY1D CLASS");

        Scanner inputObj = new Scanner(System.in);

        System.out.println( "Please enter the problem size");

        int size1D = inputObj.nextInt();

        BoardArray1D boardArr1D = new BoardArray1D();

        boardArr1D.setSize(size1D,size1D);
        System.out.println(boardArr1D.toString());

        System.out.println("Move:R");

        boolean control = boardArr1D.move('R',1);
        System.out.println(boardArr1D.toString());

        System.out.println("Move:L");
        control = boardArr1D.move('L',1);

        System.out.println(boardArr1D.toString());

        System.out.println("Move:U");
        control = boardArr1D.move('U',1);

        System.out.println(boardArr1D.toString());

        System.out.println("Move:D");
        control = boardArr1D.move('D',1);

        System.out.println(boardArr1D.toString());

        System.out.println("Please enter file name for writing file");

        Scanner inputObj2 = new Scanner(System.in);

        String fileName1D = inputObj2.nextLine();

        boardArr1D.writeToFile(fileName1D);

        System.out.println("Please enter file name for reading file");

        fileName1D = inputObj2.nextLine();

        boardArr1D.readFromFile(fileName1D);

        System.out.println(boardArr1D.toString());

        System.out.println("Move:R");
        control = boardArr1D.move('R',1);

        System.out.println(boardArr1D.toString());

        System.out.println("Move:L");
        control = boardArr1D.move('L',1);

        System.out.println(boardArr1D.toString());

        System.out.println("Reset");
        boardArr1D.reset();

        System.out.println(boardArr1D.toString());

        System.out.println("(0,1) Cell content: "+ boardArr1D.cell(0,1));

        System.out.println("isSolved : " + boardArr1D.isSolved() );

        BoardArray1D board1 = new BoardArray1D();
        board1.setSize(3,3);
        BoardArray1D board2 = new BoardArray1D();
        board2.setSize(3,3);

        System.out.println(board1.toString());
        System.out.println(board2.toString());

        if(board1.Equals(board2))
        {
            System.out.println("Boards are equal.");
        }
        else{
            System.out.println("Boards are not equal.");
        }
    }

    public static void main(String[] args) throws CloneNotSupportedException {

        System.out.println("FUNCTION TESTS");

        Scanner inputObj = new Scanner(System.in);

        System.out.println("1 - BoardArray1D");
        System.out.println("2 - BoardArray2D");
        System.out.println("3 - GLOBAL FUNCTION");

        int choice = inputObj.nextInt();

        System.out.println("Your Choice : " + choice);

        switch(choice)
        {
            case 1 :
                driverBoardArray1D();
                break;
            case 2 :
                driverBoardArray2D();
                break;
            case 3 :
            {
                for(int i = 0; i < 5; ++i)
                {
                    boolean isValid = initializeBoardsForGlobalFunc(i);

                    if(isValid)
                        System.out.println("Valid sequence of moves");
                    else
                        System.out.println("Not valid sequence of moves");
                }
                break;
            }
            default:
                System.out.println("Invalid choice");
        }
    }
}

/**
 * Driver class that tests concrete collections.
 * @author Medine ASLAN
 */
public class Test {
    /**
     * It is for separating different tests with each other
     */
    public static void printSeparator()
    {
        System.out.println("=============================================================================");
    }

    /**
     * It is for testing GTUSet
     */
    public static void testGTUSetWithInteger()
    {
        printSeparator();
        System.out.println("Test of GTUSet");
        printSeparator();


        printSeparator();
        System.out.println("Test of insert method");
        GTUSet<Integer> gtuSet = new GTUSet<>();
        try {
            for(int i = 0; i < 8; ++i)
                gtuSet.insert(i + 1);
            gtuSet.insert(1); //It will not inserted
            gtuSet.insert(2); //It will not inserted
            gtuSet.insert(3); //It will not inserted
        }
        catch (Exception ex)
        {
            ex.getStackTrace();
        }
        System.out.println(gtuSet.toString());
        printSeparator();


        printSeparator();
        System.out.println("Test of size method");
        System.out.println(gtuSet.size());
        printSeparator();


        printSeparator();
        System.out.println("Test of erase method");
        int erasedItem = 5;
        System.out.println("Try to erase : " + erasedItem);
        gtuSet.erase(erasedItem);
        System.out.println("After erase operation");
        System.out.println(gtuSet.toString());
        erasedItem = 11;
        System.out.println("Try to erase : " + erasedItem);
        gtuSet.erase(erasedItem);
        System.out.println("After erase operation");
        System.out.println(gtuSet.toString());
        printSeparator();


        printSeparator();
        System.out.println("Test of contains method");
        int containsItem = 5;
        System.out.println("Try to contains method with item : " + containsItem);
        if(gtuSet.contains(containsItem))
            System.out.println("Item is in the set");
        else
            System.out.println("Item is not in the set");
        containsItem = 4;
        System.out.println("Try to contains method with item : " + containsItem);
        if(gtuSet.contains(containsItem))
            System.out.println("Item is in the set");
        else
            System.out.println("Item is not in the set");
        printSeparator();


        printSeparator();
        System.out.println("Test of clear method");
        gtuSet.clear();
        System.out.println(gtuSet.toString());
        printSeparator();


        printSeparator();
        System.out.println("Test of empty method");
        if(gtuSet.empty())
            System.out.println("Set is empty");
        else
            System.out.println("Set is not empty");
        printSeparator();


        printSeparator();
        System.out.println("Test of max size method");
        System.out.println(gtuSet.max_size());
        printSeparator();
    }

    /**
     * It is for testing GTUVector
     */
    public static void testGTUVectorWithString()
    {
        printSeparator();
        System.out.println("Test of GTUVector");
        printSeparator();


        printSeparator();
        System.out.println("Test of insert method");
        GTUVector<String> gtuVector = new GTUVector<>();
        try {

            gtuVector.insert("Pizza");
            gtuVector.insert("Hamburger");
            gtuVector.insert("Chicken");
            gtuVector.insert("Meat");
            gtuVector.insert("Spaghetti");
            gtuVector.insert("Chicken");
            gtuVector.insert("Pasta");
            gtuVector.insert("Salad");
            gtuVector.insert("Soup");
            gtuVector.insert("Pizza");
        }
        catch (Exception ex)
        {
            ex.getStackTrace();
        }
        System.out.println(gtuVector.toString());
        printSeparator();


        printSeparator();
        System.out.println("Test of size method");
        System.out.println(gtuVector.size());
        printSeparator();


        printSeparator();
        System.out.println("Test of erase method");
        String erasedItem = "Salad";
        System.out.println("Try to erase : " + erasedItem);
        gtuVector.erase(erasedItem);
        System.out.println("After erase operation");
        System.out.println(gtuVector.toString());
        erasedItem = "Orange";
        System.out.println("Try to erase : " + erasedItem);
        gtuVector.erase(erasedItem);
        System.out.println("After erase operation");
        System.out.println(gtuVector.toString());
        printSeparator();


        printSeparator();
        System.out.println("Test of contains method");
        String containsItem = "Salad";
        System.out.println("Try to contains method with item : " + containsItem);
        if(gtuVector.contains(containsItem))
            System.out.println("Item is in the vector");
        else
            System.out.println("Item is not in the vector");
        containsItem = "Pizza";
        System.out.println("Try to contains method with item : " + containsItem);
        if(gtuVector.contains(containsItem))
            System.out.println("Item is in the vector");
        else
            System.out.println("Item is not in the vector");
        printSeparator();


        printSeparator();
        System.out.println("Test of clear method");
        gtuVector.clear();
        System.out.println(gtuVector.toString());
        printSeparator();


        printSeparator();
        System.out.println("Test of empty method");
        if(gtuVector.empty())
            System.out.println("Vector is empty");
        else
            System.out.println("Vector is not empty");
        printSeparator();


        printSeparator();
        System.out.println("Test of max size method");
        System.out.println(gtuVector.max_size());
        printSeparator();
    }

    public static void main(String[] args) {
        testGTUSetWithInteger();
        System.out.println();
        testGTUVectorWithString();
    }
}

/**
 * GTUVector class with some methods
 * @author Medine ASLAN
 * @param <T> Generic type of objects
 */
public class GTUVector<T> extends GTUContainer<T> {
    /**
     * It is for determining how many item does collection have
     */
    private int size;
    /**
     * It is for determining how many item can collection hold.
     */
    private int capacity;
    /**
     * It is a generic type of the storage place.
     */
    private T [] arr;

    /**
     * No parameter constructor. It assignments first value of fields and makes allocation
     */
    @SuppressWarnings("unchecked")
    public GTUVector()
    {
        size = 0;
        capacity = 5;
        arr = (T[]) new Object[capacity];
    }

    /**
     * One parameter constructor. It assignments first value of fields and makes allocation
     * @param cap it is first capacity value from user defined
     */
    @SuppressWarnings("unchecked")
    public GTUVector(int cap)
    {
        size = 0;
        capacity = cap;
        arr = (T[]) new Object[capacity];
    }

    /**
     * This method controls that the collection is empty or not
     * @return Returns true if the collection is empty, otherwise returns false
     */
    @Override
    public boolean empty() {
        return size == 0;
    }

    /**
     * This method returns the size of the collection
     * @return Returns size of the collection
     */
    @Override
    public int size() {
        return size;
    }

    /**
     * This method returns the maximum number of elements a collection can hold
     * @return Returns max size of the collection
     */
    @Override
    public int max_size() {
        return 1073741823;
    }

    /**
     * This method inserts item to collection
     * @param item is the element of inserted
     * @return Returns true
     */
    @Override
    public boolean insert(T item) {
        if(isFull())
            reallocate();
        arr[size] = (T)item;
        size++;
        return true;
    }

    /**
     * This method erase the given item from the collection
     * @param item is the erased element
     */
    @Override
    public void erase(T item) {
        int index = findItemIndex(item);
        if(index != -1)
        {
            for(int i = index; i < size - 1; ++i)
                arr[i] = arr[i + 1];
            size--;
        }
    }

    /**
     * This method clears the collection
     */
    @SuppressWarnings("unchecked")
    @Override
    public void clear() {
        size = 0;
        arr = (T []) new Object[capacity];
    }

    /**
     * This method controls that, the collection has given element
     * @param item is the element for controlling if contains or not
     * @return Returns true if item is in the collection, otherwise returns false
     */
    @Override
    public boolean contains(T item) {
        for(int i = 0; i < size; ++i)
        {
            if(arr[i] == (T)item)
                return true;
        }
        return false;
    }

    /**
     * This method returns a GTUIterator object
     * @return Return a new GTUIterator
     */
    @Override
    public GTUIterator<T> iterator() {
        return new GTUVectorIterator<T>();
    }

    /**
     * This method return a formatted string version of the collection
     * @return Returns formatted string version of the collection
     */
    @Override
    public String toString()
    {
        GTUIterator it = iterator();
        String result = "[ ";
        while (it.hasNext())
        {
            result = result + String.valueOf(it.next()) + " ";
        }
        result = result + "]";
        return result;
    }

    /**
     * This method controls that size has reached the capacity
     * @return Returns true if collection is full
     */
    private boolean isFull()
    {
        return size == capacity;
    }

    /**
     * This method reallocates the storage of of the collection with two time capacity
     */
    @SuppressWarnings("unchecked")
    private void reallocate()
    {
        T [] newData;
        capacity = 2 * capacity;
        newData = (T []) new Object[capacity];

        for(int i = 0; i < size; ++i)
            newData[i] = (T) arr[i];

        arr = newData;
    }

    /**
     * This method search item. If it founds return the index of the item, otherwise returns -1
     * @param item is the searching element
     * @return Returns the index of given item if it was found, otherwise returns false
     */
    private int findItemIndex(T item)
    {
        for(int i = 0; i < size; ++i)
        {
            if(arr[i] == (T)item)
                return i;
        }
        return -1;
    }

    /**
     * @author Medine ASLAN
     * @param <T> Generic type of objects
     */
    private class GTUVectorIterator<T> implements GTUIterator<T>
    {
        /**
         * It represent the begin of collection
         */

        private int index = 0;
        /**
         * This method controls that, the collection has next item or not
         * @return Returns true if there is next item in the collection, otherwise returns false
         */
        @Override
        public boolean hasNext()
        {
            return index < size;
        }

        /**
         * This method returns the generic item T
         * @return Returns generic item T
         */
        @SuppressWarnings("unchecked")
        @Override
        public T next()
        {
            return (T) arr[index++];
        }
    }
}


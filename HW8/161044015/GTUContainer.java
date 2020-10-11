/**
 * GTUContainer abstract class with definition of some methods
 * @author Medine ASLAN
 * @param <T> Generic type of objects
 */
public abstract class GTUContainer<T> {
    /**
     * This method controls that the collection is empty or not
     * @return Returns true if the collection is empty, otherwise returns false
     */
    public abstract boolean empty();

    /**
     * This method returns the size of the collection
     * @return Returns size of the collection
     */
    public abstract int size();

    /**
     * This method returns the maximum number of elements a collection can hold
     * @return Returns max size of the collection
     */
    public abstract int max_size();

    /**
     * This method inserts item to collection
     * @param item is the element of inserted
     * @return Returns true
     */
    public abstract boolean insert(T item);

    /**
     * This method erase the given item from the collection
     * @param item is the erased element
     */
    public abstract void erase(T item);

    /**
     * This method clears the collection
     */
    public abstract void clear();

    /**
     * This method controls that, the collection has given element
     * @param item is the element for controlling if contains or not
     * @return Returns true if item is in the collection, otherwise returns false
     */
    public abstract boolean contains(T item);

    /**
     * This method returns a GTUIterator object
     * @return Return a new GTUIterator
     */
    public abstract GTUIterator<T> iterator();
}

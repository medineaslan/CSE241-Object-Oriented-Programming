/**
 * GTUIterator interface
 * @author Medine ASLAN
 * @param <T> Generic type of objects
 */
public interface GTUIterator<T> {
    /**
     * This method controls that, the collection has next item or not
     * @return Returns true if there is next item in the collection, otherwise returns false
     */
    boolean hasNext();

    /**
     * This method returns the generic item T
     * @return Returns generic item T
     */
    T next();
}
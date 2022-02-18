/**
 * An ordered collection (also known as a sequence). The user of this interface has precise control 
 * over where in the list each element is inserted. The user can access elements by their integer index 
 * (position in the list), and search for elements in the list.
 */
public interface List<E> extends Collection<E>{
    /**
     * It returns the data of the given index. This works only random access collections.
     * @param index
     * @return
     */
    public E get(int index);
}
import java.util.NoSuchElementException;

public class Iterator<E> {
    private E[] data;
    private int current = 0;
    private int size;
    private Collection<E> c;
    /**
     * 
     * @param data Data array of the current collection
     * @param size Size of the data array
     * @param c Current Collection
     */
    public Iterator(E[] data,int size,Collection<E> c){
        this.data = data;
        this.size=size;
        this.c=c;
    }
    /**
     * This function returns true if the collection has more elements.
     * @return
     */
    public boolean hasNext() {
        return current < size;
    }
    /**
     * This function returns the next element of the collection
     * @return
     */
    public E next() {
        if (!hasNext()) {
            throw new NoSuchElementException();
        }
        current++;
        return data[current-1];
    }
    /**
     * Removes from the underlying collection the last element returned
     * by this iterator. This method does not work for Queues, it throws
     * an exception.
     * 
     * @throws ClassFormatError
     */
    public void remove() throws ClassFormatError{
        if (!(c instanceof Queue)) {
            c.remove(data[current]);
        }
        else
            throw new ClassFormatError("This operation cannot be used on queues");
    }
}
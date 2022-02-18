/**
 * A collection designed for holding elements prior to processing. Besides basic Collection operations, 
 *  provide additional insertion, extraction, and inspection operations
 */
public interface Queue<E> extends Collection<E>{
    public boolean add(E e);
    public E element();
    public boolean offer(E e);
    public E poll();
}
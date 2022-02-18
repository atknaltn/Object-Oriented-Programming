/**
 * The root interface in the collection hierarchy. A collection represents a group of objects, 
 * known as its elements. Some collections allow duplicate elements and others do not. Some are ordered 
 * and others unordered.
 * 
 * 
 * @author Atakan Altın
 */
public interface Collection<E> {

    public Iterator<E> iterator();
    public boolean add(E e);
    public boolean addAll(Collection<E> c);
    public void clear();
    public boolean contains(E e);
    public boolean containsAll(Collection<E> c);
    public boolean isEmpty();
    public boolean remove(E e);
    public void removeAll(Collection<E> c);
    public void retainAll(Collection<E> c) ;
    public int size();
}
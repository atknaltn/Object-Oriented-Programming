import java.util.NoSuchElementException;

public class LinkedList<E> implements List<E>,Queue<E>{
    private E[] data;
    private int size=0;
    private int capacity=10;
    /**
    * This constructor creates LinkedList with default capacity 10. 
    * 
    */
    @SuppressWarnings("unchecked")
    public LinkedList(){
        data = (E[])new Object[this.capacity];
    }
    /**
     * This constructor creates LinkedList with given size.
     * @param size Size of the arraylist
     */
    @SuppressWarnings("unchecked")
    public LinkedList(int size){
        this.capacity=size;
        data = (E[])new Object[this.capacity];
    }
    /**
     * This function returns the current iterator of the collection.
     */
    @Override
    public Iterator<E> iterator() {
        return new Iterator<E>(data, size,this);
    }
    /**
     * This function adds the given element into collection's data array. If capacity is full then it increases capacity by 1.
     * @param e Element,data
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean add(E e) {
        int i;
        if (size>=capacity) {
            capacity=capacity+1;
        }
        if (data==null) {
            data = (E[])new Object[this.capacity];
        }
        E[] tempArr = (E[])new Object[capacity];
        for (i = 0; i < size; i++) {
            tempArr[i]=data[i];
        }
        tempArr[size]=(E)e;
        size=size+1;
        data=tempArr;
        return true;
    }
    /**
     * Adds all of the elements in the specified collection to this collection.
     * @param c Collection
     */
    @Override
    public boolean addAll(Collection<E> c) {
        Iterator<E> iter=c.iterator();
        while (iter.hasNext()) {
            add(iter.next());
        }
        return true;
    }
    /**
     * Removes all of the elements from this collection.
     * 
     */
    @Override
    public void clear() {
        for (int i = 0; i < size; i++) {
            data[i]=null;
        }
        data=null;
        size=0;
        capacity=10;
    }
    /**
     * Returns true if this collection contains the specified element.
     * @param e Element,data
     */
    @Override
    public boolean contains(E e) {
        for (int i = 0; i < size; i++) {
            if (data[i]==e) {
                return true;
            }
        }    
        return false;
    }
    /**
     * Returns true if this collection contains all of the elements in the specified collection.
     * @param c Collection
     */
    @Override
    public boolean containsAll(Collection<E> c) {
        Iterator<E> iter=c.iterator();
        while (iter.hasNext()) {
            if (this.contains(iter.next())==false) {
                return false;
            }
        }
        return true;
    }
    /**
     * Returns true if this collection contains no elements.
     */
    @Override
    public boolean isEmpty() {
        return size==0;
    }
    /**
     * Removes a single instance of the specified element from this collection, if it is present
     * @param e Element,data
     */
    @Override
    @SuppressWarnings("unchecked")
    public boolean remove(E e) {
        int index= findIndex(e);
        if (index!=-1) {
            if (size==1) {
                size=0;
                return true;
            }else{
                E[] tempArr = (E[])new Object[size-1];
                for (int i = 0,j=0; i < size; i++) {
                    if (i!=index) {
                        tempArr[j++] = data[i];
                    }
                }
                data=tempArr;
                size=tempArr.length;
                return true;
            }
        }else
            return false;
    }
    /**
     * Returns the index of given data.
     * @param e Element,data
     * @return
     */
    private int findIndex(E e){
        for (int i = 0; i < size; i++) {
            if (data[i].equals(e)) {
                return i;
            }
        }
        return -1;
    }
    /**
    * Removes all of this collection's elements that are also contained in the specified collection 
    * @param c Collection 
    */
    @Override
    public void removeAll(Collection<E> c) {
        int i;
        for (i = 0; i < size; i++) {
            Iterator<E> iter=c.iterator();
            while (iter.hasNext()) {
                if (data[i].equals(iter.next())) {
                    this.remove(data[i]);
                }
            }
        }
    }
    /**
     * Retains only the elements in this collection that are contained in the specified collection.
     * @param c Collection.
     */
    @Override
    @SuppressWarnings("unchecked")
    public void retainAll(Collection<E> c) {
        int i,count=0;
        E[] tempArr = (E[])new Object[capacity];
        for (i = 0; i < size; i++) {
            if (c.contains(data[i])) {
                tempArr[count]=data[i];
                count++;
            }
        }  
        size=count;
        data=tempArr;
    }
    /**
     * Returns true if the given element is in the given collection.
     * @param e Element,data
     * @param c Collection
     * @return
     */
    public boolean isExist(E e,Collection<E> c) {
        Iterator<E> iter=c.iterator();
        while (iter.hasNext()) {
            if (e.equals(iter.next())) {
                return true;
            }
        }
        return false;    
    }
    /**
    * Return size of the collection
    */
    @Override
    public int size() {
        return size;
    }
    /**
     * Retrieves, but does not remove, the head of this queue.
     * @throws NoSuchElementException
     */
    @Override
    public E element() throws NoSuchElementException{
        if (size==0) {
            throw new NoSuchElementException("Queue is Empty.");
        }else
            return data[0];
    }
    /**
     * 
     * Inserts the specified element into this queue if it is possible to do so 
     * immediately without violating capacity restrictions.
     * @param e Element,data
     */
    @Override
    public boolean offer(E e) {
        if (size>=capacity) {
            return false;
        }
        add(e);
        return true;
    }
    /**
     * Retrieves and removes the head of this queue, or throws if this queue is empty
     */
    @Override
    public E poll() throws NoSuchElementException{
        if (size==0) {
            throw new NoSuchElementException("Queue is empty.");
        }
        else{
            this.remove(data[0]);
            return data[0];
        }
    }
    /**
    * It returns the data in the given index.
    * @param index Index.
    */
    @Override
    public E get(int index) {
        return data[index];
    }   
}
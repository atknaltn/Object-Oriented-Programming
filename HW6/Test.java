import java.util.NoSuchElementException;
/**
 * Test Class
 */
public class Test {
    /**
     * This function prints contents of collections
     * 
     * @param <E> Data Type
     * @param c Collection Type
     */
    public static<E> void printData(Collection<E> c) {
        Iterator<E> itr = c.iterator();
        while (itr.hasNext()) {
            System.out.print(itr.next());
            if (itr.hasNext()) {
                System.out.print(" , ");
            }
        }
        System.out.println();
    }
    /**
     * Here is the main function to test all classes.
     * @param args
     */
    public static void main(String[] args) {
        ArrayList<Integer> arrList1 = new ArrayList<Integer>();
        ArrayList<String> arrList2 = new ArrayList<String>();
        HashSet<Integer> hashSet1 = new HashSet<Integer>();
        HashSet<String> hashSet2 = new HashSet<String>();
        LinkedList<Integer> linkedList1 = new LinkedList<Integer>();
        LinkedList<String> linkedList2 = new LinkedList<String>();

        for (int i = 0; i < 5; i++) {
            arrList1.add((i+1)*10);
            hashSet1.add((i+1)*20);
            linkedList1.add((i+1)*30);
        }
        arrList2.add("Atakan Altin");
        arrList2.add("Computer Engineering");
        arrList2.add("Turkey");
        hashSet2.add("Earth");
        hashSet2.add("Saturn");
        hashSet2.add("Neptun");
        linkedList2.add("C");
        linkedList2.add("C++");
        linkedList2.add("Java");
        System.out.println();
        System.out.println("/********* DATA STRUCTURES **********/");
        System.out.print("ArrayList 1: ");
        printData(arrList1);
        System.out.print("ArrayList 2: ");
        printData(arrList2);
        System.out.print("HashSet 1: ");
        printData(hashSet1);
        System.out.print("HashSet 2: ");
        printData(hashSet2);
        System.out.print("LinkedList 1: ");
        printData(linkedList1);
        System.out.print("LinkedList 2: ");
        printData(linkedList2);
        System.out.println();
        
        System.out.println("/************ADD ALL FUNCTION*****************/");
        arrList1.addAll(hashSet1);
        arrList1.addAll(linkedList1);
        System.out.print("ArrayList 1 (Integers):");
        printData(arrList1);
        arrList2.addAll(hashSet2);
        arrList2.addAll(linkedList2);
        System.out.print("ArrayList 2 (Strings):");
        printData(arrList2);
        System.out.println();

        System.out.println("/************CONTAINS FUNCTION*****************/");
        System.out.print("ArrayList1 does contain '56' ?: ");
        System.out.println(arrList1.contains(56));
        System.out.print("ArrayList2 does contain 'Atakan Altin' ?: ");
        System.out.println(arrList2.contains("Atakan Altin"));
        System.out.print("HashSet1 does contain '40' ?: ");
        System.out.println(hashSet1.contains(40));
        System.out.print("HashSet2 does contain 'Mars' ?: ");
        System.out.println(hashSet2.contains("Mars"));
        System.out.print("LinkedList1 does contain '135' ?: ");
        System.out.println(linkedList1.contains(135));
        System.out.print("LinkedList2 does contain 'Python' ?: ");
        System.out.println(linkedList2.contains("Python"));
        System.out.println();

        System.out.println("/************CONTAINS ALL FUNCTION*****************/");
        System.out.print("ArrayList1 does contain all elements of LinkedList1 ?: ");
        System.out.println(arrList1.containsAll(linkedList1));
        System.out.print("HashSet2 does contain all elements of ArrayList2 ?: ");
        System.out.println(hashSet2.containsAll(arrList2));
        System.out.println();

        System.out.println("/************REMOVE FUNCTION*****************/");
        System.out.println("'C++' removed from LinkedList2");
        System.out.print("LinkedList 2: ");
        linkedList2.remove("C++");
        printData(linkedList2);
        System.out.println("'60' removed from HashSet1");
        System.out.print("HashSet 1: ");
        hashSet1.remove(60);
        printData(hashSet1);
        System.out.println("'Computer Engineering' removed from ArrayList2");
        System.out.print("ArrayList2 : ");
        arrList2.remove("Computer Engineering");
        printData(arrList2);
        System.out.println();

        System.out.println("/************REMOVE ALL FUNCTION*****************/");
        System.out.println("Remove All The Elements Of LinkedList1 from ArrayList1 :");
        arrList1.removeAll(linkedList1);
        System.out.print("ArrayList 1: ");
        printData(arrList1);
        System.out.println("Remove All The Elements Of HashSet 2 from ArrayList2 :");
        arrList2.removeAll(hashSet2);
        System.out.print("ArrayList 2: ");
        printData(arrList2);
        System.out.println();
        //Throwlu Halini yap
        System.out.println("/************RETAIN ALL FUNCTION*****************/");
        System.out.println("Retain All The Elements Of ArrayList2 which are also in the LinkedList2 :");
        arrList2.retainAll(linkedList2);
        System.out.print("ArrayList2: ");
        printData(arrList2);
        System.out.println("Retain All The Elements Of ArrayList1 which are also in the HashSet1 :");
        arrList1.retainAll(hashSet1);
        System.out.print("ArrayList1: ");
        printData(arrList1);
        System.out.println("Retain All The Elements Of HashSet1 which are also in the LinkedList1 :");
        hashSet1.retainAll(linkedList1);
        System.out.print("HashSet1: ");
        printData(hashSet1);
        System.out.println();

        System.out.println("/************LINKED LIST OPERATORS*****************/");
        System.out.print("LinkedList 1: ");
        printData(linkedList1);
        System.out.print("LinkedList 2: ");
        printData(linkedList2);
        System.out.println();
        System.out.print("Head of the LinkedList1 is : ");
        System.out.println(linkedList1.element());
        System.out.print("Head of the LinkedList2 is : ");
        System.out.println(linkedList2.element());
        System.out.println();
        System.out.println("'7845 offered into LinkedList1 and 'Flutter' offered into LinkedList2");
        linkedList1.offer(7845);
        linkedList2.offer("Flutter");
        System.out.print("LinkedList 1: ");
        printData(linkedList1);
        System.out.print("LinkedList 2: ");
        printData(linkedList2);
        System.out.println();
        System.out.println("LinkedList1 and LinkedList2 are polled: ");
        try {
            linkedList1.poll();
            System.out.print("LinkedList 1: ");
            printData(linkedList1);
        } catch (NoSuchElementException e) {
            e.printStackTrace();
        }
        try {
            linkedList2.poll();
            System.out.print("LinkedList 2: ");
            printData(linkedList2);
        } catch (NoSuchElementException e) {
            e.printStackTrace();
        }
        System.out.println();
        System.out.println("/************CLEAR,SIZE AND IS EMPTY FUNCTION*****************/");
        System.out.println("ArrList2 ,HashSet1 and LinkedList2 will be deleted.");
        System.out.println();
        arrList2.clear();
        hashSet1.clear();
        linkedList2.clear();
        System.out.print("ArrayList 1: ");
        printData(arrList1);
        System.out.print("Size: ");
        System.out.println(arrList1.size());
        System.out.print("Is Empty?: ");
        System.out.println(arrList1.isEmpty());
        System.out.println();
        System.out.print("ArrayList 2: ");
        printData(arrList2);
        System.out.print("Size: ");
        System.out.println(arrList2.size());
        System.out.print("Is Empty?: ");
        System.out.println(arrList2.isEmpty());
        System.out.println();
        System.out.print("HashSet 1: ");
        printData(hashSet1);
        System.out.print("Size: ");
        System.out.println(hashSet1.size());
        System.out.print("Is Empty?: ");
        System.out.println(hashSet1.isEmpty());
        System.out.println();
        System.out.print("HashSet 2: ");
        printData(hashSet2);
        System.out.print("Size: ");
        System.out.println(hashSet2.size());
        System.out.print("Is Empty?: ");
        System.out.println(hashSet2.isEmpty());
        System.out.println();
        System.out.print("LinkedList 1: ");
        printData(linkedList1);
        System.out.print("Size: ");
        System.out.println(linkedList1.size());
        System.out.print("Is Empty?: ");
        System.out.println(linkedList1.isEmpty());
        System.out.println();
        System.out.print("LinkedList 2: ");
        printData(linkedList2);
        System.out.print("Size: ");
        System.out.println(linkedList2.size());
        System.out.print("Is Empty?: ");
        System.out.println(linkedList2.isEmpty());
        System.out.println();

        System.out.println("/*************TRYING ITERATOR REMOVE ON QUEUES*****************/");
        Iterator<Integer> iter = linkedList1.iterator();
        iter.next();
        try {
            iter.remove();
        } catch (ClassFormatError e) {
            e.printStackTrace();
        }
        System.out.println();
        System.out.println("/************* ARRAY LIST AND LINKEDLIST HAS RANDOM ACCESS *****************/");
        System.out.print("4. Index Of ArrayList1 :");
        System.out.println(arrList1.get(4));
        System.out.print("2. Index Of LinkedList1 :");
        System.out.println(linkedList1.get(2));
        System.out.println();
    }
}
/**
 * Created by Zain on 12/13/16.
 */

import java.util.ArrayList;

public class GenericStack<E> {

    ArrayList<E> list = new ArrayList<E>();

    public int getSize() {
        return list.size();
    }

    public E peek() {
        return list.get( getSize() - 1 );
    }

    public E pop() {
        E e = list.get( getSize() - 1 );
        list.remove( getSize() - 1 );
        return e;
    }

    public void push( E object ) {
        list.add( object );
    }

    public boolean isEmpty() {
        return list.isEmpty();
    }

}

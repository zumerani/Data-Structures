public class LinkedList<E> {

    private class Node<E> {
        E data;
        Node<E> next;

        /* Constructor */
        public Node( E e ) {
            this.data = e;
        }
    }

    private Node<E> head = null;
    private Node<E> tail = null;

    /* Constructor */
    public LinkedList(E e) {
        Node<E> temp = new Node<E>(e);
        temp.next = null;
        this.head = temp;
        this.tail = temp;
    }

    /* Main Methods */
    public void addFirst(E e) {
        Node<E> temp = new Node<E>(e);
        temp.next = head;
        this.head = temp;
    }

    public void addLast(E e) {
        Node<E> temp = new Node<E>(e);
        temp.next = null;
        this.tail.next = temp;
        this.tail = temp;
    }

    public E getFirst() {
        if( this.head == null ) {
            return null;
        }

        return this.head.data;

    }

    public E getLast() {
        if( this.tail == null ) {
            return null;
        }

        return this.tail.data;

    }

    public void removeFirst() {

        if( this.head == null ) return;

        /*Only one node */
        if( this.head == this.tail ) {
            this.head = null;
            this.tail = null;
            return;
        }

        this.head = this.head.next;
        if( this.head == null ) this.tail = null;

    }

    public void removeLast() {

        if( this.head == null ) return;

        Node<E> curr = this.head;
        /* Only one node */
        if( this.head == this.tail ) {
            this.head = null;
            this.tail = null;
            return;
        }

        while( curr.next != this.tail ) {
            curr = curr.next;
        }

        /* 'curr' now is second to last node */
        curr.next = null;
        this.tail = curr;

    }

    public static void main( String[] args ) {
        /* Filled Later */
    }

}
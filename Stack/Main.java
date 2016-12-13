public class Main {

    public static void main( String[] args ) {

        GenericStack<Integer> s1 = new GenericStack<Integer>();

        s1.push(5);
        s1.push(4);

        System.out.println( s1.peek() );

    }

}
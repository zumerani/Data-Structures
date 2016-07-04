/*

 This is the implementation for a maxheap using a vector (STL).
 
 */

#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <algorithm>

using namespace std;

template <class Data>
class Heap {
    
    public:
        //No need for constructor or destructor
        
        //Member Functions
        void push( Data x ); // O(log(n))
        Data pop(); // O(log(n))
        Data maxChild( int i ); // O(1)
    
        //const member functions
        size_t getSize() const; // O(1)
        Data front() const; // O(1)
        bool isEmpty() const; // O(1)
        bool isLeaf( int i ); // O(1)
        void print( int i );
    
    private:
        int p( int i ) {
            return ( i - 1 )/2;
        }
        
        int l( int i ) {
            return ( 2*i + 1 );
        }
        
        int r( int i ) {
            return( 2*i + 2 );
        }
        
        vector<Data> data;
};


/* --------- Heap Implementation --------- */


//Member Functions

template <class Data>
void Heap<Data>::push( Data x ) {
    
    this->data.push_back( x );
    size_t i = this->data.size() - 1;
    
    while( i > 0 && data[i] > data[ p(i) ] ) {
        swap( data[i]  , data[ p(i) ] );
        i = p(i);
    }
    
}

template <class Data>
Data Heap<Data>::pop() {
    
    if( isEmpty() )
        return 0;
    
    
    Data temp = data[0];
    data[0] = data[ data.size() - 1 ];
    
    data.pop_back();
    
    int i = 0;
    
    while( !isLeaf(i) && ( data[i] < data[ maxChild(i) ] ) ) {
        swap( data[i] , data[ maxChild(i) ] );
        i = maxChild(i);
    }
    
    return temp;
    
}

//Constant Member Functions

template <class Data>
size_t Heap<Data>::getSize() const {
    return this->data.size();
}

template <class Data>
Data Heap<Data>::front() const {
    return this->data[0];
}

template <class Data>
bool Heap<Data>::isEmpty() const {
    
    if( this->data.size() == 0 )
        return true;
    
    return false;
    
}

template <class Data>
bool Heap<Data>::isLeaf( int i ) {
    
    if( l(i) > ( this->data.size() - 1 ) )
        return true;
    
    return false;
    
}

template <class Data>
Data Heap<Data>::maxChild( int i ) {
    
    int left = l(i);
    int right = r(i);
    
    if( ( left == (this->data.size() ) ) || ( this->data[left] > this->data[right] ) )
        return left;
    
    return right;
    
}

template <class Data>
void Heap<Data>::print(int i){
    if (this->data.empty())
        cout << "No nodes." << endl;
    else {
        size_t N = this->data.size();
        if (2 * i + 2 < N)
            print(2 * i + 2);
        int depth = floor(log(i + 1) / log(2.0));
        std::cout << std::setw(depth * 4) << "";
        std::cout << this->data[i];
        std::cout << std::endl;
        if (2 * i + 1 < N){
            print(2 * i + 1);
        }
    }
}



int main(int argc, const char * argv[]) {
    
    cout << "OUTPUT FOR CHAPTER 11, PROJECT FIVE: " << endl << endl;
    
    Heap<int> h1;
    
    h1.push(13);
    h1.push(2);
    h1.push(9);
    h1.push(11);
    h1.push(1);
    h1.push(10);

    cout << "Tree looks like this: " << endl << endl;
    
    h1.print(0);
    
    /*h1.pop();
    
    cout << endl;
    
    cout << "Pop the 1: " << endl << endl;
    
    h1.print(0);
    
    cout << endl;
    
    cout << "The root node is: " << h1.front() << endl;
    
    cout << endl<< "Inserting 0: " << endl << endl;
    
    h1.push(0);
    
    h1.print(0);*/
   
    
}






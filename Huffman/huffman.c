#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#include "tree.h"
#include "pack.h"


#define p(x) (((x)-1)/2) //returns parent location
#define l(x) ((x)*2 +1) // returns address of left child in heap
#define r(x) ((x)*2 +2) //returns right child in heap

struct tree* heap[257]; //the heap
struct tree* leaves[257]; //contains child pointers
int count[257];//an array that holds the frequency of each letter
int heapCount = 0; //heapCount is directly related to the index of the last item


//The function has a complexity of O(n)
void insert(struct tree *np) { //inserts into min heap! -- this function works
    struct tree *temp = NULL; //temp to swap with parent if child is smaller in value (min heap)
    int pos = heapCount++;
    heap[pos] = np;
    while(pos != 0 && getData(np) < getData(heap[p(pos)])) { //checks that the data entered is less than heap (if it is then swap)
        //swaps
        temp = heap[pos];
        heap[pos] = heap[ p(pos) ];
        heap[ p(pos) ] = temp;
        pos = p(pos);
    }
} // --done

//The function has a time complextiy of O(n)
//this function finds the min in the min heap sequentially
struct tree *delete(void) {
    struct tree *min = heap[0]; 
    int pos = 0;
    struct tree *np = heap[heapCount-1];
    
    while(l(pos) < heapCount) { //loop while left child is less than the heap count
        int child = l(pos);//assumes that left child is min
        if(r(pos) < heapCount && getData(heap[l(pos)]) > getData(heap[r(pos)])) //checks if right child is less than left (if it is, then swap)
            child = r(pos);
        if(getData(np) > getData(heap[child])) { //you need to also check that the last element in the heap is larger than the child position
            heap[pos] = heap[child]; 
            pos = child;
        }
        else
            break;
    }
    
    heap[pos] = np;
    heapCount--;
    return min;

} //--done

//The function has a time complexity of O(height) -- where height is the height of the tree
//this function uses recursion to print 1 or 0 -- depending whether we're on the left or right branch
void printBinary(struct tree *np) {
    if(getParent(np) == NULL) { //base case check
        return;
	}
    printBinary(getParent(np)); //call the function recursively to get the parent of the tree passed in
    struct tree *parent = getParent(np); //get the parent of the tree passed in
    
    //check whether we are on the left or right branch and print accordingly
    if(np == getLeft(parent)) {
        printf("0");
    } else {
        printf("1");
	}

} //--done

//this is my function that I used for debugging
void printTree() {

    int i;
    for(i = 0 ; i < heapCount ; i++ ) {
        printf("value is %d\n" , getData(heap[i]));
    }

}

//this is my function that I used for debugging
void printHeap( struct tree *np) {
    if( np == NULL ) {
        return;
    }
    printf("value is %d\n" , getData(np));
    printHeap( getLeft(np) );
    printHeap( getRight(np) );


}

//this is the function I used for debugging
void printLeaves() {
    int i;
    for( i = 0 ; i < 257 ; i++ ) {
        if( leaves[i] != NULL ) {
            printf("leaf here is %d\n" , getData(leaves[i]));
        }
    }
}
           
int main(int argc, char *argv[]) {
    if(argc != 3) {
		printf("Error! Failed to execute program.\n");
		exit(255);
	}
    
    FILE *fp = fopen(argv[1],"rb");
    
	if(!fp){
		printf("Could not open file.\n");
		return -1;
	}
    
    //loop to set the count elements to 0 and the leaves and heap spots to NULL, before we begin
    for(int i = 0; i < 257; i++) {
        count[i] = 0;
        heap[i] = NULL;
        leaves[i] = NULL;
    }
    
    int c;
    while((c=getc(fp)) != EOF) { //grab each character and increase the frequency count where appropriate in the array
        count[c]++;
    }
    
    fclose(fp);
    
    //loops through count and if the element is greater than 0, then we create a tree in the appropriate spot in 'leaves' and insert that tree into the heap (heapCount position)
    for(int i = 0; i < 257; i++) {
        if(count[i] > 0) {
            leaves[i] = createTree(count[i],NULL,NULL); //create a leaf
            assert(leaves[i] != NULL); //ensure leaf is not null
            insert(leaves[i]); //insert into heap
        }
    }


 
    //create tree for EOF and insert into heap
    leaves[256] = createTree(0, NULL, NULL);
    count[256] = 0;
    insert(leaves[256]);
    
    //this loop has a time complexity of O(heapCount)
    //the loop checks until heapCount is 1 and if it isn't, it takes out two of the smallest element in the heap and combines
    //those values to create a new tree. Once created, that tree is entered into the heap/   
    while(heapCount > 1) { //you need to check the condition
        struct tree *left = delete(); //remove first min
        struct tree *right = delete(); //remove second min
        int combo  = getData(left) + getData(right); //add the data up
        struct tree *combinationTree = createTree( combo , left , right ); //enter the new tree into heap ... this means that at the end -- heap[0] is your huffman tree!
        
        insert(combinationTree);
    }

    
    //the loop goes through 'leaves' and if the spot isn't NULL, prints out the encoding for each character
    for(int i = 0; i < 257; i++) {
        if(leaves[i] != NULL) { //ensure that we are not at a NULL spot
            if(isprint(i)) { //check if we can print using 'isprint()'
                printf("'%c': %d ",i,getData(leaves[i])); //print frequency 
                printBinary(leaves[i]); //print encoding 
                printf("\n");
            } else {
                printf("%.3o: %d ",i,getData(leaves[i])); //print frequency 
                printBinary(leaves[i]); //print encoding
                printf("\n");
            }
        }
    }
    
    pack(argv[1],argv[2], leaves); //pack using the pack.h header

    //freeing goes here
    int counter;
    //loop through leaves and destroy each tree	
    for( counter = 0 ; counter < 257 ; counter++ ) {
        if( count[counter] != 0 ) {
            destroyTree(leaves[counter]); //destroy tree
        }
    }

    destroyTree(leaves[256]); //destroy EOF 

    return 0;
}





#include <stdio.h>
#include <stdlib.h>
#define INPUT_FILE_NAME "pa4_data.txt"

// COP 3502C Spring 2025
// Student Name: TODO_your_name_here
// File Name: pa4_yoursurname.c
// Note: Rename to use your actual surname. File name should be in lowercase.
// You must remove any whitespaces or dashes from your surname.
// Note: **do not** modify or remove TODO comments


// DO NOT MODIFY THIS PORTION
// function prototypes defined here
unsigned long get_the_element(unsigned long *, unsigned long);

// DO NOT MODIFY THIS PORTION OF THE MAIN FUNCTION
int main(void) {
    FILE *input_file = fopen(INPUT_FILE_NAME, "r");

    // check if the file was opened
    if(input_file == NULL) {
        // if there was a problem, simply return a 1
        printf("There was a problem opening the file. Abort!\n");
        return 1;
    }

    // the first line of the input file indicates
    // how many numbers to read from the file
    // you can assume that this will be an odd
    // number; note that this can be a very big
    // number to represent a very big list
    unsigned long count;
    fscanf(input_file, "%lu", &count);

    // dynamically allocate this array of this size
    unsigned long *list = malloc(sizeof(unsigned long) * count);

    unsigned long i = 0;
    // read the remaining numbers and
    // store them in the array
    unsigned long num;
    while( fscanf(input_file, "%lu", &num) != EOF ) {
        list[i++] = num;
    }

    // close the file
    fclose(input_file);

    // output the element we are looking for
    printf("%lu\n", get_the_element(list, count));


    return 0;
}
// DO NOT MODIFY THIS PORTION OF THE MAIN FUNCTION

// define BSTNode and Tree structures
typedef struct BSTNode_s {
    int data;
    struct BSTNode_s *left;
    struct BSTNode_s *right;
} BSTNode;

typedef struct BSTree_s {
    BSTNode *root;
} BSTree;

BSTNode* createNode(unsigned long value){
    //malloc node
    BSTNode *newNode = malloc(sizeof(BSTNode));

    //set the data and left/right values of the new Node;
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

BSTNode* insertNode(BSTNode *root, unsigned long value){

    //base case if tree is empty (root == NULL)
    if(root == NULL){
        return createNode(value); //will be the node inserted
    }

    //tree isnt empty
    if(value <= root->data){ // if value is less than or equal go left on the binary tree
        root->left = insertNode(root->left, value); //call insert node again new root = left
    }
    else if(value > root->data){ // greater than go right
        root->right = insertNode(root->right, value); 
    }

    return root; //working way back up binary tree returning correct roots 
}

void inorderTraversal(BSTNode *root, unsigned long *arr, int* index){

    // base case reached end of tree or tree is empty
    if (root != NULL) {

        // traverse LVR left first to get smallest nodes
        inorderTraversal(root->left, arr, index);

        // store nodes value in array at current index
        arr[*index] = root->data;
        (*index)++; // update index ++

        // R of inorder LVR trvaerse right to get larger nodes after smaller
        inorderTraversal(root->right, arr, index);
    }
}

void freeTree(BSTNode *root){
    //if there node exists / havent reach off of the end of the tree
    if(root != NULL){
        //traverse left and right until end if reached
        freeTree(root->left);
        freeTree(root->right);

        //free the node back up the recurisve calls
        free(root);
    }
}

unsigned long get_the_element(unsigned long *arr, unsigned long size) {
    // TODO START
    // TODO: Return the ((n+1)/2)-th highest element
    // of an odd-length list. Assume that all the numbers
    // in the list are distinct.

    //malloc and intialize tree
    BSTree *tree = malloc(sizeof(BSTree));
    tree->root = NULL;
    
    // for each element in array
    for(int i = 0; i < size; i++){
        tree->root = insertNode(tree->root, arr[i]); //insert each element into the tree;
    }

    // new array consisting of sorted values
    unsigned long *sortedArr = malloc(sizeof(unsigned long) * size);
    int index = 0;

    // populate array with sorted valye by preforming in order binary tree traversal
    inorderTraversal(tree->root, sortedArr, &index);

    //save middle element in array and free sorted and tree
    int midElement = sortedArr[size / 2];
    free(sortedArr);
    freeTree(tree->root);
    free(tree);
    
    return midElement; //return the middle index of the sorted array
    // TODO END
}


// You may define other helper functions if you want

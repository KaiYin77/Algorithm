//
//  RBT.cpp
//  C++ code
//


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using std::string;
using std::cout;
using std::endl;

class RBT;

class Rect{
    private:
        int lowX, lowY, hiX, hiY;

    public:
        Rect(): lowX(0), lowY(0), hiX(0), hiY(0){}
        Rect(int x1, int y1, int x2, int y2): lowX(x1), lowY(y1), hiX(x2), hiY(y2){}

        int GetLowX() const{return lowX;};
        int GetLowY() const{return lowY;};
        int GetHiX() const{return hiX;};
        int GetHiY() const{return hiY;};


};

class TreeNode{
    private:
        TreeNode *leftchild;
        TreeNode *rightchild;
        TreeNode *parent;
        std::string element;
        int key;
        int color;		// for color: 0: Red, 1: Black
        friend class RBT;

    public:
        TreeNode():leftchild(0), rightchild(0), parent(0), key(0), element(""), color(0){}
        TreeNode(int key, string str = ""):leftchild(0), rightchild(0), parent(0), key(key), element(str), color(0){}

        int GetKey() const{return key;};
        string GetElement() const{return element;};


};


class RBT{
    private:
        TreeNode *root;
        TreeNode *neel;


        void LeftRotation(TreeNode *x);
        void RightRotation(TreeNode *x);
        void InsertFixedUpRBT(TreeNode *current);
        void DeleteFixedUpRBT(TreeNode *current);
        TreeNode* Successor(TreeNode *current);	// called bt DeleteRBT()
        TreeNode* Leftmost(TreeNode *current);	// called by Succesor


    public:
        RBT(){
            neel = new TreeNode;
            neel->color = 1;
            root = neel;
            root->parent = neel;
        };

        void InsertRBT(int key, string str);
        void DeleteRBT(int KEY);
        TreeNode* Search(int KEY);


};


/**
 *  Rotation operation
 *
 *  Maintain RBT structure
 *
 *  @param TreeNode *x
 *  @return
 */

void RBT::LeftRotation(TreeNode *x){
  
    TreeNode *y = x->rightchild;

    x->rightchild = y->leftchild;

    if (y->leftchild != neel){
        y->leftchild->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == neel){		//if x was root, then y is new root
        root = y;
    }
    else if (x == x->parent->leftchild){
        x->parent->leftchild = y;
    }
    else {
        x->parent->rightchild = y;
    }
    y->leftchild = x;
    x->parent = y;
}

void RBT::RightRotation(TreeNode *y){
  
    TreeNode *x = y->leftchild;

    y->leftchild = x->rightchild;

    if (x->rightchild != neel){
        x->rightchild->parent = y;
    }

    x->parent = y->parent;

    if (y->parent == neel){		//if x was root, then y is new root
        root = x;
    }
    else if (y == y->parent->leftchild){
        y->parent->leftchild = x;
    }
    else {
        y->parent->rightchild = x;
    }
    x->rightchild = y;
    y->parent = x;
}

TreeNode* RBT::Leftmost(TreeNode *current){
    
    while (current->leftchild != NULL){
        current = current->leftchild;
    }
    return current;
}
TreeNode* RBT::Successor(TreeNode *current){
    
    if (current->rightchild != NULL){
        return Leftmost(current->rightchild);
    }
    
    TreeNode *new_node = current->parent;
    
    while (new_node != NULL && current == new_node->rightchild) {
        current = new_node;
        new_node = new_node->parent;
    }
    
    return new_node;
}
TreeNode* RBT::Search(int KEY){

    TreeNode *current = root;               
         
    while (current != NULL && KEY != current->key) {  
    	                                              
        if (KEY < current->key){                      
            current = current->leftchild;   
        }
        else {
            current = current->rightchild;  
        }
    }
    return current;
}

/**
 *  InsertRBT
 *
 *  Insert new (key, value) into dictionary implemented by RBT structure
 *
 *  @param key, value
 *  @return
 */

void RBT::InsertFixedUpRBT(TreeNode *current){

    // case0: parent is Black? return: go to while loop to fix
    while (current->parent->color == 0) {
        
        // UPPER-Part: parent is the grandparent's left child
        if (current->parent == current->parent->parent->leftchild) {
        TreeNode *uncle = current->parent->parent->rightchild;

        // case1: uncle is red
        if (uncle->color == 0) {
            current->parent->color = 1;
        uncle->color = 1;
        current->parent->parent->color = 0;
        current = current->parent->parent;
        }
        // case2 & 3: uncle is black
        else {
        // transform case2 to case3
            if (current == current->parent->rightchild) {
        current = current->parent;
        LeftRotation(current);
        }
        // case3
        current->parent->color = 1;
        current->parent->parent->color = 0;
        RightRotation(current->parent->parent);
        }
        }
        // LOWER-Part: parent is the grandparent's right chlid
        else {
        TreeNode *uncle = current->parent->parent->leftchild;
        // case1: uncle is red
        if (uncle->color == 0) {
            current->parent->color = 1;
        uncle->color = 1;
        current->parent->parent->color = 0;
        current = current->parent->parent;
        }
        // case2 & 3: uncle is black;
        else {
        // transform case2 to case3
            if (current == current->parent->leftchild) {
        current = current->parent;
        RightRotation(current);
        }
        // case3
        current->parent->color = 1;
        current->parent->parent->color = 0;
        LeftRotation(current->parent->parent);
        }
        }
    }

    root->color = 1;

}
void RBT::InsertRBT(int key, string element){
  
  TreeNode *y = neel;  //準新手爸媽
  TreeNode *x = root;  //哨兵
  
  TreeNode *insert_node = new TreeNode(key, element);

  while (x!=neel){
    y = x;
    if (insert_node->key < x->key)
      x = x->leftchild;
    else
      x = x->rightchild;
  }

  insert_node->parent = y;

  if (y == neel){
    this->root = insert_node;
  }
  else if (insert_node->key < y->key){
    y->leftchild = insert_node;
  }
  else{
    y->rightchild = insert_node;
  }
  
  // customized for RBT settings
  insert_node->leftchild = neel;
  insert_node->rightchild = neel;
  insert_node->color = 0;	//Setting new insertion node's color to be red

  // Fixed the color setting
  InsertFixedUpRBT(insert_node);

}


/**
 *  DeleteRBT
 *
 *  Delete (key, value) from dictionary implemented by RBT structure
 *
 *  @param key
 *  @return
 */
void RBT::DeleteFixedUpRBT(TreeNode *current){
    // Case0:(i) current is red, then draw black directly
    //       (ii) current is root, then draw black directly

    while (current != root && current->color == 1) {
        // current is leftchild
        if (current == current->parent->leftchild) {
        TreeNode *sibling = current->parent->rightchild;

        // Case1: Sibling is red
        if (sibling->color == 0) {
            sibling->color = 1;
            current->parent->color = 0;
            LeftRotation(current->parent);
        sibling = current->parent->rightchild;
        }
        // Goto Case2,3,4 (Sibling become black)
        // Case2: Sibling's both child is black
        if (sibling->leftchild->color == 1 && sibling->rightchild->color == 1 ){
            sibling->color = 0;
        current = current->parent;
        }
        // Case3 & 4: current has only child with Black color
        else {
            // case3 sibling's right child is black, left child is red
        if (sibling->rightchild->color == 1){
        sibling->leftchild->color = 1;
        sibling->color = 0;
        RightRotation(sibling);
        sibling = current->parent->rightchild;
        }
        // after Case3 operation, will always be case4
        // case4 sibling's right child is red, left child is black
        sibling->color = current->parent->color;
        current->parent->color = 1;
        sibling->rightchild->color = 1;
        LeftRotation(current->parent);
        current = root;
        }
        }
        // current is rightchild
        else {
        TreeNode *sibling = current->parent->leftchild;
        
        // Case1: Sibling is red
        if (sibling->color == 0) {
            sibling->color = 1;
            current->parent->color = 0;
            RightRotation(current->parent);
        sibling = current->parent->leftchild;
        }
        // Goto Case2,3,4
        // Case2: Sibling's both child is black
        if (sibling->leftchild->color == 1 && sibling->rightchild->color == 1 ){
            sibling->color = 0;
        current = current->parent;
        }
        // Case3 & 4: current has only child with Black color
        else {
            // case3 sibling's left child is black, right child is red
        if (sibling->leftchild->color == 1){
        sibling->rightchild->color = 1;
        sibling->color = 0;
        LeftRotation(sibling);
        sibling = current->parent->leftchild;
        }
        // after Case3 operation, will always be case4
        // case4 sibling's left child is red, right child is black
        sibling->color = current->parent->color;
        current->parent->color = 1;
        sibling->leftchild->color = 1;
        RightRotation(current->parent);
        current = root;
        }
        }
    }

    current->color = 1;


}

void RBT::DeleteRBT(int KEY) {
  
    TreeNode *delete_node = Search(KEY);

    if (delete_node == NULL) {
        std::cout << "data not found.\n";
        return; 
    } 

    TreeNode *y = 0; 	//The Node Ready to be deleted
    TreeNode *x = 0; 	//The Node's child
    
    // Modified the delete_node to own at most 1 child
    if (delete_node->leftchild == neel || delete_node->rightchild == neel) {
        y = delete_node;
    }
    else {
        y = Successor(delete_node);
    }

    if (y->leftchild != neel){
        x = y->leftchild;
    }
    else {
        x = y->rightchild;
    }

    if (x != neel) {
        x->parent = y->parent;
    }
    
    if (y->parent == neel) {
        this->root = x;
    }
    else if (y == y->parent->leftchild){
        y->parent->leftchild = x;
    }
    else {
        y->parent->rightchild = x;
    }
    
    // case3 刪掉替身
    if (y != delete_node){
        delete_node->key = y->key;
        delete_node->element = y->element;
    }
    
    if (y->color == 1){
        DeleteFixedUpRBT(x);
    } 
}



int main(int argc, char**argv) {
    // Setting Usage
    if ( argc < 3 || argc > 3 ){
        std::cout << "Warning!!" << std::endl;
        std::cout << "[Usage]: ./Lab1 input.txt output.txt" << std::endl;
        return 1;
    }
    else if ( argc == 3 ){
        std::cout << "Parsing input.txt ..." << std::endl;
    }
    
    // Input Output file
    std::ifstream inputFile;
    inputFile.open(std::string(argv[1]));
    std::ofstream outputFile;
    outputFile.open(std::string(argv[2]));

    // Building Interval Tree
    //RBT intervalTree;

    std::string line;
    while ( std::getline(inputFile, line) ){
        std::stringstream buffer(line);
        std::string operation;
        buffer >> operation;
        
        if (operation == "I"){
            std::string idx;
            int lowX, lowY, highX, highY;
            buffer >> idx >> lowX >> lowY >> highX >> highY;
            
        }
        else if (operation == "D"){
            int lowX, lowY, highX, highY;
            buffer >> lowX >> lowY >> highX >> highY;
            
            
        }
        else if (operation == "O"){
            int lowX, lowY, highX, highY;
            buffer >> lowX >> lowY >> highX >> highY;
           
            outputFile << "O" << std::endl;
        }
        else if (operation == "S"){
            int lowX, lowY, highX, highY;
            buffer >> lowX >> lowY >> highX >> highY;
            
            outputFile << "S" << std::endl;
        }
        else if (operation == "A"){
            int lowX, lowY;
            buffer >> lowX >> lowY;
            
            outputFile << "A" << std::endl;
        }
        
        
    }
    
    outputFile.close();
    return 0;
}
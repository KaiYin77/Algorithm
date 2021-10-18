//
// BST.cpp
// C++ code
//

#include <iostream>
#include <string>
#include <queue>

using std::string;
using std::cout;
using std::endl;

class BST;
class TreeNode{
private:
  TreeNode *leftchild;
  TreeNode *rightchild;
  TreeNode *parent;
  int key;
  string element;
public:
  TreeNode():leftchild(0), rightchild(0), parent(0), key(0), element(""){};
  TreeNode(int a, string b):leftchild(0), rightchild(0), parent(0), key(a), element(b){};

  int GetKey(){return key;}
  string GetElement(){return element;}
  
  //BST can access TreeNode private data
  friend class BST;

};

class BST{
private:
  TreeNode *root;
  TreeNode *Leftmost(TreeNode *current);
  TreeNode *Successor(TreeNode *current);
  TreeNode *Rightmost(TreeNode *current);
  TreeNode *Predecessor(TreeNode *current);
public:
  BST():root(0){};

  TreeNode* Search(int key);
  void InsertBST(int key, string element);
  void InorderPrint();
  void Levelorder();
  void DeleteBST(int key);

};

TreeNode* BST::Search(int KEY){
  
  TreeNode *current = root;

  while(current != NULL && KEY != current->key){
    if (KEY < current->key){
      current = current->leftchild;
    }
    else {
      current = current->rightchild;
    } 
  }
  return current;

}

void BST::InsertBST(int key, string element){
  
  TreeNode *y = 0;  //準新手爸媽
  TreeNode *x = 0;  //哨兵
  
  TreeNode *insert_node = new TreeNode(key, element);

  x = root;
  while (x!=NULL){
    y = x;
    if (insert_node->key < x->key)
      x = x->leftchild;
    else
      x = x->rightchild;
  }

  insert_node->parent = y;
  if(y==NULL){
    this->root = insert_node;
  }
  else if (insert_node->key < y->key){
    y->leftchild = insert_node;
  }
  else{
    y->rightchild = insert_node;
  }

}

TreeNode* BST::Rightmost(TreeNode *current){
  
  while(current->leftchild != NULL){
    current = current->rightchild;
  }
  return current;
}

TreeNode* BST::Leftmost(TreeNode *current){
  
  while(current->leftchild != NULL){
    current = current->leftchild;
  }
  return current;
}

TreeNode* BST::Successor(TreeNode *current){
 
  if(current->rightchild!=NULL){
    return Leftmost(current->rightchild);
  }

  TreeNode *successor = current->parent;
  
  //Two-pointers
  while (successor != NULL && current == successor->rightchild) {
    current = successor;
    successor = successor->parent;
  }

  return successor;
}


TreeNode* BST::Predecessor(TreeNode *current){
 
  if(current->leftchild!=NULL){
    return Rightmost(current->leftchild);
  }

  TreeNode *predecessor = current->parent;
  
  //Two-pointers
  while (predecessor != NULL && current == predecessor->leftchild) {
    current = predecessor; 
    predecessor = predecessor->parent;
  }

  return predecessor;
}

void BST::InorderPrint(){
  TreeNode *current = new TreeNode;
  current = Leftmost(root);
  while(current){
    cout << current->element << "(" << current->key << ")" << " ";
    current = Successor(current); 
  }
}

void BST::Levelorder(){
  std::queue<TreeNode*> q;
  q.push(this->root);

  while (!q.empty()){
  
    TreeNode *current = q.front();
    q.pop();
    cout << current->element << "(" << current->key << ")" << " ";

    if (current->leftchild != NULL)
      q.push(current->leftchild);
    if (current->rightchild != NULL)
      q.push(current->rightchild);
  }
}

void BST::DeleteBST(int KEY) {
  
  TreeNode *delete_node = Search(KEY);

  if (delete_node == NULL) {
    std::cout << "data not found.\n";
    return; 
  } 

  TreeNode *y = 0; 	//The Node Ready to be deleted
  TreeNode *x = 0; 	//The Node's child

  if (delete_node->leftchild == NULL || delete_node->rightchild == NULL) {
    y = delete_node;
  }
  else {
    y = Successor(delete_node);
  }

  if (y->leftchild != NULL){
    x = y->leftchild;
  }
  else {
    x = y->rightchild;
  }

  if (x != NULL) {
    x->parent = y->parent;
  }
  
  if (y->parent == NULL) {
    this->root = x;
  }
  else if (y == y->parent->leftchild){
    y->parent->leftchild = x;
  }
  else {
    y->parent->rightchild = x;
  }

  if (y != delete_node){
    delete_node->key = y->key;
    delete_node->element = y->element;
  }
  
  delete y;
  y = 0; 
}

int main() {

  BST T;

  T.InsertBST(8, "龜神人");
  T.InsertBST(1000, "悟空");
  T.InsertBST(2, "克林");
  T.InsertBST(513, "比克");
  

  cout << "Inorder Traversal: \n";
  T.InorderPrint();
  cout << endl;
  cout << "Level-order Traversal: \n";
  T.Levelorder();
  cout << endl;
  
  T.DeleteBST(8);
  cout << "Level-order Traversal:\n";
  T.Levelorder();
  cout << endl << endl;

  TreeNode *node = T.Search(1000);
  if(node != NULL){
    cout << "There is" << node->GetElement() << "(" << node->GetKey() << ")" << endl;
  }
  else{
    cout << "no element with Key(1000)" << endl;
  }

  node = T.Search(73);
  if(node != NULL){
    cout << "There is" << node->GetElement() << "(" << node->GetKey() << ")" << endl;
  }
  else{
    cout << "no element with Key(73)" << endl;
  }

  return 0;
}

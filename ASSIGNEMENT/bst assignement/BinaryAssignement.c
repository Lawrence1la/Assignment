#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
}Node;


Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insertNode(Node* root, int data){
    if(root == NULL)
        return createNode(data);
    if(data < root->data)
        root ->left = insertNode(root->left , data);
    else if(data > root->data)
        root -> right = insertNode(root ->right ,data);
    return root ;

}


Node* minValueNode(Node* node){
    Node* current = node;
    while(current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root , int data)
{
    if(root == NULL)
        return root;
    if(data < root->data)
        root->left = deleteNode(root->left,data);
    else if(data > root->data)
        root->right = deleteNode(root->right , data);
    else{
        if(root->left == NULL){
            Node* temp = root->right;
            free(root);
            return temp;
        }else if(root->right == NULL){
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right,temp->data);
    }
    return root;
}


int height(Node* node){
    if(node == NULL)
        return -1;
    else{
        int leftHeight = height(node-> left);
        int rightHeight = height(node->right);
        return(leftHeight > rightHeight ? leftHeight : rightHeight )+1;
    }
}


int getLevelUtil(Node* node , int data ,int level){
    if(node == NULL)
        return 0;
    if (node->data == data)
        return level;
    int downLevel = getLevelUtil(node->left ,data,level+1);
    if(downLevel != 0)
        return downLevel;
    downLevel = getLevelUtil(node->right ,data,level+1);
    return downLevel;
}

int getLevel(Node* node , int data){
    return getLevelUtil(node , data , 1);
}


int main()
{
    int elements[] = {30,20,40,10,25,35,45,5,15};
    int n = sizeof(elements)/sizeof(elements[0]);
    Node* root = NULL;

    for(int i = 0;i < n; i++){
        root = insertNode(root, elements[i]);
    }

    root = deleteNode(root,20);

    printf("Height of the bst: %d\n",height(root));

    int node_data = 25;
    printf("Level of node %d: %d\n", node_data,getLevel(root,node_data));
    printf("Height of node %d: %d\n",node_data,height(root));

    return 0;
}









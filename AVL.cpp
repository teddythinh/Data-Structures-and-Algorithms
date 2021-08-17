#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
};

Node *createNode(int value)
{
    Node *p = new Node;
    p->left = p->right = NULL;
    p->key = value;
    return p;
}

void leftRotate(Node *&pRoot)
{
    Node *p = pRoot->right;
    pRoot->right = p->left;
    p->left = pRoot;
    pRoot = p;
}

void rightRotate(Node *&pRoot)
{
    Node *p = pRoot->left;
    pRoot->left = p->right;
    p->right = pRoot;
    pRoot = p;
}

int Height(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return 0;
    }
    return max(Height(pRoot->left), Height(pRoot->right)) + 1;
}

void Balance(Node *&pRoot)
{
    int bal = Height(pRoot->left) - Height(pRoot->right);
    if (bal > 1)
    {
        if (Height(pRoot->left->left) >= Height(pRoot->left->right))
        {
            rightRotate(pRoot);
        }
        //! Cay lech trai phai
        if (Height(pRoot->left->left) < Height(pRoot->left->right))
        {
            leftRotate(pRoot->left);
            rightRotate(pRoot);
        }
    }
    if (bal < -1)
    {
        if (Height(pRoot->right->right) >= Height(pRoot->right->left))
        {
            leftRotate(pRoot);
        }
        //! Cay lech phai trai
        if (Height(pRoot->right->right) < Height(pRoot->right->left))
        {
            rightRotate(pRoot->right);
            leftRotate(pRoot);
        }
    }
}

void Insert(Node *&pRoot, int value)
{
    if (pRoot == NULL)
    {
        pRoot = createNode(value);
    }

    if (pRoot->key == value)
    {
        return;
    }

    if (pRoot->key > value)
    {
        Insert(pRoot->left, value);
    }

    if (pRoot->key < value)
    {
        Insert(pRoot->right, value);
    }

    int bal = Height(pRoot->left) - Height(pRoot->right);

    //! Mat can bang trai
    if (bal > 1)
    {

        //! Mat can bang trai trai
        if (Height(pRoot->left->left) > Height(pRoot->left->right))
        {
            rightRotate(pRoot);
        }

        //! Mat can bang trai phai
        if (Height(pRoot->left->left) < Height(pRoot->left->right))
        {
            leftRotate(pRoot->left);
            rightRotate(pRoot);
        }
    }

    //! Mat can bang phai
    if (bal < -1)
    {

        //! Mat can bang phai phai
        if (Height(pRoot->right->right) > Height(pRoot->right->left))
        {
            leftRotate(pRoot);
        }

        if (Height(pRoot->right->right) < Height(pRoot->right->left))
        {
            rightRotate(pRoot->right);
            leftRotate(pRoot);
        }
    }
}

Node *createTree(int a[], int n)
{
    Node *p = NULL;
    for (int i = 0; i < n; i++)
    {
        Insert(p, a[i]);
    }
    return p;
}

void levelOrder(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return;
    }

    queue<Node *> q;
    q.push(pRoot);

    while (!q.empty())
    {
        Node *p = q.front();
        q.pop();
        if (p->left != NULL)
        {
            q.push(p->left);
        }
        if (p->right != NULL)
        {
            q.push(p->right);
        }
        cout << p->key << " ";
    }
}

// void Remove(Node* & pRoot, int x){
//     if(pRoot == NULL){
//         return;
//     }

//     if(pRoot->key > x){
//         Remove(pRoot->left, x);
//     }
//     else {
//         if(pRoot->key < x){
//             Remove(pRoot->right, x);
//         }
//         else {

//             //! Cay co 1 con
//             if(pRoot->key == x){
//                 if(pRoot->left == NULL && pRoot->right == NULL){
//                     //! Node khong co con thi phai gan bang NULL
//                     delete pRoot;
//                     pRoot = NULL;
//                 }
//                 else {

//                     //! Cay co con ben trai
//                     if(pRoot->left != NULL && pRoot->right == NULL){
//                         Node*p = pRoot->left;
//                         pRoot = pRoot->left;
//                         delete p;
//                     }
//                     else {

//                         //! Cay co con ben phai
//                         if(pRoot->left == NULL && pRoot->right == NULL){
//                             Node* p = pRoot->right;
//                             pRoot = pRoot->right;
//                             delete p;
//                         }
//                         else {
//                             if(pRoot->left == NULL && pRoot->right == NULL){
//                                 Node* p = pRoot->right;
//                                 while(p->left != NULL){
//                                     p = p->left;
//                                 }
//                                 pRoot->key = p->key;
//                                 Remove(pRoot->right, pRoot->key);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
//     }
//     if(pRoot == NULL){
//         return;
//     }
//     Balance(pRoot);
// }

// void Remove(Node*& pRoot, int x)
// {
//     if (pRoot == NULL) return;
//     else if (pRoot->key > x) Remove(pRoot->left, x);
//     else if (pRoot->key < x) Remove(pRoot->right, x);
//     else if (pRoot->key == x)
//     {
//         if (pRoot->left == NULL && pRoot->right == NULL)
//         {
//             Node* p = pRoot;
//             pRoot = NULL;
//             delete p;
//             return;
//         }
//         else if (pRoot->left != NULL && pRoot->right == NULL)
//         {
//             Node* p = pRoot;
//             pRoot = pRoot->left;
//             delete p;
//         }
//         else if (pRoot->right != NULL && pRoot->left == NULL)
//         {
//             Node* p = pRoot;
//             pRoot = pRoot->right;
//             delete p;
//         }
//         else if (pRoot->left != NULL && pRoot->right != NULL)
//         {
//             Node* q = pRoot->right;
//             while (q->left != NULL)
//             {
//                 q = q->left;
//             }
//             pRoot->key = q->key;
//             Remove(pRoot->right, pRoot->key);
//         }
//     }
//     if (pRoot == NULL) return;
//     Balance(pRoot);
// }

void Remove(Node* &pRoot, int x)
{
    if(pRoot == NULL) return;
    if(pRoot->key > x)
        Remove(pRoot->left,x);
    else if(pRoot->key < x)
        Remove(pRoot->right,x);
    else if(pRoot->key == x){
        if(pRoot->left == NULL && pRoot->right == NULL){
            //Giả sử node 0 có con
            delete pRoot;
            pRoot = NULL;
        }
        else if(pRoot->left != NULL && pRoot->right == NULL){
            Node* p = pRoot;
            pRoot = pRoot->left;
            delete p;
        }
        else if(pRoot->left == NULL && pRoot->right != NULL){
            Node* p = pRoot;
            pRoot = pRoot->right;
            delete p;
        }
        else if(pRoot->left != NULL && pRoot->right != NULL){
            Node* p = pRoot->right;
            while(p->left != NULL){
                p = p->left;
            }
            pRoot->key = p->key;
            Remove(pRoot->right, pRoot->key);
        }
    }
    if(pRoot == NULL) return;
    Balance(pRoot);
}

int minNode(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return 1000000;
    }
    return min(min(minNode(pRoot->left), minNode(pRoot->right)), pRoot->key);
}

int maxNode(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return -1000000;
    }
    return max(max(maxNode(pRoot->left), maxNode(pRoot->right)), pRoot->key);
}

bool isBST(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return true;
    }
    if (pRoot->key < minNode(pRoot->right) && pRoot->key > maxNode(pRoot->left))
    {
        return isBST(pRoot->left) && isBST(pRoot->right);
    }
    return false;
}

bool isAVL(Node *pRoot)
{
    if (pRoot == NULL)
    {
        return true;
    }
    int bal = Height(pRoot->left) - Height(pRoot->right);
    return (bal > -2) && (bal < 2) && isBST(pRoot) && isAVL(pRoot->left) && isAVL(pRoot->right);
}
int main()
{
    int a[7] = {12, 8, 18, 5, 11, 17, 4};
    Node *pRoot = createTree(a, 7);
    levelOrder(pRoot);
    cout << "\n";
    Remove(pRoot, 12);
    levelOrder(pRoot);
    cout << "\n";
    if(isAVL(pRoot)){
        cout << "yes" << endl;
    }
    else {
        cout << "no" << endl;
    }
    cout << "The height is: " << Height(pRoot);
}
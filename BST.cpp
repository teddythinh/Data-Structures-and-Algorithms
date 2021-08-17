#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct Node
{
    int key;
    Node* pLeft;
    Node* pRight;
};

Node* createNode(int data){
    Node* p = new Node;
    p->key = data;
    p->pLeft = p->pRight = NULL;
    return p;
}

void Insert(Node*& pRoot, int x){
    if (pRoot == NULL){
        pRoot = createNode(x);
        return;
    }
    if(pRoot->key > x){
        Insert(pRoot->pLeft, x);
    }
    if(pRoot->key < x){
        Insert(pRoot->pRight, x);
    }
}

//! Pre-order
void NLR(Node* pRoot){
    if(pRoot == NULL){
        return;
    }
    cout << pRoot->key << " ";
    NLR(pRoot->pLeft);
    NLR(pRoot->pRight);
}

//! In-order
void LNR(Node* pRoot){
    if(pRoot == NULL){
        return;
    }
    LNR(pRoot->pLeft);
    cout << pRoot->key << " ";
    LNR(pRoot->pRight);
}

//! Post-order
void LRN(Node* pRoot){
    if(pRoot == NULL){
        return;
    }
    LRN(pRoot->pLeft);
    LRN(pRoot->pRight);
    cout << pRoot->key << " ";
}

void levelOrder(Node* pRoot){
    if(pRoot == NULL){
        return;
    }
    queue <Node*> q; // ! Queue kieu Node*
    q.push(pRoot);
    while(!q.empty()){
        Node* temp = q.front();
        q.pop();
        if(temp->pLeft != NULL){
            q.push(temp->pLeft);
        }
        if(temp->pRight != NULL){
            q.push(temp->pRight);
        }
        cout << temp->key << " ";
    }
}

int height(Node* pRoot){
    if(pRoot == NULL){
        return 0;
    }
    return max(height(pRoot->pLeft), height(pRoot->pRight)) + 1;
}

int countNode(Node* pRoot){
    if(pRoot == NULL){
        return 0;
    }
    return countNode(pRoot->pLeft) + countNode(pRoot->pRight) + 1;
}

int sumNode(Node* pRoot){
    if(pRoot == NULL){
        return 0;
    }
    return sumNode(pRoot->pLeft) + sumNode(pRoot) + pRoot->key;
}

Node* Search(Node* pRoot, int x){
    if(pRoot == NULL || pRoot->key == x){
        return pRoot;
    }
    if(pRoot->key < x){
        Search(pRoot->pRight, x);
    }
    if(pRoot->key > x){
        Search(pRoot->pLeft, x);
    }
}

void Remove(Node*& pRoot, int x){
    if(pRoot == NULL){
        return;
    }
    if(pRoot->key > x){
        Remove(pRoot->pLeft, x);
    }
    if(pRoot->key < x){
        Remove(pRoot->pRight, x);
    }
    if(pRoot->key == x){
        
        //! Truong hop cay co mot con
        if(pRoot->pLeft == NULL && pRoot->pRight == NULL){
            delete pRoot;
            //! Node parent tro vao NULL de khong bi gia tri rac
            pRoot = NULL;
            return;
        }

        //! Truong hop cay co mot con ben trai
        if(pRoot->pLeft != NULL && pRoot->pRight == NULL){
            Node* p = pRoot;
            pRoot = pRoot->pLeft;
            delete p;
            return;
        }

        //! Truong hop cay co mot con ben phai
        if(pRoot->pLeft == NULL && pRoot->pRight != NULL){
            Node* p = pRoot;
            pRoot = pRoot->pRight;
            delete p;
            return;
        }

        //! Truong hop cay co hai con
        if(pRoot->pLeft != NULL && pRoot->pRight != NULL){
            Node* p = pRoot->pRight;
            while(p->pLeft != NULL){
                p = p->pLeft; //! Node ben trai cuoi cung cua cay ben phai
                //! Thay bang Node ben phai cuoi cung cua cai ben trai cung duoc
            }
            pRoot->key = p->key;
            Remove(pRoot->pRight, pRoot->key);
        }
    }
}

Node* createTree(int a[], int n){
    Node* pRoot = NULL;
    for(int i = 0; i < n; i++){
        Insert(pRoot, a[i]);
    }
    return pRoot;
}

void removeTree(Node*& pRoot){
    while(pRoot != NULL){
        Remove(pRoot, pRoot->key);
    }
}

//! Chieu cao cua mot node la chieu cao cua cay duoc tao ra boi node do
int heightNode(Node* pRoot, int value){
    //! Node khong ton tai thi de quy trai = de quy phai = 0
    if(pRoot == NULL){
        return 0;
    }
    if(pRoot->key == value){
        return height(pRoot);
    }
    return heightNode(pRoot->pLeft, value) + heightNode(pRoot->pRight, value);
}

int Level(Node* pRoot, Node* p){
    if (pRoot == NULL){
        return 0;
    }
    queue <Node*> q1; //! Chua node tren cay
    queue <int> q2; //! Chua level tuong ung cua node trong q1
    q1.push(pRoot);
    q2.push(1);
    while(!q1.empty()){
        Node* temp = q1.front(); //! Lay gia tri phan tu dau tien cua q1
        q1.pop(); //! Xoa gia tri dau tien khoi q1
        int x = q2.front();
        q2.pop();
        
        if(temp == p){
            return x;
        }

        if(temp->pLeft != NULL){
            q1.push(temp->pLeft);
            q2.push(x + 1);
        }

        if(temp->pRight != NULL){
            q1.push(temp->pRight);
            q2.push(x + 1);
        }
    }
    return 0;
}

int countLeaf(Node* pRoot){
    if(pRoot == NULL){
        return 0;
    }
    if(pRoot->pLeft == NULL && pRoot->pRight == NULL){
        return 1;
    }
    return countLeaf(pRoot->pLeft) + countLeaf(pRoot->pRight);
}

//! Gia tri cua Node nho hon gia tri x
int countLess(Node* pRoot, int x){
    if(pRoot == NULL){
        return 0;
    }
    if(pRoot->key == x){
        return countNode(pRoot);
    }
    if(pRoot->key > x){
        return countLess(pRoot->pLeft, x);
    }
    if(pRoot->key < x){
        return countNode(pRoot->pLeft) + 1 + countLess(pRoot->pRight, x);
    }
}

//! Gia tri cua Node lon hon gia tri x
int countGreater(Node* pRoot, int x){
    if(pRoot == NULL){
        return 0;
    }
    if(pRoot->key == x){
        return countNode(pRoot);
    }
    if(pRoot->key > x){
        return countNode(pRoot->pRight) + 1 + countGreater(pRoot->pLeft, x);
    }
    if(pRoot->key < x){
        return countGreater(pRoot->pRight, x);
    }
}

int minNode(Node* pRoot){
    if(pRoot == NULL){
        return 10000000;
    }
    return min(min(pRoot->key, minNode(pRoot->pLeft)), minNode(pRoot->pRight));
}

int maxNode(Node* pRoot){
    if(pRoot == NULL){
        return -10000000;
    }
    return max(max(pRoot->key, maxNode(pRoot->pLeft)), maxNode(pRoot->pRight));
}

bool isBST(Node* pRoot){
    if(pRoot == NULL){
        return true;
    }
    //! Node goc lon hon Node lon nhat ben trai
    //! Node goc nho hon Node nho nhat ben phai
    //! Tat ca cac Node tren cay phai thoa 2 dieu kien nay
    if(pRoot->key < minNode(pRoot->pRight) && pRoot->key > maxNode(pRoot->pLeft)){
        return isBST(pRoot->pLeft) && isBST(pRoot->pRight);
    }
    return false;
}

bool isFullBST(Node* pRoot){
    if(pRoot == NULL){
        return true;
    }
    if(pRoot->pLeft == NULL && pRoot->pRight == NULL){
        return true;
    }
    if(pRoot->pLeft != NULL && pRoot->pRight != NULL && isBST(pRoot)){
        return isFullBST(pRoot->pLeft) && isFullBST(pRoot->pRight);
    }
    return false;
}



#include <iostream>
using namespace std;

enum class Color : char
{
	RED,
	BLACK
};

struct Node
{
	int Key;
	Color Color;
	Node* Parent;
	Node* Left;
	Node* Right;
};

void Initialize(Node*& root, Node*& nil);

Node* CreateNode(Node* nil, int key, Color color);

void LNR(Node* root, Node* nil);

void Insert(Node*& root, Node* nil, int key);

void InsFixUp(Node*& root, Node* nil, Node* x);

void Remove(Node*& root, Node* nil, int key);

void RevFixUp(Node*& root, Node* nil, Node* p);

void SingleRotationWithRightChild(Node*& root, Node* nil, Node* p);

void SingleRotationWithLeftChild(Node*& root, Node* nil, Node* p);

void RemoveAll(Node*& root, Node*& nil);

void RemoveAllNode(Node*& root, Node*& nil);

void Initialize(Node*& root, Node*& nil)
{
	if (nil == NULL)
	{
		nil = CreateNode(nil, -1, Color::BLACK);
		nil->Parent = nil->Left = nil->Right = nil;
		root = nil;
	}
}

Node* CreateNode(Node* nil, int key, Color color)
{
	Node* p = new Node;

	p->Key = key;
	p->Color = color;
	p->Parent = p->Left = p->Right = nil;

	return p;
}

void LNR(Node* root, Node* nil)
{

}

void Insert(Node*& root, Node* nil, int key)
{
	Node* p = root;
	Node* chase_p = nil;

	while (p != nil)
	{
		chase_p = p;

		if (key < p->Key)
			p = p->Left;
		else if (key > p->Key)
			p = p->Right;
		else
			return;
	}

	Node* new_node = CreateNode(nil, key, Color::RED);

	new_node->Parent = chase_p;

	if (chase_p == nil)
		root = new_node;
	else
	{
		if (new_node->Key < chase_p->Key)
			chase_p->Left = new_node;
		else
			chase_p->Right = new_node;
	}

	InsFixUp(root, nil, new_node);
}

void InsFixUp(Node*& root, Node* nil, Node* x)
{
	while (x->Parent->Color == Color::RED)
	{
		Node* p = x->Parent;			// Parent of x
		Node* g = x->Parent->Parent;	// Grandparent of x

		if (p == g->Left)
		{
			Node* u = g->Right;			// Uncle of x

			if (u->Color == Color::RED)		// Case 1: Uncle u is RED
			{
				p->Color = u->Color = Color::BLACK;
				g->Color = Color::RED;

				x = g;
			}
			else
			{
				if (x == p->Right)	// Case 3: Uncle u is BLACK and x is INTERNAL child of p
				{
					SingleRotationWithRightChild(root, nil, p);

					x = p;
					p = x->Parent;
				}

				// Case 2: Uncle u is BLACK and x is EXTERNAL child of p
				p->Color = Color::BLACK;
				g->Color = Color::RED;

				SingleRotationWithLeftChild(root, nil, g);
			}
		}
		else
		{
			Node* u = g->Left;

			if (u->Color == Color::RED)
			{
				p->Color = u->Color = Color::BLACK;
				g->Color = Color::RED;

				x = g;
			}
			else
			{
				if (x == p->Left)
				{
					SingleRotationWithLeftChild(root, nil, p);

					x = p;
					p = x->Parent;
				}

				p->Color = Color::BLACK;
				g->Color = Color::RED;

				SingleRotationWithRightChild(root, nil, g);
			}
		}
	}

	root->Color = Color::BLACK;
}

void Remove(Node*& root, Node* nil, int key)
{

}

void RevFixUp(Node*& root, Node* nil, Node* p)
{

}

void SingleRotationWithRightChild(Node*& root, Node* nil, Node* p)
{
	if (p == NULL)
		return;

	Node* x = p->Right;

	p->Right = x->Left;
	if (p->Right != nil)
		p->Right->Parent = p;

	x->Parent = p->Parent;
	if (p->Parent == nil)
		root = x;
	else
	{
		if (p == p->Parent->Left)
			p->Parent->Left = x;
		else
			p->Parent->Right = x;
	}

	x->Left = p;
	p->Parent = x;
}

void SingleRotationWithLeftChild(Node*& root, Node* nil, Node* p)
{
	if (p == NULL)
		return;

	Node* x = p->Left;

	p->Left = x->Right;
	if (p->Left != nil)
		p->Left->Parent = p;

	x->Parent = p->Parent;
	if (p->Parent == nil)
		root = x;
	else
	{
		if (p == p->Parent->Left)
			p->Parent->Left = x;
		else
			p->Parent->Right = x;
	}

	x->Right = p;
	p->Parent = x;
}

void RemoveAll(Node*& root, Node*& nil)
{
	RemoveAllNode(root, nil);
	root = NULL;		// In case: root == nil (initial state)

	delete nil;
	nil = NULL;
}

void RemoveAllNode(Node*& root, Node*& nil)
{
	if (root == nil)
		return;

	RemoveAllNode(root->Left, nil);
	RemoveAllNode(root->Right, nil);
	delete root;
	root = NULL;
}
int main()
{
	Node* root = NULL;
	Node* nil = NULL;

	Initialize(root, nil);



	RemoveAll(root, nil);

	return 0;
}

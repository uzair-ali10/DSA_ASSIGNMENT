#include<bits/stdc++.h>
using namespace std;


struct Node
{
	int data;
	Node* left, *right;
};

bool isMirror(Node* a, Node* b)
{
	if (a==NULL && b==NULL)
		return true;

	if (a==NULL || b == NULL)
		return false;

	return a->data == b->data && isMirror(a->left, b->right) && isMirror(a->right, b->left);
}


Node* newNode(int data)
{
	Node* node = new Node;
	node->data = data;
	node->left = node->right = NULL;
	return(node);
}


int main()
{
	Node *a = newNode(1);
	Node *b = newNode(1);
	a->left = newNode(2);
	a->right = newNode(3);
	a->left->left = newNode(4);
	a->left->right = newNode(5);

	b->left = newNode(3);
	b->right = newNode(2);
	b->right->left = newNode(5);
	b->right->right = newNode(4);

	// isMirror(a, b)? cout << "Yes" : cout << "No";
	bool result = isMirror(a, b);
	if(result)
	{
		cout<<"The Given Trees Are Mirror Images"<<endl;
	}
	else
	{
		cout<<"The Given Trees Are NOT Mirror Images"<<endl;
	}

	return 0;
}

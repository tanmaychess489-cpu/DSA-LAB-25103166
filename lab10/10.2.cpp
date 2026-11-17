#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node *left,*right;
    bool lthread,rthread;

    Node(int val)
    {
        data=val;
        left=right=NULL;
        lthread=rthread=true;
    }
};

void convert(Node* root,Node*& prev)
{
    if(root==NULL)
        return;

    if(!root->lthread)
        convert(root->left,prev);

    if(root->left==NULL)
    {
        root->left=prev;
        root->lthread=true;
    }

    if(prev!=NULL && prev->right==NULL)
    {
        prev->right=root;
        prev->rthread=true;
    }

    prev=root;

    if(!root->rthread)
        convert(root->right,prev);
}

Node* leftmost(Node* root)
{
    if(root==NULL)
        return NULL;

    while(!root->lthread)
        root=root->left;

    return root;
}

void inorder(Node* root)
{
    Node* curr=leftmost(root);

    while(curr!=NULL)
    {
        cout<<curr->data<<" ";

        if(curr->rthread)
            curr=curr->right;
        else
            curr=leftmost(curr->right);
    }
}

int main()
{
    Node* root=new Node(10);
    root->left=new Node(5);
    root->right=new Node(15);
    root->left->left=new Node(2);
    root->left->right=new Node(7);
    root->right->left=new Node(12);
    root->right->right=new Node(20);
    root->lthread=root->rthread=false;

    root->left->lthread=root->left->rthread=false;
    root->right->lthread=root->right->rthread=false;

    root->left->left->lthread=false;
    root->left->right->lthread=false;
    root->right->left->lthread=false;
    root->right->right->lthread=false;

    Node* prev=NULL;
    convert(root,prev);

    inorder(root);

    return 0;
}
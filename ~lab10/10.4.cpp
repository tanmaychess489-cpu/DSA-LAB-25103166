#include<iostream>
#include<vector>
using namespace std;

struct Node
{
    int data;
    Node *left,*right;

    Node(int val)
    {
        data=val;
        left=right=NULL;
    }
};

void inorder(Node* root,vector<int>& v)
{
    if(root==NULL)
        return;

    inorder(root->left,v);
    v.push_back(root->data);
    inorder(root->right,v);
}

int kthSmallest(Node* root,int k)
{
    vector<int> v;
    inorder(root,v);

    if(k<1 || k>v.size())
        return -1;

    return v[k-1];
}

int main()
{
    Node* root=new Node(8);
    root->left=new Node(3);
    root->right=new Node(10);
    root->left->left=new Node(1);
    root->left->right=new Node(6);
    root->right->right=new Node(14);
    root->left->right->left=new Node(4);
    root->left->right->right=new Node(7);
    root->right->right->left=new Node(13);

    vector<int> v;
    inorder(root,v);

    int q;
    cout<<"Enter number of queries: ";
    cin>>q;

    cout<<"Enter queries: ";

    while(q--)
    {
        int k;
        cin>>k;

        if(k<1 || k>v.size())
            cout<<"Invalid ";
        else
            cout<<v[k-1]<<" ";
    }

    return 0;
}
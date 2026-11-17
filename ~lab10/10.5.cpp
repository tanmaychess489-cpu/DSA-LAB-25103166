#include<iostream>
#include<vector>
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

Node* insert(Node* root,int val)
{
    if(root==NULL)
        return new Node(val);

    if(val<root->data)
    {
        if(!root->lthread)
            root->left=insert(root->left,val);
        else
        {
            Node* temp=new Node(val);
            temp->left=root->left;
            temp->right=root;
            root->left=temp;
            root->lthread=false;
        }
    }
    else if(val>root->data)
    {
        if(!root->rthread)
            root->right=insert(root->right,val);
        else
        {
            Node* temp=new Node(val);
            temp->right=root->right;
            temp->left=root;
            root->right=temp;
            root->rthread=false;
        }
    }

    return root;
}

Node* leftmost(Node* root)
{
    if(root==NULL)
        return NULL;

    while(!root->lthread)
        root=root->left;

    return root;
}

Node* rightmost(Node* root)
{
    if(root==NULL)
        return NULL;

    while(!root->rthread)
        root=root->right;

    return root;
}

Node* successor(Node* root)
{
    if(root->rthread)
        return root->right;

    return leftmost(root->right);
}

Node* predecessor(Node* root)
{
    if(root->lthread)
        return root->left;

    return rightmost(root->left);
}

Node* search(Node* root,int x)
{
    while(root!=NULL)
    {
        if(x==root->data)
            return root;

        if(x<root->data)
        {
            if(root->lthread)
                return NULL;
            root=root->left;
        }
        else
        {
            if(root->rthread)
                return NULL;
            root=root->right;
        }
    }

    return NULL;
}

void rangeQuery(Node* root,int l,int r)
{
    Node* curr=leftmost(root);

    while(curr!=NULL && curr->data<l)
        curr=successor(curr);

    while(curr!=NULL && curr->data<=r)
    {
        cout<<curr->data<<" ";
        curr=successor(curr);
    }
}

int kthSmallest(Node* root,int k)
{
    Node* curr=leftmost(root);

    while(curr!=NULL && k>1)
    {
        curr=successor(curr);
        k--;
    }

    if(curr==NULL || k!=1)
        return -1;

    return curr->data;
}

int main()
{
    Node* root=NULL;

    int n;
    cout<<"Enter number of scores: ";
    cin>>n;

    cout<<"Enter scores: ";

    for(int i=0;i<n;i++)
    {
        int x;
        cin>>x;
        root=insert(root,x);
    }

    int choice;

    do
    {
        cout<<"\n1. NEXT\n2. PREV\n3. RANGE\n4. KTH\n5. EXIT\n";
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice==1 || choice==2)
        {
            int x;
            cin>>x;

            Node* curr=search(root,x);
            Node* ans=NULL;

            if(curr!=NULL)
            {
                if(choice==1)
                    ans=successor(curr);
                else
                    ans=predecessor(curr);
            }

            if(ans==NULL)
                cout<<"NULL\n";
            else
                cout<<ans->data<<"\n";
        }
        else if(choice==3)
        {
            int l,r;
            cin>>l>>r;
            rangeQuery(root,l,r);
            cout<<"\n";
        }
        else if(choice==4)
        {
            int k;
            cin>>k;

            if(k<1)
                cout<<"NULL\n";
            else
                cout<<kthSmallest(root,k)<<"\n";
        }

    }while(choice!=5);

    return 0;
}
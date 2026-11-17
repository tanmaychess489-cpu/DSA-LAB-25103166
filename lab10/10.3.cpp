#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
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
void buildParent(Node* root,unordered_map<Node*,Node*>& parent,Node*& target,int s)
{
    if(root==NULL)
        return;

    if(root->data==s)
        target=root;

    if(root->left)
    {
        parent[root->left]=root;
        buildParent(root->left,parent,target,s);
    }

    if(root->right)
    {
        parent[root->right]=root;
        buildParent(root->right,parent,target,s);
    }
}
vector<int> distanceK(Node* root,int s,int k)
{
    unordered_map<Node*,Node*> parent;
    Node* target=NULL;

    buildParent(root,parent,target,s);

    queue<Node*> q;
    unordered_map<Node*,bool> visited;

    q.push(target);
    visited[target]=true;

    int dist=0;

    while(!q.empty() && dist<k)
    {
        int size=q.size();

        while(size--)
        {
            Node* curr=q.front();
            q.pop();

            if(curr->left && !visited[curr->left])
            {
                q.push(curr->left);
                visited[curr->left]=true;
            }

            if(curr->right && !visited[curr->right])
            {
                q.push(curr->right);
                visited[curr->right]=true;
            }

            if(parent.count(curr) && !visited[parent[curr]])
            {
                q.push(parent[curr]);
                visited[parent[curr]]=true;
            }
        }

        dist++;
    }

    vector<int> ans;

    while(!q.empty())
    {
        ans.push_back(q.front()->data);
        q.pop();
    }

    return ans;
}

int main()
{
    Node* root=new Node(3);
    root->left=new Node(5);
    root->right=new Node(1);
    root->left->left=new Node(6);
    root->left->right=new Node(2);
    root->right->left=new Node(0);
    root->right->right=new Node(8);
    root->left->right->left=new Node(7);
    root->left->right->right=new Node(4);

    int s,k;
    cout<<"Enter target: ";
    cin>>s;

    cout<<"Enter distance: ";
    cin>>k;

    vector<int> ans=distanceK(root,s,k);

    cout<<"Nodes at distance "<<k<<": ";
    cout<<"[";

    for(int i=0;i<ans.size();i++)
    {
        cout<<ans[i];
        if(i<ans.size()-1)
            cout<<", ";
    }

    cout<<"]";
    

    return 0;
}
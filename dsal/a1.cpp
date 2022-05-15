/*
    Shreyash Halge (21132 F1-Batch)
    DSAL Assignment-1

    Beginning with an empty binary tree, Construct binary tree by inserting the values in the order given.
    After constructing a binary tree perform following operations on it-

    Perform inorder / preorder and post order traversal
    Change a tree so that the roles of the left and right pointers are swapped at every node
    Find the height of tree
    Copy this tree to another
    Count number of leaves, number of internal nodes.
    Erase all nodes in a binary tree.
    (implement both recursive and non-recursive methods)

Cases:
                    10                      1
        15                      12          2
    17      19              27      26      3
                11                          4

    Inorder: 17 15 19 11 10 27 12 26
    Preorder:10 15 17 19 11 12 27 26
    postorder:17 11 19 15 27 26 12 10

                    10
        12                      15
    26      27              19      17
                        11

    Inorder: 26 12 27 10 11 19 15 17
    Preorder: 10 12 26 27 15 19 11 17
    postorder: 26 27 12 11 19 17 15 10

*/

#include <iostream>
using namespace std;

class Tree;
class Node
{
private:
    int data;
    Node *left, *right;
    static unsigned int nodeCount;
    static unsigned int leafCount;

public:
    static void nodeCT() { cout << "The number of nodes in tree is: " << Node::nodeCount << endl; }
    static void leafCT() { cout << "\nThe number of leaves in tree is: " << Node::leafCount << endl; }
    static void setDef() { leafCount = nodeCount = 0; };
    friend class Tree;
    Node(int x)
    {
        data = x;
        left = right = NULL;
    };
    ~Node(){};
    void erase(Node *&);
} *root1 = NULL, *root2 = NULL;

class Tree
{
public:
    Node *create(Node *&);
    void preorder(Node *);
    void iterativePreorder(Node *);
    void postorder(Node *);
    void iterativePostorder(Node *);
    void inorder(Node *);
    void iterativeInorder(Node *);
    void swapChildren(Node *);
    Node *copyTree(Node *&, Node *&);
    int height(Node *);
} tree;

template <typename T>
class Stack
{
public:
    class StackNode
    {
    private:
        T data;
        StackNode *next;

    public:
        friend class Stack;
        StackNode(T &data)
        {
            this->data = data;
            next = NULL;
        }
        StackNode() { next = NULL; }
    };

private:
    StackNode *top;

public:
    Stack() { top = NULL; }
    void push(T x)
    {
        StackNode *tmp = new StackNode(x);
        tmp->next = top;
        top = tmp;
    };

    T pop()
    {
        StackNode *tmp;
        tmp = top;
        auto x = tmp->data;
        top = top->next;
        delete tmp;
        return x;
    };

    bool isEmpty() { return top == NULL ? 1 : 0; };
};

unsigned int Node::nodeCount = 0;
unsigned int Node::leafCount = 0;

int main()
{
    bool menu = 1;
    int choice;
    cout << "\nEnter the data for tree: ";
    tree.create(root1);
    while (menu)
    {
        cout << "\n\nMENU\n1.RECURSIVE TRAVERSAL\n2.ITERATIVE TRAVERSAL\n3.NUMBER OF LEAVES,NODES AND HEIGHT\n4.SWAP CHILDREN\n5.COPY TREE\n6.ERASE NODES\n\nEnter your choice(-1 to exit): ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\nRECURSIVE TRAVERSALS:-";
            cout << "\nIN-ORDER TRAVERSAL: ";
            tree.inorder(root1);
            cout << "\nPRE-ORDER TRAVERSAL: ";
            tree.preorder(root1);
            cout << "\nPOST-ORDER TRAVERSAL: ";
            tree.postorder(root1);
            break;

        case 2:
            cout << "\nITERATIVE TRAVERSALS:-";
            cout << "\nIN-ORDER: ";
            tree.iterativeInorder(root1);
            cout << "\nPRE-ORDER: ";
            tree.iterativePreorder(root1);
            cout << "\nPOST-ORDER: ";
            tree.iterativePostorder(root1);
            break;

        case 3:
            root1->leafCT();
            root1->nodeCT();
            cout << "HEIGHT: " << tree.height(root1);
            break;

        case 4:
            tree.swapChildren(root1);
            break;

        case 5:
            tree.copyTree(root2, root1);
            cout << "\nTree copied!";
            cout << "\nTraversals on copied tree: ";
            cout << "\nIN-ORDER: ";
            tree.inorder(root2);
            cout << "\nPRE-ORDER: ";
            tree.preorder(root2);
            cout << "\nPOST-ORDER: ";
            tree.postorder(root2);
            break;

        case 6:
            root1->erase(root1);
            root1->setDef();
            break;

        case -1:
            menu = 0;
            break;

        default:
            cout << "\nInvalid choice!";
            break;
        }
    }

    return 0;
}

Node *Tree::copyTree(Node *&rt1, Node *&rt2)
{
    Node *temp;
    if (rt2 == NULL)
        return NULL;
    temp = new Node(rt2->data);
    if (rt1 == NULL)
        rt1 = temp;
    temp->left = copyTree(rt1, rt2->left);
    temp->right = copyTree(rt1, rt2->right);
    return temp;
}

Node *Tree::create(Node *&root)
{
    Node *tmp;
    int x;
    cout << "\nEnter data(Enter -1 to stop):  ";
    cin >> x;
    if (x == -1)
        return NULL;
    tmp = new Node(x);
    Node::nodeCount++;
    tmp->data = x;

    if (root == NULL)
        root = tmp;
    // char ch;
    // cout << "\nDo you want to create children for " << x;
    // cout << "\nEnter your choice?(y/n): ";
    // cin >> ch;

    // if (ch == 'y')
    // {
    cout << "\nEnter left child of " << x;
    tmp->left = create(root);

    cout << "\nEnter right child of " << x;
    tmp->right = create(root);

    // }
    if (tmp->left == NULL && tmp->right == NULL)
        Node::leafCount++;

    return tmp;
}

int Tree::height(Node *rt)
{
    int x = 0, y = 0;

    if (root1->nodeCount == 0)
        return -1;
    if (rt == NULL)
        return 0;
    x = height(rt->left);
    y = height(rt->right);
    if (x > y)
        return x + 1;
    else
        return y + 1;
}

void Node::erase(Node *&temp)
{
    if (Node::nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    if (temp != NULL)
    {
        erase(temp->left);
        erase(temp->right);
        delete temp;
        temp = NULL;
    }
}

void Tree::swapChildren(Node *tmp)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    if (tmp != NULL)
    {
        swapChildren(tmp->right);
        swapChildren(tmp->left);
        if (tmp->left != NULL && tmp->right != NULL)
            swap(tmp->left, tmp->right);
        else if (tmp->left || tmp->right)
        {
            Node *temp = tmp->left;
            tmp->left = tmp->right;
            tmp->right = temp;
        }
    }
}

void Tree::preorder(Node *root)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    if (root)
    {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void Tree::inorder(Node *root)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    if (root)
    {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void Tree::postorder(Node *root)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    if (root)
    {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

void Tree::iterativePreorder(Node *p)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    Stack<Node *> st;
    while (p != NULL || !st.isEmpty())
    {
        if (p != NULL)
        {
            cout << p->data << " ";
            st.push(p);
            p = p->left;
        }
        else
        {
            p = st.pop();
            p = p->right;
        }
    }
}

void Tree::iterativePostorder(Node *p)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    Stack<long long int> st;
    long long int temp;
    while (p != NULL || !st.isEmpty())
    {
        if (p != NULL)
        {
            st.push((long long int)p);
            p = p->left;
        }
        else
        {
            temp = st.pop();
            if (temp > 0)
            {
                st.push(-1 * temp);
                p = (Node *)temp;
                p = p->right;
            }
            else
            {
                cout << ((Node *)(-1 * temp))->data << " ";
                p = NULL;
            }
        }
    }
}

void Tree::iterativeInorder(Node *p)
{
    if (root1->nodeCount == 0)
    {
        cout << "\nTree does not exist!!!";
        return;
    }
    Stack<Node *> st;
    while (p != NULL || !st.isEmpty())
    {
        if (p != NULL)
        {
            st.push(p);
            p = p->left;
        }
        else
        {
            p = st.pop();
            cout << p->data << " ";
            p = p->right;
        }
    }
}
/*
Enter the data for tree: 
Enter data(Enter -1 to stop):  33

Enter left child of 33
Enter data(Enter -1 to stop):  12

Enter left child of 12
Enter data(Enter -1 to stop):  19

Enter left child of 19
Enter data(Enter -1 to stop):  -1

Enter right child of 19
Enter data(Enter -1 to stop):  -1

Enter right child of 12
Enter data(Enter -1 to stop):  25

Enter left child of 25
Enter data(Enter -1 to stop):  -1

Enter right child of 25
Enter data(Enter -1 to stop):  -1

Enter right child of 33
Enter data(Enter -1 to stop):  45

Enter left child of 45
Enter data(Enter -1 to stop):  35

Enter left child of 35
Enter data(Enter -1 to stop):  -1

Enter right child of 35
Enter data(Enter -1 to stop):  -1

Enter right child of 45
Enter data(Enter -1 to stop):  21

Enter left child of 21
Enter data(Enter -1 to stop):  -1

Enter right child of 21
Enter data(Enter -1 to stop):  -1


MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 1

RECURSIVE TRAVERSALS:-
IN-ORDER TRAVERSAL: 19 12 25 33 35 45 21 
PRE-ORDER TRAVERSAL: 33 12 19 25 45 35 21 
POST-ORDER TRAVERSAL: 19 25 12 35 21 45 33 

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 2

ITERATIVE TRAVERSALS:-
IN-ORDER: 19 12 25 33 35 45 21 
PRE-ORDER: 33 12 19 25 45 35 21 
POST-ORDER: 19 25 12 35 21 45 33 

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 3

The number of leaves in tree is: 4
The number of nodes in tree is: 7
HEIGHT: 3

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 4


MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 1

RECURSIVE TRAVERSALS:-
IN-ORDER TRAVERSAL: 21 45 35 33 25 12 19 
PRE-ORDER TRAVERSAL: 33 45 21 35 12 25 19 
POST-ORDER TRAVERSAL: 21 35 45 25 19 12 33 

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 5

Tree copied!
Traversals on copied tree: 
IN-ORDER: 21 45 35 33 25 12 19 
PRE-ORDER: 33 45 21 35 12 25 19 
POST-ORDER: 21 35 45 25 19 12 33 

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 6


MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 1

RECURSIVE TRAVERSALS:-
IN-ORDER TRAVERSAL: 
Tree does not exist!!!
PRE-ORDER TRAVERSAL: 
Tree does not exist!!!
POST-ORDER TRAVERSAL: 
Tree does not exist!!!

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): 2

ITERATIVE TRAVERSALS:-
IN-ORDER: 
Tree does not exist!!!
PRE-ORDER: 
Tree does not exist!!!
POST-ORDER: 
Tree does not exist!!!

MENU
1.RECURSIVE TRAVERSAL
2.ITERATIVE TRAVERSAL
3.NUMBER OF LEAVES,NODES AND HEIGHT
4.SWAP CHILDREN
5.COPY TREE
6.ERASE NODES

Enter your choice(-1 to exit): -1
*/
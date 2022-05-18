#include "OrgChart.hpp"
#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <list>
using namespace std;
namespace ariel
{
    OrgChart::OrgChart()
    {
        this->root = nullptr;
        this->loi = new LevelOrderIterator();
        this->lori = new LevelOrderReversedIterator();
        this->poi = new PreOrderIterator();
    }

    OrgChart::~OrgChart(){};

    void levelOrder(Node *root, vector<Node *> &iter) // got help from https://www.tutorialspoint.com/n-ary-tree-level-order-traversal-in-cplusplus
    { // Good
        if(root==nullptr) return;
        iter.clear();
        queue<Node*> q;
        q.push(root); 
        while (!q.empty())
        {
            Node *p = q.front();
            iter.push_back(p);
            for(unsigned long i = 0; i < p->sons.size(); i++) // insert all node sons to the queue
            {
                q.push(p->sons[i]);
            }
            q.pop();
        }
    }
    void levelOrderReverse(Node *root, vector<Node *> &iter) // got help from https://www.tutorialspoint.com/n-ary-tree-level-order-traversal-in-cplusplus
    {
        vector < vector <Node*> > reverseIter;
        if(root == nullptr) return;
        queue <Node*> q;
        q.push(root);
        while(!q.empty()){
            int sz = q.size();
            vector<Node*> temp;
            while(sz--){
                Node* curr = q.front();
                temp.push_back(curr);
                q.pop();
                for(unsigned long i = 0; i < curr->sons.size(); i++){
                q.push(curr->sons[i]);
                }
            }
            reverseIter.push_back(temp);
        }
        for(int i= reverseIter.size()-1; i >=0; i--)
        {
            for(unsigned long j = 0; j < reverseIter[(unsigned long)i].size(); j ++)
            {
                iter.push_back(reverseIter[(unsigned long)i][j]);
            }
        }
   }

    // Insert the nodes to the iter in preorder
    void preOrder(Node *root, vector<Node *> &iter) // Got help from https://www.geeksforgeeks.org/iterative-preorder-traversal-of-a-n-ary-tree/
    { // Good
        stack<Node*> Stack;
        Stack.push(root);
        while(!Stack.empty()){
            Node* temp = Stack.top();
            Stack.pop();
            iter.push_back(temp);
            for (int i = temp->sons.size() - 1; i >= 0; i--) { // insert all node sons to stack: start from the last son
            Stack.push(temp->sons[(unsigned long)i]);
        }
        }
    }

    LevelOrderIterator OrgChart::begin_level_order()
    { // Good
        this->loi->first = root;
        this->loi->i = 0;
        if (root != nullptr) 
        {
            levelOrder(root, this->loi->iter); 
            if (this->loi->iter.empty()) // we finish to pass the iterator so put null in the first node of the iterator
            {
                this->loi->first = nullptr;
            }
        }
        return *(this->loi);
    }

    LevelOrderIterator OrgChart::end_level_order()
    { // Good
        this->loi->first = NULL;
        this->loi->i = 0;
        return *(this->loi);
    }
    LevelOrderReversedIterator OrgChart::begin_reverse_order() 
    { // Good
        this->lori->first = root;
        this->lori->i = 0;
        if (root != nullptr) 
        {
            levelOrderReverse(root, this->lori->iter); 
            if (this->lori->iter.empty()) // we finish to pass the iterator so put null in the first node of the iterator
            {
                this->lori->first = nullptr;
            }
        }
        return *(this->lori);
    }

    LevelOrderReversedIterator OrgChart::reverse_order() 
    { // Good
        this->lori->first = NULL;
        this->lori->i = 0;
        return *(this->lori);
    }

    PreOrderIterator OrgChart::begin_preorder() 
    { // Good
        this->poi->first = root;
        this->poi->i = 0;
        if (root != nullptr) 
        {
            preOrder(root, this->poi->iter); 
            if (this->poi->iter.empty()) // we finish to pass the iterator so put null in the first node of the iterator
            {
                this->poi->first = nullptr;
            }
        }
        return *(this->poi);
    }

    PreOrderIterator OrgChart::end_preorder() 
    { // Good
        this->poi->first = NULL;
        this->poi->i = 0;
        return *(this->poi);
    }

    LevelOrderIterator OrgChart::begin() 
    { // Good
        return this->begin_level_order();
    }
    LevelOrderIterator OrgChart::end()
    { // Good
        return this->end_level_order();
    }

    OrgChart &OrgChart::add_root(const string &jobRank)
    { // Good
        Node* n = new Node(); // initialize new node struct
        n->jobRank = jobRank; // insert the job role of the root
        this->root = n; // make n root
        return *this;
    }

    Node *OrgChart::findNode(Node *node, string jobRank)
    { // Good
        if (node == nullptr) // not exit
        {
            return nullptr;
        }
        if (node->jobRank == jobRank) // We find the node
        {
            return node;
        }

        for (unsigned long i = 0; i < node->sons.size(); i++)
        {
            Node *n = findNode(node->sons[i], jobRank); // check in the sons of current ptr
            if (n) // we find the node
            {
                return n;
            }
        }

        return nullptr;
    }

    OrgChart &OrgChart::add_sub(const string &father, const string &son)
    {  // Good
        if (this->root == nullptr)
        {
            throw ("You can't do it, the orgChart is empty :(");
        }
        Node *n = findNode(this->root, father);
        if (n == nullptr)
        {
            throw ("The father not exist in the orgChart");
        }
        Node* son_node = new Node();
        son_node->jobRank = son;
        n->sons.push_back(son_node);
        return *this;
    }
    ostream &operator<<(ostream &os, const OrgChart &org) // got help from https://www.studytonight.com/advanced-data-structures/nary-tree
    { // Good
        string answer = "";
        if(org.root == nullptr) return os;
        queue<Node*> q;
        q.push(org.root);
        while(!q.empty()) {
            int len = q.size();
            for(int i=0;i<len;i++) { // so that we can reach each level
                Node* node = q.front();
                q.pop();
                answer += node->jobRank;
                answer += " ";
                for (Node* item : node->sons) { // for-Each loop to iterate over all childrens
                    q.push(item);
                }
            }
            answer += '\n';
        }
        os << answer;
        return os;
    }
}

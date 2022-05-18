#pragma once
#include <vector>
#include <string>
#include <iostream>
using namespace std;
namespace ariel
{
    struct Node{
        string jobRank;
        vector<Node*> sons;
    };
    typedef struct Node Node;


    class LevelOrderIterator
    {
    private:

    public:
        Node *first;
        vector<Node *> iter;
        unsigned long i; // index of the current node
        LevelOrderIterator(){};
        std::string operator*()
        { 
            return this->iter[i]->jobRank;
        }

        std::string *operator->()
        {
            return &(this->iter[i]->jobRank);
        }
        LevelOrderIterator &operator++()
        {
            this->i+=1;
            if ( this->iter.size() == this->i )
            { // We finish to pass this iterator, so we make the first node NULL in order to avoid access to this iterator 
                this->first = NULL; 
            }
            return *this;
        }

        bool operator!=(const LevelOrderIterator &it) const
        { // use the deafult C++ operator !=
            return this->first != it.first;
        }

        LevelOrderIterator(Node *root);
    };
    class LevelOrderReversedIterator
        {
        private:
        public:
            Node *first;
            vector<Node *> iter;
            unsigned long i;
            LevelOrderReversedIterator(){};
            std::string operator*()
            {
                return this->iter[i]->jobRank;
            }

            std::string *operator->()
            {
                return &(this->iter[i]->jobRank);
            }
            LevelOrderReversedIterator &operator++()
            {
                this->i++;
                if (this->i == this->iter.size())
                {
                    this->first = NULL;
                }
                return *this;
            }
            bool operator!=(const LevelOrderReversedIterator &it) const
            {
                return this->first != it.first;
            }
            LevelOrderReversedIterator(Node *first);
        };
    class PreOrderIterator
        {
        private:
        public:
            Node *first;
            vector<Node *> iter;
            unsigned long i;
            PreOrderIterator(){};
            std::string operator*()
            {
                return this->iter[i]->jobRank;
            }

            std::string *operator->() // -> operator for demo will work
            {
                return &(this->iter[i]->jobRank);
            }
            PreOrderIterator &operator++()
            {
                this->i++;
                if (this->i == this->iter.size())
                {
                    this->first = NULL;
                }
                return *this;
            }

            bool operator!=(const PreOrderIterator &it) const
            {
                return this->first != it.first;
            }
            PreOrderIterator(Node *root);
        };

    class OrgChart
    {
    private:
        Node *root;
        LevelOrderIterator *loi;
        LevelOrderReversedIterator *lori;
        PreOrderIterator *poi;
    public:
        OrgChart();
        ~OrgChart();
        OrgChart &add_root(const string &jobRank);
        Node *findNode(Node *node, string jobRank);
        OrgChart &add_sub(const string &father,const std::string &son);
        LevelOrderIterator begin_level_order();
        LevelOrderIterator end_level_order();
        LevelOrderReversedIterator begin_reverse_order();
        LevelOrderReversedIterator reverse_order();
        PreOrderIterator begin_preorder();
        PreOrderIterator end_preorder();
        LevelOrderIterator begin();
        LevelOrderIterator end() ;
        friend std::ostream &operator<<(ostream &os, const OrgChart &org);
    };
}

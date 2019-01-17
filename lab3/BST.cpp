#include <iostream>

using namespace std;

template<class T>
class BST
{
public:
    struct node
    {
        T data;
        node *right = NULL;
        node *left = NULL;
        char height = 0;
        node(){}
        node(T key): data(key){}
    };
    size_t _size = 0;
    node* root;
    node* last;
    node* first;
    node* _end;
    BST()
    : root(NULL)
    , last(NULL)
    , first(NULL)
    , _end(new node)
    {}

    BST(const BST& tree)
    {
        copyNode(this->root, tree.root);
    }
    BST& operator=(const BST& tree)
    {
        copyNode(this->root, tree.root);
        return *this;
    }

    class iterator
    {
    public:
        BST* tree = NULL;
        node* act = NULL;
        iterator(){}
        iterator(BST* tree, node* n)
        : tree(tree)
        , act(n){}
        iterator& operator=(const iterator& it)
        {
            this->tree = it.tree;
            this->act = it.act;
            return *this;
        }
        iterator& operator++()
        {
            this->act = this->next(act);
            if (this->act == NULL)
                this->act = this->tree->_end;
            return *this;
        }
        iterator& operator++(int)
        {
            this->act = this->tree->next(act);
            if (this->act == NULL)
                this->act = this->tree->_end;
            return *this;
        }
        iterator& operator--()
        {
            this->act = this->prev(act);
            if (this->act == this->tree->_end)
                this->act = this->tree->last;
            return *this;
        }
        iterator& operator--(int)
        {
            this->act = this->tree->prev(act);
            if (this->act == this->tree->_end )
                this->act = this->tree->last;
            return *this;
        }
        bool operator==(const iterator& it)
        {
            if (this->act == it.act)
                return true;
            return false;
        }
        bool operator!=(const iterator& it)
        {
            if (this->act != it.act)
                return true;
            return false;
        }

        T operator*()
        {
            return this->act->data;
        }

    };

    iterator begin()
    {
        iterator it;
        it.tree = this;
        it.act = this->first;
        return it;
    }
    iterator end()
    {
        iterator it;
        it.tree = this;
        it.act = this->_end;
        return it;
    }

    node* copyNode(node* n, node* m)
    {
        if (!m) return NULL;
        n = new node(m->data);
        n->left = copyNode(n->left, m->left);
        n->right = copyNode(n->right, m->right);
        return n;
    }

    char height(node* n)
    {
        return n? n->height : 0;
    }
    char dif(node* n)
    {
        return height(n->right) - height(n->left);
    }
    void fixHeight(node* n)
    {
        n->height = max(height(n->left),height(n->right)) + 1;
    }

    node* rotateLeft (node* n)
    {
        node* q = n->right;
        n->right =  q->left;
        q->left = n;
        fixHeight(n);
        fixHeight(q);
        return q;
    }
    node* rotateRight (node* n)
    {
        node* q = n->left;
        n->left = q->right;
        q->right = n;
        fixHeight(n);
        fixHeight(q);
        return q;
    }

    node* balance(node* n)
    {
        fixHeight(n);
        if (dif(n) == 2)
        {
            if (dif(n->right) < 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        if (dif(n) == -2)
        {
            if (dif(n->left) > 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        return n;
    }

    node* insert(node* n, T key)
    {
        if (!n)
        {

            n = new node(key);
            if(!last || last->data < key)
                last = n;
            if(!first || first->data > key)
                first = n;
            _size++;
            return n;
        }
        if (key < n->data)
        {
            n->left = insert(n->left, key);
            _size--;
        }
        else
        {
            n->right = insert(n->right, key);
            _size--;
        }

        _size++;
        return balance(n);
    }

    node* findmin(node* n)
    {
        return n->left?findmin(n->left):n;
    }

    node* remove(node* n, T key)
    {
        _size--;
        if (!n) return NULL;
        if (key < n->data)
        {
            n->left = remove(n->left,key);
            _size++;
        }

        else
            if (key > n->data)
            {
               n->right = remove(n->right,key);
               _size++;
            }

            else
            {
                node* l = n->left;
                node* r = n->right;
                delete n;
                if  (!r) return l;
                node* minn = findmin(r);
                _size++;
                minn->right = remove(minn->right, r->data);
                minn->left = l;
                return balance(minn);
            }
        return balance(n);
    }

    node* next(node* n)
    {
        if (n == this->last)
            return NULL;
        node* m = this->root;
        node* mbNext = this->last;
        while (true)
        {
            if (m == NULL)
                break;
            if (m->data <= n->data)
                m = m->right;
            else
            {
                if (m->data < mbNext->data)
                    mbNext = m;
                m = m->left;
            }
        }
        return mbNext;
    }

    node* prev(node* n)
    {
        if (n == this->first)
            return NULL;
        node* m = this->root;
        node* mbPrev = this->first;
        while (true)
        {
            if (m == NULL)
                break;
            if (m->data >= n->data)
                m = m->left;
            else
            {
                if (m->data > mbPrev->data)
                    mbPrev = m;
                m = m->right;
            }
        }
        return mbPrev;
    }

    bool empty()
    {
        if (this->root = NULL)
            return true;
        return false;
    }
    size_t size()
    {
        return _size;
    }


};

int main()
{
    BST<int> a;
    a.root = a.insert(a.root,3);
    a.root = a.insert(a.root,5);
    a.root = a.insert(a.root,1);
    a.root = a.insert(a.root,4);
    a.root = a.insert(a.root,2);
    BST<int>::iterator it = a.begin();
    BST<int>::iterator it1 = a.end();
    for (BST<int>::iterator it2 = a.begin(); it2 != a.end(); it2++)
        cout << *it2;
    cout << endl << a.size() << endl;
    a.root = a.remove(a.root, 3);
    cout << a.size();
    return 0;
}

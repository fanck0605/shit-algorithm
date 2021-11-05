#pragma once
#include <utility>

template <typename Data>
class RbTree
{
public:
    enum class Color
    {
        red, black
    };

    struct Node
    {
        Data data{};

        Color color = Color::black;

        Node* lchild = nullptr;
        Node* rchild = nullptr;
        Node* parent = nullptr;
    };

    void insert(Data data)
    {
        Node* parent = nil;
        Node* current = root;

        while (current != nil)
        {
            parent = current;
            if (data < current->data)
            {
                current = current->lchild;
            }
            else
            {
                current = current->rchild;
            }
        }

        Node* toInsert = createNode(std::move(data), parent);

        if (parent == nil)
        {
            root = toInsert;
        }
        else if (toInsert->data < parent->data)
        {
            parent->lchild = toInsert;
        }
        else
        {
            parent->rchild = toInsert;
        }

        insertFixup(toInsert);
    }

    Node* find(const Data& data)
    {
        Node* current = root;
        while (current != nil)
        {
            if (data < current->data)
            {
                current = current->lchild;
            }
            else if (data > current->data)
            {
                current = current->rchild;
            }
            else
            {
                break;
            }
        }
        return current;
    }

    void remove(Node* z)
    {
        Node* y = z;
        Color yOriginalColor = y->color;

        Node* x;
        if (z->lchild == nil)
        {
            x = z->rchild;
            transplant(z, z->rchild);
        }
        else if (z->rchild == nil)
        {
            x = z->lchild;
            transplant(z, z->lchild);
        }
        else
        {
            y = minimumHelper(z->rchild);
            yOriginalColor = y->color;

            x = y->rchild;
            if (y->parent == z)
            {
                x->parent = y; // x == nil
            }
            else
            {
                transplant(y, y->rchild);
                y->rchild = z->rchild;
                y->rchild->parent = y;
            }
            transplant(z, y);
            y->lchild = z->lchild;
            y->lchild->parent = y;
            y->color = z->color;
        }

        if (yOriginalColor == Color::black)
        {
            removeFixup(x);
        }
    }

private:
    Node* const nil = new Node{};
    Node* root = nil;

    Node* minimumHelper(Node* x)
    {
        while (x->lchild != nil)
        {
            x = x->lchild;
        }
        return x;
    }

    Node* maximumHelper(Node* x)
    {
        while (x->rchild != nil)
        {
            x = x->rchild;
        }
        return x;
    }

    Node* createNode(Data data, Node* parent) {
        return new Node{ std::move(data),Color::red,nil,nil,parent };
    }

    void insertFixup(Node* z)
    {
        while (z->parent->color == Color::red)
        {
            if (z->parent == z->parent->parent->lchild)
            {
                Node* y = z->parent->parent->rchild;
                if (y->color == Color::red)
                {
                    z->parent->color = Color::black;
                    y->color = Color::black;
                    z->parent->parent->color = Color::red;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->rchild)
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = Color::black;
                    z->parent->parent->color = Color::red;
                    rightRotate(z->parent->parent);
                }
            }
            else
            {
                Node* y = z->parent->parent->lchild;
                if (y->color == Color::red)
                {
                    z->parent->color = Color::black;
                    y->color = Color::black;
                    z->parent->parent->color = Color::red;
                    z = z->parent->parent;
                }
                else {
                    if (z == z->parent->lchild)
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = Color::black;
                    z->parent->parent->color = Color::red;
                    leftRotate(z->parent->parent);
                }
            }
        }

        root->color = Color::black;
    }

    Node* rightRotate(Node* parent)
    {
        Node* newParent = parent->lchild;

        parent->lchild = newParent->rchild;
        newParent->rchild = parent;

        newParent->parent = parent->parent;
        if (parent->parent == nil)
        {
            root = newParent;
        }
        else if (parent->parent->lchild == parent)
        {
            parent->parent->lchild = newParent;
        }
        else // parent->parent->rchild == parent
        {
            parent->parent->rchild = newParent;
        }
        parent->parent = newParent;
        if (parent->lchild != nil)
        {
            parent->lchild->parent = parent;
        }

        return newParent;
    }

    Node* leftRotate(Node* parent)
    {
        Node* newParent = parent->rchild;

        parent->rchild = newParent->lchild;
        newParent->lchild = parent;

        newParent->parent = parent->parent;
        if (parent->parent == nil)
        {
            root = newParent;
        }
        else if (parent->parent->lchild == parent)
        {
            parent->parent->lchild = newParent;
        }
        else // parent->parent->rchild == parent
        {
            parent->parent->rchild = newParent;
        }
        parent->parent = newParent;
        if (parent->rchild != nil)
        {
            parent->rchild->parent = parent;
        }

        return newParent;
    }

    void transplant(Node* u, Node* v)
    {
        if (u->parent == nil) // root node
        {
            root = v;
        }
        else if (u == u->parent->lchild)
        {
            u->parent->lchild = v;
        }
        else
        {
            u->parent->rchild = v;
        }
        v->parent = u->parent;
    }

    void removeFixup(Node* x)
    {
        while (x != root && x->color == Color::black)
        {
            if (x == x->parent->lchild)
            {
                Node* w = x->parent->rchild;
                if (w->color == Color::red)
                {
                    w->color = Color::black;
                    x->parent->color = Color::red;
                    leftRotate(x->parent);
                    w = x->parent->rchild;
                }
                if (w->lchild->color == Color::black && w->rchild->color == Color::black)
                {
                    w->color = Color::red;
                    x = x->parent;
                }
                else
                {
                    if (w->rchild->color == Color::black) // w->lchild->color == Color::red
                    {
                        w->lchild->color = Color::black;
                        w->color = Color::red;
                        rightRotate(w);
                        w = x->parent->rchild;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::black;
                    w->rchild->color = Color::black;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                Node* w = x->parent->lchild;
                if (w->color == Color::red)
                {
                    w->color = Color::black;
                    x->parent->color = Color::red;
                    rightRotate(x->parent);
                    w = x->parent->lchild;
                }
                if (w->lchild->color == Color::black && w->rchild->color == Color::black)
                {
                    w->color = Color::red;
                    x = x->parent;
                }
                else
                {
                    if (w->lchild->color == Color::black) // w->rchild->color == Color::red
                    {
                        w->rchild->color = Color::black;
                        w->color = Color::red;
                        leftRotate(w);
                        w = x->parent->lchild;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Color::black;
                    w->lchild->color = Color::black;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = Color::black;
    }
};

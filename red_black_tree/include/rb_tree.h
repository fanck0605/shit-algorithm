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

private:
    Node* const nil = new Node{};
    Node* root = nil;

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
};

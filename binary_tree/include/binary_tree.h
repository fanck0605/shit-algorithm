#pragma once
#include <iostream>
#include <memory>
#include <utility>
#include <stack>
#include <queue>

template <typename DataType>
class BinaryTree
{
public:
    struct Node
    {
        DataType data;
        Node *lchild;
        Node *rchild;

        template <typename T>
        Node(T &&data = {}, Node *lchild = nullptr, Node *rchild = nullptr)
            : data(std::forward<T>(data)), lchild(lchild), rchild(rchild) {}

        template <typename T>
        void insertLeft(T &&data)
        {
            lchild = new Node(std::forward<T>(data));
        }

        template <typename T>
        void insertRight(T &&data)
        {
            rchild = new Node(std::forward<T>(data));
        }
    };

    template <typename Generator>
    void createTreePreOrder(Generator &&generate)
    {
        std::cout << "root: ";
        root = createTreePreOrderHelper(generate);
    }

    template <typename Visitor>
    void preOrderTraverse(const Visitor &visit)
    {
        preOrderTraverseHelper(root, visit);
    }

    template <typename Visitor>
    void inOrderTraverse(const Visitor &visit)
    {
        inOrderTraverseHelper(root, visit);
    }

    template <typename Visitor>
    void postOrderTraverse(const Visitor &visit)
    {
        postOrderTraverseHelper(root, visit);
    }

    template <typename Visitor>
    void preOrderTraverseNonRecursive(const Visitor &visit);

    template <typename Visitor>
    void inOrderTraverseNonRecursive(const Visitor &visit);

    template <typename Visitor>
    void postOrderTraverseNonRecursive(const Visitor &visit);

    template <typename Visitor>
    void levelOrderTraverse(const Visitor &visit);

private:
    Node *root = nullptr;

    template <typename Generator>
    static Node *createTreePreOrderHelper(Generator &&generate);

    template <typename Visitor>
    static void preOrderTraverseHelper(const Node *root, const Visitor &visit);

    template <typename Visitor>
    static void inOrderTraverseHelper(const Node *root, const Visitor &visit);

    template <typename Visitor>
    static void postOrderTraverseHelper(const Node *root, const Visitor &visit);
};

template <typename DataType>
template <typename Generator>
auto BinaryTree<DataType>::createTreePreOrderHelper(Generator &&generate) -> Node *
{
    std::unique_ptr<DataType> data = generate();

    if (!data)
        return nullptr;

    Node *current = new Node(*data);

    std::cout << "parent: " << current->data << " lchild: ";
    current->lchild = createTreePreOrderHelper(generate);

    std::cout << "parent: " << current->data << " rchild: ";
    current->rchild = createTreePreOrderHelper(generate);

    return current;
}

template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::preOrderTraverseHelper(const Node *root, const Visitor &visit)
{
    if (!root)
        return;

    visit(root->data);
    preOrderTraverseHelper(root->lchild, visit);
    preOrderTraverseHelper(root->rchild, visit);
}

template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::preOrderTraverseNonRecursive(const Visitor &visit)
{
    std::stack<Node *> s;
    Node *current = root;

    while (true)
    {
        if (current)
        {
            visit(current->data);
            s.push(current);
            current = current->lchild;
        }
        else
        {
            if (s.empty())
                break;

            current = s.top();
            s.pop();
            current = current->rchild;
        }
    }
}

template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::inOrderTraverseHelper(const Node *root, const Visitor &visit)
{
    if (!root)
        return;

    inOrderTraverseHelper(root->lchild, visit);
    visit(root->data);
    inOrderTraverseHelper(root->rchild, visit);
}

template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::inOrderTraverseNonRecursive(const Visitor &visit)
{
    std::stack<Node *> s;
    Node *current = root;

    while (true)
    {
        if (current)
        {
            s.push(current);
            current = current->lchild;
        }
        else
        {
            if (s.empty())
                break;

            current = s.top();
            s.pop();
            visit(current->data);
            current = current->rchild;
        }
    }
}

template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::postOrderTraverseHelper(const Node *root, const Visitor &visit)
{
    if (!root)
        return;

    postOrderTraverseHelper(root->lchild, visit);
    postOrderTraverseHelper(root->rchild, visit);
    visit(root->data);
}

// https://leetcode-cn.com/problems/binary-tree-postorder-traversal/solution/er-cha-shu-de-hou-xu-bian-li-by-leetcode-solution/
template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::postOrderTraverseNonRecursive(const Visitor &visit)
{
    Node *current = root;

    std::stack<Node *> s;
    Node *previous = nullptr;

    while (true)
    {
        while (current)
        {
            s.push(current);
            current = current->lchild;
        }

        if (s.empty())
            break;

        current = s.top();

        if (!current->rchild || current->rchild == previous)
        {
            s.pop();
            visit(current->data);
            previous = current;
            current = nullptr;
        }
        else
        {
            current = current->rchild;
        }
    }
}

template <typename DataType>
template <typename Visitor>
void BinaryTree<DataType>::levelOrderTraverse(const Visitor &visit)
{
    if (!root)
        return;

    std::queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        const Node *current = q.front();
        q.pop();

        if (current->lchild)
            q.push(current->lchild);
        if (current->rchild)
            q.push(current->rchild);

        visit(current->data);
    }
}

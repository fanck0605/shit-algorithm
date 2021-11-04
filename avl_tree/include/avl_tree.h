#include <utility>
#include <exception>

template <typename Data>
class AvlTree
{
public:
    struct Node
    {
        Data data{};

        Node* lchild = nullptr;
        Node* rchild = nullptr;

        size_t height = 1;

        void insertLeft(const Data& data)
        {
            lchild = new Node{ data };
        }

        void insertRight(const Data& data)
        {
            rchild = new Node{ data };
        }
    };

    Data min()
    {
        Node* current = root;

        if (!current)
        {
            throw std::runtime_error("empty tree!");
        }

        while (current->lchild)
        {
            current = current->lchild;
        }

        return current->data;
    }

    Data max()
    {
        Node* current = root;

        if (!current)
        {
            throw std::runtime_error("empty tree!");
        }

        while (current->rchild)
        {
            current = current->rchild;
        }

        return current->data;
    }

    template <typename Visitor>
    void inOrderTraverse(Visitor visit)
    {
        inOrderTraverseHelper(root, visit);
    }

    void insert(Data data) {
        root = insertHelper(root, data);
    }
private:
    Node* root = nullptr;

    template <typename Visitor>
    static void inOrderTraverseHelper(Node* parent, Visitor&& visit)
    {
        if (parent)
        {
            inOrderTraverseHelper(parent->lchild, visit);
            visit(parent->data);
            inOrderTraverseHelper(parent->rchild, visit);
        }
    }

    static int balanceFactor(Node* parent)
    {
        if (!parent)
        {
            return 0;
        }

        size_t leftHeight = nodeHeight(parent->lchild);
        size_t rightHeight = nodeHeight(parent->rchild);

        return leftHeight > rightHeight ? static_cast<int>(leftHeight - rightHeight) : -static_cast<int>(rightHeight - leftHeight);
    }

    static size_t nodeHeight(Node* node)
    {
        return node ? node->height : 0;
    }

    static size_t height(Node* root)
    {
        return std::max(nodeHeight(root->lchild), nodeHeight(root->rchild)) + 1;
    }

    static Node* rightRotate(Node* parent)
    {
        Node* newParent = parent->lchild; // the new parent

        parent->lchild = newParent->rchild;
        newParent->rchild = parent;

        parent->height = height(parent);
        newParent->height = height(newParent);

        return newParent;
    }

    static Node* leftRotate(Node* parent)
    {
        Node* newParent = parent->rchild;

        parent->rchild = newParent->lchild;
        newParent->lchild = parent;

        parent->height = height(parent);
        newParent->height = height(newParent);

        return newParent;
    }

    static Node* rebalance(Node* root)
    {
        auto factor = balanceFactor(root);

        if (factor > 1)
        {
            if (balanceFactor(root->lchild) > 0) // LL
            {
                return rightRotate(root);
            }
            else // LR
            {
                root->lchild = leftRotate(root->lchild);
                return rightRotate(root);
            }
        }
        else if (factor < -1)
        {
            if (balanceFactor(root->rchild) < 0) // RR
            {
                return leftRotate(root);
            }
            else // RL
            {
                root->rchild = rightRotate(root->rchild);
                return leftRotate(root);
            }
        }
        else
        {
            return root;
        }
    }

    static Node* insertHelper(Node* root, Data data)
    {
        if (!root)
        {
            return new Node{ data };
        }

        if (data < root->data)
        {
            root->lchild = insertHelper(root->lchild, data);
        }
        else if (data > root->data)
        {
            root->rchild = insertHelper(root->rchild, data);
        }
        else
        {
            return root;
        }

        root->height = height(root);

        return rebalance(root);
    }
};

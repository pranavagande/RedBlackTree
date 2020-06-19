#include <iostream>
#include <queue>

enum Color { RED, BLACK };

struct Node
{
    int key = -1;
    enum Color color = RED;
    Node* parent_ptr = nullptr;
    Node* left_ptr = nullptr;
    Node* right_ptr = nullptr;
};

class RedBlackTree
{
private:
    void double_black(Node* node)
    {
        root->color = BLACK;
        bool case1 = (node->parent_ptr == nullptr);
        if (case1)
        {
            return;
        }

        bool black_parent = (node->parent_ptr->color == BLACK);
        bool parent_right_ptr = (node->parent_ptr->right_ptr == node);

        bool case2 = false;
        if (parent_right_ptr && black_parent) // check if parent is black
        {
            if (node->parent_ptr->left_ptr->color == RED)
            {
                case2 = true;
            }
        }
        else if (black_parent)
        {
            if (node->parent_ptr->right_ptr->color == RED)
            {
                case2 = true;
            }
        }

        if (case2 && !parent_right_ptr)
        {
            if (node->parent_ptr == root)
            {
                root = node->parent_ptr->right_ptr;
            }
            node->parent_ptr->color = RED;
            node->parent_ptr->right_ptr->color = BLACK;
            node->parent_ptr->parent_ptr = node->parent_ptr->right_ptr;

            node->parent_ptr->right_ptr = node->parent_ptr->right_ptr->left_ptr;
            node->parent_ptr->right_ptr->parent_ptr->left_ptr = node->parent_ptr;
            node->parent_ptr->right_ptr->parent_ptr = node->parent_ptr;

            double_black(node);
            return;
        }
        else if (case2)
        {
            if (node->parent_ptr == root)
            {
                root = node->parent_ptr->left_ptr;
            }
            node->parent_ptr->color = RED;
            node->parent_ptr->left_ptr->color = BLACK;
            node->parent_ptr->parent_ptr = node->parent_ptr->left_ptr;

            node->parent_ptr->left_ptr = node->parent_ptr->left_ptr->right_ptr;
            node->parent_ptr->left_ptr->parent_ptr->right_ptr = node->parent_ptr;
            node->parent_ptr->left_ptr->parent_ptr = node->parent_ptr;

            double_black(node);
            return;
        }

        bool case3 = false;
        if (parent_right_ptr && black_parent)
        {
            if ((node->parent_ptr->left_ptr->left_ptr->color == BLACK && node->parent_ptr->left_ptr->right_ptr->color == BLACK)
                && node->left_ptr->color == BLACK)
            {
                case3 = true;
            }
        }
        else
        {
            if ((node->parent_ptr->right_ptr->right_ptr->color == BLACK && node->parent_ptr->right_ptr->left_ptr->color == BLACK)
                && node->parent_ptr->right_ptr->color == BLACK)
            {
                case3 = true;
            }
        }

        if (case3 && parent_right_ptr)
        {
            node->parent_ptr->left_ptr->color = RED;
            node = node->parent_ptr;
            if (node->parent_ptr == nullptr)
            {
                return;
            }

            double_black(node);
            return;
        }
        else if (case3)
        {
            node->parent_ptr->right_ptr->color = RED;
            node = node->parent_ptr;
            if (node->parent_ptr == nullptr)
            {
                return;
            }

            double_black(node);
            return;
        }

        bool case4 = false;
        if (!black_parent)
        {
            case4 = true;
        }

        if (case4 && parent_right_ptr)
        {
            node->parent_ptr->color = BLACK;
            node->parent_ptr->left_ptr->color = RED;
            return;
        }
        else if (case4)
        {
            node->parent_ptr->color = BLACK;
            node->parent_ptr->right_ptr->color = RED;
            return;
        }

        bool case5 = false;
        if (parent_right_ptr && black_parent)
        {
            if (node->parent_ptr->left_ptr->right_ptr != nullptr)
            {
                if (node->parent_ptr->left_ptr->color == BLACK && node->parent_ptr->left_ptr->right_ptr->color == RED)
                {
                    case5 = true;
                }
            }
        }
        else if (black_parent)
        {
            if (node->parent_ptr->right_ptr->left_ptr != nullptr)
            {
                if (node->parent_ptr->right_ptr->color == BLACK && node->parent_ptr->right_ptr->left_ptr->color == RED)
                {
                    case5 = true;
                }
            }
        }

        if (parent_right_ptr && case5)
        {
            node->parent_ptr->left_ptr->color = RED;
            node->parent_ptr->left_ptr->right_ptr->color = BLACK;
            node->parent_ptr->left_ptr->left_ptr->color = BLACK;

            node->parent_ptr->left_ptr = node->parent_ptr->left_ptr->right_ptr;
            node->parent_ptr->left_ptr->left_ptr = node->parent_ptr->left_ptr->parent_ptr;
            node->parent_ptr->left_ptr->left_ptr->right_ptr = nullptr;
            node->parent_ptr->left_ptr->parent_ptr = node->parent_ptr; 

            double_black(node);
            return;
        }
        else if (case5)
        {
            node->parent_ptr->right_ptr->color = RED;
            node->parent_ptr->right_ptr->left_ptr->color = BLACK;
            node->parent_ptr->right_ptr->right_ptr->color = BLACK;
            
            node->parent_ptr->right_ptr = node->parent_ptr->right_ptr->left_ptr;
            node->parent_ptr->right_ptr->right_ptr = node->parent_ptr->right_ptr->parent_ptr;
            node->parent_ptr->right_ptr->right_ptr->left_ptr = nullptr;
            node->parent_ptr->right_ptr->parent_ptr = node->parent_ptr;

            double_black(node);
            return;
        }
        
        bool case6 = false;
        if (parent_right_ptr)
        {
            if (node->parent_ptr->left_ptr->color == BLACK && node->parent_ptr->left_ptr->left_ptr->color == RED)
            {
                case6 = true;
            }
        }
        else
        {
            if (node->parent_ptr->right_ptr->color == BLACK && node->parent_ptr->right_ptr->right_ptr->color == RED)
            {
                case6 = true;
            }
        }

        if (case6 && parent_right_ptr)
        {
            if (node->parent_ptr == root)
            {
                root = node->parent_ptr->left_ptr;
            }

            node->parent_ptr->color = BLACK;
            node->parent_ptr->left_ptr->left_ptr->color = BLACK;

            Node* left = node->parent_ptr->left_ptr->left_ptr;
            if (node->parent_ptr->parent_ptr)
            {
                if (node->parent_ptr->parent_ptr->left_ptr == node->parent_ptr)
                {
                    node->parent_ptr->parent_ptr->left_ptr = node->parent_ptr->left_ptr;
                    node->parent_ptr->left_ptr->right_ptr = node->parent_ptr;
                }
                else
                {
                    node->parent_ptr->parent_ptr->right_ptr = node->parent_ptr->left_ptr;
                    node->parent_ptr->left_ptr->right_ptr = node->parent_ptr;
                }
            }
            node->parent_ptr->left_ptr->parent_ptr = node->parent_ptr->parent_ptr;
            node->parent_ptr->left_ptr->right_ptr = node->parent_ptr;
            node->parent_ptr->parent_ptr = node->parent_ptr->left_ptr;
            node->parent_ptr->left_ptr = left;

            return;
        }
        else if (case6)
        {
            if (node->parent_ptr == root)
            {
                root = node->parent_ptr->right_ptr;
            }

            node->parent_ptr->color = BLACK;
            node->parent_ptr->right_ptr->right_ptr->color = BLACK;

            Node* right = node->parent_ptr->right_ptr->right_ptr;
            if (node->parent_ptr->parent_ptr != nullptr)
            {
                if (node->parent_ptr->parent_ptr->left_ptr == node->parent_ptr)
                {
                    node->parent_ptr->parent_ptr->left_ptr = node->parent_ptr->right_ptr;
                    node->parent_ptr->right_ptr->left_ptr = node->parent_ptr;
                }
                else
                {
                    node->parent_ptr->parent_ptr->right_ptr = node->parent_ptr->right_ptr;
                    node->parent_ptr->right_ptr->right_ptr = node->parent_ptr;
                }
            }
            node->parent_ptr->right_ptr->parent_ptr = node->parent_ptr->parent_ptr;
            node->parent_ptr->right_ptr->left_ptr = node->parent_ptr;
            node->parent_ptr->parent_ptr = node->parent_ptr->right_ptr;
            node->parent_ptr->right_ptr = right;

            return;
        } 
    }

    void delete_sub(Node* delete_node, bool right_ptr_exists, bool left_ptr_exists)
    {
        if (delete_node->color == BLACK)
        {
            if (right_ptr_exists)
            {
                if (delete_node->right_ptr->color == RED)
                {
                    delete_node->right_ptr->color = BLACK;
                    delete_node->right_ptr->parent_ptr = delete_node->parent_ptr;
                    if (delete_node->parent_ptr->left_ptr == delete_node)
                    {
                        delete_node->parent_ptr->left_ptr = delete_node->right_ptr;
                    }
                    else
                    {
                        delete_node->parent_ptr->right_ptr = delete_node->right_ptr;
                    }
                }
                else
                {
                    double_black(delete_node);
                    delete_node->right_ptr->parent_ptr = delete_node->parent_ptr;
                    if (delete_node->parent_ptr->left_ptr == delete_node)
                    {
                        delete_node->parent_ptr->left_ptr = delete_node->right_ptr;
                    }
                    else
                    {
                        delete_node->parent_ptr->right_ptr = delete_node->right_ptr;
                    }
                }
            }
            else if (left_ptr_exists)
            {
                if (delete_node->left_ptr->color == RED)
                {
                    delete_node->left_ptr->color = BLACK;
                    delete_node->left_ptr->parent_ptr = delete_node->parent_ptr;
                    if (delete_node->parent_ptr->left_ptr == delete_node)
                    {
                        delete_node->parent_ptr->left_ptr = delete_node->left_ptr;
                    }
                    else
                    {
                        delete_node->parent_ptr->right_ptr = delete_node->left_ptr;
                    }
                }
                else
                {
                    double_black(delete_node);
                    delete_node->left_ptr->parent_ptr = delete_node->parent_ptr;
                    if (delete_node->parent_ptr->left_ptr == delete_node)
                    {
                        delete_node->parent_ptr->left_ptr = delete_node->left_ptr;
                    }
                    else
                    {
                        delete_node->parent_ptr->right_ptr = delete_node->left_ptr;
                    }
                }
            }
            else
            {
                double_black(delete_node);
            }
        }
    }

    void balance(Node* start_ptr)
    {
        Node* currentnode = start_ptr;

        bool right_red = true;
        bool left_red = true;
        bool right_right_red = true;
        bool right_left_red = true;
        bool left_left_red = true;
        bool left_right_red = true;

        while (currentnode->parent_ptr != nullptr)
        {
            while (currentnode->color != BLACK)
            {
                currentnode = currentnode->parent_ptr;
            }

            if (currentnode->right_ptr == nullptr)
            {
                right_red = false;
            }
            else if (currentnode->right_ptr->color == BLACK)
            {
                right_red = false;
            }

            if (currentnode->left_ptr == nullptr)
            {
                left_red = false;
            }
            else if (currentnode->left_ptr->color == BLACK)
            {
                left_red = false;
            }

            if (right_red && left_red) // checks if both red
            {
                // promotion - color flip
                currentnode->color = RED;
                currentnode->right_ptr->color = BLACK;
                currentnode->left_ptr->color = BLACK;
            }
            else if (right_red)
            {
                if (currentnode->right_ptr->right_ptr == nullptr)
                {
                    right_right_red = false;
                }
                else if (currentnode->right_ptr->right_ptr->color == BLACK)
                {
                    right_right_red = false;
                }

                if (currentnode->right_ptr->left_ptr == nullptr)
                {
                    right_left_red = false;
                }
                else if (currentnode->right_ptr->left_ptr->color == BLACK)
                {
                    right_left_red = false;
                }

                if (right_right_red)
                {

                    // rotation
                    Node* parent = currentnode->parent_ptr;
                    currentnode->color = RED;
                    currentnode->right_ptr->color = BLACK;
                    currentnode->right_ptr->left_ptr = currentnode;
                    currentnode->right_ptr->parent_ptr = parent;
                    if (root != currentnode)
                    {
                        if (currentnode->parent_ptr->left_ptr == currentnode)
                        {
                            currentnode->parent_ptr->left_ptr = currentnode->right_ptr;
                        }
                        else
                        {
                            currentnode->parent_ptr->right_ptr = currentnode->right_ptr;
                        }
                    }
                    currentnode->parent_ptr = currentnode->right_ptr;
                    currentnode->right_ptr = nullptr;
                }
                else if (right_left_red)
                {
                    // triangle
                    Node* parent = currentnode->parent_ptr;
                    currentnode->color = RED;
                    currentnode->right_ptr->left_ptr->color = BLACK;
                    currentnode->right_ptr->left_ptr->left_ptr = currentnode;
                    currentnode->right_ptr->left_ptr->parent_ptr = parent;
                    if (currentnode != root)
                    {
                        if (currentnode->parent_ptr->left_ptr = currentnode)
                        {
                            currentnode->parent_ptr->left_ptr = currentnode->right_ptr->left_ptr;
                        }
                        else
                        {
                            currentnode->parent_ptr->right_ptr = currentnode->right_ptr;
                        }
                    }
                    else
                    {
                        root = currentnode->right_ptr->left_ptr;
                    }
                    currentnode->parent_ptr = currentnode->right_ptr->left_ptr;
                    currentnode->right_ptr = nullptr;
                }
                if (currentnode->parent_ptr != nullptr)
                {
                    currentnode = currentnode->parent_ptr;
                }
            }
            else if (left_red)
            {

                if (currentnode->left_ptr->left_ptr == nullptr)
                {
                    left_left_red = false;
                }
                else if (currentnode->left_ptr->left_ptr->color == BLACK)
                {
                    left_left_red = false;
                }

                if (currentnode->left_ptr->right_ptr == nullptr)
                {
                    left_right_red = false;
                }
                else if (currentnode->left_ptr->right_ptr->color == BLACK)
                {
                    left_right_red = false;
                }

                // rotation
                if (left_left_red)
                {

                    Node* parent = currentnode->parent_ptr;
                    currentnode->color = RED;
                    currentnode->left_ptr->color = BLACK;
                    currentnode->left_ptr->right_ptr = currentnode;
                    currentnode->left_ptr->parent_ptr = parent;
                    if (root != currentnode)
                    {
                        if (currentnode->parent_ptr->left_ptr == currentnode)
                        {
                            currentnode->parent_ptr->left_ptr = currentnode->left_ptr;
                        }
                        else
                        {
                            currentnode->parent_ptr->right_ptr = currentnode->right_ptr;
                        }
                    }
                    else
                    {
                        root = currentnode->left_ptr;
                    }
                    currentnode->parent_ptr = currentnode->left_ptr;
                    currentnode->left_ptr = nullptr;
                }
                else if (left_right_red)
                {
                    /*
                    Node* parent = currentnode->parent_ptr;
                    currentnode->color = RED;
                    currentnode->right_ptr->left_ptr->color = BLACK;
                    currentnode->right_ptr->left_ptr->left_ptr = currentnode;
                    currentnode->right_ptr->left_ptr->parent_ptr = parent;
                    if (currentnode != root)
                    {
                        if (currentnode->parent_ptr->left_ptr = currentnode)
                        {
                            currentnode->parent_ptr->left_ptr = currentnode->right_ptr->left_ptr;
                        }
                        else
                        {
                            currentnode->parent_ptr->right_ptr = currentnode->right_ptr;
                        }
                    }
                    else
                    {
                        root = currentnode->right_ptr->left_ptr;
                    }
                    currentnode->parent_ptr = currentnode->right_ptr->left_ptr;
                    currentnode->right_ptr = nullptr;
                    */

                    Node* parent = currentnode->parent_ptr;
                    currentnode->color = RED;
                    currentnode->left_ptr->right_ptr->color = BLACK;
                    currentnode->left_ptr->right_ptr->right_ptr = currentnode;
                    currentnode->right_ptr->left_ptr->parent_ptr = parent;
                    if (currentnode != root)
                    {
                        if (currentnode->parent_ptr->left_ptr == currentnode)
                        {
                            currentnode->parent_ptr->left_ptr = currentnode->left_ptr->right_ptr;
                        }
                        else
                        {
                            currentnode->parent_ptr->right_ptr = currentnode->left_ptr->right_ptr;
                        }
                    }
                    else
                    {
                        root = currentnode->left_ptr->right_ptr;
                    }

                    currentnode->parent_ptr = currentnode->left_ptr->right_ptr;
                    currentnode->left_ptr = nullptr;
                }
            }
        }

        root->color = BLACK;
    }

public:
    Node* root = new Node;

    RedBlackTree(int new_key)
    {
        root->key = new_key;
        root->color = BLACK;
    }

    Node* search(int search_key) // returns pointer to node where it was found or if not there, node before nullptr
    {
        Node* currentnode = root;
        while (search_key != currentnode->key)
        {
            if (search_key > currentnode->key)
            {
                if (currentnode->right_ptr == nullptr)
                {
                    return currentnode;
                }
                currentnode = currentnode->right_ptr;
            }
            else if (search_key < currentnode->key)
            {
                if (currentnode->left_ptr == nullptr)
                {
                    return currentnode;
                }
                currentnode = currentnode->left_ptr;
            }
        }

        return currentnode;
    }

    struct Node* predecessor(int key)
    {
        Node* key_node = search(key);
        Node* currentnode;
        if (key_node->left_ptr != nullptr)
        {
            currentnode = key_node->left_ptr;
            while (currentnode->right_ptr != nullptr)
            {
                currentnode = currentnode->right_ptr;
            }
        }
        else
        {
            currentnode = key_node->parent_ptr;
            while (currentnode->key >= key)
            {
                currentnode = currentnode->parent_ptr;
            }
        }

        return currentnode;
    }

    void delete_key(int delete_key)
    {
        Node* node_key = search(delete_key);
        if (node_key->key != delete_key)
        {
            throw std::invalid_argument("Key not found");
        }

        if (node_key->left_ptr != nullptr && node_key->right_ptr != nullptr)
        {
            Node* predecessor_node = predecessor(delete_key);
            if (predecessor_node->left_ptr != nullptr)
            {
                delete_sub(predecessor_node, false, true);
            }
            else
            {
                delete_sub(predecessor_node, false, false);
            }

            if (node_key != root)
            {
                if (node_key->parent_ptr->left_ptr == node_key)
                {
                    node_key->parent_ptr->left_ptr = predecessor_node;
                }
                else
                {
                    node_key->parent_ptr->right_ptr = predecessor_node;
                }
            }

            if (predecessor_node->parent_ptr->left_ptr == predecessor_node)
            {
                predecessor_node->parent_ptr->left_ptr = nullptr;
            }
            else if (predecessor_node->parent_ptr->right_ptr == predecessor_node)
            {
                predecessor_node->parent_ptr->right_ptr = nullptr;
            }

            predecessor_node->parent_ptr = node_key->parent_ptr;
            predecessor_node->right_ptr = node_key->right_ptr;
            predecessor_node->left_ptr = node_key->left_ptr;
            if (node_key == root)
            {
                root = predecessor_node;
            }
            delete node_key;
        }
        else if (node_key->right_ptr != nullptr)
        {
            delete_sub(node_key, true, false);
            node_key->right_ptr->parent_ptr = node_key->parent_ptr;
            if (node_key != root)
            {
                if (delete_key > node_key->parent_ptr->key)
                {
                    node_key->parent_ptr->right_ptr = node_key->right_ptr;
                }
                else
                {
                    node_key->parent_ptr->left_ptr = node_key->right_ptr;
                }
            }
            else
            {
                root = node_key->right_ptr;
            }

            delete node_key;
        }
        else if (node_key->left_ptr != nullptr)
        {
            delete_sub(node_key, false, true);
            node_key->left_ptr->parent_ptr = node_key->parent_ptr;
            if (node_key != root)
            {
                if (delete_key > node_key->parent_ptr->key)
                {
                    node_key->parent_ptr->right_ptr = node_key->left_ptr;
                }
                else
                {
                    node_key->parent_ptr->left_ptr = node_key->left_ptr;
                }
            }
            else
            {
                root = node_key->left_ptr;
            }

            delete node_key;
        }
        else
        {
            delete_sub(node_key, false, false);
            if (node_key != root)
            {
                if (node_key->parent_ptr->left_ptr == node_key)
                {
                    node_key->parent_ptr->left_ptr = nullptr;
                }
                else
                {
                    node_key->parent_ptr->right_ptr = nullptr;
                }
            }
            delete node_key;
        }

        root->color = BLACK;
    }

    void insert(int new_key) // only inserts distinct keys - need to update
    {
        Node* prev = search(new_key);
        if (new_key >= prev->key)
        {
            prev->right_ptr = new Node;
            prev->right_ptr->parent_ptr = prev;
            prev->right_ptr->color = RED;
            prev->right_ptr->key = new_key;
            if (prev->color == RED)
            {
                balance(prev->right_ptr);
            }
        }
        else
        {
            prev->left_ptr = new Node;
            prev->left_ptr->parent_ptr = prev;
            prev->left_ptr->color = RED;
            prev->left_ptr->key = new_key;
            if (prev->color == RED)
            {
                balance(prev->left_ptr);
            }
        }

    }

    void RecursiveDestructor(Node* node)
    {
        if (node->left_ptr != nullptr)
        {
            RecursiveDestructor(node->left_ptr);
        }
        
        if (node->right_ptr != nullptr)
        {
            RecursiveDestructor(node->right_ptr);
        }

        delete node;
    }

    ~RedBlackTree() // need to implement rule of three
    {
        RecursiveDestructor(root);
    }
};

void BFS(RedBlackTree &tree) // to print out contents of tree
{
    std::queue<Node*> myq;
    Node* i = tree.root;
    myq.push(nullptr);
    bool push_null = true;
    while (true)
    {
        if (i == nullptr)
        {
            std::cout << '\n';
            push_null = false;
        }
        else
        {
            std::cout << i->key;
            std::cout << i->color;
            std::cout << " ";

            if (i->left_ptr != nullptr && i->right_ptr != nullptr)
            {
                myq.push(i->left_ptr);
                myq.push(i->right_ptr);
            }
            else if (i->left_ptr != nullptr)
            {
                //std::cout << "\n";
                myq.push(i->left_ptr);
            }
            else if (i->right_ptr != nullptr)
            {
                //std::cout << "\n";
                myq.push(i->right_ptr);
            }
        }

        if (myq.empty())
        {
            break;
        }
        i = myq.front();
        myq.pop();
        if (push_null)
        {
            myq.push(nullptr);
        }
        push_null = true;
    }
}

int main()
{
    
    RedBlackTree tree(7);
    tree.insert(3);
    tree.insert(1);
    tree.insert(9);
    tree.insert(10);
    tree.insert(4);

    tree.delete_key(7);

    BFS(tree);

    std::cin.get();
    return 0;
}

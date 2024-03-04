template<typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, T item) {
        if (node == nullptr) {
            return new Node<T>(item);
        }

        if (item < node->getItem()) {
            node->setNext(insert(node->getNext(), item));
        }
        else if (item > node->getItem()) {
            node->setNext(insert(node->getNext(), item));
        }

        return node;
    }

    Node<T>* removeById(Node<T>* node, int id) {
        if (node == nullptr) {
            return nullptr;
        }

        if (id < node->getItem()->getID()) {
            node->setNext(removeById(node->getNext(), id));
        }
        else if (id > node->getItem()->getID()) {
            node->setNext(removeById(node->getNext(), id));
        }
        else {
            if (node->getNext() == nullptr) {
                Node<T>* temp = node->getNext();
                delete node;
                return temp;
            }
            else if (node->getNext() == nullptr) {
                Node<T>* temp = node->getNext();
                delete node;
                return temp;
            }

            Node<T>* successor = findMin(node->getNext());
            node->setItem(successor->getItem());
            node->setNext(removeById(node->getNext(), successor->getItem()->getID()));
        }

        return node;
    }

    Node<T>* findMin(Node<T>* node) {
        while (node->getNext() != nullptr) {
            node = node->getNext();
        }
        return node;
    }

    Node<T>* getMin(Node<T>* node, T& minItem) {
        while (node->getNext() != nullptr) {
            node = node->getNext();
        }
        minItem = node->getItem();
        return node;
    }
    Node<T>* remove(Node<T>* node, T item) {
        if (node == nullptr) {
            return nullptr;
        }

        if (item < node->getItem()) {
            node->setNext(remove(node->getNext(), item));
        }
        else if (item > node->getItem()) {
            node->setNext(remove(node->getNext(), item));
        }
        else {
            if (node->getNext() == nullptr) {
                Node<T>* temp = node->getNext();
                delete node;
                return temp;
            }
            else if (node->getNext() == nullptr) {
                Node<T>* temp = node->getNext();
                delete node;
                return temp;
            }

            Node<T>* successor = findMin(node->getNext());
            node->setItem(successor->getItem());
            node->setNext(remove(node->getNext(), successor->getItem()));
        }

        return node;
    }

public:
    BST() : root(nullptr) {}

    void insert(T item) {
        root = insert(root, item);
    }

    void removeById(int id) {
        root = removeById(root, id);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void getMin(T& minItem) {
        if (!isEmpty()) {
            getMin(root, minItem);
        }
    }

    void remove(T item) {
        root = remove(root, item);
    }

    // Add other BST operations as needed
};

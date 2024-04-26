#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>

/**
 * @brief Класс Бинарного дерева
 *

 * Класс имеет следуюшие поля:
 * \tparam Node - узел дерева, содержащий в себе ключ-значение, количество значений, которые находятся под одним ключом и указетли на левого и правого потомка
 * \tparam root - вершина дерева
 */
template <typename T, typename U>
class BinaryTree {
private:
    struct Node {
        T key;
        U data[10000]; //10 for nodes with equal keys
        int count;
        Node* left;
        Node* right;

        Node(T key, U data) : key(key), count(0), left(nullptr), right(nullptr) {
            this->data[count++] = data;
        }
    };

    /** \brief Функция для очистки паямяти, выделяемой для дерева
     *
     * Вызывает другую функцию, которая очищает память
     */
    void clear() { clear_tree(root); }

    /** \brief Функция для рекурсивной очистки дерева
     *
     * @param node - узел, который нужно удалить
     */
    void clear_tree(Node* node);

public:
    Node* root;

    /** \brief Стандартный конструктор класса
     *
     * Инициализирует поле root, как указатель на NULL
     */
    BinaryTree() : root(nullptr) {
    }

    /** \brief Стандартный деструктор класса
     *
     * Вызывает приватную функуию clear()
     */
    ~BinaryTree() { clear(); }

    /** \brief Функция вставки очередного узла в дерево
     *
     * @param node - узел от которого нужно искать место для вставки
     * @param key - ключ элемента
     * @param data - значение элемента
     */
    void insert_node(Node*& node, T key, U data);

    /** \brief Функция поиска элемента по ключу
     *
     * @param node - узел, от которого нужно искать элемент
     * @param key  - ключ элемента
     * @return Массив элементов, лежащих под нужным ключом
     */
    U* find_node(Node* node, T key);

    /** \brief Функция для печати дерева на экран
     *
     * @param node - узел, с которого нужно печатать
     * @param depth - (необязательный) - глубина печати дерева
     */
    void print_tree(Node* node, int depth = 0);
};

template <typename T, typename U>
void BinaryTree<T, U>::insert_node(Node*& node, T key, U data) {
    if (node == nullptr) {
        node = new Node(key, data);
        if (root == nullptr) root = node;
    } else if (node->key == key)
        node->data[node->count++] = data;
    else if (key < node->key)
        insert_node(node->left, key, data);
    else
        insert_node(node->right, key, data);
}

template <typename T, typename U>
U* BinaryTree<T, U>::find_node(Node* node, T key) {
    U* result = nullptr;
    while (node != nullptr) {
        if (node->key == key) {
            result = node->data;
            break;
        } else if (key < node->key)
            node = node->left;
        else
            node = node->right;
    }
    return result;
}

template <typename T, typename U>
void BinaryTree<T, U>::print_tree(Node* node, int depth) {
    if (node != nullptr) {
        print_tree(node->right, depth + 1);
        for (int i = 0; i < depth; ++i)
            std::cout << "    "; // Indent based on depth
        std::cout << node->key << std::endl;
        print_tree(node->left, depth + 1);
    }
}

template <typename T, typename U>
void BinaryTree<T, U>::clear_tree(Node* node) {
    if (node != nullptr) {
        clear_tree(node->left);
        clear_tree(node->right);
        delete node;
    }
    root = nullptr;
}


#endif //BINARYTREE_H

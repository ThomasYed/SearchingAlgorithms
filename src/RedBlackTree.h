#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include <iostream>

/**
 * @brief Класс Красно-черного дерева
 *
 * Правила, по которым работает дерево:
 * 1) У листа всегда есть потомок 'NULL' узел
 * 2) Корень и null листья всегда черные
 * 3) У каждого красного узла оба потомка черные
 * 4) Одинаковая черная высота - количество черных узлов от корня до любого 'NULL'
 * 5) Каждый новый узел красный, после вставки - балансируем
 *
 * Правила, по которым балансируется дерево после каждой вставки:
 * Крайние случаи
 * 0 случай: родитель черный => балансировка не нужна
 * 1 случай: родителя нет (т.е. узел – корень) => просто перекрашиваем в черный

 * Если дядя красный
 * 2 случай: дед не корень => перекрашиваем родителя и дядю в черный, а деда - в красный
 * 3 случай: дед корень => перекрашиваем родителя и дядю в черный (корень не считается в высоте, все осталось ок, поэтому выполняем 2 случай)

 * Если дядя черный
 * 4 случай: "зиг-заг" (дед и отец не на одной линии) => левый поворот относительно отца
 * 5 случай: дед и отец на одной линии => отца красим в черный, деда - в красный, правый поворот относительно деда
 *
 * Класс имеет следуюшие поля:
 * \tparam Node - узел дерева, содержащий в себе цвет, ключ-значение, количество значений, которые находятся под одним ключом и указетли на родителя, левого и правого потомка
 * \tparam root - вершина дерева
 * \tparam nil - нуль-элемент, который вешается на крайние листья
 */

template <typename T, typename U>
class RedBlackTree {
private:
    struct Node {
        T key;
        U data[10000]; //10 for nodes with equal keys
        int count;
        char color;
        Node* parent;
        Node* left;
        Node* right;

        explicit Node(char color): count(0), parent(nullptr), left(nullptr), right(nullptr) {
            this->color = 'b';
        }

        Node(char color, T key, U data, Node* p, Node* left,
             Node* right) : key(key), count(0),
                            parent(p), left(left),
                            right(right) {
            this->color = color;
            this->data[count++] = data;
        }
    };

    /** \brief Приватная функция балансировки дерева, которая вызывается, после каждой вставки
     *
     * @param node - узел, с которого нужно начать балансировку
     */
    void fix_insert(Node* node);

    /** \brief Левый поворот дерева относительно определённого узла
     *
     * @param node - узел, относительно которого нужно сделать поворот
     */
    void left_rotate(Node* node);

    /** \brief Правый поворот дерева относительно определённого узла
     *
     * @param node - узел, относительно которого нужно сделать поворот
     */
    void right_rotate(Node* node);

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
    Node* nil;

    /** \brief Стандартный конструктор класса
     *
     * Инициализирует специальную NULL-переменную (NULL-лист)
     * Переменная root инициализируется также
     */
    RedBlackTree() {
        nil = new Node('b');
        root = nil;
    }

    /** \brief Стандартный деструктор класса
     *
     * Вызывает приватный методы clear() и очищает память, выделенную под nil
     */
    ~RedBlackTree() {
        clear();
        delete nil;
    }

    /** \brief Функция вставки очередного узла в дерево
     *
     * @param key - ключ элемента
     * @param data - значение элемента
     */
    void insert_node(T key, U data);

    /** \brief Функция поиска элемента по ключу
     *
     * @param node - узел, от которого необходимо искать элемент
     * @param key - ключ элемента
     * @return Массив элементов, лежащих под определённым ключом
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
void RedBlackTree<T, U>::insert_node(T key, U data) {
    Node* current = root;
    Node* parent = nullptr;
    while (current != nil && current->key != key) {
        parent = current;
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (current->key == key)
        current->data[current->count++] = data;
    else {
        Node* new_node = new Node('r', key, data, parent, nil, nil);
        if (parent == nullptr)
            root = new_node;
        else if (key < parent->key)
            parent->left = new_node;
        else
            parent->right = new_node;
        fix_insert(new_node);
    }
}

template <typename T, typename U>
void RedBlackTree<T, U>::left_rotate(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    if (right->left != nil)
        right->left->parent = node;
    right->parent = node->parent;
    if (node->parent == nullptr)
        root = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}

template <typename T, typename U>
void RedBlackTree<T, U>::right_rotate(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    if (left->right != nil)
        left->right->parent = node;
    left->parent = node->parent;
    if (node->parent == nullptr)
        root = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}

template <typename T, typename U>
void RedBlackTree<T, U>::fix_insert(Node* node) {
    while (node->parent != nullptr && node->parent->color == 'r') {
        if (node->parent == node->parent->parent->left) {
            Node* uncle = node->parent->parent->right;
            if (uncle->color == 'r') {
                uncle->color = 'b';
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    left_rotate(node);
                }
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                right_rotate(node->parent->parent);
            }
        } else {
            Node* uncle = node->parent->parent->left;
            if (uncle->color == 'r') {
                uncle->color = 'b';
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    right_rotate(node);
                }
                node->parent->color = 'b';
                node->parent->parent->color = 'r';
                left_rotate(node->parent->parent);
            }
        }
    }
    root->color = 'b';
}

template <typename T, typename U>
U* RedBlackTree<T, U>::find_node(Node* node, T key) {
    U* result = nullptr;
    while (node != nil) {
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
void RedBlackTree<T, U>::print_tree(Node* node, int depth) {
    if (node != nullptr) {
        print_tree(node->right, depth + 1);
        for (int i = 0; i < depth; ++i)
            std::cout << "    "; // Indent based on depth
        std::cout << node->key << std::endl;
        print_tree(node->left, depth + 1);
    }
}

template <typename T, typename U>
void RedBlackTree<T, U>::clear_tree(Node* node) {
    if (node != nil) {
        clear_tree(node->left);
        clear_tree(node->right);
        delete node;
    }
    root = nullptr;
}


#endif //REDBLACKTREE_H
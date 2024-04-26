#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <list>

/**
 * @brief Класс хеш-таблицы
 *

 * Класс имеет следуюшие поля:
 * \tparam table - таблица: массив связных списков, несущих в себе пару ключ-значение
 * \tparam count - количество занятых ячеек
 * \tparam size - общий объем таблицы
 */
template <typename T, typename U>
class HashTable {
private:
    std::list<std::pair<T, U>>* table;
    int count;
    int size;

    /** \brief Приватная функция хеширования
     *
     * Хеширует строки с помощью биномальной суммы, приведённой по модулю размера таблицы
     */
    size_t hash(T key);

public:
    /** \brief Стандартный конструктор класса
     *
     * Конструктор динамически выделяет память необходимого размера
     *
     * @param size - указывает на необходимый размер таблицы
     */
    explicit HashTable(int size);

    /**\brief Стандартный деструктор класса
     *
     *Очищает всю память, выделяемую для таблицы
     */
    ~HashTable();

    /** \brief Функция вставки элемента по паре ключ-значение
     *
     * @param key - ключ элемента
     * @param data - значение элемента
     */
    void insert(T key, U data);

    /** \brief Функция поиска элемента по ключу
     *
     * @param key - ключ, который необходимо найти
     * @return Массив найденных значений, принадлежащих одному ключу
     */
    U* find(T key);
};

template <typename T, typename U>
size_t HashTable<T, U>::hash(T key) {
    size_t hashsum = 0;
    for (int i = 0; i < key.size(); i++) {
        hashsum += (key[i] * static_cast<int>(pow(31, i))) % size;
    }
    return hashsum % size;
}

template <typename T, typename U>
HashTable<T, U>::HashTable(int size): count(0), size(size) {
    table = new std::list<std::pair<T, U>>[size];
}

template <typename T, typename U>
HashTable<T, U>::~HashTable() {
    delete[] table;
}

template <typename T, typename U>
void HashTable<T, U>::insert(T key, U data) {
    if (count == size)
        std::cerr << "Table is full" << std::endl;
    else {
        size_t i = hash(key);
        bool ifempty = table[i].size() == 0;
        if (ifempty || table[i].front().first != key) {
            table[i].push_back(make_pair(key, data));
            if (ifempty)
                count++;
        }
    }
}

template <typename T, typename U>
U* HashTable<T, U>::find(T key) {
    U* result = nullptr;
    size_t i = hash(key);
    for (auto item : table[i])
        if (item.first == key)
            result = &item.second;
    return result;
}

#endif //HASHTABLE_H

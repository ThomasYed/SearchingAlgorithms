#include "BinaryTree.h"
#include "HashTable.h"
#include "RedBlackTree.h"
#include "exportGoods.h"
#include <ctime>
#include <fstream>
#include <map>

/** \brief Устанавливает количество строк, которые будут прочитаны из файла
 */
#define N 100055
/** \brief Устанавливает, сколько измерений необходимо прозвести (число от 0 до 9)
 */
#define cycle 12
/** \brief Устанавливает, сколько поисков необходимо прозвести
 */
#define FIND 100

/**
 * \brief Основная функция в программе
 * \return ноль, если программа завершилась успешно
 */
int main() {
    /**В начале программы создаётся вектор data, в который считается весь файл.
     * \code
     * std::vector<Goods> data;
     * \endcode
     */
    std::vector<Goods> data;
    std::ifstream file("data.txt", std::ios::in);
    if (file.is_open()) {
        int i = 0;
        std::string temp;
        std::getline(file, temp);
        while (i < N) {
            std::string name, country, q_temp, p_temp;
            std::getline(file, name, ';');
            std::getline(file, country, ';');
            std::getline(file, q_temp, ';');
            std::getline(file, p_temp, '\n');
            int quant = std::stoi(q_temp);
            int price = std::stoi(p_temp);
            /** Стоит обратить внимание, что данные помещаются в вектор с помощью emplace_back, дабы избежать
             * излишнего копирования \code data.emplace_back(name, country, quant, price); \endcode
             */
            data.emplace_back(name, country, quant, price);
            i++;
        }
    } else {
        std::cerr << "error";
    }
    file.close();
    std::cout << "The file has succesfully readed" << std::endl;

    /** Для проведения измерений задаётся статически массив, в котором записано количество элементов, которые
     * будут учавствовать в сортировке на каждом конкретном замере
     * \code
     * int sizes[9] = {100, 500, 1000, 2000, 5000, 10000, 20000, 50000, 100050};
     * \endcode
     */
    int sizes[12] = {50, 100, 500, 1000, 1500, 2000, 5000, 10000, 20000, 30000, 50000, 100050};
    /** До начала замеров, открывается файл datagraph.txt на запись, в который запишутся данные для
     * дальнейшего построения графиков некоторыми средствами визуализации данных
     * \code
     * std::ofstream graph("datagraph.txt");
     * \endcode
     */
    std::ofstream graph("datagraph.txt");
    std::ofstream graphmmap("mmapdata.txt");
    for (int size : sizes) graph << size << " ";
    double bindata[cycle], hashdata[cycle], RBdata[cycle], multidata[cycle];

    for (int i = 0; i < cycle; i++) {
        int n = sizes[i];
        std::cout << n << " elements\n";
        std::vector<Goods> check(data.begin() + 1801, data.begin() + 1801 + FIND + 1);

        BinaryTree<std::string, Goods> btree;
        for (size_t j = 0; j < n; j++) {
            btree.insert_node(btree.root, data[j].getName(), data[j]);
        }
        clock_t start = clock();
        for (size_t j = 0; j < FIND; j++)
            btree.find_node(btree.root, check[j].getName());
        clock_t end = clock();
        double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "BinaryTree finished search at: " << seconds << " sec" << std::endl;
        bindata[i] = seconds;

        HashTable<std::string, Goods> hasht(n);
        for (size_t j = 0; j < n; j++) {
            hasht.insert(data[j].getName(), data[j]);
        }
        start = clock();
        for (size_t j = 0; j < FIND; j++)
            hasht.find(check[j].getName());
        end = clock();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "HashTble finished search at: " << seconds << " sec" << std::endl;
        hashdata[i] = seconds;

        RedBlackTree<std::string, Goods> rbtree;
        for (size_t j = 0; j < n; j++) {
            rbtree.insert_node(data[j].getName(), data[j]);
        }
        start = clock();
        for (size_t j = 0; j < FIND; j++)
            rbtree.find_node(rbtree.root, check[j].getName());
        end = clock();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "RedBlackTree finished search at: " << seconds << " sec" << std::endl;
        RBdata[i] = seconds;

        std::multimap<std::string, Goods> mmap;
        for (size_t j = 0; j < n; j++) {
            mmap.insert(std::pair(data[j].getName(), data[j]));
        }
        start = clock();
        for (size_t j = 0; j < FIND; j++)
            mmap.find(data[j].getName());
        end = clock();
        seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;
        std::cout << "MultiMap finished search at: " << seconds << " sec" << std::endl;
        multidata[i] = seconds;

        std::cout << std::endl;
    }
    graph << "\n";
    for (double sec : bindata) graph << sec << " ";
    graph << "\n";
    for (double sec : hashdata) graph << sec << " ";
    graph << "\n";
    for (double sec : RBdata) graph << sec << " ";
    graph << std::endl;
    graph.close();

    for (double sec : multidata) graphmmap << sec << " ";
    graphmmap << std::endl;
    graphmmap.close();
    return 0;
}

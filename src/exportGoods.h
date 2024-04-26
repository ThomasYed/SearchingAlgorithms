#ifndef EXPORTGOODS_H
#define EXPORTGOODS_H
#include <iomanip>
#include <iostream>
#include <string>

/**
 * @brief Класс продуктов, поставляемых на экспорт
 *
 * Класс, объекты которого будут подвергнуты различным сортировкам в соответствии с заданием.
 * Класс имеет следуюшие поля:
 * \tparam prod_name - Название товара
 * \tparam export_country - Страна, в которую экспортируются товары
 * \tparam quant - Количество товаров
 * \tparam price - Цена за партию товара
 */

class Goods {
   private:
    std::string prod_name;
    std::string export_country;
    int quant, price;

   public:
    /** \brief Стандартный конструктор без параметров
     *
     *Проставляет всем полям класса "нулевые" значения
     */
    Goods();

    /** \brief Стандартный конструктор копирования
     *
     * Все поля good копируются в новый объект класса Good
    \param good - объект подлежащий копированию
    */
    Goods(const Goods& good) = default;

    /** \brief Стандартный конструктор c параметрами
     * \param name - имя товара
     * \param country - страна экспорта
     * \param quant - количество товара
     * \param price - цена товара
     */
    Goods(std::string name, std::string country, int quant, int price);

    /** \brief Стандартный деструктор */
    ~Goods() = default;

    /**
     * \brief Get-тер для значения поля prod_name
     * \return Значения поля prod_name - название товара
     */
    std::string getName() const { return prod_name; }

    /** \brief Get-тер для значения поля export_country
     * \return Значение поля export_country - страну экспорту
     */
    std::string getCountry() const { return export_country; }

    /**
     * \brief Get-тер для значения поля quant
     * \return Значения поля quant - количество товара
     */
    int getQuant() const { return quant; }

    /**
     * \brief Get-тер для значения поля price
     * \return Значения поля price - цену товара
     */
    int getPrice() const { return price; }

    /** \brief Оператор сравнения <
     *
     * Сравнивает по полям: название товара, его количество, страна экспорта
     * Сравнение происходит по убыванию приоритета
     * \param good - правый операнд
     * \return true либо false в зависимости от результата сравнения
     */
    bool operator<(const Goods& good) const;

    /** \brief Оператор сравнения >
     *
     * Сравнивает по полям: название товара, его количество, страна экспорта
     * Сравнение происходит по убыванию приоритета
     * \param good - правый операнд
     * \return  true либо false в зависимости от результата сравнения
     */
    bool operator>(const Goods& good) const;

    /** \brief Оператор сравнения >=
     *
     * Сравнивает по полям: название товара, его количество, страна экспорта
     * Сравнение происходит по убыванию приоритета
     * \param good - правый операнд
     * \return  true либо false в зависимости от результата сравнения
     */
    bool operator>=(const Goods& good) const;

    /** \brief Оператор сравнения <=
     *
     * Сравнивает по полям: название товара, его количество, страна экспорта
     * Сравнение происходит по убыванию приоритета
     * \param good - правый операнд
     * \return true либо false в зависимости от результата сравнения
     */
    bool operator<=(const Goods& good) const;

    /** \brief Стандартный оператор  =
     *
     * Позволяет присваивать объекта класса друг к другу (копировать)
     */
    Goods& operator=(const Goods& good) = default;
};

/** \brief Перегруженный оператор вставки потока <<
 *
 * Позволяет эффективно выводить все поля класса ввиде форматированной строки
 */
std::ostream& operator<<(std::ostream& out, const Goods& good);

#endif  // EXPORTGOODS_H

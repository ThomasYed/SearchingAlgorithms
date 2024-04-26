#include "exportGoods.h"

Goods::Goods() {
    this->prod_name = "";
    this->export_country = "";
    this->quant = 0;
    this->price = 0;
}

Goods::Goods(std::string name, std::string country, int quant, int price) {
    this->prod_name = std::move(name);
    this->export_country = std::move(country);
    this->quant = quant;
    this->price = price;
}

bool Goods::operator<(const Goods& good) const {
    if (this->prod_name < good.prod_name) return true;
    if (this->prod_name > good.prod_name) return false;

    if (this->quant < good.quant) return true;
    if (this->quant > good.quant) return false;

    if (this->export_country < good.export_country) return true;
    return false;
}

bool Goods::operator>(const Goods& good) const {
    if (this->prod_name > good.prod_name) return true;
    if (this->prod_name < good.prod_name) return false;

    if (this->quant > good.quant) return true;
    if (this->quant < good.quant) return false;

    if (this->export_country > good.export_country) return true;
    return false;
}

bool Goods::operator>=(const Goods& good) const {
    if (this->prod_name > good.prod_name) return true;
    if (this->prod_name < good.prod_name) return false;

    if (this->quant > good.quant) return true;
    if (this->quant < good.quant) return false;

    if (this->export_country < good.export_country) return false;
    return true;
}

bool Goods::operator<=(const Goods& good) const {
    if (this->prod_name < good.prod_name) return true;
    if (this->prod_name > good.prod_name) return false;

    if (this->quant < good.quant) return true;
    if (this->quant > good.quant) return false;

    if (this->export_country > good.export_country) return false;
    return true;
}

std::ostream& operator<<(std::ostream& out, const Goods& good) {
    out << std::setw(39) << std::left << good.getName() << " " << std::setw(15) << std::left
        << good.getCountry() << " " << good.getQuant() << " " << good.getPrice();
    return out;
}

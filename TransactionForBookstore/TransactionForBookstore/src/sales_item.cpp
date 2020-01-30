#include "sales_item.h"

sales_item::sales_item(): sale_count(0), price(0)
{
	sale_count = 0;
	price = 0;
}

sales_item::sales_item(int count, double price, string isbn){
	this->sale_count = count;
	this->price = price;
	this->isbn = isbn;
}

bool sales_item::IsSameItem(const sales_item& item) const {
	return this->isbn == item.isbn;
}

bool sales_item::operator==(const sales_item& item) {
	return this->isbn == item.isbn;
}

/*
 *define the function of class member, class_name:: must be used
 *
*/
bool sales_item::operator!=(const sales_item& item) {
	return this->isbn != item.isbn;
}

#ifndef COUT_IS_MEMBER 
ostream& operator<<(ostream& out, const sales_item& item) {
	out << item.isbn << "  " << item.price << endl;
	return out;
}
#else /*defined COUT_IS_MEMBER*/

ostream& sales_item::operator<<(ostream& os) {
	os << this->isbn << endl;
	return os;
}
#endif /*COUT_IS_MEMBER*/

sales_item& sales_item::operator+=(const sales_item& item)
{
	this->sale_count += item.sale_count;
	return *this;
}
#include "item_base.h"
#include <iostream>

/*virtual is not used for function definition*/
double item_base:: net_price(size_t n) const
{
	return price * n;
}

void item_base::print_total(ostream& os, const item_base& item, size_t n)
{
	os << "ISBN:  " << item.book() << "\tnumber sold: " << n << "\ttotal price: "
		<< item.net_price(n) << endl;
}

double bulk_item::net_price(size_t n) const
{
	if (n <= min_qty)
		return n * (1 - discount) * price;
	else
		return n * price;

}

void bulk_item::memfcn(const bulk_item& d, const item_base& b)
{
	double ret = price;
	ret = d.price;
	//ret = b.price; //error, price is mermber of base class object
}

void test_print(item_base *pbase_ref) {
	pbase_ref->print(cout);
}

int main(int argc, char* argv[])
{
	item_base base;
	bulk_item bulk;

	item_base& base_ref(bulk);

	base.print(cout);
	bulk.print();
	base_ref.print(cout);

	return 0;
}
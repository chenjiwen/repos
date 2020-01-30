#pragma once
#ifndef __ITEM_BASE_H__
#define __ITEM_BASE_H__

#include <string>
#include <iostream>
using namespace std;

class item_base
{
public:

	item_base(const string& book = " ", double sales_price = 0.0) :isbn(book), price(sales_price) {}
	string book() const 
	{ 
		return isbn; 
	}

	void print_total(ostream& os, const item_base& item, size_t n);

	virtual void print(ostream& os) {
		os << "base" << endl;
		//os << isbn;
	}

	/*
	* keyword virtual can be only used for function declaration.
	*/
	virtual double net_price(size_t n) const;

	~item_base();

private:
	string isbn;/*can't be accessed by anything else except member function*/

protected:
	/*drived class can access but other users can't access*/
	double price;

};

class bulk_item : public item_base {
public:
	void  memfcn(const bulk_item &d, const item_base& b);
	virtual double net_price(size_t n) const;
	void print() {
		//print(ostream & os);
		//os << " " << discount;
		cout << "derived class: bulk_item->print" << endl;
		//cout << discount << endl;
	}
	double net_price(size_t n);/*function overloading based on const*/
	string book() const {
		return "derived + isbn";
	}
private:
	size_t min_qty;
	double discount;
};

item_base::~item_base()
{
}

#endif /*__ITEM_BASE_H__*/
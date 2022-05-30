#pragma once
#include <vector>
#include <string>
#include "Product.h"
using namespace std;
class Order
{
private:
	string id;
	float totalPrice = 0;
	string date;
	string customerId;
	bool isActivated = false;
	vector<Product>orderProducts;

public:
	bool operator< (const Order& right) const
	{
		return date < right.date;
	}
	Order();
	~Order();
	void setId(string id);
	void addProductToOrder(Product product);
	void setTotalPrice(float totalPrice);
	void setDate(string date);
	void setCustomerId(string customerId);
	void setIsActivated(bool value);
	void setOrderProducts(vector<Product> products);

	string getId();
	vector<Product>getOrderProducts();
	float getTotalPrice();
	string getDate();
	string getCustomerId();
	bool getIsActivated();
	string toString();
};


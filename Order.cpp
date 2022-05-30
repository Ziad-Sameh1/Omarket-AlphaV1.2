#include "Order.h"
#include "Utils.h"

Order::Order() {};
Order::~Order() {};

void Order::setId(string id) {
	this->id = id;
}

void Order::addProductToOrder(Product product) {
	orderProducts.push_back(product);
};

void Order::setTotalPrice(float totalPrice) {
	this->totalPrice = totalPrice;
};

void Order::setDate(string date) {
	this->date = date;
};

void Order::setCustomerId(string customerId) {
	this->customerId = customerId;
};

void Order::setIsActivated(bool value) {
	this->isActivated = isActivated;
}
void Order::setOrderProducts(vector<Product> products)
{
	this->orderProducts = products;
}
;

string Order::getId() {
	return this->id;
}

vector<Product> Order::getOrderProducts() {
	return this->orderProducts;
}

float Order::getTotalPrice() {
	return this->totalPrice;
}

string Order::getDate() {
	return this->date;
}

string Order::getCustomerId() {
	return this->customerId;
}

bool Order::getIsActivated() {
	return this->isActivated;
}

string Order::toString() {
	Utils* utils = Utils::getInstance();
	return "\n*********************************\nOrder Id: " + id + "\nTotal Price: " + to_string(totalPrice) + "\nDate: " + date + "\nIs Working: " + to_string(isActivated) + "\n*********************************";
}



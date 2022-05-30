#include "Cart.h"
#include "Utils.h"

Cart::Cart() {};
Cart::~Cart() {};

void Cart::setUserId(string id) {
	this->userId = id;
}

string Cart::getUserId() {
	return this->userId;
}

vector<Product> Cart::getProductsInCart() {
	return this->productsInCart;
}


float Cart::getTotalPrice() {
	return this->totalPrice;
}


bool Cart::addProductToCart(Product product) {
	Utils* utils = Utils::getInstance();
	Product originalProduct;
	for (int i = 0; i < productsInCart.size(); i++) {
		if (productsInCart[i].getId() == product.getId()) {
			return false;
		}
	}
	for (int i = 0; i<utils->products.size(); i++) {
		if (product.getId() == utils->products[i].getId() && utils->products[i].getQuantity() >= product.getQuantity()) {
			productsInCart.push_back(product);
			totalPrice += product.getPrice() * product.getQuantity();
			return true;
		}
	}
	return false;
}

void Cart::setProductsinCart(vector<Product> products)
{
	this->productsInCart = products;
}

void Cart::setTotalPrice(float totalPrice) {
	this->totalPrice = totalPrice;
}

void Cart::emptyCart() {
	productsInCart.clear();
	totalPrice = 0;
}

void Cart::removeProduct(Product product) {
	for (int i = 0; i < productsInCart.size(); i++) {
		if (productsInCart[i].getId() == product.getId()) {
			productsInCart.erase(productsInCart.begin() + i);
		}
	}
}
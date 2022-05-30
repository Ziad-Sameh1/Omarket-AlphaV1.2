#include "Customer.h"
#include "Utils.h"
#include <ctime>
#include <algorithm>

Customer::Customer() {}

Customer::~Customer() {}

void Customer::setPhone(string phone)
{
	this->phone = phone;
}

void Customer::setAddress(string address)
{
	this->address = address;
}

void Customer::setFavs(vector<string> favs)
{
	this->favsProductsIds = favs;
}

void Customer::setOrders(vector<string> orders)
{
	this->orders = orders;
}

void Customer::setPoints(int points)
{
	this->points = points;
}

string Customer::getPhone()
{
	return this->phone;
}

string Customer::getAddress()
{
	return address;
}

int Customer::getPoints()
{
	return this->points;
}

vector<string> Customer::getFavs()
{
	return favsProductsIds;
}

vector<string> Customer::getOrders()
{
	return orders;
}

bool Customer::isProductInFavs(Product product)
{
	size_t favsCnt = favsProductsIds.size();
	for (int i = 0; i < favsCnt; i++) {
		if (favsProductsIds[i] == product.getId()) {
			return true;
		}
	}
	return false;
}


bool Customer::addProductToFavs(Product product) {
	if (isProductInFavs(product)) {
		return false;
	}
	favsProductsIds.push_back(product.getId());
	return true;
}

bool Customer::removeProductFromFavs(string productId) {
	size_t favsCnt = favsProductsIds.size();
	for (int i = 0; i < favsCnt; i++) {
		if (favsProductsIds[i] == productId) {
			favsProductsIds.erase(favsProductsIds.begin() + i);
			return true;
		}
	}
	return false;
}

void Customer::addPoints(int points)
{
	this->points += points;
}

void Customer::removePoints(int points)
{
	if (this->points - points >= 0) {
		this->points -= points;
		return;
	}
	// todo: show error that points are not enough
}

bool Customer::convertPointstoCash(int points)
{
	Utils* utils = Utils::getInstance();
	if (this->points - points >= 0) {
		/*
		* Each point = 0.25$
		*/
		for (int i = 0; i < utils->wallets.size(); i++) {
			if (utils->wallets[i].getUserId() == this->id) {
				utils->wallets[i].deposit(this->id, this->points * 0.25);
				return true;
			}
		}
	}
	return false;
}

void Customer::deleteUser() {
	if (ordersValidation() && depositValidation()) {
		clear();
		cout << "Done successfully\n";
	}
	else
		cout << "You Cant Delete Your Account\n";


}
bool Customer::ordersValidation()
{
	Utils* utils = Utils::getInstance();
	vector<string>myOrders = getOrders();
	map<string, bool>founded;
	for (int i = 0; i < utils->orders.size(); i++) {
		string orderId = utils->orders[i].getId();
		if (utils->orders[i].getIsActivated() == true)
			founded[orderId] = true;
	}
	for (int i = 0; i < myOrders.size(); i++) {
		if (founded[myOrders[i]])
			return false;
	}
	return true;
}
bool Customer::depositValidation() {
	Utils* utils = Utils::getInstance();
	string customerId = getId();
	for (int i = 0; i < utils->depositRequests.size(); i++) {
		if (utils->depositRequests[i].getUserId() == customerId)
			return false;
	}
	return true;
}
void Customer::clear()
{
	Utils* utils = Utils::getInstance();
	string customerId = getId();
	for (int i = 0; i < utils->customers.size(); i++) {
		if (utils->customers[i].getId() == customerId) {
			utils->customers.erase(utils->customers.begin() + i);
			break;
		}
	}
	for (int i = 0; i < utils->wallets.size(); i++) {
		if (utils->wallets[i].getUserId() == customerId) {
			utils->wallets.erase(utils->wallets.begin() + i);
			break;
		}
	}
	for (int i = 0; i < utils->carts.size(); i++) {
		if (utils->carts[i].getUserId() == customerId) {
			utils->carts.erase(utils->carts.begin() + i);
			break;
		}
	}
}

void Customer::refund(Product refundedProduct)
{
	float cash = refundedProduct.getQuantity() * refundedProduct.getPrice();
	backCash(cash);
	backProduct(refundedProduct.getId(), refundedProduct.getQuantity());
	backPoints(refundedProduct);
}
void Customer::backCash(float cash)
{
	Utils* utils = Utils::getInstance();
	for (int i = 0; i < utils->wallets.size(); i++) {
		if (utils->wallets[i].getUserId() == getId()) {
			utils->wallets[i].deposit(getId(), cash);
		}
	}
}
void Customer::backProduct(string refundedProduct, int quantity)
{
	Utils* utils = Utils::getInstance();
	for (int i = 0; i < utils->products.size(); i++) {
		if (utils->products[i].getId() == refundedProduct)
			utils->products[i].increaseQuantity(quantity);
	}
}

void Customer::backPoints(Product refundedProduct) {
	int points = refundedProduct.getPoints() * refundedProduct.getQuantity();
	removePoints(points);
}

vector<Product>Customer::browse(string productName) {
	Utils* util = Utils::getInstance();
	vector<Product>products;
	for (size_t i = 0; i < util->products.size(); i++)
	{
		if (util->products[i].getName().find(productName) != string::npos) {
			products.push_back(util->products[i]);
		}
	}
	return products;
}
vector<Product>Customer::browseByCategory(string categoryName) {
	vector<Product>v;
	Utils* utils = Utils::getInstance();
	for (size_t i = 0; i < utils->products.size(); i++)
	{
		if (utils->products[i].getCategory() == categoryName) {
			v.push_back(utils->products[i]);
		}
	}
	return v;
}

void Customer::logOut() {
	CurrentUser* user = CurrentUser::getInstance();
	user->clearUserData();
}
bool Customer::checkOut() {
	Utils* util = Utils::getInstance();
	time_t now = time(0);

	Customer x;
	int walletIndex = 0;
	int cartIndex = 0;

	// first get the user cart
	for (int i = 0; i < util->carts.size(); i++) {
		if (util->carts[i].getUserId() == getId()) {
			cartIndex = i;
			break;
		}
	}

	// second get the user wallet
	for (int i = 0; i < util->wallets.size(); i++) {
		if (util->wallets[i].getUserId() == getId()) {
			walletIndex = i;
			break;
		}
	}


	if (util->wallets[walletIndex].getWalletAmount() >= util->carts[cartIndex].getTotalPrice()) {
		// decrease products quantity
		for (size_t i = 0; i < util->carts[cartIndex].getProductsInCart().size(); i++)
		{
			for (size_t j = 0; j < util->products.size(); j++)
			{
				if (util->products[j].getId() == util->carts[cartIndex].getProductsInCart()[i].getId()) {
					util->products[j].decreaseQuantity(util->carts[cartIndex].getProductsInCart()[i].getQuantity());
					break;
				}
			}
		}
		// withdraw money
		util->wallets[walletIndex].withDraw(getId(), util->carts[cartIndex].getTotalPrice());
		// create order
		createOrder(util->carts[cartIndex]);
		// empty cart
		util->carts[cartIndex].emptyCart();
		// increase user points
		addPoints(getCartPoints(util->carts[cartIndex]));
		return true;
	}	
	else {
		return false;
	}
}

void Customer::createOrder(Cart cart)
{
	Utils* utils = Utils::getInstance();
	Order order;
	order.setId(utils->generateId());
	vector<Product> products;
	for (int i = 0; i < cart.getProductsInCart().size(); i++) {
		order.addProductToOrder(cart.getProductsInCart()[i]);
	}
	order.setTotalPrice(cart.getTotalPrice());
	order.setDate(utils->getCurrentDate());
	order.setCustomerId(getId());
	order.setIsActivated(true);
	utils->orders.push_back(order);
}

int Customer::getCartPoints(Cart cart) {
	int totalPoints = 0;
	for (int i = 0; i < cart.getProductsInCart().size(); i++) {
		totalPoints += cart.getProductsInCart()[i].getPoints();
	}
	return totalPoints;
}

vector<Order> Customer::viewCheckoutHistory() {
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	vector<Order>ordersHistory;
	vector<string>history;
	for (int i = 0; i < utils->orders.size(); i++) {
		if (utils->orders[i].getCustomerId() == user->getId()) {
			history.push_back(utils->orders[i].getDate());
		}
	}
	sort(history.begin(), history.end());
	reverse(history.begin(), history.end());
	for (int i = 0; i < history.size(); i++) {
		for (int j = 0; j < utils->orders.size(); j++) {
			if (history[i] == utils->orders[j].getDate() and utils->orders[j].getCustomerId() == user->getId()) {
				ordersHistory.push_back(utils->orders[j]);
			}
		}
	}
	return ordersHistory;
}

bool Customer::createCustomer(Customer customer)
{
	Utils* utils = Utils::getInstance();
	for (int i = 0; i < utils->customers.size(); i++) {
		if (customer.getEmail() == utils->customers[i].getEmail()) {
			// show error: user found before
			cout << "User Found Before" << endl;
			return false;
		}
	}
	// create customer
	customer.setId(utils->generateId());
	utils->customers.push_back(customer);
	// create wallet for user
	Wallet userWallet;
	userWallet.setUserId(customer.getId());
	userWallet.setAmount(0.0);
	utils->wallets.push_back(userWallet);
	// create cart for user
	Cart userCart;
	userCart.setUserId(customer.getId());
	userCart.setTotalPrice(0.0);
	utils->carts.push_back(userCart);
	return true;
}

bool Customer::loginCustomer(Customer customer) {
	Utils* utils = Utils::getInstance();
	for (int i = 0; i < utils->customers.size(); i++) {
		if (customer.getEmail() == utils->customers[i].getEmail() && customer.getPassword() == utils->customers[i].getPassword()) {
			utils->setLoggedInUserData(utils->customers[i]);
			CurrentUser* user = CurrentUser::getInstance();
			return true;
		}
	}
	return false;
} 

void Customer::clearData() {
	this->id = "";
	this->name = "";
	this->email = "";
	this->password = "";
	this->phone = "";
	this->address = "";
	this->points = 0;
	this->favsProductsIds.clear();
	this->orders.clear();
}

vector<Product> Customer::browseByRate(float rate) {
	Utils* utils = Utils::getInstance();
	vector<Product>v;
	for (int i = 0; i < utils->products.size(); i++) {
		if (utils->products[i].getAverageRate() >= rate) {
			v.push_back(utils->products[i]);
		}
	}
	return v;
}
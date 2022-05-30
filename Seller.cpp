 #include "Seller.h"
#include "Utils.h"
#include <algorithm>

Seller::Seller() {};

Seller::~Seller() {}

float Seller::getAverageRate()
{
    return this->averageRate;
}

float Seller::getTotalRates()
{
    return totalRates;
}

int Seller::getNumOfRates()
{
    return this->numOfRates;
}

int Seller::getNumOfReports()
{
	return this->numOfReports;
}

vector<string> Seller::getProductsAdded()
{
	return this->productsAdded;
}

void Seller::setAverageRate(float averageRate)
{
    this->averageRate = averageRate;
}

void Seller::setTotalRate(float totalRates)
{
    this->totalRates = totalRates;
}

void Seller::setNumOfRates(int numOfRates)
{
    this->numOfRates = numOfRates;
}
void Seller::setNumOfReports(int numOfReports)
{
	this->numOfReports = numOfReports;
}
/*
bool Seller::comparator(const Order& order1, const Order& order2)
{
	return order1.key < order2.key;
}
*/

// Rating For Seller
void Seller::updateRating(float newRate) {
    this->numOfRates++;
    this->totalRates += newRate;
    this->averageRate = totalRates / numOfRates;
}

// Seller sign up
bool Seller::signUp(Seller newSeller) {
	Utils* utils = Utils::getInstance();
	bool isFound = false;
	for (int i = 0; i < utils->sellers.size(); i++) {
		if (utils->sellers[i].getEmail() == newSeller.getEmail()) {
			isFound = true;
			return false;
		}
	}
	if (!isFound) {
		newSeller.setId(utils->generateId());
		utils->sellers.push_back(newSeller);
		return true;
	}
}

// Seller login
bool Seller::login(Seller seller) {
	Utils* utils = Utils::getInstance();
	size_t sellerCnt = utils->sellers.size();
	bool isFound = false;
	for (int i = 0; i < sellerCnt; i++) {
		if (utils->sellers[i].getEmail() == seller.getEmail()) {
			isFound = true;
			if (utils->sellers[i].getPassword() == seller.getPassword()) {
				utils->setLoggedInUserData(utils->sellers[i]);
				return true;
			}
			else {
				return false;
			}
		}
	}
	if (!isFound) {
		return false;
	}
}

vector<string> Seller::getPeopleReported()
{
	return this->peopleReported;
}

vector<Order> Seller::getActiveOrders() {
	Utils* utils = Utils::getInstance();
	size_t sellerProductsCnt = productsAdded.size();
	int productOrdersCnt = 0;
	vector<Order>productOrders;
	vector<Order>activeOrders;
	set<Order>uniqueOrders;
	for (int i = 0; i < sellerProductsCnt; i++) {
		productOrders = utils->productsOrders[productsAdded[i]].getProductOrders();
		productOrdersCnt = productOrders.size();
		for (int j = 0; j < productOrdersCnt; j++) {
			if (productOrders[j].getIsActivated()) {
				uniqueOrders.insert(productOrders[j]);
			}
		}
	}
	copy(uniqueOrders.begin(), uniqueOrders.end(), back_inserter(activeOrders));
	return activeOrders;
}

void Seller::addNewProduct(Product product) {
	Utils* utils = Utils::getInstance();
	utils->products.push_back(product);
	productsAdded.push_back(product.getId());
}

void Seller::setPeopleReported(vector<string> peopleReported) {
	this->peopleReported = peopleReported;
}

void Seller::setProductsAdded(vector<string> products)
{
	this->productsAdded = products;
}

bool Seller::isUserReported(string userId) {
	size_t reports = peopleReported.size();
	for (int i = 0; i < reports; i++) {
		if (peopleReported[i] == userId) {
			return true;
		}
	}
	return false;
}

void Seller::addReport(string userId) {
	if (isUserReported(userId)) {
		// todo: show error that user has reported the seller before
		return;
	}
	peopleReported.push_back(userId);
	this->numOfReports++;
}

void Seller::removeReport(string userId) {
	for (int i = 0; i < peopleReported.size(); i++) {
		if (peopleReported[i] == userId) {
			peopleReported.erase(peopleReported.begin() + i);
			return;
		}
	}
	// todo: show error that user has not reported the seller before
}

void Seller::deleteUser()
{
	if (productsValidation()) {
		clear();
		cout << "Done successfully\n";
	}
	else
		cout << "You Cant Delete Your Account\n";
}
bool Seller::productsValidation()
{
	Utils* utils = Utils::getInstance();
	map<string, bool>activatedProducts;
	for (int i = 0; i < utils->products.size(); i++) {
		activatedProducts[utils->products[i].getId()] = utils->products[i].getIsActivated();
	}
	for (int i = 0; i < productsAdded.size(); i++) {
		if (activatedProducts[productsAdded[i]])
			return false;
	}
	return true;
}
void Seller::clear()
{
	Utils* utils = Utils::getInstance();
	map<string, bool>ProductQuantity;
	for (int i = 0; i < productsAdded.size(); i++) {
		ProductQuantity[productsAdded[i]] = true;
	}
	for (int i = 0; i < utils->products.size(); i++) {
		if (ProductQuantity[utils->products[i].getId()])
			utils->products[i].decreaseQuantity(utils->products[i].getQuantity());
	}
	for (int i = 0; i < utils->sellers.size(); i++) {
		if (utils->sellers[i].getId() == this->getId()) {
			utils->sellers.erase(utils->sellers.begin() + i);
			// make current status emptyyy
			break;
		}
	};
}

void Seller::clearData() {
	this->id = "";
	this->name = "";
	this->password = "";
	this->email = "";
}
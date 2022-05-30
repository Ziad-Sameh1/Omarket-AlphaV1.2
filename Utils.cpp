#pragma warning(disable: 4996)
#include "Utils.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include "CurrentUser.h"

Utils::Utils() {}
Utils::~Utils() {}
Utils* Utils::instance = NULL;

Utils* Utils::getInstance() {
	if (Utils::instance == NULL) {
		instance = new Utils();
	}
	return instance;
}

string Utils::generateId() {
	/*
	* GENERATE 16 BIT STRING WITH 0 - 9, A-Z , a-Z CHARACTERS
	* 0 - 9 ASCII CODE IS : 48 - 57 (1)
	* A - Z ASCII CODE IS : 65 - 90	(2)
	* a - z ASCII CODE IS : 97 - 122 (3)
	*/
	srand(time(0));
	string id;
	int rand1 = 0, rand2 = 0;
	for (int i = 0; i < 16; i++) {
		rand1 = rand() % 3 + 1;
		switch (rand1) {
		case 1: {
			rand2 = rand() % 10 + 48;
			break;
		}
		case 2: {
			rand2 = rand() % 26 + 65;
			break;
		}
		case 3: {
			rand2 = rand() % 26 + 97;
			break;
		}
		}
		id += (char)rand2;
	}
	return id;
}

string Utils::encode(string dehashedString) {
	char hashed[100] = {};
	int lastIndex = 0;
	string hashedString = "";
	for (int i = 0; i < dehashedString.length(); i++) {
		if (dehashedString[i] % 2 == 0) {
			hashed[i] = dehashedString[i] - 4;
		}
		else if (dehashedString[i] % 2 == 1) {
			hashed[i] = dehashedString[i] - 2;
		}
		lastIndex = i;
	}
	for (int i = 0; i <= lastIndex; i++) {
		hashedString += hashed[i];
	}
	return hashedString;
}

string Utils::decode(string hashedString) {
	char unhashed[100] = {};
	int lastIndex = 0;
	string unhashedString = "";
	for (int i = 0; i < hashedString.length(); i++) {
		if (hashedString[i] % 2 == 0) {
			unhashed[i] = hashedString[i] + 4;
		}
		else if (hashedString[i] % 2 == 1) {
			unhashed[i] = hashedString[i] + 2;
		};
		
		lastIndex = i;
	}
	for (int i = 0; i <= lastIndex; i++) {
		unhashedString += unhashed[i];
	}
	return unhashedString;
}

string Utils::jsonValueToStdString(Json::Value jsonValue) {
	string stringValue = jsonValue.toStyledString();
	stringValue.pop_back();
	stringValue.pop_back();
	stringValue.erase(stringValue.begin());
	return stringValue;
}

void Utils::setLoggedInUserData(User user) {
	CurrentUser* currentUser = CurrentUser::getInstance();
	currentUser->setEmail(user.getEmail());
	currentUser->setId(user.getId());
	currentUser->setName(user.getName());
}

string Utils::getCurrentDate() {
	std::time_t time = std::time(0);
	std::tm* now = std::localtime(&time);
	string date = to_string(now->tm_year + now->tm_mon + now->tm_mday + now->tm_hour);
	return date;
}

int Utils::getNumberOfFilesInDir(string dirPath) {
	auto dirIter = filesystem::directory_iterator(dirPath);

	return std::count_if(
		begin(dirIter),
		end(dirIter),
		[](auto& entry) { return entry.is_regular_file(); }
	);

}

bool Utils::stob(string value) {
	if (value == "true") return true; else return false;
}

Customer Utils::mappingJsonCustomertoCustomer(Value jsonValue) {
	Customer customer;
	Reader reader;

	root.clear();

	customer.setId(jsonValueToStdString(jsonValue["id"]));
	customer.setName(jsonValueToStdString(jsonValue["name"]));
	customer.setEmail(jsonValueToStdString(jsonValue["email"]));
	customer.setPhone(jsonValueToStdString(jsonValue["phone"]));
	customer.setAddress(jsonValueToStdString(jsonValue["address"]));
	
	// get List of favs
	vector<string>favs;
	int favsCnt = jsonValue["favs"].size();
	for (int i = 0; i < favsCnt; i++) {
		favs.push_back(jsonValueToStdString(jsonValue["favs"][i]));
	}
	customer.setFavs(favs);

	// get List of orders
	vector<string>orders;
	int ordersCnt = jsonValue["orders"].size();
	for (int i = 0; i < ordersCnt; i++) {
		orders.push_back(jsonValueToStdString(jsonValue["orders"][i]));
	}
	customer.setOrders(orders);

	ifstream inputPassword(DATABASE_PATH + "customers/customers_passwords/" + customer.getId() + ".json");
	bool isSuccess = reader.parse(inputPassword, root);
	if (isSuccess) {
		customer.setPassword(decode(jsonValueToStdString(root["password"])));
	}
	inputPassword.close();
	
	root.clear();

	ifstream inputPoint(DATABASE_PATH + "customers/customers_points/" + customer.getId() + ".json");
	isSuccess = reader.parse(inputPoint, root);
	if (isSuccess) {
		customer.setPoints(stof(decode(jsonValueToStdString(root["points"]))));
	}
	inputPoint.close();
	return customer;
}

vector<Value> Utils::mappingCustomertoJsonCustomer(Customer customer) {
	v.clear();

	root.clear();

	root["id"] = customer.getId();
	root["name"] = customer.getName();
	root["email"] = customer.getEmail();
	root["phone"] = customer.getPhone();
	root["address"] = customer.getAddress();

	for (int i = 0; i < customer.getFavs().size(); i++) {
		root["favs"][i] = customer.getFavs()[i];
	}

	for (int i = 0; i < customer.getOrders().size(); i++) {
		root["orders"][i] = customer.getOrders()[i];
	}
	
	v.push_back(root);

	root.clear();

	root["password"] = encode(customer.getPassword());

	v.push_back(root);

	root.clear();

	root["points"] = encode(to_string(customer.getPoints()));

	v.push_back(root);

	return v;
}

Admin Utils::mappingJsonAdmintoAdmin(Value jsonValue) {
	Admin admin;
	Reader reader;

	root.clear();

	admin.setId(jsonValueToStdString(jsonValue["id"]));
	admin.setName(jsonValueToStdString(jsonValue["name"]));
	admin.setEmail(jsonValueToStdString(jsonValue["email"]));
	
	// get Password
	ifstream input(DATABASE_PATH + "admins/admins_passwords/" + admin.getId() + ".json");
	bool isSuccess = reader.parse(input, root);
	if (isSuccess) {
		admin.setPassword(decode(jsonValueToStdString(root["password"])));
	}
	input.close();

	return admin;
}

vector<Value> Utils::mappingAdmintoJsonAdmin(Admin admin) {

	v.clear();

	root.clear();

	root["id"] = admin.getId();
	root["name"] = admin.getName();
	root["email"] = admin.getEmail();

	v.push_back(root);

	root.clear();

	root["password"] = encode(admin.getPassword());

	v.push_back(root);

	return v;
}

Seller Utils::mappingJsonSellertoSeller(Value jsonValue) {
	Seller seller;

	Reader reader;

	root.clear();

	seller.setId(jsonValueToStdString(jsonValue["id"]));
	seller.setName(jsonValueToStdString(jsonValue["name"]));
	seller.setEmail(jsonValueToStdString(jsonValue["email"]));
	
	// get Password
	ifstream input(DATABASE_PATH + "sellers/sellers_passwords/" + seller.getId() + ".json");
	bool isSuccess = reader.parse(input, root);
	if (isSuccess) {
		seller.setPassword(decode(jsonValueToStdString(root["password"])));
	}

	input.close();

	// get Products added
	vector<string>productsAdded;
	int productsCnt = jsonValue["products"].size();
	for (int i = 0; i < productsCnt; i++) {
		productsAdded.push_back(jsonValueToStdString(jsonValue["products"][i]));
	}
	seller.setProductsAdded(productsAdded);

	// get People reported
	vector<string>peopleReported;
	int peopleCnt = jsonValue["people_reported"].size();
	for (int i = 0; i < peopleCnt; i++) {
		peopleReported.push_back(jsonValueToStdString(jsonValue["people_reported"][i]));
	}
	seller.setPeopleReported(peopleReported);

	seller.setNumOfReports(stoi(jsonValueToStdString(jsonValue["num_of_reports"])));
	seller.setTotalRate(stof(jsonValueToStdString(jsonValue["total_rates"])));
	seller.setAverageRate(stof(jsonValueToStdString(jsonValue["average_rate"])));
	seller.setNumOfRates(stoi(jsonValueToStdString(jsonValue["num_of_rates"])));

	return seller;
}

vector<Value> Utils::mappingSellertoJsonSeller(Seller seller) {
	
	v.clear();

	root.clear();

	root["id"] = seller.getId();
	root["name"] = seller.getName();
	root["email"] = seller.getEmail();
	root["num_of_reports"] = to_string(seller.getNumOfReports());
	root["total_rates"] = to_string(seller.getTotalRates());
	root["average_rate"] = to_string(seller.getAverageRate());
	root["num_of_rates"] = to_string(seller.getNumOfRates());

	for (int i = 0; i < seller.getProductsAdded().size(); i++) {
		root["products"][i] = seller.getProductsAdded()[i];
	}

	for (int i = 0; i < seller.getPeopleReported().size(); i++) {
		root["people_reported"][i] = seller.getPeopleReported()[i];
	}

	v.push_back(root);

	root.clear();

	root["password"] = encode(seller.getPassword());

	v.push_back(root);

	return v;

}

Cart Utils::mappingJsonCarttoCart(Value jsonValue) {

	Cart cart;

	cart.setUserId(jsonValueToStdString(jsonValue["user_id"]));
	cart.setTotalPrice(stof(jsonValueToStdString(jsonValue["total_price"])));

	vector<Product> productsInCart;
	int productsCnt = jsonValue["products"].size();

	for (int i = 0; i < productsCnt; i++) {
		productsInCart.push_back(mappingJsonProducttoProduct(jsonValue["products"][i]));
	}

	cart.setProductsinCart(productsInCart);

	return cart;

}

Value Utils::mappingCarttoJsonCart(Cart cart) {
	root.clear();
	root["user_id"] = cart.getUserId();
	root["total_price"] = to_string(cart.getTotalPrice());
	for (int i = 0; i < cart.getProductsInCart().size(); i++) {
		root["products"][i] = mappingProducttoJsonProduct(cart.getProductsInCart()[i]);
	}
	return root;
}

Product Utils::mappingJsonProducttoProduct(Value jsonValue) {
	Product product;

	product.setId(jsonValueToStdString(jsonValue["id"]));
	product.setName(jsonValueToStdString(jsonValue["name"]));
	product.setDescription(jsonValueToStdString(jsonValue["description"]));
	product.setImagePath(jsonValueToStdString(jsonValue["image_path"]));
	product.setSellerId(jsonValueToStdString(jsonValue["seller_id"]));
	product.setPrice(stof(jsonValueToStdString(jsonValue["price"])));
	product.setQuantity(stoi(jsonValueToStdString(jsonValue["quantity"])));
	product.setCategory(jsonValueToStdString(jsonValue["category"]));
	product.setNumOfRates(stoi(jsonValueToStdString(jsonValue["num_of_rates"])));
	product.setTotalRate(stof(jsonValueToStdString(jsonValue["total_rate"])));
	product.setAverageRate(stof(jsonValueToStdString(jsonValue["average_rate"])));
	product.setPoints(stoi(jsonValueToStdString(jsonValue["points"])));
	product.setIsActivated(stob(jsonValueToStdString(jsonValue["is_activated"])));

	vector<Comment> comments;
	
	int commentsCnt = jsonValue["comments"].size();

	for (int i = 0; i < commentsCnt; i++) {
		comments.push_back(mappingJsonCommenttoComment(jsonValue["comments"][i]));
	}
	
	product.setComments(comments);

	return product;
}

Value Utils::mappingProducttoJsonProduct(Product product) {
	
	Value productRoot;

	productRoot["id"] = product.getId();
	productRoot["name"] = product.getName();
	productRoot["description"] = product.getDescription();
	productRoot["image_path"] = product.getImagePath();
	productRoot["seller_id"] = product.getSellerId();
	productRoot["price"] = to_string(product.getPrice());
	productRoot["quantity"] = to_string(product.getQuantity());
	productRoot["category"] = product.getCategory();
	productRoot["num_of_rates"] = to_string(product.getNumOfRates());
	productRoot["total_rate"] = to_string(product.getTotalRates());
	productRoot["average_rate"] = to_string(product.getAverageRate());
	productRoot["points"] = to_string(product.getPoints());
	if (product.getIsActivated()) {
		productRoot["is_activated"] = "true";
	}
	else {
		productRoot["is_activated"] = "false";
	}

	for (int i = 0; i < product.getComments().size(); i++) {
		productRoot["comments"][i] = mappingCommenttoJsonComment(product.getComments()[i]);
	}

	return productRoot;
}

Comment Utils::mappingJsonCommenttoComment(Value jsonValue) {
	Comment comment;

	comment.setId(jsonValueToStdString(jsonValue["id"]));
	comment.setCustomerId(jsonValueToStdString(jsonValue["customer_id"]));
	comment.setDate(jsonValueToStdString(jsonValue["date"]));
	comment.setNumOfLikes(stoi(jsonValueToStdString(jsonValue["num_of_likes"])));
	comment.setNumOfDislikes(stoi(jsonValueToStdString(jsonValue["num_of_dislikes"])));
	comment.setContent(jsonValueToStdString(jsonValue["content"]));

	vector<string>peopleLiked;
	vector<string>peopleDisliked;
	
	int likesCnt = jsonValue["people_liked"].size();
	int dislikesCnt = jsonValue["people_disliked"].size();

	for (int i = 0; i < likesCnt; i++) {
		peopleLiked.push_back(jsonValueToStdString(jsonValue["people_liked"][i]));
	}

	for (int i = 0; i < dislikesCnt; i++) {
		peopleDisliked.push_back(jsonValueToStdString(jsonValue["people_disliked"][i]));
	}

	comment.setPeopleLiked(peopleLiked);
	comment.setPeopleDisliked(peopleDisliked);

	return comment;
}

Value Utils::mappingCommenttoJsonComment(Comment comment) {

	Value CommentRoot;

	CommentRoot["id"] = comment.getId();
	CommentRoot["customer_id"] = comment.getCustomerId();
	CommentRoot["date"] = comment.getDate();
	CommentRoot["num_of_likes"] = to_string(comment.getNumOfLikes());
	CommentRoot["num_of_dislikes"] = to_string(comment.getNumOfDislikes());
	CommentRoot["content"] = comment.getContent();

	for (int i = 0; comment.getPeopleLiked().size(); i++) {
		CommentRoot["people_liked"][i] = comment.getPeopleLiked()[i];
	}

	for (int i = 0; comment.getPeopleDisliked().size(); i++) {
		CommentRoot["people_disliked"][i] = comment.getPeopleDisliked()[i];
	}

	return CommentRoot;
}

Coupon Utils::mappingJsonCoupontoCoupon(Value jsonValue) {
	Coupon coupon;

	coupon.setId(jsonValueToStdString(jsonValue["id"]));
	coupon.setCoupon(jsonValueToStdString(jsonValue["coupon"]));
	coupon.setDiscountAmount(stof(jsonValueToStdString(jsonValue["discount_amount"])));

	return coupon;
}

Value Utils::mappingCoupontoJsonCoupon(Coupon coupon) {

	root.clear();

	root["id"] = coupon.getId();
	root["coupon"] = coupon.getCoupon();
	root["discount_amount"] = to_string(coupon.getDiscountAmount());

	return root;
}

CurrentUser* Utils::mappingJsonCurrentUsertoCurrentUser(Value jsonValue) {
	CurrentUser* currentUser = CurrentUser::getInstance();

	currentUser->setId(jsonValueToStdString(jsonValue["id"]));
	currentUser->setName(jsonValueToStdString(jsonValue["name"]));
	currentUser->setEmail(jsonValueToStdString(jsonValue["email"]));
	currentUser->setType(jsonValueToStdString(jsonValue["type"]));

	return currentUser;
}

Value Utils::mappingCurrentUsertoJsonCurrentUser(CurrentUser* currentUser) {

	root.clear();

	root["id"] = currentUser->getId();
	root["name"] = currentUser->getName();
	root["email"] = currentUser->getEmail();
	root["type"] = currentUser->getType();

	return root;
}

DepositRequests Utils::mappingJsonDepositRequeststoDepositRequests(Value jsonValue) {
	DepositRequests depositRequest;

	depositRequest.setUserId(jsonValueToStdString(jsonValue["id"]));
	depositRequest.setAmount(stof(jsonValueToStdString(jsonValue["deposit_amount"])));
	depositRequest.setIsApproved(stob(jsonValueToStdString(jsonValue["is_approved"])));

	return depositRequest;
}

Value Utils::mappingDepositRequeststoJsonDepositRequests(DepositRequests depositRequest) {

	root.clear();

	root["id"] = depositRequest.getUserId();
	root["deposit_amount"] = to_string(depositRequest.getAmount());
	root["is_approved"] = to_string(depositRequest.status());

	return root;
}

Order Utils::mappingJsonOrdertoOrder(Value jsonValue) {
	Order order;

	order.setId(jsonValueToStdString(jsonValue["id"]));
	order.setDate(jsonValueToStdString(jsonValue["date"]));
	order.setCustomerId(jsonValueToStdString(jsonValue["customer_id"]));
	order.setTotalPrice(stof(jsonValueToStdString(jsonValue["total_price"])));
	order.setIsActivated(stob(jsonValueToStdString(jsonValue["is_activated"])));

	vector<Product> products;
	int productsCnt = jsonValue["products"].size();
	for (int i = 0; i < productsCnt; i++) {
		products.push_back(mappingJsonProducttoProduct(jsonValue["products"][i]));
	}

	order.setOrderProducts(products);

	return order;
}

Value Utils::mappingOrdertoJsonOrder(Order order) {

	root.clear();

	root["id"] = order.getId();
	root["date"] = order.getDate();
	root["customer_id"] = order.getCustomerId();
	root["total_price"] = to_string(order.getTotalPrice());
	if (order.getIsActivated()) {
		root["is_activated"] = "true";
	}
	else {
		root["is_activated"] = "false";
	}

	for (int i = 0; i < order.getOrderProducts().size(); i++) {
		root["products"][i] = mappingProducttoJsonProduct(order.getOrderProducts()[i]);
	}

	return root;
}

ProductOrders Utils::mappingJsonProductOrderstoProductOrders(Value jsonValue) {
	ProductOrders productOrders;

	productOrders.setProductId(jsonValueToStdString(jsonValue["product_id"]));

	vector<Order> orders;
	int ordersCnt = jsonValue["orders"].size();
	for (int i = 0; i < ordersCnt; i++) {
		orders.push_back(mappingJsonOrdertoOrder(jsonValue["orders"][i]));
	}

	productOrders.setProductOrders(orders);

	return productOrders;
}

Value Utils::mappingProductOrderstoJsonProductOrders(ProductOrders productOrders) {

	root.clear();

	root["id"] = productOrders.getProductId();

	for (int i = 0; i < productOrders.getProductOrders().size(); i++) {
		root["orders"][i] = mappingOrdertoJsonOrder(productOrders.getProductOrders()[i]);
	}

	return root;
}

Wallet Utils::mappingJsonWallettoWallet(Value jsonValue) {
	Wallet wallet;

	wallet.setUserId(jsonValueToStdString(jsonValue["user_id"]));
	wallet.setAmount(stof(jsonValueToStdString(jsonValue["amount"])));

	return wallet;
}

Value Utils::mappingWallettoJsonWallet(Wallet wallet) {

	root.clear();

	root["user_id"] = wallet.getUserId();
	root["amount"] = to_string(wallet.getWalletAmount());

	return root;
}

void Utils::readDatebase() {
	Reader reader;
	// read all customers
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "customers/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			customers.push_back(mappingJsonCustomertoCustomer(root));
			input.close();
		}
	}

	// read all sellers
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "sellers/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			sellers.push_back(mappingJsonSellertoSeller(root));
			input.close();
		}
	}

	// read all admins
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "admins/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			admins.push_back(mappingJsonAdmintoAdmin(root));
			input.close();
		}
	}
	// read all carts
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "carts/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			carts.push_back(mappingJsonCarttoCart(root));
			input.close();
		}
	}

	// read all comments
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "comments/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			comments.push_back(mappingJsonCommenttoComment(root));
			input.close();
		}
	}

	// read all coupons
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "coupons/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			coupons.push_back(mappingJsonCoupontoCoupon(root));
			input.close();
		}
	}
	// read current user
	CurrentUser* user = CurrentUser::getInstance();
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH)) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			user = mappingJsonCurrentUsertoCurrentUser(root);
			input.close();
			break;
		}
	}
	// read all deposit requests
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "deposit_requests/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			depositRequests.push_back(mappingJsonDepositRequeststoDepositRequests(root));
			input.close();
		}
	}
	// read all orders
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "orders/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			orders.push_back(mappingJsonOrdertoOrder(root));
			input.close();
		}
	}

	// read all products
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "products/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			products.push_back(mappingJsonProducttoProduct(root));
			input.close();
		}
	}

	// read all product orders
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "product_orders/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			productsOrders[jsonValueToStdString(root["product_id"])] = mappingJsonProductOrderstoProductOrders(root);
			input.close();
		}
	}
	// read all wallets
	for (auto& entry : filesystem::directory_iterator(DATABASE_PATH + "wallets/")) {
		if (entry.is_regular_file()) {
			ifstream input(entry.path());
			bool isSuccess = reader.parse(input, root);
			wallets.push_back(mappingJsonWallettoWallet(root));
			input.close();
		}
	}

	// read all categories
	ifstream inputCategories(DATABASE_PATH + "categories.json");
	bool isSuccess = reader.parse(inputCategories, root);
	int categoriesCnt = root["categories"].size();
	for (int i = 0; i < categoriesCnt; i++) {
		categories.push_back(jsonValueToStdString(root["categories"][i]));
	}
	inputCategories.close();
}

void Utils::writeDatabase() {
	// write all customers
	for (int i = 0; i < customers.size(); i++) {
		ofstream output(DATABASE_PATH + "customers/" + customers[i].getId() + ".json");
		ofstream output2(DATABASE_PATH + "customers/customers_passwords/" + customers[i].getId() + ".json");
		ofstream output3(DATABASE_PATH + "customers/customers_points/" + customers[i].getId() + ".json");
		if (mappingCustomertoJsonCustomer(customers[i]).size() > 2) {
			for (int j = 0; j < mappingCustomertoJsonCustomer(customers[i]).size(); j++) {
				switch (j) {
				case 0:
				{
					output << mappingCustomertoJsonCustomer(customers[i])[j] << endl;
					output.close();
					break;
				}
				case 1: {
					output2 << mappingCustomertoJsonCustomer(customers[i])[j] << endl;
					output2.close();
					break;
				}
				case 2: {
					output3 << mappingCustomertoJsonCustomer(customers[i])[j] << endl;
					output3.close();
					break;
				}
				}
			}
		}
	}

	// write all sellers
	for (int i = 0; i < sellers.size(); i++) {
		ofstream outputSeller(DATABASE_PATH + "sellers/" + sellers[i].getId() + ".json");
		ofstream outputSeller2(DATABASE_PATH + "sellers/sellers_passwords/" + sellers[i].getId() + ".json");
		if (mappingSellertoJsonSeller(sellers[i]).size() > 1) {
			for (int j = 0; j < mappingSellertoJsonSeller(sellers[i]).size(); j++) {
				switch (j) {
				case 0:
				{
					outputSeller << mappingSellertoJsonSeller(sellers[i])[j] << endl;
					outputSeller.close();
					break;
				}
				case 1: {
					outputSeller2 << mappingSellertoJsonSeller(sellers[i])[j] << endl;
					outputSeller2.close();
					break;
				}
				}
			}
		}
	}

	// write all admins
	for (int i = 0; i < admins.size(); i++) {
		ofstream outputAdmin(DATABASE_PATH + "admins/" + admins[i].getId() + ".json");
		ofstream outputAdmin2(DATABASE_PATH + "admins/admins_passwords/" + admins[i].getId() + ".json");
		if (mappingAdmintoJsonAdmin(admins[i]).size() > 1) {
			for (int j = 0; j < mappingAdmintoJsonAdmin(admins[i]).size(); j++) {
				switch (j) {
				case 0:
				{
					outputAdmin << mappingAdmintoJsonAdmin(admins[i])[j] << endl;
					outputAdmin.close();
					break;
				}
				case 1: {
					outputAdmin2 << mappingAdmintoJsonAdmin(admins[i])[j] << endl;
					outputAdmin2.close();
					break;
				}
				}
			}
		}
	}

	// write all carts
	for (int i = 0; i < carts.size(); i++) {
		ofstream outputCart(DATABASE_PATH + "carts/" + carts[i].getUserId() + ".json");
		outputCart << mappingCarttoJsonCart(carts[i]) << endl;
		outputCart.close();
	}

	// write all comments
	for (int i = 0; i < comments.size(); i++) {
		ofstream outputComments(DATABASE_PATH + "comments/" + comments[i].getId() + ".json");
		outputComments << mappingCommenttoJsonComment(comments[i]) << endl;
		outputComments.close();
	}

	// write all coupons
	for (int i = 0; i < coupons.size(); i++) {
		ofstream outputCoupons(DATABASE_PATH + "coupons/" + coupons[i].getId() + ".json");
		outputCoupons << mappingCoupontoJsonCoupon(coupons[i]) << endl;
		outputCoupons.close();
	}

	// write current user
	CurrentUser* user = CurrentUser::getInstance();
	ofstream outputCurrentUser(DATABASE_PATH + "current_user.json");
	outputCurrentUser << mappingCurrentUsertoJsonCurrentUser(user);

	// write all deposit requests
	for (int i = 0; i < depositRequests.size(); i++) {
		ofstream outputDepositRequests(DATABASE_PATH + "deposit_requests/" + depositRequests[i].getUserId() + ".json");
		outputDepositRequests << mappingDepositRequeststoJsonDepositRequests(depositRequests[i]) << endl;
		outputDepositRequests.close();
	}

	// write all orders
	for (int i = 0; i < orders.size(); i++) {
		ofstream outputOrders(DATABASE_PATH + "orders/" + orders[i].getId() + ".json");
		outputOrders << mappingOrdertoJsonOrder(orders[i]) << endl;
		outputOrders.close();
	}

	// write all products
	for (int i = 0; i < products.size(); i++) {
		ofstream outputProducts(DATABASE_PATH + "products/" + products[i].getId() + ".json");
		outputProducts << mappingProducttoJsonProduct(products[i]) << endl;
		outputProducts.close();
	}

	// write all product orders
	for (auto it : productsOrders) {
		ofstream outputProductOrders(DATABASE_PATH + "product_orders/" + it.first + ".json");
		outputProductOrders << mappingProductOrderstoJsonProductOrders(it.second) << endl;
		outputProductOrders.close();
	}
	
	// write all wallets
	for (int i = 0; i < wallets.size(); i++) {
		ofstream outputWallets(DATABASE_PATH + "wallets/" + wallets[i].getUserId() + ".json");
		outputWallets << mappingWallettoJsonWallet(wallets[i]) << endl;
		outputWallets.close();
	}

	// write all categories
	ofstream outputCategories(DATABASE_PATH + "categories.json");
	root.clear();
	for (int i = 0; i < categories.size(); i++) {
		root["categories"][i] = categories[i];
	}
	outputCategories << root << endl;
	outputCategories.close();
}

bool Utils::isEmailValid(string email) {
	CurrentUser* now = CurrentUser::getInstance();
	Utils* utils = Utils::getInstance();
	bool at = false;
	for (int i = 0; i < email.size(); i++) {
		if (email[i] == '@')
		{
			at = true;
			break;
		}
	}
	return email.length() >= 4 && at;
}

bool Utils::isPasswordValid(string password) {
	return password.length() >= 6;
}

bool Utils::isPhoneNumberValid(string phoneNumber) {
	if (phoneNumber.length() < 9) {
		return false;
	}
	else {
		for (int i = 0; i < phoneNumber.length(); i++) {
			if (phoneNumber[i] >= 48 && phoneNumber[i] <= 57) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}

bool Utils::isNotEmpty(string value) {
	return value.length() > 0;
}
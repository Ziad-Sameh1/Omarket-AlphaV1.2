#pragma once
#include <string>
#include <json/json.h>
#include <vector>
#include <map>
#include "Customer.h"
#include "Seller.h"
#include "Product.h"
#include "Cart.h"
#include "Order.h"
#include "Admin.h"
#include "Comment.h"
#include "Wallet.h"
#include "DepositRequests.h"
#include "Coupon.h"
#include "ProductOrders.h"
#include <filesystem>
#include <stack>
using namespace std;
using namespace Json;
class Utils
{
private:
	static Utils* instance;
	Utils();
	~Utils();
public:
	 vector<Customer>customers;
	 vector<Seller>sellers;
	 vector<Product>products;
	 vector<Cart>carts;
	 vector<Order>orders;
	 vector<Admin>admins;
	 vector<Comment>comments;
	 vector<Wallet>wallets;
	 vector<DepositRequests>depositRequests;
	 vector<Coupon>coupons;
	 vector<string>categories;
	 map<string, ProductOrders>productsOrders;
	 stack<string> screensOrder;
	 string DATABASE_PATH = "C:/Users/ziads/Desktop/DS Project/Omarket-V1.0-Alpha/database/";
	 Value root;
	 vector<Value> v;

	static Utils* getInstance();
	string generateId();
	string encode(string dehashedString);
	string decode(string hashedString);
	string jsonValueToStdString(Value jsonValue);
	void setLoggedInUserData(User user);
	string getCurrentDate();
	int getNumberOfFilesInDir(string path);
	Customer mappingJsonCustomertoCustomer(Value jsonValue);
	vector<Value> mappingCustomertoJsonCustomer(Customer customer);
	Admin mappingJsonAdmintoAdmin(Value jsonValue);
	vector<Value> mappingAdmintoJsonAdmin(Admin admin);
	Seller mappingJsonSellertoSeller(Value jsonValue);
	vector<Value> mappingSellertoJsonSeller(Seller seller);
	Cart mappingJsonCarttoCart(Value jsonValue);
	Value mappingCarttoJsonCart(Cart cart);
	Product mappingJsonProducttoProduct(Value jsonValue);
	Value mappingProducttoJsonProduct(Product product);
	bool stob(string value);
	Comment mappingJsonCommenttoComment(Value jsonValue);
	Value mappingCommenttoJsonComment(Comment comment);
	Coupon mappingJsonCoupontoCoupon(Value jsonValue);
	Value mappingCoupontoJsonCoupon(Coupon coupon);
	CurrentUser* mappingJsonCurrentUsertoCurrentUser(Value jsonValue);
	Value mappingCurrentUsertoJsonCurrentUser(CurrentUser* currentUser);
	DepositRequests mappingJsonDepositRequeststoDepositRequests(Value jsonValue);
	Value mappingDepositRequeststoJsonDepositRequests(DepositRequests depositRequests);
	Order mappingJsonOrdertoOrder(Value jsonValue);
	Value mappingOrdertoJsonOrder(Order order);
	ProductOrders mappingJsonProductOrderstoProductOrders(Value jsonValue);
	Value mappingProductOrderstoJsonProductOrders(ProductOrders productOrders);
	Wallet mappingJsonWallettoWallet(Value jsonValue);
	Value mappingWallettoJsonWallet(Wallet wallet);
	void readDatebase();
	void writeDatabase();
	bool isEmailValid(string email);
	bool isPasswordValid(string password);
	bool isPhoneNumberValid(string phoneNumber);
	bool isNotEmpty(string value);
};


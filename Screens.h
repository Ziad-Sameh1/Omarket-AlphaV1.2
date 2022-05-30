#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "Utils.h"
#include "Routes.h"
#include "CurrentUser.h"
using namespace std;
class Screens
{
private :
	Screens();
	~Screens();
	static Screens* instance;

public:
	Customer customer;
	Seller seller;
	vector<Product>browseByNameResult;
	vector<Product>browseByCategoryResult;
	vector<Product>browseByRateResult;
	static Screens* getInstance();
	void gotoChooseUserTypeScreen();
	void gotoCustomerSignUpScreen();
	void gotoSellerSignUpScreen();
	void validateCustomerSignUpData();
	void validateSellerSignUpData();
	void gotoSellerSignUpConfirmationScreen(bool status);
	void gotoCustomerSignUpConfirmationScreen(bool status);

	// gaber 17-5-2022
	void drawMenuCustomerSeller(string); // for Customer , Seller 
	void drawMenuAdmin(string);
	void gotoCustomerEntryPage();
	void gotoSellerEntryPage();
	void gotoAdminEntryPage();

	// 7oda 17-5-2022
	void gotoCustomerLoginScreen();
	void gotoSellerLoginScreen();
	void gotoAdminLoginScreen();

	void gotoCustomerHomePage();
	void gotoCustomerBrowseScreen();
	void gotoCustomerBrowseByNameScreen();
	void gotoCustomerBrowseByCategoriesScreen();
	void gotoCustomerBrowseByRateScreen();
	void productsMenu(int cnt, vector<Product> products);
	void exitProgram();
	void exitMenu(int startLine,string backScreenRoute);
	void gotoWalletScreen();
	void gotoDepositScreen();
	void gotoConvertPointsScreen();
	void gotoSeeCheckoutHistoryScreen();
	void navigate(string screenRoute);
	void gotoCheckCartScreen();
	void gotoCheckoutScreen();
	void gotoFavsScreen();
	void gotoRefundScreen();
	void showProductsMenu(vector<Product> products);
	void gotoDeleteAccountScreen();
	void gotoApproveDepositsScreen();
	void gotoFinishOrdersScreen();
	void gotoViewDeliveryProductsScreen();
	void gotoAdminHomePageScreen();
	void gotoSellerHomePageScreen();
	void ReactToACommentPage(Comment c);
	void ReactToACommentPageConfirmationPage();
	void ReportASellerPage(string id);
	void gottoaddadminscreeen();
	void addingAdminPageConfirmationPage(Admin a);
	void sellerAddProduct();
	void sellerViewProduct();
	void sellerlogout();
	void DeleteUser();
	void adminAddCoupon();
	void gotoProductScreen(Product product);
	void showCommentsScreen(vector<Comment> comments);
	void gotoCommentScreen(Comment comment);
	void gotoAddToCartSucceededPage();
	void gotoAddToCartFailedPage();
	void drawMenuAddedToCart();
	void gotoRateProductPage(Product product);
	void showRateMenue(Product product);
	void drawMenuRatePage();
	void gotoAddProdutToFavPage();
	void drawMenuAddProductToFav();
	void gotoAddCommentPage();
	void drawMenuAddComment();
	void gotoAddCommentConfermationpage(string);
	void gotoRateSellerPage(int sellerIndex);
};


#pragma once
#include <stdlib.h>
#include <string>
using namespace std;
class Routes
{
private:
	Routes();
	~Routes();
	static Routes* instance;
public:
	static Routes* getInstance();
	const string viewCheckoutHistoryScreenRoute = "route_for_checkout_history_screen";
	const string customerHomePageScreenRoute = "route_for_customer_home_page_screen";
	const string checkCartScreenRoute = "route_for_customer_cart_screen";
	const string checkoutScreenRoute = "route_for_customer_checkout_screen";
	const string checkFavsScreenRoute = "route_for_favs_screen";
	const string requestRefundScreenRoute = "route_for_refund_screen";
	const string deleteAccountScreenRoute = "route_for_delete_account_screen";
	const string chooseUserTypeScreenRoute = "route_for_choose_user_type_screen";
	const string approveDepositsScreenRoute = "route_for_approve_deposit_requests_screen";
	const string finishOrdersScreenRoute = "route_for_finish_orders_screen";
	const string viewDeliveryProductsScreenRoute = "route_for_view_delivery_products_screen";
	const string sellerHomePageScreenRoute = "route_for_seller_home_screen";
	const string AdminHomePageScreenRoute = "route_for_admin_home_screen";
	const string commentScreenRoute = "route_for_comment_screen";
	const string productScreenRoute = "route_for_product_screen";
};


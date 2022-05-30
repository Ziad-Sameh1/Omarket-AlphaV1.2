#include "Screens.h"

Screens::Screens() {}

Screens::~Screens() {}

Screens* Screens::instance = NULL;

void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

Screens* Screens::getInstance() {
	if (instance == NULL) {
		instance = new Screens();
	}
	return instance;
}

void Screens::gotoChooseUserTypeScreen() {
	Utils* utils = Utils::getInstance();
	system("cls");
	cout << " ********************* CHOOSE USER TYPE ********************* " << endl;
	vector<int>set;
	for (int i = 0; i < 5; i++) {
		set.push_back(7);
	}
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 1);
		color(set[0]);
		cout << "1.Customer";
		gotoxy(0, 2);
		color(set[1]);
		cout << "2.Seller";
		gotoxy(0, 3);
		color(set[2]);
		cout << "3.Admin";
		gotoxy(0, 4);
		color(set[3]);
		cout << "4.Exit";

		key = _getch();

		if (key == 72 and counter>=1) {
			counter--;
		}

		if (key == 80 and counter<4) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				gotoCustomerEntryPage();
			}
			else if (counter == 2) {
				gotoSellerEntryPage();
			}
			else if(counter==3) {
				gotoAdminEntryPage();
			}
			else {
				color(7);
				exitProgram();
			}

		}
		for (int i = 0; i < 5; i++) {
			set[i] = 7;
		}

		if (counter >= 1) {
			set[(counter - 1)] = 8;
		}
		

	}
	color(7);



}

void Screens::validateCustomerSignUpData() {
	Utils* utils = Utils::getInstance();
	if (utils->isNotEmpty(customer.getName()) && utils->isEmailValid(customer.getEmail()) && utils->isPhoneNumberValid(customer.getPhone()) && utils->isPasswordValid(customer.getPassword()) && utils->isNotEmpty(customer.getAddress())) {
		if(Customer::createCustomer(customer))
		gotoCustomerSignUpConfirmationScreen(true);
		else
			gotoCustomerSignUpConfirmationScreen(false);
	}
	else {
		gotoCustomerSignUpConfirmationScreen(false);
	}
}

void Screens::validateSellerSignUpData() {
	Utils* utils = Utils::getInstance();
	if (utils->isNotEmpty(seller.getName()) && utils->isEmailValid(seller.getEmail()) && utils->isPasswordValid(seller.getPassword())) {
		
		if(Seller::signUp(seller))
		gotoSellerSignUpConfirmationScreen(true);
		else
			gotoSellerSignUpConfirmationScreen(false);
	}
	else {
		gotoSellerSignUpConfirmationScreen(false);
	}
}

void Screens::gotoCustomerSignUpScreen() {
	system("cls");
	string input;
	customer.clearData();
	cout << " ********************* ENTER NEW CUSTOMER ********************* " << endl;
	cout << "- Enter your Name: ";
	cin >> input;
	this->customer.setName(input);
	cout << "- Enter your Email: ";
	cin >> input;
	this->customer.setEmail(input);
	cout << "- Enter your Phone: ";
	cin >> input;
	this->customer.setPhone(input);
	cout << "- Enter your Password: ";
	cin.ignore();
	getline(cin, input);
	this->customer.setPassword(input);
	cout << "- Enter your Address: ";
	getline(cin, input);
	this->customer.setAddress(input);
	validateCustomerSignUpData();
}

void Screens::gotoSellerSignUpScreen() {
	Utils* utils = Utils::getInstance();
	system("cls");
	string input;
	seller.clearData();
	cout << " ********************* ENTER NEW SELLER ********************* " << endl;
	cout << "- Enter your Name: ";
	cin >> input;
	this->seller.setName(input);
	cout << "- Enter your Email: ";
	cin >> input;
	this->seller.setEmail(input);
	cout << "- Enter your Password: ";
	cin.ignore();
	getline(cin, input);
	this->seller.setPassword(input);
	validateSellerSignUpData();
}

void Screens::gotoSellerSignUpConfirmationScreen(bool status) {
	Utils* utils = Utils::getInstance();
	if (status) {
		system("cls");
		cout << " ********************* SELLER SIGNED UP SUCCESSFULLY :) ********************* " << endl;
		cout << " *** MENU ***" << endl;
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "1.Login as a Seller";
			gotoxy(0, 2);
			color(set[1]);
			cout << "2.Go Back";
			gotoxy(0, 3);
			color(set[2]);
			cout << "3.EXIT";

			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoSellerLoginScreen();
				}
				else if (counter == 2) {
					gotoSellerEntryPage();
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
	else {
		system("cls");
		cout << " ********************* SELLER SIGN UP FAILED :( ********************* " << endl;
		cout << " *** MENU ***" << endl;
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "1.Try Again";
			gotoxy(0, 2);
			color(set[1]);
			cout << "2.Go Back";
			gotoxy(0, 3);
			color(set[2]);
			cout << "3.EXIT";

			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoSellerSignUpScreen();
				}
				else if (counter == 2) {
					gotoSellerEntryPage();
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
}

void Screens::gotoCustomerSignUpConfirmationScreen(bool status) {
	Utils* utils = Utils::getInstance();
	if (status) {
		system("cls");
		cout << " ********************* CUSTOMER SIGNED UP SUCCESSFULLY :) ********************* " << endl;
		cout << " *** MENU ***" << endl;
		int set[] = { 7,7,7 }; 
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "1.Login as a Customer";
			gotoxy(0, 2);
			color(set[1]);
			cout << "2.Go Back";
			gotoxy(0, 3);
			color(set[2]);
			cout << "3.EXIT";

			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoCustomerLoginScreen();
					break;
				}
				else if (counter == 2) {
					gotoCustomerEntryPage();
					break;
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
	else {
		system("cls");
		cout << " ********************* CUSTOMER SIGN UP FAILED :( ********************* " << endl;
		cout << " *** MENU ***" << endl;
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "1.Try Again";
			gotoxy(0, 2);
			color(set[1]);
			cout << "2.Go Back";
			gotoxy(0, 3);
			color(set[2]);
			cout << "3.EXIT";

			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoCustomerSignUpScreen();
					break;
				}
				else if (counter == 2) {
					gotoCustomerEntryPage();
					break;
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
}

void Screens::drawMenuCustomerSeller(string type) {
	int set[] = { 7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 1);
		color(set[0]);
		cout << "Sign up";
		gotoxy(0, 2);
		color(set[1]);
		cout << "Login";
		gotoxy(0, 3);
		color(set[2]);
		cout << "Back to Choose User type";

		key = _getch();

		if (key == 72 and (counter == 2 or counter == 3)) {
			counter--;
		}
		if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				if (type == "customer") {
					gotoCustomerSignUpScreen();
				}
				else if (type == "seller") {
					gotoSellerSignUpScreen();
				}

			}
			else if (counter == 2) {
				if (type == "customer") {
					gotoCustomerLoginScreen();
				}
				else if (type == "seller") {
					gotoSellerLoginScreen();
				}
				else if (type == "admin") {
					gotoAdminLoginScreen();
				}
			}
			else {
				color(7);
				if (type == "customer") {
					gotoChooseUserTypeScreen();
				}
				else if (type == "seller") {
					gotoChooseUserTypeScreen();
				}
				else if (type == "admin") {
					gotoChooseUserTypeScreen();
				}
			}

		}
		set[0] = 7;
		set[1] = 7;
		set[2] = 7;
		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		if (counter == 3) {
			set[2] = 8;
		}
	}
	color(7);
}

void Screens::drawMenuAdmin(string type) {
	int set[] = { 7,7,7 }; 
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 1);
		color(set[0]);
		cout << "Login";
		gotoxy(0, 2);
		color(set[1]);
		cout << "Back to Choose User type";

		key = _getch();

		if (key == 72 and (counter == 2 or counter == 3)) {
			counter--;
		}
		if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				gotoAdminLoginScreen();

			}
			else if (counter == 2) {
				gotoChooseUserTypeScreen();
			}
		}
		set[0] = 7;
		set[1] = 7;

		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		color(7);
	}
}

void Screens::gotoCustomerEntryPage() {
	CurrentUser* user = CurrentUser::getInstance();
	user->setType("Customer");
	system("cls");
	cout << "********************* WELCOME TO Customer Page :) *********************\n";
	drawMenuCustomerSeller("customer");
}

void Screens::gotoSellerEntryPage() {
	CurrentUser* user = CurrentUser::getInstance();
	user->setType("Seller");
	system("cls");
	cout << "********************* WELCOME TO Seller Page :) *********************\n";
	drawMenuCustomerSeller("seller");
}

void Screens::gotoAdminEntryPage() {
	CurrentUser* user = CurrentUser::getInstance();
	user->setType("Admin");
	system("cls");
	cout << "********************* WELCOME TO Admin Page :) *********************\n";
	drawMenuAdmin("admin");
}

void Screens::gotoCustomerLoginScreen() {
	system("cls");
	customer.clearData();
	string email, password;
	cout << " ********************* Customer Login ********************* " << endl;
	cout << "Enter Email\n";
	cin >> email;
	cout << "Enter Password\n";
	cin >> password;
	customer.setEmail(email);
	customer.setPassword(password);
	Utils* utils = Utils::getInstance();
	if (utils->isEmailValid(email) && utils->isPasswordValid(password) && Customer::loginCustomer(customer)) {
		gotoCustomerHomePage();
	}
	else {
		system("cls");
		cout << "Invalid Information\n";
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "Login Again";
			gotoxy(0, 2);
			color(set[1]);
			cout << "Back Menu";
			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoCustomerLoginScreen();
				}
				else {
					color(7);
					gotoCustomerEntryPage();
				}

			}

			set[0] = 7;
			set[1] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}

		}
		color(7);
	}

}
void Screens::gotoSellerLoginScreen() {
	Routes* routes = Routes::getInstance();
	system("cls");
	Seller s;
	string email, password;
	cout << " ********************* Seller Login ********************* " << endl;
	cout << "Enter Email\n";
	cin >> email;
	cout << "Enter Password\n";
	cin >> password;
	cin.ignore();
	s.setEmail(email);
	s.setPassword(password);
	Utils* utils = Utils::getInstance();
	if (utils->isEmailValid(email) && utils->isPasswordValid(password) && Seller::login(s)) {
		navigate(routes->sellerHomePageScreenRoute);
	}
	else {
		system("cls");
		cout << "Invalid Information\n";
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "Login Again";
			gotoxy(0, 2);
			color(set[1]);
			cout << "Go back";
			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoSellerLoginScreen();
				}
				else {
					color(7);
					gotoSellerEntryPage();
				}

			}

			set[0] = 7;
			set[1] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			color(7);
		}


	}
}
void Screens::gotoAdminLoginScreen() {
	Routes* routes = Routes::getInstance();
	system("cls");
	Admin a;
	string email, password;
	cout << " ********************* Admin Login ********************* " << endl;
	cout << "Enter Email\n";
	cin >> email;
	cout << "Enter Password\n";
	cin >> password;
	a.setEmail(email);
	a.setPassword(password);
	cin.ignore();
	Utils* utils = Utils::getInstance();
	if (utils->isEmailValid(email) && utils->isPasswordValid(password) && Admin::loginAdmin(a)) {
		navigate(routes->AdminHomePageScreenRoute);
	}
	else {
		system("cls");
		cout << "Invalid Information\n";
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 1);
			color(set[0]);
			cout << "Login Again";
			gotoxy(0, 2);
			color(set[1]);
			cout << "Back Menu";
			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 0)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoAdminLoginScreen();
				}
				else {
					color(7);
					gotoAdminEntryPage();
				}

			}

			set[0] = 7;
			set[1] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}

		}
		color(7);
	}


}

void Screens::gotoCustomerHomePage() {
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	system("cls");
	cout << "********************* CUSTOMER HOME PAGE *********************" << endl;
	cout << "    -- CHOOSE AN ACTION --    " << endl;
	int set[] = { 7,7,7,7,7,7,7,7};
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 2);
		color(set[0]);
		cout << "    1.Browse Products";
		gotoxy(0, 3);
		color(set[1]);
		cout << "    2.Check your Wallet";
		gotoxy(0, 4);
		color(set[2]);
		cout << "    3.Check your Favourites";
		gotoxy(0, 5);
		color(set[3]);
		cout << "    4.Check your Cart";
		gotoxy(0, 6);
		color(set[4]);
		cout << "    5.See your Checkout History";
		gotoxy(0, 7);
		color(set[5]);
		cout << "    6.Request a Refund";
		gotoxy(0, 8);
		color(set[6]);
		cout << "    7.Delete your Account";
		gotoxy(0, 9);
		color(set[7]);
		cout << "    8.Logout";

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < 8) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				gotoCustomerBrowseScreen();
			}
			else if (counter == 2) {
				gotoWalletScreen();
			}
			else if (counter == 3) {
				navigate(routes->checkFavsScreenRoute);
			}
			else if (counter == 4) {
				navigate(routes->checkCartScreenRoute);
			}
			else if (counter == 5) {
				navigate(routes->viewCheckoutHistoryScreenRoute);
			}
			else if (counter == 6) {
				navigate(routes->requestRefundScreenRoute);
			}
			else if (counter == 7) {
				navigate(routes->deleteAccountScreenRoute);
			}
			else {
				user->clearUserData();
				navigate(routes->chooseUserTypeScreenRoute);
				color(7);
			}

		}

		for (int i = 0; i < 8; i++) {
			set[i] = 7;
		}

		set[counter - 1] = 8;

	}
	color(7);
}

void Screens::gotoCustomerBrowseByNameScreen()
{
	system("cls");
	string input;
	color(7);
	cout << "- Enter Product Name: ";
	cin.ignore();
	getline(cin, input);
	if (Customer::browse(input).size() == 0) {
		cout << "========================= No Products Found! =========================" << endl;
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 4);
			color(set[0]);
			cout << "    - Try again";
			gotoxy(0, 5);
			color(set[1]);
			cout << "    - Go back";
			gotoxy(0, 6);
			color(set[2]);
			cout << "    - Exit";
			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 0 or counter == 2)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoCustomerBrowseScreen();
				}
				else if (counter == 2) {
					gotoCustomerHomePage();
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
	else {
		cout << "============ Search Results ============" << endl;
		productsMenu(Customer::browse(input).size(), Customer::browse(input));
	}
}

void Screens::gotoCustomerBrowseByCategoriesScreen()
{
	system("cls");
	cout << "- Select a category: " << endl;
	Utils* utils = Utils::getInstance();
	size_t cnt = utils->categories.size() + 1;
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = 1; i < cnt + 1; i++) {
			gotoxy(0, i);
			color(v[(i - 1)]);
			if (i == 1) {
				cout << "  - All" << endl;
			}
			else {
				cout << "  - " << utils->categories[i - 2] << endl;
			}
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r') {
			if (counter == 1) {
				browseByCategoryResult = utils->products;
			}
			else {
				browseByCategoryResult = Customer::browseByCategory(utils->categories[counter - 2]);
			}

		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}


	}
	color(7);
	if (browseByCategoryResult.size() > 0) {
		system("cls");
		cout << "============ Search Results ============" << endl;
		productsMenu(browseByCategoryResult.size(), browseByCategoryResult);
	}
	else {
		system("cls");
		cout << "========================= No Products Found! =========================" << endl;
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 4);
			color(set[0]);
			cout << "    - Try again";
			gotoxy(0, 5);
			color(set[1]);
			cout << "    - Go back";
			gotoxy(0, 6);
			color(set[2]);
			cout << "    - Exit";
			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 0 or counter == 2)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoCustomerBrowseScreen();
				}
				else if (counter == 2) {
					gotoCustomerHomePage();
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
	
}

void Screens::gotoCustomerBrowseScreen() {
	system("cls");
	string input;
	cout << "********************* BROWSE PRODUCTS *********************" << endl;
	int set[] = { 7,7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 1);
		color(set[0]);
		cout << "    -Browse By Name";
		gotoxy(0, 2);
		color(set[1]);
		cout << "    -Browse By Categories";
		gotoxy(0, 3);
		color(set[2]);
		cout << "    -Browse By Rate";
		gotoxy(0, 4);
		color(set[3]);
		cout << "    -Back To Home Page";
		key = _getch();

		if (key == 72 and counter>=1) {
			counter--;
		}

		if (key == 80 and counter<4) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				gotoCustomerBrowseByNameScreen();
			}
			else if (counter == 2) {
				gotoCustomerBrowseByCategoriesScreen();
			}
			else if (counter == 3) {
				gotoCustomerBrowseByRateScreen();
			}
			else {
				color(7);
				gotoCustomerHomePage();
			}

		}

		set[0] = 7;
		set[1] = 7;
		set[2] = 7;
		set[3] = 7;

		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		if (counter == 3) {
			set[2] = 8;
		}
		if (counter == 4) {
			set[3] = 8;
		}

	}
}

void Screens::productsMenu(int cnt, vector<Product>products) {
	Utils* utils = Utils::getInstance();
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	size_t startLine = cnt;
	vector<int>v;
	for (int i = 0; i <products.size(); i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, startLine + ((i-startLine) * 10));
			color(v[(i - startLine)]);
			cout << products[(i - startLine)].toString();
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r') {
			gotoProductScreen(products[counter-1]);
		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}


	}
	color(7);
}

void Screens::exitProgram() {
	Utils* utils = Utils::getInstance();
	utils->writeDatabase();
	cout << "\n";
	cout << "Bye Bye :)" << endl;
	exit(0);
}

void Screens::exitMenu(int startLine,string backScreenRoute) {
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	int set[] = { 7,7 }; 
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, startLine);
		color(set[0]);
		cout << "1.Go back";

		gotoxy(0, startLine +1 );
		color(set[1]);
		cout << "2.Exit";

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < 2) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				if (utils->screensOrder.size() > 0) {
					utils->screensOrder.pop();
				}
				navigate(backScreenRoute);
			}
			else {
				color(7);
				exitProgram();
			}

		}

		set[0] = 7;
		set[1] = 7;

		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
	}
	color(7);
}

void Screens::navigate(string screenRoute) {
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	if (screenRoute == routes->viewCheckoutHistoryScreenRoute) {
		gotoSeeCheckoutHistoryScreen();
		utils->screensOrder.push(routes->viewCheckoutHistoryScreenRoute);
	}
	else if (screenRoute == routes->customerHomePageScreenRoute) {
		gotoCustomerHomePage();
		utils->screensOrder.push(routes->customerHomePageScreenRoute);
	}
	else if (screenRoute == routes->checkCartScreenRoute) {
		gotoCheckCartScreen();
		utils->screensOrder.push(routes->checkCartScreenRoute);
	}
	else if (screenRoute == routes->checkoutScreenRoute) {
		gotoCheckoutScreen();
		utils->screensOrder.push(routes->checkoutScreenRoute);
	}
	else if (screenRoute == routes->checkFavsScreenRoute) {
		gotoFavsScreen();
		utils->screensOrder.push(routes->checkFavsScreenRoute);
	}
	else if (screenRoute == routes->requestRefundScreenRoute) {
		gotoRefundScreen();
		utils->screensOrder.push(routes->requestRefundScreenRoute);
	}
	else if (screenRoute == routes->deleteAccountScreenRoute) {
		gotoDeleteAccountScreen();
		utils->screensOrder.push(routes->deleteAccountScreenRoute);
	}
	else if (screenRoute == routes->chooseUserTypeScreenRoute) {
		gotoChooseUserTypeScreen();
		utils->screensOrder.push(routes->chooseUserTypeScreenRoute);
	}
	else if (screenRoute == routes->approveDepositsScreenRoute) {
		gotoApproveDepositsScreen();
		utils->screensOrder.push(routes->approveDepositsScreenRoute);
	}
	else if (screenRoute == routes->finishOrdersScreenRoute) {
		gotoFinishOrdersScreen();
		utils->screensOrder.push(routes->finishOrdersScreenRoute);
	}
	else if (screenRoute == routes->viewDeliveryProductsScreenRoute) {
		gotoViewDeliveryProductsScreen();
		utils->screensOrder.push(routes->viewDeliveryProductsScreenRoute);
	}
	else if (screenRoute == routes->AdminHomePageScreenRoute) {
		gotoAdminHomePageScreen();
		utils->screensOrder.push(routes->AdminHomePageScreenRoute);
	}
	else if (screenRoute == routes->sellerHomePageScreenRoute) {
		gotoSellerHomePageScreen();
		utils->screensOrder.push(routes->sellerHomePageScreenRoute);
	}
	else if (screenRoute == routes->commentScreenRoute) {
		utils->screensOrder.push(routes->sellerHomePageScreenRoute);
	}
}

void Screens::gotoCustomerBrowseByRateScreen() {
	system("cls");
	cout << "******************** BrowseByRate**************\n";
	Utils* utils = Utils::getInstance();
	int cnt = 7;
	int counter = 0;
	char key = '0';
	string rates[6] = { " >= 0.0"," >= 1.0", " >= 2.0", " >= 3.0", " >= 4.0", " = 5.0" };
	const int normalColor = 7;
	vector<int>v;
	for (int i = 0; i < 8; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = 1; i <7; i++) {
			gotoxy(0, i);
			color(v[(i - 1)]);
			if (i == 1) {
				cout << "  - All" << endl;
			}
			else {
				cout << "-"<<rates[i-1] << endl;
			}
		}

		key = _getch();

		if (key == 72 and counter >1) {
			counter--;
		}

		if (key == 80 and counter < 6 ) {
			counter++;
		}
		if (key == '\r') {

			switch (counter) {
			case 1: {
				browseByRateResult = Customer::browseByRate(0.0);
				break;
			}
			case 2: {
				browseByRateResult = Customer::browseByRate(1.0);
				break;
			}
			case 3: {
				browseByRateResult = Customer::browseByRate(2.0);
				break;
			}
			case 4: {
				browseByRateResult = Customer::browseByRate(3.0);
				break;
			}
			case 5: {
				browseByRateResult = Customer::browseByRate(4.0);
				break;
			}
			case 6: {
				browseByRateResult = Customer::browseByRate(5.0);
				break;
			}
			}
			
		}

		for (int i = 0; i < 6; i++) {
			v[i] = 7;
		}

		if (counter > 0) {
			v[(counter - 1)] = 8;
		}
	}
	color(7);
	if (browseByRateResult.size() > 0) {
		system("cls");
		cout << "============ Search Results ============" << endl;
		productsMenu(browseByRateResult.size(), browseByRateResult);
		color(7);
	}else{
		system("cls");
		cout << "========================= No Products Found! =========================" << endl;
		int set[] = { 7,7,7 };
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, 4);
			color(set[0]);
			cout << "    - Try again";
			gotoxy(0, 5);
			color(set[1]);
			cout << "    - Go back";
			gotoxy(0, 6);
			color(set[2]);
			cout << "    - Exit";
			key = _getch();

			if (key == 72 and (counter == 2 or counter == 3)) {
				counter--;
			}

			if (key == 80 and (counter == 1 or counter == 0 or counter == 2)) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					gotoCustomerBrowseScreen();
				}
				else if (counter == 2) {
					gotoCustomerHomePage();
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter == 1) {
				set[0] = 8;
			}
			if (counter == 2) {
				set[1] = 8;
			}
			if (counter == 3) {
				set[2] = 8;
			}

		}
		color(7);
	}
}

void Screens::gotoWalletScreen() {
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	Wallet userWallet;
	Customer customer;
	for (int i = 0; i < utils->wallets.size(); i++) {
		if (utils->wallets[i].getUserId() == user->getId()) {
			userWallet = utils->wallets[i];
		}
	}
	for (int i = 0; i < utils->customers.size(); i++) {
		if (utils->customers[i].getId() == user->getId()) {
			customer = utils->customers[i];
		}
	}
	system("cls");
	cout << "================= Your Wallet =================" << endl;
	cout << " == Account balance: " << userWallet.getWalletAmount() << endl;
	cout << " == Account points: " << customer.getPoints() << endl;
	cout << " == Actions to take: == " << endl;
	int set[] = { 7,7,7,7 }; 
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 4);
		color(set[0]);
		cout << "   - 1.Deposit";

		gotoxy(0, 5);
		color(set[1]);
		cout << "   - 2.Convert Points";
		gotoxy(0, 6);
		color(set[2]);
		cout << "   - 3.Go back";
		gotoxy(0, 7);
		color(set[3]);
		cout << "   - 4.Exit";

		key = _getch();

		if (key == 72 and counter >= 1) {
			counter--;
		}

		if (key == 80 and counter < 4) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				gotoDepositScreen();
			}
			else if (counter == 2) {
				gotoConvertPointsScreen();
			}
			else if (counter == 3) {
				gotoCustomerHomePage();
			}
			else {
				color(7);
				exitProgram();
			}

		}

		set[0] = 7;
		set[1] = 7;
		set[2] = 7;
		set[3] = 7;

		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		if (counter == 3) {
			set[2] = 8;
		}
		if (counter == 4) {
			set[3] = 8;
		}

	}
	color(7);
}

void Screens::gotoDepositScreen() {
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	system("cls");
	bool isFound = false;
	int startLine = 3;
	cout << "================= Deposit =================" << endl;
	for (int i = 0; i < utils->depositRequests.size(); i++) {
		if (utils->depositRequests[i].getUserId() == user->getId()) {
			isFound = true;
			break;
		}
	}
	if (!isFound) {
		Wallet userWallet;
		float amount;
		for (int i = 0; i < utils->wallets.size(); i++) {
			if (utils->wallets[i].getUserId() == user->getId()) {
				userWallet = utils->wallets[i];
			}
		};
		cout << " == Enter amount: ";
		cin >> amount;
		userWallet.requestDeposit(amount);
		startLine += 1;
	}
	cout << " *** Deposit is waiting for confirmation ***" << endl;
	cout << " == Actions to take: == " << endl;
	int set[] = { 7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, startLine);
		color(set[0]);
		cout << "   - 1.Go back";

		gotoxy(0, startLine + 1);
		color(set[1]);
		cout << "   - 2.Exit";

		key = _getch();

		if (key == 72 and counter >= 1) {
			counter--;
		}

		if (key == 80 and counter < 2) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				gotoCustomerHomePage();
			}
			else {
				color(7);
				exitProgram();
			}

		}

		set[0] = 7;
		set[1] = 7;

		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}

	}
	color(7);
}

void Screens::gotoConvertPointsScreen() {
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	Customer customer;
	for (int i = 0; i < utils->customers.size(); i++) {
		if (utils->customers[i].getId() == user->getId()) {
			customer = utils->customers[i];
			break;
		}
	}
	Wallet userWallet;
	for (int i = 0; i < utils->wallets.size(); i++) {
		if (utils->wallets[i].getUserId() == user->getId()) {
			userWallet = utils->wallets[i];
			break;
		}
	};
	system("cls");
	float points;
	cout << "================= Convert Points =================" << endl;
	cout << " == Enter points: ";
	cin >> points;
	if (customer.convertPointstoCash(points)) {
		cout << " ***** Conversion Done Successfully!, Your Account Balance is " << userWallet.getWalletAmount() << " *****"<< endl;
	}
	else {
		cout << " ***** Conversion Failed! *****" << endl;
	}
	cout << " == Actions to take: == " << endl;
	int set[] = { 7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 4);
		color(set[0]);
		cout << "   - 1.Go back";
		gotoxy(0, 7);
		color(set[1]);
		cout << "   - 2.Exit";

		key = _getch();

		if (key == 72 and counter >= 1) {
			counter--;
		}

		if (key == 80 and counter < 2) {
			counter++;
		}

		if (key == '\r') {
			if (counter == 1) {
				gotoCustomerHomePage();
			}
			else {
				color(7);
				exitProgram();
			}
		}

		set[0] = 7;
		set[1] = 7;
		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
	}
	color(7);
}

void Screens::gotoSeeCheckoutHistoryScreen() {
	system("cls");
	cout << "================= SEE YOUR CHECKOUT HISTORY =================" << endl;
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	int counter = 0;
	char key = '0';
	vector<Order> orders = Customer::viewCheckoutHistory();
	size_t cnt = orders.size();
	if (cnt == 0) {
		cout << "********* NO HISTORY *********" << endl;
		exitMenu(2, routes->customerHomePageScreenRoute);
	}
	else {
		for (int i = 0; i < cnt; i++) {
			cout << orders[i].toString() << endl;
		}
		exitMenu(((cnt*6) + 2), routes->customerHomePageScreenRoute);
	}
}

void Screens::gotoCheckCartScreen() {
	system("cls");
	cout << "================= CHECK YOUR CART =================" << endl;
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	int counter = 0;
	char key = '0';
	vector<Product> products;
	CurrentUser* user = CurrentUser::getInstance();
	int index = 0;
	for (int i = 0; i < utils->carts.size(); i++) {
		if (utils->carts[i].getUserId() == user->getId()) {
			products = utils->carts[i].getProductsInCart();
			index = i;
			break;
		}
	}
	size_t cnt = products.size();
	if (cnt == 0) {
		cout << "********* YOUR CART IS EMPTY *********" << endl;
		exitMenu(2, routes->customerHomePageScreenRoute);
	}
	else {
		for (int i = 0; i < cnt; i++) {
			cout << products[i].toString() << endl;
		}
		int set[] = { 7,7,7,7 };
		int startLine = (cnt * 10) + 2;
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, startLine + 1);
			color(set[0]);
			cout << "1.Checkout";

			gotoxy(0, startLine + 2);
			color(set[1]);
			cout << "2.Remove Product";

			gotoxy(0, startLine + 3);
			color(set[2]);
			cout << "3.Go back";

			gotoxy(0, startLine + 4);
			color(set[3]);
			cout << "4.Exit";

			key = _getch();

			if (key == 72 and counter > 1) {
				counter--;
			}

			if (key == 80 and counter < 4) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					navigate(routes->checkoutScreenRoute);
				}
				else if (counter == 2) {
					cout << "\nEnter Product Number: ";
					int input;
					cin >> input;
					if (input <= products.size()) {
						utils->carts[index].removeProduct(products[input - 1]);
						cout << "Product Removed Successfully!" << endl;
						exitMenu(3 + (cnt * 10), routes->customerHomePageScreenRoute);
					}
					else {
						system("cls");
						cout << "********* INVALID CHOICE *********" << endl;
						exitMenu(2, routes->customerHomePageScreenRoute);
					}
				}
				else if (counter == 3) {
					if (utils->screensOrder.size() > 0) {
						utils->screensOrder.pop();
					}
					navigate(routes->customerHomePageScreenRoute);
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;
			set[3] = 7;

			if (counter > 0) {
				set[counter - 1] = 8;
			}
		}
		color(7);
	}
}

void Screens::gotoCheckoutScreen() {
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	system("cls");
	cout << "================= CHECKOUT =================" << endl;
	cout << "====== ENTER YOUR EMAIL TO CONFIRM CHECKOUT: ";
	string input;
	cin >> input;
	bool result = false;
	if (input == user->getEmail()) {
		int counter = 0;
		char key = '0';
		for (int i = 0; i < utils->customers.size(); i++) {
			if (utils->customers[i].getId() == user->getId()) {
				result = utils->customers[i].checkOut();
				break;
			}
		}
	}
	if (!result) {
		cout << "********* CHECKOUT FAILED!, TRY AGAIN LATER. *********" << endl;
	}
	else {
		cout << "********* CHECKOUT DONE SUCCESSFULLY *********" << endl;
	}
	exitMenu(3, routes->customerHomePageScreenRoute);
}

void Screens::gotoFavsScreen() {
	system("cls");
	cout << "================= CHECK YOUR FAVS =================" << endl;
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	int counter = 0;
	char key = '0';
	vector<Product> products;
	int index = 0;
	CurrentUser* user = CurrentUser::getInstance();
	for (int i = 0; i < utils->customers.size(); i++) {
		if (utils->customers[i].getId() == user->getId()) {
			index = i;
			break;
		}
	}
	for (int i = 0; i < utils->customers[index].getFavs().size(); i++) {
		for (int j = 0; j < utils->products.size(); j++) {
			if (utils->products[j].getId() == utils->customers[index].getFavs()[i]) {
				products.push_back(utils->products[j]);
				break;
			}
		}
	}
	size_t cnt = products.size();
	if (cnt == 0) {
		cout << "********* YOUR FAVOURITES LIST IS EMPTY *********" << endl;
		exitMenu(2, routes->customerHomePageScreenRoute);
	}
	else {
		for (int i = 0; i < cnt; i++) {
			cout << products[i].toString() << endl;
		}
		int set[] = { 7,7,7 };
		int startLine = (cnt * 10) + 2;
		int counter = 0;
		char key = '0';
		while (key != '\r') {
			gotoxy(0, startLine + 1);
			color(set[0]);
			cout << "1.Remove Product";

			gotoxy(0, startLine + 2);
			color(set[1]);
			cout << "2.Go back";

			gotoxy(0, startLine + 3);
			color(set[2]);
			cout << "3.Exit";

			key = _getch();

			if (key == 72 and counter > 1) {
				counter--;
			}

			if (key == 80 and counter < 3) {
				counter++;
			}
			if (key == '\r') {

				if (counter == 1) {
					cout << "\nEnter Product Number: ";
					int input;
					cin >> input;
					if (input <= products.size()) {
						utils->customers[index].removeProductFromFavs(utils->customers[index].getFavs()[input-1]);
					}
					else {
						system("cls");
						cout << "********* INVALID CHOICE *********" << endl;
						exitMenu(2, routes->customerHomePageScreenRoute);
					}
				}
				else if (counter == 2) {
					if (utils->screensOrder.size() > 0) {
						utils->screensOrder.pop();
					}
					navigate(routes->customerHomePageScreenRoute);
				}
				else {
					color(7);
					exitProgram();
				}

			}

			set[0] = 7;
			set[1] = 7;
			set[2] = 7;

			if (counter > 0) {
				set[counter - 1] = 8;
			}
		}
		color(7);
	}
}

void Screens::gotoRefundScreen() {
	system("cls");
	cout << "================= REQUEST A REFUND =================" << endl;
	Utils* utils = Utils::getInstance();
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	vector<Order> orders = Customer::viewCheckoutHistory();
	size_t cnt = orders.size();
	int startLine = 2;
	int numOfLines = 6;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, startLine + ((i - startLine) * numOfLines));
			color(v[(i - startLine)]);
			cout << orders[(i - startLine)].toString();
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r') {
			if (counter > 0) {
				vector<Product> orderProducts = orders[counter - 1].getOrderProducts();

			}
		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}


	}
	color(7);
}
void Screens::showProductsMenu(vector<Product> products) {
	system("cls");
	cout << "================= REQUEST A REFUND =================" << endl;
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	Routes* routes = Routes::getInstance();
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	size_t cnt = products.size();
	int startLine = 2;
	int numOfLines = 10;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, startLine + ((i - startLine) * numOfLines));
			color(v[(i - startLine)]);
			cout << products[(i - startLine)].toString();
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r' and counter > 1) {
			system("cls");
			cout << "================= REQUEST A REFUND =================" << endl;
			cout << "Do you really want to refund this product? Y|N : ";
			char input;
			cin >> input;
			int index = 0;
			if (input == 'Y') {
				for (int i = 0; i < utils->customers.size(); i++) {
					if (utils->customers[i].getId() == user->getId()) {
						index = i;
						break;
					}
				}
				utils->customers[index].refund(products[counter - 1]);
			}
			exitMenu(2, routes->requestRefundScreenRoute);
		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}
	}
	color(7);
}

void Screens::gotoDeleteAccountScreen() {
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	Routes* routes = Routes::getInstance();
	system("cls");
	cout << "================= DELETE ACCOUNT =================" << endl;
	cout << "Do you really want to delete this account? Y|N : ";
	char input;
	cin >> input;
	int index = 0;
	if (input == 'Y') {
		for (int i = 0; i < utils->customers.size(); i++) {
			if (utils->customers[i].getId() == user->getId()) {
				index = i;
				break;
			}
		}
		utils->customers[index].deleteUser();
	}
	exitMenu(2, routes->chooseUserTypeScreenRoute);
}

void Screens::gotoApproveDepositsScreen() {
	system("cls");
	cout << "================= APPROVE DEPOSIT REQUEST =================" << endl;
	cout << "=== PRESS ENTER ON REQUEST TO APPROVE IT ===" << endl;
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	size_t cnt = utils->depositRequests.size();
	int startLine = 2;
	int numOfLines = 4;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r' && key!= 27) {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, startLine + ((i - startLine) * numOfLines));
			color(v[(i - startLine)]);
			cout << utils->depositRequests[(i - startLine)].toString();
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r') {
			if (counter > 0) {
				int adminIndex = 0;
				for (int i = 0; i < utils->admins.size(); i++) {
					if (utils->admins[i].getId() == user->getId()) {
						adminIndex = i;
					}
				}
				utils->admins[adminIndex].approveDepositRequest(utils->depositRequests[counter-1]);
				utils->depositRequests.erase(utils->depositRequests.begin() + (counter - 1));
				gotoApproveDepositsScreen();
				break;
			}
		}

		if (key == 27) {
			system("cls");
			exitMenu(0, routes->AdminHomePageScreenRoute);
		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}


	}
	color(7);
}

void Screens::gotoFinishOrdersScreen() {
	system("cls");
	cout << "================= FINISH ORDERS =================" << endl;
	cout << "=== PRESS ENTER ON ORDER TO FINISH IT ===" << endl;
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	int index = 0;
	for (int i = 0; i < utils->sellers.size(); i++) {
		if (utils->sellers[i].getId() == user->getId()) {
			index = i;
		}
	}
	vector<Order> orders;
	for (int i = 0; i < utils->sellers[index].getProductsAdded().size(); i++) 
	{
		orders.insert(orders.end(), utils->productsOrders[utils->sellers[index].getProductsAdded()[i]].getProductOrders().begin(), utils->productsOrders[utils->sellers[index].getProductsAdded()[i]].getProductOrders().end());
	}
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i].getIsActivated() == false) {
			orders.erase(orders.begin() + i);
		}
	}
	size_t cnt = orders.size();
	int startLine = 2;
	int numOfLines = 6;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, startLine + ((i - startLine) * numOfLines));
			color(v[(i - startLine)]);
			cout << orders[(i - startLine)].toString();
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r') {
			if (counter > 0) {
				for (int i = 0; i < utils->orders.size(); i++) {
					if (utils->orders[i].getId() == orders[counter - 1].getId()) {
						utils->orders[i].setIsActivated(false);
					}
				}
				gotoFinishOrdersScreen();
				break;
			}
		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}


	}
	color(7);
}

void Screens::gotoViewDeliveryProductsScreen() {
	system("cls");
	cout << "================= VIEW DELIVERY ORDERS =================" << endl;
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	int counter = 0;
	char key = '0';
	vector<Order> orders;
	int index = 0;
	for (int i = 0; i < utils->sellers.size(); i++) {
		if (utils->sellers[i].getId() == user->getId()) {
			index = i;
			break;
		}
	}
	for (int i = 0; i < utils->sellers[index].getProductsAdded().size(); i++) {
		orders.insert(orders.end(), utils->productsOrders[utils->sellers[index].getProductsAdded()[i]].getProductOrders().begin(), utils->productsOrders[utils->sellers[index].getProductsAdded()[i]].getProductOrders().end());
	}
	for (int i = 0; i < orders.size(); i++) {
		if (orders[i].getIsActivated() == false) {
			orders.erase(orders.begin() + i);
		}
	}
	size_t cnt = orders.size();
	if (cnt == 0) {
		cout << "********* NO ORDERS AVAILABLE! *********" << endl;
	}
	else {
		for (int i = 0; i < cnt; i++) {
			cout << orders[i].toString() << endl;
		}
	}
	exitMenu(2, routes->sellerHomePageScreenRoute);
}

void Screens::gotoAdminHomePageScreen() {
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	system("cls");
	cout << "********************* ADMIN HOME PAGE *********************" << endl;
	cout << "    -- CHOOSE AN ACTION --    " << endl;
	int set[] = { 7,7,7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 2);
		color(set[0]);
		cout << "    1.Add Admin";
		gotoxy(0, 3);
		color(set[1]);
		cout << "    2.Add Coupon";
		gotoxy(0, 4);
		color(set[2]);
		cout << "    3.Approve Deposits";
		gotoxy(0, 5);
		color(set[3]);
		cout << "    4.Finish Orders";
		gotoxy(0, 6);
		color(set[4]);
		cout << "    5.Logout";

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < 5) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				gottoaddadminscreeen();
			}
			else if (counter == 2) {
				adminAddCoupon();
			}
			else if (counter == 3) {
				navigate(routes->approveDepositsScreenRoute);
			}
			else if (counter == 4) {
				navigate(routes->finishOrdersScreenRoute);
			}
			else {
				user->clearUserData();
				navigate(routes->chooseUserTypeScreenRoute);
				color(7);
			}

		}

		for (int i = 0; i < 5; i++) {
			set[i] = 7;
		}

		set[counter - 1] = 8;

	}
	color(7);
}

void Screens::gotoSellerHomePageScreen() {
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	system("cls");
	cout << "********************* SELLER HOME PAGE *********************" << endl;
	cout << "    -- CHOOSE AN ACTION --    " << endl;
	int set[] = { 7,7,7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 2);
		color(set[0]);
		cout << "    1.Add Product";
		gotoxy(0, 3);
		color(set[1]);
		cout << "    2.View Delivery Orders";
		gotoxy(0, 4);
		color(set[2]);
		cout << "    3.View Products";
		gotoxy(0, 5);
		color(set[3]);
		cout << "    4.Delete Account";
		gotoxy(0, 6);
		color(set[4]);
		cout << "    5.Logout";

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < 5) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				sellerAddProduct();
				
			}
			else if (counter == 2) {
				navigate(routes->viewDeliveryProductsScreenRoute);
			}
			else if (counter == 3) {
				sellerViewProduct();
			}
			else if (counter == 4) {
				DeleteUser();
			}
			else {
				user->clearUserData();
				navigate(routes->chooseUserTypeScreenRoute);
				color(7);
			}

		}

		for (int i = 0; i < 5; i++) {
			set[i] = 7;
		}

		set[counter - 1] = 8;

	}
	color(7);
}

void Screens::gottoaddadminscreeen()
{
	Routes* routes = Routes::getInstance();
	Utils* utils = Utils::getInstance();
	system("cls");
	Admin a;
	string input;
	cout << " ********************* ENTER NEW Admin ********************* " << endl;
	cout << "- Enter your Name: ";
	cin >> input;
	a.setName(input);
	cout << "- Enter your Email: ";
	cin >> input;
	a.setEmail(input);
	cout << "- Enter your Password: ";
	cin.ignore();
	getline(cin, input);
	a.setPassword(input);
	a.setId(utils->generateId());
	addingAdminPageConfirmationPage(a);
}
void Screens::addingAdminPageConfirmationPage(Admin a)
{
	system("cls");
	cout << " ********************* Adding Admin CONFIRMATION  ********************* " << endl;
	cout << "The Admin " << a.getName() << "Added Successfully\n";
	gottoaddadminscreeen();
}
void Screens::sellerAddProduct()
{
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	cin.ignore();
	system("cls");
	cout << " *********************  Add Product   ********************* " << endl;
	Utils* utils = Utils::getInstance();
	Product added;
	string in;
	float price;
	int quantity = 0;
	int points = 0;
	added.setId(utils->generateId());
	cout << "Name: ";
	getline(cin, in);
	added.setName(in);
	cout << "Description: ";
	getline(cin, in);
	added.setDescription(in);
	cout << "Price: ";
	cin >> price;
	added.setPrice(price);
	cout << "quantity: ";
	cin >> quantity;
	added.setQuantity(quantity);
	cout << "points: ";
	cin >> points;
	added.setPoints(points);
	cout << "categories :-\n";
	int counter = 0, cnt = utils->categories.size();
	char key = '0';
	const int normalColor = 7;
	int startLine = 7;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, i);
			color(v[(i - startLine)]);
			cout << utils->categories[(i - startLine)];
		}
		key = _getch();
		if (key == 72 and counter > 1) {
			counter--;
		}

		// down
		if (key == 80 and counter < cnt) {
			counter++;
		}
		// enter
		if (key == '\r') {
			added.setCategory(utils->categories[counter - 1]);
		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}

	}
	added.setSellerId(user->getId());
	added.setIsActivated(true);
	system("cls");
	if (quantity > 0&& price > 0) {
		CurrentUser* now = CurrentUser::getInstance();
		cout << "Product Added Successfully With Id " << added.getId() << "\n";
		for (int i = 0; i < utils->sellers.size(); i++)
		{
			if (utils->sellers[i].getId() == now->getId()) {
				utils->sellers[i].addNewProduct(added);
			}
		}
		exitMenu(1, routes->sellerHomePageScreenRoute);
	}
	else {
		system("cls");
		cout << "Invalid Information\n";
		exitMenu(1, routes->sellerHomePageScreenRoute);
	}


}
void Screens::sellerViewProduct()
{
	system("cls");
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	for (int i = 0; i < utils->products.size(); i++)
	{
		cout << utils->products[i].toString();
	}
	exitMenu(10 * utils->products.size(), routes->sellerHomePageScreenRoute);
}
void Screens::sellerlogout()
{
	CurrentUser* utils = CurrentUser::getInstance();
	utils->clearUserData();
	gotoChooseUserTypeScreen();
}
void Screens::DeleteUser()
{
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	CurrentUser* now = CurrentUser::getInstance();
	if (now->getType() == "Customer") {
		for (int i = 0; i < utils->customers.size(); i++)
		{
			if (utils->customers[i].getId() == now->getId()) {
				utils->customers[i].deleteUser();
				system("cls");
				exitMenu(0, routes->customerHomePageScreenRoute);
			}
		}
	}
	else if (now->getType() == "Seller") {
		for (int i = 0; i < utils->sellers.size(); i++)
		{
			if (utils->sellers[i].getId() == now->getId()) {
				utils->sellers[i].deleteUser();
				system("cls");
				exitMenu(0, routes->sellerHomePageScreenRoute);
			}
		}
	}
}
void Screens::adminAddCoupon()
{
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	Coupon c;
	float d;
	string in;
	cout << "****************Add Coupon **********************\n";
	cout << "Enter Coupon Name\n";
	cin >> in;
	c.setCoupon(in);
	cout << "Enter Discount Amount\n";
	cin >> d;
	c.setDiscountAmount(d);
	c.setId(utils->generateId());
	utils->coupons.push_back(c);
	exitMenu(4, routes->AdminHomePageScreenRoute);
}
void Screens::ReportASellerPage(string id)
{
	system("cls");
	Routes* routes = Routes::getInstance();
	cout << " ********************* REPORT A SELLER   ********************* " << endl;
	Utils* utils = Utils::getInstance();
	for (int i = 0; i < utils->sellers.size(); i++) {
		if (utils->sellers[i].getId() == id) {
			if (utils->sellers[i].isUserReported(id)) {
				int set[] = { 7,7 };
				int counter = 0;
				char key = '0';
				while (key != '\r') {
					gotoxy(0, 1);
					color(set[0]);
					cout << "RemoveReport";
					gotoxy(0, 2);
					color(set[1]);
					cout << "Back";
					key = _getch();

					// up
					if (key == 72 and (counter == 2 or counter == 3)) {
						counter--;
					}

					// down
					if (key == 80 and (counter == 1 or counter == 0)) {
						counter++;
					}
					// enter
					if (key == '\r') {

						if (counter == 1) {
							utils->sellers[i].removeReport(id);
							system("cls");
							cout << "Done\n";
							exitMenu(1, routes->customerHomePageScreenRoute);
						}
						else {
							color(7);
							system("cls");
							exitMenu(1, routes->customerHomePageScreenRoute);
						}

					}

					set[0] = 7;
					set[1] = 7;

					if (counter == 1) {
						set[0] = 8;
					}
					if (counter == 2) {
						set[1] = 8;
					}

				}
				color(7);
			}
			else{
				int set[] = { 7,7 };
				int counter = 0;
				char key = '0';
				while (key != '\r') {
					gotoxy(0, 1);
					color(set[0]);
					cout << "Report";
					gotoxy(0, 2);
					color(set[1]);
					cout << "Back";
					key = _getch();

					// up
					if (key == 72 and (counter == 2 or counter == 3)) {
						counter--;
					}

					// down
					if (key == 80 and (counter == 1 or counter == 0)) {
						counter++;
					}
					// enter
					if (key == '\r') {

						if (counter == 1) {
							utils->sellers[i].addReport(id);
							system("cls");
							cout << "Done\n";
							exitMenu(1, routes->customerHomePageScreenRoute);
						}
						else {
							color(7);
							system("cls");
							exitMenu(1, routes->customerHomePageScreenRoute);
							break;
						}

					}

					set[0] = 7;
					set[1] = 7;

					if (counter == 1) {
						set[0] = 8;
					}
					if (counter == 2) {
						set[1] = 8;
					}

				}
				color(7);
			}
		}
	}
	system("cls");
	cout << "NotFount\n";
	exitMenu(1, routes->customerHomePageScreenRoute);
}

void Screens::ReactToACommentPage(Comment c)
{
	Routes* routes = Routes::getInstance();
	cout << " ********************* REACT TO A COMMENT  ********************* " << endl;
	int set[] = { 7,7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 1);
		color(set[0]);
		cout << "AddLike";
		gotoxy(0, 2);
		color(set[1]);
		cout << "AddDisLike";
		gotoxy(0, 3);
		color(set[2]);
		cout << "RemoveLike";
		gotoxy(0, 4);
		color(set[3]);
		cout << "RemoveDisLike";
		key = _getch();

		// up
		if (key == 72 and counter >= 1) {
			counter--;
		}

		// down
		if (key == 80 and counter < 4) {
			counter++;
		}
		// enter
		if (key == '\r') {

			if (counter == 1) {
				if (c.addLike(c.getCustomerId())) {
					ReactToACommentPageConfirmationPage();
				}
				else {
					system("cls");
					cout << "Error!\n";
					exitMenu(2, routes->customerHomePageScreenRoute);
				}
			}
			else if (counter == 2) {
				if (c.addDisLike(c.getCustomerId())) {
					ReactToACommentPageConfirmationPage();
				}
				else {
					system("cls");
					cout << "Error!\n";
					exitMenu(2, routes->customerHomePageScreenRoute);
				}
			}
			else if (counter == 3) {
				if (c.removeLike(c.getCustomerId())) {
					ReactToACommentPageConfirmationPage();
				}
				else {
					system("cls");
					cout << "Error!\n";
					exitMenu(2, routes->customerHomePageScreenRoute);
				}
			}
			else if (counter == 4) {
				if (c.removeDislike(c.getCustomerId())) {
					ReactToACommentPageConfirmationPage();
				}
				else {
					system("cls");
					cout << "Error!\n";
					exitMenu(2, routes->customerHomePageScreenRoute);
				}
			}

		}
		set[0] = 7;
		set[1] = 7;
		set[2] = 7;
		set[3] = 7;
		if (counter >= 1 && counter <= 4) {
			set[counter - 1] = 8;
		}

	}
	color(7);
}
void Screens::ReactToACommentPageConfirmationPage()
{
	Routes* routes = Routes::getInstance();
	system("cls");
	cout << " ********************* REACT TO A COMMENT CONFIRMATION  ********************* " << endl;
	cout << "React Added to Comment Successfully\n";
	exitMenu(2, routes->customerHomePageScreenRoute);
}

void Screens::gotoProductScreen(Product product) {
	color(7);
	system("cls");
	cout << "********************* PRODUCT PAGE *********************" << endl;
	cout << product.toString() << endl;
	cout << "    -- CHOOSE AN ACTION --    " << endl;
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	Utils* utils = Utils::getInstance();
	int set[] = { 7,7,7,7,7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 14);
		color(set[0]);
		cout << "    1.Add to Cart";
		gotoxy(0, 15);
		color(set[1]);
		cout << "    2.Add to favs";
		gotoxy(0, 16);
		color(set[2]);
		cout << "    3.Add comment";
		gotoxy(0, 17);
		color(set[3]);
		cout << "    4.Rate Product";
		gotoxy(0, 18);
		color(set[4]);
		cout << "    5.Show Comments";
		gotoxy(0, 19);
		color(set[5]);
		cout << "    6.Report the seller";
		gotoxy(0, 20);
		color(set[6]);
		cout << "    7.Rate the seller";

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < 8) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				system("cls");
				cout << "Enter a Quantity: ";
				int input;
				cin >> input;
				product.setQuantity(input);
				int index = 0;
				for (int i = 0; i < utils->carts.size(); i++) {
					if (utils->carts[i].getUserId() == user->getId()) {
						index = i;
						break;
					}
				}
				if (utils->carts[index].addProductToCart(product)) {
					gotoAddToCartSucceededPage();
				}
				else {
					gotoAddToCartFailedPage();
				}
			}
			else if (counter == 2) {
				int index = 0;
				for (int i = 0; i < utils->customers.size(); i++) {
					if (utils->customers[i].getId() == user->getId()) {
						index = i;
						break;
					}
				}
				if (utils->customers[index].addProductToFavs(product)) {
					gotoAddProdutToFavPage();
				}
				else {
					system("cls");
					cout << "An error occured!" << endl;
					exitMenu(1, routes->customerHomePageScreenRoute);
				}
			}
			else if (counter == 3) {
				gotoAddCommentPage();
			}
			else if (counter == 4) {
				gotoRateProductPage(product);
			}
			else if (counter == 5) {
				showCommentsScreen(product.getComments());
			}
			else if (counter == 6) {
				ReportASellerPage(product.getSellerId());
			}
			else {
				int sellerIndex = 0;
				for (int i = 0; i < utils->sellers.size(); i++) {
					if (utils->sellers[i].getId() == product.getSellerId()) {
						sellerIndex = i;
					}
				}
				gotoRateSellerPage(sellerIndex);
				color(7);
			}

		}

		for (int i = 0; i < 6; i++) {
			set[i] = 7;
		}

		set[counter - 1] = 8;

	}
	color(7);
}

void Screens::showCommentsScreen(vector<Comment> comments) {
	system("cls");
	cout << "********************* PRODUCT COMMENTS *********************" << endl;
	Utils* utils = Utils::getInstance();
	int counter = 0;
	char key = '0';
	const int normalColor = 7;
	int cnt = comments.size();
	size_t startLine = 2;
	vector<int>v;
	for (int i = 0; i < cnt; i++) {
		v.push_back(normalColor);
	}
	while (key != '\r') {
		for (int i = startLine; i < cnt + startLine; i++) {
			gotoxy(0, startLine + ((i - startLine) * 6));
			color(v[(i - startLine)]);
			cout << comments[(i - startLine)].toString();
		}

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < cnt) {
			counter++;
		}
		if (key == '\r') {

			gotoCommentScreen(comments[counter - 1]);

		}

		for (int i = 0; i < cnt; i++) {
			v[i] = 7;
		}

		if (counter >= 1) {
			v[(counter - 1)] = 8;
		}


	}
	color(7);
}
void Screens::gotoCommentScreen(Comment comment) {
	system("cls");
	cout << "********************* COMMENT PAGE *********************" << endl;
	cout << comment.toString();
	cout << "    -- CHOOSE AN ACTION --    " << endl;
	Routes* routes = Routes::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	int set[] = { 7,7,7 };
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 8);
		color(set[0]);
		cout << "    1.React to the comment";
		gotoxy(0, 9);
		color(set[1]);
		cout << "    2.Go back";
		gotoxy(0, 10);
		color(set[2]);
		cout << "    3.Exit";

		key = _getch();

		if (key == 72 and counter > 1) {
			counter--;
		}

		if (key == 80 and counter < 3) {
			counter++;
		}
		if (key == '\r') {

			if (counter == 1) {
				ReactToACommentPage(comment);
			}
			else if (counter == 2) {
				gotoCustomerHomePage();
			}
			else {
				color(7);
				exitProgram();
			}

		}

		for (int i = 0; i < 3; i++) {
			set[i] = 7;
		}

		set[counter - 1] = 8;

	}
	color(7);
}
void Screens::drawMenuAddedToCart() {
	Routes* routes = Routes::getInstance();
	exitMenu(3, routes->customerHomePageScreenRoute);
}

void Screens::drawMenuAddProductToFav() {
	int set[] = { 7,7,7 }; // default colors 
	int counter = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 3);
		color(set[0]);
		cout << "1.Go to your favs";

		gotoxy(0, 4);
		color(set[1]);
		cout << "2.Go back";
		gotoxy(0, 5);
		color(set[2]);
		cout << "3.Exit";

		key = _getch();

		// up
		if (key == 72 and (counter == 2 or counter == 3)) {
			counter--;
		}

		// down
		if (key == 80 and (counter == 1 or counter == 2 or counter == 0)) {
			counter++;
		}
		// enter
		if (key == '\r') {

			if (counter == 1) {
				gotoFavsScreen();
				break;
			}
			else if (counter == 2) {
				gotoCustomerHomePage();
				break;
			}
			else { 
				color(7);
				exitProgram();
				break;
			}

		}

		set[0] = 7;
		set[1] = 7;
		set[2] = 7;

		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		if (counter == 3) {
			set[2] = 8;
		}

	}
	color(7);
}

void Screens::drawMenuAddComment() {
	Routes* routes = Routes::getInstance();
	system("cls");
	cout << "Comment added successfully\n";
	exitMenu(1, routes->customerHomePageScreenRoute);
}
void Screens::gotoAddToCartSucceededPage() {
	system("cls");
	cout << "************* Add Product to Cart ************\n";
	cout << "Product Added to your Cart Successfully\n";
	cout << "________________________________\n";
	drawMenuAddedToCart();
}

void Screens::gotoAddToCartFailedPage() {
	system("cls");
	cout << "************* Add Product to Cart ************\n";
	cout << "Cannot Add Product to Cart\n";
	cout << "________________________________\n";
	drawMenuAddedToCart();
}

void Screens::gotoAddProdutToFavPage() {
	system("cls");
	cout << "****** Add Product to favourites page ******* \n";
	cout << "Product Added to your Favs Successfully\n";
	cout << "________________________________\n";
	drawMenuAddProductToFav();
}

void Screens::gotoAddCommentPage() {
	system("cls");
	cout << "****** Add Comment to Product page ******* \n";
	string com;
	cout << "Enter your comment : ";
	getline(cin, com);

	Comment comment;
	Product product;
	Utils* utils = Utils::getInstance();
	CurrentUser* currentUser = CurrentUser::getInstance();

	comment.setCustomerId(currentUser->getId());
	comment.setContent(com);
	comment.setDate(utils->getCurrentDate());
	product.addComment(comment);

	gotoAddCommentConfermationpage(com);
}

void Screens::gotoAddCommentConfermationpage(string com) {
	if (com != "") {
		drawMenuAddComment();
	}
	else {
		cout << "Invalid comment\n";
	}
}

void Screens::gotoRateProductPage(Product product) {
	system("cls");
	cout << "*****RATE PRODUCT****\n";
	showRateMenue(product);
}

void Screens::showRateMenue(Product product) {
	Utils* utils = Utils::getInstance();
	system("cls");
	cout << "Choose your rate\n";
	int set[] = { 7,7,7,7,7 }; // default colors 
	int counter = 0;
	int index = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 3);
		color(set[0]);
		cout << "1";

		gotoxy(0, 4);
		color(set[1]);
		cout << "2";
		gotoxy(0, 5);
		color(set[2]);
		cout << "3";
		gotoxy(0, 6);
		color(set[3]);
		cout << "4";
		gotoxy(0, 7);
		color(set[4]);
		cout << "5";

		key = _getch();

		// up
		if (key == 72 and (counter == 2 or counter == 3 or counter == 4 or counter == 5)) {
			counter--;
		}

		// down
		if (key == 80 and (counter != 5)) {
			counter++;
		}
		// enter
		if (key == '\r') {
			for (int i = 0; i < utils->products.size(); i++) {
				if (utils->products[i].getId() == product.getId()) {
					index = i;
				}
			}
			gotoxy(0, 9);
			if (counter == 1) {
				utils->products[index].updateRating(1);
				cout << "Thanks for your Rate! (1)\n";
				break;
			}
			else if (counter == 2) {
				utils->products[index].updateRating(2);
				cout << "Thanks for your Rate! (2)\n";

				break;
			}
			else if (counter == 3) {
				utils->products[index].updateRating(3);
				cout << "Thanks for your Rate! (3)\n";

				break;
			}
			else if (counter == 4) {
				utils->products[index].updateRating(4);
				cout << "Thanks for your Rate! (4)\n";

				break;
			}
			else if (counter == 5) {
				utils->products[index].updateRating(5);
				cout << "Thanks for your Rate! (5)\n";

				color(7);
				break;
			}

		}

		set[0] = 7;
		set[1] = 7;
		set[2] = 7;
		set[3] = 7;
		set[4] = 7;


		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		if (counter == 3) {
			set[2] = 8;
		}
		if (counter == 4) {
			set[3] = 8;
		}
		if (counter == 5) {
			set[4] = 8;

		}

	}
	color(7);
	drawMenuRatePage();
}

void Screens::drawMenuRatePage() {
	Routes* routes = Routes::getInstance();
	system("cls");
	cout << "Rate Confirmed \n";
	exitMenu(1, routes->customerHomePageScreenRoute);
}

void Screens::gotoRateSellerPage(int sellerIndex) {
	color(7);
	Utils* utils = Utils::getInstance();
	Routes* routes = Routes::getInstance();
	system("cls");
	cout << "**************** RATE A SELLER **************" << endl;;
	cout << "Choose your rate\n";
	int set[] = { 7,7,7,7,7 }; // default colors 
	int counter = 0;
	int index = 0;
	char key = '0';
	while (key != '\r') {
		gotoxy(0, 2);
		color(set[0]);
		cout << "1";

		gotoxy(0, 3);
		color(set[1]);
		cout << "2";
		gotoxy(0, 4);
		color(set[2]);
		cout << "3";
		gotoxy(0, 5);
		color(set[3]);
		cout << "4";
		gotoxy(0, 6);
		color(set[4]);
		cout << "5";

		key = _getch();

		// up
		if (key == 72 and (counter == 2 or counter == 3 or counter == 4 or counter == 5)) {
			counter--;
		}

		// down
		if (key == 80 and (counter != 5)) {
			counter++;
		}
		// enter
		if (key == '\r') {
			gotoxy(0, 9);
			if (counter == 1) {
				utils->sellers[sellerIndex].updateRating(1);
				cout << "Thanks for your Rate! (1)\n";
				exitMenu(11, routes->customerHomePageScreenRoute);
				break;
			}
			else if (counter == 2) {
				utils->sellers[sellerIndex].updateRating(2);
				cout << "Thanks for your Rate! (2)\n";
				exitMenu(11, routes->customerHomePageScreenRoute);
				break;
			}
			else if (counter == 3) {
				utils->sellers[sellerIndex].updateRating(3);
				cout << "Thanks for your Rate! (3)\n";
				exitMenu(11, routes->customerHomePageScreenRoute);
				break;
			}
			else if (counter == 4) {
				utils->sellers[sellerIndex].updateRating(4);
				cout << "Thanks for your Rate! (4)\n";
				exitMenu(11, routes->customerHomePageScreenRoute);
				break;
			}
			else if (counter == 5) {
				utils->sellers[sellerIndex].updateRating(5);
				cout << "Thanks for your Rate! (5)\n";
				exitMenu(11, routes->customerHomePageScreenRoute);
				color(7);
				break;
			}

		}

		set[0] = 7;
		set[1] = 7;
		set[2] = 7;
		set[3] = 7;
		set[4] = 7;


		if (counter == 1) {
			set[0] = 8;
		}
		if (counter == 2) {
			set[1] = 8;
		}
		if (counter == 3) {
			set[2] = 8;
		}
		if (counter == 4) {
			set[3] = 8;
		}
		if (counter == 5) {
			set[4] = 8;

		}

	}
	color(7);
}
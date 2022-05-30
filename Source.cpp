#include <iostream>
#include "Screens.h"
using namespace std;
int main() {
	Screens* screens = Screens::getInstance();
	Utils* utils = Utils::getInstance();
	utils->readDatebase();
	cout << "********************* WELCOME TO OMARKET STORE :) *********************\n";
	screens->gotoChooseUserTypeScreen();
}
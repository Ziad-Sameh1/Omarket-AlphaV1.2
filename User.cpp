#include "User.h"

void User::createUser() {}
void User::loginUser() {}
void User::deleteUser() {}
void User::userLogout() {}

string User::getId() {
	return this->id;
}
string User::getEmail() {
	return this->email;
}
string User::getName() {
	return this->name;
}
string User::getPassword() {
	return this->password;
}

void User::setId(string id) {
	this->id = id;
}
void User::setEmail(string email) {
	this->email = email;
}
void User::setName(string name) {
	this->name = name;
}
void User::setPassword(string password) {
	this->password = password;
}
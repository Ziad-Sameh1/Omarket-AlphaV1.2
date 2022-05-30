#include "Wallet.h"
#include "Utils.h"
#include "DepositRequests.h"
#include "CurrentUser.h"

Wallet::Wallet() {
	amount = 0;
}

Wallet::~Wallet() {}

void Wallet::setUserId(string userId) {
	this->userId = userId;
}

void Wallet::setAmount(float amount) {
	this->amount = amount;
}

string Wallet::getUserId()
{
	return this->userId;
}

float Wallet::getWalletAmount()
{
	return this->amount;
}
// deposit
void Wallet::deposit(string userId, float amount) {
	Utils* utils = Utils::getInstance();
	size_t walletsCnt = utils->wallets.size();
	for (int i = 0; i < walletsCnt; i++) {
		if (utils->wallets[i].getUserId() == userId) {
			utils->wallets[i].setAmount(utils->wallets[i].getWalletAmount() + amount);
			break;
		}
	}
}

// withdraw
void Wallet::withDraw(string userId, float amount) {
	Utils* utils = Utils::getInstance();
	size_t walletsCnt = utils->wallets.size();
	for (int i = 0; i < walletsCnt; i++) {
		if (utils->wallets[i].getUserId() == userId) {
			utils->wallets[i].setAmount(utils->wallets[i].getWalletAmount() - amount);
			break;
		}
	}
}

// request deposit
void Wallet::requestDeposit(float amount) {
	Utils* utils = Utils::getInstance();
	CurrentUser* user = CurrentUser::getInstance();
	DepositRequests dr;
	dr.setUserId(user->getId());
	dr.setAmount(amount);
	// no status
	utils->depositRequests.push_back(dr);
}
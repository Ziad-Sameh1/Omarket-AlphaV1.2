#include "Admin.h"
#include "Utils.h"

Admin::Admin() {}


bool Admin::createAdmin(Admin obj) {
    Utils* generator = Utils::getInstance();
    bool found = false;
    for (int i = 0; i < generator->admins.size(); ++i) {
        if (generator->admins[i].getEmail() == obj.getEmail()) {
            found = true;
            break;
        }
    }
        generator->admins.push_back(obj);
        return true;
}

bool Admin::loginAdmin(Admin obj) {
    Utils* utils = Utils::getInstance();
    for (int i = 0; i < utils->admins.size(); ++i) {
        if (utils->admins[i].getEmail() == obj.getEmail() &&
            utils->admins[i].getPassword() == obj.getPassword()) {
            utils->setLoggedInUserData(utils->admins[i]);
            return true;
        }
    }
    return false;
}

void Admin::approveDepositRequest(DepositRequests requestID) {
    Utils* utils = Utils::getInstance();
    pair<int, pair<string, float>> data;
    for (int i = 0; i < utils->depositRequests.size(); ++i) {
        if (utils->depositRequests[i].getUserId() == requestID.getUserId()) {
            data.first = i;
            data.second.first = utils->depositRequests[i].getUserId();
            data.second.second = utils->depositRequests[i].getAmount();
            break;
        }
    }
    for (int i = 0; i < utils->wallets.size(); ++i) {
        if (utils->wallets[i].getUserId() == data.second.first) {
            float currentAmount = utils->wallets[i].getWalletAmount() + data.second.second;
            utils->wallets[i].setAmount(currentAmount);
            swap(utils->depositRequests[data.first], utils->depositRequests.back());
            utils->depositRequests.pop_back();
            return;
        }
    }
}

void Admin::showActiveRequests() {
    Utils* utils = Utils::getInstance();
    for (int i = 0; i < utils->depositRequests.size(); ++i) {
        // todo: show request
    }
}

void Admin::showActiveOrders() {
    Utils* utils = Utils::getInstance();
    for (int i = 0; i < utils->orders.size(); ++i) {
        if (utils->orders[i].getIsActivated()) {
            //todo: show active order
        }
    }
}

void Admin::finishActiveOrder(Order obj) {
    Utils* utils = Utils::getInstance();
    for (int i = 0; i < utils->orders.size(); ++i) {
        if (utils->orders[i].getId() == obj.getId()) {
            utils->orders[i].setIsActivated(false);
        }
    }
}

Admin::~Admin() {}
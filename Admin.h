#pragma once
#include "Wallet.h"
#include "User.h"
#include "DepositRequests.h"
#include "Order.h"
#include "CurrentUser.h"

class Admin : public User {
public:
    Admin();

    static bool createAdmin(Admin obj);

    static bool loginAdmin(Admin obj);

    void approveDepositRequest(DepositRequests requestID);

    void showActiveRequests();

    void showActiveOrders();

    void finishActiveOrder(Order obj);

    ~Admin();
};



#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Member.h"
#include "Withdraw.h"
#include "TicketManager.h"
using namespace std;


//class : WithdrawUI
//description : È¸¿øÅ»ÅðUI
//created : 2019/06/03 1:21am
// Author : Á¶À±ÇØ

class WithdrawUI{

public:
	void clickWithdrawButton(ifstream &in_fp,ofstream &out_fp,Withdraw &withdraw);
};
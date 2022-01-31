#include "WithdrawUI.h"



//function : void clickWithdrawButton(ifstream &in_fp, ofstream &out_fp, Withdraw &withdraw);
//description : È¸¿øÅ»Åð UI

void WithdrawUI::clickWithdrawButton(ifstream &in_fp, ofstream &out_fp, Withdraw &withdraw) {
	string id;

	id = withdraw.showWithdrawal();
	out_fp << "1.2 È¸¿øÅ»Åð" << endl;
	//out_fp << "> " << id << endl;
	if (id == "") {
		out_fp << "> È¸¿øÅ»Åð½ÇÆÐ" << endl;
	}
	else {
		out_fp << "> " << id << endl;
	}

}
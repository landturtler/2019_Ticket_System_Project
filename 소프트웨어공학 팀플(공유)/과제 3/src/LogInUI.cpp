#include "LogInUI.h"


//function : void inputLogInInformation(ifstream &in_fp, ofstream &out_fp, LogIn &logIn);
//description : 로그인 UI
//parameter : ifstream &in_fp-파일입력, ofstream &out_fp-파일출력, LogIn &logIn-컨트롤 

void LogInUI::inputLogInInformation(ifstream &in_fp, ofstream &out_fp, LogIn &logIn){

	string inputID, inputPassword;
	bool logInMember;
	out_fp << "2.1. 로그인" << endl;
	in_fp >> inputID >> inputPassword;
	logInMember = logIn.showLogIn(inputID, inputPassword);
	
	if (logInMember == true){

		out_fp << "> " << inputID << " " << inputPassword << endl;
	}
	else{ 
		out_fp << "> 로그인 실패" << endl;
	}

	
}
#include <iostream>
#include <fstream>
#include <string>
#include "SignUpUI.h"
#include "SignUp.h"
using namespace std;

// function : inputSignUpInformation(ifstream &in_fp, ofstream &out_fp)
// description : 회원가입을 위한 정보를 입력하는 함수
// parameter : ifstream &in_fp :인풋파일
//						ofstream &out_fp : 아웃풋파일
// return value : 없음

void SignUpUI::inputSignUpInformation(ifstream &in_fp, ofstream &out_fp, SignUp &signUp) {
	string savedID, savedPassword, name, userTypeBuff;
	int identityNumber, userType;

	out_fp << "1.1. 회원가입" << endl;
	in_fp >> savedID >> savedPassword >> name >> identityNumber >> userTypeBuff;
	userType = (userTypeBuff == "buyer") ? 0 : 1;	 //0이면 buyer, 1이면 seller를 나타냄
	
	signUp.showSignUp(savedID, savedPassword, name, identityNumber, userType);

	out_fp << "> " << savedID << " " << savedPassword << " " << name << " " << identityNumber << " " << userTypeBuff << endl;
}
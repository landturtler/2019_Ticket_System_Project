#include <iostream>
#include <string>
#include "SignUp.h"
#include "MemberManager.h"
using namespace std;

// function : showSignUp(string savedID, string savedPassword, string name, int identityNumber, int userType)
// description : 회원가입을 위한  함수
// parameter : string savedID, 
//						string savedPassword,
//						string name
//						int identityNumber
//						int userType
// return value : 없음

void SignUp::showSignUp(string savedID, string savedPassword, string name, int identityNumber, int userType) {
	MemberManager* membermanager = MemberManager::getInstance();
	membermanager->requestSignUp(savedID, savedPassword, name, identityNumber, userType);
}
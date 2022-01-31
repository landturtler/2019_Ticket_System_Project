#include "LogIn.h"

//function : bool showLogIn(string inputID, string inputPassword)
//description : 로그인을 위한 함수
//parameter : string inputID-입력받은 아이디, string inputPassword-입력받은 패스워드

bool LogIn::showLogIn(string inputID, string inputPassword){
	bool logInMember=false;
	MemberManager *memberManager = MemberManager::getInstance();
	logInMember = memberManager->requestLogIn(inputID, inputPassword);
	return logInMember;
}
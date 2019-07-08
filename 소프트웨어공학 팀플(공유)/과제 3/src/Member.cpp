#include "Member.h"

//function : Member(int userType, string name, int identityNumber, bool logInState, string savedID, string savedPassword)
//description : Member 객체를 생성하는 생성자
/*parameter :
int userType(0/buyer,1/seller)
string name : 사용자 이름
int identityNumber : 사용자 주민번호
bool logInState : 로그인상태 확인(0/false,1/true)
string savedID : 사용자 ID, 유효성 검사시 사용
string savedPassword : 사용자 password,유효성 검사시 사용
*/
Member::Member(int userType, string name, int identityNumber, bool logInState, string savedID, string savedPassword){

	this->userType = userType;
	this->name = name;
	this->identityNumber = identityNumber;
	this->logInState = logInState;
	this->savedID = savedID;
	this->savedPassword = savedPassword;
}

//function : string getPassword()
//description : savedPassword가져오는 함수

string Member::getPassword(){
	return savedPassword;
}

//function : string getID()
//description : savedID가져오는 함수

string Member::getID(){
	return savedID;
}

//function : bool getLogInState()
//description : logInState가져오는 함수(LogIn/out에서 사용)
//default값=false

bool Member::getLogInState(){
	return logInState;
}

//function : int getUserType()
//description : userType리턴함(회원탈퇴시 사용)

int Member::getUserType(){
	return userType;
}

//function : void setLogInState(bool logInState)
//description : 로그인상태 바꿀 때 사용
void Member::setLogInState(bool logInState){
	this->logInState = logInState;
}


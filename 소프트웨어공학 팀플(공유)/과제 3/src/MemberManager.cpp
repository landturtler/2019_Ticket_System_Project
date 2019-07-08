#include "MemberManager.h"

MemberManager*MemberManager::memberManagerInstance = nullptr;
MemberManager::MemberManager(){}
// Function : static MemberManager *getInstance() 
// description : MemberManager객체는 한번만 생성되고 그 이후에는 생성한 객체 반환
MemberManager*MemberManager::getInstance(){
	if (memberManagerInstance == NULL){
		memberManagerInstance = new MemberManager();
	}
	return memberManagerInstance;
}


//Function : void requestLogIn(string inputID,string inputPassword)
// description : 로그인을 처리한다. 만약 없는 ID이거나 비밀번호가 틀린 경우엔 false를 리턴한다.
//				 성공적으로 로그인시 logInMembers에 추가한다.
// parameter : string inputID - 로그인 시도하는 ID
//			   string inputPasswd - 로그인 시도하는 비밀번호
// Return Value: true - 로그인 성공시
//				 false - 로그인 실패시 
bool MemberManager::requestLogIn(string inputID, string inputPasswd) {
	if (members.find(inputID) == members.end()) return false;
	Member* member = members[inputID];
	string memPasswd = member->getPassword();
	if (inputPasswd != memPasswd) return false;
	
	member->setLogInState(true);
	logInMembers.push_back(member->getID());
	changeSession(member->getID());
	
	return true;
}

// Function : void requestLogOut();
// description : 로그아웃을 처리한다. 현재 세션인 멤버가 로그아웃 하는 상황인 것으로 간주한다.
// parameter : None
// Return Value: None
void MemberManager::requestLogOut(){
	string curSessionID = getCurrentSessionID();
	Member* member = members[curSessionID];
	
	member->setLogInState(false);
	for (int i = 0; i < logInMembers.size(); i++) {
		string loginID = logInMembers[i];
		if (loginID == curSessionID) {
			logInMembers.erase(logInMembers.begin() + i);
			changeSession("");
			return;
		}
	}
}


//Function : void requestSignUp(string savedID, string savedPassword, string name, int identityNumber, int userType)
//description : 회원가입 요청함수
//revision: 
//1.when&who : 2019/06/03 02:29:pm
//what : requestSignUp 매개변수 추가 및 구현

void MemberManager::requestSignUp(string savedID, string savedPassword, string name, int identityNumber, int userType){
	if (userType == 0) { //Buyer
		bool loginState = false;
		Buyer *newBuyer = new Buyer(userType, name, identityNumber, loginState, savedID, savedPassword);
		members.insert(make_pair(savedID, newBuyer));
	}
	else { //Seller
		bool loginState = false;
		Seller *newSeller = new Seller(userType, name, identityNumber, loginState, savedID, savedPassword);
		members.insert(make_pair(savedID, newSeller));
	}
}


// Function : void changeSession(string targetID);
// description : 입력받은 회원 id로 세션을 교체한다
//				login중이 아닌 회원id는 주어지지 않는다고 가정함
// parameter : string targetID - 세션을 변경할 ID
// Return Value: None
void MemberManager::changeSession(string targetID) {
	currentSessionID = targetID;
}


// Function : string getCurrentSessionID()
// description : 현재 세션의 ID를 반환함
// parameter : None
// Return Value: currentSessionID
string MemberManager::getCurrentSessionID() {
	return currentSessionID;
}


// Function : void eraseMember(string ID)
// description : 해당 ID의 멤버를 멤버 목록에서 제거함
// parameter : string ID
// Return Value: None
void MemberManager::eraseMember(string ID) {
	members.erase(ID);
}


// Function : void reserveTicket(int ticketID, string buyerID)
// description : buyerID와 티켓 정보를 받아 해당 바이어가 구매한 티켓 목록에 티켓을 추가
// parameter : int ticketID - 구매한 티켓 id
//				string buyerID - 구매자 id
// Return Value: None
void MemberManager::reserveTicket(int ticketID, string buyerID) {
	Member *member = members[buyerID];
	((Buyer*)member)->addBuyersTicketList(ticketID);
}

// Function : Member * MemberManager::getCurrentMemberPtr()
// description : 현재 활성화된 세션의 멤버 포인터 반환
// parameter : None
// Return Value: Member * members[currentSessionID]
Member * MemberManager::getCurrentMemberPtr() {
	return members[currentSessionID];
}


// Function : deleteMembersTicket(int ticketID, string memberID)
// description : 인자로 들어온 member의 티켓 목록 중 ticketID에 해당하는 티켓을 삭제
// parameter : int ticketID, string memberID
// Return Value: None
void MemberManager::deleteMembersTicket(int ticketID, string memberID) {
	Member* mem = members[memberID];
	mem->deleteTicket(ticketID);
}

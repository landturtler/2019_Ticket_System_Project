#include "Withdraw.h"



// Function : string showWithdrawal()
// description : 현재 로그인한 멤버가 회원탈퇴를 할 경우 실행되는 함수
// parameter : None
// Return Value: string ID
// Revisions :
//	1.	When & Who : 2019/06/05 08:08 pm by 박형준
//		What : 회원탈퇴 시 멤버 목록에서 해당 멤버 제거하는 함수 추가 작성
//	2.	When & Who : 2019/06/05 09:02 pm by 박형준
//		What : 참조 오류 수정
string Withdraw::showWithdrawal(){
	int ticketID=0;
	string buyerID;
	string id;
	MemberManager *memberManager = MemberManager::getInstance();
	TicketManager *ticket = TicketManager::getInstance();
	Member *m=memberManager->getCurrentMemberPtr();
	
	if (m->getUserType() == 1){
		//sellerTicketNum = ((Seller*)m)->getSellersTicketList().size();
		vector <int>sellerTicketList = ((Seller*)m)->getSellersTicketList();
		for (vector<int>::iterator iter = sellerTicketList.begin(); iter != sellerTicketList.end();iter++){
			ticketID = *iter;
			buyerID=ticket->getTicket(ticketID).getBuyerID();
			if (buyerID == ""){
				return "";
			}
			
		}
		//return m->getID();
		id=m->getID();
	    memberManager->requestLogOut();
		memberManager->eraseMember(id);
		delete m;
	}
	
	else if (m->getUserType() == 0){
		id = m->getID();
		memberManager->requestLogOut();
		memberManager->eraseMember(id);
		delete m;
	}
	return id;
}
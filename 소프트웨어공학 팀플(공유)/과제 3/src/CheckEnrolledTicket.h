#pragma once
#include <iostream>
#include "Ticket.h"
#include "MemberManager.h"

using namespace std;
// Class : CheckEnrolledTicket
// Description : CheckEnrolledTicket control Ŭ����
// Created : 2019/06/03 23:02pm
// Author : ������
//
// Revision :
//	     1. When & Who : 
//         What : 
class CheckEnrolledTicket {
public:
	vector < pair<int, Ticket>> getSellersTIcketList();
};
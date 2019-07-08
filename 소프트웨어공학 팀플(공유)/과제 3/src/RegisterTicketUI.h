#pragma once
#include <iostream>
#include <string>
#include "RegisterTicket.h"
using namespace std;

// Class : RegisterTicketUI
// Description : RegisterTicket Boundary클래스
// Created : 2019/06/03 02:55pm
// Author : 이지현
//
// Revision :
//	     1. When & Who : 
//         What : 

class RegisterTicketUI {
public:
	void inputTicketInformationToRegister(ifstream &in_fp, ofstream &out_fp, RegisterTicket& registerTicket);
};
#pragma once
#include <iostream>
#include <string>
#include "MemberManager.h"
using namespace std;

// Class : SignUp
// Description : SignUp Control클래스
// Created : 2019/06/03 02:11pm
// Author : 이지현
//
// Revision :
//	     1. When & Who : 
//         What : 

class SignUp {
public:
	void showSignUp(string savedID, string savedPassword, string name, int identityNumber, int userType);
};
#include <iostream>
#include <fstream>
#include <string>
#include "LogIn.h"
#pragma once
using namespace std;


//class : LogInUI
//description : �α���UI
//created : 2019/06/03 1:21am
// Author : ������

class LogInUI{

public:
	
	void inputLogInInformation(ifstream &in_fp, ofstream &out_fp, LogIn &logIn);
};
/***************************************************************
**	Copyright(c) 2019 VisionMC
**	File Name: ioStream.cpp
**	Auther: Zonglin Shao  Version: 1.0  Data: 2019-5-16
**	Description: 
**			io stream Common usage
**			ios/istream/ostream/iostream/ifstream/ofstream
**	History:null
***************************************************************/
#include <iostream>
#include "ioStream.h"

int test_io(void)
{
    double values[] = { 1.23,35.36,653.7,4358.24 };
    for (int i = 0; i < 4; i++) {
        std::cout.width(10);
        std::cout << values[i] << std::endl;
    }
    return 0;
}

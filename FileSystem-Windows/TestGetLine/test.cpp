
/////////////////////////////////////////////////////////////////////
// test.cpp - SoftwareRepository                                   //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #2         //
// Language:    C++, Visual Studio 2017                            //
// Platform:    Win 10, Visual Studio 2017                         //
// Author:      RUXIN WANG, 921886400                              //
//              rwang64@syr.edu                                    //
/////////////////////////////////////////////////////////////////////


// test.cpp - check functionality of std::IStream::getline(...)

#include <fstream>
#include <iostream>
#include <string>

int main()
{
  const size_t BufSize = 25;
  char buffer[BufSize];
  std::string filename = "test.cpp";
  std::ifstream in(filename);
  if (in.good())
  {
    for (int i = 0; i < 25; ++i)
    {
      in.getline(buffer, BufSize);
      if (in.good())
        std::cout << "\n  -- in.good() == true";
      else
        std::cout << "\n  -- in.good() == false";
      in.clear();
      std::cout << "\n  " << std::string(buffer).c_str();
    }
    in.close();
  }
  else
    std::cout << "\n  " << "can't open " << filename;
  std::cout << "\n\n";
}
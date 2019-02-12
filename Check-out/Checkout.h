#pragma once

/////////////////////////////////////////////////////////////////////
// Checkout.h - SoftwareRepository                                 //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #2         //
// Language:    C++, Visual Studio 2017                            //
// Platform:    Win 10, Visual Studio 2017                         //
// Author:      RUXIN WANG, 921886400                              //
//              rwang64@syr.edu                                    //
/////////////////////////////////////////////////////////////////////


#include <string>
#include <vector>
#include <iostream>
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Check-in/Checkin.h"

using namespace FileSystem;

class Checkout
{
public:
	Checkout();
	~Checkout();

	static bool checkout(const std::string& path);

private:

};

Checkout::Checkout()
{
}

Checkout::~Checkout()
{
}

bool Checkout::checkout(const std::string & path)
{
	if (Directory::exists(path) && Directory::exists(path + "/.rep"))
	{
		std::vector<std::string> files = getAllFilesInPath(path + "/.rep");
		for (std::size_t i = 0; i < files.size(); ++i)
		{
			std::string fileSpec1 = Path::fileSpec(path + "/.rep", files[i]);
			std::string dstFile1 = Path::fileSpec(path, files[i].substr(0, files[i].rfind('.')));
			std::cout << fileSpec1 << "== copy to ==>" << dstFile1 << std::endl;
			File::copy(fileSpec1, dstFile1);
		}
	}
	return false;
}

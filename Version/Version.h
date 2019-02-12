#pragma once

/////////////////////////////////////////////////////////////////////
// Version.h - SoftwareRepository                                   //
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
#include "../NoSqlDb/DbCore/DbCore.h"
#include "../NoSqlDb/PayLoad/PayLoad.h"
#include "../NoSqlDb/Query/Query.h"

using namespace FileSystem;
using namespace NoSqlDb;

class Version
{
public:
	Version();
	~Version();
	
	static std::vector<std::string> getFileVersions(DbCore<PayLoad>& db, const std::string& path, const std::string& file);
};

Version::Version()
{
}

Version::~Version()
{
}

std::vector<std::string> Version::getFileVersions(DbCore<PayLoad>& db, const std::string& path, const std::string & file)
{
	std::vector<std::string> versions;
	typename DbCore<PayLoad>::DbStore dbs = db.dbStore();
	for (auto item : dbs)
	{
		if (item.first.substr(0, item.first.rfind('.')) == file)
		{
			std::cout << item.first << " => " << item.first.substr(item.first.rfind('.') + 1) << std::endl;
		}
	}
	return versions;
}

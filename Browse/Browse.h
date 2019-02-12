#pragma once

/////////////////////////////////////////////////////////////////////
// Browse.h - SoftwareRepository                                   //
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

class Browse
{
public:
	Browse();
	~Browse();

	static bool browseFile(const std::string& path, const std::string& file);
	static bool browseFileInfo(DbCore<PayLoad>& db, const std::string& path, const std::string regex);
};

Browse::Browse()
{
}

Browse::~Browse()
{
}

bool Browse::browseFile(const std::string& path, const std::string& file)
{
	std::string fileSpec1 = Path::fileSpec(path, file);
	std::cout << fileSpec1 << std::endl;
	File f = File(fileSpec1);
	f.open(File::in);
	if (f.isGood()) {
		std::string content = f.readAll();
		std::cout << "file -- " << fileSpec1 << "\tcontents:" << std::endl << content << std::endl;
	}
	return false;
}

bool Browse::browseFileInfo(DbCore<PayLoad>& db, const std::string & path, const std::string regex)
{
	Query<PayLoad> q1(db);
	Keys saveKeys = q1.keys();
	Conditions<PayLoad> conds1;
	conds1.name(regex);
	q1.select(conds1).show();
	Utilities::putline();
	for (auto key : saveKeys)
	{
		browseFile(path + "/.rep/", key);
		std::cout << "----------------------------";
		Utilities::putline();
	}
	return false;
}

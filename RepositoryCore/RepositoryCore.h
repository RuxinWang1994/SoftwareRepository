#pragma once

/////////////////////////////////////////////////////////////////////
// Repository.h - SoftwareRepository                               //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #2         //
// Language:    C++, Visual Studio 2017                            //
// Platform:    Win 10, Visual Studio 2017                         //
// Author:      RUXIN WANG, 921886400                              //
//              rwang64@syr.edu                                    //
/////////////////////////////////////////////////////////////////////


#include <vector>
#include <string>
#include "../NoSqlDb/DbCore/DbCore.h"
#include "../Check-in/Checkin.h"
#include "../Check-out/Checkout.h"
#include "../Browse/Browse.h"
#include "../Version/Version.h"
#include "../NoSqlDb/PayLoad/PayLoad.h"

static bool checkin(DbCore<PayLoad>& dbcore,
	const std::string& path,
	std::vector<std::string> filesdepends,
	std::vector<std::string> categories,
	const std::string& desc = "",
	const std::string& author = "",
	bool isopen = true)
{
	return Checkin::init(dbcore, path, filesdepends, categories, desc, author, isopen);
}

static bool checkout(const std::string & path)
{
	return Checkout::checkout(path);
}

static bool browse(DbCore<PayLoad>& db, const std::string & path, const std::string regex)
{
	return Browse::browseFileInfo(db, path, regex);
}

static std::vector<std::string> version(DbCore<PayLoad>& db, const std::string& path, const std::string & file)
{
	return Version::getFileVersions(db, path, file);
}
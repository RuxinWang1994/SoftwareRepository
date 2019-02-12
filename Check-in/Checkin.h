#pragma once

/////////////////////////////////////////////////////////////////////
// Check-in.h - SoftwareRepository                                 //
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

using namespace FileSystem;
using namespace NoSqlDb;

static std::vector<std::string> getAllFilesInPath(const std::string& path)
{
	std::vector<std::string> files;
	if (Directory::exists(path))
	{
		files = Directory::getFiles(path);
		//for (std::size_t i = 0; i < files.size(); ++i)
		//{
		//	std::cout << files[i] << std::endl;
		//}
	}
	return files;
}

class Checkin
{
public:
	Checkin();
	~Checkin();

	static bool init(DbCore<PayLoad>& dbcore,
		const std::string& path,
		std::vector<std::string> filesdepends,
		std::vector<std::string> categories,
		const std::string& desc="",
		const std::string& author="",
		bool isopen=true);
};

Checkin::Checkin()
{
}

Checkin::~Checkin()
{
}

bool Checkin::init(DbCore<PayLoad>& dbcore,
	const std::string& path,
	std::vector<std::string> filesdepends,
	std::vector<std::string> categories,
	const std::string& desc,
	const std::string& author,
	bool isopen)
{
	if (Directory::exists(path))
	{
		if (!Directory::exists(path + "/.rep"))Directory::create(path + "/.rep");

		const static std::string version = "1";

		std::vector<std::string> files = getAllFilesInPath(path);
		for (std::size_t i = 0; i < files.size(); ++i)
		{
			//store file with version numbers
			std::string fileSpec1 = Path::fileSpec(path, files[i]);
			std::string dstFile1 = Path::fileSpec(path + "/.rep/", files[i] + "." + version);
			std::cout << fileSpec1 << " ==copy to==> " << dstFile1 << std::endl;
			File::copy(fileSpec1, dstFile1);

			// create metadata
			DbElement<PayLoad> dbelement = makeElement<PayLoad>(author, desc);
			for (std::size_t j = 0; j < filesdepends.size(); ++j)
			{
				dbelement.addChildKey(filesdepends[j]);
			}

			PayLoad& payload = dbelement.payLoad();
			payload.value(path + "/.rep/");
			std::vector<std::string>& payload_categories = payload.categories();
			for (std::size_t j = 0; j < categories.size(); ++j)
			{
				payload_categories.push_back(categories[j]);
			}

			dbcore.addRecord(files[i] + "." + version, dbelement);
		}
	}
	return false;
}

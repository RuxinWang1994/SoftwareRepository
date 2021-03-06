
/////////////////////////////////////////////////////////////////////
// TestExecutive.cpp - SoftwareRepository                          //
//                                                                 //
// Application: CSE687 - Object Oriented Design Project #2         //
// Language:    C++, Visual Studio 2017                            //
// Platform:    Win 10, Visual Studio 2017                         //
// Author:      RUXIN WANG, 921886400                              //
//              rwang64@syr.edu                                    //
/////////////////////////////////////////////////////////////////////


#include <iostream>
#include <iomanip>
#include <functional>
#include "../Utilities/StringUtilities/StringUtilities.h"
#include "../Utilities/TestUtilities/TestUtilities.h"

#include "../Check-in/Checkin.h"
#include "../Check-out/Checkout.h"
#include "../Browse/Browse.h"
#include "../Version/Version.h"

using namespace Utilities;
//----< reduce the number of characters to type >----------------------
auto putLine = [](size_t n=1, std::ostream& out = std::cout)
{
  Utilities::putline(n, out);
};

///////////////////////////////////////////////////////////////////////
// DbProvider class
// - provides mechanism to share a test database between test functions
//   without explicitly passing as a function argument.

class DbProvider
{
public:
	DbCore<PayLoad>& db() { return db_; }
private:
	static DbCore<PayLoad> db_;
};

DbCore<PayLoad> DbProvider::db_;

///////////////////////////////////////////////////////////////////////
// test functions


bool testR1()
{
  Utilities::title("Demonstrating check-in");
  putLine();

  DbProvider dbp;
  DbCore<PayLoad>& db = dbp.db();
  std::vector<std::string> filesdepends = {"README"};
  std::vector<std::string> categories = { "cpp", "h" };
  std::string desc = "This is a package whith open check-in";
  std::string author = "gary";

  std::cout << "check-in package -- TestPackage, metadatas: \n\
				1)filesdepends are: \"README\";\n\
				2)categories are: \"cpp\", \"h\"\n\
				3)description: \"This is a package whith open check-in\"\n\
				4)author: \"gary\"\n";

  Checkin::init(db, "../TestPackage", filesdepends, categories, desc, author);

  showDb<PayLoad>(db);

  return true;
}

bool testR2()
{
	Utilities:title("Demonstrating check-out");
	putLine();
	Checkout::checkout("../TestPackage");
	return true;
}

bool testR3()
{
	Utilities:title("Demonstrating browse");
	putLine();
	std::cout << "query files with author \"gary\"";
	DbProvider dbp;
	DbCore<PayLoad>& db = dbp.db();
	Browse::browseFileInfo(db, "../TestPackage/", "gary");
	return true;
}

bool testR4()
{
Utilities:title("Demonstrating version");
	putLine();
	std::cout << "Show me all version of file main.cpp";
	putLine();
	DbProvider dbp;
	DbCore<PayLoad>& db = dbp.db();
	std::vector<std::string> versions = Version::getFileVersions(db, "../TestPackage/", "main.cpp");
	for (auto v : versions)
	{
		std::cout << v << " ";
	}
	putLine();
	return true;
}

//----< test stub >----------------------------------------------------



int main()
{
  Utilities::Title("Testing SoftwareRepository");
  putLine();

  TestExecutive ex;

  // define test structures with test function and message
  TestExecutive::TestStr ts1{ testR1, "Check-in" };
  TestExecutive::TestStr ts2{ testR2, "Check-out" };
  TestExecutive::TestStr ts3{ testR3, "Browse" };
  TestExecutive::TestStr ts4{ testR4, "Version" };

  // register test structures with TestExecutive instance
  ex.registerTest(ts1);
  ex.registerTest(ts2);
  ex.registerTest(ts3);
  ex.registerTest(ts4);

  // run tests

  bool result = ex.doTests();
  if (result == true)
    std::cout << "\n  all tests passed";
  else
    std::cout << "\n  at least one test failed";

  putLine(2);
  std::cin.get();
  return 0;
}

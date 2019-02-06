#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "05";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2019";
	static const char UBUNTU_VERSION_STYLE[] =  "19.02";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 6;
	static const long BUILD  = 55;
	static const long REVISION  = 343;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 134;
	#define RC_FILEVERSION 1,6,55,343
	#define RC_FILEVERSION_STRING "1, 6, 55, 343\0"
	static const char FULLVERSION_STRING [] = "1.6.55.343";
	
	//SVN Version
	static const char SVN_REVISION[] = "0";
	static const char SVN_DATE[] = "unknown date";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 5;
	

}
#endif //VERSION_H

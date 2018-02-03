/** Introduction.
This class contains some useful funtion.

Final editd time	:	2018.01.19
Verson				:	1.0
Author				:	Alex
license				:
						Free to share.
						No commercial use. 
	Welcome to improve it together.
*/

#include "baseOperation.h"

/*
Command line text operation.
*/

/** @brief
Set command line text color to white\red\blue\green and default(gray).
If you need more, you can write your own function with any two of them.

@Notes: A function will influence the current output text, and also the next.
After setting color, you need to call defaultColor to recover the default color setting.
See example in detail.

@Example:
std::cout << greenColor << "Hello world !" << std::endl;
std::cout << "Hello world !" << std::endl;									// will also be green.
std::cout << greenColor << "Hello world !" << defaultColor << std::endl;	// change back;
std::cout << "Hello world !" << std::endl;									// will be default.

*/
BOOL SetConsoleTextColor(WORD wAttributes)
{
	if (!SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes))
	{
		SetLastError(GetLastError());
		return FALSE;
	}
	return TRUE;
}

std::ostream& greenColor(std::ostream &out)
{
	SetConsoleTextColor(FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	return out;
}

std::ostream& redColor(std::ostream &out)
{
	SetConsoleTextColor(FOREGROUND_INTENSITY | FOREGROUND_RED);
	return out;
}

std::ostream& blueColor(std::ostream &out)
{
	SetConsoleTextColor(FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	return out;
}

std::ostream& whiteColor(std::ostream &out)
{
	SetConsoleTextColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return out;
}

std::ostream& defaultColor(std::ostream &out)
{
	SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	return out;
}


/*
Type conversion
*/

int string2int(std::string str)
{
	return atoi(str.c_str());
}

long string2long(std::string str)
{
	return atol(str.c_str());
}

long long string2longlong(std::string str)
{
	return atoll(str.c_str());
}

double string2double(std::string str)
{
	return atof(str.c_str());
}

/** @brief string2char_ptr
Conver std::string to char*

@Notes: You must free the memory allocated with "delete[]", see example.
@Example:

char *data = string2char_ptr(s1);
for (size_t i=0; i<s1.size(); ++i)
std::cout << data[i];

delete[] data;

*/
char* string2char_ptr(std::string str)
{
	char *data = nullptr;
	data = new char[str.length()]; // Dynamic array 

	for (size_t i = 0; i<str.length(); ++i)
		data[i] = str[i];

	return data;
}

/** @brief string2const_char_ptr NOT_CALL
Conver std::string to const char*. You can use std::string::c_str() directly.

@Notes: You donot need to call this. See example.
@Example:

const char *cdata = s1.c_str(); // c_str() return const char*

for (size_t i=0; i<s1.size(); ++i)
std::cout << cdata[i];

*/
const char * string2const_char_ptr_SEE_example_THIS_NOT_USE(std::string str)
{
	return nullptr;
}

std::string int2string(int num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

std::string double2string(double num)
{
	std::stringstream ss;
	ss << num;
	return ss.str();
}

std::string char_ptr2string(char* ArrayChar)
{
	return std::string(ArrayChar);
}

std::string const_char_ptr2string(const char* ArrayChar)
{
	return std::string(ArrayChar);
}

std::wstring string2wstring(const std::string &str)
{
	std::wstring wstr(str.length(), L' ');
	std::copy(str.begin(), str.end(), wstr.begin());
	return wstr;
}

std::string wstring2string(const std::wstring &wstr)
{
	std::string str(wstr.length(), ' ');
	std::copy(wstr.begin(), wstr.end(), str.begin());
	return str;
}

/** @brief Convert char* to wchar_t*
To call W2A or A2W is sample enough.
"USES_CONVERSION" is necessary.

@Example:

USES_CONVERSION;
char* lc = W2A(L"xsff23+-+++");
std::string strlc(lc);
wchar_t* wlc = A2W("xsff23+-+++");

@Notes: You had better use "W2A" and "A2W" in the same function if you need them both.
*/
wchar_t* char_ptr2wchar_t_ptr_SEE_example_THIS_NOT_USE(char* cp)
{
	/*USES_CONVERSION;
	return A2W(cp);*/
	return nullptr;
}

char* wchar_t_ptr2char_ptr_SEE_example_THIS_NOT_USE(wchar_t* wcp)
{
	/*USES_CONVERSION;
	return W2A(wcp);*/
	return nullptr;
}

/** @brief convert_const_to_nonconst NOT_CALL && convert_nonconst_to_const NOT_CALL
You can call "=" for nonconst to const and "cosnt_cast" for const to nonconst directly.

@Example:

char cArray[] = "zxc123+-*<>::=_+_";
const char* cpc = cArray;				// Convert XXX* to const XXX*
char* pc = const_cast<char*>(cpc);		// Convert const XXX* to XXX*

*/
void convert_const_to_nonconst()
{}

void convert_nonconst_to_const()
{}


/*
CLASS baseOperation Definition
*/


baseOperation::baseOperation()
{
}


baseOperation::~baseOperation()
{
}


inline void baseOperation::errorMessage(std::string functionName, std::string errorCode)
{
	std::cout << redColor << "ERROR (" << functionName << ") : " << blueColor << errorCode << defaultColor << std::endl;
}

inline std::string baseOperation::getErrorMessage(std::string functionName, std::string errorCode)
{
	std::string re = "ERROR (" + functionName + ") : " + errorCode;
	return re;
}


inline std::vector<std::string> baseOperation::getFileNames(std::string path)
{
	// 文件句柄  
	intptr_t hFile = 0; 

	// 文件信息  
	struct _finddata_t fileinfo;
	std::string p;
	std::vector<std::string> files;

	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if (fileinfo.attrib & _A_SUBDIR)
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					files = getFileNames(p.assign(path).append("\\").append(fileinfo.name));
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	return files;
}


inline std::string baseOperation::getSysTime(bool ms)
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);

	// 使用时间作为文件夹名字  
	char char_folder_names[50] = {};

	if (!ms)
	{
		sprintf_s(char_folder_names, 50, "%4d%02d%02d%02d%02d%02d", sys.wYear, sys.wMonth, sys.wDay, \
			sys.wHour, sys.wMinute, sys.wSecond);
	}
	else {
		sprintf_s(char_folder_names, 50, "%4d%02d%02d%02d%02d%02d%03d", sys.wYear, sys.wMonth, sys.wDay, \
			sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	}



	return std::string(char_folder_names);
}


inline int baseOperation::createFolder(std::string folderName)
{
	return _mkdir(folderName.c_str());
}


inline void baseOperation::popUpFolder(std::string folderName)
{
	ShellExecute(nullptr, (LPCWSTR)L"open", nullptr, nullptr, \
		stringToLPCWSTR(folderName), SW_SHOWNORMAL);
}


inline bool baseOperation::checkFile(std::string fileName, fileMode _mode)
{
	if (_access(fileName.c_str(), _mode) != -1)
		return true;

	return false;
}


std::fstream baseOperation::openTXT(std::string txtName)
{
	std::fstream file;
	file.open(txtName, std::ios::app); // input mode, see brief.
	// How to write a data, see brief.

	return file;
}


inline bool baseOperation::closeTXT(std::fstream& file)
{
	file.close();
	return false;
}


inline std::vector<std::vector<double>> baseOperation::getDoubleDataInTXT(std::string txtName, std::string separator)
{
	std::vector<std::vector<double>> result;
	std::ifstream infile(txtName);
	std::string aline;
	while (std::getline(infile, aline))
	{
		std::vector<double> v_line;
		std::string tmp_aline(aline);
		while (tmp_aline != "")
		{
			size_t begin = tmp_aline.find_first_of(separator);
			if (begin > tmp_aline.length())
			{
				// A line like "1;2;3;4", keep the last "4", result will be {1,2,3,4}.
				// A line "1;2;3;4;", result will also be {1,2,3,4}. 
				v_line.push_back(atof(tmp_aline.c_str()));
				break;
			}

			v_line.push_back(atof(tmp_aline.substr(0, begin).c_str() ) );
			tmp_aline = tmp_aline.substr(begin + separator.length());
		}
		result.push_back(v_line);
	}

	return result;
}


inline std::vector<std::vector<std::string>> baseOperation::getStringDataInTXT(std::string txtName, std::string separator)
{
	std::vector < std::vector < std::string >> result;
	std::ifstream infile(txtName);
	std::string aline;
	while (std::getline(infile, aline))
	{
		std::vector<std::string> v_line;
		std::string tmp_aline(aline);
		while (tmp_aline != "")
		{
			size_t begin = tmp_aline.find_first_of(separator);
			if (begin > tmp_aline.length())
			{
				// A line like "1;2;3;4", keep the last "4", result will be {1,2,3,4}.
				// A line "1;2;3;4;", result will also be {1,2,3,4}. 
				v_line.push_back(tmp_aline);
				break;
			}

			v_line.push_back(tmp_aline.substr(0, begin));
			tmp_aline = tmp_aline.substr(begin + separator.length());
		}
		result.push_back(v_line);
	}

	return result;
}


#ifdef HAVE_OPENCV3

inline void baseOperation::writeMat2XML(std::string xmlFile, std::map<std::string, cv::Mat>& mData)
{
	cv::FileStorage file(xmlFile, cv::FileStorage::WRITE);
	for (std::map<std::string, cv::Mat>::iterator it = mData.begin(); it != mData.end(); ++it)
		file << (*it).first << (*it).second;

	file.release();
}


inline std::map<std::string, cv::Mat> baseOperation::loadMatFromXML(std::string xmlFile, std::vector<std::string>& MatName)
{
	std::map<std::string, cv::Mat> v_result;
	
	cv::FileStorage file(xmlFile, cv::FileStorage::READ);
	if (!file.isOpened())
	{
		std::cout << redColor << "xml not exist!" << defaultColor << std::endl;
		return std::map<std::string, cv::Mat>();
	}

	for (auto sub : MatName)
	{
		cv::Mat result;
		file[sub] >> result;
		if (result.empty())
			std::cout << redColor << "Image name( "<< sub <<" ) not exist!" << defaultColor << std::endl;

#ifdef VS_2012
		v_result.insert(std::pair<std::string, cv::Mat>(sub, result));
#else
		v_result.insert({ sub, result });
#endif // VS_2012

	}
	file.release();
	return v_result;
}


inline cv::Mat baseOperation::loadMatFromXML(std::string xmlFile, std::string MatName)
{
	cv::Mat result;
	cv::FileStorage file(xmlFile, cv::FileStorage::READ);
	if (!file.isOpened())
	{
		std::cout << redColor << "xml not exist!" << defaultColor << std::endl;
		return cv::Mat();
	}

	file[MatName] >> result;
	if (result.empty())
		std::cout << redColor << "Image name( " << MatName << " ) not exist!" << defaultColor << std::endl;

	return result;
}


inline cv::FileStorage baseOperation::openParametersXML(std::string xmlFile)
{
	return cv::FileStorage(xmlFile, cv::FileStorage::READ);
}


inline void baseOperation::closeParametersXML(cv::FileStorage xmlFile)
{
	xmlFile.release();
}



#endif // HAVE_OPENCV3


inline LPCWSTR baseOperation::stringToLPCWSTR(std::string str)
{
	size_t origsize = str.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t *wcstring = (wchar_t *)malloc(sizeof(wchar_t)*(str.length() - 1));
	mbstowcs_s(&convertedChars, wcstring, origsize, str.c_str(), _TRUNCATE);
	return wcstring;
}



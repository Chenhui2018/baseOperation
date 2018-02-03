/** Introduction.
This class contains some useful funtion.

Final editd time	:	2018.02.03
Verson				:	1.0
Author				:	Alex
license				:
						Free to share.
						No commercial use. 
	Welcome to improve it together.
*/

#pragma once

#define HAVE_OPENCV3
//#define VS_2012

#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <io.h>
#include <fstream>
#include <direct.h>  
#include <atlconv.h> 

#ifdef HAVE_OPENCV3
#include <opencv2\opencv.hpp>
#endif // HAVE_OPENCV3


/*
	CLASS baseOperation Declaration 
*/


class baseOperation
{
public:
	baseOperation();
	~baseOperation();
	
	/* Error message */
	void errorMessage(std::string functionName, std::string errorCode);
	std::string getErrorMessage(std::string functionName, std::string errorCode);


	/* File and folder operation */

	/** @brief getFileNames
	Get all the files' name in a folder, also include the sub-folders.

	@Example

	/------ Code begin ------

	baseOperation ba;
	std::vector<std::string> file = ba.getFileNames("C:\\***\\&&&");

	//iterator is faster, ++it faster than it++.
	for (std::vector<std::string>::iterator it = file.begin(); it != file.end(); ++it)
	{
	// Select the *.bmp only.
	if ((*it).substr((*it).length()-3) == "bmp" )
	std::cout << greenColor << (*it) << defaultColor << std::endl;
	else
	std::cout << redColor << (*it) << defaultColor << std::endl;

	}

	// or //

	// type of vector.size is size_t(unsigned int). Better size_t than int here.
	for (size_t i = 0; i>file.size(); ++i)
	{
		// Select the *.bmp only.
		if (file[i].substr(file[i].length() - 3) == "bmp")
			std::cout << greenColor << file[i] << defaultColor << std::endl;
		else
			std::cout << redColor << file[i] << defaultColor << std::endl;

	}
	/ ------Code end------

	*/
	std::vector<std::string> getFileNames(const std::string path);

	/** @brief getSysTime
	Return system time as a std::string.

	Such as : 20180102030405 (s) | 20180102030405999 (ms)
	year 4 bits; month 2 bits; day 2 bits; hour 2 bits; minute 2 bits; second 2 bits;
	millisecond 3 bits.

	@Param: ms Input If ms==true, will return milliseconds.
	*/
	std::string getSysTime(bool ms = false);

	/** @brief createFolder
	If folder is inexistent, create it, return 0;
	If folder is exisetent, do noting, return -1.
	*/
	int createFolder(const std::string folderName);

	/** @brief showFolder
	While trianing a model, it may cost lot of time. 
	You may want a pop-up window to remind you when training finished.
	*/
	void popUpFolder(const std::string folderName);

	enum fileMode
	{
		ba_EXIST = 0,
		ba_WRITE = 2,
		ba_READ = 4,
		ba_WR = 6
	};
	/** @brief checkFile
	Check file exiset or not and write-and-read mode.

	@Example:

	baseOperation ba;
	int re = ba.checkFile("test.db", baseOperation::ba_EXIST);

	*/
	bool checkFile(std::string fileName, fileMode _mode);
	

	/* TXT operation */

	/** @brief createTXT
	Create A txt-file with "app" mode. If you need other mode, rewrite the code.
	"app" mode: 
	if file is inexistent, create it;
	if file is existent, start a new line behind the last line of the txt-file and write. Keep all the previous data.

	@Example:

	// write data;
	baseOperation ba;
	td::fstream file = ba.createTXT("123.txt");
	file << "Hello World!" << std::endl; // just like the std::cout.
	file.close();
	*/ 
	std::fstream openTXT(const std::string txtName);
	bool closeTXT(std::fstream& file);
	
	/** @brief getDoubleDataInTXT
	Get data in type double. You can convert them to any other type you like after that.
	A std::vector<double> contains a line data in TXT-file.
	
	@Param: txtName Input txt-file name.
	@Param: separator Input Separator of data. It can be a char like ";" or a separating word like "stop".
	DATA: 1;2;3;4
	DATA: 1stop2stop3stop6stop

	@Notes: 
	You need to make sure all the data is number. There is no checking in this function.
	If a data is "1.xx7", it will get a wrong result.
	@Notes:
	DATA: 1;2;3;4
	DATA: 1;2;3;4;
	will return the same result, if seperator is ";". 
	*/
	std::vector<std::vector<double>> getDoubleDataInTXT(const std::string txtName, const std::string separator);

	/** @brief getStringDataInTXT
	Get data in type string.
	Brief is similar to getDoubleDataInTXT.
	*/
	std::vector<std::vector<std::string>> getStringDataInTXT(const std::string txtName, const std::string separator);

	/* opencv xml operation (for loading and saving data) */
#ifdef HAVE_OPENCV3
	/** @brief writeMat2XML
	Support matrix of single and multi channels.  

	@Param: xmlFile Input Xml-file name. 
	@Param: mData Input std::Map of data. 
	
	@Example:
	// Prepare data map
	cv::Mat src1 = cv::imread("...");
	cv::Mat src2 = cv::imread("...");
	std::map<std::string, cv::Mat> mData;
	mData.insert({ "Image1", src });									// VS2013 or higher, C++11 standard
	mData.insert(std::pair < std::string, cv::Mat >("Image2", src2));	// VS2012 or lower
	
	writeMat2XML("test.xml", mData);
	
	*/
	void writeMat2XML(std::string xmlFile, std::map<std::string, cv::Mat>& mData);

	/** @brief loadMatFromXML
	Load Mat with the name saved.
	Overload function.
	1. Load all mats in a functon.
	2. Load a mat in a function.
	*/
	std::map<std::string, cv::Mat> loadMatFromXML(std::string xmlFile, std::vector<std::string>& MatName);
	cv::Mat loadMatFromXML(std::string xmlFile, std::string MatName);

	/** @brief openParametersXML
	Load some parameters written in xml file.

	@Example of xml file.
	/------ Begin(not belong to xml file) ----
	<?xml version="1.0"?>
	<opencv_storage>
	<!-- example 1 -->
	<rows>720</rows>
	<cols>1024.0</cols>

	<!-- example 2 -->
	<class>	
		<stduent_1>
			<Name>Xiaoming</Name>
			<Age>14.0</Age>
		</stduent_1>
		<stduent_2>
			<Name>Xiaohong</Name>
			<Age>15.0</Age>
		</stduent_2>
	</class>

	</opencv_storage>
	------- Begin(not belong to xml file) ---/

	@Example of loading data.

	cv::FileStorage file = openParametersXML(string_xmlFile);
	int rows = (int)file["rows"];
	double cols = (double)file["cols"];
	int XiaomingAge = (int)file["class"]["stduent_1"]["Age"];

	*/
	cv::FileStorage openParametersXML(std::string xmlFile);
	void loadParametersXML_See_brief_openParametersXML_NOT_USE(){} // Blank function
	void closeParametersXML(cv::FileStorage xmlFile);

#endif // HAVE_OPENCV3

	/* Sqlite3 Operation (see class SqliteProcessing, will come soon) */

protected:
	LPCWSTR stringToLPCWSTR(std::string str);

private:
	
};

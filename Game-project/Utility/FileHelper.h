#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

//#include "../Dependancies/Boost/text_iarchive.hpp"
//#include "../Dependancies/Boost/text_oarchive.hpp"
#include "../Dependancies/cereal/archives/json.hpp"
#include "../Dependancies/cereal/types/vector.hpp"

namespace game { namespace utilities {

class FileHelper {

public:

	static const std::string resourceFolder;

	//template<typename T>
	//static void save(T data, const std::string& fileName)
	//{

	//}

	template<typename T>
	static void writeMatrixToFile(std::vector<std::vector<T>> mat, const std::string& fileName)
	{
		std::ofstream outFile;
		outFile.open(fileName);

		cereal::JSONOutputArchive oarchive(outFile); // Create an output archive
		oarchive(mat); // Write the data to the archive
	}

	template<typename T>
	static void readMatrixFromFile(std::vector<std::vector<T>>& mat, std::string fileName)
	{
		std::ifstream inFile;
		inFile.open(fileName);

		cereal::JSONInputArchive iarchive(inFile); // Create an input archive

		iarchive(mat); // Read the data from the archive
	}

	static bool fileExists(const std::string& filename);

};


} }

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

// Archiving headers
//#include "../Dependancies/Boost/text_iarchive.hpp"
//#include "../Dependancies/Boost/text_oarchive.hpp"
#include "../Dependancies/cereal/archives/json.hpp"
#include "../Dependancies/cereal/archives/binary.hpp"

// stl types
#include "../Dependancies/cereal/types/vector.hpp"
#include "../Dependancies/cereal/types/map.hpp"
#include "../Dependancies/cereal/types/memory.hpp"

namespace game { namespace utilities {

class FileHelper {

public:

	static const std::string resourceFolder;

	template<typename T>
	static void writeDataToFile(T data, const std::string& fileName)
	{
		std::ofstream outFile;
		outFile.open(fileName);

		cereal::BinaryOutputArchive oarchive(outFile);
		//cereal::JSONOutputArchive oarchive(outFile); // Create an output archive
		oarchive(data); // Write the data to the archive
	}

	template<typename T>
	static void abc(T data, const std::string& fileName)
	{
		cereal::JSONOutputArchive output(std::cout); // stream to cout
		// make_nvp does a key value pair
		output(cereal::make_nvp("best data ever", data));
	}

	template<typename T>
	static void readDataFromFile(T& data, std::string fileName)
	{
		std::ifstream inFile;
		inFile.open(fileName);

		cereal::BinaryInputArchive iarchive(inFile);
		// cereal::JSONInputArchive iarchive(inFile); // Create an input archive

		iarchive(data); // Read the data from the archive
	}

	static bool fileExists(const std::string& filename);

};


} }

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

namespace game { namespace utilities {

class FileHelper {

public:

	static const std::string resourceFolder;

	template<typename T>
	static void writeMatrixToFile(std::vector<std::vector<T>> mat)
	{
		std::ofstream file;
		file.open("navMesh.txt");

		// Go through the vector a row at a time
		for (auto const &x_vect : mat)
		{
			// This loop is for the columns
			for (auto const &y : x_vect)
			{
				file << y;
			}

			file << "\n";
		}

		file.close();
	}

};


} }

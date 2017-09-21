#include "FileHelper.h"

#include <sys/stat.h>

namespace game { namespace utilities {

const std::string FileHelper::resourceFolder = "C:\\Users\\Roy\\Documents\\Game-project\\Game-project\\Resources\\";
//"Game-project/Resources/"

/*
 * Check if a file exists
 * @param[in] filename - the name of the file to check
 *
 * @return    true if the file exists, else false
 */
bool FileHelper::fileExists(const std::string& filename)
{
	struct stat buf;
	if (stat(filename.c_str(), &buf) != -1)
	{
		return true;
	}
	return false;
}

} }
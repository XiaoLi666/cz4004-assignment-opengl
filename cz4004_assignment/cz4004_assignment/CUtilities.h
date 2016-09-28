#ifndef __CUTILITIES_H__
#define __CUTILITIES_H__

#include <string>
#include <vector>

namespace CZ4004
{
	class CUtilities
	{
	public:
		static std::string directory;
		static void SplitString(const std::string & full_string, const std::string & token, std::vector<std::string> & sub_strings);
	};
}

#endif // __CUTILITIES_H__
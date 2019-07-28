#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdarg.h>
#include <string.h>
#include <fstream>

namespace SystemCalls {

class System {
	public:
		static void printf(const char * format,  ...) {
			va_list vListPrintf;
			va_start (vListPrintf, format);
			::printf(format, *vListPrintf);
			va_end(vListPrintf); 
		}
		static std::string getFile(const char * fileName) {
			std::ifstream fileStream;
			fileStream.open(fileName);
			if (fileStream.is_open() == false) {
				return "";
			}
			std::string result, line;
			while (getline(fileStream, line)) {
				result.append(line);
			}
			fileStream.close();
			return result;
		}
};

}

#endif // SYSTEM_H

#ifndef READXML_H_
#define READXML_H_
#include <fstream>
#include <string>
#include <map>

inline std::string XMLValue(const char* filename,std::string tagname)
{
	std::ifstream file;
	file.open(filename);
	std::string line;
	std::string container;
	while (std::getline(file, line))
	{
		size_t index = line.find(tagname);
		if (index>0&&index<sizeof(size_t))
		{
			while(line.at(line.size()-1)!='>'&&line.size()>tagname.size()*2+4)line.erase(line.begin()+line.size()-1);
			container= line.substr(index+tagname.size()+1,line.size()-index-2*(tagname.size())-4);
			break;
		}
	}
	file.close();

	return container;
}

#endif

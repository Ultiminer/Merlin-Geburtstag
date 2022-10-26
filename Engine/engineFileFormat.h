#ifndef ENGINE_FILE_FORMAT_H_
#define ENGINE_FILE_FORMAT_H_
#include <fstream>
#include <vector>
#include <map>
#include "convert_numbers.h"
#include "exception_handling.h"
#include "primitives.h"


struct MGE_DOUBLE { std::string id; std::string data; };
struct MGE_OBJ {std::vector<unsigned char> vals; std::vector<vec2d> pos; };

inline void MGE_OBJ_WRITE(const char* path, const size_t obj_id, const std::vector<unsigned char>& vals, const std::vector<vec2d>& pos)
{
	std::ofstream file;
	file.open(path,std::ios::app);
	if (file.is_open())
	{
		file <<"$"<<IntToHexL(obj_id,1)<<IntToHexL(vals.size(),1);
		for (unsigned int i = 0; i < vals.size(); i++)file << IntToHexL(vals.at(i),1);
		for (unsigned int i = 0; i < pos.size(); i++)file << IntToHexL(pos.at(i).x,4)+IntToHexL(pos.at(i).y,4);
	}
	file.close();
}
inline std::string MGE_RET_OBJ(const char* filename)
{
	bool START = false;
	std::ifstream  file;
	std::string data, line;
	file.open(filename);
	if(file.is_open())
		while (std::getline(file, line))
		{
			for (size_t i = 0; i < line.size(); i++)
			{
				switch (line.at(i))
				{
				case '#': { line.erase(line.begin()+i); const size_t range = ctoi(line.at(i)); line.erase(line.begin() + i); for (size_t j = 0; j < range; j++)line.insert(line.begin() + i, '0'); }break;
				case ' ': line.erase(line.begin() + i); break;
				case '\n': line.erase(line.begin() + i); break;
				}
				
				data += line.at(i);
			}
			line = "";
		}
	file.close();
	MGE_PRINT("Retrieved file:");
	MGE_PRINT(data.c_str());
	return data;
}


/*Returns every instance of an object id with certain values*/
inline std::vector<MGE_OBJ> MGE_OBJ_GET(const std::string& ret_file, const size_t id)
{
	std::vector<MGE_OBJ> obj;
	for (size_t i = 0; i < ret_file.size(); i++)
	{
		if (ret_file.at(i) == '$')if (HexToInt(ret_file.substr(i + 1, 2)) == id)
		{
			obj.push_back({});
			const size_t r_val=HexToInt(ret_file.substr(i+3,2));
			for (size_t j = 0; j < r_val; j++)
			{
				obj.back().vals.push_back(HexToInt(ret_file.substr(i+5+j*2,2)));
			}
			i=i+4+r_val*2;
			while (i < ret_file.size() - 16) { if (ret_file.at(i + 1) == '$')break; obj.back().pos.push_back({ HexToInt(ret_file.substr(i + 1,8)),HexToInt(ret_file.substr(i + 9,8)) }); i += 16; }

		}
	}
	return obj;
}
/*UNEFFICIENT FUNCTION: retrieves all the positions of an object type*/
inline std::vector<vec2d> MGE_OBJ_POS(const std::string& ret_file, const size_t id)
{
	std::vector<vec2d> obj;
	for (size_t i = 0; i < ret_file.size(); i++)
	{
		if (ret_file.at(i) == '$')if (HexToInt(ret_file.substr(i + 1, 2)) == id)
		{	
			const size_t r_val = HexToInt(ret_file.substr(i + 3, 2));
			i = i + 4 + r_val * 2;
			while (i < ret_file.size() - 16) { if (ret_file.at(i + 1) == '$')break; obj.push_back({ HexToInt(ret_file.substr(i + 1,8)),HexToInt(ret_file.substr(i + 9,8)) }); i += 16; }
		}
	}
	
	return obj;
}

inline std::vector<MGE_DOUBLE> MGE_RET_DOUBLE(const char* filename)
{
	std::ifstream  file;
	std::string line;
	std::vector<MGE_DOUBLE> data;
	bool SWITCH = false;
	file.open(filename);
	if (file.is_open())
		while (std::getline(file, line))
		{
			SWITCH = false;
			data.push_back({});
			for (size_t i = 0; i < line.size(); i++)
			{
				if (line.at(i) == ':')SWITCH = true;
				else if(line.at(i)!='\n'&&line.at(i)!=' ')
				((SWITCH) ? data.back().data : data.back().id) += line.at(i);
			}
			//Checking for non-emptiness of the data structure
			if (data.back().data.size() < 2 || data.back().id.size() == 0)data.erase(data.end());
		}
	file.close();

	return data;
}
inline std::string MGE_LAZY_RET_DOUBLE(const char* filename,const std::string& id)
{
	std::ifstream  file;
	std::string line;
	MGE_DOUBLE data;
	bool SWITCH = false;
	file.open(filename);
	if (file.is_open())
		while (std::getline(file, line))
		{
			data = {"",""};
			SWITCH = false;
			for (size_t i = 0; i < line.size(); i++)
			{
				if (line.at(i) == ':') { SWITCH = true; if (data.id.compare(id) != 0)i = line.size(); }
				else if (line.at(i) != '\n' && line.at(i) != ' ')
				((SWITCH) ? data.data : data.id) += line.at(i);
			}
			if (data.data.size() > 5)
			{
				file.close();
				return data.data;
			}
		}
	file.close();
	return "!ERROR!: NO_MGE_DOUBLE_FOUND";
}

/*LAZY MACRO TO LOAD A FUNCTION WITH MGE_DOUBLE VALUES <function> has to be inserted WITHOUT parenthesis*/
#define MGE_DOUBLE_FILL(function,filename){std::vector<MGE_DOUBLE>vec=MGE_RET_DOUBLE(filename);for(size_t i=0;i<vec.size();i++){function(vec.at(i).data.c_str(),vec.at(i).id.c_str());}}
#endif
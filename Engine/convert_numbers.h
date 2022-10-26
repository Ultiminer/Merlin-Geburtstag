#pragma once
#include <string>
#include <bitset>
inline int ctoi(const char& c)noexcept
{
	return c - (47 < c) * (c < 58) * 48;
}
inline int BinToInt(const std::string& str)noexcept
{
	int v = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		v += (1 << i) * ctoi(str.at(str.size() - i - 1));
	}
	return v;
}
inline std::string IntToBin(const int& a)noexcept
{
	return std::bitset<64 >(a).to_string();
}
inline std::string BinToHex(const std::string& bin)noexcept
{
	std::string a = bin;
	std::string hex;
	while (a.size() % 4 != 0)a = "0" + a;
	for (size_t i = 0; i < a.size() / 4; i++)
	{
		const int e = BinToInt(a.substr(4 * i, 4));
		hex.push_back(e + 48 * (e > -1) * (e < 10) + 55 * (e > 9) * (e < 16));
	}
	return hex;
}
inline int HexToInt(std::string hex)noexcept
{
	int a = 0;

	for (size_t i = 0; i < hex.size(); i++)
	{
		const size_t ind = hex.size() - i - 1;
		a += (1 << (4 * i)) * (hex.at(ind) - 48 * (47 < hex.at(ind)) * (hex.at(ind) < 58) - 55 * (64 < hex.at(ind)) * (hex.at(ind) < 91));
	}
	return a;
}



inline std::string HexToBin(const std::string& hex)noexcept
{

	return IntToBin(HexToInt(hex));
}


inline std::string IntToHex(const int x)
{
	return BinToHex(IntToBin(x));
}

inline std::string IntToHexL(const int x, const size_t bytelength)
{
	std::string hex = IntToHex(x);
	if (hex.size()>2*bytelength)hex.erase(hex.begin(),hex.end()-2*bytelength);
	size_t s = 0;
	for (unsigned int i = 0; hex.at(i) == '0' && i < hex.size() - 1; i++)s++; if (s > 1) { hex.erase(hex.begin(), hex.begin() + s); hex=("#" + std::to_string(s))+hex; }
	return hex;
}
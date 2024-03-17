#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include <string>
#include <vector>
#include <map>

std::string getafter(const std::string &str,const std::string &data);
std::string getafterinc(const std::string &str,const std::string &data);
std::string getbetween(std::string s1,std::string s2,std::string data);
std::string strdelete(std::string str,std::string data);
void writestring(std::string str,std::string file);
std::string getuntil(std::string str,std::string data);
std::string getuntilinc(std::string str,std::string data);
std::string getline(int line,std::string str);
int linecount(const std::string &str);
std::string getFile(std::string filename);
std::string ExtractFileName(std::string fulln);
std::string ExtractFilePath(std::string fulln);
std::wstring wconvert(bool pBool);
std::wstring wconvert(int i);
std::wstring wconvert(float f);
std::string convert(bool pBool);
std::string convert(int i);
std::string convert(unsigned int i);
std::string convert(float f);
std::string findextension(const std::string& pString);
std::string wnarrow(const std::wstring& pStr);
std::wstring widen(std::string tw);
std::string replaceonce(std::string tor, std::string tin, std::string data);
std::wstring replaceonce(std::wstring tor, std::wstring tin, std::wstring data);
void Tokenize(std::string& str, std::vector<std::string> &tokens, std::string seps);
bool isnumber(char ch);
bool isletter(char ch);
bool isnumber(wchar_t ch);
bool isletter(wchar_t ch);
void strupper(std::string *pStr);
void strupper(std::wstring *pStr);
std::string greplace(std::string tor, std::string tin, std::string data);
int getNextNumber(const std::string &pStr, int *read=NULL);
std::string strlower(const std::string &str);
bool next(const std::string &pData, const size_t & doff, const std::string &pStr);
char getRandomChar(void);
std::string getRandomNumber(void);
void transformHTML(std::string &str);
void EscapeSQLString(std::string &pStr);
void ParseParamStr(const std::string &pStr, std::map<std::string,std::string> *pMap);
int round(float f);
std::string FormatTime(int timeins);
std::string htmldecode(std::string str, bool html=true);
bool checkhtml(const std::string &str);
std::string nl2br(std::string str);

#endif

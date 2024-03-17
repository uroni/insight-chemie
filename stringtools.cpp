#include <string>
#include <vector>
#include <fstream>
#include <sstream> 
#include <map>


using namespace std;

typedef int s32;
typedef unsigned int u32;
typedef float f32;


//--------------------------------------------------------------------
/**
*	liefert einen teil des strings nach dem gelieferten teilstring
*/
string getafterinc(const std::string &str,const std::string &data)
{
	const char* ptr=strstr(data.c_str(), str.c_str() );
	if(ptr!=NULL)
	{
		return ptr;
	}
	else
	{
		return "";
	}
}

string getafter(const std::string &str,const std::string &data)
{
	std::string ret=getafterinc(str,data);
	ret.erase(0,str.size() );
	return ret;
}

//--------------------------------------------------------------------
/**
*	liefert einen teil des strings zwischen zwei teilstrings
*/
string getbetween(string s1,string s2,string data)
{
	size_t off1=data.find(s1);

	if(off1==-1)return "";

	off1+=s1.size();

	size_t off2=data.find(s2,off1);

	if(s2=="\n")
	{
		size_t off3=data.find("\r\n",off1);
		if(off3<off2)
			off2=off3;
	}

	if(off2==-1)return "";

	string ret=data.substr(off1,off2-off1);
	return ret;
}

//--------------------------------------------------------------------
/**
*	lˆsche einen teil des strings ab einem bestimmten teilstring
*/
string strdelete(string str,string data)
{
	size_t off=data.find(str);
	if(off==-1)
		return data;
	data.erase(off,str.size() );
	return data;
}

//--------------------------------------------------------------------
/**
*	string in eine datei schreiben (hinzuf¸gen)
*/
void writestring(string str,string file)
{
	fstream out;
	out.open(file.c_str(),ios::out|ios::binary);

	out.write(str.c_str(),(s32)str.size() );

	out.close();
}

//--------------------------------------------------------------------
/**
*	liefert einen teil des strings bevor einem teilstring
*/
string getuntil(string str,string data)
{
	size_t off=data.find(str);
	if(off==-1)
		return "";
	return data.substr(0,off);
}

//--------------------------------------------------------------------
/**
*	liefert einen teil des strings bevor einem teilstring inklusive
*	dem teilstring..
*/
string getuntilinc(string str,string data)
{
	size_t off=data.find(str);
	if(off==-1)
		return "";
	return data.substr(0,off+str.size());
}

//--------------------------------------------------------------------
/**
*	eine bestimmte zeile (getrennt duch \n) aus dem string anfordern
*/
string getline(s32 line,string str)
{
	s32 num=0;
	string tl;

	for(size_t i=0;i<str.size();i++)
	{
		if(str[i]=='\n')
		{
			if(num==line)
				break;
			num++;
		}
		if(str[i]!='\n'&&str[i]!='\r'&&num==line)
			tl+=str[i];
	}

	return tl;
}

//--------------------------------------------------------------------
/**
*	zeilenanzahl andorfern (getrennt durch \n)
*/
s32 linecount(const std::string &str)
{
	s32 lines=0;
	for(size_t i=0;i<str.size();i++)
	{
		if(str[i]=='\n')
			lines++;
	}
	return lines+1;
}

//--------------------------------------------------------------------
/**
*	text datei auslesen
*/
string getFile(string filename)
{
        fstream FileBin;
	FileBin.open(filename.c_str(), ios::in|ios::binary);
	if(FileBin.is_open()==false)
        {
                return "";
        }
        FileBin.seekg(0, ios::end);
        unsigned long FileSize = (unsigned int)streamoff(FileBin.tellg());
        FileBin.seekg(0, ios::beg);
	char* buffer=new char[FileSize+1];

        FileBin.read(buffer, FileSize);
	buffer[FileSize]='\0';
        string ret=buffer;
	FileBin.close();
        delete [] buffer;
        return ret;
}

//--------------------------------------------------------------------
/**
*	string in groﬂbuchstaben umwandeln
*/
void strupper(char *string)
{
   for(; *string != '\0'; string++ )
      if(*string >= 'a' && *string <='z')
         *string -= 32;   /* siehe ASCII-Tabelle */
}

//--------------------------------------------------------------------
/**
*	string in kleinbuchstaben umwandeln
*/
void strlower(char *string)
{
   for(; *string != '\0'; string++ )
      if(*string >= 'A' && *string <='Z')
         *string += 32;
}

std::string strlower(const std::string &str)
{
	std::string ret=str;
   for(size_t i=0; i<str.size();++i)
      if(str[i] >= 'A' && str[i] <='Z')
         ret[i] += 32;

   return ret;
}


//--------------------------------------------------------------------
/**
*	string in groﬂbuchstaben umwandeln
*/
void strupper(std::string *pStr)
{
	for(size_t i=0;i<pStr->size();++i)
	{
		(*pStr)[i]=toupper((*pStr)[i] );
	}
}

//--------------------------------------------------------------------
/**
*	string in groﬂbuchstaben umwandeln
*/
void strupper(std::wstring *pStr)
{
	for(size_t i=0;i<pStr->size();++i)
	{
		(*pStr)[i]=toupper((*pStr)[i] );
	}
}

//--------------------------------------------------------------------
/**
*	dateiname aus pfadangabe extrahieren
*/
string ExtractFileName(string fulln)
{
	string filename;

	for(s32 i=(s32)fulln.length()-1;i>-1;i--)
	{
		if(fulln[i]=='/'||fulln[i]=='\\')
		{
			if(i<(s32)fulln.length()-2)
				break;
		}
		if(fulln[i]!=0&&fulln[i]!='/')
			filename=fulln[i]+filename;
	}

	return filename;
}

//--------------------------------------------------------------------
/**
*	pfad aus pfadangabe (inkl. dateiname) extrahieren
*/
string ExtractFilePath(string fulln)
{
	bool in=false;
	string path;
	for(s32 i=(s32)fulln.length()-2;i>-1;i--)
	{
		if((fulln[i]=='/'||fulln[i]=='\\')&&in==false)
		{
			in=true;
			continue;
		}
		
		if(in==true)
		{
			path=fulln[i]+path;
		}

	}

	return path;
}

//--------------------------------------------------------------------
/**
*	bool in wide string (true/false) konvertieren
*/
std::wstring wconvert(bool pBool)
{
	if(pBool==true)
		return L"true";
	else 
		return L"false";
}

//--------------------------------------------------------------------
/**
*	integer in wide character
*/
std::wstring wconvert(s32 i){
	wostringstream ss;
	ss << i;
	return ss.str();
}

//--------------------------------------------------------------------
/**
*	f32 in wide character
*/
std::wstring wconvert(f32 f){
	wostringstream ss;
	ss << f;
	return ss.str();
}

//--------------------------------------------------------------------
/**
*	bool in string (true/false) konvertieren
*/
std::string convert(bool pBool)
{
	if(pBool==true)
		return "true";
	else 
		return "false";
}

//--------------------------------------------------------------------
/**
*	integer in string
*/
std::string convert(s32 i){
	ostringstream ss;
	ss << i;
	return ss.str();
}

//--------------------------------------------------------------------
/**
*	unsigned integer in string
*/
std::string convert(u32 i){
	ostringstream ss;
	ss << i;
	return ss.str();
}

//--------------------------------------------------------------------
/**
*	f32 in string
*/
std::string convert(f32 f){
	ostringstream ss;
	ss << f;
	return ss.str();
}

//--------------------------------------------------------------------
/**
*	datei-endung finden
*/
std::string findextension(const std::string& pString)
{
	std::string retv;
	std::string temp;

	for(s32 i=(s32)pString.size()-1; i>=0; i--)
		if( pString[i] != '.' )
			temp.push_back(pString[i]);
		else
			break;

	for(s32 i=(s32)temp.size()-1; i>=0; i--)
		retv.push_back(temp[i]);

	return retv;
}

//--------------------------------------------------------------------
/**
*	string in wide string
*/
std::wstring widen(std::string tw)
{
	std::wstring out;
	out.resize(tw.size() );
	for(size_t i=0;i<tw.size();++i)
	{
		out[i]=tw[i];
	}
	return out;
}

//--------------------------------------------------------------------
/**
*	wide string in string
*/
std::string wnarrow(const std::wstring& pStr)
{
	std::string out;
	out.resize( pStr.size() );
	for(size_t i=0;i<pStr.size();++i)
	{
		out[i]=(char)pStr[i];
	}
	return out;
}

//--------------------------------------------------------------------
/**
*/
std::wstring replaceonce(std::wstring tor, std::wstring tin, std::wstring data)
{
        s32 off=(s32)data.find(tor);
        if(off!=-1)
        {
                data.erase(off,tor.size() );
                data.insert(off,tin);
        }
        return data;
}

//--------------------------------------------------------------------
/**
*/
std::string replaceonce(std::string tor, std::string tin, std::string data)
{
        s32 off=(s32)data.find(tor);
        if(off!=-1)
        {
                data.erase(off,tor.size() );
                data.insert(off,tin);
        }
        return data;
}

//--------------------------------------------------------------------
/**
	Tokenizes a string "str" and stores the tokens in "tokens". "seps"
	is a string or character which defines the seperator (the breaks
	between the tokens) - strings, which are declared by two \" are not
	tokenized = treated as a single token
*/
void	Tokenize(std::string& str, std::vector<std::string> &tokens, std::string seps)
{
	// one-space line for storing blank lines in the file
	std::string blankLine = " ";

	// pos0 and pos1 store the scope of the current turn, i stores
	// the position of the symbol \".
	s32 pos0 = 0, pos1 = 0, i = 0;
	while(true)
	{ 
		// find the next seperator
		pos1 = (s32)str.find_first_of(seps.c_str(), pos0);
		// find the next \" 
		i    = (s32)str.find_first_of("\"", pos0);
	    
		// if the end is reached..
	    if(pos1 == std::string::npos)
	    {
			// ..push back the string to the end
			tokens.push_back(str.substr(pos0, str.size()));
			break;
	    }  
		// if a string \" was found before the next seperator...
	    if(( i<pos1 )&&( i > 0 ))
	    {      
			// .. find the end of the string and push it back, strings
			// are treated like a single token
			pos1 = (s32)str.find_first_of("\"", i+1);
			tokens.push_back(str.substr(pos0, pos1-pos0+1));
	    }  
		// if two seperators are found in a row, the file has a blank
		// line, in this case the one-space string is pushed as a token
		else if( pos1==pos0 )
		{
			tokens.push_back(blankLine);
		}
	    else
            // if no match is found, we have a simple token with the range
			// stored in pos0/1
			tokens.push_back(str.substr(pos0, (pos1 - pos0)));

		// equalize pos
		pos0=pos1;
		// increase 
	    ++pos1;
		// added for ini-file!
		// increase by length of seps
		pos0+=(s32)seps.size();
	}
	  
	// loop through all tokens and check for empty tokens which may result
	// as garbage through the process
	for(s32 i=0;i<(s32)tokens.size();i++)
		if(tokens[i]=="") tokens.erase(tokens.begin()+(i--));
}

//--------------------------------------------------------------------
/**
*/
bool isnumber(char ch)
{
	if( ch>=48 && ch <=57 )
		return true;
	else
		return false;
}

//--------------------------------------------------------------------
/**
*/
bool isletter(char ch)
{
	ch=toupper(ch);
	if( ch<=90 && ch>=65)
		return true;
	else
		return false;
}

//--------------------------------------------------------------------
/**
*/
bool isnumber(wchar_t ch)
{
	if( ch>=48 && ch <=57 )
		return true;
	else
		return false;
}

//--------------------------------------------------------------------
/**
*/
bool isletter(wchar_t ch)
{
	ch=toupper(ch);
	if( ch<=90 && ch>=65)
		return true;
	else
		return false;
}

bool next(const std::string &pData, const size_t & doff, const std::string &pStr)
{
        for(size_t i=0;i<pStr.size();++i)
        {
                if( i+doff>=pData.size() )
                        return false;
                if( pData[doff+i]!=pStr[i] )
                        return false;
        }
        return true;
}

std::string greplace(std::string tor, std::string tin, std::string data)
{
        for(size_t i=0;i<data.size();++i)
        {
                if( next(data, i, tor)==true )
                {
                        data.erase(i, tor.size());
                        data.insert(i,tin);
                }
        }

        return data;
}

int getNextNumber(const std::string &pStr, int *read)
{
	std::string num;
	bool start=false;
	for(size_t i=0;i<pStr.size();++i)
	{
		if( isnumber(pStr[i] ) )
		{
			num+=pStr[i];
			start=true;
		}
		else if(start==true)
			return atoi(num.c_str() );

		if(read!=NULL)
			++*read;
	}

	return 0;
}

char getRandomChar(void)
{
	 return (rand()%25) + 97;
}

std::string getRandomNumber(void)
{
	return convert((float)(rand()%10000000)/(float)100);
}

void transformHTML(std::string &str)
{
	for(size_t i=0;i<str.size();++i)
	{
		if( next(str, i, "$amp;" )==true )
		{
			str.erase(i,5);
			str.insert(i,"&");
		}
	}
}

void EscapeSQLString(std::string &pStr)
{
	for(size_t i=0;i<pStr.size();++i)
	{
		if(pStr[i]=='\'')
		{
			pStr.insert(i,"'");
			++i;
		}
	}
}

void ParseParamStr(const std::string &pStr, std::map<std::string,std::string> *pMap)
{
	std::string key;
	std::string value;

	int pos=0;
	for(size_t i=0;i<pStr.size();++i)
	{
		char ch=pStr[i];
		if( ch=='=' && pos==0)
		{
			pos=1;
		}
		else if( (ch=='&'||ch=='$') && pos==1 )
		{
			pos=0;
			EscapeSQLString(value);
			pMap->insert( std::pair<std::string, std::string>(key,value) );
			key.clear(); value.clear();
		}
		else if( pos==0 )
		{
			key+=ch;
		}
		else if( pos==1 )
		{
			value+=ch;
		}
	}

	if( value.size()>0 || key.size()>0 )
	{
		EscapeSQLString(value);
		pMap->insert( std::pair<std::string, std::string>(key,value) );
	}
}

int round(float f)
{
  return (int)(f<0?f-0.5f:f+0.5f);
}

std::string FormatTime(int timeins)
{
	float t=(float)timeins;
	int h;
	int m;
	int s;

	h=int(t/3600.0f);
	m=int(t/60)-h*60;
	s=int(t-h*3600-m*60);

	std::string sh,sm,ss;
	sh=convert(h);
	sm=convert(m);
	ss=convert(s);
	if( sm.size()==1 && h>0 )
		sm="0"+sm;
	if( ss.size()==1 )
		ss="0"+ss;

	std::string ret=sm+":"+ss;

	if(h>0)
		ret=sh+":"+ret;

	return ret;
}

//-------------------HTML DECODE-----------------

const char array[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'}; 

unsigned long hexToULong(const std::string &data)
{
	std::string str=strlower(data);
	unsigned int hex_length = (unsigned int)str.size();
	unsigned long return_value = 0;
	for(unsigned int i = 0; i < hex_length; i++)
	{
		for(unsigned char j = 0; j < 16; j++)
		{
			if( str[i] == array[j])
			{			
				return_value = ((return_value * 16) + j);
			}
		}
	}
	return return_value;
}


string htmldecode(string str, bool html)
{
	for(size_t i=0;i<str.size();i++)
	{
		if(str[i]=='%' && i+2<str.size())
		{
			std::string data; data.push_back(str[i+1]); data.push_back(str[i+2]);
			unsigned char ch=(unsigned char)hexToULong(data);
			if( ch!=0 && html==true )
			{
				str.erase(i,3);
				if( ch!='-' && ch!=',' && ch!='#' )
					str.insert(i,"&#"+convert((unsigned int)ch)+";" );
				else
				{
					std::string c;
					c.push_back(ch);
					str.insert(i,c);
				}
			}
			else if( ch!=0 )
			{
				str[i]=ch;
				str.erase(i+1,2);
			}
		}
	}
	return str;
}

bool checkhtml(const std::string &str)
{
	for(size_t i=0;i<str.size();++i)
	{
		char ch=str[i];
		if( ch=='<' || ch=='>')
			return false;
	}

	return true;
}

std::string nl2br(std::string str)
{
	for(size_t i=0;i<str.size();++i)
	{
		if( str[i]=='\n' )
		{
			str.erase(i,1);
			str.insert(i,"<br>");
		}
		else if( next(str,i,"&#10;")==true )
		{
			str.erase(i,5);
			str.insert(i,"<br>");
		}
	}

	return str;
}

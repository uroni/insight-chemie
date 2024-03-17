#ifndef MESHLIST_H
#define MESHLIST_H

//-------------------
#include <string>

using namespace std;

class meshlist
{
public:
	meshlist(void);
	~meshlist(void);
	bool open(string file,bool create=false);
	bool save(string file="");
	bool selectmesh(string mesh);
	bool selectmesh(int mnum);
	bool delmesh(string mesh);
	bool delmesh(int mnum);
	string getvalue(string name);
	string getvalue(int vnum);
	string getkey(int vnum);
	bool delvalue(string name);
	bool changevalue(string name,string value);
	bool savemesh(void);
	void delall(void);
	int getidbyname(string mname);
	string getnamebyid(int id);
	void add(string toAdd,bool front=false);
	void setdata(string dts);

private:
	string* data;
	string* meshdata;
	string* selmeshname;
	string* sFileName;
	int selid;
};






//----------------------

#endif //MESHLIST_H

#include <fstream>
#include <iostream>
#include <string>

#pragma hdrstop

#include "meshlist.h"


using namespace std; 



meshlist::meshlist(void){
	data=new string();
	meshdata=new string();
	selmeshname=new string();
	sFileName=new string();
}

meshlist::~meshlist(void){
	delete data;
	delete meshdata;
	delete selmeshname;;
	delete sFileName;;
}


bool meshlist::open(string file,bool create)
{
	fstream FileBin;

	FileBin.open(file.c_str(), ios::in|ios::binary);
	
	if(!FileBin){
		cout << "Could not open " << file << endl;
		if(create==true){
			cout << "Creating it!" <<endl;
			(*sFileName)=file;
			data->clear();
			save();
			return true;			
		}
		else{
			return false;
		}
	}

	// 1. Dateigröße bestimmen. 
    FileBin.seekg(0, ios::end); 
    unsigned long FileSize = streamoff(FileBin.tellg()); 
    FileBin.seekg(0, ios::beg); 

	char* buffer=new char[FileSize+5];
     
    // 2. Puffer anlegen und Datei einlesen. 
    FileBin.read(buffer, FileSize);
	buffer[FileSize]='\0';
	(*data)=buffer;

	delete[] buffer;


	for(unsigned int i=0;i<(*data).size();i++){
		if((*data)[i]=='\r'){
			(*data).erase(i,1);
		}

	}


	(*sFileName)=file;

	FileBin.close();


	return true;
}

bool meshlist::save(string file)
{
	if(file=="")file=(*sFileName);

	fstream FileBin;

	FileBin.open(file.c_str(), ios::out|ios::binary);
	
	if(!FileBin) return false;

	FileBin.seekg(0, ios::beg); 

	FileBin.write((*data).c_str(), (*data).length());

	FileBin.close();

	return true;
}

bool meshlist::selectmesh(string mesh)
{
	(*selmeshname)=mesh;
	selid=getidbyname(mesh);
	bool in=false;
	string name;
	string inner;
	bool in2=false;
	for(unsigned int i=0;i<(*data).size();i++){
		char ch=(*data)[i];
		if(in2==false&&ch!='\n'&&ch!='{') name+=ch;
		if(ch=='{'&&in==false){
			if(name.compare(mesh)==0) in=true;
			name="";
			in2=true;
		}
		if(in==true&&ch!='{'&&ch!='}')
			inner+=ch;
		if(ch=='}'&&in==true){
			in=false;
			name="";
		}
		if(ch=='}'&&in2==true){
			in2=false;
		}
	}
	if(inner.length()<3) return false;
	*meshdata=inner;

	return true;
}

string meshlist::getvalue(string name)
{
	string right;
	string left;
	string gLine;
	for(unsigned int i=0;i<(*meshdata).size();i++){
		char ch=(*meshdata)[i];
		if(ch!='\n')gLine+=ch;
		if(ch=='\n'){
			if(gLine.size()>3){
				int pos=0;
				for(unsigned int u=0;u<gLine.size();u++){
					char x=gLine[u];
					if(pos==0&&x!='=')left+=x;
					if(pos==1)right+=x;
					if(x=='=')pos=1;
				}
				if(left.compare(name)==0){
					//right=convertPath(right);
					return right;
				}
			}
			right="";
			left="";
			gLine="";
		}
	}
	return "";
}

bool meshlist::selectmesh(int mnum)
{
	(*selmeshname)=getnamebyid(mnum);
	selid=mnum;
	bool in=false;
	string inner;
	int num=0;
	for(unsigned int i=0;i<(*data).size();i++){
		char ch=(*data)[i];
		if(ch=='{'&&in==false){
			num++;
			if(num==mnum) in=true;
		}
		if(in==true&&ch!='\r'&&ch!='{'&&ch!='}')
			inner+=ch;
		if(ch=='}'&&in==true){
			in=false;
		}
	}
	if(inner.length()<3) return false;
	(*meshdata)=inner;

	return true;
}

string meshlist::getvalue(int vnum){
	string right;
	string left;
	string gLine;
	int num=0;
	for(unsigned int i=0;i<(*meshdata).size();i++){
		char ch=(*meshdata)[i];
		if(ch!='\n')gLine+=ch;
		if(ch=='\n'){
			if(gLine.size()>3){
				int pos=0;
				for(unsigned int u=0;u<gLine.size();u++){
					char x=gLine[u];
					if(pos==0&&x!='=')left+=x;
					if(pos==1)right+=x;
					if(x=='=')pos=1;
				}
				num++;
				if(num==vnum){
					return right;
				}
			}
			right="";
			left="";
			gLine="";
		}
	}
	return "";
	
}

string meshlist::getkey(int vnum)
{
	string right;
	string left;
	string gLine;
	int num=0;
	for(unsigned int i=0;i<(*meshdata).size();i++){
		char ch=(*meshdata)[i];
		if(ch!='\n')gLine+=ch;
		if(ch=='\n'){
			if(gLine.size()>3){
				int pos=0;
				for(unsigned int u=0;u<gLine.size();u++){
					char x=gLine[u];
					if(pos==0&&x!='=')left+=x;
					if(pos==1&&x!='=')right+=x;
					if(x=='=')pos++;
				}
				num++;
				if(num==vnum){
					return left;
				}
			}
			right="";
			left="";
			gLine="";
		}
	}
	return "";
}


bool meshlist::delmesh(int mnum){
	bool in=false;
	int start=0;
	int num=0;
	int le=0;

	if(mnum>1){
		for(unsigned int i=0;i<(*data).size();i++){
			char ch=(*data)[i];
			if(ch=='}'&&in==true){
				break;
			}
			if(in==true)le++;
			if(ch=='}'&&in==false){
				num++;
				if(num==mnum-1){
					start=i;
					in = true;
				}
			}
			
		}
	}
	else{
		start=-1;
		for(unsigned int i=0;i<(*data).size();i++){
			le++;
			if((*data)[i]=='}')break;
		}
	}

	if(start==0||le==0)return false;
	le++;
	start++;
	(*data).erase(start,le);

	return true;
}

bool meshlist::delmesh(string mesh){

	int mnum=getidbyname(mesh);
	if(mnum==-1) return false;
	bool in=false;
	int start=0;
	int num=0;
	int le=0;

	if(mnum>1){
		for(unsigned int i=0;i<(*data).size();i++){
			char ch=(*data)[i];
			if(ch=='}'&&in==true){
				break;
			}
			if(in==true)le++;
			if(ch=='}'&&in==false){
				num++;
				if(num==mnum-1){
					start=i;
					in = true;
				}
			}
			
		}
	}
	else{
		start=-1;
		for(unsigned int i=0;i<(*data).size();i++){
			le++;
			if((*data)[i]=='}')break;
		}
	}

	if(start==0||le==0)return false;
	le++;
	start++;
	(*data).erase(start,le);

	return true;
}

int meshlist::getidbyname(string mname){
	int num=0;
	string thename;
	bool n=true;
	for(unsigned int i=0;i<(*data).size();i++){
		char ch=(*data)[i];
		if(n==true&&ch!='{'&&ch!='}'&&ch!='\n'&&ch!='\r')thename+=ch;
		if(ch=='{'){
			num++;
			n=false;
			if(thename.compare(mname)==0)return num;
			thename="";
		}
		if(ch=='}')n=true;
	}
	return -1;
}

string meshlist::getnamebyid(int id){
	int num=0;
	string thename;
	bool n=true;
	for(unsigned int i=0;i<(*data).size();i++){
		char ch=(*data)[i];
		if(n==true&&ch!='{'&&ch!='}'&&ch!='\n'&&ch!='\r')thename+=ch;
		if(ch=='{'){
			num++;
			n=false;
			if(num==id)return thename;
			thename="";
		}
		if(ch=='}'){
			n=true;
		}
	}
	return "";
}


bool meshlist::delvalue(string name)
{
	string right;
	string left;
	string gLine;
	int start,il=0;
	for(unsigned int i=0;i<(*meshdata).size();i++){
		char ch=(*meshdata)[i];
		if(ch!='\n'&&ch!=' ')gLine+=ch;
		il++;
		if(ch=='\n'){
			if(gLine.size()>3){
				int pos=0;
				for(unsigned int u=0;u<gLine.size();u++){
					char x=gLine[u];
					if(pos==0&&x!='=')left+=x;
					if(pos==1&&x!='=')right+=x;
					if(x=='=')pos++;
				}
				if(left.compare(name)==0){
					start++;
					(*meshdata).erase(start,il);
					return true;
				}					
			}
			right="";
			left="";
			gLine="";
			start=i;
			il=0; 
		}
	}
	return false;
}


bool meshlist::changevalue(string name,string value)
{
	string right;
	string left;
	string gLine;
	int start,il=0;
	for(unsigned int i=0;i<(*meshdata).size();i++){
		char ch=(*meshdata)[i];
		if(ch!='\n'&&ch!=' ')gLine+=ch;
		il++;
		if(ch=='\n'){
			if(gLine.size()>3){
				int pos=0;
				for(unsigned int u=0;u<gLine.size();u++){
					char x=gLine[u];
					if(pos==0&&x!='=')left+=x;
					if(pos==1&&x!='=')right+=x;
					if(x=='=')pos++;
				}
				if(left.compare(name)==0){
					start++;
					(*meshdata).erase(start,il);
					string newvalue=name+"="+value+"\n";
					(*meshdata)+=newvalue;
					savemesh();
					return true;
				}					
			}
			right="";
			left="";
			gLine="";
			start=i;
			il=0; 
		}
	}
	string newvalue=name+"="+value+"\n";
	(*meshdata)+=newvalue;
	savemesh();
	return true;
}


bool meshlist::savemesh(void)
{
	int id=getidbyname((*selmeshname));

	int num=0;
	int in=0;
	string out1;
	string out2;
	string sin;

	for(unsigned int i=0;i<(*data).size();i++){
		char ch=(*data)[i];

		if(ch=='}'&&in==1)in=2;
		if(in==0) out1+=ch;
		if(in==1) sin+=ch;
		if(in==2) out2+=ch;

		if(ch=='{'){
			num++;
			if(num==id)in=1;
		}
	}

	if(out1==""||out2==""||sin=="")return false;
	else
	{
		(*data)=out1+(*meshdata)+out2;
	}
	return true;
}


void meshlist::add(string toAdd,bool front){
	if(front==false)(*data)+=toAdd;
	else (*data)=toAdd+(*data);
}

void meshlist::setdata(string dts)
{
	(*data)=dts;
}


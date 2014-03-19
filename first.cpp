#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
using namespace std;

int main(int argc, char *argv[]){
	string line;
	//string search="407143";
	string search=argv[1];
	unsigned int line_count=1;
	string file_name;
	DIR *dp;
	struct dirent *dirp;
	if ((dp = opendir(".")) != NULL){
		
	}
	while((dirp=readdir(dp))!=NULL){
		if((string(dirp->d_name) != ".") and (string(dirp->d_name) != "..") and (string(dirp->d_name).find(".exe") == -1)){
			cout<<"\nFile: "<<string(dirp->d_name)<<endl;
			file_name=dirp->d_name;
			ifstream file1;
			file1.open(file_name.c_str());
			if(file1.is_open()){
				while(getline(file1,line)){
					int pos = line.find(search);
					if (pos!=-1){
						cout<<"Line: "<<line_count;
						cout<<", "<<line.substr(0,pos);
						cout<<"\e[033;31m";
						cout<<line.substr(pos,search.length());
						cout<<"\e[033;0m";
						cout<<line.substr(pos+search.length(),line.length())<<"\n";
						
					}
					++line_count;
				}
				file1.close();
			}else{
				cout<<"Unable to open";
			}
		}
	}

	return 0;
}

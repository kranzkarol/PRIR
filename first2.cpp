#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sstream>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
using namespace std;

int file__count(DIR *dp){
	struct dirent dirp;
	struct dirent *result;
	unsigned int file_count=1;
	int return_code;
	for (return_code = readdir_r(dp, &dirp, &result);
         result != NULL && return_code == 0;
         return_code = readdir_r(dp, &dirp, &result))
		file_count++;
	return file_count;
}
int line__count(string file_name){
	ifstream file1;
	file1.open(file_name.c_str());
	int line_count=1;
	string line;
	while(getline(file1,line)){
		line_count++;
	}
	file1.close();
	return line_count;
}

int main(int argc, char *argv[]){
	string line;
	string file_name;
	DIR *dp;
	dp = opendir(".");
	struct dirent dirp;
	struct dirent *result;
	struct stat file_info;
	
	if (argc!=2){
		cout<<"USAGE:\n "+string(argv[0])+" word_to_search";
	}else{
		string search = argv[1];
		int file_count = file__count(dp);		
		
		dp = opendir(".");
		for(int j=1;j<file_count;j++){
		
			readdir_r(dp, &dirp, &result);
			file_name=dirp.d_name;
			lstat(dirp.d_name, &file_info); 
			ostringstream temp;
			
			if((file_name.find(".exe") == -1) and !S_ISDIR(file_info.st_mode)){
				
				ifstream file1;
				int line_count = line__count(file_name);
				file1.open(file_name.c_str());	
				
				if(file1.is_open()){
					for(int i=1;i<=line_count;i++){
						getline(file1,line);
						int pos = line.find(search);
						if (pos!=-1){
							temp<<"Line: "<<i;
							temp<<", "<<line.substr(0,pos);
							temp<<"\e[033;31m";
							temp<<line.substr(pos,search.length());
							temp<<"\e[033;0m";
							temp<<line.substr(pos+search.length(),line.length())<<"\n";
						
						}
					}
					if(!temp.str().empty()){
						char path [PATH_MAX-1];
						char *ptr;
						ptr = realpath(dirp.d_name,path);
						
						cout<<endl<<ptr<<endl<<temp.str();
					}
				}else{
					cout<<"Unable to open";
				}
				file1.close();
			}
		}
	}
	return 0;
}


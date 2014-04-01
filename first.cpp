#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sstream>
using namespace std;

int file__count(DIR *dp){
	struct dirent *dirp;
	unsigned int file_count=1;
	while((dirp=readdir(dp))!=NULL){
		file_count++;
	}
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
	struct dirent *dirp;
	if (argc!=2){
		cout<<"USAGE:\n "+string(argv[0])+" word_to_search";
	}else{
		string search = argv[1];
		int file_count = file__count(dp);	
		ostringstream output;
		ostringstream temp;
		dp = opendir(".");
		int i,j;
		unsigned char isFile=0x8;
		ifstream file1;
		int line_count;
		int pos;
		#pragma omp parallel for private(i,j,temp,dirp,file_name,file1,line_count,line,pos,isFile)\
		shared(output,dp, search) 
		for(i=1;i<file_count;i++){
			dirp=readdir(dp);
			if((string(dirp->d_name).find(".exe") == -1) and dirp->d_type == isFile){
				temp<<"\nFile: "<<string(dirp->d_name)<<endl;
				//cout<<"\nFile: "<<string(dirp->d_name)<<endl;
				file_name=dirp->d_name;
				line_count = line__count(file_name);
				file1.open(file_name.c_str());				
				if(file1.is_open()){
					for(j=1;j<=line_count;j++){
						getline(file1,line);
						pos = line.find(search);
						if (pos!=-1){
							temp<<"Line: "<<j;
							temp<<", "<<line.substr(0,pos);
							temp<<"\e[033;31m";
							temp<<line.substr(pos,search.length());
							temp<<"\e[033;0m";
							temp<<line.substr(pos+search.length(),line.length())<<"\n";
						}
					}
					output<<temp.str();
				}else{
					cout<<"Unable to open";
				}
				file1.close();
			}
		}
		cout<<output.str();
	}
	return 0;
}


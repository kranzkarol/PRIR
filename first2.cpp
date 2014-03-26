#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
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
		
		dp = opendir(".");
		
		#pragma omp parallel 
		{
		#pragma omp for schedule(static) 
		for(int j=1;j<file_count;j++){
			unsigned char isFile=0x8;
			dirp=readdir(dp);
			if((string(dirp->d_name).find(".exe") == -1) and dirp->d_type == isFile){
				cout<<"\nFile: "<<string(dirp->d_name)<<endl;
				file_name=dirp->d_name;
				ifstream file1;
				int line_count = line__count(file_name);
				
				file1.open(file_name.c_str());				
				if(file1.is_open()){
					#pragma omp parallel private(file1)
					{
					#pragma omp for schedule(static) 
					for(int i=1;i<=line_count;i++){
						getline(file1,line);
						int pos = line.find(search);
						if (pos!=-1){
							cout<<"Line: "<<i;
							cout<<", "<<line.substr(0,pos);
							cout<<"\e[033;31m";
							cout<<line.substr(pos,search.length());
							cout<<"\e[033;0m";
							cout<<line.substr(pos+search.length(),line.length())<<"\n";
						}
					}
					}
				}else{
					cout<<"Unable to open";
				}
				file1.close();
			}
		}
		}
	}
	return 0;
}


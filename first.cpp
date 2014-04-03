#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sstream>

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
		ostringstream output;
		ostringstream temp;
		dp = opendir(".");
		int i,j;
		ifstream file1;
		int line_count;
		int pos;
		#pragma omp parallel for private(i,j,temp,dirp,file_name,file1,line_count,line,pos,file_info)\
		shared(output,dp, search) 
		for(i=1;i<file_count;i++){
			readdir_r(dp, &dirp, &result);
			lstat(dirp.d_name, &file_info); 
			
			if((string(dirp.d_name).find(".exe") == -1) and !S_ISDIR(file_info.st_mode)){
				temp<<"\nFile: "<<i<<" "<<string(dirp.d_name)<<endl;
				file_name=dirp.d_name;
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
		//cout<<temp.str();
	}
	return 0;
}


#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sstream>
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

int main(int argc, char *argv[]){
	int x=5;
	char files[x][40];
	char lines[x][40];
	int i,j;
	

	DIR *dp;
	dp = opendir(".");
	struct dirent dirp;
	struct dirent *result;

	unsigned int y=-1;
	cout<<y;

	
	for (i=0;i<9;i++){
		readdir_r(dp, &dirp, &result);
		if((string(dirp.d_name).find(".exe") == -1)){
			
			cout<<dirp.d_name<<" "<<dirp.d_type<<endl;
		}
	}
		 
	string file_name="test";
	string line;
	ifstream file1;
	file1.open(file_name.c_str());	
	cout<<file1.is_open();
	getline(file1,line);
	cout<<line;
	// #pragma omp parallel for private(i,j) 
	// 	for(i=0;i<x;i++){
	// 		ostringstream loc;
	// 		loc<<"File: "<<i<<endl;
	// 		//snprintf(files[i],sizeof(files[i]),"%s %d %s","File: ",i,"\n");
	// 		for(j=0;j<x;j++){
	// 			loc<<"Line: "<<j<<endl;
	// 			//snprintf(lines[i],sizeof(lines[i]),"%s %d %s","Line: ",i,"\n");
	// 		}
	// 		st<<loc.str()<<endl;
	// 	}
	//cout<<st.str();

	
	return 0;
}
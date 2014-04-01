#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>
#include <sstream>
#include <dirent.h>
using namespace std;


int main(int argc, char *argv[]){
	int x=5;
	char files[x][40];
	char lines[x][40];
	int i,j;
	
	DIR *dp;
	dp = opendir(".");
	struct dirent dirp;
	struct dirent *result;
	int return_code;
	dp = opendir(".");
	
	for (return_code = readdir_r(dp, &dirp, &result);
         result != NULL && return_code == 0;
         return_code = readdir_r(dp, &dirp, &result))
		 cout<<dirp.d_name<<endl;
	
	//dirp=readdir_r(dp,dirp,dirp);
	// cout<<dirp<<endl;
	// dirp=readdir(dp);
	// dirp=readdir(dp);
	// dirp=readdir(dp);
	// dirp=readdir(dp);
	// dirp=readdir(dp);
	//unsigned char sd=dirp->d_type;
	//cout<<"fefef "<<sd<<endl;
	
	ostringstream st;
	
	#pragma omp parallel for private(i,j) 
		for(i=0;i<x;i++){
			ostringstream loc;
			loc<<"File: "<<i<<endl;
			//snprintf(files[i],sizeof(files[i]),"%s %d %s","File: ",i,"\n");
			for(j=0;j<x;j++){
				loc<<"Line: "<<j<<endl;
				//snprintf(lines[i],sizeof(lines[i]),"%s %d %s","Line: ",i,"\n");
			}
			st<<loc.str()<<endl;
		}
	cout<<st.str();
	// for(i=0;i<x;i++){
		// cout<<files[i];
		// for(j=0;j<x;j++){
			// cout<<lines[j];
		// }
	// }
	
	// int num =1;
	// string b;
	// ostringstream st;
	// st<<num<<' ';
	// cout<<st.str();
	
	return 0;
}
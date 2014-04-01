#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <stdlib.h>

using namespace std;


int main(int argc, char *argv[]){
	
	
	
	int i,j;
	int file__count=5;
	int line__count=5;
	string* files = new string[file__count];
	string* lines = new string[line__count];
	
	int Number=1;
	string a=itoa(Number);
	
	cout<<a;

	#pragma omp parallel for private(a,i,j) reduction(+:files) 
		for(i=1;i<file__count;i++){
			// sprintf(files[i],"%s%d\n","File: ",i);
			
			files[i]="Files: ";

			for(j=1;j<line__count;j++){
				// sprintf(files[j],"%s%d\n","Line: ",j);
				
			}
		}

	cout<<files[1];


	return 0;
}
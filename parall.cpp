#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
using namespace std;


int main(int argc, char *argv[]){
	
	string li1[]={"1","2","3"};
	string li2[]={"4","5","6"};
	string li3[]={"7","8","9"};
	string fi[3][4]={*li1,*li2,*li3};
	
	int i,j;
	string glo;
	#pragma omp parallel private(j) shared(fi)
	{
		#pragma omp for schedule(static) 
		for(j=1;j<5;j++){
			glo=glo+"File: "+std::to_string(j)+"\n";
			string loc;
			#pragma omp parallel private(i) shared(fi)
			{
			#pragma omp for schedule(static) 
			for(i=1;i<5;i++){
				
			}
			}
		}
	}
	return 0;
}
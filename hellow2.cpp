#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <sstream>
#include <stdlib.h>

#include <sys/stat.h>
#include <sys/types.h>
#include "mpi.h"


using namespace std;

MPI_Status status;

int file__count(DIR *dp){
	struct dirent dirp;
	struct dirent *result;
	struct stat file_info;
	unsigned int file_count=1;
	int return_code;
	for (return_code = readdir_r(dp, &dirp, &result);
         result != NULL && return_code == 0;
         return_code = readdir_r(dp, &dirp, &result)){
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
main(int argc, char **argv)
{
	int	i,j,k, mynum, nprocs;

	int length;	
	char name[BUFSIZ];
	
	
	if (argc!=2){
		//cout<<"USAGE:\n "+file_name+" word_to_search";
		exit(0);
	}
	string search = argv[1];
	string file_name=string(argv[0]);
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &mynum);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Get_processor_name(name, &length);
	
	
	string line;
	ostringstream output;
	
	DIR *dp;
	dp = opendir(".");
	int file_count = file__count(dp);

	string *files = new string[file_count];
	
	struct dirent dirp;
	struct dirent *result;
	struct stat file_info;
	
	dp = opendir(".");
	
	int return_code;
	ifstream file1;
	int line_count;
	int pos;
	j=0;

	return_code = readdir_r(dp, &dirp, &result);

	while(result != NULL && return_code == 0){
		lstat(dirp.d_name, &file_info); 
		file_name=dirp.d_name;
		if (!S_ISDIR(file_info.st_mode))
		{
			files[j]=file_name;
			j++;
		}
		return_code = readdir_r(dp, &dirp, &result);
	}
	
	for (int i = mynum; i < j; i+=nprocs){
			
		file_name=files[i];
		
		ostringstream temp;
		line_count = line__count(file_name);
		file1.open(file_name.c_str());	
		
		if(file1.is_open()){
			for(k=1;k<=line_count;k++){
				getline(file1,line);
				pos = line.find(search);
				if (pos!=-1){
					temp<<"Line: "<<k;
					temp<<", "<<line.substr(0,pos);
					temp<<"\e[033;31m";
					temp<<line.substr(pos,search.length());
					temp<<"\e[033;0m";
					temp<<line.substr(pos+search.length(),line.length())<<"\n";
				}
			}
			if(!temp.str().empty()){
				char path [PATH_MAX];
				char *ptr;
				ptr = realpath(file_name.c_str(), path);
				output<<endl<<ptr<<endl<<temp.str();
			}
			file1.close();
		}else{
			output<<"Unable to open";
		}
		//cout<<"mynum: "<<mynum<<" i: "<<files[i]<<" name: "<<name<<endl;
	}
	fflush(stdout);
	cout<<output.str()<<endl;
	
	/*

	while (N > 0) {
		w = 1.0/(float)N;
		sum = 0.0;
		for (i = mynum+1; i <= N; i+=nprocs)
			sum = sum + f(((float)i-0.5)*w);
		sum = sum * w;
		err = sum - pi;

	 Step (4): print the results
		* Parallel version: collect partial results and let master instance
		* print it.
	
		
		if (mynum==0) {
			printf ("host calculated x = %7.5f\n", sum);
			for (i=1; i<nprocs; i++) {
				source = i;
				info = MPI_Recv(&x, 1, MPI_FLOAT, source, type, MPI_COMM_WORLD, &status);
				printf ("host got x = %7.5f\n", x);
				sum=sum+x;
			}
			err = sum - pi;
			printf ("sum, err = %7.5f, %10e\n", sum, err);
			fflush(stdout);
		}

	 Other instances just send their sum and wait for more input 
		
		else {
			info = MPI_Send(&sum, 1, MPI_FLOAT, dest, type, MPI_COMM_WORLD);
			if (info != 0) {
				printf ("instance no, %d failed to send\n", mynum);
				exit(0);
			}
			printf ("inst %d sent partial sum %7.2f to inst 0\n", mynum, sum);
			fflush(stdout);
		}
		
 get a value of N for the next run */
		
//		solicit (&N, &nprocs, mynum);
	//}
	MPI_Finalize();
}


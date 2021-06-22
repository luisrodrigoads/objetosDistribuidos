#include<stdio.h>
#include<string.h>

int main(){
	
	int x;
	FILE *file;
	
	file = fopen("multiplosde3.txt","w+");
	for(x=1; x <= 90000000;x++){
		if(x%3 == 0)
			fprintf(file,"%d\n",x);
	}
	fclose(file);
	
	file = fopen("multiplosde5.txt","w+");
	for(x=1; x <= 9000000;x++){
		if(x%5 == 0)
			fprintf(file,"%d\n",x);
	}
	fclose(file);
	
	file = fopen("multiplosde7.txt","w+");
	for(x=1; x <= 9000000;x++){
		if(x%7 == 0)
			fprintf(file,"%d\n",x);
	}
	fclose(file);
	
	file = fopen("multiplosde9.txt","w+");
	for(x=1; x <= 9000000;x++){
		if(x%9 == 0)
			fprintf(file,"%d\n",x);
	}
	fclose(file);
		
}

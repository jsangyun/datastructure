#include <stdio.h>
#include <stdlib.h>

typedef struct studentT{
	char *name;
	int literature;
	int math;
	int science;
	double average;
} studentT;

int main(int argc, char *argv[]){
  FILE *fp = NULL;
  
	fp = fopen(argv[1], "rt");
	
	if(fp==NULL){
	  exit(0);
	}

	unsigned int number;
	fscanf(fp, "%u", &number);
	
	studentT *students = (studentT*)malloc(sizeof(studentT)*number); 
	
	int i;
	for(i=0;i<number;i++){
	  students[i].name = (char*)malloc(sizeof(char));  
		fscanf(fp, "%s %d %d %d", students[i].name, &students[i].literature, &students[i].math, &students[i].science);
		students[i].average = ((double)students[i].literature + (double)students[i].math + (double)students[i].science) / 3;
	}
	fclose(fp);
	
	fp = fopen(argv[2], "wt");
	
	fprintf(fp, "Name    Literature    Math    Science    Ave.\n");
	for(i=0;i<number;i++){
		fprintf(fp, "%s    %d    %d    %d    %.2f\n", students[i].name, students[i].literature, students[i].math, students[i].science, students[i].average);
	}
	
	double lit_avg, math_avg, sce_avg, all_avg;
	int total1=0, total2=0, total3=0;
	double total4=0;
	for(i=0;i<number;i++){
		total1 += students[i].literature;
		total2 += students[i].math;
		total3 += students[i].science;
		total4 += students[i].average;
	}
	lit_avg = (double)total1/number;
	math_avg = (double)total2/number;
	sce_avg = (double)total3/number;
	all_avg = (double)total4/number;
	
	fprintf(fp, "Ave.    %.2f    %.2f    %.2f    %.2f\n", lit_avg, math_avg, sce_avg, all_avg);
	
	fclose(fp);
	
	free(students);
	
	return 0;
}

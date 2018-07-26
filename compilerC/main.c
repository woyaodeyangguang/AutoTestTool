/*
**Entry point of HCC 1.0
**This code is based on various open resources, intented for educational
**purposes only. You can access, modify this for your personal use freely,
**but any attempts for comercial exploitation from this code are considered 
**unethical and should be discouraged.
*/

#include "c.h"
#include <stdio.h>
#include <stdlib.h>
char *file;

int main(int argc, char *argv[]) 
{
  char * infile, *shortclass, *finalclass;
  char classname[256], inputfile[256], outputfile[256];    
  
  if(argc != 3){
    fprintf(stderr,"usage: hcc input-file-name.t\n");
    return 1;
    }

  if(argc==3) {
    int len = strlen(argv[1]) - 2;
    //Invoke the python script to preprocess the input .t file
    char command[256], newoutput[256];
    shortclass = (char*)malloc(256*sizeof(char));
    
    memset(classname, 256*sizeof(char), 0);
    strncpy(classname, argv[1], strlen(argv[1])-2);
    classname[len] = '\0';
    sprintf(inputfile, "%s%s", classname, ".top");
    
    sprintf(command, "python preprocess.py %s\n", argv[1]);
    printf(command);
    system(command);
    
//    printf("class name %s\n", inputfile);
    sprintf(command, "python topDef.py %s\n", inputfile);

    system(command);

    sprintf(inputfile, "%s%s", classname, ".c");
    sprintf(outputfile, "%s%s", classname, ".java");
    infile = inputfile;        

    //printf("class name %s\n", classname);
    strcpy(shortclass, classname);
    finalclass = (char*)strtok(shortclass,"/");
    if(finalclass) { 
         shortclass = strtok(NULL, "/"); 
         //printf("C %s, class %s\n", shortclass, classname);
         if(shortclass!=NULL) {
             while(shortclass) {
                 finalclass = shortclass;
                 shortclass = strtok(NULL,"/");
             } 
         }
         else {                         
             shortclass = (char*)strtok(finalclass, "\\");
             while(shortclass) {
                 finalclass = shortclass;
                 shortclass = strtok(NULL,"\\");
             } 
         }
    }  
   
  if(!infile || freopen(infile, "r", stdin)==NULL) {
    fprintf(stderr,"%s: can not read file: '%s'\n", argv[0], infile);
    exit(1);
  } 
  //printf("STAT\n");
  inittypes();

  /* the file under compilation */
  file = infile;
  yyparse();

  astchk();
//Generate Java code here.
    irgen(infile, outputfile, finalclass, argv[2]);
  
//FOR test only  
      sprintf(newoutput, "%s%s\\", "..\\WebAutoTest\\src\\test\\java\\com\\sinosoft\\autotest\\", argv[2]); 
      //sprintf(newoutput, "%s", "C:\\gugong_test\\test\\WebAutoTest\\src\\test\\java\\com\\sinosoft\\autotest\\cloudplatform\\"); 

      sprintf(command, "copy %s %s\n", outputfile, newoutput);
      printf(command);
      system(command);
      fclose(stdin);
      
      //move and delete the intermediate files
      sprintf(command, "del %s\n", infile);
      system(command);
    
      sprintf(infile, "%s.top", classname);
      sprintf(command, "del %s\n", infile);  
 
      system(command);
      
      sprintf(infile, "%s.it", classname);
      sprintf(command, "del %s\n", infile); 
      system(command);
  // irecho();
        sprintf(infile, "%s.java", classname);
      sprintf(command, "del %s\n", infile); 
      system(command);

  //  x86gen();
  deallocate();
}
  return 0;
}

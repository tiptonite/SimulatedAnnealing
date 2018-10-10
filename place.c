#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
	
	int x;
	int y;
	int num;
			

} Node;


Node* array;



void main(int argc, char const *argv[]){

    if(argc<3){
        printf("\n Not enough arguments, please provide input file and output file\n");
        exit(EXIT_FAILURE);

    }
    FILE *fptr;
    size_t len = 0;
    ssize_t nread;
    if((fptr=fopen(argv[1],"r"))==NULL){
        printf("Error opening input file");
        exit(EXIT_FAILURE);
    }
    char *buffer=NULL;
    char intBuff[32];
    int intBuffindex=0;
    int x=-1;
    int y=-1;
    int numNodes=-1;
    int arrayIndex=0;
    int nodeX=-1;
    int nodeY=-1;
	int testNumNodes=0;
	char* test;
    char* value;
    const char delim[2]="\n";
    const char space[2]=" ";
    while((nread = getline(&buffer, &len, fptr))!= -1){
        printf("Retrieved line of length %zu:\n",nread);
        fwrite(buffer,nread,1,stdout);
        if(buffer[0]=='g'){
            for(int i=2;buffer[i] != '\0';i++)
                if(buffer[i]==' '||buffer[i]=='\r'||buffer[i]=='\n')
                {
                    printf("X\n");
                    intBuffindex=0;
                    if(x==-1){
                        x=atoi(intBuff);
                        intBuff[0]='\0';

                    }else y=atoi(intBuff);
                }else{
                    intBuff[intBuffindex]=buffer[i];
                    intBuffindex=intBuffindex+1;
                    
                    for(int z=0;z<(intBuffindex);z++){
                        printf("%u ",intBuff[z]);

                    }
                    printf("\n");
                }



        }
        else if(buffer[0]=='v'){
		//sscanf(buffer, "%c %d",test,testNumNodes);
        value=strtok(buffer,space);
        printf("value: %s\n",value);
        test=value;

        value=strtok(NULL,delim);
        printf("value2: %s",value);
        testNumNodes=atoi(value);
            /*
             for(int i=2;buffer[i] != '\0';i++){
                 if(buffer[i]==' '||buffer[i]=='\r'||buffer[i]=='\n')
                {
                    printf("X\n");
                    intBuffindex=0;
                    if(numNodes==-1){
                        numNodes=atoi(intBuff);
                        intBuff[0]='\0';

                    }
                }else{
                    intBuff[intBuffindex]=buffer[i];
                    intBuffindex=intBuffindex+1;
                   
                    for(int z=0;z<(intBuffindex);z++){
                        printf("%u ",intBuff[z]);

                    }
                    printf("\n");
                }
                */
                Node* array=malloc(testNumNodes*sizeof(Node));
                


           //  }
                
        

        }
        else if(buffer[0]=='e'){
            value=strtok(buffer,space);
            value=strtok(NULL,space);
            nodeX=atoi(value);
            value=strtok(NULL,delim);
            array[arrayIndex].num=arrayIndex;
            array[arrayIndex].x=nodeX;
            array[arrayIndex].y=nodeY;
            arrayIndex=arrayIndex+1;
        }

     
    }
    printf("grid is sized %u by %u\n",x,y);
    printf("Number of nodes: %u\n",numNodes);
	printf("Test number of nodes: %s %d\n",test,testNumNodes);
  //  printf("Nodes:\n");
   for(int i=0;i<testNumNodes;i++){
       //printf("Node %d is at %d %d\n",i,array[i].x,array[i].y);
       printf("%d\n",i);
    }
    free(buffer);
    fclose(fptr);



    exit(EXIT_SUCCESS);
}

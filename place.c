#include <stdio.h>
#include <stdlib.h>


typedef struct Node{

    int x;
    int y;

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
    int arrayIndex=-1;
    int nodeX=-1;
    int nodeY=-1;
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
             for(int i=2;buffer[i] != '\0';i++)
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
                Node* array=malloc(numNodes*sizeof(Node));
        }
        
        else if(buffer[0]=='e'){
            for(int i=2;buffer[i] != '\0';i++)
                if(buffer[i]==' '||buffer[i]=='\r'||buffer[i]=='\n')
                {
                    printf("X\n");
                    intBuffindex=0;
                    if(arrayIndex==-1){
                        if(nodeX==-1){
                            nodeX=atoi(intBuff);
                            intBuff[0]='\0';
                        }
                        if(nodeY==-1 && nodeX !=-1){
                            nodeY=atoi(intBuff);
                            intBuff[0]='\0';
                            arrayIndex=0;
                            array[arrayIndex].x=nodeX;
                            array[arrayIndex].y=nodeY;
                            arrayIndex=arrayIndex+1;
                            nodeY=-1;
                            nodeX=-1;

                        }
                        

                    }else if(arrayIndex>0){
                        if(nodeX==-1){
                            nodeX=atoi(intBuff);
                            intBuff[0]='\0';
                        }
                        if(nodeY==-1 && nodeX !=-1){
                            nodeY=atoi(intBuff);
                            intBuff[0]='\0';
                            array[arrayIndex].x=nodeX;
                            array[arrayIndex].y=nodeY;
                            arrayIndex=arrayIndex+1;
                            nodeY=-1;
                            nodeX=-1;

                        }
                        

                    }
                }else{
                    intBuff[intBuffindex]=buffer[i];
                    intBuffindex=intBuffindex+1;
                  
                    for(int z=0;z<(intBuffindex);z++){
                        printf("%u ",intBuff[z]);

                    }
                    printf("\n");
                }


        }
     
    }
    printf("grid is sized %u by %u\n",x,y);
    printf("Number of nodes: %u\n",numNodes);
    printf("Nodes:\n");
    for(int i=0;i<numNodes;i++){
        printf("Node %u is at %u %u\n",i,array[i].x,array[i].y);

    }
    free(buffer);
    fclose(fptr);



    exit(EXIT_SUCCESS);
}
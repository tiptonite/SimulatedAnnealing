#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>

using namespace std;

#define INITIAL_TEMPERATURE 10000
#define COOLING_RATE 0.999
#define STOP_THRESHOLD 0.0001

class Edge{
public:
    int node1;
    int node2;
    double length;
};
class Node{
public:
    int x;
    int y;
    int number;
};
class Solution{
    public:
    vector<Edge> edgeArray;
    vector<Node> nodeArray;
    int score;

};
Solution anneal(Solution initial,int x, int y);
int evaluate(Solution& s);
void alter(Solution& s, int x, int y);
void copy(Solution& current, Solution& next);

int main(int argc, char const *argv[]){

    srand(time(NULL));

    if(argc<3){
        printf("\n Not enough arguments, please provide input file and output file\n");
        exit(EXIT_FAILURE);



    }
    ofstream fout;
    ifstream fin;

    fin.open(argv[1]);
    if(!fin.is_open()){

        cout<<"Error opening input file\n";
        exit(EXIT_FAILURE);
    } 
    fout.open(argv[2]);
    fout<<"Solution for "<<argv[1]<<"\n";
    char parameter;
    int x;
    int y;
    int numNodes;
    int nodeOne;
    int nodeTwo;
    int arrayIndex=0;
   // while(!fin.eof()){
       fin>>parameter;
       cout<<parameter<<" ";
       fin>>x;
       cout<<x<<" ";
       fin>>y;
       cout<<y<<"\n";

       fin>>parameter;
       cout<<parameter<<" ";
       fin>>numNodes;
       cout<<numNodes<<"\n";
        Solution initial;
       Edge temp;
       while(true){

           fin>>parameter;
           if(fin.eof())break;
           cout<<parameter<<" ";
           fin>>nodeOne;
           cout<<nodeOne<<" ";
           fin>>nodeTwo;
           cout<<nodeTwo<<"\n";
           temp.node1=nodeOne;
           temp.node2=nodeTwo;
           initial.edgeArray.push_back(temp);


            
       }

        for(int i=0; i<initial.edgeArray.size();i++){
            cout<<"Edge from "<<initial.edgeArray[i].node1<<" "<<initial.edgeArray[i].node2<<"\n";


        }
        for(int i=0; i<numNodes;i++){
            Node temp;
            temp.x=rand()%x;
            temp.y=rand()%y;
            temp.number=i;
            initial.nodeArray.push_back(temp);

        }
        for(int i=0; i<initial.nodeArray.size();i++){

            cout<<"Node "<<initial.nodeArray[i].number<<" placed at ("<<initial.nodeArray[i].x<<","<<initial.nodeArray[i].y<<")\n";
        }
   // }
   cout<<"Grid is size "<<x<<" by "<<y<<"\n";
    Solution finalSolution;
    finalSolution=anneal(initial,x,y);
    fout<<"Final score: "<<finalSolution.score<<"\n";
  
     for(int i=0; i<finalSolution.nodeArray.size();i++){

            fout<<"Node "<<finalSolution.nodeArray[i].number<<" placed at ("<<finalSolution.nodeArray[i].x<<","<<finalSolution.nodeArray[i].y<<")\n";
        }
    for(int i=0; i<finalSolution.edgeArray.size();i++){
        fout<<"Edge from "<<finalSolution.edgeArray[i].node1<<" to "<<finalSolution.edgeArray[i].node2<<" has length "<<finalSolution.edgeArray[i].length<<"\n";
    }
    fout.close();
    fin.close();
    return 0;
}

Solution anneal(Solution initial,int x, int y){

    Solution finalSolution;
    Solution current;
    Solution next;
    int deltaE;
    float p,r;
    float temperature;
    temperature=INITIAL_TEMPERATURE;
    initial.score=evaluate(initial);
    for(int i=0;i<initial.edgeArray.size();i++){
        cout<<"edge length "<<initial.edgeArray[i].length<<"\n";
    }
    cout<<"Initial Score: "<<initial.score<<"\n";
    copy(initial,current);
    cout<<"Current Score: "<<current.score<<"\n";
    while((temperature > STOP_THRESHOLD)){

        copy(current,next);
        alter(next,x,y);
        next.score=evaluate(next);
       // cout<<"new score: "<<next.score<<"\n";
        if(next.score<current.score){
            copy(next,current);
        }else{
            deltaE=abs(current.score-next.score);
            p= exp(-((float)deltaE)/temperature);
            r = (float) rand() / (float) RAND_MAX;
            if(r<p){
                copy(next,current);
            }
        }
        
        temperature=temperature*COOLING_RATE;
       // cout<<temperature<<"\n";
    }

    copy(current,finalSolution);
  


    return finalSolution;
}
void copy(Solution& current, Solution& next){
next.edgeArray=current.edgeArray;
next.nodeArray=current.nodeArray;
next.score=current.score;




}
int evaluate(Solution& s){
    int currentScore=0;
    double distance=0;
    //calculate distance between nodes based on edges
    for(int i=0;i<s.edgeArray.size();i++){
        distance=abs(s.nodeArray[s.edgeArray[i].node1].x-s.nodeArray[s.edgeArray[i].node2].x)+abs(s.nodeArray[s.edgeArray[i].node1].y-s.nodeArray[s.edgeArray[i].node2].y);       
       // cout<<"distance: "<<distance<<"\n";
        s.edgeArray[i].length=distance;
        currentScore=currentScore+distance;
    }
    //check for overlapping nodes

    for(int i=0;i<s.nodeArray.size();i++){
        for(int j=i+1;j<s.nodeArray.size();j++){

            if(s.nodeArray[i].x==s.nodeArray[j].x){
                if(s.nodeArray[i].y==s.nodeArray[j].y){
                    if(i != j){
                        currentScore=currentScore+1000;
                       // cout<<"Nodes "<<i<<" and "<<j<<" overlap\n";
                    }
                }


            }
        }

    }



    return currentScore;

}

void alter(Solution& s, int x, int y){
    
    int changeIndex;
    changeIndex=rand()%s.nodeArray.size();
    s.nodeArray[changeIndex].x=rand()%x;
    s.nodeArray[changeIndex].y=rand()%y;





}
#include <iostream>
#include <math.h>
#include <stdlib.h> 
//s#include<conio.h>
using namespace std;


struct nodeelements
{

int x;                  /* x co-ordinate*/
int y;                  /* y co-ordinate*/
int power;              /* Power associated with each of the nodes on the grid*/
int visited ;            /*set 1 to indicate predessor*/
}node;


int main()
{
   int noofNodes=700;
   int noofSources=10;
   int noofDestinations=1; 
   int gridSize=64;
   int powerCapacity=30; 
   int count=0;
   int hop=0;
   int num=0;
   int reached=0;
   float distSnN=0;/*Distance between source and sensor node*/
   float distNnD=0;/*Distance between node and destination*/
   float totalDist=0;/*Distance between source and destination*/
   float distNnN=0;/*Distance between node and node*/
   float totalDist1=0;
   int sensingRange=8;
   int communicationRange=16;
   nodeelements netNode[noofNodes];
   nodeelements netSource[noofSources];
   nodeelements netDestination[noofDestinations];
   nodeelements temp1[50];/*struc to store node in sensing range*/
   nodeelements path[50];/*struc to store nodes in path traversed*/
   cout<<"Nodes(x,y,power)"<<endl;
   for (int NN= 0; NN < noofNodes; NN++)//for generation of nodes
   {
       netNode[NN].x     = rand() % gridSize;
       netNode[NN].y     = rand() % gridSize;
       netNode[NN].power = (rand() % powerCapacity)+1;
       cout <<"("<< netNode[NN].x <<"," << netNode[NN].y <<"," << netNode[NN].power << ")"<<endl;
   }//end for generation of nodes
   cout<<"Sources(x,y,power)"<<endl;
   for (int NS= 0; NS < noofSources; NS++)//for generation of source/event
   {
       netSource[NS].x     = rand() % gridSize;
       netSource[NS].y     = rand() % gridSize;
       netSource[NS].power = (rand() % 3) + 1; 
       cout <<"("<< netSource[NS].x <<"," << netSource[NS].y <<"," << netSource[NS].power <<")"<< endl;
   }//end for generation of source/event
   netDestination[0].x=15;
   netDestination[0].y=15;
   netDestination[0].power=0;   
   for(int NN= 0; NN < noofNodes; NN++)//for setting initial visited value
   {
          netNode[NN].visited=0;     
   } //end for setting initial visited value
   for(int NS= 0; NS < noofSources; NS++)//for each sources 
   {
       int hop=0;
       reached=0;
       count=0;
       num=0;
       totalDist=0;
       totalDist1=0; 
       for(int NN= 0; NN < noofNodes; NN++)//for setting initial visited value
       {
          netNode[NN].visited=0;     
       } //end for setting initial visited value
       for (int NN= 0; NN < noofNodes; NN++)//for each node
       {
          distSnN=sqrt((((netSource[NS].x-netNode[NN].x)*(netSource[NS].x-netNode[NN].x))+((netSource[NS].y-netNode[NN].y)*(netSource[NS].y-netNode[NN].y))));
          if(distSnN<=sensingRange)//if condition for sensing range
          {
                if(netNode[NN].power>=netSource[NS].power)//if check for power
                {
                   // netNode[NN].visited=1;
                    temp1[count].x=netNode[NN].x;
                    temp1[count].y=netNode[NN].y;
                    temp1[count].power=netNode[NN].power; 
                    count++;  
                }//end if check for power         
          }//end if condition for sensing range
        }//end for each node     
        if(count==0)//check if no nodes in sensing range
        {
            cout<<"Not able to sense Source"<<NS<<" by any node"<<endl;
            break;
        }//check if no nodes in sensing range
        num=rand() % count;
        path[hop].x=temp1[num].x;
        path[hop].y=temp1[num].y;
        path[hop].power=temp1[num].power;
        for(int NN= 0; NN < noofNodes; NN++)//for reducing power
        {
            if(netNode[NN].x==path[hop].x && netNode[NN].y==path[hop].y && netNode[NN].power==path[hop].power)
            {
                 netNode[NN].power=netNode[NN].power-netSource[NS].power; 
                 netNode[NN].visited=1;
                 path[hop].power=netNode[NN].power;   
                 totalDist=sqrt((((netSource[NS].x-netNode[NN].x)*(netSource[NS].x-netNode[NN].x))+((netSource[NS].y-netNode[NN].y)*(netSource[NS].y-netNode[NN].y))));  
            }
        } //end for reducing 
        hop++;        
        count=0; 
        distNnD=sqrt((((path[hop-1].x-netDestination[0].x)*(path[hop-1].x-netDestination[0].x))+((path[hop-1].y-netDestination[0].y)*(path[hop-1].y-netDestination[0].y))));  
        if(distNnD<=communicationRange)/*check whether destination reached*/
        {
             cout<<"*************************************************************"<<endl;
             cout<<"Source"<<NS<<" Reached Destination"<<endl;
             path[hop].x=netDestination[0].x;
             path[hop].y=netDestination[0].y;
             path[hop].power=netDestination[0].power;
             hop++;
             totalDist=totalDist+distNnD;
             cout<<"path"<<endl;
             cout<<"("<<netSource[NS].x<<","<<netSource[NS].y<<","<<netSource[NS].power<<")";
             for(int i=0;i<hop;i++)/*display of path nodes*/
             {
                     cout<<"("<<path[i].x<<","<<path[i].y<<","<<path[i].power<<")";    
             }/*end display of path nodes*/
             cout<<endl;
             cout<<"No of hops "<<hop<<endl;
             cout<<"Total distance from source to destination "<<totalDist<<endl;
             //cout<<"*************************************************************"<<endl;
             reached=1;
        }/*end check whether destination reached*/
       while(reached!=1)/*while loop*/
       {
          for(int NN= 0; NN < noofNodes; NN++)/*for which next hop nodes*/
           {
              if(netNode[NN].visited!=1)/*check whether node visited*/
              {
                  distNnN=sqrt((((path[hop-1].x-netNode[NN].x)*(path[hop-1].x-netNode[NN].x))+((path[hop-1].y-netNode[NN].y)*(path[hop-1].y-netNode[NN].y))));  
                  if(distNnN<=communicationRange)/*check communication range betweeen nodes*/
                  {
                      if(netNode[NN].power>=netSource[NS].power)/*check for power*/
                      {
                         //netNode[NN].visited=1;
                         temp1[count].x=netNode[NN].x;
                         temp1[count].y=netNode[NN].y;
                         temp1[count].power=netNode[NN].power; 
                         totalDist1=distNnN;
                         count++;  
                      }//end check for power                      
                  }/*end check communication range betweeen nodes*/
              }/*end check whether node visited*/
           }/*end for which next hop nodes*/
           if(count==0)/*check if no nodes in communication range*/
           {
               cout<<"Not able to find path since node not in communication range"<<NS<<endl;
               break;
           }/*end check if no nodes in communication range*/
           num=rand() % count;
           path[hop].x=temp1[num].x;
           path[hop].y=temp1[num].y;
           path[hop].power=temp1[num].power;
           for(int NN= 0; NN < noofNodes; NN++)//for reducing power
           {
              if(netNode[NN].x==path[hop].x && netNode[NN].y==path[hop].y && netNode[NN].power==path[hop].power)
              {
                 netNode[NN].power=netNode[NN].power-netSource[NS].power;
                 netNode[NN].visited=1; 
                 path[hop].power=netNode[NN].power;   
                 totalDist=totalDist+totalDist1;                
              }
           } //end for reducing power            
           hop++; 
           count=0;
           distNnD=sqrt((((path[hop-1].x-netDestination[0].x)*(path[hop-1].x-netDestination[0].x))+((path[hop-1].y-netDestination[0].y)*(path[hop-1].y-netDestination[0].y))));  
           if(distNnD<=communicationRange)/*check whether reached destination*/
           {
               cout<<"*************************************************************"<<endl;
               cout<<"Source"<<NS<<" Reached Destination"<<endl;
               path[hop].x=netDestination[0].x;
               path[hop].y=netDestination[0].y;
               path[hop].power=netDestination[0].power;
               hop++;
               totalDist=totalDist+distNnD;
               cout<<"path"<<endl;
               cout<<"("<<netSource[NS].x<<","<<netSource[NS].y<<")";
               for(int i=0;i<hop;i++)/*display of path nodes*/
               {
                     cout<<"("<<path[i].x<<","<<path[i].y<<","<<path[i].power<<")";    
               }/*end display of path nodes*/
               cout<<endl;
               cout<<"No of hops for Source"<<NS<<" "<<hop<<endl;
               cout<<"Total distance from source to destination for Source"<<totalDist<<endl;
               reached=1;
               //cout<<"*************************************************************"<<endl;
            }/*end check whether reached destination*/
        }//end while              
    }//end for each source
   //getch();
}//end main

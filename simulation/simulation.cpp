// simulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sensor_node.h"
#include <stdlib.h>     /* srand, rand */
#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
int R=100;
int D=5; //5-70
int T=2; 
int N=5; //5-50
int SEND=0;
sensor_node * sensor_array;
int ** distance_array;
map<int,int> *disable;
void drop()
{
	for(int i=0;i<N;i++)
	{
		sensor_array[i].~sensor_node();
	}
	disable->clear();
	free(distance_array);

}
void ran()
{
	srand (time(NULL));
	R=rand()%100;
	N=rand()%100;
	D=rand()%R;
}
void init()
{
	SEND=0;
	srand (time(NULL));
	sensor_array=new sensor_node[N];
	disable=new map<int,int>();

	distance_array=new int*[N];
	for(int i=0;i<N;i++)
	{
		sensor_array[i].set_id(i);
		int x=rand()%(R+1);
		int y=rand()%(R+1);
		sensor_array[i].set_x(x);
		sensor_array[i].set_y(y);
		sensor_array[i].set_total_node(N);
		distance_array[i]=new int[N];
	}
	for(int i=0;i<N;i++)
	{
		for(int m=0;m<N;m++)
		{
			float distance=(sensor_array[i].get_x()-sensor_array[m].get_x())*(sensor_array[i].get_x()-sensor_array[m].get_x())
				+(sensor_array[i].get_y()-sensor_array[m].get_y())*(sensor_array[i].get_y()-sensor_array[m].get_y());
			if(distance>(D*D))
			{
				distance_array[i][m]=0;
				distance_array[m][i]=0;
			}
			else
			{
				distance_array[i][m]=1;
				distance_array[m][i]=1;
			}
		}
	}
	map<int,int> * neigh=new map<int,int>();
	for(int i=0;i<N;i++)
	{
		//cout<<"node "<<i<<endl;
		neigh->clear();
		for(int z=0;z<N;z++)
		{
			if(distance_array[i][z]==1)
			{
				neigh->insert(pair<int,int>(z,z));
				//cout<<"neighbour "<<i<<endl;
			}
		}
		neigh->erase(i);
		sensor_array[i].set_neighbour(neigh);
	}
}
bool update()
{
	bool result=true;
	disable->clear();
	for(int i=0;i<N;i++)
	{
		if(sensor_array[i].finished())
		{
		}
		else
		{
			result=false;
		}
		
		map<int,int>::iterator it=disable->find(sensor_array[i].get_id());
		if(it!=disable->end())
		{
			//disable
			SEND+=sensor_array[i].unexplored_neightbour->size();
		}
		else
		{
			int z=0;
			while(1)
			{
				int node=sensor_array[i].get_next(z);
				if(node==-1)
					break;
				map<int,int>::iterator itt=disable->find(sensor_array[node].get_id());
				if(itt==disable->end())
				{
					if(distance_array[node][i]==1)
					{
						//cout<<"case 1 "<<i<<" to "<<node<<endl;
						//case 1
						SEND++;
						sensor_array[node].send(i);
						sensor_array[i].send(node);
						disable->insert(pair<int,int>(i,i));
						disable->insert(pair<int,int>(node,node));
						SEND-=sensor_array[node].unexplored_neightbour->size();
						for(int y=0;y<N;y++)
						{
							if(distance_array[i][y]==1)
							{
								disable->insert(pair<int,int>(y,y));
							}
							if(distance_array[node][y]==1)
							{
								disable->insert(pair<int,int>(y,y));
							}
						}
						break;
					}
					else
					{
						//case 2
						
						//cout<<"case 2 "<<i<<" to "<<node<<endl;
						SEND++;
						sensor_array[i].outofrange(node);
						disable->insert(pair<int,int>(i,i));
						for(int y=0;y<N;y++)
						{
							if(distance_array[i][y]==1)
							{
								disable->insert(pair<int,int>(y,y));
							}
						}
						break;
					}
				}
				else
				{
					SEND++;
					z++;
				}
			}
		}
	}
	return result;
}
int _tmain(int argc, _TCHAR* argv[])
{
	ofstream out("D:\output.txt");
	out<<"R\tD\tT\tN\tSEND\tIteration"<<endl;
	for(D=0;D<=100;D+=5)
	{
		cout<<D<<endl;
		for(N=0;N<=70;N+=5)
		{
			cout<<N<<endl;
			int it=0;
			int send=0;
			for(int a=0;a<10;a++)
			{
				//ran();
				//int it=0;
				//int send=0;
				//for(int z=0;z<5;z++)
				{
					Sleep(1000);
					init();
					cout<<N<<endl;
					int i=0;
					while(1)
					{
						if(update())
						{
							break;
						}
						i++;
					}
					it+=i;
					send+=SEND;
					drop();
				}
				
				//out<<R<<"\t"<<D<<"\t"<<T<<"\t"<<N<<"\t"<<(send/5)<<"\t"<<(it/5)<<endl;
				//cout<<R<<"\t"<<D<<"\t"<<T<<"\t"<<N<<"\t"<<(send/5)<<"\t"<<(it/5)<<endl;
			}
			
			out<<R<<"\t"<<D<<"\t"<<T<<"\t"<<N<<"\t"<<(send/10)<<"\t"<<(it/10)<<endl;
			cout<<R<<"\t"<<D<<"\t"<<T<<"\t"<<N<<"\t"<<(send/10)<<"\t"<<(it/10)<<endl;
		}
	}
	
	out.close();
	return 0;
}


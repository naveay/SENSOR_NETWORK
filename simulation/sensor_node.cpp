#include "stdafx.h"
#include "sensor_node.h"

int sensor_node::get_id()
{
	return ID;
}
sensor_node::~sensor_node()
{
	neighbour->erase(neighbour->begin(),neighbour->end());
	true_neighbour->erase(true_neighbour->begin(),true_neighbour->end());
	unexplored_neightbour->erase(unexplored_neightbour->begin(),unexplored_neightbour->end());
}
void sensor_node::set_id(int i)
{
	this->ID=i;
}
void sensor_node::set_total_node(int i)
{
	this->total_node=i;
	neighbour=new map<int,int>();
	true_neighbour=new map<int,int>();
	unexplored_neightbour=new map<int,int>();
	for(int m=0;m<i;m++)
	{
		unexplored_neightbour->insert(pair<int,int>(m,m));
	}
	unexplored_neightbour->erase(ID);
}
bool sensor_node::finished()
{
	if(neighbour->size()==true_neighbour->size()&&unexplored_neightbour->size()==0)
		return true;
	else
		return false;
}
int sensor_node::get_next(int i)
{
	if(unexplored_neightbour->size()>0&&unexplored_neightbour->size()>i)
	{
		map<int,int>::iterator iter=unexplored_neightbour->begin();
		for(int m=0;m<i;m++)
		{
			iter++;
		}
		return iter->first;
	}
	else
		return -1;
}
void sensor_node::send(int i)
{
	unexplored_neightbour->erase(i);
	neighbour->insert(pair<int,int>(i,i));
}
void sensor_node::outofrange(int i)
{
	unexplored_neightbour->erase(i);
}
void sensor_node::set_neighbour(map<int,int> *true_neigh)
{
	map<int,int>::iterator iter=true_neigh->begin();
	for(int m=0;m<true_neigh->size();m++)
	{
		true_neighbour->insert(pair<int,int>(iter->first,iter->second));
		iter++;
	}
}
int sensor_node::get_x()
{
	return x_axis;
}
int sensor_node::get_y()
{
	return y_axis;
}
void sensor_node::set_x(int i)
{
	this->x_axis=i;
}
void sensor_node::set_y(int i)
{
	this->y_axis=i;
}
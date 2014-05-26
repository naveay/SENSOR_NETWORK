#include "map"
using namespace std;
class sensor_node
{
public:
	int ID;
	int x_axis;
	int y_axis;
	int total_node;
	map<int,int> *neighbour;
	map<int,int> *true_neighbour;
	map<int,int> *unexplored_neightbour;
public:
	~sensor_node();
	int get_x();
	int get_y();
	void set_x(int i);
	void set_y(int i);
	int get_id();
	void set_id(int i);
	void set_total_node(int i);  //init
	void set_neighbour(map<int,int> *true_neigh);
	bool finished();
	int get_next(int i);
	void send(int i);
	void outofrange(int i);
};
#include "gamehead.hpp"

///initial the moving direction of the snake

int direct=RIGHT; 

///This is a snake node class
class snake_node{
 
 
public:
	/// x,y,z represent the coordinate of the node
	int x;
	int y;
	int z;

};

///This is a snake class
class snake{
	
private:
	///The vector stores all the boday nodes of the snake
	vector <snake_node> v;
	///This is the body node 
	snake_node sn;
	///This is the Pickachu node
	snake_node fd;
	///This is the Meowth node
	snake_node bug;
	///This records the length of the snake
	int node_count;

public:
	
	 /// default constructor
	snake(){
		
	}
	
	///default destructor 
	~snake(){
		
	}
	
	///Special constructor of the snake
	snake(float x, float y, float z, float x_f, float y_f, float z_f,float x_b, float y_b, float z_b){
		///initial snake has three node, this initial the position of each node
		node_count=1;
		sn.x=x;
		sn.y=y;
		sn.z=z;
		v.push_back(sn);
		
		node_count=node_count+1;
		sn.x=x+2;
		sn.y=y;
		sn.z=z;
		v.push_back(sn);
		
		node_count=node_count+1;
		sn.x=x+4;
		sn.y=y;
		sn.z=z;
		v.push_back(sn);
		
		///initial the position of the Pikachu
		fd.x=x_f;
		fd.y=y_f;
		fd.z=z_f;
		
		///initial the position of the Meowth
		bug.x=x_b;
		bug.y=y_b;
		bug.z=z_b;


	}
	
	///This function reset the position of the snake and the length of the snake back to 3 when the game restart
	void reset_snack(float x, float y, float z){
			int l=node_count;
			snake_node nh;
			

			while(node_count!=3){
				if(node_count>3){
					remove_tail();
					node_count=node_count-1;
				}
				else{
					nh.x=x;
					nh.y=y;
					nh.z=z;
					add_head(nh);
					node_count=node_count+1;
				}
				
			}
			
			int i=0;
			vector <snake_node>::iterator it;
			 for(it=v.begin();it!=v.end();++it){
				 it[0].x=x+2*i;
				 it[0].y=y;
				 it[0].z=z;
				 i=i+1;			 
			}
	
	}
	
	///This function return the length of the snake
	int get_length(){
		return node_count;
		
	}
	
	///This function return any nodes of the snake body
	snake_node get_node(int id){
		vector <snake_node>::iterator it;
		snake_node snode;
		it=v.begin()+id;
		snode.x=it[0].x;
		snode.y=it[0].y;
		snode.z=it[0].z;
		
		return snode;
		
	}
	
	///This function return the Pikachu
	snake_node get_food(){
		return fd;		
	}
	
	///This function return the Meowth
	snake_node get_bug(){

		return bug;
	}
	
	///This function add the node at the head of the snake
	void add_head(snake_node sn){
		v.insert(v.begin(),sn);
	}
	
	///This function remove one node of the snake body on the tail
	void remove_tail(){
			v.pop_back();
	}
	
	///This function control the movee of the snake
	int step(int go_dir){
		snake_node head;
		snake_node new_head;
		int x_next;
		int y_next;
		int z_next;
		head=get_node(0);
		
		///This calculate the position of the new snake head
		if ((direct + go_dir) != 0){
			direct = go_dir;
			x_next=head.x+(direct%10)*STEP_SIZE;
			y_next=head.y;
			z_next=head.z+(direct/10)*STEP_SIZE;
			new_head.x=x_next;
			new_head.y=y_next;
			new_head.z=z_next;
			///If the snake head touch the Pikachu is_eat() will return true
			if(is_eat()){
				///when the snake touch the Pikachu, the snake will add one node to its body and a new Pikachu will be generated at a new position
				add_head(new_head);
				node_count=node_count+1;
				new_food();
				
				///If the snake touch the boundary of the field, the tree, the house and the car is_dead() will return true and the step() will return 1
				if(is_dead()){
					return 1;
				}
				
				
			}
			else{
				///if the snake touch the Meowth, one body node will be removed and a new Meowth will be generated at a new position and if the lenght of the snake become 0 the step() will return a 1
				if(is_reduce()){
					add_head(new_head);
					remove_tail();
					node_count=node_count-1;
					if(node_count!=0){
						remove_tail();
						new_bug();
					}
					else{
						cout << "No body" <<endl;						
						return 1;
					}

				}
				else{
					///If everything is fine, the snake will move forward to the direction by adding a new head and remove its tail
					add_head(new_head);
					remove_tail();
				}
				
				if(is_dead()){
					return 1;
				}
				
			}
			
		}
		
		return 0;
	
	}
	
	
	///This function is used to judge wether a point is inside the scope of the snake body
	bool snake_contain(float x, float z){
		vector <snake_node>::iterator it;
		for(it=v.begin();it!=v.end();++it){
			if(fabs(it[0].x-x)<4&&fabs(it[0].z-z)<4){
				return true;
			}
				 
		}
		return false;
	}
	
	///This function is used to judge whether the snake head has touch the Pikachu
	bool is_eat(){
		snake_node tmp_head, tmp_food;
		tmp_head=get_node(0);
		tmp_food=get_food();
		return fabs(tmp_head.x-tmp_food.x)<4&&fabs(tmp_head.z-tmp_food.z)<4;
		
	}

	///This function is used to judge whether the snake head has touch the Meowth
	bool is_reduce(){
		snake_node tmp_head, tmp_bug;
		tmp_head=get_node(0);
		tmp_bug=get_bug();
		return fabs(tmp_head.x-tmp_bug.x)<4&&fabs(tmp_head.z-tmp_bug.z)<4;


	}
	
	///This function is used to judge whether the snake head has touch its own body, the boundary of the field , the house, the tree or the car
	bool is_dead(){
		snake_node head;
		head=get_node(0);
				
		///Judge whether the snake has touched itself
		vector <snake_node>::iterator it;
		for(it=v.begin()+1;it!=v.end();++it){
				if(head.x==it[0].x && head.z==it[0].z){
						return true;
				}
		}
		
		float up_x=FLOOR_WIDTH/2;
		float up_z=FLOOR_HEIGHT/2;
		int node_width=NODE_WIDTH/2;
		
		
		///Judge whether the snake has touched the wall
		if(head.x < (-up_x+node_width)|| head.x>(up_x-node_width) || head.z>(up_z-node_width)|| head.z<(-up_z+node_width)){
				cout<<"wall"<<endl;
				return true;
		}
		
		///Judge whether the snake has touched the house
		//obstacles house1
		if(head.x < -25 && head.x > -35 && head.z < -30 && head.z > -40){
			cout<<"house1"<<endl;
			return true;
		}

		//obstacles house2
		if(head.x < -4 && head.x > -16 && head.z < -5 && head.z > -15){
			cout<<"house2"<<endl;
			return true;
		}

		//obstacles house3
		if(head.x < 34 && head.x > 26 && head.z < 20 && head.z > 10){
			cout<<"house3"<<endl;
			return true;
		}

		//obstacles house4
		if(head.x < 5 && head.x > -5 && head.z < 25 && head.z > 15){
			cout<<"house4"<<endl;
			return true;
		}

		//obstacles house5
		if(head.x < -25 && head.x > -35 && head.z < 41 && head.z > 29){
			cout<<"house5"<<endl;
			return true;
		}

		//obstacles house6
		if(head.x < 9 && head.x > 1 && head.z < -30 && head.z > -40){
			cout<<"house6"<<endl;
			return true;
		}
		
		///Judge whether the snake has touched the tree
		//obstacles tree1
		if(head.x < -38 && head.x > -42 && head.z < -3 && head.z > -7){
			cout<<"tree1"<<endl;
			return true;
		}

		//obstacles tree3
		if(head.x < -3 && head.x > -7 && head.z < 42 && head.z > 38){
			cout<<"tree3"<<endl;
			return true;
		}

		//obstacles tree4
		if(head.x < -13 && head.x > -17 && head.z < 22 && head.z > 18){
			cout<<"tree4"<<endl;
			return true;
		}

		//obstacles tree5
		if(head.x < 13 && head.x > 7 && head.z < -17 && head.z > -23){
			cout<<"tree5"<<endl;
			return true;
		}

		//obstacles tree6
		if(head.x < 43 && head.x > 37 && head.z < -7 && head.z > -13){
			cout<<"tree6"<<endl;
			return true;
		}

		//obstacles tree7
		if(head.x < 33 && head.x > 27 && head.z < 38 && head.z > 32){
			cout<<"tree7"<<endl;
			return true;
		}

		//obstacles tree8
		if(head.x < 8 && head.x > 2 && head.z < 8 && head.z > 2){
			cout<<"tree8"<<endl;
			return true;
		}
		
		///Judge whether the snake has touched the car
		//obstacles car1
		if(head.x < 22 && head.x > 18 && head.z < -17 && head.z > -23){
			cout<<"car1"<<endl;
			return true;
		}

		return false;
		
	}
	
	
	///This function print the coordinates of the node of the snake
	void printall(){
			vector <snake_node>::iterator it;
			 for(it=v.begin();it!=v.end();++it){
				 cout<<"x="<<it[0].x<<" y="<<it[0].y<<" z="<<it[0].z<<endl;
			}
			
	}
	
	///This function genrate a new Pikachu at a new position
	void new_food(){
		int width=FLOOR_WIDTH;
		int height=FLOOR_HEIGHT;
		int node_width=NODE_WIDTH;
		float aix_x=FLOOR_WIDTH/2;
		float aix_z=FLOOR_HEIGHT/2;
		float x_tmp=rand()%width-aix_x;
		float z_tmp=rand()%height-aix_z;
		while (snake_contain(x_tmp, z_tmp) || (x_tmp==bug.x && z_tmp==bug.z )
			||x_tmp < (-aix_x+node_width)||x_tmp>(aix_x-node_width)
			|| z_tmp>(aix_z-node_width)||z_tmp<(-aix_z+node_width)
			||(x_tmp < -23 && x_tmp > -37 && z_tmp < -28 && z_tmp > -42)
			||(x_tmp < -2 && x_tmp > -18 && z_tmp < -3 && z_tmp > -17)
			||(x_tmp < 32 && x_tmp > 24 && z_tmp < 22 && z_tmp > 8)
			||(x_tmp < 7 && x_tmp > -7 && z_tmp < 27 && z_tmp > 13)
			||(x_tmp < -23 && x_tmp > -37 && z_tmp < 43 && z_tmp > 27)
			||(x_tmp < 11 && x_tmp > -1 && z_tmp < -28 && z_tmp > -42)
			||(x_tmp < -36 && x_tmp > -44 && z_tmp < -1 && z_tmp > -9)
			||(x_tmp < -1 && x_tmp > -9 && z_tmp < 44 && z_tmp > 36)
			||(x_tmp < -11 && x_tmp > -19 && z_tmp < 24 && z_tmp > 16)
			||(x_tmp < 14 && x_tmp > 6 && z_tmp < -16 && z_tmp > -24)
			||(x_tmp < 44 && x_tmp > 36 && z_tmp < -6 && z_tmp > -14)
			||(x_tmp < 34 && x_tmp > 26 && z_tmp < 39 && z_tmp > 31)
			||(x_tmp < 9 && x_tmp > 1 && z_tmp < 9 && z_tmp > 1)
			||(x_tmp < 24 && x_tmp > 16 && z_tmp < -15 && z_tmp > -25)){
		
				
			x_tmp=rand()%width-aix_x;
			z_tmp=rand()%height-aix_z;
		}

		fd.x=x_tmp;
		fd.z=z_tmp;
		
	}
	
	///This function genrate a new Meowth at a new position
	void new_bug(){
		int width=FLOOR_WIDTH;
		int height=FLOOR_HEIGHT;
		int node_width=NODE_WIDTH;
		float aix_x=FLOOR_WIDTH/2;
		float aix_z=FLOOR_HEIGHT/2;
		float x_tmp=rand()%width-aix_x;
		float z_tmp=rand()%height-aix_z;
		while (snake_contain(x_tmp, z_tmp)||(x_tmp==fd.x && z_tmp==fd.z )
			|| x_tmp < (-aix_x+node_width)||x_tmp>(aix_x-node_width)
			|| z_tmp>(aix_z-node_width)||z_tmp<(-aix_z+node_width)
			||(x_tmp < -23 && x_tmp > -37 && z_tmp < -28 && z_tmp > -42)
			||(x_tmp < -2 && x_tmp > -18 && z_tmp < -3 && z_tmp > -17)
			||(x_tmp < 32 && x_tmp > 24 && z_tmp < 22 && z_tmp > 8)
			||(x_tmp < 7 && x_tmp > -7 && z_tmp < 27 && z_tmp > 13)
			||(x_tmp < -23 && x_tmp > -37 && z_tmp < 43 && z_tmp > 27)
			||(x_tmp < 11 && x_tmp > -1 && z_tmp < -28 && z_tmp > -42)
			||(x_tmp < -36 && x_tmp > -44 && z_tmp < -1 && z_tmp > -9)
			||(x_tmp < -1 && x_tmp > -9 && z_tmp < 44 && z_tmp > 36)
			||(x_tmp < -11 && x_tmp > -19 && z_tmp < 24 && z_tmp > 16)
			||(x_tmp < 14 && x_tmp > 6 && z_tmp < -16 && z_tmp > -24)
			||(x_tmp < 44 && x_tmp > 36 && z_tmp < -6 && z_tmp > -14)
			||(x_tmp < 34 && x_tmp > 26 && z_tmp < 39 && z_tmp > 31)
			||(x_tmp < 9 && x_tmp > 1 && z_tmp < 9 && z_tmp > 1)
			||(x_tmp < 24 && x_tmp > 16 && z_tmp < -15 && z_tmp > -25)){
			x_tmp=rand()%width-aix_x;
			z_tmp=rand()%height-aix_z;
		}
		bug.x=x_tmp;
		bug.z=z_tmp;
		
	}
	
};

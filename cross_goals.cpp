#include <queue>
#include <vector>
using namespace std;


bool check_cross_goals(Cube frontier_state, Cube goal_state){
    for(int i = 0; i<dim48; i++){
        if(goal_state.colors[i] != '0' && (frontier_state.colors[i] != goal_state.colors[i])){
            return false;
        }
    }

    return true;
}

vector<string> cross_BDF(Cube starting_state, Cube goal){
	queue<Cube> frontier;
	vector<string> moves;

	starting_state.add_move("0");
	frontier.push(starting_state);
	int n_cicles = 0;
	bool goal_found = false;

	while(goal_found == false){
		
		n_cicles++;
		//cout<<n_cicles<<"\n";

		if(check_cross_goals(frontier.front(), goal) == true){ //checking if the node is the goal state
			goal_found = true;

			for(int i =0; i<frontier.front().moves.size(); i++){
				moves.insert(moves.begin(), frontier.front().moves[i]);
			}

			frontier = {};

			return moves;
		}
		else{
			if(frontier.front().moves.size() < 5){ //setting a max depth of 4 moves (if a node has already been permuted 4 times it doens't do  it further)
                frontier.front().return_possible_states(&frontier);//checking for the new possible states(deleting the one already seen)    
            }
			
            frontier.pop(); //deleting new node from the frontier
		}
	}

	return {"0"};
}


vector<string> white_cross_search(Cube start_state){
    const int xy = 0;

    Cube appoggio_cube(start_state);

    appoggio_cube.moves = {};

    char g1[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'w', '0'};
    Cube goal_cross_1;
    goal_cross_1.add_colors(g1);

    vector<string> moves_g1 = cross_BDF(appoggio_cube, goal_cross_1);
    appoggio_cube = appoggio_cube.scramble_cube(moves_g1);

    if(check_cross_goals(appoggio_cube, goal_cross_1) == false){
        cout<<"White cross 1"<<endl;
        throw 10;
    }

    

    //cout<<"moves goal 1 found"<<endl;
    //cout<<endl; //max 4 moves so 50 000 max n nodes



    appoggio_cube.moves = {};

    char g2[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'w', '0', 'w', '0'};
    Cube goal_cross_2;
    goal_cross_2.add_colors(g2);

    vector<string> moves_g2 = cross_BDF(appoggio_cube, goal_cross_2);
    appoggio_cube = appoggio_cube.scramble_cube(moves_g2);

    if(check_cross_goals(appoggio_cube, goal_cross_2) == false){
        cout<<"White cross 2"<<endl;
        throw 20;
    }

    //cout<<"moves goal 2 found"<<endl;
    //cout<<endl; //max 4 moves as well




    appoggio_cube.moves = {};

   
    char g_3[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', '0', 'w', '0', 'w', '0'};
    Cube goal_cross_3;
    goal_cross_3.add_colors(g_3);

    vector<string> moves_g3 = cross_BDF(appoggio_cube, goal_cross_3);
    appoggio_cube = appoggio_cube.scramble_cube(moves_g3);

    if(check_cross_goals(appoggio_cube, goal_cross_3) == false){
        cout<<"White cross partial goal 3"<<endl;
        throw 31;
    }

    //cout<<"set up moves goal 3 found"<<endl;


    
    appoggio_cube.moves = {};
    
    char g_4[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', '0', '0', '0', '0', '0', '0', '0', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};
    Cube goal_cross_4;
    goal_cross_4.add_colors(g_4);
    

    vector<string> moves_g4 = cross_BDF(appoggio_cube, goal_cross_4);
    appoggio_cube = appoggio_cube.scramble_cube(moves_g4);

    if(check_cross_goals(appoggio_cube, goal_cross_4) == false){
        cout<<"White cross partial goal 3"<<endl;
        throw 41;
    }
   
    //cout<<"set up moves goal 4 found"<<endl;


    vector<string> moves_cross;
    moves_cross.insert(moves_cross.end(), moves_g1.begin(), moves_g1.end());
    moves_cross.insert(moves_cross.end(), moves_g2.begin(), moves_g2.end());
    moves_cross.insert(moves_cross.end(), moves_g3.begin(), moves_g3.end());
    moves_cross.insert(moves_cross.end(), moves_g4.begin(), moves_g4.end());

    return moves_cross;

}


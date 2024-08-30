class Cubie{
    public:

    char colors[dim3];
    int position; //indicates the position that the cubie has in the solved state

    Cubie& operator=(const Cubie& copy){
        for(int i = 0; i<dim3; i++){
            this->colors[i] = copy.colors[i];
        }

        this->position = copy.position;

        return *this;
    }

    void insert_colors(char c1, char c2, char c3){
        this->colors[0] = c1;
        this->colors[1] = c2;
        this->colors[2] = c3;
    }

    void insert_position(int pos){
        this->position = pos;
    }

    void intialize_cubie(char c1, char c2, char c3, int pos){
        this->insert_colors(c1, c2, c3);
        this->insert_position(pos);
    }

    
};

int return_position(char c1, char c2, char c3){

    if(c1 == '0' && c2=='0' && c3=='0'){ //if the corner or edge is not relevant, i just put position = 99, so that it can be ignored during the goal BDF
        return 99;
    }
        
    if(c3 == '0'){ //edge
        if(c1 == 'y' || c2 == 'y'){ //from 0 to 3
            if(c1 == 'o' || c2 == 'o'){
                return 0;
            }
            else if(c1 == 'g' || c2 == 'g'){
                return 1;
            }
            else if(c1 == 'r' || c2 == 'r'){
                return 2;
            }
            else if(c1 == 'b' || c2 == 'b'){
                return 3;
            }
            else{
                cout<<"Errore return_position 1";
                throw 701;
            }
        }
        else if(c1 == 'w' || c2 == 'w'){ //from 8 to 11
            if(c1 == 'o' || c2 == 'o'){
                return 8;
            }
            else if(c1 == 'g' || c2 == 'g'){
                return 9;
            }
            else if(c1 == 'r' || c2 == 'r'){
                return 10;
            }
            else if(c1 == 'b' || c2 == 'b'){
                return 11;
            }
            else{
                cout<<"Errore return_position 2";
                throw 702;
            }
        }
        else{ // from 4 to 7
            if(c1 == 'r' || c2 == 'r'){
                if(c1 == 'g' || c2 == 'g'){
                    return 6;
                }
                else{ //blue
                    return 7;
                }
            }
            else if(c1 == 'o' || c2 == 'o'){
                if(c1 == 'g' || c2 == 'g'){
                    return 5;
                }
                else{ //blue
                    return 4;
                }
            }
            else{
                cout<<"Errore return_position 3";
                throw 703;
            }   
        }
    }


    else{ //corner
        if(c1 == 'y' || c2 == 'y' || c3 == 'y'){
            if(c1 == 'o' || c2 == 'o' || c3 == 'o'){
                if(c1 == 'b' || c2 == 'b' || c3 == 'b'){
                    return 0;
                }
                else{ //green
                    return 1;
                }
            }
            else  if(c1 == 'r' || c2 == 'r' || c3 == 'r'){
                if(c1 == 'b' || c2 == 'b' || c3 == 'b'){
                    return 3;
                }
                else{ //green
                    return 2;
                }
            }
            else{
                cout<<"Erroe return_position 5";
                throw 705;
            }
        }
        else if(c1 == 'w' || c2 == 'w' || c3 == 'w'){
            if(c1 == 'o' || c2 == 'o' || c3 == 'o'){
                if(c1 == 'b' || c2 == 'b' || c3 == 'b'){
                    return 4;
                }
                else{ //green
                    return 5;
                }
            }
            else  if(c1 == 'r' || c2 == 'r' || c3 == 'r'){
                if(c1 == 'b' || c2 == 'b' || c3 == 'b'){
                    return 7;
                }
                else{ //green
                    return 6;
                }
            }
            else{
                cout<<"Errore return_position 6";
                throw 706;
            }
        }
        else{
            cout<<"Errore return_position 4";
            throw 704;
        }
    }
    return -1;
}

class F2L{
    public:

    Cubie corners[dim8];
    Cubie edges[dim12];

    vector<string> moves;

    F2L(){}

    F2L(const F2L& copy){
        for(int i = 0; i<dim12; i++){
            this->edges[i] = copy.edges[i];
        }

        for(int i = 0; i<dim8; i++){
            this->corners[i] = copy.corners[i];
        }

        for(int i = 0; i < copy.moves.size(); i++){
		    moves.insert(moves.begin() + i, copy.moves[i]);
	    }
    }

    void add_move(string move){
        moves.insert(moves.begin(), move);
    }

    void erase_moves(){
        this->moves = {};
    }

    void initialize_F2L(){
        this->corners[0].intialize_cubie('o', 'b', 'y', 0);
        this->corners[1].intialize_cubie('o', 'g', 'y', 1);
        this->corners[2].intialize_cubie('r', 'g', 'y', 2);
        this->corners[3].intialize_cubie('r', 'b', 'y', 3);
        this->corners[4].intialize_cubie('o', 'b', 'w', 4);
        this->corners[5].intialize_cubie('o', 'g', 'w', 5);
        this->corners[6].intialize_cubie('r', 'b', 'w', 6);
        this->corners[7].intialize_cubie('r', 'g', 'w', 7);
        
        this->edges[0].intialize_cubie('o', 'y', '0', 0);
        this->edges[1].intialize_cubie('o', 'g', '0', 1);
        this->edges[2].intialize_cubie('o', 'r', '0', 2);
        this->edges[3].intialize_cubie('o', 'b', '0', 3);
        this->edges[4].intialize_cubie('o', 'b', '0', 4);
        this->edges[5].intialize_cubie('o', 'g', '0', 5);
        this->edges[6].intialize_cubie('r', 'g', '0', 6);
        this->edges[7].intialize_cubie('r', 'b', '0', 7);
        this->edges[8].intialize_cubie('o', 'w', '0', 8);
        this->edges[9].intialize_cubie('g', 'w', '0', 9);
        this->edges[10].intialize_cubie('r', 'w', '0', 10);
        this->edges[11].intialize_cubie('b', 'w', '0', 11);

        moves = {};
    }

    void conversion_cube_F2L(Cube cube){
        this->corners[0].intialize_cubie(cube.colors[0], cube.colors[34], cube.colors[24], return_position(cube.colors[0], cube.colors[34], cube.colors[24]));
        this->corners[1].intialize_cubie(cube.colors[2], cube.colors[18], cube.colors[32], return_position(cube.colors[2], cube.colors[18], cube.colors[32]));
        this->corners[2].intialize_cubie(cube.colors[7], cube.colors[10], cube.colors[16], return_position(cube.colors[7], cube.colors[10], cube.colors[16]));
        this->corners[3].intialize_cubie(cube.colors[5], cube.colors[8], cube.colors[26], return_position(cube.colors[5], cube.colors[8], cube.colors[26]));
        this->corners[4].intialize_cubie(cube.colors[39], cube.colors[29], cube.colors[42], return_position(cube.colors[39], cube.colors[29], cube.colors[42]));
        this->corners[5].intialize_cubie(cube.colors[37], cube.colors[40], cube.colors[23], return_position(cube.colors[37], cube.colors[40], cube.colors[23]));
        this->corners[6].intialize_cubie(cube.colors[15], cube.colors[21], cube.colors[45], return_position(cube.colors[15], cube.colors[21], cube.colors[45]));
        this->corners[7].intialize_cubie(cube.colors[13], cube.colors[31], cube.colors[47], return_position(cube.colors[13], cube.colors[31], cube.colors[47]));
        
        this->edges[0].intialize_cubie(cube.colors[1], cube.colors[33], '0', return_position(cube.colors[1], cube.colors[33], '0'));
        this->edges[1].intialize_cubie(cube.colors[4], cube.colors[17], '0', return_position(cube.colors[4], cube.colors[17], '0'));
        this->edges[2].intialize_cubie(cube.colors[6], cube.colors[9], '0', return_position(cube.colors[6], cube.colors[9], '0'));
        this->edges[3].intialize_cubie(cube.colors[3], cube.colors[25], '0', return_position(cube.colors[3], cube.colors[25], '0'));
        this->edges[4].intialize_cubie(cube.colors[36], cube.colors[27], '0', return_position(cube.colors[36], cube.colors[27], '0'));
        this->edges[5].intialize_cubie(cube.colors[35], cube.colors[20], '0', return_position(cube.colors[35], cube.colors[20], '0'));
        this->edges[6].intialize_cubie(cube.colors[12], cube.colors[19], '0', return_position(cube.colors[12], cube.colors[19], '0'));
        this->edges[7].intialize_cubie(cube.colors[11], cube.colors[28], '0', return_position(cube.colors[11], cube.colors[28], '0'));
        this->edges[8].intialize_cubie(cube.colors[38], cube.colors[41], '0', return_position(cube.colors[38], cube.colors[41], '0'));
        this->edges[9].intialize_cubie(cube.colors[43], cube.colors[22], '0', return_position(cube.colors[43], cube.colors[22], '0'));
        this->edges[10].intialize_cubie(cube.colors[14], cube.colors[46], '0', return_position(cube.colors[14], cube.colors[46], '0'));
        this->edges[11].intialize_cubie(cube.colors[30], cube.colors[44], '0', return_position(cube.colors[30], cube.colors[44], '0'));
    }

    void conversion_array_F2L(char colors[]){
        this->corners[0].intialize_cubie(colors[0], colors[34], colors[24], return_position(colors[0], colors[34], colors[24]));
        this->corners[1].intialize_cubie(colors[2], colors[18], colors[32], return_position(colors[2], colors[18], colors[32]));
        this->corners[2].intialize_cubie(colors[7], colors[10], colors[16], return_position(colors[7], colors[10], colors[16]));
        this->corners[3].intialize_cubie(colors[5], colors[8], colors[26], return_position(colors[5], colors[8], colors[26]));
        this->corners[4].intialize_cubie(colors[39], colors[29], colors[42], return_position(colors[39], colors[29], colors[42]));
        this->corners[5].intialize_cubie(colors[37], colors[40], colors[23], return_position(colors[37], colors[40], colors[23]));
        this->corners[6].intialize_cubie(colors[15], colors[21], colors[45], return_position(colors[15], colors[21], colors[45]));
        this->corners[7].intialize_cubie(colors[13], colors[31], colors[47], return_position(colors[13], colors[31], colors[47]));

        this->edges[0].intialize_cubie(colors[1], colors[33], '0', return_position(colors[1], colors[33], '0'));
        this->edges[1].intialize_cubie(colors[4], colors[17], '0', return_position(colors[4], colors[17], '0'));
        this->edges[2].intialize_cubie(colors[6], colors[9], '0', return_position(colors[6], colors[9], '0'));
        this->edges[3].intialize_cubie(colors[3], colors[25], '0', return_position(colors[3], colors[25], '0'));
        this->edges[4].intialize_cubie(colors[36], colors[27], '0', return_position(colors[36], colors[27], '0'));
        this->edges[5].intialize_cubie(colors[35], colors[20], '0', return_position(colors[35], colors[20], '0'));
        this->edges[6].intialize_cubie(colors[12], colors[19], '0', return_position(colors[12], colors[19], '0'));
        this->edges[7].intialize_cubie(colors[11], colors[28], '0', return_position(colors[11], colors[28], '0'));
        this->edges[8].intialize_cubie(colors[38], colors[41], '0', return_position(colors[38], colors[41], '0'));
        this->edges[9].intialize_cubie(colors[43], colors[22], '0', return_position(colors[43], colors[22], '0'));
        this->edges[10].intialize_cubie(colors[14], colors[46], '0', return_position(colors[14], colors[46], '0'));
        this->edges[11].intialize_cubie(colors[30], colors[44], '0', return_position(colors[30], colors[44], '0'));
    
    }

    void move_edges(int i1, int i2, int i3, int i4){
        Cubie appo = this->edges[i1];
        this->edges[i1] = this->edges[i2];
        this->edges[i2] = this->edges[i3];
        this->edges[i3] = this->edges[i4];
        this->edges[i4] = appo;
    }

    void move_corners(int i1, int i2, int i3, int i4){
        Cubie appo = this->corners[i1];
        this->corners[i1] = this->corners[i2];
        this->corners[i2] = this->corners[i3];
        this->corners[i3] = this->corners[i4];
        this->corners[i4] = appo;
    }

    void move_edges_2(int i1, int i2, int i3, int i4){
        Cubie appo = this->edges[i1];
        this->edges[i1] = this->edges[i3];
        this->edges[i3] = appo;

        appo = this->edges[i2];
        this->edges[i2] = this->edges[i4];
        this->edges[i4] = appo;
    }

    void move_corners_2(int i1, int i2, int i3, int i4){
        Cubie appo = this->corners[i1];
        this->corners[i1] = this->corners[i3];
        this->corners[i3] = appo;

        appo = this->corners[i2];
        this->corners[i2] = this->corners[i4];
        this->corners[i4] = appo;
    }

    F2L r(){ //problme here
        F2L return_cube(*this);

        return_cube.move_corners(2, 1, 5, 6);
        return_cube.move_edges(6, 1, 5, 9);

        return return_cube;
    }
	F2L R(){
        F2L return_cube(*this);

        return_cube.move_corners(6, 5, 1, 2);
        return_cube.move_edges(9, 5, 1, 6);

        return return_cube;
    }
	F2L l(){
        F2L return_cube(*this);

        return_cube.move_corners(0, 3, 7, 4);
        return_cube.move_edges(3, 7, 11, 4);

        return return_cube;
    }
	F2L L(){
        F2L return_cube(*this);

        return_cube.move_corners(4, 7, 3, 0);
        return_cube.move_edges(4, 11, 7, 3);

        return return_cube;
    }
	F2L u(){
        F2L return_cube(*this);

        return_cube.move_corners(0, 1, 2, 3);
        return_cube.move_edges(0, 1, 2, 3);

        return return_cube;
    }
	F2L U(){
        F2L return_cube(*this);

        return_cube.move_corners(3, 2, 1, 0);
        return_cube.move_edges(3, 2, 1, 0);

        return return_cube;
    }
	F2L d(){
        F2L return_cube(*this);

        return_cube.move_corners(7, 6, 5, 4);
        return_cube.move_edges(11, 10, 9, 8);

        return return_cube;
    }
	F2L D(){
        F2L return_cube(*this);

        return_cube.move_corners(4, 5, 6, 7);
        return_cube.move_edges(8, 9, 10, 11);

        return return_cube;
    }
	F2L f(){
        F2L return_cube(*this);

        return_cube.move_corners(3, 2, 6, 7);
        return_cube.move_edges(2, 6, 10, 7);

        return return_cube;
    }
	F2L F(){
        F2L return_cube(*this);

        return_cube.move_corners(7, 6, 2, 3);
        return_cube.move_edges(7, 10, 6, 2);

        return return_cube;
    }
	F2L b(){
        F2L return_cube(*this);

        return_cube.move_corners(1, 0, 4, 5);
        return_cube.move_edges(5, 0, 4, 8);

        return return_cube;
    }
	F2L B(){
        F2L return_cube(*this);

        return_cube.move_corners(5, 4, 0, 1);
        return_cube.move_edges(8, 4, 0, 5);

        return return_cube;
    }


	F2L R2(){
        F2L return_cube(*this);

        return_cube.move_corners_2(2, 1, 5, 6);
        return_cube.move_edges_2(6, 1, 5, 9);

        return return_cube;
    }
	F2L L2(){
        F2L return_cube(*this);

        return_cube.move_corners_2(0, 3, 7, 4);
        return_cube.move_edges_2(3, 7, 11, 4);

        return return_cube;
    }
	F2L U2(){
        F2L return_cube(*this);

        return_cube.move_corners_2(0, 1, 2, 3);
        return_cube.move_edges_2(0, 1, 2, 3);

        return return_cube;
    }
	F2L D2(){
        F2L return_cube(*this);

        return_cube.move_corners_2(7, 6, 5, 4);
        return_cube.move_edges_2(11, 10, 9, 8);

        return return_cube;
    }
	F2L F2(){
        F2L return_cube(*this);

        return_cube.move_corners_2(3, 2, 6, 7);
        return_cube.move_edges_2(2, 6, 10, 7);
        
        return return_cube;
    }
	F2L B2(){
        F2L return_cube(*this);

        return_cube.move_corners_2(1, 0, 4, 5);
        return_cube.move_edges_2(5, 0, 4, 8);

        return return_cube;
    }

    F2L execute_move(string move){
        if(move == "R"){
            return this->R();
        }
        else if(move == "r"){
            return this->r();
        }
        else if(move == "L"){
            return this->L();
        }
        else if(move == "l"){
            return this->l();
        }
        else if(move == "B"){
            return this->B();
        }
        else if(move == "b"){
            return this->b();
        }
        else if(move == "F"){
            return this->F();
        }
        else if(move == "f"){
            return this->f();
        }
        else if(move == "U"){
            return this->U();
        }
        else if(move == "u"){
            return this->u();
        }
        else if(move == "D"){
            return this->D();
        }
        else if(move == "d"){
            return this->d();
        }
        else if(move == "2R"){
            return this->R2();
        }
        else if(move == "2L"){
            return this->L2();
        }
        else if(move == "2B"){
            return this->B2();
        }
        else if(move == "2F"){
            return this->F2();
        }
        else if(move == "2U"){
            return this->U2();
        }
        else if(move == "2D"){
            return this->D2();
        }
        else if(move == "0"){
            return *this;
        }
        else{
            cout<<"Errore execute moves"<<endl;
            return *this;
        }
    }

    void scramble_f2l(vector<string> moves){
        for(int i = 0; i<moves.size(); i++){
            *this = this->execute_move(moves[i]);
        }
    }

    void change_some_position_corner(int final_position, int position_to_move_to){
        int current_pos;

        for(int i =0; i<dim8; i++){
            if(this->corners[i].position == final_position){
                current_pos = i;
            }
        }

        Cubie appo = this->corners[current_pos];

        this->corners[current_pos] = this->corners[position_to_move_to];
        this->corners[position_to_move_to] = appo;
    }

    void change_some_position_edge(int final_position, int position_to_move_to){
        int current_pos;

        for(int i =0; i<dim12; i++){
            if(this->edges[i].position == final_position){
                current_pos = i;
            }
        }

        Cubie appo = this->edges[current_pos];

        this->edges[current_pos] = this->edges[position_to_move_to];
        this->edges[position_to_move_to] = appo;
    }


    bool is_goal_found(F2L goal /*this is the goal with color = 0 for parts that are different*/){ //probably problm here or in moves functions, but most likey with this function
        for(int i = 0; i<dim8; i++){
            if(goal.corners[i].position != 99){
                if(goal.corners[i].position != this->corners[i].position){
                    return false;
                }
            }
        }

        for(int i = 0; i<dim12; i++){
            if(goal.edges[i].position != 99){
                if(goal.edges[i].position != this->edges[i].position){
                    return false;
                }
            }
        }

        return true;
    }

    bool check_some_positions(vector<int> positions_to_check_corners, vector<int> positions_to_check_edges, F2L f2l){
        for(int i = 0; i<positions_to_check_corners.size(); i++){
            if(this->corners[positions_to_check_corners[i]].position != f2l.corners[positions_to_check_corners[i]].position){
                return false;
            }
        }

        for(int i = 0; i<positions_to_check_edges.size(); i++){
            if(this->edges[positions_to_check_edges[i]].position != f2l.edges[positions_to_check_edges[i]].position){
                return false;
            }
        }

        return true;
    }


    void return_states(queue<F2L>* frontier){
        F2L appoggio_cube;

        for(int i = 0; i < dim18; i++){
            if(all_moves[i] != return_opposite_move(this->moves[0]) && all_moves[i] != this->moves[0] && all_moves[i] != return_double_move(this->moves[0])){
                appoggio_cube = this->execute_move(all_moves[i]);
                appoggio_cube.add_move(all_moves[i]);

                frontier->push(appoggio_cube);
            }
        }
    }
};

F2L BDF_f2l(F2L start_state, F2L goal_state){
    queue<F2L> frontier;

    start_state.add_move("0");
    frontier.push(start_state);

    int n_cicles = 0;
    bool goal_found = false;

    while(goal_found == false){
            
        n_cicles++;
        //cout<<n_cicles<<"\n";

        if(frontier.front().is_goal_found(goal_state) == true){ //checking if the node is the goal state
            goal_found = true;
            return frontier.front();
        }
        else{
            frontier.front().return_states(&frontier);//checking for the new possible states(deleting the one already seen)

            frontier.pop(); //deleting new node from the frontier
        }
    }

    return start_state;
}

F2L BDF_f2l_multiple_goals(F2L start_state, F2L goal_state_1, F2L goal_state_2, F2L goal_state_3, F2L goal_state_4, F2L goal_state_5){
    queue<F2L> frontier;

    start_state.add_move("0");
    frontier.push(start_state);
        
    int n_cicles = 0;
    bool goal_found = false;

    while(goal_found == false){
            
        n_cicles++;
        //cout<<n_cicles<<"\n";

        if(frontier.front().is_goal_found(goal_state_1) == true || frontier.front().is_goal_found(goal_state_2) == true || frontier.front().is_goal_found(goal_state_3) == true || frontier.front().is_goal_found(goal_state_4) == true || frontier.front().is_goal_found(goal_state_5) == true){ //checking if the node is the goal state
            goal_found = true;
            return frontier.front();
        }
        else{
            frontier.front().return_states(&frontier);//checking for the new possible states(deleting the one already seen)

            frontier.pop(); //deleting new node from the frontier
        }
    }

    return start_state;
}

string shift1(string move){
    if(move == "R"){
        return "F";
    }
    else if(move == "r"){
        return "f";
    }
    else if(move == "L"){//
        return "B";
    }
    else if(move == "l"){//
        return "b";
    }
    else if(move == "B"){//
        return "R";
    }
    else if(move == "b"){//
        return "r";
    }
    else if(move == "F"){//
        return "L";
    }
    else if(move == "f"){//
        return "l";
    }
    else if(move == "2R"){
        return "2F";
    }
    else if(move == "2L"){
        return "2B";
    }
    else if(move == "2B"){
        return "2R";
    }
    else if(move == "2F"){
        return "2L";
    }
    else{
        return move;
    }
}

string shift2(string move){
    if(move == "R"){
        return "L";
    }
    else if(move == "r"){
        return "l";
    }
    else if(move == "L"){
        return "R";
    }
    else if(move == "l"){
        return "r";
    }
    else if(move == "B"){
        return "F";
    }
    else if(move == "b"){
        return "f";
    }
    else if(move == "F"){
        return "B";
    }
    else if(move == "f"){
        return "b";
    }
    else if(move == "2R"){
        return "2L";
    }
    else if(move == "2L"){
        return "2R";
    }
    else if(move == "2B"){
        return "2F";
    }
    else if(move == "2F"){
        return "2B";
    }
    else{
        return move;
    }
}

string shift3(string move){
    if(move == "R"){
        return "B";
    }
    else if(move == "r"){
        return "b";
    }
    else if(move == "L"){
        return "F";
    }
    else if(move == "l"){
        return "f";
    }
    else if(move == "B"){
        return "L";
    }
    else if(move == "b"){
        return "l";
    }
    else if(move == "F"){
        return "R";
    }
    else if(move == "f"){
        return "r";
    }
    else if(move == "2R"){
        return "2B";
    }
    else if(move == "2L"){
        return "2F";
    }
    else if(move == "2B"){
        return "2L";
    }
    else if(move == "2F"){
        return "2R";
    }
    else{
        return move;
    }
}

vector<string> shift_moves(int shift, vector<string> moves){
    vector<string> replace_vec;
    
    if(shift == 1){
        for(int i = 0; i<moves.size(); i++){
            replace_vec.insert(replace_vec.begin()+i, shift1(moves[i]));
        }
    }
    else if(shift == 2){
        for(int i = 0; i<moves.size(); i++){
            replace_vec.insert(replace_vec.begin()+i, shift2(moves[i]));
        }
    }
    else if(shift == 3){
        for(int i = 0; i<moves.size(); i++){
            replace_vec.insert(replace_vec.begin()+i, shift3(moves[i]));
        }
    }
    else if(shift == 0){
        return moves;
    }
    else{
        cout<<"Errore shift"<<endl;
        throw 444;
    }

    return replace_vec;
}

vector<string> F2L_patterns(char c1 /*colore faccia lla sinistra*/, char c2 /*colore faccia alla destra*/, Cube x /*current_state*/){ //c1 e il colore alla sinistr dello soigolo, c2 e il colore alla destra
    int shift_;

    int c_1, c_2, c_3, c_4, c_5, c_6, c_7, c_8, c_9, c_10, c_11, c_12, c_13;
    
    if(c1 == 'b' && c2 == 'r'){
        shift_ = 1;

        c_1 = 26;
        c_2 = 8;
        c_3 = 5;
        c_4 = 3;
        c_5 = 25;
        c_6 = 1;
        c_7 = 33;
        c_8 = 4;
        c_9 = 17;
        c_10 = 6;
        c_11 = 9;
        c_12 = 28;
        c_13 = 11;
    }
    else if(c1 == 'o' && c2 == 'b'){
        shift_ = 2;

        c_1 = 34;
        c_2 = 24;
        c_3 = 0;
        c_4 = 1;
        c_5 = 33;
        c_6 = 4;
        c_7 = 17;
        c_8 = 6;
        c_9 = 9;
        c_10 = 3;
        c_11 = 25;
        c_12 = 36;
        c_13 = 27;
    }
    else if(c1 == 'g' && c2 == 'o'){
        shift_ = 3;

        c_1 = 18;
        c_2 = 32;
        c_3 = 2;
        c_4 = 4;
        c_5 = 17;
        c_6 = 6;
        c_7 = 9;
        c_8 = 3;
        c_9 = 25;
        c_10 = 1;
        c_11 = 33;
        c_12 = 20;
        c_13 = 35;
    }
    else{ //c1 == r && c2 == g
        shift_ = 0;

        c_1 = 10;
        c_2 = 16;
        c_3 = 17;
        c_4 = 6;
        c_5 = 9;
        c_6 = 3;
        c_7 = 25;
        c_8 = 1;
        c_9 = 33;
        c_10 = 4;
        c_11 = 17;
        c_12 = 12;
        c_13 = 19;
    }

    vector<string> moves;
    //https://ruwix.com/the-rubiks-cube/advanced-cfop-fridrich/first-two-layers-f2l/

    if(x.colors[c_1] == c1){
        if(x.colors[c_4] == c1 && x.colors[c_5] == c2){
            moves = {"U", "f", "2U", "F", "u", "R", "U", "r"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_5] == c1 && x.colors[c_4] == c2){
            moves = {"u", "f", "U", "F"}; //easy case
        }
        else if(x.colors[c_6] == c1 && x.colors[c_7] == c2){
            moves = {"u", "R", "U", "r", "U", "R", "U", "r"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_7] == c1 && x.colors[c_6] == c2){
            moves = {"U", "f", "u", "F", "U", "f", "2U", "F"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_8] == c1 && x.colors[c_9] == c2){
            moves = {"R", "U", "r"}; //easy case
        }
        else if(x.colors[c_9] == c1 && x.colors[c_8] == c2){
            moves = {"U", "f", "2U", "F", "U", "f", "2U", "F"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_10] == c1 && x.colors[c_11] == c2){
            moves = {"u", "R", "u", "r", "U", "R", "U", "r"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_11] == c1 && x.colors[c_10] == c2){
            moves = {"R", "u", "r", "2U", "f", "u", "F"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_12] == c1 && x.colors[c_13] == c2){ 
            moves = {"U", "f", "U", "F", "U", "f", "2U", "F"}; //corner in top edge in middle
        }
        else if(x.colors[c_13] == c1 && x.colors[c_12] == c2){
            moves = {"U", "f", "u", "F", "u", "R", "U", "r"}; //corner in top edge in middle                
        }
        else{
            cout<<"Errore 'c1' in F2L patterns"<<endl;
            throw 1;
        }
    }
    else if(x.colors[c_1] == 'w'){
        if(x.colors[c_4] == c1 && x.colors[c_5] == c2){
            moves = {"f", "U", "F", "2U", "R", "U", "r"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_5] == c1 && x.colors[c_4] == c2){
            moves = {"U", "f", "U", "F", "u", "f", "u", "F"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_6] == c1 && x.colors[c_7] == c2){
            moves = {"u", "R", "2U", "r", "u", "R", "2U", "r"}; //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_7] == c1 && x.colors[c_6] == c2){
            moves = {"f", "u", "F"}; //easy case
        }
        else if(x.colors[c_8] == c1 && x.colors[c_9] == c2){
            moves = {"u", "R", "U", "r", "u", "R", "2U", "r"};  //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_9] == c1 && x.colors[c_8] == c2){
            moves = {"U", "f", "u", "F", "u", "f", "u", "F"};   //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_10] == c1 && x.colors[c_11] == c2){
            moves = {"U", "R", "u", "r"}; //easy case
        }
        else if(x.colors[c_11] == c1 && x.colors[c_10] == c2){
            moves = {"u", "R", "2U", "r", "U", "f", "u", "F"};  //conrer pointing outwards, edge in top layer
        }
        else if(x.colors[c_12] == c1 && x.colors[c_13] == c2){
            moves = {"u", "R", "u", "r", "u", "R", "2U", "r"}; //corner in top, edge in middle
        }
        else if(x.colors[c_13] == c1 && x.colors[c_12] == c2){
            moves = {"u", "R", "U", "r", "U", "f", "u", "F"}; //corner in top, edge in middle
        }
        else{
            cout<<"Errore 'w' in F2L patterns"<<endl;
            throw 2;
        }
    }
    else if(x.colors[c_1] == c2){
        if(x.colors[c_4] == c1 && x.colors[c_5] == c2){
            moves = {"R", "U", "r", "2U", "R", "U", "r", "u", "R", "U", "r"}; //Corner pointing upwards, edge in top layer
        }
        else if(x.colors[c_5] == c1 && x.colors[c_4] == c2){
            moves = {"f", "2U", "F", "U", "f", "u", "F"}; //Corner pointing upwards, edge in top layer
        }
        else if(x.colors[c_6] == c1 && x.colors[c_7] == c2){
            moves = {"2U", "R", "U", "r", "U", "R", "u", "r"};   //Corner pointing upwards, edge in top layer
        }
        else if(x.colors[c_7] == c1 && x.colors[c_6] == c2){
            moves = {"u", "f", "2U", "F", "u", "f", "U", "F"};   //Corner pointing upwards, edge in top layer
        }
        else if(x.colors[c_8] == c1 && x.colors[c_9] == c2){
            moves = {"U", "R", "2U", "r", "U", "R", "u", "r"};     //Corner pointing upwards, edge in top layer       
        }
        else if(x.colors[c_9] == c1 && x.colors[c_8] == c2){
            moves = {"2U", "f", "u", "F", "u", "f", "U", "F"};      //Corner pointing upwards, edge in top layer
        }
        else if(x.colors[c_10] == c1 && x.colors[c_11] == c2){
            moves = {"R", "2U", "r", "u", "R", "U", "r"};   //Corner pointing upwards, edge in top layer             
        }
        else if(x.colors[c_11] == c1 && x.colors[c_10] == c2){
            moves = {"u", "R", "u", "r", "u", "f", "u", "F", "u", "f", "U", "F"};
        }
        else if(x.colors[c_12] == c1 && x.colors[c_13] == c2){ //corner in top, edge in middle
            moves = {"R", "U", "r", "u", "R", "U", "r", "u", "R", "U", "r", "u"};
        }
        else if(x.colors[c_13] == c1 && x.colors[c_12] == c2){   //corner in top, edge in middle     
            moves = {"R", "2U", "r", "2U", "f", "U", "F"};
        }
        else{
            cout<<"Errore 'c2' in F2L patterns"<<endl;
            throw 3;
        }
    }
    else{
        cout<<"Errore no F2L patterns found"<<endl;
        throw 4;
    }

    moves = shift_moves(shift_, moves);

    return moves;
}


vector<string> mirror_vector(vector<string> v){
    vector<string> returnV;

    for(int i = 0; i<v.size(); i++){
        returnV.insert(returnV.end() - i, v[i]);
    }

    return returnV;
}

bool check_f2l_goals(Cube cube, char colors[]){
    for(int i = 0; i<dim48; i++){
        if(colors[i] != 0){
            if(colors[i] != cube.colors[i]){
                return false;
            }
        }
    }

    return true;
}

vector<string> F2L_goals(Cube current_state){
    Cube appoggio_cube(current_state);

    bool x;

    //          goal 1

    F2L current_state_f2l;
    current_state_f2l.conversion_cube_F2L(current_state);

    current_state_f2l.erase_moves();

    char g_1_1[dim48] = {'0', '0', '0', '0', '0', '0', '0', 'r', '0', '0', 'g', '0', '0', '0', 'r', '0', 'w', '0', '0', '0', '0', '0', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};
    char g_1_2[dim48] = {'0', '0', '0', '0', '0', '0', 'r', 'r', '0', 'g', 'g', '0', '0', '0', 'r', '0', 'w', '0', '0', '0', '0', '0', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};
    char g_1_3[dim48] = {'0', '0', '0', 'r', '0', '0', '0', 'r', '0', '0', 'g', '0', '0', '0', 'r', '0', 'w', '0', '0', '0', '0', '0', 'g', '0', '0', 'g', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};
    char g_1_4[dim48] = {'0', 'r', '0', '0', '0', '0', '0', 'r', '0', '0', 'g', '0', '0', '0', 'r', '0', 'w', '0', '0', '0', '0', '0', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', 'g', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};
    char g_1_5[dim48] = {'0', '0', '0', '0', 'r', '0', '0', 'r', '0', '0', 'g', '0', '0', '0', 'r', '0', 'w', 'g', '0', '0', '0', '0', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};
    char g_1_6[dim48] = {'0', '0', '0', '0', '0', '0', '0', 'r', '0', '0', 'g', '0', 'r', '0', 'r', '0', 'w', '0', '0', 'g', '0', '0', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', '0', 'w', '0'};

    F2L goal_1_1; //partial goal, green red corner
    F2L goal_1_2; //partial goal green red edge
    F2L goal_1_3;
    F2L goal_1_4;
    F2L goal_1_5;
    F2L goal_1_6;
    
    goal_1_1.conversion_array_F2L(g_1_1); //partial goal, green red corner
    goal_1_2.conversion_array_F2L(g_1_2); //partial goals green red edge
    goal_1_3.conversion_array_F2L(g_1_3);
    goal_1_4.conversion_array_F2L(g_1_4);
    goal_1_5.conversion_array_F2L(g_1_5);
    goal_1_6.conversion_array_F2L(g_1_6);
    
    char g_1[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', '0', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', '0', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};
    F2L f2l_goal_1;
    f2l_goal_1.conversion_array_F2L(g_1); //goal of green red corner and edge
    
    vector<string> moves_goal_1_1;
    vector<string> moves_goal_1_2;
    vector<string> set_up_moves_1;
    vector<string> moves_red_green;

    x = true;
    for(int i = 0; i<dim48; i++){
        if(g_1[i] != '0'){
            if(g_1[i] != appoggio_cube.colors[i]){
                x = false;
            }
        }
    }

    if(x == false){
        current_state_f2l = BDF_f2l(current_state_f2l, goal_1_1); //BDF for setup moves
        moves_goal_1_1 = current_state_f2l.moves; //this works
        current_state_f2l.erase_moves();

        current_state_f2l = BDF_f2l_multiple_goals(current_state_f2l, goal_1_2, goal_1_3, goal_1_4, goal_1_5, goal_1_6);
        moves_goal_1_2 = current_state_f2l.moves;
        current_state_f2l.erase_moves();
        
        moves_goal_1_1 = mirror_vector(moves_goal_1_1);
        moves_goal_1_2 = mirror_vector(moves_goal_1_2);
        
        set_up_moves_1.insert( set_up_moves_1.end(), moves_goal_1_1.begin(), moves_goal_1_1.end());
        set_up_moves_1.insert(set_up_moves_1.end(), moves_goal_1_2.begin(), moves_goal_1_2.end());

        appoggio_cube = current_state.scramble_cube(set_up_moves_1);
        moves_red_green = F2L_patterns('r', 'g', appoggio_cube);
        current_state_f2l.scramble_f2l(moves_red_green);
        appoggio_cube = appoggio_cube.scramble_cube(moves_red_green);
        

        bool check = true;
        for(int i = 0; i<dim48; i++){
            if(g_1[i] != '0'){
                if(g_1[i] != appoggio_cube.colors[i]){
                    check = false;
                    break;
                }
            }
        }
        if(check == false){
            cout<<"Errore F2L red and green"<<endl;
            throw 101;
        }
    }

     

    //          goal 2

    char g_2_1[dim48] = {'0', '0', '0', '0', '0', 'b', '0', '0', 'r', '0', '0', '0', 'r', '0', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', 'w', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};
    char g_2_2[dim48] = {'0', '0', '0', '0', '0', 'b', 'r', '0', 'r', 'b', '0', '0', 'r', '0', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', 'w', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};
    char g_2_3[dim48] = {'0', '0', '0', '0', 'r', 'b', '0', '0', 'r', '0', '0', '0', 'r', '0', 'r', 'r', '0', 'b', '0', 'g', '0', 'g', 'g', '0', '0', '0', 'w', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};
    char g_2_4[dim48] = {'0', 'r', '0', '0', '0', 'b', '0', '0', 'r', '0', '0', '0', 'r', '0', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', 'w', '0', '0', '0', 'b', '0', '0', 'b', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};
    char g_2_5[dim48] = {'0', '0', '0', 'r', '0', 'b', '0', '0', 'r', '0', '0', '0', 'r', '0', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', 'b', 'w', '0', '0', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};
    char g_2_6[dim48] = {'0', '0', '0', '0', '0', 'b', '0', '0', 'r', '0', '0', 'r', 'r', '0', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', 'w', '0', 'b', '0', 'b', '0', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', '0'};

    F2L goal_2_1; //partial goal, red blue corner                                       ############################## CHECK GOALS 2_2 ,...., 2_6 ARE GOOD
    F2L goal_2_2; //partial goal red blue edge
    F2L goal_2_3;
    F2L goal_2_4;
    F2L goal_2_5;
    F2L goal_2_6;
    
    goal_2_1.conversion_array_F2L(g_2_1); //partial goal, red blue corner
    goal_2_2.conversion_array_F2L(g_2_2); //partial goals red blue edge
    goal_2_3.conversion_array_F2L(g_2_3);
    goal_2_4.conversion_array_F2L(g_2_4);
    goal_2_5.conversion_array_F2L(g_2_5);
    goal_2_6.conversion_array_F2L(g_2_6);

    char g_2[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', '0', '0', 'b', '0', 'b', 'b', '0', '0', '0', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};
    F2L f2l_goal_2;
    f2l_goal_2.conversion_array_F2L(g_2);

    vector<string> moves_goal_2_1;
    vector<string> moves_goal_2_2;
    vector<string> set_up_moves_2;
    vector<string> moves_blue_red;

    x = true;
    for(int i = 0; i<dim48; i++){
        if(g_2[i] != '0'){
            if(g_2[i] != appoggio_cube.colors[i]){
                x = false;
            }
        }
    }

    if(x == false){
        current_state_f2l = BDF_f2l(current_state_f2l, goal_2_1); //should work
        moves_goal_2_1 = current_state_f2l.moves;
        current_state_f2l.erase_moves();

        current_state_f2l = BDF_f2l_multiple_goals(current_state_f2l, goal_2_2, goal_2_3, goal_2_4, goal_2_5, goal_2_6); // its the fucking wrong order of moves
        moves_goal_2_2 = current_state_f2l.moves;
        current_state_f2l.erase_moves();

        moves_goal_2_1 = mirror_vector(moves_goal_2_1);
        moves_goal_2_2 = mirror_vector(moves_goal_2_2);

        set_up_moves_2.insert(set_up_moves_2.end(), moves_goal_2_1.begin(), moves_goal_2_1.end());
        set_up_moves_2.insert(set_up_moves_2.end(), moves_goal_2_2.begin(), moves_goal_2_2.end());

        appoggio_cube = appoggio_cube.scramble_cube(set_up_moves_2);
        moves_blue_red = F2L_patterns('b', 'r', appoggio_cube);
        appoggio_cube = appoggio_cube.scramble_cube(moves_blue_red);
        current_state_f2l.scramble_f2l(moves_blue_red);

        bool check = true;
        for(int i = 0; i<dim48; i++){
            if(g_2[i] != '0'){
                if(g_2[i] != appoggio_cube.colors[i]){
                    check = false;
                }
            }
        }
        if(check == false){
            cout<<"Errore F2L blue and red"<<endl;
            throw 102;
        }
    }

    

    //      goal 3

    char g_3_1[dim48] = {'w', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', 'b', '0', '0', '0', 'b', '0', 'b', 'b', '0', '0', 'o', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};
    char g_3_2[dim48] = {'w', 'o', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', 'b', '0', '0', '0', 'b', '0', 'b', 'b', '0', 'b', 'o', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};
    char g_3_3[dim48] = {'w', '0', '0', '0', '0', '0', 'o', '0', '0', 'b', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', 'b', '0', '0', '0', 'b', '0', 'b', 'b', '0', '0', 'o', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};
    char g_3_4[dim48] = {'w', '0', '0', '0', 'o', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', 'b', '0', 'g', '0', 'g', 'g', '0', 'b', '0', '0', '0', 'b', '0', 'b', 'b', '0', '0', 'o', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};
    char g_3_5[dim48] = {'w', '0', '0', 'o', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', 'b', 'b', '0', '0', 'b', '0', 'b', 'b', '0', '0', 'o', '0', '0', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};
    char g_3_6[dim48] = {'w', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', 'b', '0', '0', 'b', 'b', '0', 'b', 'b', '0', '0', 'o', '0', 'o', '0', 'o', '0', '0', 'w', '0', 'w', 'w', 'w', 'w', 'w'};

    F2L goal_3_1; //partial goal, blue orange corner
    F2L goal_3_2; //partial goal blue orange edge
    F2L goal_3_3;
    F2L goal_3_4;
    F2L goal_3_5;
    F2L goal_3_6;
    
    goal_3_1.conversion_array_F2L(g_3_1); //partial goal, blue orange corner
    goal_3_2.conversion_array_F2L(g_3_2); //partial goals blue orange edge
    goal_3_3.conversion_array_F2L(g_3_3);
    goal_3_4.conversion_array_F2L(g_3_4);
    goal_3_5.conversion_array_F2L(g_3_5);
    goal_3_6.conversion_array_F2L(g_3_6);

    char g_3[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', '0', 'g', 'g', '0', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', '0', '0', '0', '0', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    F2L f2l_goal_3;
    f2l_goal_3.conversion_array_F2L(g_3);

    vector<string> moves_goal_3_1;
    vector<string> moves_goal_3_2;
    vector<string> set_up_moves_3;
    vector<string> moves_orange_blue;

    x = true;
    for(int i = 0; i<dim48; i++){
        if(g_3[i] != '0'){
            if(g_3[i] != appoggio_cube.colors[i]){
                x = false;
            }
        }
    }

    if(x == false){
        current_state_f2l = BDF_f2l(current_state_f2l, goal_3_1);
        moves_goal_3_1 = current_state_f2l.moves;
        current_state_f2l.erase_moves();

        current_state_f2l = BDF_f2l_multiple_goals(current_state_f2l, goal_3_2, goal_3_3, goal_3_4, goal_3_5, goal_3_6);
        moves_goal_3_2 = current_state_f2l.moves;
        current_state_f2l.erase_moves();

        moves_goal_3_1 = mirror_vector(moves_goal_3_1);
        moves_goal_3_2 = mirror_vector(moves_goal_3_2);

        set_up_moves_3.insert(set_up_moves_3.end(), moves_goal_3_1.begin(), moves_goal_3_1.end());
        set_up_moves_3.insert(set_up_moves_3.end(), moves_goal_3_2.begin(), moves_goal_3_2.end());

        appoggio_cube = appoggio_cube.scramble_cube(set_up_moves_3);
        moves_orange_blue = F2L_patterns('o', 'b', appoggio_cube);
        appoggio_cube = appoggio_cube.scramble_cube(moves_orange_blue);
        current_state_f2l.scramble_f2l(moves_orange_blue);

        bool check = true;
        for(int i = 0; i<dim48; i++){
            if(g_3[i] != '0'){
                if(g_3[i] != appoggio_cube.colors[i]){
                    check = false;
                }
            }
        }
        if(check == false){
            cout<<"Errore F2L orange and blue"<<endl;
            throw 103;
        }
    }
    

    //      goal 4

    char g_4_1[dim48] = {'0', '0', 'w', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', 'g', 'g', '0', 'g', 'g', '0', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', 'o', '0', '0', '0', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    char g_4_2[dim48] = {'0', '0', 'w', '0', '0', '0', 'o', '0', '0', 'g', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', 'g', 'g', '0', 'g', 'g', '0', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', 'o', '0', '0', '0', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    char g_4_3[dim48] = {'0', '0', 'w', '0', 'o', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', 'g', 'g', 'g', '0', 'g', 'g', '0', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', 'o', '0', '0', '0', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    char g_4_4[dim48] = {'0', '0', 'w', 'o', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', 'g', 'g', '0', 'g', 'g', '0', '0', 'g', '0', 'b', 'b', 'b', 'b', 'b', 'o', '0', '0', '0', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    char g_4_5[dim48] = {'0', 'o', 'w', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', 'g', 'g', '0', 'g', 'g', '0', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', 'o', 'g', '0', '0', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    char g_4_6[dim48] = {'0', '0', 'w', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', 'g', 'g', 'o', 'g', 'g', '0', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', 'o', '0', '0', 'g', 'o', '0', 'o', 'o', '0', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};

    F2L goal_4_1; //partial goal, orange green corner
    F2L goal_4_2; //partial goal orange green edge
    F2L goal_4_3;
    F2L goal_4_4;
    F2L goal_4_5;
    F2L goal_4_6;
    
    goal_4_1.conversion_array_F2L(g_4_1); //partial goal, orange green corner
    goal_4_2.conversion_array_F2L(g_4_2); //partial goals orange green edge
    goal_4_3.conversion_array_F2L(g_4_3);
    goal_4_4.conversion_array_F2L(g_4_4);
    goal_4_5.conversion_array_F2L(g_4_5);
    goal_4_6.conversion_array_F2L(g_4_6);

    char g_4[dim48] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', 'r', 'r', 'r', 'r', 'r', '0', '0', '0', 'g', 'g', 'g', 'g', 'g', '0', '0', '0', 'b', 'b', 'b', 'b', 'b', '0', '0', '0', 'o', 'o', 'o', 'o', 'o', 'w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'};
    F2L f2l_goal_4;
    f2l_goal_4.conversion_array_F2L(g_4);

    vector<string> moves_goal_4_1;
    vector<string> moves_goal_4_2;
    vector<string> set_up_moves_4;
    vector<string> moves_green_orange;

    x = true;
    for(int i = 0; i<dim48; i++){
        if(g_4[i] != '0'){
            if(g_4[i] != appoggio_cube.colors[i]){
                x = false;
            }
        }
    }

    if(x == false){
        current_state_f2l = BDF_f2l(current_state_f2l, goal_4_1);
        moves_goal_4_1 = current_state_f2l.moves;
        current_state_f2l.erase_moves();

        current_state_f2l = BDF_f2l_multiple_goals(current_state_f2l, goal_4_2, goal_4_3, goal_4_4, goal_4_5, goal_4_6);
        moves_goal_4_2 = current_state_f2l.moves;
        current_state_f2l.erase_moves();

        moves_goal_4_1 = mirror_vector(moves_goal_4_1);
        moves_goal_4_2 = mirror_vector(moves_goal_4_2);

        set_up_moves_4.insert(set_up_moves_4.end(), moves_goal_4_1.begin(), moves_goal_4_1.end());
        set_up_moves_4.insert(set_up_moves_4.end(), moves_goal_4_2.begin(), moves_goal_4_2.end());

        appoggio_cube = appoggio_cube.scramble_cube(set_up_moves_4);
        moves_green_orange = F2L_patterns('g', 'o', appoggio_cube);
        appoggio_cube = appoggio_cube.scramble_cube(moves_green_orange);
        current_state_f2l.scramble_f2l(moves_green_orange);

        bool check = true;
        for(int i = 0; i<dim48; i++){
            if(g_4[i] != '0'){
                if(g_4[i] != appoggio_cube.colors[i]){
                    check = false;
                }
            }
        }
        if(check == false){
            cout<<"Errore F2L green and orange"<<endl;
            throw 104;

        }
    }
    


    vector<string> moves_f2l;

    moves_f2l.insert(moves_f2l.end(), set_up_moves_1.begin(), set_up_moves_1.end());
    moves_f2l.insert(moves_f2l.end(), moves_red_green.begin(), moves_red_green.end());

    moves_f2l.insert(moves_f2l.end(), set_up_moves_2.begin(), set_up_moves_2.end());
    moves_f2l.insert(moves_f2l.end(), moves_blue_red.begin(), moves_blue_red.end());

    moves_f2l.insert(moves_f2l.end(), set_up_moves_3.begin(), set_up_moves_3.end());
    moves_f2l.insert(moves_f2l.end(), moves_orange_blue.begin(), moves_orange_blue.end());

    moves_f2l.insert(moves_f2l.end(), set_up_moves_4.begin(), set_up_moves_4.end());
    moves_f2l.insert(moves_f2l.end(), moves_green_orange.begin(), moves_green_orange.end());

    return moves_f2l;
}
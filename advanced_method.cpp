#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
using namespace std;


#include "Cube.h"

const int dim8 = 8;
const int dim24 = 24;
const int dim18 = 18;
string all_moves[dim18] ={"R", "r", "L", "l", "F", "f", "B", "b", "U", "u", "D", "d", "2R", "2L", "2F", "2B", "2U", "2D"}; 

///////////////////////////////////////////////////////////////////////////
// prototipi

Cube execute_move(string move, Cube previous_state);
string return_opposite_move(string move);
string return_double_move(string move);

/////////////////////////////////////////////////////////////////////////////
//		Cube

Cube::Cube(){}

Cube::Cube(const Cube &copy){

	for(int i=0; i<dim48; i++){
		this->colors[i] = copy.colors[i]; 
	}

	for(int i = 0; i < copy.moves.size(); i++){
		moves.insert(moves.begin() + i, copy.moves[i]);
	}

}

void Cube::return_possible_states(queue<Cube>* frontier){
	Cube appoggio_cube;


	for(int i = 0; i < dim18; i++){
		if(all_moves[i] != return_opposite_move(this->moves[0]) && all_moves[i] != this->moves[0] && all_moves[i] != return_double_move(this->moves[0])){
			appoggio_cube = execute_move(all_moves[i], *this);
			appoggio_cube.add_move(all_moves[i]);

			frontier->push(appoggio_cube);
		}
	}
}

bool Cube::operator== (Cube& cube){
	for(int i = 0; i<dim48; i++){
		if(cube.colors[i] != this->colors[i]){
			return false;
		}
	}

	return true;
}

bool Cube::operator!= (Cube& cube){
	for(int i = 0; i<dim48; i++){
		if(cube.colors[i] != this->colors[i]){
			return true;
		}
	}

	return false;
}

void Cube::add_move(string m){
	this->moves.insert(this->moves.begin(), m);
}

void Cube::add_move_end(string m){
	this->moves.insert(this->moves.end(), m);
}

Cube Cube::R(){  
	Cube return_cube(*this);

	return_cube.change_colors(7, 15, 40, 32);
	return_cube.change_colors(2, 10, 45, 37);
	return_cube.change_colors(4, 12, 43, 35);
	return_cube.change_colors(16, 21, 23, 18);
	return_cube.change_colors(19, 22, 20, 17);
	
	return return_cube;
}
Cube Cube::r(){
	Cube return_cube(*this);

	return_cube.change_colors(32, 40, 15, 7);
	return_cube.change_colors(37, 45, 10, 2);
	return_cube.change_colors(35, 43, 12, 4);
	return_cube.change_colors(18, 23, 21, 16);
	return_cube.change_colors(17, 20, 22, 19);
	
	return return_cube;
}

Cube Cube::L(){
	Cube return_cube(*this);

	return_cube.change_colors(13, 5, 34, 42);
	return_cube.change_colors(8, 0, 39, 47);
	return_cube.change_colors(11, 3, 36, 44);
	return_cube.change_colors(28, 25, 27, 30);
	return_cube.change_colors(31, 26, 24, 29);

	return return_cube;
}
Cube Cube::l(){
	Cube return_cube(*this);

	return_cube.change_colors(42, 34, 5, 13);
	return_cube.change_colors(47, 39, 0, 8);
	return_cube.change_colors(44, 36, 3, 11);
	return_cube.change_colors(30, 27, 25, 28);
	return_cube.change_colors(29, 24, 26, 31);

	return return_cube;
}
Cube Cube::U(){
	Cube return_cube(*this);

	return_cube.change_colors(8, 16, 32, 24);
	return_cube.change_colors(10, 18, 34, 26);
	return_cube.change_colors(6, 4, 1, 3);
	return_cube.change_colors(7, 2, 0, 5);
	return_cube.change_colors(9, 17, 33, 25);

	return return_cube;
}
Cube Cube::u(){
	Cube return_cube(*this);
	
	return_cube.change_colors(24, 32, 16, 8);
	return_cube.change_colors(26, 34, 18, 10);
	return_cube.change_colors(3, 1, 4, 6);
	return_cube.change_colors(5, 0, 2, 7);
	return_cube.change_colors(25, 33, 17, 9);

	return return_cube;
}
Cube Cube::D(){
	Cube return_cube(*this);
	
	return_cube.change_colors(21, 13, 29, 37);
	return_cube.change_colors(23, 15, 31, 39);
	return_cube.change_colors(22, 14, 30, 38);
	return_cube.change_colors(45, 47, 42, 40);
	return_cube.change_colors(46, 44, 41, 43);

	return return_cube;
}
Cube Cube::d(){
	Cube return_cube(*this);
	
	return_cube.change_colors(37, 29, 13, 21);
	return_cube.change_colors(39, 31, 15, 23);
	return_cube.change_colors(38, 30, 14, 22);
	return_cube.change_colors(40, 42, 47, 45);
	return_cube.change_colors(43, 41, 44, 46);

	return return_cube;
}
Cube Cube::F(){
	Cube return_cube(*this);
	
	return_cube.change_colors(16, 5, 31, 45);
	return_cube.change_colors(21, 7, 26, 47);
	return_cube.change_colors(19, 6, 28, 46);
	return_cube.change_colors(10, 8, 13, 15);
	return_cube.change_colors(9, 11, 14, 12);

	return return_cube;
}
Cube Cube::f(){ //problema qui
	Cube return_cube(*this);
	
	return_cube.change_colors(45, 31, 5, 16);
	return_cube.change_colors(47, 26, 7, 21);
	return_cube.change_colors(46, 28, 6, 19);
	return_cube.change_colors(15, 13, 8, 10);
	return_cube.change_colors(12, 14, 11, 9);

	return return_cube;
}
Cube Cube::B(){
	Cube return_cube(*this);
	
	return_cube.change_colors(34, 32, 37, 39);
	return_cube.change_colors(33, 35, 38, 36);
	return_cube.change_colors(42, 24, 2, 23);
	return_cube.change_colors(40, 29, 0, 18);
	return_cube.change_colors(41, 27, 1, 20);

	return return_cube;
}
Cube Cube::b(){
	Cube return_cube(*this);
	
	return_cube.change_colors(39, 37, 32, 34);
	return_cube.change_colors(36,38, 35, 33);
	return_cube.change_colors(23, 2, 24, 42);
	return_cube.change_colors(18, 0, 29, 40);
	return_cube.change_colors(20, 1, 27, 41);

	return return_cube;
}


Cube Cube::R2(){  
	Cube return_cube(*this);

	return_cube.change_colors_2(7, 15, 40, 32);
	return_cube.change_colors_2(2, 10, 45, 37);
	return_cube.change_colors_2(4, 12, 43, 35);
	return_cube.change_colors_2(16, 21, 23, 18);
	return_cube.change_colors_2(19, 22, 20, 17);
	
	return return_cube;
}
Cube Cube::L2(){
	Cube return_cube(*this);

	return_cube.change_colors_2(13, 5, 34, 42);
	return_cube.change_colors_2(8, 0, 39, 47);
	return_cube.change_colors_2(11, 3, 36, 44);
	return_cube.change_colors_2(28, 25, 27, 30);
	return_cube.change_colors_2(31, 29, 24, 26);

	return return_cube;
}
Cube Cube::U2(){
	Cube return_cube(*this);

	return_cube.change_colors_2(8, 16, 32, 24);
	return_cube.change_colors_2(10, 18, 34, 26);
	return_cube.change_colors_2(6, 4, 1, 3);
	return_cube.change_colors_2(7, 2, 0, 5);
	return_cube.change_colors_2(9, 17, 33, 25);

	return return_cube;
}
Cube Cube::D2(){
	Cube return_cube(*this);
	
	return_cube.change_colors_2(21, 13, 29, 37);
	return_cube.change_colors_2(23, 15, 31, 39);
	return_cube.change_colors_2(22, 14, 30, 38);
	return_cube.change_colors_2(45, 47, 42, 40);
	return_cube.change_colors_2(46, 44, 41, 43);

	return return_cube;
}
Cube Cube::F2(){
	Cube return_cube(*this);
	
	return_cube.change_colors_2(16, 5, 31, 45);
	return_cube.change_colors_2(21, 7, 26, 47);
	return_cube.change_colors_2(19, 6, 28, 46);
	return_cube.change_colors_2(10, 8, 13, 15);
	return_cube.change_colors_2(9, 11, 14, 12);

	return return_cube;
}
Cube Cube::B2(){
	Cube return_cube(*this);
	
	return_cube.change_colors_2(34, 32, 37, 39);
	return_cube.change_colors_2(33, 35, 38, 36);
	return_cube.change_colors_2(42, 24, 2, 23);
	return_cube.change_colors_2(40, 29, 0, 18);
	return_cube.change_colors_2(41, 27, 1, 20);
	
	return return_cube;
}


void Cube::add_colors(char colors_array[]){
	for(int i = 0; i<dim48; i++){
		this->colors[i] = colors_array[i];
	}
}

void Cube::make_array(char empty_array[]){
	for(int i =0; i < dim48; i++){
		empty_array[i] = this->colors[i];
	}
}

/////////////////////////////////////////////////////////////////////////////
//		functions for moves

void Cube::change_colors(int index1, int index2, int index3, int index4){
	char appo = colors[index1];

	colors[index1] = colors[index2];
	colors[index2] = colors[index3];
	colors[index3] = colors[index4];
	colors[index4] = appo;

}

void Cube::change_colors_2(int index1, int index2, int index3, int index4){
	char appo = colors[index1];

	colors[index1] = colors[index3];
	colors[index3] = appo;

	appo = colors[index2];
	colors[index2] = colors[index4];
	colors[index4] = appo;
}

Cube execute_move(string move, Cube previous_state){
	
	if(move == "R"){
		return previous_state.R();
	}
	else if(move == "r"){
		return previous_state.r();
	}
	else if(move == "L"){
		return previous_state.L();
	}
	else if(move == "l"){
		return previous_state.l();
	}
	else if(move == "B"){
		return previous_state.B();
	}
	else if(move == "b"){
		return previous_state.b();
	}
	else if(move == "F"){
		return previous_state.F();
	}
	else if(move == "f"){
		return previous_state.f();
	}
	else if(move == "U"){
		return previous_state.U();
	}
	else if(move == "u"){
		return previous_state.u();
	}
	else if(move == "D"){
		return previous_state.D();
	}
	else if(move == "d"){
		return previous_state.d();
	}
	else if(move == "2R"){
		return previous_state.R2();
	}
	else if(move == "2L"){
		return previous_state.L2();
	}
	else if(move == "2B"){
		return previous_state.B2();
	}
	else if(move == "2F"){
		return previous_state.F2();
	}
	else if(move == "2U"){
		return previous_state.U2();
	}
	else if(move == "2D"){
		return previous_state.D2();
	}
	else if(move == "0"){
		return previous_state;
	}
	else{
		cout<<"Errore execute moves"<<endl;
		return previous_state;
	}
}


string return_opposite_move(string move){
	if(move == "R"){
		return "r";
	}
	else if(move == "r"){
		return "R";
	}
	else if(move == "L"){
		return "l";
	}
	else if(move == "l"){
		return "L";
	}
	else if(move == "B"){
		return "b";
	}
	else if(move == "b"){
		return "B";
	}
	else if(move == "F"){
		return "f";
	}
	else if(move == "f"){
		return "F";
	}
	else if(move == "U"){
		return "u";
	}
	else if(move == "u"){
		return "U";
	}
	else if(move == "D"){
		return "d";
	}
	else if(move == "d"){
		return "D";
	}
	else{
		return move;
	}
}

string return_double_move(string move){
	if(move == "R" || move == "r"){
		return "2R";
	}
	else if(move == "L" || move == "l"){
		return "2L";
	}
	else if(move == "B" || move == "b"){
		return "2B";
	}
	else if(move == "F" || move == "f"){
		return "2F";
	}
	else if(move == "U" || move == "u"){
		return "2U";
	}
	else if(move == "D" || move == "d"){
		return "2D";
	}
	else {
		return "0";
	}
}

bool return_special_move(string move1, string move2, string& move_to_change){
	if((move1 == "R" && move2 == "2R") || (move2 == "R" && move1 == "2R")){
		move_to_change = "r";
		return true;
	}
	else if((move1 == "r" && move2 == "2R") || (move2 == "r" && move1 == "2R")){
		move_to_change = "R";
		return true;
	}
	else if((move1 == "L" && move2 == "2L") || (move2 == "L" && move1 == "2L")){
		move_to_change = "l";
		return true;
	}
	else if((move1 == "l" && move2 == "2L") || (move2 == "l" && move1 == "2L")){
		move_to_change = "L";
		return true;
	}
	else if((move1 == "F" && move2 == "2F") || (move2 == "F" && move1 == "2F")){
		move_to_change = "f";
		return true;
	}
	else if((move1 == "f" && move2 == "2F") || (move2 == "f" && move1 == "2F")){
		move_to_change = "F";
		return true;
	}
	else if((move1 == "B" && move2 == "2B") || (move2 == "B" && move1 == "2B")){
		move_to_change = "b";
		return true;
	}
	else if((move1 == "b" && move2 == "2B") || (move2 == "b" && move1 == "2B")){
		move_to_change = "B";
		return true;
	}
	else if((move1 == "U" && move2 == "2U") || (move2 == "U" && move1 == "2U")){
		move_to_change = "u";
		return true;
	}
	else if((move1 == "u" && move2 == "2U") || (move2 == "u" && move1 == "2U")){
		move_to_change = "U";
		return true;
	}
	else if((move1 == "D" && move2 == "2D") || (move2 == "D" && move1 == "2D")){
		move_to_change = "d";
		return true;
	}
	else if((move1 == "d" && move2 == "2D") || (move2 == "d" && move1 == "2D")){
		move_to_change = "D";
		return true;
	}
	else{
		return false;
	}
}


//////////////////////////////////////////////////////////////////////////
//		functions for search

vector<string> breadth_first_search(Cube starting_state, Cube goal_state){
	queue<Cube> frontier;
	vector<string> moves;

	starting_state.add_move("0");
	frontier.push(starting_state);
	int n_cicles = 0;
	bool goal_found = false;

	while(goal_found == false){
		
		n_cicles++;
		cout<<n_cicles<<"\n";

		if(frontier.front() == goal_state){ //checking if the node is the goal state
			goal_found = true;
			cout<<"Goal Node found"<<endl;
			cout<<"Clearing frontier"<<endl;

			for(int i =0; i<frontier.front().moves.size(); i++){
				moves.insert(moves.begin(), frontier.front().moves[i]);
			}

			frontier = {};
			return moves;
		}
		else{
			frontier.front().return_possible_states(&frontier);//checking for the new possible states(deleting the one already seen)

			frontier.pop(); //deleting new node from the frontier
		}
	}

	return {"0"};
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//		functions to insert colors

int insert_array(char array[], int last_index){
    int x;
    for(int i=last_index; i<last_index+8; i++){
        cin>>x;
        array[i] = x;
    }

	return last_index+8;
}

void cout_moves(vector<string> moves){
	for(int i = 0; i<moves.size(); i++){
		cout<<moves[i]<<" ";
	}

	cout<<endl;
	cout<<endl;
}

void insert_colors(char initial_array[]){ //order for adding colors: yellow, red, green blue, orange, white
    int last_index = 0;

    cout<<"Inserire tutti i colori da sinistra a destra, dal basso verso l'alto "<<endl;
    cout<<""<<endl;

	cout<<"Inserisci i colori della faccia gialla: ";
    last_index = insert_array(initial_array, last_index);
    cout<<""<<endl;

    cout<<"Inserisci i colori della faccia rossa: ";
    last_index = insert_array(initial_array, last_index);
    cout<<""<<endl;
	 
	cout<<"Inserisci i colori della faccia verde: ";
    last_index = insert_array(initial_array, last_index);
    cout<<""<<endl;    
    
	cout<<"Inserisci i colori della faccia blu: ";
    last_index = insert_array(initial_array, last_index);
    cout<<""<<endl;
 
    cout<<"Inserisci i colori della faccia arancione: ";
    last_index = insert_array(initial_array, last_index);
    cout<<""<<endl;

    cout<<"Inserisci i colori della faccia bianca: ";
    last_index = insert_array(initial_array, last_index);
    cout<<""<<endl;
}

void declare_goal_array(char goal_array[]){
	for(int i = 0; i < dim48; i++){
		if(i < 8){
			goal_array[i] = 'y';
		}
		else if(i < 16){
			goal_array[i] = 'r';
		}
		else if(i < 24){
			goal_array[i] = 'g';
		}
		else if(i < 32){
			goal_array[i] = 'b';
		}
		else if(i < 40){
			goal_array[i] = 'o';
		}
		else if(i < 48){
			goal_array[i] = 'w';
		}
	}
}

Cube Cube::scramble_cube(vector<string> moves){
	Cube scrambled_cube(*this);

	for(int i = 0; i<moves.size(); i++){
		scrambled_cube = execute_move(moves[i], scrambled_cube);
	}

	return scrambled_cube;
}



vector<string> compress_moves(vector<string> v){ //might have the last problem of the code
	for(int i =0; i<v.size()-1; i++){
		if(v[i] == v[i+1]){
			v[i] = return_double_move(v[i]);
			v[i+1] = "0";
		}
		
		if(v[i] == return_opposite_move(v[i+1])){
			v[i] = "0";
			v[i+1] = "0";
		}

		string appoggio_move;
		if(return_special_move(v[i], v[i+1], appoggio_move) == true){
			v[i] = appoggio_move;
			v[i+1] = "0";
		}
	}

	for(int i =0; i<v.size(); i++){
		if(v[i] == "0"){
			v.erase(v.begin() + i);
			i--;
		}
	}


	for(int i =0; i<v.size()-1; i++){
		if(v[i] == v[i+1]){
			v[i] = return_double_move(v[i]);
			v[i+1] = "0";
		}
		
		if(v[i] == return_opposite_move(v[i+1])){
			v[i] = "0";
			v[i+1] = "0";
		}

		string appoggio_move;
		if(return_special_move(v[i], v[i+1], appoggio_move) == true){
			v[i] = appoggio_move;
			v[i+1] = "0";
		}
	}

	for(int i =0; i<v.size(); i++){
		if(v[i] == "0"){
			v.erase(v.begin() + i);
			i--;
		}
	}

	return v;
}

/////////////////////////////////////////////////////////////////////////////
//		Main

#include "cross_goals.cpp"
#include "f2l_goals.cpp"
#include "OLL_goals.cpp"
#include "PLL_goals.cpp"

int main(){
	srand(unsigned(time(NULL)));

	char start_array[dim48]; //array containing the colors of the inital state

	char goal_array[dim48];
	declare_goal_array(goal_array);
	Cube goal_cube;
	goal_cube.add_colors(goal_array); //intialising the goal: solved rubik's cube

	vector<string> scramble_moves;
	int decision = 3;

	while(decision != 1 && decision != 2){
		cout<<"Choose how to insert initial state of the rubik's cube: "<<endl;
		cout<<"[1] get random scramble"<<endl;
		cout<<"[2] insert color of initial state"<<endl;
		cin>>decision;
		cout<<endl;

		if(decision != 1 && decision != 2){
			cout<<"Input error, try again"<<endl;
			cout<<endl;
			cout<<endl;
		}
	}

	if(decision == 1){
		for(int i = 0; i<30; i++){
			scramble_moves.insert(scramble_moves.begin() + i, all_moves[rand()%18]); //for random scrambling
		}

		scramble_moves = compress_moves(scramble_moves);

		cout<<"this is the scramble moves: ";
		cout_moves(scramble_moves);
		cout<<"number of moves: "<<scramble_moves.size()<<endl;
	}
	else{
		cout<<"Orient the yellow face like this: "<<endl;
		cout<<"    O"<<endl;
		cout<<"B   Y   G"<<endl;
		cout<<"    R"<<endl;
		cout<<"insert the intial of the color, following this order: "<<endl;
		cout<<" 1 2 3"<<endl;
		cout<<" 4   5"<<endl;
		cout<<" 6 7 8"<<endl;
		for(int i=0; i<8; i++){
			char color;
			cin>>color;
			start_array[i] = color;
		}
		cout<<endl;

		cout<<"Orient the red face like this: "<<endl;
		cout<<"    Y"<<endl;
		cout<<"B   R   G"<<endl;
		cout<<"    W"<<endl;
		cout<<"insert the intial of the color, following this order: "<<endl;
		cout<<" 1 2 3"<<endl;
		cout<<" 4   5"<<endl;
		cout<<" 6 7 8"<<endl;
		for(int i=8; i<16; i++){
			char color;
			cin>>color;
			start_array[i] = color;
		}
		cout<<endl;

		cout<<"Orient the green face like this: "<<endl;
		cout<<"    Y"<<endl;
		cout<<"R   G   O"<<endl;
		cout<<"    W"<<endl;
		cout<<"insert the intial of the color, following this order: "<<endl;
		cout<<" 1 2 3"<<endl;
		cout<<" 4   5"<<endl;
		cout<<" 6 7 8"<<endl;
		for(int i=16; i<24; i++){
			char color;
			cin>>color;
			start_array[i] = color;
		}
		cout<<endl;

		cout<<"Orient the blue face like this: "<<endl;
		cout<<"    Y"<<endl;
		cout<<"O   B   R"<<endl;
		cout<<"    W"<<endl;
		cout<<"insert the intial of the color, following this order: "<<endl;
		cout<<" 1 2 3"<<endl;
		cout<<" 4   5"<<endl;
		cout<<" 6 7 8"<<endl;
		for(int i=24; i<32; i++){
			char color;
			cin>>color;
			start_array[i] = color;
		}
		cout<<endl;

		cout<<"Orient the orange face like this: "<<endl;
		cout<<"    Y"<<endl;
		cout<<"G   O   B"<<endl;
		cout<<"    W"<<endl;
		cout<<"insert the intial of the color, following this order: "<<endl;
		cout<<" 1 2 3"<<endl;
		cout<<" 4   5"<<endl;
		cout<<" 6 7 8"<<endl;
		for(int i=32; i<40; i++){
			char color;
			cin>>color;
			start_array[i] = color;
		}
		cout<<endl;

		cout<<"Orient the white face like this: "<<endl;
		cout<<"    O"<<endl;
		cout<<"G   W   B"<<endl;
		cout<<"    R"<<endl;
		cout<<"insert the intial of the color, following this order: "<<endl;
		cout<<" 1 2 3"<<endl;
		cout<<" 4   5"<<endl;
		cout<<" 6 7 8"<<endl;
		for(int i=40; i<48; i++){
			char color;
			cin>>color;
			start_array[i] = color;
		}
		cout<<endl;
	}

	Cube start_state(goal_cube);
	if(decision == 1){
		start_state = start_state.scramble_cube(scramble_moves);
	}
	else{
		start_state.add_colors(start_array);
	}
	
	Cube goal_check(start_state);

	vector<string> white_cross = white_cross_search(start_state);
	start_state = start_state.scramble_cube(white_cross);
	for(int i = 0; i<white_cross.size(); i++){
		if(white_cross[i] == "0"){
			white_cross.erase(white_cross.begin() + i);
			i--;
		}
	}
	cout<<endl;
	cout<<"Stage 1, moves white cross: "<<endl;
	cout_moves(white_cross);
	cout<<"-----------------------------------------------"<<endl;


	vector<string> f2l = F2L_goals(start_state);
	start_state = start_state.scramble_cube(f2l);
	for(int i = 0; i<f2l.size(); i++){
		if(f2l[i] == "0"){
			f2l.erase(f2l.begin() + i);
			i--;
		}
	}
	cout<<endl;
	cout<<"Stage 2, moves F2L: "<<endl;
	cout_moves(f2l);
  	cout<<"-----------------------------------------------"<<endl;


	vector<string> OLL = OLL_solve(start_state);
	start_state = start_state.scramble_cube(OLL);
	cout<<endl;
	cout<<"Stage 3, moves OLL: "<<endl;
	cout_moves(OLL);
	cout<<"-----------------------------------------------"<<endl;


	vector<string> PLL = PLL_search(start_state, goal_cube);
	start_state = start_state.scramble_cube(PLL);
	cout<<endl;
	cout<<"Stage 4, moves PLL: "<<endl;
	cout_moves(PLL);
	cout<<"-----------------------------------------------"<<endl;

	vector<string> moves_to_do;
	moves_to_do.insert(moves_to_do.end(), white_cross.begin(), white_cross.end());
	moves_to_do.insert(moves_to_do.end(), f2l.begin(), f2l.end());
	moves_to_do.insert(moves_to_do.end(), OLL.begin(), OLL.end());
	moves_to_do.insert(moves_to_do.end(), PLL.begin(), PLL.end());
	
	moves_to_do = compress_moves(moves_to_do);

	//cout_moves(moves_to_do);

	goal_check = goal_check.scramble_cube(moves_to_do);
	
	if(goal_check == goal_cube){
		cout<<endl;
		cout<<"The moves to solve the rubik's cube are: "<<endl;
		cout_moves(moves_to_do);
		cout<<"the number of moves is: "<<moves_to_do.size()<<endl;
	}
	else{
		cout<<"Error: Advance Method failed"<<endl;
		throw 999;
	}
}





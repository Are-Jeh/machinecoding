#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;

class Snake{
    public: 
    int head, tail;
    Snake(int _head, int _tail){
        tail = _tail, head = _head;
    }
    //isValid
    int update(int player_position){
        if (player_position == head){
            player_position = tail;
        }
        cout<<"Snake attack from "<<head<<" to "<<tail<<'\n';
        return player_position;
    }
};

class Ladder{
    public: 
    int head, tail;
    Ladder(int _head, int _tail){
        tail = _tail, head = _head;
    }
    int update(int player_position){
        if (player_position == tail){
            player_position = head;
        }
        cout<<"Ladder support from "<<tail<<" to "<<head<<'\n';
        return player_position;
    }
    //isValid
};

class Player{
    public: 
    string name;// string color;
    int pos;
    Player(string _name){
        name = _name, pos = 0;
    }
    Player(int _pos){
        pos = _pos;
    }
    void playerIncrement(int _pos){
        if ((pos+_pos)<=100){
            pos = pos+_pos;
        } 
    }
    //isValid?
};

int throwDice(){
    return 1 + rand()%6;
}

void displayPlayerPosition(Player p){
    cout<<" is at position: "<<p.pos<<'\n';
    return ;
}

int main(){
    int n; //no_of_players;
    cin >> n;
    int NO_OF_SNAKES = 4, NO_OF_LADDERS = 6;
    //we should check if the heads and tails are not colliding
    vector<Player>players(n, Player(""));
    unordered_map<int, int>snakes; //search via head
    unordered_map<int, int>ladders; //search via tail

    snakes[98] =  78; snakes[87] = 24; 
    snakes[95] = 75; snakes[62] =  19;

    ladders[28] = 84; ladders[51] = 67; ladders[18] = 55;
    ladders[9] = 31; ladders[24] = 42; ladders[71] = 91;

    srand(time(0));
    while(1){
    for(int i=0; i<n; ++i){
        // throw Dice
        // increment those many steps and check
        // if it is head of any snake or tail of any head
        int dice_result = 0;
        do{
            dice_result = throwDice();
            cout<<"DICE_RESULT for Player: "<<i<<" = "<<dice_result<<'\n';
            Player p = players[i];
            cout<<"Player: "<<i;
            displayPlayerPosition(p);
            p.playerIncrement(dice_result);
            cout<<"Player: "<<i;
            displayPlayerPosition(p);
            if (p.pos == 100){
                cout<<"PLAYER: "<<i<<" WON THE GAME\n";
                return 0;
            }
            int cur_loc = p.pos;
            if (snakes.count(cur_loc)) {
                int snake_tail = snakes[cur_loc];
                Snake snake = Snake(cur_loc, snake_tail);
                cout<<"Player: "<<i<<" bit by snake at " << p.pos << "\n";
                p.pos = snake.update(p.pos);
            } else if (ladders.count(cur_loc)) {
                int ladder_head = ladders[cur_loc];
                Ladder ladder = Ladder(ladder_head, cur_loc);
                cout<<"Player: "<<i<<" climbed ladder at " << p.pos << "\n";
                p.pos = ladder.update(p.pos);
            } 
            players[i] = p;
            cout<<"Player: "<<i;
            displayPlayerPosition(p);
        }while(dice_result == 6);
    }
    }


}

#include<ctime>
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include<ctime>
#include<cstdlib>

//KalahBoard class - > Kalah
//noofslots -> slots
//hole_number = hole_num
//evaluation - myEvaluationFunction
//winDecider - > maxWinNumber
//print -> winner()
//DISPLAY_BOARD -> DISPLAY()

using namespace std;

int total_nodes,expanded_node_count,game_path_length;
const int SIZE = 6;
/*




*/
class Kalah
{
public:
    int Player_A[SIZE],
        Player_B[SIZE],
        store_A,
        store_B,
        slots,
        maxWinNumber;

    int *pointer;

    Kalah();
    Kalah(Kalah *);//copy constructor
    void display();
    void operator=(Kalah);
    char move_decider(int,char);// returns which player has to make a move next
    char move_generator_A(int);//returns the next player that gets a chance, usually B but rare cases A gets a second chance
    char move_generator_B(int);//returns the next player that gets a chance, usually A but rare cases B gets a second chance
    char result();//

};

Kalah::Kalah()
{
    for(int i = 0 ; i < SIZE; i++)
    {
        Player_A[i] = 6;
        Player_B[i] = 6;
    }

    store_A = store_B = 0;
    slots = 5;

    pointer = NULL;
    maxWinNumber = 36;
}

//copy constructor to copy the value of the board from one var to another
Kalah::Kalah(Kalah *b)
{
    for(int i = 0; i < SIZE; i++)
    {
        this->Player_A[i] = b->Player_A[i];
        this->Player_B[i] = b->Player_B[i];
    }

    this->store_A = b->store_A;
    this->store_B = b->store_B;
}

//Function to display the board
void Kalah::display()
{
    cout << endl;
    cout << "\t\tPLAYER A";
    cout << endl << endl;
    cout << " \t | ";

    for(int i = 0 ; i < SIZE; i++)
    {
        cout  << i << setw(2) << "|";
        cout << " ";
    }

    cout << "--------------> Pit Numbers of A" << endl;
    // First Line
    cout << "\t=========================";

    //Second Line
    cout << endl;
    cout << "\t" << "|";
    cout << setw(2);


    for(int i = (SIZE - 1) ; i >= 0 ; i--)
    {
        //cout << "store_A" << endl;
        cout << Player_A[i] << setw(2) << "|";
        cout << " ";
    }

    cout << endl;
    cout << "\t=========================";

    cout << endl;
    cout << "store_A" << "\t\t\t\t   store_B" <<endl;
    cout << "------"  << "\t\t\t\t   ------";
    cout << endl;
    cout <<"|" << setw(3) << store_A << " |"; // Fourth Line
    cout <<"\t\t\t\t   |" << setw(3) << store_B << " |" << endl;
    cout << "------"  << "\t\t\t\t   ------";
    cout << endl;
    // Fifth Line
    cout << "\t=========================";
    cout << endl;
    //Sixth Line
    cout << "\t" << "|";
    cout << setw(2);

    for(int i = 0 ; i < SIZE; i++)
    {
        cout << Player_B[i] << setw(2) << "|";
        cout << " ";
    }

    cout << endl;
    cout << "\t=========================";
    cout << endl;
    cout << " \t | ";
     for(int i = 0 ; i < SIZE; i++)
    {
        cout  << i << setw(2) << "|";
        cout << " ";
    }
    cout << "--------------> Pit Numbers of B";
    cout << endl << endl;
    cout << "\t\tPLAYER B";
    cout << endl << endl << endl << endl;
}

//copy the value of Player_A[i] from the object kb to the original array Player_A[i] and Player_B[i] in the class
void Kalah::operator=(Kalah k)
{
    for(int i = 0; i < SIZE; i++)
    {
        Player_A[i] = k.Player_A[i];
        Player_B[i] = k.Player_B[i];

    }

    store_A = k.store_A;
    store_B = k.store_B;
    slots = 5;
    pointer = NULL;
    maxWinNumber = 36;

}

//Function which decides as to who should move
char Kalah::move_decider(int hole_num,char player)
{
    if(player == 'A')
        return (move_generator_A(hole_num));
    else
        return (move_generator_B(hole_num));
}

//Function to move for the A player
char Kalah::move_generator_A(int hole_num)
{
    int current_Position = hole_num;
    pointer = Player_A;

    int stoneCount = pointer[current_Position];

    pointer[current_Position] = 0;
    int opPosition, opStones;

    current_Position++;

    while(stoneCount > 0)
    {
        //last stone lands in Player A's store
        if(current_Position == 6 && stoneCount >= 1)
        {
            stoneCount--;
            store_A ++;

            if(stoneCount == 0)
                return 'A'; // giving A another chance as last stone falls in A's store
        }

        // a normal scenario where B gets the next chance
        else if(current_Position >= 0 && current_Position <= 5)
        {
            if(stoneCount == 1)
            {
                stoneCount--;

                opPosition = slots - current_Position;

                if(pointer[current_Position] == 0 && Player_B[opPosition] > 0)
                {
                    pointer = Player_B;
                    opStones = pointer[opPosition];
                    pointer[opPosition] = 0;

                    store_A += opStones + 1;

                    if(stoneCount == 0)
                        return 'B';
                }

                else
                {
                    pointer[current_Position]++;

                    if(stoneCount == 0)
                        return 'B';
                }
            }

            else if(stoneCount > 1)
            {
                stoneCount--;

                pointer[current_Position]++;
            }
        }

        else if(current_Position > 6 && current_Position <= 12)
        {
            pointer = Player_B;
            stoneCount--;

            pointer[current_Position-7]++;

            if(stoneCount == 0)
                return 'B';
        }

        //skip Player B's store
        else if(current_Position >= 12)
        {
            current_Position = -1;
            pointer = Player_A;
        }

        current_Position++;
    }
    return 'B';
}

//Function to move for the B player
char Kalah::move_generator_B(int hole_num)
{
    int current_Position = hole_num;
    pointer = Player_B;

    int stoneCount = pointer[current_Position];

    pointer[current_Position] = 0;
    int opPosition, opStones;

    current_Position++;

    while(stoneCount > 0)
    {
        //last stone lands in Player B's store
        if(current_Position == 6 && stoneCount >= 1)
        {
            stoneCount--;
            store_B++;

            if(stoneCount == 0)
                return 'B'; // giving B another chance as last stone falls in B's store
        }

        else if(current_Position >= 0 && current_Position <= 5)
        {
            if(stoneCount == 1)
            {
                stoneCount--;

                opPosition = slots - current_Position;

                if(pointer[current_Position] == 0)
                {
                    pointer = Player_A;
                    opStones = pointer[opPosition];
                    pointer[opPosition] = 0;

                    store_B += opStones + 1;

                    if(stoneCount == 0)
                        return 'A';
                }

                else
                {
                    pointer[current_Position]++;

                    if(stoneCount == 0)
                        return 'A';
                }
            }

            else if(stoneCount > 1)
            {
                stoneCount--;

                pointer[current_Position]++;
            }
        }

        else if(current_Position > 6 && current_Position <= 12)
        {
            pointer = Player_A;
            stoneCount--;

            pointer[current_Position-7]++;

            if(stoneCount == 0)
                return 'A';
        }

        else if(current_Position >= 12)
        {
            current_Position = -1;
            pointer = Player_B;
        }

        current_Position++;
    }
    return 'A';
}



//Function to decide as to which player wins
char Kalah::result()
{
    int empty_pits_A = 0,
        empty_pits_B = 0,
        a_stones = 0,
        b_stones = 0;

    for(int i = 0; i < SIZE; i++)
    {
        //if any pit in player A array is empty/ has no stones, we increment empty_pits_a
        if(Player_A[i]==0)
            empty_pits_A++;

        if(Player_B[i]==0)
            empty_pits_B++;

        a_stones += Player_A[i];
        b_stones += Player_B[i];

    }

    if(empty_pits_A == 6)
    {
        store_B += b_stones;

        //make all the pits in B empty too
        for(int i = 0 ; i < SIZE; i++)
            Player_B[i] = 0;

        cout << "Player A ran out of all the stones! All the pits in A are empty! " << endl;
    }

    if( empty_pits_B == 6)
    {
        store_A += a_stones;

        for(int i = 0 ; i < SIZE ; i++)
            Player_A[i] = 0;

        cout << "Player B ran out of all the stones! All the pits in A are empty! " << endl;
    }

    //if Player A has more than 36 stones, Player A wins
    if(store_A > maxWinNumber)
        return 'A';

    //if Player B has more than 36 stones, Player B wins
    else if(store_B > maxWinNumber)
        return 'B';

    //Player A or Player B ran out of stones and neither of their stores have more than 36 stones, it is a tie
    else if(empty_pits_A == 6 || empty_pits_B == 6)
        return 'T';

    else
        return 'N';
}




class KalahFlow
{

public:

    char player;
    Kalah current_status;
    int heuristic;
    KalahFlow * successors[SIZE];
    int successor_count;

    KalahFlow();
    KalahFlow(char);
    bool is_deep_enough(int, int);
    void generate_successors();
    int myEvaluationFunction();
    void current_player_status(Kalah);

};
    extern int nodes_generated,nodes_expanded,steps;

KalahFlow::KalahFlow()
{
    player = ' ';
    heuristic = -2000;
    successor_count = 0;

    for(int i = 0; i < SIZE; i++)
        successors[i] = NULL;
}

KalahFlow::KalahFlow(char player)
{
    this->player = player;
    heuristic = -2000;
    successor_count = 0;
    for(int i = 0; i < SIZE; i++)
    {
        successors[i] = NULL;
    }
}

bool KalahFlow::is_deep_enough(int depth, int selected)
{
    if(heuristic != -2000)
        return heuristic;

    if(depth >= selected || current_status.result() != 'N' )
        return true;

    else
    {
        expanded_node_count++;
        generate_successors();
        return false;
    }
}

void KalahFlow::generate_successors()
{
    char player_temp;

    if(player == 'A')
        player_temp = 'B';

    else
        player_temp = 'A';

    for(int i = 0; i < SIZE; i++)
    {
        successor_count++;

        successors[i] = new KalahFlow(player_temp);

        if(current_status.Player_A[i]!=0 && player == 'A')
            successors[i]->current_status = current_status;

        else if(current_status.Player_B[i]!=0 && player == 'B')
            successors[i]->current_status = current_status;

        else
            successors[i] = NULL;

        if(successors[i]!=NULL)
        {
            total_nodes++;
            successors[i]->current_status.move_decider(i,successors[i]->player);
        }
    }
}
//
int KalahFlow::myEvaluationFunction()
{
int p0 = current_status.store_A;
int p1 = current_status.store_B;
int value;
    if(player == 'A')
    {
        if(p0 != 0)
        {

            value = (current_status.store_A/current_status.store_B);
        }
        else{
            return -1;
        }
    }
    else if(player == 'B')
    {
        if(p1 !=0)
        {
            value = (current_status.store_B/ current_status.store_A);
        }
        else{
            return -1;
        }
    heuristic = value;
    return value;
}
}
//int KalahFlow::myEvaluationFunction()
//{
//
//int value;
//    if(player == 'A')
//    {
//        value= current_status.store_B - current_status.store_A;
//    }
//    else if(player == 'B')
//    {
//        value = current_status.store_B - current_status.store_A;
//    }
//    heuristic = value;
//
//    return value;
//
//}
void KalahFlow::current_player_status(Kalah k)
{
    for(int i = 0; i < SIZE; i++)
    {
        this->current_status.Player_A[i] = k.Player_A[i];
        this->current_status.Player_B[i] = k.Player_B[i];
    }

    this->current_status.store_A = k.store_A;
    this->current_status.store_B = k.store_B;
}

int AlphaBetaSearch(KalahFlow *alphabeta, int depth, char player, int alpha, int beta, int selected)
{

    if(alphabeta->is_deep_enough(depth, selected))
        return alphabeta->myEvaluationFunction() ;



    if (player == 'A' )
    {
       int bestValue = -100;
       int value;

       for (int i=0; i < 6; i++ )
        {

            if(alphabeta->successors[i]== NULL)
                continue;
            value = AlphaBetaSearch(alphabeta->successors[i], depth+1, alphabeta->player, alpha, beta, selected); // set resultant value from while loop
            if (bestValue > value)                                                     // set the best value for alpha and beta
                bestValue = bestValue;

            else
                bestValue = value;

            if (beta < bestValue)
                beta = beta;

            else beta = bestValue;

            if (beta <= alpha)
                break;

        }

        alphabeta->heuristic = bestValue;

        return bestValue;
    }

    else
    {
        int bestValue = +100;
        int value;

        for(int i=0; i < 6; i++)
        {
            if(alphabeta->successors[i]== NULL)
                continue;

            value = AlphaBetaSearch(alphabeta->successors[i], depth+1, alphabeta->player, alpha, beta, selected);

            if (bestValue < value)
                bestValue = bestValue;

            else
                bestValue = value;

            if (beta > bestValue)
                beta = beta;

            else
                beta = bestValue;

            if (beta < alpha)
                break;
        }

        alphabeta->heuristic = bestValue;

        return bestValue;
    }
}



int MinMaxAB(KalahFlow *min_max,int depth, char player, int use_Threshold, int pass_Threshold, int selectedDepth)
{
    int structure;
    int new_value;
    char new_Player;
    int result_successor = 0;

    if(min_max->is_deep_enough(depth, selectedDepth))
    {
        structure = min_max->myEvaluationFunction();

        if(player == 'B')
            structure = -structure;

        min_max->heuristic = structure;

        return structure;
    }

    for(int i = 0 ; i < SIZE; i++)
    {
        if(min_max->successors[i] == NULL)
            continue;

        if(player == 'A')
            new_Player = 'B';

        else
            new_Player = 'A';

        result_successor = MinMaxAB(min_max->successors[i],depth+1,new_Player,-pass_Threshold,-use_Threshold, selectedDepth);

        new_value = -result_successor;

        if(new_value > pass_Threshold)
        {
            min_max->heuristic = i;
            pass_Threshold = new_value;
        }

        if(pass_Threshold >= use_Threshold)
        {
            result_successor = pass_Threshold;
            return result_successor;
        }
    }

    result_successor = pass_Threshold;

    return result_successor;
}


void winner(char,int, Kalah);

//int total_nodes,expanded_node_count,game_path_length;

void winner(char result,int total_time, Kalah k)
{
    if(result == 'A')
        cout << "Player A won the GAME with " << k.store_A << " stones! " << endl << endl;

    else if(result == 'B')
        cout << "Player B won the GAME with " << k.store_B << " stones! " << endl << endl;

    else if(result == 'T')
        cout << "Oh, it's a TIE! " << endl << endl;

    cout << "******************************************************************************************************************" << endl;
    cout << "                                                 ***GAME OVER***                                                  " << endl ;
    cout << "******************************************************************************************************************" << endl << endl << endl;

    cout << "The program took " << "'" << ((total_time)/double(CLOCKS_PER_SEC)*1000) << "'" << "milliseconds of Execution time for the completed game! " << endl;
}

void display_PerfomanceAnalysis()
{
    cout << "The program generated " << "'" << total_nodes << "'" << " nodes for the completed game!" << endl;
    cout << "The program expanded " << "'" << expanded_node_count << "'" << " nodes for the completed game!" << endl;
    cout << "The total length of the Game path is " << "'" << game_path_length << "'" << " for the completed game! " << endl;
    cout << "1 node takes 81 bytes of Memory "<<endl;
    int total_memory = 81* total_nodes;
    cout << "The algorithm takes : "<< "'" << total_memory << "'" << " bytes = " << "'" << total_memory / (1024) << "'" << " kb" << " of memory!" <<endl;

}

int main()
{
    int choice, selectedDepth;
    Kalah *display = new Kalah();

        cout << endl << endl;
        cout << "*****************************************************************************************************************" << endl;
        cout << "                                            YOU ARE NOW IN THE KALAH GAME ZONE!                                  " << endl ;
        cout << "*****************************************************************************************************************" << endl;
        cout << endl;
        cout << "                                    The game rules are as below:                              " << endl << endl;
        cout << " ** Kalah is played by two players on a board with two rows of 6 holes facing each other." << endl << endl;
        cout << " ** It has two KALAHS (Stores for each player.)" << endl << endl;
        cout << " ** The stones are called beans. At the beginning of the game, there are 6 beans in every hole. The KALAHS are empty." << endl << endl;
        cout << " ** The object of Kalah is to get as many beans into your own kalah by distributing them." << endl << endl;
        cout << " ** A player moves by taking all the beans in one of his 6 holes and distributing them counterclockwise," << endl;
        cout << "    by putting one bean in every hole including his, but excluding the opponent's kalah." << endl << endl;
        cout << " ** There are two special moves:" << endl << endl;
        cout << " ** Extra move: If the last bean is distributed into his own kalah, the player may move again. " << endl
             << "    He has to move again even if he does not want to." << endl << endl;
        cout << " ** Capture: If the last bean falls into an empty hole of the player and the opponent's hole above (or below) is not empty," << endl
             << "    the player puts his last bean and all the beans in his opponent's hole into his kalah. He has won all those beans." << endl << endl;
        cout << " ** The game ends if all 6 holes of one player become empty (no matter if it is this player's move or not)." << endl
             <<"     The beans in the other player's holes are given into this player's kalah." << endl << endl;
        cout << " ** The player who won more beans (at least 37) becomes the winner." << endl << endl;


        cout << " *****************************************************************************************************************" << endl;
        cout << "                                            ***KALAH BOARD DISPLAY***                                             " << endl ;
        cout << " *****************************************************************************************************************" << endl;

        display->display();

        cout << " You now have the below choices :" << endl << endl
             << "Choose your option :" << endl << endl;

        cout << " ** Choose 1 for MinMaxAB: " << endl;
        cout << " ** Choose 2 for AlphaBetaSearch: " << endl;
        cout << " ** Choose 3 to QUIT:" << endl;
        cin >> choice;

        cout << "Please enter the depth that you would want to check the results for: The allowed depths are 2 and 4:" << endl;
        cin >> selectedDepth;

        while(selectedDepth !=2 && selectedDepth !=4)
        {
            cout << "Invalid Depth! Please enter depth value 2 or 4!" << endl;
            cin >> selectedDepth;
        }

        switch(choice)
        {
            case 1:
                {
                    Kalah *min_max = new Kalah();
                    cout << "Initial board " << endl;
                    min_max->display();

                    char result = min_max->result();

                    char player ='A';
                    int start_timer = clock();

                    while(result == 'N')
                    {
                        game_path_length++;

                        KalahFlow *min_max_ab = new KalahFlow(player);
                        min_max_ab->current_player_status( min_max );
                        cout << "It is player " << player << "'s turn!" << endl;

                        MinMaxAB(min_max_ab,0,player,2000,-2000,selectedDepth);

                        int pit = min_max_ab->heuristic;

                        player = min_max->move_decider(pit,player);
                        min_max->display();

                        result = min_max->result();
                    }

                    int stop_timer = clock();
                    min_max->display();
                    int total_time = stop_timer - start_timer;
                    winner(result, total_time, min_max );
                }

                break;

            case 2:
                {
                    Kalah *alpha_beta = new Kalah();
                    cout << "Initial board " << endl;
                    alpha_beta->display();

                    char result = alpha_beta->result();

                    char player = 'A';
                    int start_timer = clock();

                    while(result == 'N')
                    {
                        game_path_length++;

                        KalahFlow *alpha_beta_flow = new KalahFlow(player);
                        alpha_beta_flow->current_player_status(alpha_beta);
                        cout << "It is player " << player << "'s turn!" << endl;

                        AlphaBetaSearch(alpha_beta_flow,0,player,1000,-1000, selectedDepth);

                        int pit;

                        for(int i = 0; i < SIZE; i++)
                        {
                            if(alpha_beta_flow->successors[i] == NULL)
                                continue;

                            if(alpha_beta_flow->successors[i]->heuristic == alpha_beta_flow->heuristic)
                                pit = i;
                        }

                        player = alpha_beta->move_decider(pit,player);

                        alpha_beta->display();
                        result = alpha_beta->result();
                    }

                    int stop_timer = clock();
                    alpha_beta->display();
                    int total_time = stop_timer - start_timer;
                    winner(result,total_time, alpha_beta);
                }

                break;

            case 3:
                cout <<"Thanks. See you again later........." << endl;
                return 0;
        }

        display_PerfomanceAnalysis();

    return 0;
}

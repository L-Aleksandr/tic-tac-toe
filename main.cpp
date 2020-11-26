#include <iostream>
#include <vector>
#include <array>

const uint HEIGHT = 3;
const uint WIDTH = 3;
const uint IN_ROW_TO_WIN = 3;


enum CellLable{
    ZERO_lable,
    X_lable,
    O_lable,    
}; 


class Player{

    public:

        void Initialize(CellLable payer_lable){
            _players_lable = payer_lable;
        }
        
        std::array<uint, 2> MyTurn() const {
            std::array<uint, 2> input_coords;
            std::cout << "Player"<< static_cast<int>(_players_lable) << "'s turn, input coordinates:" << std::endl;
            
            std::cin >> input_coords[0];
            std::cin >> input_coords[1];

            if (input_coords[0] < 0 || input_coords[0] > 2 || input_coords[1] < 0 || input_coords[1] > 2){
                std::cerr << "Wrong coordinates!" << std::endl;
            }

            return input_coords;
        }

        CellLable GetLable(){
            return _players_lable;
        }

    private:

        CellLable _players_lable;
    
};

class GameBoard{

    public:

        void GetCell(){}

        void SetCell(CellLable players_lable, std::array<uint, 2> lable_coords){            
            _board_condition[lable_coords[0]][lable_coords[1]] = players_lable;
        }

        void Initialize(){
            _board_condition = clean_board;
        }

        std::array<std::array<CellLable, WIDTH>, HEIGHT> GetBoard() const {
            return _board_condition;
        }

        bool CellCorrect(std::array<uint, 2> lable_coords) const {
            if((_board_condition[lable_coords[0]][lable_coords[1]] == CellLable::ZERO_lable) && lable_coords[0] >= 0 && lable_coords[0] < HEIGHT && lable_coords[1] >= 0 && lable_coords[1] < WIDTH){
                return true;
            } else {
                return false;
            }
        }

    private:

        std::array<std::array<CellLable, WIDTH>, HEIGHT> _board_condition;

        const std::array<std::array<CellLable, WIDTH>, HEIGHT> clean_board { { 
            { {CellLable::ZERO_lable, CellLable::ZERO_lable, CellLable::ZERO_lable} }, 
            { {CellLable::ZERO_lable, CellLable::ZERO_lable, CellLable::ZERO_lable} },
            { {CellLable::ZERO_lable, CellLable::ZERO_lable, CellLable::ZERO_lable} }
        } };
};

class Drawer{

    public:

        void Init_Draw() const {
            std::cout << "     1 | 2 | 3 " << std::endl;
            std::cout << "    ---------- " << std::endl;
            std::cout << " a |   |   |   " << std::endl;
            std::cout << "   |---+---+---" << std::endl;
            std::cout << " b |   |   |   " << std::endl;
            std::cout << "   |---+---+---" << std::endl;
            std::cout << " c |   |   |   " << std::endl;
        }
        void TestDrawBoardCondition(std::array<std::array<CellLable, WIDTH>, HEIGHT> board_cond ) const {
            std::cout << "Test_output" << std::endl;
            for(uint i = 0; i < HEIGHT; i++){
                for(uint j = 0; j < WIDTH; j++){
                    std::cout << board_cond[i][j] << '\t';
                }
                std::cout << "\n";
            }
        }
        void DrawBoardCondition(std::array<std::array<CellLable, WIDTH>, HEIGHT> board_cond){
                std::cout << "     0 | 1 | 2 " << std::endl;
                std::cout << "    ---------- " << std::endl;
                std::cout << " 0 | " << LabelToChar(board_cond[0][0]) << " | " << LabelToChar(board_cond[0][1]) << " | " << LabelToChar(board_cond[0][2]) << " " << std::endl;
                std::cout << "   |---+---+---" << std::endl;
                std::cout << " 1 | " << LabelToChar(board_cond[1][0]) << " | " << LabelToChar(board_cond[1][1]) << " | " << LabelToChar(board_cond[1][2]) << " " << std::endl;
                std::cout << "   |---+---+---" << std::endl;
                std::cout << " 2 | " << LabelToChar(board_cond[2][0]) << " | " << LabelToChar(board_cond[2][1]) << " | " << LabelToChar(board_cond[2][2]) << " " << std::endl;
        }

    private:

        char LabelToChar(CellLable cell_lable) const {                
            char char_cell_labe;
            if(cell_lable == CellLable::ZERO_lable){
                char_cell_labe = ' ';
            } else if(cell_lable == CellLable::X_lable) {
                char_cell_labe = 'X';
            } else if(cell_lable == CellLable::O_lable) {
                char_cell_labe = 'O';
            } else {
                std::cerr << "LABLE DOES NOT EXIST" << std::endl;
            }
            return char_cell_labe;
        }
};

class GameManager{

    public:

        void GameCycle(){

            char answer;

            while(true){

                InitGame();
                uint _number_of_turns = 0;
                while (true){

                    std::array<uint,2> coords_candidates;
                    coords_candidates = _player1.MyTurn();
                    while( true ){                
                        if( _game_board.CellCorrect(coords_candidates) ){
                            _game_board.SetCell(_player1.GetLable(), coords_candidates);
                            _drawer.DrawBoardCondition(_game_board.GetBoard());
                            _number_of_turns++;
                            break;
                        } else {
                            std::cerr << "Player"<< static_cast<int>(_player1.GetLable()) << " your move is illegal, try another!" << std::endl;
                            coords_candidates = _player1.MyTurn();
                        }
                    }

                    if(CheckEndGame(_game_board.GetBoard(), _number_of_turns))
                        break;
                    

                    coords_candidates = _player2.MyTurn();
                    while( true ){                
                        if( _game_board.CellCorrect(coords_candidates) ){
                            _game_board.SetCell(_player2.GetLable(), coords_candidates);
                            _drawer.DrawBoardCondition(_game_board.GetBoard());
                            _number_of_turns++;
                            break;
                        } else {
                            std::cerr << "Player"<< static_cast<int>(_player2.GetLable()) << ", your move is illegal, try another!" << std::endl;
                            coords_candidates = _player2.MyTurn();
                        }
                    }

                    if(CheckEndGame(_game_board.GetBoard(), _number_of_turns))
                        break;                
                }

                std::cout << "_______________" << std::endl;
                std::cout << "Play again? [Y/n]" << std::endl;
                std::cin >> answer;
                if (answer == 'Y' || answer == 'y'){
                    continue;
                } else if(answer == 'N'){
                    break;
                } else {
                    break;
                }
            }
        }
    private:

        uint _number_of_turns;
        Player _player1;
        Player _player2;
        Drawer _drawer;
        GameBoard _game_board;

        void InitGame(){

            CellLable lable1 = CellLable::X_lable;
            CellLable lable2 = CellLable::O_lable;

            _player1.Initialize(X_lable);
            _player2.Initialize(O_lable);
            _game_board.Initialize();
            std::cout << "New game is initialised!" << std::endl;
            std::cout << "Player1's sign is \"X\"; Player2's sign is \"O\" " << std::endl;
            _drawer.DrawBoardCondition(_game_board.GetBoard());
        }

        bool CheckEndGame(std::array<std::array<CellLable, WIDTH>, HEIGHT> board_cond, uint _number_of_turns) const {

            CellLable winn_lable = ZERO_lable; 
            uint X_diag = 0, X_rdiag = 0;
            uint O_diag = 0, O_rdiag = 0;            
            
            for(uint i = 0; i < HEIGHT; i++){

                uint X_row = 0;
                uint O_row = 0;
                uint X_column = 0;
                uint O_column = 0;

                //CHECKING DIAGONAL
                if(board_cond[i][i] == CellLable::X_lable){
                    X_diag++;
                } else if(board_cond[i][i] == CellLable::O_lable) {
                    O_diag++;
                }
                if(X_diag == IN_ROW_TO_WIN){
                    winn_lable = CellLable::X_lable;
                    break;
                } else if(O_diag == IN_ROW_TO_WIN){
                    winn_lable = CellLable::O_lable;
                    break;
                }

                //CHECKING R_DIAGONAL
                if(board_cond[i][WIDTH-1-i] == CellLable::X_lable){
                    X_rdiag++;
                } else if(board_cond[i][WIDTH-1-i] == CellLable::O_lable) {
                    O_rdiag++;
                }
                if(X_rdiag == IN_ROW_TO_WIN){
                    winn_lable = CellLable::X_lable;
                    break;
                } else if(O_rdiag == IN_ROW_TO_WIN){
                    winn_lable = CellLable::O_lable;
                    break;
                }

                //CHECKING ROWS+COLS
                for(uint j = 0; j < WIDTH; j++){  //can be done WIDTH=HEIGTH
                    if(board_cond[i][j] == CellLable::X_lable){
                        X_row++;
                    } else if(board_cond[i][j] == CellLable::O_lable) {
                        O_row++;
                    }
                    if(board_cond[j][i] == CellLable::X_lable){
                        X_column++;
                    } else if(board_cond[j][i] == CellLable::O_lable) {
                        O_column++;
                    }
                }
                if(X_row == IN_ROW_TO_WIN || X_column == IN_ROW_TO_WIN){
                    winn_lable = CellLable::X_lable;
                    break;
                }else if(O_row == IN_ROW_TO_WIN || O_column == IN_ROW_TO_WIN){
                    winn_lable = CellLable::O_lable;
                    break;
                }

                /*//COLS
                for(uint j = 0; j < HEIGHT; j++){
                    if(board_cond[j][i] == CellLable::X_lable){
                        X_column++;
                    } else if(board_cond[j][i] == CellLable::O_lable) {
                        O_column++;
                    }
                }  //Can be added to rows
                if(X_column == IN_ROW_TO_WIN || O_column == IN_ROW_TO_WIN){
                    break;
                }else{
                    X_column = 0;
                    O_column = 0;
                }*/
            }    

            if(winn_lable == CellLable::X_lable || winn_lable == CellLable::O_lable && _number_of_turns <= HEIGHT*WIDTH){
                std::cout << "Player" << winn_lable << " wins!!!" << std::endl;
                return true;
            }else if(_number_of_turns >= HEIGHT*WIDTH){ 
                std::cout << "it's a draw!" << std::endl;
                return true;
            }else{
                return false;
            }
        }
};

std::array<std::array<CellLable, WIDTH>, HEIGHT> TestBoard(){
    std::array<std::array<CellLable, WIDTH>, HEIGHT> test_board_cond;
    
    for(uint i = 0; i < HEIGHT; i++){
        for(uint j = 0; j < WIDTH; j++){
            test_board_cond[i][j] = CellLable::ZERO_lable;
        }
    }

    test_board_cond[2][2] = CellLable::O_lable;
    test_board_cond[2][0] = CellLable::O_lable;
    test_board_cond[1][2] = CellLable::O_lable;
    test_board_cond[1][0] = CellLable::X_lable;
    test_board_cond[1][1] = CellLable::X_lable;

    return test_board_cond;
}

int main()
{
    GameManager game;
    game.GameCycle();

    return 0;
}
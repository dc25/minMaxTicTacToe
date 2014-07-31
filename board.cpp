#include <vector>
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include <math.h>

using namespace std;

#define HUMAN -1
#define COMPUTER 1

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

class game
{ 
public:

    game()
        : grid(9, 0),
        rowCount(3, 0), 
        columnCount(3,0),
        leftDiagonalCount(0),
        rightDiagonalCount(0),
        totalMoveCount(0)
    {
    }
 
    bool boardFull() const
    {
        return totalMoveCount == 9;
    }

    void display() const
    {
        cout << "  1 2 3\n";
        for(auto i = 0; i < 3; ++i)
        {
            cout << static_cast<char>('A'+i) << " ";
            for(auto j = 0; j < 3; ++j)
            {
                auto moveChar = ' ';
                switch (grid[i*3+j])
                {
                case 1:
                    moveChar = 'X';
                    break;
                case -1:
                    moveChar = 'Y';
                    break;
                }

                cout << moveChar;
                cout << ((j <2 ) ? '|' : '\n');
            }
            cout << ((i <2) ? "  -----\n" : "\n");
        }

        auto winner = getWinner();  // -1 or 1
        switch (getWinner())
        {
        case 1:
            cout << "Computer has won." << endl;
            break;
        case -1:
            cout << "Human has won." << endl;
            break;
        }

        if (boardFull())
        {
            cout << "Tie game." << endl;
        }
    }

    bool occupied(int row, int column) const
    {
        return 0 != grid[row*3 + column];
    }

    void makeMove(int row, int column, int moveValue)
    {
        grid[row*3 + column] = moveValue;
        rowCount[row] += moveValue;
        columnCount[column] += moveValue;
        if (row == column)
        {
            leftDiagonalCount += moveValue;
        }
        if (2 - row == column)
        {
            rightDiagonalCount += moveValue;
        }
        ++totalMoveCount;
    }

    void makeMove(int index, int moveValue)
    {
        makeMove(index / 3, index % 3, moveValue);
    }

    int max()
    {
        auto winner = getWinner();  // -1 or 1
        if (winner)
        {
            return winner;
        }

        if (boardFull())
        {
            return 0;
        }

        auto res = INT_MIN;
        for (auto move = 0; move < 9; ++move)
        {
            if (!grid[move])  // unused
            {
                auto new_game = *this;
                new_game.makeMove(move, COMPUTER);
                auto newRes = new_game.min();
                if (newRes > res)
                {
                    res = newRes;
                }
            }
        }
        return res;
    }

    int min()
    {
        auto winner = getWinner();  // -1 or 1
        if (winner)
        {
            return winner;
        }

        if (boardFull())
        {
            return 0;
        }

        auto res = INT_MAX;
        for (auto move = 0; move < 9; ++move)
        {
            if (!grid[move])  // unused
            {
                auto new_game = *this;
                new_game.makeMove(move, HUMAN);
                auto newRes = new_game.max();
                if (newRes < res)
                {
                    res = newRes;
                }
            }
        }
        return res;
    }

    void humanMove()
    {
        while (true) {
            string rc;
            getline(cin, rc);
            auto row = rc[0] - 'A';
            auto column = rc[1] - '1';
            if (occupied(row, column))
            {
                cout << "Already occupied." << endl;
            }
            else
            {
                makeMove(row, column, HUMAN);
                break;
            }
        }
    }

    void computerMove()
    {
        auto bestMove = -1;
        auto res = INT_MIN;
        for (auto move = 0; move < 9; ++move)
        {
            if (!grid[move])  // unused
            {
                auto new_game = *this;
                new_game.makeMove(move, COMPUTER);
                auto newRes = new_game.min();
                if (newRes > res)
                {
                    res = newRes;
                    bestMove = move;
                }
            }
        }
        
        makeMove(bestMove, COMPUTER);
    }

    int getWinner() const
    {
        for (auto i = 0; i < 3; ++i)
        {
            if (abs(rowCount[i]) == 3)
            {
                return sgn(rowCount[i]);
            }
            if (abs(columnCount[i]) == 3)
            {
                return sgn(columnCount[i]);
            }
        }

        if (abs(leftDiagonalCount)==3)
            return sgn(leftDiagonalCount);

        if (abs(rightDiagonalCount) == 3)
            return sgn(rightDiagonalCount);

        return 0;
    }
        
private:
    vector<int> grid;
    vector<int> rowCount;
    vector<int> columnCount;
    int leftDiagonalCount;
    int rightDiagonalCount;
    int totalMoveCount;
};

int main()
{
    game G;
    while (!G.getWinner() && !G.boardFull())
    {
        G.humanMove();
        G.display();
        if (G.getWinner() || G.boardFull())
        {
            break;
        }
        G.computerMove();
        G.display();
    }
}

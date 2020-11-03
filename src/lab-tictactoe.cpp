#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Triplet {
public:
	int indexes[3];

	Triplet(int index0, int index1, int index2) {
		Triplet::indexes[0] = index0;
		Triplet::indexes[1] = index1;
		Triplet::indexes[2] = index2;
	}
};

class Triplets {
public:
	vector<Triplet> triplets;
	Triplets() {
		triplets.push_back(newTriplet(0, 1, 2));
		triplets.push_back(newTriplet(3, 4, 5));
		triplets.push_back(newTriplet(6, 7, 8));
		triplets.push_back(newTriplet(0, 3, 6));
		triplets.push_back(newTriplet(1, 4, 7));
		triplets.push_back(newTriplet(2, 5, 8));
		triplets.push_back(newTriplet(0, 4, 8));
		triplets.push_back(newTriplet(6, 4, 2));
	}

	Triplet newTriplet(int index0, int index1, int index2) {
		Triplet triplet(index0, index1, index2);

		return triplet;
	}
};

class Board {
public:
	vector<string> cells;

	Board() {
		for (int i = 0; i < 9; i++) {
			Board::cells.push_back(" ");
		}
	}

	void show() {
		for (int row = 0; row < 3; row++) {
			for (int column = 0; column < 3; column++) {
				cout << " | " << row * 3 + column << " "
						<< Board::cells.at(row * 3 + column) << " |";
			}
			cout << endl;
		}
		cout << "----------------------------------------------------" << endl;
	}
};

class HumanPlayer {
public:
	void humanMove(Board *board) {
		bool validMove = false;
		int index = -1;

		while (!validMove) {
			while ((index < 0) || (index > 8)) {
				cout << "Jugues tu (humà)" << endl;
				cout << "A quina casella vols posar la fitxa ? ( 0 - 8 ) ?"
						<< endl;
				cin >> index;
			}

			if (board->cells.at(index) == " ") {
				validMove = true;
				board->cells.at(index) = "X";
			} else {
				cout << "La casella " << index
						<< " ja està ocupada. Tria'n una altre." << endl;
				index = -1;
			}
		}
	}
};

class ComputerPlayer {
	int scoreTable[9];

	bool isCentralCellAvailable() {
		bool centralCellAvailable = false;

		if (board->cells.at(4) == " ") {
			board->cells.at(4) = "O";
			cout << "Jo jugo a la casella 4" << endl;
			centralCellAvailable = true;
		}

		return centralCellAvailable;
	}

	bool canIWin() {
		bool iWin = false;

		for (int indexTriplet = 0; indexTriplet < 8; indexTriplet++) {
			int iNumComputerCoins = 0;
			int indexFreeCell = -1;

			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[0])
					== "O")
				iNumComputerCoins++;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[1])
					== "O")
				iNumComputerCoins++;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[2])
					== "O")
				iNumComputerCoins++;

			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[0])
					== " ")
				indexFreeCell = 0;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[1])
					== " ")
				indexFreeCell = 1;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[2])
					== " ")
				indexFreeCell = 2;

			if ((iNumComputerCoins == 2) && (indexFreeCell >= 0)) {
				cout << "Jo jugo a la casella "
						<< triplets.triplets.at(indexTriplet).indexes[indexFreeCell]
						<< endl;
				cout << "Guanyo jo!" << endl;
				board->cells.at(
						triplets.triplets.at(indexTriplet).indexes[indexFreeCell]) =
						"O";
				iWin = true;

				break;
			}
		}

		return iWin;
	}

	bool canIBlock() {
		bool iBlock = false;

		for (int indexTriplet = 0; indexTriplet < 8; indexTriplet++) {
			int iNumHumanCoins = 0;
			int indexFreeCell = -1;

			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[0])
					== "X")
				iNumHumanCoins++;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[1])
					== "X")
				iNumHumanCoins++;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[2])
					== "X")
				iNumHumanCoins++;

			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[0])
					== " ")
				indexFreeCell = 0;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[1])
					== " ")
				indexFreeCell = 1;
			if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[2])
					== " ")
				indexFreeCell = 2;

			if ((iNumHumanCoins == 2) && (indexFreeCell >= 0)) {
				cout << "Jo jugo a la casella "
						<< triplets.triplets.at(indexTriplet).indexes[indexFreeCell]
						<< endl;
				board->cells.at(
						triplets.triplets.at(indexTriplet).indexes[indexFreeCell]) =
						"O";
				iBlock = true;

				break;
			}
		}

		return iBlock;
	}

	void chooseOne() {
		cleanScoreTable();
		calculateScoreTable();
		// showScoreTable();
		int indexCell = selectMostValuableCell();
		board->cells.at(indexCell) = "O";
		cout << "Jo jugo a la casella " << indexCell << endl;
	}

	void cleanScoreTable() {
		for (int i = 0; i < 9; i++) {
			scoreTable[i] = 0;
		}
	}

	void calculateScoreTable() {
		for (int i = 0; i < 9; i++) {
			calculateScoreCell(i);
		}
	}

	void showScoreTable() {
		cout << "---------------------------------------------------------"
				<< endl;
		cout << "score table :";
		for (int i = 0; i < 9; i++) {
			cout << " " << scoreTable[i];
		}
		cout << endl;
		cout << "---------------------------------------------------------"
				<< endl;
	}

	void calculateScoreCell(int indexCell) {
		if ((board->cells.at(indexCell) == "O")
				|| (board->cells.at(indexCell) == "X")) {
			scoreTable[indexCell] = 0;
		} else {
			scoreTable[indexCell] = numFreeTripletsForCell(indexCell);
		}
	}

	int numFreeTripletsForCell(int indexCell) {
		int numFreeTriplets = 0;

		for (int indexTriplet = 0; indexTriplet < 8; indexTriplet++) {
			if (isCellInTriplet(indexCell, indexTriplet)) {
				if (isTripletFree(indexTriplet)) {
					numFreeTriplets++;
				}
			}
		}

		return numFreeTriplets;
	}

	bool isCellInTriplet(int indexCell, int indexTriplet) {
		bool isInTriplet = false;

		if ((triplets.triplets.at(indexTriplet).indexes[0] == indexCell)
				|| (triplets.triplets.at(indexTriplet).indexes[1] == indexCell)
				|| (triplets.triplets.at(indexTriplet).indexes[2] == indexCell)) {
			isInTriplet = true;
		}

		return isInTriplet;
	}

	bool isTripletFree(int indexTriplet) {
		bool isTripletFree = false;

		if (board->cells.at(triplets.triplets.at(indexTriplet).indexes[0])
				== " "
				&& board->cells.at(
						triplets.triplets.at(indexTriplet).indexes[1]) == " "
				&& board->cells.at(
						triplets.triplets.at(indexTriplet).indexes[2]) == " ") {
			isTripletFree = true;
		}

		return isTripletFree;
	}

	int selectMostValuableCell() {
		int indexMax = -1;
		int actualMax = 0;

		for (int i = 0; i < 9; i++) {
			if (scoreTable[i] > actualMax) {
				actualMax = scoreTable[i];
				indexMax = i;
			}
		}

		if (indexMax == -1) {
			indexMax = selectEmptyCell();
		}

		return indexMax;
	}

	int selectEmptyCell() {
		int indexCell;

		for (indexCell = 0; indexCell < 9; indexCell++) {
			if (board->cells.at(indexCell) == " ")
				break;
		}

		return indexCell;
	}

public:
	Board *board;
	Triplets triplets;

	void computerMove(Board* board) {
		this->board = board;
		cout << "Jugo jo (ordinador)" << endl;
		if (!isCentralCellAvailable()) {
			if (!canIWin()) {
				if (!canIBlock()) {
					chooseOne();
				}
			}
		}
	}
};

class Game {
	const int HUMAN = 1;
	const int COMPUTER = 0;

	int firstPlayer() {
		int i = rand() % 2;
		return i;
	}

	bool isEndGame() {
		bool endGame = false;
		board.show();

		if (isHumanWin() || isComputerWin() || isTie()) {
			endGame = true;
		}

		return endGame;
	}

	bool isHumanWin() {
		return isPlayerWin("X");
	}

	bool isComputerWin() {
		return isPlayerWin("O");
	}

	bool isPlayerWin(string playerCoin) {
		bool playerWin = false;
		for (int indexTriplet = 0; indexTriplet < 8; indexTriplet++) {
			if (board.cells.at(triplets.triplets.at(indexTriplet).indexes[0])
					== playerCoin
					&& board.cells.at(
							triplets.triplets.at(indexTriplet).indexes[1])
							== playerCoin
					&& board.cells.at(
							triplets.triplets.at(indexTriplet).indexes[2])
							== playerCoin) {

				playerWin = true;
				break;
			}
		}

		return playerWin;
	}

	bool isTie() {
		bool tie = true;

		for (int indexCell = 0; indexCell < 9; indexCell++) {
			if (board.cells.at(indexCell) == " ") {
				tie = false;
				break;
			}
		}
		if (tie) {
			cout << "Hem empatat" << endl;
		}

		return tie;
	}

public:
	Board board;
	Triplets triplets;
	int currentPlayer;
	HumanPlayer human;
	ComputerPlayer computer;

	Game() {
		srand(time(NULL));
		currentPlayer = firstPlayer();
	}

	void play() {
		while (!isEndGame()) {
			if (currentPlayer == HUMAN) {
				human.humanMove(&board);
				currentPlayer = COMPUTER;
			} else {
				computer.computerMove(&board);
				currentPlayer = HUMAN;
			}
		}
	}

};

int main() {
	cout << "LAB - Tic Tac Toe" << endl;
	cout << "----------------------------------------------------" << endl;

	Game game;

	game.play();

	return 0;
}

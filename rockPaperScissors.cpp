#include <iostream>
using namespace std;

enum enGameChoice {Stone = 1, Paper = 2, Scissors = 3};
enum enWinner {Player = 1, Computer = 2, Draw = 3};

struct stRoundInfo {
	short roundNumber = 0;
	enGameChoice playerChoice;
	enGameChoice computerChoice;
	enWinner Winner;
	string whoWinner = "";
};

struct stGameResult {
	short totalRound = 0;
	short playerWonTime = 0;
	short computerWonTime = 0;
	short howManyDraw = 0;
	enWinner gameWinner;
	string win = "";
};

int randomNumber(int from, int to) {
	return rand() % (to - from + 1) + from;
}

int manyRound() {
	int round;
	do {
		cout << "How Many Round 1 to 10\n";
		cin >> round;
	} while (round < 1 || round > 10);
	return round;
}

enGameChoice playerChoice() {
	int numberChoice;
	do {
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
		cin >> numberChoice;
	} while (numberChoice < 1 || numberChoice > 3);
	return (enGameChoice)numberChoice;
}

enGameChoice computerChoice() {
	return (enGameChoice)randomNumber(1, 3);
}

enWinner roundWinner(stRoundInfo roundInfo) {
	if (roundInfo.computerChoice == roundInfo.playerChoice) {
		return enWinner::Draw;
	}

	switch (roundInfo.playerChoice) {
	case enGameChoice::Stone:
		if (roundInfo.computerChoice == enGameChoice::Paper) {
			return enWinner::Computer;
		}
		break;

	case enGameChoice::Scissors:
		if (roundInfo.computerChoice == enGameChoice::Stone) {
			return enWinner::Computer;
		}
		break;	

	case enGameChoice::Paper:
		if (roundInfo.computerChoice == enGameChoice::Scissors) {
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}

enWinner gameWinner(short playerWonTime, short computerWonTime) {
	if (playerWonTime > computerWonTime) {
		return enWinner::Player;
	}	

	else if (computerWonTime > playerWonTime) {
		return enWinner::Computer;
	}

	return enWinner::Draw;
}

string ChoiceName(enGameChoice choice) {
	string choiceGame[] = { "Stone", "Paper", "Scissors" };
	return choiceGame[choice - 1];
}

string WinnerName(enWinner Winner) {
	string winnerGame[] = { "Player", "Computer", "Draw" };
	return winnerGame[Winner - 1];
}

void screenColor(enWinner win) {
	switch (win) {
	case enWinner::Player:
		system("color 20");
		break;

	case enWinner::Computer:
		system("color 40");
		cout << "\a";
		break;

	case enWinner::Draw:
		system("color 60");
		break;
	}
}

void screenRound(stRoundInfo round) {
	cout << "\n_______________Round[" << round.roundNumber << "]_______________\n";
	cout << "Player 1 Choice : " << ChoiceName(round.playerChoice) << "\n";
	cout << "Computer Choice : " << ChoiceName(round.computerChoice) << "\n";
	cout << "Round Winner    : " << WinnerName(roundWinner(round)) << '\n';
	cout << "--------------------------------------\n";
	screenColor(roundWinner(round));
}

string taps(int num) {
	string result = "";
	for (int i = 0; i < num; i++) {
		result += '\t';
	}
	return result;
}

void gameOverScreen() {
	cout << taps(4) << "------------------------------------------------------\n";
	cout << taps(4) << "            + + + G A M E   O V E R + + +\n";
	cout << taps(4) << "------------------------------------------------------\n";
	cout << taps(4) << "-----------------------[Game Result]------------------\n";
}

void gameScreen(stGameResult gameEnd) {
	gameOverScreen();
	cout << taps(4) << "Game Rounds        : " << gameEnd.totalRound << "\n";
	cout << taps(4) << "Player1 won times  : " << gameEnd.playerWonTime << "\n";
	cout << taps(4) << "Computer won times : " << gameEnd.computerWonTime << "\n";	
	cout << taps(4) << "Draw Times         : " << gameEnd.howManyDraw << "\n";
	cout << taps(4) << "Final Winner       : " << gameEnd.win << "\n";
	cout << taps(4) << "------------------------------------------------------\n";
	screenColor(gameWinner(gameEnd.playerWonTime, gameEnd.computerWonTime));
}

stGameResult roundGame(short manyGame) {
	stRoundInfo round;

	short draw = 0, player = 0, computer = 0;

	for (int roundGame = 1; roundGame <= manyGame; roundGame++) {
		cout << "Round [" << roundGame << "] begin" << "\n";
		round.roundNumber = roundGame;
		round.playerChoice = playerChoice();
		round.computerChoice = computerChoice();
		round.Winner = roundWinner(round);
		round.whoWinner = WinnerName(round.Winner);

		if (round.Winner == enWinner::Player) {
			player++;
		}

		else if (round.Winner == enWinner::Computer) {
			computer++;
		}

		else
			draw++;

		screenRound(round);
	}
	return { manyGame , player, computer, draw, gameWinner(player, computer), WinnerName(gameWinner(player, computer))};
}

void deleteScreen() {
	system("cls");
	system("color 07");
}

void startGame() {
	stGameResult game;
	char again = 'Y';
	do {
		game = roundGame(manyRound());
		gameScreen(game);
		cout << "Do you Went play Again y/n : ";
		cin >> again;
		deleteScreen();
	} while (again == 'y' || again == 'Y');
}

int main() {
	srand((unsigned)time(NULL));
	startGame();
}
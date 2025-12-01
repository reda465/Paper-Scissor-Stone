#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
enum enChoix { paper = 1, scissor = 2, stone = 3 };
typedef struct {
	string choixUtil;
	string ChoixOrdi;
	string Winner;
}stRound;
void Menu() {
	cout << "*************************Menu************************" << endl;
	cout << "paper=1\nscissor=2\nstone=3\n";
}
int readNbre(string message) {
	int nbre = 0;
	do {
		cout << message << endl;
		cin >> nbre;
	} while (nbre <= 0 || nbre > 3);
	return nbre;
}
int readNbreOfRound(string message) {
	int nbre = 0;
	do {
		cout << message << endl;
		cin >> nbre;
	} while (nbre <= 0 || nbre > 10);
	return nbre;
}
int aleatoire(int from, int to) {
	return rand() % (to - from + 1) + from;
}
enChoix ChoixOrdina(stRound Round[], int& i) {
	enChoix choix = enChoix(aleatoire(1, 3));
	if (choix == enChoix::paper) Round[i].ChoixOrdi = "paper";
	else if (choix == enChoix::stone) Round[i].ChoixOrdi = "stone";
	else if (choix == enChoix::scissor) Round[i].ChoixOrdi = "scissor";
	return choix;

}
enChoix ChoixUtilisa(stRound Round[], int& i) {
	enChoix choix = enChoix(readNbre("please enter your choice between 1 and 3 "));
	if (choix == enChoix::paper) Round[i].choixUtil = "paper";
	else if (choix == enChoix::stone) Round[i].choixUtil = "stone";
	else if (choix == enChoix::scissor) Round[i].choixUtil = "scissor";
	return choix;
}
void Play(stRound Round[], int& i) {
	int tap;
	enChoix choixOrdinateur = ChoixOrdina(Round, i);
	cout << "le choix d'ordi est : " << Round[i].ChoixOrdi << endl;
	enChoix choixJoueur = ChoixUtilisa(Round, i);
	switch (choixJoueur) {
	case enChoix::paper:
		if (choixOrdinateur == enChoix::scissor) {
			system("color 40");
			cout << " YOU LOST :-( \n";
			Round[i].Winner = "Ordinateur";
			break;
		}
		if (choixOrdinateur == enChoix::paper) {
			system("color 10");
			cout << "It's a draw :-| \n";
			Round[i].Winner = "NoOne";
			break;
		}
		system("color 20");
		cout << "YOU WON \n";
		Round[i].Winner = "Player1";
		break;
	case enChoix::scissor:
		if (choixOrdinateur == enChoix::stone) {
			system("color 40");
			cout << " YOU LOST :-( \n";
			Round[i].Winner = "Ordinateur";
			break;
		}
		if (choixOrdinateur == enChoix::scissor) {
			system("color 10");
			cout << "It's a draw :-| \n";
			Round[i].Winner = "NoOne";
			break;
		}
		system("color 20");
		cout << "YOU WON \n";
		Round[i].Winner = "You";
		break;
	case enChoix::stone:
		if (choixOrdinateur == enChoix::paper) {
			system("color 04");
			cout << " YOU LOST :-( \n";
			Round[i].Winner = "Ordinateur";
			break;
		}
		if (choixOrdinateur == enChoix::stone) {
			system("color 10");
			cout << "It's a draw :-| \n";
			Round[i].Winner = "NoOne";
			break;
		}
		system("color 20");
		cout << "YOU WON \n";
		Round[i].Winner = "Player1";
		break;
	}
	i++;
}
void Result(stRound Round[], int nbreRound) {
	cout << "\n\n*********************************Result*************************************\n\n";
	for (int i = 0; i < nbreRound; i++) {
		cout << "*****************************Round Nbre : " << i + 1 << "********************" << endl;
		cout << "Player Choice :\t " << Round[i].choixUtil << endl;
		cout << "Ordinateur Choice :\t" << Round[i].ChoixOrdi << endl;
		cout << "The winner is :\t " << Round[i].Winner << endl;
	}
	cout << "\n\n";
}
int Ask_user() {
	int answer = 0;
	do {
		cout << "Do you still wana play ?\n";
		cout << "1 For Yes :-) \n";
		cout << "0 For No :-(\n";
		cin >> answer;
	} while (answer < 0 || answer>1);
	return answer != 0;
}
int main() {
	srand(time(0));
	do {
		int i = 0;
		stRound Round[10];
		int nbreRound = readNbreOfRound("please enter the nbre of Round");
		do {
			Menu();
			Play(Round, i);
		} while (i < nbreRound);
		Result(Round, i);
	} while (Ask_user() != 0);
	cout << "YOU've Done Great Work";
}
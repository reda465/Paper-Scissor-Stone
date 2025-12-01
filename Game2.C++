#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
enum enChoice {paper=1,scissor=2,stone=3};
enum enWinner{Computer=1,Player1=2,Draw=3};
typedef struct {
	enChoice PlayerChoice;
	enChoice ComputerChoice;
	enWinner winner;
}stRound;
typedef struct {
	int nbreRound;
	int PlayerWon_time;
	int ComputerWon_time;
	int draw_time;
	enWinner FinalWinner;
	}stGame;
void originalColor(){
	system("color 07");
}
void Menu_choix() {
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
enChoice ChoixCompu(){
	return enChoice(aleatoire(1,3));
}
enChoice choixPlayer(){
	return enChoice(readNbre("entrer a number between 1 and 3 "));
}
void MakeColor(stRound Round){
	if(Round.winner==Computer){system("color 40");} 
	else if(Round.winner==Player1) {system("color 20" );}
	else{
		system("color 60");
	}
}
enWinner WinnerRound(stRound &Round){
	if(Round.PlayerChoice==Round.ComputerChoice) {
		return enWinner::Draw;
	}
	else{
		switch(Round.PlayerChoice){
			case enChoice::paper:
			if(Round.ComputerChoice==scissor)
			{
		      return enWinner::Computer;
	        }
			break;
			case enChoice::scissor:
			if(Round.ComputerChoice==stone)  {
		      return enWinner::Computer;
	        }
			break;
			case enChoice::stone:
			if(Round.ComputerChoice==paper)
			{
		      return enWinner::Computer;
	        } 
			break;
		}
		return enWinner::Player1;
	}
	
}
void ApplyChanges(stGame &Game, enWinner WinnerRound)
{
	if(WinnerRound==enWinner::Computer){
	Game.ComputerWon_time++;
	}
	else if(WinnerRound==enWinner::Player1){
		Game.PlayerWon_time++;
	}
	else{
		Game.draw_time++;
	}
}
void InfoRound(stRound &Round){
	Round.PlayerChoice=choixPlayer();
	Round.ComputerChoice=ChoixCompu();
	Round.winner= WinnerRound(Round);
}
string afficheWinner(enWinner WinnerRound){
	string tabWinner[3]={"Computer","Player1","Draw"};
	return tabWinner[WinnerRound-1];
}
string AfficheChoix(enChoice Choix){
	string tabChoix[3]={"paper","scissor","stone"};
	return tabChoix[Choix-1];
}
void afficheResultRound(stRound Round,int RoundNbr){
	MakeColor(Round);
	cout<<"***********Round Nbre ["<<RoundNbr<<"]************"<<endl;
	cout<<"Computer Choice \t: "<<AfficheChoix(Round.ComputerChoice)<<endl;
	cout<<"Player Choice  \t: "<<AfficheChoix(Round.PlayerChoice)<<endl;
	cout<<"Winner is \t"<<afficheWinner(Round.winner)<<endl;
}
void DecideTheFinalWinner(stGame &Game){
	if(Game.ComputerWon_time>Game.PlayerWon_time) Game.FinalWinner=Computer;
	else if(Game.PlayerWon_time>Game.ComputerWon_time) Game.FinalWinner=Player1;
	else{
		Game.FinalWinner=Draw;
	}
}
void AfficherGame(stGame Game){
	cout<<"Game Rounds\t: "<<Game.nbreRound<<endl;
	cout<<"Computer Won time\t:"<<Game.ComputerWon_time<<endl;
	cout<<"Player Won time :\t"<<Game.PlayerWon_time<<endl;
	cout<<"Draw time \t"<<Game.draw_time<<endl;
	cout<<"Final Winner\t:"<<afficheWinner(Game.FinalWinner)<<endl;
}
void affichRoundNbre(int RoundNbre){
	cout<<"\n *******Round Nbre["<<RoundNbre+1<<"] begins*******\n";
}
void afficherEndOfGame(){
	cout<<"-----------------------------+++++++++++GAME OVER+++++++++----------------------------------";
	cout<<"\n\t\t\t-----------------------------------------------------------------------------\t\t\t"<<endl;
	cout<<"**********************************************GAME RESULTS******************************************"<<endl;
	cout<<"\t\t\t-----------------------------------------------------------------------------\t\t\t"<<endl;
}
void RoundsExecution(stGame &Game){
	Game.nbreRound=readNbreOfRound("Enter the nomber of Rounds (min=1, max=10)");
	Game.ComputerWon_time=0;
	Game.PlayerWon_time=0;
	 Game.draw_time=0;
	for(int RoundNbre=0;RoundNbre<Game.nbreRound;RoundNbre++){
		stRound Round;
		affichRoundNbre(RoundNbre);
	    Menu_choix();
		InfoRound(Round);
		afficheResultRound(Round,RoundNbre);
		ApplyChanges(Game,Round.winner);
	}
}
char DoUWannaContin(){
	char answer;
	cout<<"Do you wanna continue presse \n \t 'y' for Yes \n\t 'n' for No\n"<<endl;
	cin>>answer;
	return answer;
}
void PlayGame(){
	char yOrN='y';
	do{
	stRound Round;
	stGame Game;
	originalColor();
	RoundsExecution(Game);
	afficherEndOfGame();
	DecideTheFinalWinner(Game);
	AfficherGame(Game);
	yOrN=DoUWannaContin();
	}while(yOrN=='y' || yOrN=='Y' );
	originalColor();
}
int main(){
	srand(time(NULL));
	PlayGame();
}
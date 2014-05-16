#include "Hangman.h"


int main(int argc, char** argv){
	std::ifstream f;

	if(argc == 1){
		f.open("defaultLibrary.txt");
	}else{
		f.open(argv[1]);
	}

	Hangman hangman;

	hangman.verify_valid_library(f);
	hangman.init_library(f);
	hangman.randomise_word();
	hangman.init_guesses_blank();
	hangman.init_man_blank();

	/* Remove comments to show words in library taken from file
	for(int i = 0; (unsigned)i < hangman.get_library().size(); i++){
		std::cout << hangman.get_library()[i] << std::endl;
	}
	*/

	while(hangman.is_completed() == false){
		if(hangman.get_num_wrong() == MAX_GUESSES) break;
		hangman.print_man();
		hangman.update_guesses();
		hangman.print_guesses();
		hangman.print_already_guessed();
		if(hangman.is_completed() == true) break;
		hangman.ask_guess();
		hangman.update_num_wrong();
	}
	if(hangman.get_num_wrong() == MAX_GUESSES){
		hangman.print_man();
		hangman.print_guesses();
		hangman.print_already_guessed();
	}
	hangman.print_end_game();

	return 0;
}



Hangman::Hangman(){
	this->m_num_wrong = 0;
	this->m_guess = ' ';
	set_word("llama");
}



int Hangman::get_num_wrong(void){ return m_num_wrong; }
char Hangman::get_guess(void){ return m_guess; }
std::string Hangman::get_guesses(void){ return m_guesses; }
std::string Hangman::get_word(void){ return m_word; }
std::vector <char> Hangman::get_already_guessed(){ return m_already_guessed;}
std::vector <std::string> Hangman::get_library(){return m_library;}
void Hangman::set_guess(char guess){this->m_guess = guess; }
void Hangman::set_num_wrong(int num_wrong){this->m_num_wrong = num_wrong; }
void Hangman::set_word(std::string word){ m_word= word; }
void Hangman::push_back_already_guessed(){ m_already_guessed.push_back(get_guess()); }



void Hangman::init_guesses_blank(){
	for(int i = 0; i < (int)( get_word().size() ); i++){
		this->m_guesses.push_back('_');
	}
}



void Hangman::init_man_blank(){
	m_man[0] = "________   ";
	m_man[1] = "|       |  ";
	m_man[2] = "|          ";//(2,8)
	m_man[3] = "|          ";//(3,8)(3,7)(3,9)
	m_man[4] = "|          ";//(4,8)
	m_man[5] = "|          ";//(5,7)(5,9)
	m_man[6] = "|          ";
}



void Hangman::print_guesses(){
	std::cout << "WORD: ";
	for(int i = 0; i < (int)( get_word().size() ); i++){
		std::cout << get_guesses()[i] << " ";
	}
	std::cout << std::endl;
}



void Hangman::print_end_game(){
	if(get_num_wrong() == MAX_GUESSES){
		std::cout << "Sorry, you've lost!" << std::endl;
		std::cout << "The word was: " << get_word() << std::endl;
	}
	else{
		std::cout << "Congrats! You win!";
	}
}



void Hangman::print_man(){
	switch(get_num_wrong()){
		case MAX_GUESSES:		{m_man[5][9] = '\\'; break;}
		case (MAX_GUESSES-1): 	{m_man[5][7] = '/'; break;}
		case (MAX_GUESSES-2): 	{m_man[4][8] = '|'; break;}
		case (MAX_GUESSES-3): 	{m_man[3][9] = '\\'; break;}
		case (MAX_GUESSES-4): 	{m_man[3][7] = '/'; break;}
		case (MAX_GUESSES-5): 	{m_man[3][8] = '|'; break;}
		case (MAX_GUESSES-6): 	{m_man[2][8] = 'O'; break;}
		default: break;
	}
	for(int i = 0; i <= NUM_HANGMAN_COLS; i++){
		if(i == NUM_HANGMAN_COLS){
			std::cout << m_man[i];
		}else{
			std::cout << m_man[i] << std::endl;
		}
	}
}



void Hangman::print_already_guessed(){
	std::cout << std::endl;
	std::cout << "List of Wrong Guesses: ";
	for(int i = 0; (unsigned)i < get_already_guessed().size(); i++){
		std::cout << get_already_guessed()[i] << ", ";
	}
	std::cout << std::endl;
}



void Hangman::ask_guess(void){
	char us_guess;
	printf("Please enter a letter to guess:(%d remaining) ", MAX_GUESSES - get_num_wrong());
	std::cin >> us_guess;
	set_guess(us_guess);
	if(!is_correct()){
		push_back_already_guessed();
	}
}



bool Hangman::is_correct(){
	if( m_word.find(get_guess()) != std::string::npos ){
		return true;
	}else{
		return false;
	}
}



bool Hangman::is_completed(){
	if( (unsigned)get_guesses().compare(get_word()) != std::string::npos){
		return true;
	}else{
		return false;
	}
}



void Hangman::update_guesses(){
	if(is_correct() == true){
		for(int i = 0; (unsigned)i < get_word().size(); i++ ){
			if(get_word()[i] == get_guess() ){
				m_guesses[i] = get_guess();
			}
		}
	}
}



void Hangman::update_num_wrong(){
	if(is_correct() == false){
		m_num_wrong++;
	}
}



void Hangman::randomise_word(){
	srand(time(NULL));
	//int i = rand() % ( get_library().size() );
	//set_word(get_library()[i]);
	int i = rand() % m_library.size();
	this->m_word = m_library[i];
}

void Hangman::verify_valid_library(std::ifstream& f){
	if ( !f.is_open() ){
		std::cout << "ERROR: Please select a valid *Library.txt file."
				  << std::endl;
		exit(EXIT_FAILURE);
	}
}

void Hangman::init_library(std::ifstream& f){
	std::string us_word;
	while( !f.eof() ){
		f >> us_word;
		m_library.push_back(us_word);
	}
}

#include "Hangman.h"


int main(){
	Hangman hangman;
	while(hangman.is_completed() == false){
		if(hangman.get_num_wrong() == MAX_GUESSES) break;
		hangman.print_man();
		hangman.print_guesses();
		hangman.ask_guess();
		hangman.is_correct();
	}
	hangman.print_man();
	hangman.print_guesses();
	hangman.print_end_game();

	return 0;
}



Hangman::Hangman(){
	this->m_num_wrong = 0;
	this->m_guess = ' ';
	m_word= "llama";
	init_guesses_blank();
	init_man_blank();
}



int Hangman::get_num_wrong(void){ return m_num_wrong; }
char Hangman::get_guess(void){ return m_guess; }
std::string Hangman::get_guesses(void){ return m_guesses; }
std::string Hangman::get_word(void){ return m_word; }
void Hangman::set_guess(char guess){this->m_guess = guess; }
void Hangman::set_num_wrong(int num_wrong){this->m_num_wrong = num_wrong; }
void Hangman::set_word(std::string word){ m_word= word; }



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
		case MAX_GUESSES: {
			m_man[5][9] = '\\';
		}
		case (MAX_GUESSES-1): m_man[5][7] = '/';
		case (MAX_GUESSES-2): m_man[4][8] = '|';
		case (MAX_GUESSES-3): m_man[3][9] = '\\';
		case (MAX_GUESSES-4): m_man[3][7] = '/';
		case (MAX_GUESSES-5): m_man[3][8] = '|';
		case (MAX_GUESSES-6): {
				m_man[2][8] = 'O';
				break;
		}
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


void Hangman::ask_guess(void){
	char us_guess;
	printf("Please enter a letter to guess:(%d remaining) ", MAX_GUESSES - get_num_wrong());
	std::cin >> us_guess;
	set_guess(us_guess);
}



bool Hangman::is_correct(){
	if( m_word.find(get_guess()) != std::string::npos ){
		for(int i = 0; i < get_word().size(); i++ ){
			if(get_word()[i] == get_guess() ){
				m_guesses[i] = get_guess();
			}
		}
		return true;
	}else{
		m_num_wrong++;
		return false;
	}
}



bool Hangman::is_completed(){
	if( get_guesses().compare(get_word()) == 0){
		return true;
	}
	return false;
}

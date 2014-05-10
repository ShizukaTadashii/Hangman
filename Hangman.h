#include <iostream>
#include <stdio.h> //printf

#define MAX_GUESSES 8

class Hangman{
	public:
		Hangman(void);

		int get_num_wrong(void);
		char get_guess(void);
		std::string get_guesses(void);
		std::string get_word(void);
		void set_guess(char guess);
		void set_num_wrong(int num_wrong);
		void set_word(std::string word);

		void make_guesses_blank();
		void print_guesses();
		void print_end_game();
		void print_man();

		void ask_guess(void);
		bool is_correct();
		bool is_completed();

	private:
		int m_num_wrong;
		char m_guess;
		std::string m_guesses;
		std::string m_word;
};

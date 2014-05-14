#include <iostream>
#include <vector>
#include <stdio.h> //printf

#define MAX_GUESSES 7
#define NUM_HANGMAN_ROWS 10
#define NUM_HANGMAN_COLS 6

class Hangman{
	public:
		Hangman(void);

		int get_num_wrong(void);
		char get_guess(void);
		std::string get_guesses(void);
		std::string get_word(void);
		std::vector <char> get_already_guessed();
		void set_guess(char guess);
		void set_num_wrong(int num_wrong);
		void set_word(std::string word);
		void push_back_already_guessed();

		void init_guesses_blank();
		void init_man_blank();
		void print_guesses();
		void print_end_game();
		void print_man();
		void print_already_guessed();

		void ask_guess(void);
		bool is_correct();
		bool is_completed();
		void update_guesses();
		void update_num_wrong();

	private:
		int m_num_wrong;
		char m_guess;
		std::string m_guesses;
		std::string m_word;
		std::string m_man[7];
		std::vector <char> m_already_guessed;
};

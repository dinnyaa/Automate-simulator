#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <assert.h>
#include <stack>
#include <iostream>

class Automate
{
public:
	void	parsing(std::string str);
	void	solve();
private:
	std::vector<std::string>	enter;
	std::vector<std::string>	exit;
	std::vector<std::string>	states;
	std::string					input;
	std::string					start;
	std::stack<std::pair<std::string, std::string>>		commands;
	std::map < std::pair < std::string, std::string >,
				std::pair < std::string, std::string >> table;

	void	init_vectors(std::ifstream &infile);
	void	init_stack(std::ifstream& infile);
	void	init_table();
	void	check_dup();
	void	check_input(std::string tmp);
	void	check_table(std::pair<std::string, std::string> tmp);

};
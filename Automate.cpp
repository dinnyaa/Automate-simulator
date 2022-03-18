#include "Automate.h"

void Automate::parsing(std::string file)
{
    std::ifstream infile(file);
    assert(infile.is_open());
    init_vectors(infile);
    check_dup();
    init_stack(infile);
    init_table();
    infile.close();
}

void Automate::solve()
{
    std::string tmp;
    std::cout << "Enter expression\n";
    std::getline(std::cin, input);
    std::string prev_state = start;
    size_t i = 0, j;

   while (i < input.size())
   {
       if (input[i] == ' ')
           i++;
       j = i;
       while (input[j] != ' ' && input[j] != '\0')
           j++;
       tmp = input.substr(i, j - i);
       if (tmp == "")
           continue;
       check_input(tmp);
       std::cout << table.at(make_pair(tmp, prev_state)).first <<" ";
       prev_state = table.at(make_pair(tmp, prev_state)).second;
       i = j;
   }
}

void Automate::init_table()
{
    for (size_t j = states.size() - 1; j != -1; j--)
    {
        for (size_t i = enter.size() - 1; i != -1; i--)
        {
            std::pair<std::string, std::string> indexes(enter[i], states[j]);
            std::pair<std::string, std::string> state(commands.top());
            commands.pop();
            table.insert(make_pair(indexes, state));
        }
    }
}

void Automate::init_vectors(std::ifstream &infile)
{
    std::string line;
    int repeat = 3;
    unsigned int i, j;

    while (repeat)
    {
        i = 0;
        std::getline(infile, line);
        while (line == "")
            std::getline(infile, line);
        while (i < line.size())
        {
            while (line[i] == ' ' || line[i] == ',')
                i++;
            j = i;
            while (line[j] != ',' && line[j] != '\0')
                j++;
            std::string cut = line.substr(i, j - i);
            if (repeat == 3)
                enter.push_back(cut);
            else if (repeat == 2)
                exit.push_back(cut);
            else if (repeat == 1)
            {
                if (states.size() == 0)
                    start = cut;
                states.push_back(cut);
            }
            i = j;
        }
        repeat--;
    }
}

void Automate::check_input(std::string tmp)
{
    bool is_in_alphabet = false;
    for (size_t i = 0; i < enter.size(); i++)
        if (enter[i] == tmp)
            is_in_alphabet = true;
    assert(is_in_alphabet);

}

void Automate::check_dup()
{
    for (size_t i = 0; i < enter.size(); i++)
        for (size_t j = i + 1; j < enter.size(); j++)
            assert(enter[i] != enter[j]);
    for (size_t i = 0; i < exit.size(); i++)
        for (size_t j = i + 1; j < exit.size(); j++)
            assert(exit[i] != exit[j]);
    for (size_t i = 0; i < states.size(); i++)
        for (int j = i + 1; j < states.size(); j++)
            assert(states[i] != states[j]);
}

void Automate::check_table(std::pair<std::string, std::string> tmp)
{
    bool is_in_table = false;
    for (size_t i = 0; i < exit.size(); i++)
        if (exit[i] == tmp.first)
            is_in_table = true;
    assert(is_in_table);
    is_in_table = false;
    for (size_t i = 0; i < states.size(); i++)
        if(states[i] == tmp.second)
            is_in_table = true;
    assert(is_in_table);
}

void Automate::init_stack(std::ifstream& infile)
{
    std::string line;
    std::pair < std::string, std::string > tmp;
    unsigned int i , j;

    std::getline(infile, line);
    while (line == "")
        std::getline(infile, line);

    while (line.size() != 0)
    {
        i = 0;
        while (i < line.size())
        {
            while (line[i] == ' ')
               i++;
            j = i;
            while (line[j] != ',')
                j++;
            tmp.first = line.substr(i, j - i);
            while (line[j] == ' ' || line[j] == ',')
                j++;
            i = j;
            while (line[j] != ' ' && line[j] != '\0')
                j++;
            tmp.second = line.substr(i, j - i);
            check_table(tmp);
            while ((line[j] == ' ' || line[j] == '|') && line[j] != '\0')
                j++;
            i = j;
            commands.push(tmp);
        }
        std::getline(infile, line);
    }
    assert(commands.size() == enter.size() * states.size());
}

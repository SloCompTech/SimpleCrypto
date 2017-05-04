#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
	if (argc < 5)
	{
		std::cerr << "Usage: <method> <key_file> <in_file> <out_file>" << std::endl;
		return -1;
	}
		

	std::ifstream dat_key;
	std::ifstream dat_in;
	std::ofstream dat_out;

	std::vector<char> u_key;
	std::vector<char> e_key;

	// Load key
	std::cout << "Loading key" << std::endl;
	dat_key.open(argv[2]);
	if (!dat_key.is_open() || !dat_key.good())
	{
		std::cerr << "Key file not valid" << std::endl;
		return -2;
	}

	std::string line = "";
	int c = 0; // Line counter
	do
	{
		getline(dat_key, line); // Read line from file
		for (int i = 0; i < line.size(); i++)
			if (c == 0)
				u_key.push_back(line.at(i));
			else if (c == 1)
				e_key.push_back(line.at(i));
		c++;
	} while (line != ""&&c < 2);

	dat_key.close(); // Close key file

	if (u_key.size() != e_key.size())
	{
		std::cerr << "Inconsistent key" << std::endl;
		return -3;
	}

	dat_in.open(argv[3]);
	if (!dat_in.is_open() || !dat_in.good())
	{
		std::cerr << "Input file not found" << std::endl;
		return -4;
	}

	dat_out.open(argv[4]);
	if (!dat_out.is_open() || !dat_out.good())
	{
		dat_in.close();
		std::cerr << "Output file can't be created" << std::endl;
		return -5;
	}

	char tmp;
	bool found = false;
	while (dat_in >> tmp)
	{
		found = false;
		for (int i = 0; i < u_key.size(); i++)
		{
			if (strcmp(argv[1], "e") == 0)
			{
				if (u_key.at(i) == tmp)
				{
					dat_out << e_key.at(i);
					found = true;
					break;
				}
			}
			else if (strcmp(argv[1], "u") == 0)
			{
				if (e_key.at(i) == tmp)
				{
					dat_out << u_key.at(i);
					found = true;
					break;
				}
			}
		}

		// If not found in key, just copy
		if (!found)
			dat_out << tmp;
	}

	// Close files
	dat_in.close();
	dat_out.close();
	return 0;
}
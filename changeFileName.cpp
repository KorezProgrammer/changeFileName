
#include <dirent.h>
#include <iostream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

int main()
{
	string newFormat = ".rar";
	string oldFormat = ".rar";
	string oldnamefile = "";
	vector<string> old_name;
	vector<string> new_name;
	struct dirent* file;
	DIR* open = opendir(".");
	int formatSize = 1;

	if (open != NULL)
	{
		while ((file = readdir(open)) != NULL)
		{
			old_name.push_back(file->d_name);
		}
		closedir(open);
	}
	else
	{
		cerr << "ERROR" << endl;
	}

	for (int i = old_name[0].size() - 1; i > 1; i--)
	{
		if (old_name[0][i] == '.')
		{
			break;
		}
		else
		{
			++formatSize;
		}
	}

	int* numbers = new int[old_name.size()];
	for (int i = 0; i < old_name.size(); i++)
	{
		int dig = 0;
		int x = old_name[i].size() - formatSize;
		for (int j = 0; j < x; j++)
		{
			if (isdigit(old_name[i][j]))
			{
				dig = dig * 10 + old_name[i][j] - '0';
			}
		}
		numbers[i] = dig;
	}

	for (int i = 0; i < old_name.size(); i++)
	{
		for (int j = i + 1; j < old_name.size(); j++)
		{
			if (numbers[i] > numbers[j])
			{
				int temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
				swap(old_name[i], old_name[j]);
			}
		}
	}

	int count = 0;
	int x = 1;
	for (int i = 0; i < old_name.size(); i++)
	{
		if (old_name[i].size() > 4)
		{
			if (old_name[i].substr(old_name[i].size() - 4, 4) == oldFormat)
			{
				count++;
				for (int j = 0; j < old_name[i].size() - 4; j++)
				{
					if (isdigit(old_name[i][j]))
					{
						break;
					}
					else
					{
						if (count > 1)
						{
							break;
						}
						oldnamefile += old_name[i][j];
					}
				}
			}
		}
	}

	for (int i = 0; i < old_name.size(); i++)
	{
		if (old_name[i].size() > 4)
		{
			new_name.push_back(oldnamefile + to_string(x) + newFormat);
			x++;
		}
	}

	cout << new_name[0] << endl;
	int j = 0;
	for (auto i : old_name)
	{
		if (i.size() > 4)
		{
			if (i.substr(i.size() - 4, 4) == oldFormat)
			{
				if (!(rename(i.c_str(), new_name[j].c_str())))
				{
					cout << "anjam shod\t" << i + " -->" + " " + new_name[j] << endl;
				}
				j++;
			}
		}
	}
	delete[] numbers;
	cin.get();
	return 0;
}

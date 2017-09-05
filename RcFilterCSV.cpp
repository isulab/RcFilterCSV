#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
	std::ifstream ifs(argv[1]);
	if (!ifs)
	{
		std::cout << "入力エラー";
		return -1;
	}

	std::vector<std::string> headdar;
	std::vector<std::vector<double>> data;
	std::string str;
	

	while (std::getline(ifs, str))
	{
		std::vector<double> temp_vec;
		std::string token;
		std::istringstream stream(str);

		while (getline(stream, token, ',')) {
			double temp;
			try
			{
				temp = std::stod(token);
			}
			catch(std::invalid_argument)
			{
				headdar.push_back(str);
				break;
			}
			temp_vec.push_back(temp);
			//std::cout << temp << ",";
		}
		if(temp_vec.size() != 0) data.push_back(temp_vec);
		//std::cout << std::endl;
	}

	for (auto const& each : headdar)
	{
		std::cout << each;
	}
	for (std::size_t i = 0; i < 5 && i < data.size(); ++i)
	{
		for (auto const& ele : data[i])
		{
			std::cout << ele << ",";
		}
		std::cout << std::endl;
	}
	std::cout << "." << std::endl << "." << std::endl << "." << std::endl << "." << std::endl;


	double k;
	std::cout << "0行目を除き1,2,3行目にRCフィルタを適用します．" << std::endl;
	std::cout << "フィルタ係数を入力してください >> ";
	std::cin >> k;

	for (std::size_t i = 1; i < data.size(); ++i)
	{
		//y[i] = a*y[i-1] + (1-a)*x[i]
		for (std::size_t j = 1; j <= 3; ++j)
		{
			data[i][j] = k * data[i - 1][j] + (1 - k) * data[i][j];
		}
	}
	for (std::size_t i = 0; i < 5 && i < data.size(); ++i)
	{
		for (auto const& ele : data[i])
		{
			std::cout << ele << ",";
		}
		std::cout << std::endl;
	}
	std::cout << "." << std::endl << "." << std::endl << "." << std::endl << "." << std::endl;


	std::string filename(argv[1]);
	std::ofstream ofs(filename + "-rc.csv");


	for (std::string & each : headdar)
	{
		ofs << each << std::endl;
	}
	for (auto const& each : data)
	{
		for (auto const& ele : each)
		{
			ofs << ele << ",";
		}
		ofs << std::endl;
	}
	ifs.close();
}

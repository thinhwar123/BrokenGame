#include "DataGlobe.h"
#include <iostream>
#include <string>
#include <fstream> 

DataGlobal::DataGlobal()
{
	LoadScore();
}

DataGlobal::~DataGlobal()
{
}

void DataGlobal::LoadScore()
{
	std::ifstream fileInput("score.txt", std::ios::in);
	if (fileInput.fail())
	{
		SaveScore(0);
	}
	else
	{
		fileInput >> m_highscore;
		std::cout << m_highscore << std::endl;
	}

	fileInput.close();
}

void DataGlobal::SaveScore(int score)
{
	m_highscore = score;
	std::ofstream fileOutput("score.txt", std::ios::out);
	fileOutput << m_highscore;

	fileOutput.close();
}

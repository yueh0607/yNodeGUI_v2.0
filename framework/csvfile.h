#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include"tools.h"
using namespace std;


template <typename T>
class ISerializable
{
public:
	virtual string ToCsvRow() = 0;
	virtual void FromCsvRow(string str) = 0;
};

template<typename T>
class csvfile
{
	string path;
public:

	csvfile(string path) : path(path)
	{
		checkAndCreatePathAndFile(path);
	}


	void write(vector<T*> obj)
	{
		
		ofstream fout = ofstream(path);

		for (int i = 0; i < obj.size(); i++)
		{
			fout << obj[i]->ToCsvRow() << endl;
		}
		fout.close();
	}

	vector<T*> read()
	{

		ifstream fin (path);
		vector<T*> temp;

		string line;


		while (std::getline(fin, line))
		{
			T* t = new T();
			t->FromCsvRow(line);
			temp.push_back(t);
		}
		fin.close();
		return temp;
	}


};
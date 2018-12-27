#pragma once
#ifndef TEST_SQLITE
#define TEST_SQLITE

#include "sqlite3.h"
#include <vector>
using namespace std;

struct QueryResult
{
	vector<vector<string>> data;
	vector<string> collumns;

	void reset()
	{
		data.clear();
		collumns.clear();
	}

	void print()
	{
		for (int i = 0; i < collumns.size(); i++)
		{
			printf("%s\t", collumns.at(i).c_str());
		}

		printf("\n");
		for (int r = 0; r < data.size(); r++)
		{
			for (int c = 0; c < data[r].size(); c++)
			{
				printf("%s\t", data[r].at(c).c_str());
			}
			printf("\n");
		}
	}
};

template<class T>
struct QueryResultRecord
{
	pair<string, T> data;
};

class TestSQlite
{
public:
	TestSQlite();
	virtual ~TestSQlite();

	bool openDb(const char* name);
	void closeDb();

	void queryUsingsqlite3_exec(const char * queryString, QueryResult* dataStructResult);

	void processData();

	static int callback(void *userContext, int argc, char **argv, char **azColName);
private:
	sqlite3* m_dbInstance;


};
#endif

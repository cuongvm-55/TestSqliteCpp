// TestSqlite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "./TestSQLite.h"
int main()
{
	TestSQlite* sqlite = new TestSQlite();
	if (!sqlite->openDb("BALLASTSYSTEM"))
	{
		printf("Fail to open database");
	}

	QueryResult* result = new QueryResult();
	sqlite->queryUsingsqlite3_exec("SELECT * FROM devicetable;", result);
	if (result)
	{
		result->print();
	}

    Device{name, id}
    
	sqlite->queryUsingsqlite3_exec("SELECT * FROM sqlite_master WHERE type='table';", result);
	if (result)
	{
		result->print();
	}

    std::wcout << (LPCTSTR)table[i][j];

	delete sqlite;
    return 0;
}


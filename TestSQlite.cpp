#include "stdafx.h"
#include "TestSQLite.h"

TestSQlite::TestSQlite()
{
	m_dbInstance = NULL;
}

TestSQlite::~TestSQlite()
{
	closeDb();
}

bool TestSQlite::openDb(const char * name)
{
	int ret = sqlite3_open(name, &m_dbInstance);
	return (ret == 0);
}

void TestSQlite::closeDb()
{
	if (m_dbInstance)
	{
		sqlite3_close(m_dbInstance);
		m_dbInstance = NULL;
	}
}

void TestSQlite::processData()
{
	printf("processData is called");
}

void TestSQlite::queryUsingsqlite3_exec(const char * queryString, QueryResult* dataStructResult)
{
	if (dataStructResult == NULL)
	{
		return;
	}
	char *zErrMsg = 0;
	int rc;

	/* Execute SQL statement */
	dataStructResult->reset();
	rc = sqlite3_exec(m_dbInstance, queryString, callback, dataStructResult, &zErrMsg)
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Query successfully\n");
	}
}

//! This callback will be invoked per each row of result
int TestSQlite::callback(void * dataStruct, int argc, char ** argv, char ** azColName)
{
	QueryResult* data = static_cast<QueryResult*>(dataStruct);
	if (data)
	{
		// Get colName only once time
		if (data->collumns.empty())
		{
			for (int i = 0; i < argc; i++)
			{
				data->collumns.push_back(string(azColName[i]));
			}
		}
		// Append record to the dataStruct
		vector<string> record;
		for (int i = 0; i < argc; i++)
		{
			record.push_back(string(argv[i]));
		}
		data->data.push_back(record);

        /*
        https://docs.microsoft.com/en-us/cpp/atl-mfc-shared/cstring-operations-relating-to-c-style-strings?view=vs-2017#_core_using_cstring_as_a_c.2d.style_null.2d.terminated_stringhttps://docs.microsoft.com/en-us/cpp/atl-mfc-shared/cstring-operations-relating-to-c-style-strings?view=vs-2017#_core_using_cstring_as_a_c.2d.style_null.2d.terminated_string
        */
        // wcout << (LPCTSTR)table[i][j];
    }
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <filesystem>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>



#define _CRT_SECURE_NO_WARNINGS

using namespace std;
namespace fs = std::filesystem;
using namespace rapidjson;

string g_filename;
string g_openedFile;

// ini ���Ͽ��� �о�� ���忡�� ���丮 ��ġ�� �߶󳻴� ���ø� �Լ�
vector<string> SplitString(const string& str, const string& delimiter)
{
	vector<string> tokens;

	// size_type ������ ������ ���ص� �ڷ����� ���ֹ��� �ʵ��� �� �ִ� �ڷ���!  unsigned_int or size_t
	string::size_type start = 0;
	string::size_type end = str.find(delimiter);

	while (end != string::npos)
	{
		tokens.push_back(str.substr(start, end - start));
		start = end + delimiter.length();
		end = str.find(delimiter, start);
	}

	tokens.push_back(str.substr(start));

	return tokens;
}

// ��ǻ���� ���丮�� ini ������ �����ϰ� ��θ� �Ҵ��Ѵ�
// ���̿� json ������ �����Ѵ�
void Init()
{
	CreateDirectory("C:\\MyFolder", NULL);
	CreateDirectory("C:\\MyFolder\\MyDirectory", NULL);

	{
		//HANDLE hFile = CreateFile("C:\\MyFolder\\Myfile.ini",
		//	GENERIC_WRITE,
		//	0,
		//	NULL,
		//	CREATE_ALWAYS,
		//	FILE_ATTRIBUTE_NORMAL,
		//	NULL);
		// INI ���� ���

		const char* filePath = "C:\\MyFolder\\Myfile.ini";
		g_filename = filePath;

		// INI ���� ���� (���� ���)
		//FILE* file = fopen(filePath, "w");
		//fclose(file);

		// INI ���Ͽ� ������ ����
		WritePrivateProfileString("Directory", "Route", "C:\\MyFolder\\MyDirectory", filePath);


		// CloseHandle(hFile);
	}

	// ���� json ���� �װ� ����
	{
		HANDLE Dummy1 = CreateFile("C:\\MyFolder\\MyDirectory\\Dummy1.json",
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (Dummy1 != INVALID_HANDLE_VALUE)
		{
			const char* text = "aaa";
			DWORD bytesWritten = 0;

			WriteFile(Dummy1, text, strlen(text), &bytesWritten, NULL);

			CloseHandle(Dummy1);
		}
	}
	{
		HANDLE Dummy2 = CreateFile("C:\\MyFolder\\MyDirectory\\Dummy2.json",
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (Dummy2 != INVALID_HANDLE_VALUE)
		{
			const char* text = "bbb";
			DWORD bytesWritten = 0;

			WriteFile(Dummy2, text, strlen(text), &bytesWritten, NULL);

			CloseHandle(Dummy2);
		}
	}
	{
		HANDLE Dummy3 = CreateFile("C:\\MyFolder\\MyDirectory\\Dummy3.json",
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (Dummy3 != INVALID_HANDLE_VALUE)
		{
			const char* text = "ccc";
			DWORD bytesWritten = 0;

			WriteFile(Dummy3, text, strlen(text), &bytesWritten, NULL);

			CloseHandle(Dummy3);
		}
	}
	{
		HANDLE Dummy4 = CreateFile("C:\\MyFolder\\MyDirectory\\Dummy4.json",
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (Dummy4 != INVALID_HANDLE_VALUE)
		{
			const char* text = "ddd";
			DWORD bytesWritten = 0;

			WriteFile(Dummy4, text, strlen(text), &bytesWritten, NULL);

			CloseHandle(Dummy4);
		}
	}
	{
		HANDLE Dummy5 = CreateFile("C:\\MyFolder\\MyDirectory\\Dummy5.txt",
			GENERIC_WRITE,
			0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (Dummy5 != INVALID_HANDLE_VALUE)
		{
			const char* text = "eee";
			DWORD bytesWritten = 0;

			WriteFile(Dummy5, text, strlen(text), &bytesWritten, NULL);

			CloseHandle(Dummy5);
		}
	}


}

string FindDirectory(const string& filename)
{
	fstream myFile(filename);
	string buffer;
	vector<string> result;

	while (getline(myFile, buffer))
	{
		//cout << buffer << endl;
		result = SplitString(buffer, "=");
	}

	myFile.close();

	return *(result.end() - 1);
}


bool FindJsonFile()
{
	string directory = FindDirectory(g_filename);
	const fs::path directory_path(directory);
	cout << "======================================" << endl;
	cout << "���� ���丮 ���� .json ���� ����Դϴ�." << endl;
	cout << "======================================" << endl;
	cout << endl;

	for (const auto& entry : fs::directory_iterator(directory_path))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".json")
		{
			std::cout << entry.path().filename().string() << std::endl;
		}
	}
	cout << endl;
	return true;
}

void SearchForDataChange()
{
	ifstream prevFile(g_openedFile);
	string prevData;
	getline(prevFile, prevData);
	prevFile.close();


	while (1)
	{
		ifstream nowFile(g_openedFile);
		string nowData;

		if (!nowFile.is_open())
		{
			continue;
		}

		getline(nowFile, nowData);
		nowFile.close();


		if (prevData != nowData)
		{

			cout << "�����Ͱ� �����Ǿ����ϴ�. ������ ��������  �ٽ� ����ұ��? ... (Press SPACE)" << endl;

			auto a = _getch();

			if (a != ' ')
			{
				break;
			}
			cout << endl << "======================================" << endl;
			cout << "�����Ͱ� ������ ���� �����Ǿ����ϴ�." << endl;
			cout << "���� ������ : ";
			cout << prevData << endl;
			cout << "����� ������ : ";
			cout << nowData;
			cout << endl << "======================================" << endl;
			prevData = nowData;
			nowFile.close();
			break;
		}
	}
}

int PrintJsonFile()
{

	string directory = "C:\\MyFolder\\MyDirectory\\";
	cout << "======================================" << endl;
	cout << "�����Ͻ� ���ϸ��� �Է��ϼ��� : ";
	string fileForSearch;
	cin >> fileForSearch;

	string search = directory.append(fileForSearch);
	g_openedFile = search;
	fstream infile(search);
	string buffer;

	if (!infile.is_open())
	{
		cout << "���� ���⿡ �����߽��ϴ�." << endl;
		return 1; // Ȥ�� ���� ó�� ���� �ٸ� ��ġ�� ���� �� �ֽ��ϴ�.
	}

	while (getline(infile, buffer))
	{
		cout << buffer << endl;
	}

	if (infile.eof())
	{
		cout << "======================================" << endl;
		cout << "������ ���������� �о����ϴ�. ������ ��� ���� ������ �����մϴ�... ing" << endl;
		infile.close();
		SearchForDataChange();
	}
	else if (infile.fail())
	{
		cout << "���� �б⿡ �����߽��ϴ�." << endl;
	}

}


int main()
{
	Init();
	while (true)
	{
		FindJsonFile();
		PrintJsonFile();
	}
	return 0;
}
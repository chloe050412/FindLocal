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

// ini 파일에서 읽어온 문장에서 디렉토리 위치만 잘라내는 스플릿 함수
vector<string> SplitString(const string& str, const string& delimiter)
{
	vector<string> tokens;

	// size_type 정수의 범위가 변해도 자료형에 구애받지 않도록 해 주는 자료형!  unsigned_int or size_t
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

// 컴퓨터의 디렉토리에 ini 파일을 생성하고 경로를 할당한다
// 더미용 json 파일을 생성한다
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
		// INI 파일 경로

		const char* filePath = "C:\\MyFolder\\Myfile.ini";
		g_filename = filePath;

		// INI 파일 생성 (쓰기 모드)
		//FILE* file = fopen(filePath, "w");
		//fclose(file);

		// INI 파일에 데이터 쓰기
		WritePrivateProfileString("Directory", "Route", "C:\\MyFolder\\MyDirectory", filePath);


		// CloseHandle(hFile);
	}

	// 더미 json 파일 네개 생성
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
	cout << "현재 디렉토리 내의 .json 파일 목록입니다." << endl;
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

			cout << "데이터가 수정되었습니다. 수정된 내용으로  다시 출력할까요? ... (Press SPACE)" << endl;

			auto a = _getch();

			if (a != ' ')
			{
				break;
			}
			cout << endl << "======================================" << endl;
			cout << "데이터가 다음과 같이 수정되었습니다." << endl;
			cout << "기존 데이터 : ";
			cout << prevData << endl;
			cout << "변경된 데이터 : ";
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
	cout << "열람하실 파일명을 입력하세요 : ";
	string fileForSearch;
	cin >> fileForSearch;

	string search = directory.append(fileForSearch);
	g_openedFile = search;
	fstream infile(search);
	string buffer;

	if (!infile.is_open())
	{
		cout << "파일 열기에 실패했습니다." << endl;
		return 1; // 혹은 예외 처리 등의 다른 조치를 취할 수 있습니다.
	}

	while (getline(infile, buffer))
	{
		cout << buffer << endl;
	}

	if (infile.eof())
	{
		cout << "======================================" << endl;
		cout << "파일을 성공적으로 읽었습니다. 데이터 상시 변경 감지를 시작합니다... ing" << endl;
		infile.close();
		SearchForDataChange();
	}
	else if (infile.fail())
	{
		cout << "파일 읽기에 실패했습니다." << endl;
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
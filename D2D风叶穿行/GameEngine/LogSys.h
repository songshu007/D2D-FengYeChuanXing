#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>

#define DEBUG

class Loger
{
public:
	static Loger* sInstance;
	Loger() 
	{
#ifdef DEBUG
		sInstance = this;
		outFile.open("LogFile.txt", std::ios_base::out);
		outFile << "====================================================================\n";
		printfTime(); outFile << '\n';
#endif // DEBUG
	}
	~Loger() 
	{
#ifdef DEBUG
		outFile.close(); 
#endif
	}
	void printfTime()
	{
#ifdef DEBUG
		SYSTEMTIME t;
		GetLocalTime(&t);
		outFile << "TIME: " << t.wYear << '/' << t.wMonth << '/' << t.wDay << ' ' << t.wHour << ':' << t.wMinute << ':' << t.wSecond ;
#endif
	}
	static void Write(const char* text)
	{ 
#ifdef DEBUG
		sInstance->outFile << text;
#endif
	}
	static void Write(std::string text)
	{ 
#ifdef DEBUG
		sInstance->outFile << text;
#endif
	}
	static void WriteTime()
	{ 
#ifdef DEBUG
		sInstance->printfTime();
#endif
	}

private:
	std::ofstream outFile;
};

class Hresult
{
public:
	Hresult(const char* file, int line) : hr(S_OK), text(file), line(line) {}
	~Hresult() 
	{
	}

	HRESULT operator = (HRESULT vaule)
	{
		hr = vaule;
		std::stringstream ss;
		if (FAILED(hr))
		{
#ifdef DEBUG
			SYSTEMTIME t;
			GetLocalTime(&t);
			ss << "FAILED: " << "  File: " << text << "  Line: " << line << "  Vaule: " << hr << "  [" << t.wHour << ':' << t.wMinute << ':' << t.wSecond << ']' << '\n';
			Loger::Write(ss.str());
#endif
		}
		else
		{
#ifdef DEBUG
			//ss << "SUCCEEDED: " << "  File: " << text << "  Line: " << line << '\n';
			//Loger::Write(ss.str());
#endif
		}
		return *this;
	}

	operator HRESULT()
	{
		return hr;
	}

private:
	HRESULT hr;
	int line;
	const char* text;
};

#define HR Hresult(__FILE__, __LINE__)


#pragma once
#include <string>

using namespace std;

class Logger {
	public:
	static void Print(string text);
	static void Print(double number);
	static void Print(int32 number);
	static void Print(FVector vec);
	private:
	Logger();
	~Logger();
};


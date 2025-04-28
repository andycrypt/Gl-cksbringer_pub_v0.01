#pragma once
//https://stackoverflow.com/questions/9750344/boostasio-winsock-and-winsock-2-compatibility-issue
#include <SDKDDKVer.h>
#include <Windows.h>
#include <winhttp.h>
#include <vector>
#include <utility>
#include <cmath>
#include <string>
#include <mutex>

class web_win {
	struct answr {
		HINTERNET i;
		std::string s;
	};
	HINTERNET hSessionHandle;
	std::vector<HINTERNET> v,vv;
	
	
	//need be static, typeconv error
	static VOID CALLBACK AsyncCallback(HINTERNET hInternet,DWORD_PTR dwContext,DWORD dwInternetStatus,LPVOID lpvStatusInformation,DWORD dwStatusInformationLength);
	inline static std::mutex mx;
public:
	inline static std::vector<answr> inc;
	//void run();
	void go();
	void exit();
	static void read(HINTERNET hi,DWORD dwsize);
	std::pair<double, double> loop_prep(size_t x) {
		double y = static_cast<double>(x) / 10;
		double i;
		double f = std::modf(y, &i); f *= 10;
		return std::make_pair(i, f);
	}
	static void map(HINTERNET hi, std::string s);
};


#pragma once
//#include "fhc.h"
#include <filesystem>
#include <string>
class direct_storage {
public:
	std::string fin(const std::filesystem::path& p);
	void check_hresult(int hr);
};


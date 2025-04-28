#pragma once
#include <vector>
#include <chrono>

class statistics {
	struct Tip {
		std::vector<int> dig, star;
		double tip_cost = 3.5;
		int cnt_tmp = 0, star_tmp = 0;
		double total_cost = 0.0;
		double total_win = 0.0;
	};
	struct Dig {
		std::vector<int> dig;
		int cnt;
	};
	std::vector<Dig> spv, digp, sv, dig, digt;
	std::vector<Tip> tips;
public:
	void count_digits(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to);

	void count_digitpair(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to);
	//cnt 6 = 3,4,5
	void count_digittuple(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to, int cnt);
	
	void count_star(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to);
	
	void count_starpair(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to);
	//from=statistic,pfrom=playtime with statistic,cnt 6 = 3,4,5 ,print stats optional
	void optimize_play_eurmil(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to, const std::chrono::year_month_day& pfrom, const std::chrono::year_month_day& pto, int cnt_tuple, bool print = false);

	//optional print avalible, maybe impl
	void gen_statistic(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to, int cnt_tuple, bool print = false);
	void gen_tip();
};


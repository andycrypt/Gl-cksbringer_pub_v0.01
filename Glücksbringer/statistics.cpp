#include "statistics.h"
#include "datastore.h"
#include "log_msg.h"
#include "conv.h"
#include <ranges>
#include <cassert>
#include <execution>
#include <mutex>

using namespace std;
using namespace chrono;

void statistics::count_digits(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to) {
	for (auto x = 1; x <= 50; x++) {
		dig.push_back(Dig({ x }, 0));
		for (const auto& y : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
			if (ranges::contains(y.wnr, x)) { dig.back().cnt++; }
		}
	}
	ranges::sort(dig, {}, &Dig::cnt);
}

void statistics::count_digitpair(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to) {
	for (auto x = 1; x < 50; x++) {
		for (auto y = x + 1; y <= 50; y++) {
			digp.push_back(Dig({ x,y }, 0));
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.wnr, digp.back().dig)) { digp.back().cnt++; }
			}
		}
	}
	ranges::sort(digp, {}, &Dig::cnt);
}

void statistics::count_digittuple(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to, int cnt) {
	assert(cnt > 2 && cnt <= 6);
	mutex mx;
	if (cnt == 3 || cnt == 6) {
		for (auto x = 1; x < 49; x++) {
			for (auto y = x + 1; y < 50; y++) {
				for (auto yy = y + 1; yy <= 50; yy++) {
					digt.push_back(Dig({ x,y,yy }, 0));
				}
			}
		}
		for_each(std::execution::par, digt.begin(), digt.end(), [&](Dig& x) {
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.wnr, x.dig)) { mx.lock(); x.cnt++; mx.unlock(); }
			}
			});
	}
	if (cnt == 6) {
		ranges::sort(digt, {}, &Dig::cnt);
		cout << "Zahltuple 3" << endl;
		for (const auto& x : digt) { if (x.cnt > 1) { cout << "Zahl: "; for (const auto& y : x.dig) { cout << y << " "; } cout << "cnt: " << x.cnt << endl; } }
	}
	if (cnt == 4) {
		for (auto x = 1; x < 48; x++) {
			for (auto y = x + 1; y < 49; y++) {
				for (auto yy = y + 1; yy < 50; yy++) {
					for (auto yyy = yy + 1; yyy <= 50; yyy++) {
						digt.push_back(Dig({ x,y,yy,yyy }, 0));
					}
				}
			}
		}
		for_each(std::execution::par, digt.begin(), digt.end(), [&](Dig& x) {
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.wnr, x.dig)) { mx.lock(); x.cnt++; mx.unlock(); }
			}
		});
	}
	if (cnt == 6) {
		for (auto& x : digt) {
			x.cnt = 0;
			auto tmp = x.dig.back();
			if (tmp < 50) { x.dig.push_back(tmp + 1); }
		}
		for_each(std::execution::par, digt.begin(), digt.end(), [&](Dig& x) {
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.wnr, x.dig)) { mx.lock(); x.cnt++; mx.unlock(); }
			}
		});
		ranges::sort(digt, {}, &Dig::cnt);
		cout << "Zahltuple 4" << endl;
		for (const auto& x : digt) { if (x.cnt > 1) { cout << "Zahl: "; for (const auto& y : x.dig) { cout << y << " "; } cout << "cnt: " << x.cnt << endl; } }
	}
	if (cnt == 5) {
		for (auto x = 1; x < 47; x++) {
			for (auto y = x + 1; y < 48; y++) {
				for (auto yy = y + 1; yy < 49; yy++) {
					for (auto yyy = yy + 1; yyy < 50; yyy++) {
						for (auto yyyy = yyy + 1; yyyy <= 50; yyyy++) {
							digt.push_back(Dig({ x,y,yy,yyy,yyyy }, 0));
						}
					}
				}
			}
		}
		for_each(std::execution::par, digt.begin(), digt.end(), [&](Dig& x) {
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.wnr, x.dig)) { mx.lock(); x.cnt++; mx.unlock(); }
			}
		});
	}
	if (cnt == 6) {
		for (auto& x : digt) {
			x.cnt = 0;
			auto tmp = x.dig.back();
			if (tmp < 50) { x.dig.push_back(tmp + 1); }
		}
		for_each(std::execution::par, digt.begin(), digt.end(), [&](Dig& x) {
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.wnr, x.dig)) { mx.lock(); x.cnt++; mx.unlock(); }
			}
		});
		ranges::sort(digt, {}, &Dig::cnt);
		cout << "Zahltuple 5" << endl;
		for (const auto& x : digt) { if (x.cnt > 1) { cout << "Zahl: "; for (const auto& y : x.dig) { cout << y << " "; } cout << "cnt: " << x.cnt << endl; } }

	}
	else {
		ranges::sort(digt, {}, &Dig::cnt);
	}
}


void statistics::count_star(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to) {
	for (auto x = 1; x <= 12; x++) {
		sv.push_back(Dig({ x }, 0));
		for (const auto& y : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
			if (ranges::contains(y.star, x)) { sv.back().cnt++; }
		}
	}
	ranges::sort(sv, {}, &Dig::cnt);
}

void statistics::count_starpair(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to) {
	for (auto x = 1; x < 12; x++) {
		for (auto y = x+1; y <= 12; y++) {
			spv.push_back(Dig({ x,y }, 0));
			for (const auto& z : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(from), d->eurmil.begin() + Euromillions::get_pd(to))) {
				if (ranges::includes(z.star, spv.back().dig)) { spv.back().cnt++; }
			}
		}
	}
	ranges::sort(spv, {}, &Dig::cnt);
}

void statistics::optimize_play_eurmil(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to, const std::chrono::year_month_day& pfrom, const std::chrono::year_month_day& pto, int cnt_tuple, bool print) {
	//std::chrono::system_clock::time_point tmptp = std::chrono::system_clock::now();
	gen_statistic(from, to, cnt_tuple,print);
	gen_tip();
	//Logerr::log_elapsedtime(to_string(datetime::get_sec(tmptp)));
	int tip = tips.size();
	int cnt_tip = 0; 
	double sum = 0, wsum = 0;
	for (const auto& x : ranges::subrange(d->eurmil.begin() + Euromillions::get_pd(pfrom), d->eurmil.begin() + Euromillions::get_pd(pto))) {
		cnt_tip++;
		for (auto& y : tips) {
			y.total_cost += y.tip_cost;
			for (const auto& z : y.dig) {
				if (ranges::contains(x.wnr, z)) { y.cnt_tmp++; }
			}
			for (const auto& z : y.star) {
				if (ranges::contains(x.star, z)) { y.star_tmp++; }
			}
			if (y.cnt_tmp > 1) {
				if (y.star_tmp > 0) {
					string str_tmp = to_string(y.cnt_tmp);
					str_tmp.append("+");
					str_tmp.append(to_string(y.star_tmp));
					for (const auto& z : x.wintbl) {
						if (z.nr_hit == str_tmp) { y.total_win += z.win; break; }
					}
				}
				else {
					string str_tmp = to_string(y.cnt_tmp);
					for (const auto& z : x.wintbl) {
						if (z.nr_hit == str_tmp) { y.total_win += z.win; break; }
					}
				}
			}
			y.cnt_tmp = 0; y.star_tmp = 0;
		}
	}
	
	cout << "Auswertung Tips" << endl;
	for (const auto& x : tips) { 
		cout << "Zahl: ";
		sum += x.total_cost; wsum += x.total_win;
		for (const auto& y : x.dig) {
			cout << y << " ";
		}
		cout << "Stern: ";
		for (const auto& y : x.star) {
			cout << y << " ";
		}
		cout << "Anzahl gespielte Tips: " << cnt_tip << " Ausgaben: " << x.total_cost << " Einnahmen: " << x.total_win << endl;
	}
	cout << "Summiertes Total Tips: " << cnt_tip * tip << " Total Ausgaben: " << sum << " Total Einnahmen: " << wsum << endl;
	
	
	/*
	digt.clear();
	spv.clear();
	sv.clear();
	digp.clear();
	dig.clear();*/ // maybe later change, atm no need to clean
}

void statistics::gen_statistic(const std::chrono::year_month_day& from, const std::chrono::year_month_day& to, int cnt_tuple, bool print) {
	count_digits(from, to);
	count_digitpair(from, to);
	count_starpair(from, to);
	count_star(from, to);
	count_digittuple(from, to, cnt_tuple);
	
	if (print) {
		cout << "Zahl Anzahl" << endl;
		for (const auto& x : dig) { cout << "Zahl: " << x.dig.back() << " cnt: " << x.cnt << endl; }

		cout << "Zahlenpaar Anzahl" << endl;
		for (const auto& x : digp) { if (x.cnt > 1) { cout << "Zahl: " << x.dig.front() << " " << x.dig.back() << " cnt: " << x.cnt << endl; } }

		cout << "Stern Anzahl" << endl;
		for (const auto& x : sv) { cout << "Stern: " << x.dig.back() << " cnt: " << x.cnt << endl; }

		cout << "Sternpaar Anzahl" << endl;
		for (const auto& x : spv) { if (x.cnt > 1) { cout << "Stern: " << x.dig.front() << " " << x.dig.back() << " cnt: " << x.cnt << endl; } }
		if (cnt_tuple != 6) {
			cout << "Zahltuple " << cnt_tuple << endl;
			for (const auto& x : digt) { if (x.cnt > 1) { cout << "Zahl: "; for (const auto& y : x.dig) { cout << y << " "; } cout << "cnt: " << x.cnt << endl; } }
		}
	}
	
	
}

void statistics::gen_tip() {
	vector<int> a, b;
	auto cnt = -2;
	for (const auto& x : views::reverse(dig) | views::take(5)) { a.push_back(x.dig.back()); }
	for (const auto& x : views::reverse(sv) | views::take(2)) { b.push_back(x.dig.back()); }
	ranges::sort(a);
	ranges::sort(b);
	tips.push_back(Tip(a, b));
	//-->need chk if digit allready exist
	
	a = digt.back().dig;
	a.append_range(digp.back().dig);
	b = spv.back().dig;
	ranges::sort(a);
	tips.push_back(Tip(a, b));
	a = digt[digt.size()-2].dig;
	a.append_range(digp[digp.size()-2].dig);
	b = spv[spv.size()-2].dig;
	ranges::sort(a);
	tips.push_back(Tip(a, b));
}


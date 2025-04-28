// Glücksbringer.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include "Glücksbringer.h"

#include <chrono>
#include "netw.h"
#include <filesystem>
#include "cassert"

using namespace std;
using namespace chrono;



void Glücksbringer::start() {
    assert(d->eurmil.size() > 0);
    auto cnt = d->eurmil.size();
    if (filesystem::exists(d->wrklst)) { Fhc::rm(d->wrklst); } // --> need a cleanup function, corrupt json&html files possible -->rm(read wrklist) --> folder logic work/db
    if (!filesystem::exists(d->dslist)) {
        year_month_day to = datetime::ymdret_today();
        year_month_day from = d->eurmil.back().ymd;
        datetime::clk(datetime::ymdret_addday(from, 1), datetime::ymdret_addday(to, -1));
    }
    else {
        ifstream in{ d->dslist,in.in };
        if (!in.is_open()) {
            Logerr::log_msg("dslist open err");
            //Logerr::log_msg(to_string(GetLastError())); //need win.h
        }
        for (string line; getline(in, line);) {
            Euromillions::web_tgt(datetime::ymdret(line));
        }
        in.close();
        Fhc::rm(d->dslist);
    }
    web::web_euromilnew();
    parse::jsonfparse(false);
    Fhc::rm(d->wrklst);
    if (cnt != d->eurmil.size()) {
        parse::wout_euromil(false, cnt);
    }
}

int main()
{
    Glücksbringer g;
    g.eurm_mod();
    //g.eurodream();
    //g.swiss();  
    
    g.optimize_play_eurmil(1d / 1 / 2024, 31d / 12 / 2024, 1d / 1 / 2025, datetime::ymdret_addday(datetime::ymdret_today(), -1),3,true);
    //g.casheurm2({4,19,23,35,37},{4,8},100);
   
}



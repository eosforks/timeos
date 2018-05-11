#include "timeos.hpp"

namespace timeos {

   void timeos::createts(const account_name owner, const std::string &data) {
      eosio::require_auth(owner);
      time t = now();
      timestamps ts_table(get_self(), owner);
      ts_table.emplace(owner, [&](timestamp& ts) {
         ts.pkey = ts_table.available_primary_key();
         ts.time = t;
         ts.data = data;
      });
//      eosio::print("Data: ", data, " timestamped at: ", t);
   }

   void timeos::getts(account_name owner) {
      timestamps ts_table(get_self(), owner);
      auto index = ts_table.get_index<N(reverse)>();
      eosio::print(index.begin()->data.c_str());
//      for (auto it = index.begin(); it != index.end(); it++) {
//         eosio::print(it->time);
//      }
   }

   void timeos::removets(const account_name owner, const uint64_t pkey) {

   }

   EOSIO_ABI( timeos, (createts)(removets)(getts) )
}


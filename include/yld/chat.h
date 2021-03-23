#ifndef YT_CHAT_H
#define YT_CHAT_H

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace yld {

	class Chat {
		private:
			unsigned long timeEnd;
			unsigned long timeStart;
			string* response;
			
		public:
			Chat(string &continuation, unsigned long &start, unsigned long &end);
	};

}

#endif
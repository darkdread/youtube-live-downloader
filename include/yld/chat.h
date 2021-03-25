#ifndef YT_CHAT_H
#define YT_CHAT_H

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "chatresponse.h"

using namespace std;
using json = nlohmann::json;

namespace yld {

	class Chat {
		private:
			unsigned long m_timeEnd;
			unsigned long m_timeStart;
			std::string* response;
			
			ChatResponse BuildChatResponseFromString(std::string &p_json);
			ChatResponse SendChatRequest(std::string &continuation, std::string &innertube_key, unsigned long &start);

		public:
			Chat(std::string &continuation, std::string &innertube_key, unsigned long &start, unsigned long &end);
	};

}

#endif
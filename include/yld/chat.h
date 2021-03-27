#ifndef YT_CHAT_H
#define YT_CHAT_H

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "chatresponse.h"

using namespace std;

namespace yld {

	class Chat {
		private:
			unsigned long m_timeEnd;
			unsigned long m_timeStart;
			std::string * m_rawResponse;

			ChatResponse BuildChatResponseFromString(std::string &p_json);
			ChatResponse SendChatRequest(std::string &continuation, std::string &innertube_key, unsigned long &start);

		public:
			ChatResponse m_response;
			Chat(std::string &continuation, std::string &innertube_key, unsigned long &start, unsigned long &end);
			void OutputToFile(std::string &filepath){
				ofstream opFile;
				opFile.open(filepath);

				nlohmann::json j;
				ChatResponse::to_json(j, m_response);

				opFile << j;
				opFile.close();
			}
	};

}

#endif
#ifndef YT_CHAT_H
#define YT_CHAT_H

#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "chatresponse.h"

using namespace std;

namespace yld {

	class Chat {
		public:
			std::vector<ChatResponse> m_responses;
			Chat(std::string &continuation, std::string &innertube_key, unsigned long &start, unsigned long &end);
			static Chat FromVideoId(std::string &youtubeId, unsigned long &start, unsigned long &end);
			static void OutputToFile(std::string &filePath, std::string &text){
				ofstream opFile;
				opFile.open(filePath);

				opFile << text;
				opFile.close();
			}

		private:
			const unsigned long OFFSET_START = 0;
			unsigned long m_timeEnd;
			unsigned long m_timeStart;
			std::string * m_rawResponse;

			ChatResponse buildChatResponseFromString(std::string &p_json);
			ChatResponse sendChatRequest(std::string &continuation, std::string &innertube_key, unsigned long &start);
	};

}

#endif
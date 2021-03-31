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
			const unsigned long OFFSET_START = 0;
			unsigned long m_timeEnd;
			unsigned long m_timeStart;
			std::string * m_rawResponse;

			ChatResponse BuildChatResponseFromString(std::string &p_json);
			ChatResponse SendChatRequest(std::string &continuation, std::string &innertube_key, unsigned long &start);

		public:
			std::vector<ChatResponse> m_responses;
			static Chat FromVideoId(std::string &youtubeId, unsigned long &start, unsigned long &end);
			Chat(std::string &continuation, std::string &innertube_key, unsigned long &start, unsigned long &end);
			static void OutputToFile(std::string &filePath, std::string &text){
				ofstream opFile;
				opFile.open(filePath);

				opFile << text;
				opFile.close();
			}
	};

}

#endif
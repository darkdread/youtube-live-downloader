#ifndef YT_CHAT_RESPONSE_H
#define YT_CHAT_RESPONSE_H
#endif

#include <iostream>
#include "chatreplayitem.h"

using namespace std;

namespace yld {

    class ChatResponse {
		public:
			std::string* m_rawResponse;
			std::string m_continuation;
			unsigned long long* m_lastMessageTime;
			std::vector<ChatReplayItem>* m_chatReplayItems;
			
	};

}
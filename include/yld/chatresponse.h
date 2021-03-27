#ifndef YT_CHAT_RESPONSE_H
#define YT_CHAT_RESPONSE_H
#endif

#include <iostream>
#include "chatreplayitem.h"

using namespace std;

namespace yld {

    class ChatResponse {

		public:
			std::string m_rawResponse;
			std::string m_continuation;
			unsigned long long m_lastMessageTime;
			std::vector<ChatReplayItem> m_chatReplayItems;

			ChatResponse(){};

			ChatResponse(std::string & p_rawResponse, std::string & p_continuation,
							unsigned long long & p_lastMessageTime, std::vector<ChatReplayItem> & p_chatReplayItems){
							m_rawResponse = p_rawResponse;
							m_continuation = p_continuation;
							m_lastMessageTime = p_lastMessageTime;
							m_chatReplayItems = p_chatReplayItems;
						}

			static void to_json(nlohmann::json & j, const ChatResponse & resp){
				nlohmann::json chatReplayJson;
				ChatReplayItem::to_json(chatReplayJson, resp.m_chatReplayItems);

				j = nlohmann::json {
					// {"rawResponse", resp.m_rawResponse},
					{"continuation", resp.m_continuation},
					{"lastMessageTime", resp.m_lastMessageTime},
					{"chatReplayItems", chatReplayJson}
				};
			}

			static void from_json(nlohmann::json & j, ChatResponse & resp){
				j.at("continuation").get_to(resp.m_continuation);
				j.at("lastMessageTime").get_to(resp.m_lastMessageTime);

				ChatReplayItem::from_json(j, resp.m_chatReplayItems);
			}
	};

}
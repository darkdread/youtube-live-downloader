#ifndef YT_CHAT_RESPONSE_H
#define YT_CHAT_RESPONSE_H

#include <fstream>
#include "chatreplayitem.h"

using namespace std;

namespace yld {

    class ChatResponse {

		public:
			std::string m_rawResponse;
			std::string m_continuation;
			unsigned long m_lastMessageTime;
			std::vector<ChatReplayItem> m_chatReplayItems;

			ChatResponse(){};

			ChatResponse(std::string & p_rawResponse, std::string & p_continuation,
							unsigned long & p_lastMessageTime, std::vector<ChatReplayItem> & p_chatReplayItems){
							m_rawResponse = p_rawResponse;
							m_continuation = p_continuation;
							m_lastMessageTime = p_lastMessageTime;
							m_chatReplayItems = p_chatReplayItems;
						}

			static void BuildChatReplayItems(const std::vector<ChatResponse> &responses, std::vector<ChatReplayItem> &item){
				for(int i = 0; i < responses.size(); i++){
					ChatResponse r = responses[i];
					item.insert(item.end(), r.m_chatReplayItems.begin(), r.m_chatReplayItems.end());
				}
			}

			static void ReadFileToChatResponses(const std::string & filePath, std::vector<ChatResponse> & responses){
				std::ifstream opFile(filePath);
				std::stringstream buffer;
        		buffer << opFile.rdbuf();

				nlohmann::json j = nlohmann::json::parse(buffer.str());
				ChatResponse::from_json(j, responses);
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

			static void to_json(nlohmann::json & j, const std::vector<ChatResponse> & resp){
				nlohmann::json chatResponseJson;

				for (const ChatResponse r : resp){
					ChatResponse::to_json(chatResponseJson, r);
					j.push_back(chatResponseJson);
				}
			}

			static void from_json(const nlohmann::json & j, ChatResponse & resp){
				j.at("continuation").get_to(resp.m_continuation);
				j.at("lastMessageTime").get_to(resp.m_lastMessageTime);

				ChatReplayItem::from_json(j, resp.m_chatReplayItems);
			}

			static void from_json(const nlohmann::json & j, std::vector<ChatResponse> & resps){
				for (int i = 0; i < j.size(); i++){
					nlohmann::json jj = j[i];
					ChatResponse chatResponse;

					ChatResponse::from_json(jj, chatResponse);
					resps.push_back(chatResponse);
				}
			}
	};

}

#endif
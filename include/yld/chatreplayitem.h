#ifndef YT_CHAT_REPLAY_ITEM_H
#define YT_CHAT_REPLAY_ITEM_H

#include <nlohmann/json.hpp>
#include <iostream>

using namespace std;

namespace yld {

    class ChatReplayItem {
		public:
            enum class chat_replay_t:char {
				normal = 1,
				paid = 2,
				membership = 4
			};

            chat_replay_t m_responseType;
			std::vector<string> m_text;
			std::string m_author;
            std::string m_authorThumbnail;
			unsigned long m_messageTime;

            ChatReplayItem(){}

            ChatReplayItem(std::vector<string> & p_text, std::string & p_author, std::string & p_authorThumbnail, unsigned long & p_messageTime){
                m_text = p_text;
                m_author = p_author;
                m_authorThumbnail = p_authorThumbnail;
                m_messageTime = p_messageTime;
            }

            std::string BuildMessage() const{
                if (m_text.size() == 0){
                    return "";
                }

                return m_text[0];
            }

            static void to_json(nlohmann::json & j, const std::vector<ChatReplayItem> & chatReplayItems){
                nlohmann::json replayItems = nlohmann::json::array();
                for (int i = 0; i < chatReplayItems.size(); i++){
                    nlohmann::json itemJson;

                    to_json(itemJson, chatReplayItems[i]);
                    replayItems.push_back(itemJson);
                }

                j = replayItems;
            }

            static void to_json(nlohmann::json & j, const ChatReplayItem & chatReplayItem){
                j = nlohmann::json {
                    {"responseType", chatReplayItem.m_responseType},
                    {"text", chatReplayItem.BuildMessage()},
                    {"author", chatReplayItem.m_author},
                    {"authorThumbnail", chatReplayItem.m_authorThumbnail},
                    {"messageTime", chatReplayItem.m_messageTime}
                };
            }

            static void from_json(nlohmann::json & j, ChatReplayItem & chatReplayItem){

                j.at("messageTime").get_to(chatReplayItem.m_messageTime);
                j.at("authorThumbnail").get_to(chatReplayItem.m_authorThumbnail);
                j.at("author").get_to(chatReplayItem.m_author);
                j.at("responseType").get_to(chatReplayItem.m_responseType);

                chatReplayItem.m_text.push_back(j.at("text"));
            }

            static void from_json(const nlohmann::json & j, std::vector<ChatReplayItem> & chatReplayItems){

                for (int i = 0; i < j["chatReplayItems"].size(); i++){
                    nlohmann::json jsonReplayItem = j["chatReplayItems"][i];
                    ChatReplayItem replayItem;

                    from_json(jsonReplayItem, replayItem);
					chatReplayItems.push_back(replayItem);
				}
            }
	};

}

#endif
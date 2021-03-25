#ifndef YT_CHAT_REPLAY_ITEM_H
#define YT_CHAT_REPLAY_ITEM_H
#endif

#include <iostream>

using namespace std;

namespace yld {

    class ChatReplayItem {
		public:
			std::vector<string>* m_text;
			std::string* m_author;
            std::string* m_authorThumbnail;
			unsigned long long* m_messageTime;

            ChatReplayItem(){}

            ChatReplayItem(std::vector<string> &p_text, std::string &p_author, std::string &p_authorThumbnail, unsigned long long &p_messageTime){
                m_text = &p_text;
                m_author = &p_author;
                m_authorThumbnail = &p_authorThumbnail;
                m_messageTime = &p_messageTime;
            }

            std::string BuildMessage(){
                std::vector<std::string>& addr = *m_text;
                return addr[0];
            }
			
	};

}
#include <yld/chat.h>
#include <fstream>

namespace yld {

    ChatResponse Chat::BuildChatResponseFromString(std::string &p_json){
        ChatResponse chatResponse;
        json j = json::parse(p_json);

        std::vector<ChatReplayItem> chatReplayItems(j["continuationContents"]["liveChatContinuation"]["actions"].size());
        for (int i = 0; i < j["continuationContents"]["liveChatContinuation"]["actions"].size(); i++){
            json item = j["continuationContents"]["liveChatContinuation"]["actions"][i]["replayChatItemAction"]["actions"];

            std::string author = item[0]["addChatItemAction"]["item"]["liveChatTextMessageRenderer"]["authorName"]["simpleText"];
            std::string thumbnail = item[0]["addChatItemAction"]["item"]["liveChatTextMessageRenderer"]["authorPhoto"]["thumbnails"][0]["url"];
            std::string ts = item[0]["addChatItemAction"]["item"]["liveChatTextMessageRenderer"]["timestampUsec"];
            std::vector<string> message;

            for (int k = 0; k < item[0]["addChatItemAction"]["item"]["liveChatTextMessageRenderer"]["message"]["runs"].size(); k++){
                json messageItem = item[0]["addChatItemAction"]["item"]["liveChatTextMessageRenderer"]["message"]["runs"][k];

                if (messageItem["text"].is_string()){
                    message.push_back(messageItem["text"]);
                } else if (messageItem["emoji"].is_object()){
                    message.push_back(messageItem["emoji"]["shortcuts"][0]);
                }

            }

            unsigned long long timestamp = std::stoull(ts);

            ChatReplayItem cItem {
                message, author, thumbnail, timestamp
            };

            chatReplayItems[i] = cItem;
        }

        chatResponse.m_lastMessageTime = chatReplayItems[chatReplayItems.size() - 1].m_messageTime;
        chatResponse.m_continuation = j["continuationContents"]["liveChatContinuation"]["continuations"][0]["liveChatReplayContinuationData"]["continuation"];
        chatResponse.m_rawResponse = &p_json;
        chatResponse.m_chatReplayItems = &chatReplayItems;

        return chatResponse;
    }

    ChatResponse Chat::SendChatRequest(std::string &continuation, std::string &innertube_key, unsigned long &start){
        json j = {
            {"context", {
                {"client", {
                    {"clientName", "WEB"},
                    {"clientVersion", "2.20210318.08.00"},
                }},
            }},
            {"continuation", continuation},
            {"currentPlayerState", {
                {"playerOffsetMs", start}
            }}
        };

        cpr::Response r = cpr::Post(cpr::Url{"https://www.youtube.com/youtubei/v1/live_chat/get_live_chat_replay?key=" + innertube_key},
                            cpr::Header{{"Content-Type", "application/json"}},
                            cpr::Body(j.dump()));

        response = &r.text;
        return BuildChatResponseFromString(*response);
    }


    Chat::Chat(std::string &continuation, std::string &innertube_key, unsigned long &start, unsigned long &end)
    {
        m_timeStart = start;
        m_timeEnd = end;

        // SendChatRequest(continuation, innertube_key, start);
        std::ifstream t("timestamp0.json");
        std::stringstream buffer;
        buffer << t.rdbuf();

        std::string jsonString = buffer.str();
        ChatResponse r = BuildChatResponseFromString(jsonString);
        
        cout << *r.m_rawResponse << endl;
    }

}

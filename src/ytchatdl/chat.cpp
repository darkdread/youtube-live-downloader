#include <yld/chat.h>
#include <fstream>
#include <regex>

namespace yld {

    ChatResponse Chat::buildChatResponseFromString(std::string &p_json){
        ChatResponse chatResponse;
        nlohmann::json j = nlohmann::json::parse(p_json);

        std::vector<ChatReplayItem> chatReplayItems;
        for (int i = 0; i < j["continuationContents"]["liveChatContinuation"]["actions"].size(); i++){
            nlohmann::json item = j["continuationContents"]["liveChatContinuation"]["actions"][i]["replayChatItemAction"]["actions"][0]["addChatItemAction"]["item"];
            ChatReplayItem::chat_replay_t responseType = ChatReplayItem::chat_replay_t::normal;

            if (!item["liveChatTextMessageRenderer"].is_null()){
                item = item["liveChatTextMessageRenderer"];
            } else if (!item["liveChatMembershipItemRenderer"].is_null()){
                responseType = ChatReplayItem::chat_replay_t::membership;
                item = item["liveChatMembershipItemRenderer"];
            } else {
                continue;
            }

            std::string author = item["authorName"]["simpleText"];
            std::string thumbnail = item["authorPhoto"]["thumbnails"][0]["url"];
            std::string ts = j["continuationContents"]["liveChatContinuation"]["actions"][i]["replayChatItemAction"]["videoOffsetTimeMsec"];
            std::vector<string> message;

            for (int k = 0; k < item["message"]["runs"].size(); k++){
                nlohmann::json messageItem = item["message"]["runs"][k];

                if (messageItem["text"].is_string()){
                    message.push_back(messageItem["text"]);
                } else if (messageItem["emoji"].is_object()){
                    message.push_back(messageItem["emoji"]["shortcuts"][0]);
                } else {
                    message.push_back(messageItem.dump());
                }
            }

            unsigned long timestamp = std::stoul(ts);

            ChatReplayItem cItem {
                message, author, thumbnail, timestamp
            };

            cItem.m_responseType = responseType;

            chatReplayItems.push_back(cItem);
        }

        chatResponse.m_lastMessageTime = chatReplayItems[chatReplayItems.size() - 1].m_messageTime;
        chatResponse.m_continuation = j["continuationContents"]["liveChatContinuation"]["continuations"][0]["liveChatReplayContinuationData"]["continuation"].get<std::string>();
        chatResponse.m_rawResponse = p_json;
        chatResponse.m_chatReplayItems = chatReplayItems;

        return chatResponse;
    }

    ChatResponse Chat::sendChatRequest(std::string & continuation, std::string & innertube_key, unsigned long & start){
        nlohmann::json j = {
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

        m_rawResponse = &r.text;
        return buildChatResponseFromString(*m_rawResponse);
    }


    Chat::Chat(std::string & continuation, std::string & innertube_key, unsigned long & start, unsigned long & end)
    {
        m_timeStart = start;
        m_timeEnd = end;

        // Send requests
        unsigned long startOffset = start;
        std::vector<ChatResponse> responses;
        ChatResponse r = sendChatRequest(continuation, innertube_key, startOffset);
        do {
            // End of video.
            if (r.m_lastMessageTime == startOffset){
                break;
            }
            startOffset = r.m_lastMessageTime + OFFSET_START;
            responses.push_back(r);
            r = sendChatRequest(continuation, innertube_key, startOffset);
        } while(r.m_lastMessageTime < end);

        m_responses = responses;

        // // Read youtube response
        // std::ifstream t("documentation/timestamp99999.json");
        // std::stringstream buffer;
        // buffer << t.rdbuf();

        // std::string jsonString = buffer.str();
        // ChatResponse r = BuildChatResponseFromString(jsonString);
    }

    Chat Chat::FromVideoId(std::string & youtubeId, unsigned long &start, unsigned long &end){
        cpr::Response r = cpr::Get(cpr::Url{"https://www.youtube.com/watch?v=" + youtubeId});
        std::string resp = r.text;

        std::regex rYtInitialData("ytInitialData\\s?=\\s?(\\{[\\s\\S]*?(?=\\};))");
        std::regex rYtInitialPlayerResp("ytInitialPlayerResponse\\s?=\\s?(\\{[\\s\\S]*?(?=\\};))");
        std::regex rInnertubeApiKey("INNERTUBE_API_KEY\":\\s?\"(.+?)\"");
        std::smatch rmYtInitialPlayerResp;
        std::smatch rmYtInitialData;
        std::smatch rmInnertubeApiKey;

        // std::string out = "test_" + youtubeId + ".html";
        // Chat::OutputToFile(out, resp);

        // std::ifstream t("test.html");
        // std::stringstream buffer;
        // buffer << t.rdbuf();
        // std::string resp = buffer.str();

        if (!std::regex_search(resp, rmYtInitialPlayerResp, rYtInitialPlayerResp)){
            throw std::runtime_error("ytInitialPlayerResponse not found");
        }

        if (!std::regex_search(resp, rmYtInitialData, rYtInitialData)){
            throw std::runtime_error("ytInitialData not found");
        }

        if (!std::regex_search(resp, rmInnertubeApiKey, rInnertubeApiKey)){
            throw std::runtime_error("InnertubeApiKey not found");
        }

        std::string str2 = rmYtInitialData[1].str() + "}";
        nlohmann::json ytInitialData = nlohmann::json::parse(str2);
        if (ytInitialData["contents"]["twoColumnWatchNextResults"]["conversationBar"].is_null()){
            throw std::runtime_error("Not vod video (probably)");
        }
        std::string continuation = ytInitialData["contents"]["twoColumnWatchNextResults"]["conversationBar"]
                                                ["liveChatRenderer"]["continuations"][0]["reloadContinuationData"]["continuation"];

        std::string str1 = rmYtInitialPlayerResp[1].str() + "}";
        nlohmann::json ytInitialPlayerResponse = nlohmann::json::parse(str1);
        unsigned long videoLength = std::stoul(ytInitialPlayerResponse["streamingData"]["formats"][0]["approxDurationMs"].get<std::string>());

        std::string innertubeApiKey = rmInnertubeApiKey[1];

        Chat c{continuation, innertubeApiKey, start, end};
        return c;
    }

}

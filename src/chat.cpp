#include <yld/chat.h>

namespace yld {

    Chat::Chat(string &continuation, unsigned long &start, unsigned long &end)
    {
        timeStart = start;
        timeEnd = end;

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

        cpr::Response r = cpr::Post(cpr::Url{"https://www.youtube.com/youtubei/v1/live_chat/get_live_chat_replay?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8"},
                            // cpr::Body
                            cpr::Header{{"Content-Type", "application/json"}},
                            cpr::Body(j.dump()));

        response = &r.text;
    }

}

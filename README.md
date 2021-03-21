# Prerequisites

* [clang](https://clang.llvm.org/)
* [Code-LLVM](https://github.com/vadimcn/vscode-lldb)

# Youtube Live Chat API


| Key                            | Remarks                 |
|--------------------------------|-------------------------|
| liveChatTextMessageRenderer    | Normal message by user. |
| liveChatPaidMessageRenderer    | Paid message by user.   |
| liveChatMembershipItemRenderer | New subscription.       |
|                                |                         |


## Example Normal Message

```json
"replayChatItemAction": {
    "actions": [
        {
        "addChatItemAction": {
            "item": {
            "liveChatTextMessageRenderer": {
                "message": {
                "runs": [
                    {
                    "text": "KEKE"
                    }
                ]
                },
                "authorName": {
                "simpleText": "Tsuki"
                },
                "authorPhoto": {
                "thumbnails": [
                    {
                    "url": "https://yt4.ggpht.com/ytc/AAUvwnjzI7VcrdxxPv-r908xzTKWqiix_ezXJ9wNVbxWHUQ=s32-c-k-c0x00ffffff-no-rj",
                    "width": 32,
                    "height": 32
                    },
                    {
                    "url": "https://yt4.ggpht.com/ytc/AAUvwnjzI7VcrdxxPv-r908xzTKWqiix_ezXJ9wNVbxWHUQ=s64-c-k-c0x00ffffff-no-rj",
                    "width": 64,
                    "height": 64
                    }
                ]
                },
                "contextMenuEndpoint": {
                "commandMetadata": {
                    "webCommandMetadata": {
                    "ignoreNavigation": true
                    }
                },
                "liveChatItemContextMenuEndpoint": {
                    "params": "Q2tjS1JRb2FRMDFFVVhCaFVFeDJUemhEUmxFNFJYSlJXV1JLUVVWTlIzY1NKME5QVEZjdGNGaE1kazg0UTBaWWJGRm9VVzlrTURSUlFYVkJNVFl4TmpFMk5EZzJNREUyTmhvcEtpY0tHRlZEUlZsQlZTMXlaMTlqWmxaeU1tUk9iVk5mUVRGNFVSSUxRVGc0Ykd3NUxWcDNhazBnQVNnRU1ob0tHRlZETWxZek5FMXlaakpaUWpsNWNrOUNZMDR6Ymw5U2R3JTNEJTNE"
                }
                },
                "id": "CkUKGkNNRFFwYVBMdk84Q0ZROEVyUVlkSkFFTUd3EidDT0xXLXBYTHZPOENGWGxRaFFvZDA0UUF1QTE2MTYxNjQ4NjAxNjY%3D",
                "timestampUsec": "1616164860553335",
                "authorExternalChannelId": "UC2V34Mrf2YB9yrOBcN3n_Rw",
                "contextMenuAccessibility": {
                "accessibilityData": {
                    "label": "Comment actions"
                }
                },
                "timestampText": {
                "simpleText": "40:55"
                }
            }
            },
            "clientId": "COLW-pXLvO8CFXlQhQod04QAuA1616164860166"
        }
        }
    ],
    "videoOffsetTimeMsec": "2455068"
}
```

---

## Example Paid Message

```json
"replayChatItemAction": {
    "actions": [
        {
        "addLiveChatTickerItemAction": {
            "item": {
            "liveChatTickerPaidMessageItemRenderer": {
                "id": "ChwKGkNOT193ZXpLdk84Q0ZRbXJ3UW9kWGlZSTJB",
                "amount": {
                "simpleText": "€10.00"
                },
                "amountTextColor": 3741319168,
                "startBackgroundColor": 4294953512,
                "endBackgroundColor": 4294947584,
                "authorPhoto": {
                "thumbnails": [
                    {
                    "url": "https://yt4.ggpht.com/ytc/AAUvwngGfTCNawQXGrVgn1cm9_HKQpmtudgEtpwwFQ=s32-c-k-c0x00ffffff-no-rj",
                    "width": 32,
                    "height": 32
                    },
                    {
                    "url": "https://yt4.ggpht.com/ytc/AAUvwngGfTCNawQXGrVgn1cm9_HKQpmtudgEtpwwFQ=s64-c-k-c0x00ffffff-no-rj",
                    "width": 64,
                    "height": 64
                    }
                ],
                "accessibility": {
                    "accessibilityData": {
                    "label": "wouter delforge"
                    }
                }
                },
                "durationSec": 196,
                "showItemEndpoint": {
                "commandMetadata": {
                    "webCommandMetadata": {
                    "ignoreNavigation": true
                    }
                },
                "showLiveChatItemEndpoint": {
                    "renderer": {
                    "liveChatPaidMessageRenderer": {
                        "id": "ChwKGkNOT193ZXpLdk84Q0ZRbXJ3UW9kWGlZSTJB",
                        "timestampUsec": "1616164763812546",
                        "authorName": {
                        "simpleText": "wouter delforge"
                        },
                        "authorPhoto": {
                        "thumbnails": [
                            {
                            "url": "https://yt4.ggpht.com/ytc/AAUvwngGfTCNawQXGrVgn1cm9_HKQpmtudgEtpwwFQ=s32-c-k-c0x00ffffff-no-rj",
                            "width": 32,
                            "height": 32
                            },
                            {
                            "url": "https://yt4.ggpht.com/ytc/AAUvwngGfTCNawQXGrVgn1cm9_HKQpmtudgEtpwwFQ=s64-c-k-c0x00ffffff-no-rj",
                            "width": 64,
                            "height": 64
                            }
                        ]
                        },
                        "purchaseAmountText": {
                        "simpleText": "€10.00"
                        },
                        "message": {
                        "runs": [
                            {
                            "text": "Hello grossie , I'm in the hospital right now and can only watch youtube on their wifi. I'll be watching daily 🙂"
                            }
                        ]
                        },
                        "headerBackgroundColor": 4294947584,
                        "headerTextColor": 3741319168,
                        "bodyBackgroundColor": 4294953512,
                        "bodyTextColor": 3741319168,
                        "authorExternalChannelId": "UC9KUxJEtno5-PoLLA8jNT7g",
                        "authorNameTextColor": 2315255808,
                        "contextMenuEndpoint": {
                        "commandMetadata": {
                            "webCommandMetadata": {
                            "ignoreNavigation": true
                            }
                        },
                        "liveChatItemContextMenuEndpoint": {
                            "params": "Q2g0S0hBb2FRMDVQWDNkbGVrdDJUemhEUmxGdGNuZFJiMlJZYVZsSk1rRWFLU29uQ2hoVlEwVlpRVlV0Y21kZlkyWldjakprVG0xVFgwRXhlRkVTQzBFNE9HeHNPUzFhZDJwTklBRW9CRElhQ2hoVlF6bExWWGhLUlhSdWJ6VXRVRzlNVEVFNGFrNVVOMmMlM0Q="
                        }
                        },
                        "timestampColor": 2147483648,
                        "contextMenuAccessibility": {
                        "accessibilityData": {
                            "label": "Comment actions"
                        }
                        },
                        "timestampText": {
                        "simpleText": "39:18"
                        }
                    }
                    }
                }
                },
                "authorExternalChannelId": "UC9KUxJEtno5-PoLLA8jNT7g",
                "fullDurationSec": 300
            }
            },
            "durationSec": "196"
        }
        }
    ],
    "videoOffsetTimeMsec": "2358256"
    }
}
```
### Getting Youtube Live Chat's Api

| Key            | Remarks                                   |
|----------------|-------------------------------------------|
| playerOffsetMs | The time to start fetching chat messages. |


playerOffsetMs: 0
```
First: "videoOffsetTimeMsec": "0"  
Last: "videoOffsetTimeMsec": "32672"
```

playerOffsetMs: 32672
```
First: "videoOffsetTimeMsec": "10325"  
Last: "videoOffsetTimeMsec": "46813"
```

We can conclude that for playerOffsetMs = x = 32672,  
10325 < x < 46813

Lower bound: -22347
Upper bound: 14141

To get more messages for timestamp, do x - 22347. This results in more messages starting from the timestamp because we get less previous messages.  
Overall messages starting from x: 14141 + 22347 = 36488

### Example curl to fetch messages:
```sh
curl 'https://www.youtube.com/youtubei/v1/live_chat/get_live_chat_replay?key=AIzaSyAO_FJ2SlqU8Q4STEHLGCilw_Y9_11qcW8' \
  -H 'authority: www.youtube.com' \
  -H 'sec-ch-ua: "Google Chrome";v="89", "Chromium";v="89", ";Not A Brand";v="99"' \
  -H 'x-origin: https://www.youtube.com' \
  -H 'accept-language: en-US,en;q=0.9' \
  -H 'sec-ch-ua-mobile: ?0' \
  -H 'authorization: SAPISIDHASH 1616353822_54188bcfbd183b042e67c251625f92e7d7675e37' \
  -H 'content-type: application/json' \
  -H 'accept: */*' \
  -H 'x-youtube-client-name: 1' \
  -H 'user-agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36' \
  -H 'x-youtube-client-version: 2.20210318.08.00' \
  -H 'x-goog-authuser: 0' \
  -H 'x-client-data: CIW2yQEIo7bJAQjEtskBCKmdygEI+MfKAQjRz8oBCMbpygEI0JrLAQjVnMsBCOScywEIqJ3LARjjw8oB' \
  -H 'x-goog-visitor-id: CgtkNGNrd0VHbFp1TSiNtN6CBg%3D%3D' \
  -H 'origin: https://www.youtube.com' \
  -H 'sec-fetch-site: same-origin' \
  -H 'sec-fetch-mode: cors' \
  -H 'sec-fetch-dest: empty' \
  -H 'referer: https://www.youtube.com/live_chat_replay?continuation=op2w0wRpGlhDaWtxSndvWVZVTkZXVUZWTFhKblgyTm1Wbkl5WkU1dFUxOUJNWGhSRWd0Qk9EaHNiRGt0V25kcVRSb1Q2cWpkdVFFTkNndEJPRGhzYkRrdFduZHFUU0FCQAFaBRCQhpUBcgIIBHgB' \
  -H 'cookie: CONSENT=YES+SG.en+20180311-09-0; VISITOR_INFO1_LIVE=d4ckwEGlZuM; LOGIN_INFO=AFmmF2swRQIgcBuu66I2dndFl2zORSRBKyyTW5HQnG4N_UBeBZ-nA8oCIQCZimL-QkCwV292qhkJnD5Nw4MZTRO-xxA_FYYm8A4Rfg:QUQ3MjNmd1dBU2ltNUxhZmhpWlpHb1dOZDEwR2FTSUY2c3ZmaUpKLTJvbmpYXzVpVEhoc2E2Z09INFJrc1NmVnpGeU1rN2ozaDAzRUhoU1p4X04xOGRHQU5YNHlERFBaZ0hncjVUc1Voejk0WlFueEFMZUpzWjdkRWFZWDZlbkJOamJEWkpmTXRDNEdpTkhwM2pGWlJOWl9NSmJtZVdQRkpDRGd5TnRnMkJ4bVJBb3R5V0NXNUZr; PREF=tz=Asia.Singapore&f1=50000000&al=en&f5=30000; HSID=ADeiA7pH6y_IoPwVo; SSID=AWtkaPc_w89N46198; APISID=1nHSazlgnW0DGHo5/AeQXB0vYiijhVnmFZ; SAPISID=baF0SRcZSu-LyX6e/AWQT3D_ztL1kxFdnz; __Secure-3PAPISID=baF0SRcZSu-LyX6e/AWQT3D_ztL1kxFdnz; SID=7gfAmXwQoHMorxVha1J6g0gULG_z2mFWbUqhJGWffhZDM_O6KSO_9GFKWhsHzku9-LGAVg.; __Secure-3PSID=7gfAmXwQoHMorxVha1J6g0gULG_z2mFWbUqhJGWffhZDM_O6vgg-UktCpNB5nT3LSANX5g.; YSC=xDu6M35mDYc; SIDCC=AJi4QfEKZRPeBskKo-f_kpYhElWiwzMP8yxWBmllAaGZWWfUEHDuI1pxIDIq8tHcsQPSorIbmg; __Secure-3PSIDCC=AJi4QfGZzfgohVbDLvNYMVIQDtDFNh65QS0C4OZVFOHLJTdhlHGP6-7lVLC1K-wjHhS-VntsUQ' \
  --data-raw '{"context":{"client":{"hl":"en","gl":"SG","remoteHost":"183.90.36.154","deviceMake":"","deviceModel":"","visitorData":"CgtkNGNrd0VHbFp1TSiNtN6CBg%3D%3D","userAgent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36,gzip(gfe)","clientName":"WEB","clientVersion":"2.20210318.08.00","osName":"Windows","osVersion":"10.0","originalUrl":"https://www.youtube.com/live_chat_replay?continuation=op2w0wRpGlhDaWtxSndvWVZVTkZXVUZWTFhKblgyTm1Wbkl5WkU1dFUxOUJNWGhSRWd0Qk9EaHNiRGt0V25kcVRSb1Q2cWpkdVFFTkNndEJPRGhzYkRrdFduZHFUU0FCQAFaBRCQhpUBcgIIBHgB","platform":"DESKTOP","clientFormFactor":"UNKNOWN_FORM_FACTOR","timeZone":"Asia/Singapore","browserName":"Chrome","browserVersion":"89.0.4389.90","screenWidthPoints":400,"screenHeightPoints":565,"screenPixelDensity":1,"screenDensityFloat":1,"utcOffsetMinutes":480,"userInterfaceTheme":"USER_INTERFACE_THEME_LIGHT","connectionType":"CONN_CELLULAR_4G","mainAppWebInfo":{"graftUrl":"https://www.youtube.com/live_chat_replay?continuation=op2w0wRpGlhDaWtxSndvWVZVTkZXVUZWTFhKblgyTm1Wbkl5WkU1dFUxOUJNWGhSRWd0Qk9EaHNiRGt0V25kcVRSb1Q2cWpkdVFFTkNndEJPRGhzYkRrdFduZHFUU0FCQAFaBRCQhpUBcgIIBHgB","webDisplayMode":"WEB_DISPLAY_MODE_BROWSER"}},"user":{"lockedSafetyMode":false},"request":{"useSsl":true,"internalExperimentFlags":[],"consistencyTokenJars":[]},"clickTracking":{"clickTrackingParams":"CAEQl98BIhMIjfiek4vC7wIVVzm3AB2zqQdv"},"clientScreenNonce":"MC4zODE1MzkyNzM5MTE4MjY4NQ..","adSignalsInfo":{"params":[{"key":"dt","value":"1616353808089"},{"key":"flash","value":"0"},{"key":"frm","value":"1"},{"key":"u_tz","value":"480"},{"key":"u_his","value":"7"},{"key":"u_java","value":"false"},{"key":"u_h","value":"1080"},{"key":"u_w","value":"1920"},{"key":"u_ah","value":"1040"},{"key":"u_aw","value":"1920"},{"key":"u_cd","value":"24"},{"key":"u_nplug","value":"3"},{"key":"u_nmime","value":"4"},{"key":"bc","value":"31"},{"key":"bih","value":"434"},{"key":"biw","value":"1912"},{"key":"brdim","value":"0,0,0,0,1920,0,1920,1040,400,565"},{"key":"vis","value":"1"},{"key":"wgl","value":"true"},{"key":"ca_type","value":"image"}]}},"continuation":"op2w0wRuGlhDaWtxSndvWVZVTkZXVUZWTFhKblgyTm1Wbkl5WkU1dFUxOUJNWGhSRWd0Qk9EaHNiRGt0V25kcVRSb1Q2cWpkdVFFTkNndEJPRGhzYkRrdFduZHFUU0FCKJPRh5QJQABIBFICIAByAggEeAA%3D","currentPlayerState":{"playerOffsetMs":"2463013"}}' \
  --compressed
```

# References

clang-cl CLI Options  
> https://clang.llvm.org/docs/UsersManual.html#id9

clang CLI Options
> https://clang.llvm.org/docs/ClangCommandLineReference.html

tclap
> http://tclap.sourceforge.net/manual.html
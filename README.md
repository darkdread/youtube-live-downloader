# Building

## Prerequisites

* [clang](https://clang.llvm.org/)
* [CMake](https://cmake.org/download/)
* [vcpkg](https://github.com/microsoft/vcpkg)

## Additional Tools for VSCode

* [CodeLLDB](https://github.com/vadimcn/vscode-lldb)
* [cmake-tools](https://github.com/microsoft/vscode-cmake-tools)

## Vckpg

Project based on x64-windows triplet. Set this environment to build on x64:
> VCPKG_DEFAULT_TRIPLET=x64-windows

Dependencies:
* [TCLAP](https://github.com/mirror/tclap)
* [cpr](https://github.com/whoshuu/cpr)
* [nlohmann-json](https://github.com/nlohmann/json)

## CMake

Building for debug ver:
> cmake --build ./build --config Debug --target all -- -j 10

If using cmake-tools, modify `toolchainFile`.
> "toolchainFile": "${vckpgRoot}\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake"

# Youtube Page

<!-- When fetching a youtube page, there is a variable named `ytInitialData`. This variable is an object which contains the `continuation` key.

[Example Initial Data](ytInitialData.json) -->

When fetching a youtube page, there is a script called `desktop_polymer_inlined_html_polymer_flags.js` which generates a key called `continuation`.  
This key is used to get the first live chat api. Subsequently, the responses from the live chat api will return its own key.

However, since we can't fetch the key programmatically with the cpr library, we will utilize web scraping to do our job.

Run this command after the live chat is loaded.

> ytInitialData.continuationContents.liveChatContinuation.continuations[1].playerSeekContinuationData.continuation

Outputs a string for example:
> "op2w0wRuGlhDaWtxSndvWVZVTkZXVUZWTFhKblgyTm1Wbkl5WkU1dFUxOUJNWGhSRWd0Qk9EaHNiRGt0V25kcVRSb1Q2cWpkdVFFTkNndEJPRGhzYkRrdFduZHFUU0FCKN7Gq58JQABIBFICIAByAggEeAA%3D"

It is the `continuation` input to our program.

Key for getting live chat replay.
> ytplayer.web_player_context_config.innertubeApiKey

# Youtube Live Chat API Responses

| Key                            | Remarks                 |
|--------------------------------|-------------------------|
| liveChatTextMessageRenderer    | Normal message by user. |
| liveChatPaidMessageRenderer    | Paid message by user.   |
| liveChatMembershipItemRenderer | New membership.         |
| timestampUsec                  | Timestamp * 100000      |


```
timestampUsec,    videoOffsetTimeMsec
1616162483909012, 78779
1616162484370336, 79303
1616162484962361, 79865
```


## Examples of responses

* [Normal Message](example-normal-msg.md)
* [Paid Message](example-paid-msg.md)
* [Membership Message](example-membership-msg.md)

### Using Youtube Live Chat API

| Key            | Remarks                                   |
|----------------|-------------------------------------------|
| playerOffsetMs | The time to start fetching chat messages. |
| innertubeKey   | Key to access Youtube's api.              |
| continuation   | Key to access Youtube's api.              |

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

* [CURL](example-curl.md)

# References

clang-cl CLI Options  
> https://clang.llvm.org/docs/UsersManual.html#id9

clang CLI Options
> https://clang.llvm.org/docs/ClangCommandLineReference.html

tclap
> http://tclap.sourceforge.net/manual.html
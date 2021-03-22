# Building

## Prerequisites

* [clang](https://clang.llvm.org/)
* [Code-LLVM](https://github.com/vadimcn/vscode-lldb)


## Vckpg

Project based on x64-windows triplet. Set this environment to build on x64:
> VCPKG_DEFAULT_TRIPLET=x64-windows

Dependencies:
* tclap
* cpr

## CMake

Building for debug ver:
> cmake --build ./build --config Debug --target all -- -j 10


# Youtube Live Chat API Responses

| Key                            | Remarks                 |
|--------------------------------|-------------------------|
| liveChatTextMessageRenderer    | Normal message by user. |
| liveChatPaidMessageRenderer    | Paid message by user.   |
| liveChatMembershipItemRenderer | New subscription.       |
|                                |                         |


## Examples of responses

* [Normal Message](example-normal-msg.md)
* [Paid Message](example-paid-msg.md)

### Using Youtube Live Chat API

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

* [CURL](example-curl.md)

# References

clang-cl CLI Options  
> https://clang.llvm.org/docs/UsersManual.html#id9

clang CLI Options
> https://clang.llvm.org/docs/ClangCommandLineReference.html

tclap
> http://tclap.sourceforge.net/manual.html
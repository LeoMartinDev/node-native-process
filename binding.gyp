{
    "targets": [{
        "target_name": "addon",
        "cflags!": [ "-fno-exceptions" ],
        "cflags_cc!": [ "-fno-exceptions" ],
        "sources": [
            "src/cpp/shared/getProcessWindowHandle.cc",
            "src/cpp/GetProcessesByName/GetProcessesByNameWorker.cc",
            "src/cpp/GetProcessesByName/getProcessesByName_main.cc",
            "src/cpp/GetProcessWindowTitle/GetProcessWindowTitleWorker.cc",
            "src/cpp/GetProcessWindowTitle/getProcessWindowTitle_main.cc",
            "src/cpp/main.cpp"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }]
}
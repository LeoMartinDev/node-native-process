cmd_Release/obj.target/testaddon.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=testaddon.node -o Release/obj.target/testaddon.node -Wl,--start-group Release/obj.target/testaddon/src/cpp/main.o Release/obj.target/node_modules/node-addon-api/src/nothing.a -Wl,--end-group 

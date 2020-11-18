var ipc=require("node-ipc");

var socketId = "icp-test";
ipc.config.id   = "hello";
ipc.config.socketRoot = "/tmp/";
ipc.config.appspace = "";

ipc.config.retry= 1500;
ipc.connectTo(
socketId,
function(){
ipc.of[socketId].on(
"connect",
function(){
console.log("Connected!!");
ipc.log("## connected to world ##".rainbow, ipc.config.delay);
ipc.of[socketId].emit(
"message",  //any event or message type your server listens for
"hello world from home"
)
}
);
ipc.of[socketId].on(
"disconnect",
function(){
console.log("Disconnected!!");
ipc.log("disconnected from world".notice);
}
);
ipc.of[socketId].on(
"message",  //any event or message type your server listens for
function(data){
console.log("Got a message!!");
ipc.log("got a message from world : ".debug, data);
}
);
}
);
var io = require('socket.io-client');
var socket = io.connect('http://localhost:3000', {reconnect: true});
//enviando un numero random cada dos segundos
setInterval(function(){
  socket.emit('client/random', Math.random())
}, 2000)
//recibiendo un numero random cada dos segundos
socket.on('server/random', function(num){
  console.log(num)
})

// var io = require('socket.io-client');
// var socket = io.connect('http://localhost:3000', {reconnect: true});

// // Add a connect listener
// socket.on('connect', function (socket) {
//        console.log('Connected!');
// });
// socket.emit('CH01', 'me', 'test msg');
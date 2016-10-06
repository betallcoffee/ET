var websocket = window.WebSocket || window.MozWebSocket;
var isConnected = false;

function doOpen() {
    console.log('websocket open');
    isConnected = true;
}

function doClose() {
    console.log('websocket close');
}

function doError() {
    console.log('websocket error');
    isConnected = false;
}

function doMessage(message) {
    console.log('weboscket message' + message);
}

if (websocket) {
    var ws = new websocket('ws://127.0.0.1:8080/chat')
    ws.onopen = doOpen;
    ws.onclose = doClose;
    ws.onerror = doError;
    ws.onmessage = doMessage;
}

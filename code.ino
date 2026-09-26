#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "WI-FI"; 

WebServer server(80);




#define L1 23
#define L2 22
#define L3 21
#define L4 19
#define FAN 18


String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Smart Home</title>

<style>
body{
    margin:0;
    font-family:Arial;
    background:linear-gradient(135deg,#0f0f1a,#1a1a2e);
    color:white;
    text-align:center;
}

h1{
    padding:20px;
    color:#00ffcc;
}

.container{
    display:flex;
    flex-direction:column;
    align-items:center;
    gap:15px;
}

.btn{
    width:80%;
    max-width:300px;
    padding:18px;
    font-size:18px;
    border:none;
    border-radius:12px;
    background:#222;
    color:white;
    cursor:pointer;
    transition:0.3s;
    box-shadow:0 0 10px #000;
}

.btn:hover{
    transform:scale(1.05);
}

.on{
    background:#00ff88;
    color:black;
    box-shadow:0 0 20px #00ff88;
}

.off{
    background:#ff4444;
    box-shadow:0 0 20px #ff4444;
}

</style>
</head>

<body>

<h1>🏠 Smart Home Control</h1>

<div class="container">
    <button class="btn" onclick="toggle('l1')">Light 1</button>
    <button class="btn" onclick="toggle('l2')">Light 2</button>
    <button class="btn" onclick="toggle('l3')">Light 3</button>
    <button class="btn" onclick="toggle('l4')">Light 4</button>
    <button class="btn" onclick="toggle('fan')">Fan</button>
</div>

<script>
function toggle(device){
    fetch("/" + device);
}
</script>

</body>
</html>
)rawliteral";

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(FAN, OUTPUT);

  WiFi.softAP(ssid);
  Serial.println(WiFi.softAPIP());

  // Home page
  server.on("/", [](){
    server.send(200, "text/html", html);
  });

  // Toggle routes
  server.on("/l1", [](){ digitalWrite(L1, !digitalRead(L1)); server.send(200, "text/plain", "OK"); });
  server.on("/l2", [](){ digitalWrite(L2, !digitalRead(L2)); server.send(200, "text/plain", "OK"); });
  server.on("/l3", [](){ digitalWrite(L3, !digitalRead(L3)); server.send(200, "text/plain", "OK"); });
  server.on("/l4", [](){ digitalWrite(L4, !digitalRead(L4)); server.send(200, "text/plain", "OK"); });
  server.on("/fan", [](){ digitalWrite(FAN, !digitalRead(FAN)); server.send(200, "text/plain", "OK"); });

  server.begin();
}

// ================= LOOP =================
void loop() {
  server.handleClient();
}

#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "WI-FI";

WebServer server(80);

// ================= PIN CONFIG =================
#define L1 23
#define L2 22
#define L3 21
#define L4 19
#define FAN 18

// ================= HTML =================
String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">

<title>Smart Home Control</title>

<style>

*{
    box-sizing:border-box;
    margin:0;
    padding:0;
}

body{
    min-height:100vh;
    font-family:Arial,Helvetica,sans-serif;
    color:#fff;
    background:
        radial-gradient(circle at top left,#123b46 0%,transparent 35%),
        radial-gradient(circle at bottom right,#17285b 0%,transparent 40%),
        #050914;
    display:flex;
    justify-content:center;
    align-items:center;
    padding:20px;
}

.app{
    width:100%;
    max-width:520px;
    padding:25px;
    border:1px solid rgba(255,255,255,.1);
    border-radius:28px;
    background:rgba(10,17,32,.78);
    backdrop-filter:blur(20px);
    box-shadow:
        0 25px 70px rgba(0,0,0,.45),
        inset 0 1px 0 rgba(255,255,255,.05);
}

.header{
    text-align:center;
    margin-bottom:25px;
}

.logo{
    width:70px;
    height:70px;
    margin:0 auto 15px;
    border-radius:22px;
    display:flex;
    align-items:center;
    justify-content:center;
    font-size:35px;
    background:linear-gradient(135deg,#00f6ff,#2251d3);
    box-shadow:0 0 35px rgba(0,246,255,.25);
}

h1{
    font-size:27px;
    margin-bottom:8px;
    background:linear-gradient(90deg,#00f6ff,#7df9ff);
    -webkit-background-clip:text;
    color:transparent;
}

.subtitle{
    color:#8793a8;
    font-size:14px;
}

.status-bar{
    display:flex;
    align-items:center;
    justify-content:center;
    gap:8px;
    margin:20px 0;
    padding:11px;
    border-radius:14px;
    background:rgba(255,255,255,.045);
    color:#aeb8c9;
    font-size:13px;
}

.status-dot{
    width:9px;
    height:9px;
    border-radius:50%;
    background:#00ff88;
    box-shadow:0 0 12px #00ff88;
}

.controls{
    display:grid;
    grid-template-columns:1fr 1fr;
    gap:14px;
}

.device{
    position:relative;
    overflow:hidden;
    border:1px solid rgba(255,255,255,.08);
    border-radius:20px;
    padding:18px;
    background:rgba(255,255,255,.045);
    transition:.25s ease;
}

.device:hover{
    transform:translateY(-3px);
    border-color:rgba(0,246,255,.3);
}

.device.active{
    background:linear-gradient(
        145deg,
        rgba(0,255,136,.13),
        rgba(0,246,255,.05)
    );
    border-color:rgba(0,255,136,.35);
}

.device-top{
    display:flex;
    justify-content:space-between;
    align-items:center;
    margin-bottom:17px;
}

.icon{
    width:46px;
    height:46px;
    border-radius:14px;
    display:flex;
    align-items:center;
    justify-content:center;
    font-size:23px;
    background:#151e31;
    transition:.25s;
}

.device.active .icon{
    background:#00ff88;
    color:#001c10;
    box-shadow:0 0 20px rgba(0,255,136,.35);
}

.device-name{
    font-weight:bold;
    font-size:16px;
    margin-bottom:5px;
}

.device-state{
    font-size:12px;
    color:#718096;
}

.device.active .device-state{
    color:#00ff88;
}

.toggle{
    width:100%;
    height:45px;
    border:0;
    border-radius:13px;
    background:#1a2335;
    color:#aeb8c9;
    font-size:14px;
    font-weight:bold;
    cursor:pointer;
    transition:.25s;
}

.toggle:hover{
    background:#253149;
}

.device.active .toggle{
    background:#00ff88;
    color:#00150c;
    box-shadow:0 0 18px rgba(0,255,136,.25);
}

.fan-card{
    grid-column:1 / -1;
}

.footer{
    text-align:center;
    margin-top:23px;
    padding-top:18px;
    border-top:1px solid rgba(255,255,255,.07);
    color:#5f6c82;
    font-size:12px;
}

@media(max-width:420px){

    body{
        padding:12px;
    }

    .app{
        padding:18px;
        border-radius:23px;
    }

    .controls{
        grid-template-columns:1fr;
    }

    .fan-card{
        grid-column:auto;
    }

}

</style>
</head>

<body>

<div class="app">

    <div class="header">

        <div class="logo">🏠</div>

        <h1>Smart Home</h1>

        <div class="subtitle">
            ESP32 Wireless Control Panel
        </div>

    </div>

    <div class="status-bar">
        <span class="status-dot"></span>
        ESP32 Access Point Connected
    </div>

    <div class="controls">

        <div class="device" id="card-l1">
            <div class="device-top">
                <div>
                    <div class="device-name">Light 1</div>
                    <div class="device-state" id="state-l1">OFF</div>
                </div>
                <div class="icon">💡</div>
            </div>

            <button class="toggle" onclick="toggleDevice('l1')">
                TURN ON
            </button>
        </div>


        <div class="device" id="card-l2">
            <div class="device-top">
                <div>
                    <div class="device-name">Light 2</div>
                    <div class="device-state" id="state-l2">OFF</div>
                </div>
                <div class="icon">💡</div>
            </div>

            <button class="toggle" onclick="toggleDevice('l2')">
                TURN ON
            </button>
        </div>


        <div class="device" id="card-l3">
            <div class="device-top">
                <div>
                    <div class="device-name">Light 3</div>
                    <div class="device-state" id="state-l3">OFF</div>
                </div>
                <div class="icon">💡</div>
            </div>

            <button class="toggle" onclick="toggleDevice('l3')">
                TURN ON
            </button>
        </div>


        <div class="device" id="card-l4">
            <div class="device-top">
                <div>
                    <div class="device-name">Light 4</div>
                    <div class="device-state" id="state-l4">OFF</div>
                </div>
                <div class="icon">💡</div>
            </div>

            <button class="toggle" onclick="toggleDevice('l4')">
                TURN ON
            </button>
        </div>


        <div class="device fan-card" id="card-fan">

            <div class="device-top">
                <div>
                    <div class="device-name">Fan</div>
                    <div class="device-state" id="state-fan">OFF</div>
                </div>

                <div class="icon">🌀</div>
            </div>

            <button class="toggle" onclick="toggleDevice('fan')">
                TURN ON
            </button>

        </div>

    </div>

    <div class="footer">
        MH2 Smart Home • ESP32 Control System
    </div>

</div>


<script>

const states = {
    l1:false,
    l2:false,
    l3:false,
    l4:false,
    fan:false
};

function toggleDevice(device){

    fetch("/" + device)
    .then(response => {

        if(!response.ok){
            throw new Error("Request failed");
        }

        states[device] = !states[device];

        updateUI(device);

    })
    .catch(error => {

        console.error(error);

        alert("Connection failed. Check ESP32 connection.");

    });

}


function updateUI(device){

    const card = document.getElementById("card-" + device);
    const state = document.getElementById("state-" + device);
    const button = card.querySelector(".toggle");

    if(states[device]){

        card.classList.add("active");

        state.textContent = "ON";

        button.textContent = "TURN OFF";

    }
    else{

        card.classList.remove("active");

        state.textContent = "OFF";

        button.textContent = "TURN ON";

    }

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

    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    digitalWrite(L3, LOW);
    digitalWrite(L4, LOW);
    digitalWrite(FAN, LOW);

    WiFi.softAP(ssid);

    Serial.println();
    Serial.println("==============================");
    Serial.println("      MH2 SMART HOME");
    Serial.println("==============================");
    Serial.print("WiFi Name: ");
    Serial.println(ssid);
    Serial.print("IP Address: ");
    Serial.println(WiFi.softAPIP());
    Serial.println("==============================");


    // ================= HOME =================

    server.on("/", []() {

        server.send(
            200,
            "text/html",
            html
        );

    });


    // ================= LIGHT 1 =================

    server.on("/l1", []() {

        digitalWrite(
            L1,
            !digitalRead(L1)
        );

        server.send(
            200,
            "text/plain",
            "OK"
        );

    });


    // ================= LIGHT 2 =================

    server.on("/l2", []() {

        digitalWrite(
            L2,
            !digitalRead(L2)
        );

        server.send(
            200,
            "text/plain",
            "OK"
        );

    });


    // ================= LIGHT 3 =================

    server.on("/l3", []() {

        digitalWrite(
            L3,
            !digitalRead(L3)
        );

        server.send(
            200,
            "text/plain",
            "OK"
        );

    });


    // ================= LIGHT 4 =================

    server.on("/l4", []() {

        digitalWrite(
            L4,
            !digitalRead(L4)
        );

        server.send(
            200,
            "text/plain",
            "OK"
        );

    });


    // ================= FAN =================

    server.on("/fan", []() {

        digitalWrite(
            FAN,
            !digitalRead(FAN)
        );

        server.send(
            200,
            "text/plain",
            "OK"
        );

    });


    server.begin();

    Serial.println("Web Server Started!");
}


// ================= LOOP =================

void loop() {

    server.handleClient();

}

// // ===== POLLING ========

// async function updateDashboard()
// {

//     const response =
//         await fetch("/api/sensors");

//     const data =
//         await response.json();

//     document.getElementById("flow").innerText =
//         data.flowRate;

//     document.getElementById("pressure").innerText =
//         data.pressure;

//     document.getElementById("salt").innerText =
//         data.saltLevel;

//     document.getElementById("tds").innerText =
//         data.tds;

//     document.getElementById("wifi").innerText =
//         data.wifi;

//     document.getElementById("state").innerText =
//         data.state;

// }

// setInterval(updateDashboard,1000);



// // ============ NO POLLING ============

const socket = new WebSocket("ws://localhost:3000");

socket.onopen = () => {
    console.log("Connected to Backend");
};

socket.onmessage = (event) => {

    const data = JSON.parse(event.data);

    document.getElementById("flow").innerText =
        data.flowRate;

    document.getElementById("pressure").innerText =
        data.pressure;

    document.getElementById("salt").innerText =
        data.saltLevel;

    document.getElementById("tds").innerText =
        data.tds;

    document.getElementById("wifi").innerText =
        data.wifi;

    document.getElementById("state").innerText =
        data.state;
        document.getElementById("valve").innerText =
    data.valve;

    document.getElementById("regeneration").innerText =
        data.regeneration;

    document.getElementById("alerts").innerText =
        data.alerts || "None";

    document.getElementById("lastUpdated").innerText =
        new Date().toLocaleTimeString();
};

socket.onclose = () => {
    console.log("Disconnected");
};

async function sendCommand(command)
{
    await fetch("/api/command", {

        method: "POST",

        headers: {
            "Content-Type": "application/json"
        },

        body: JSON.stringify({
            command: command
        })

    });
}
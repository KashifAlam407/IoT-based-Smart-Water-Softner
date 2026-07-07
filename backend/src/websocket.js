const WebSocket = require("ws");

let wss;

function initialize(server)
{
    wss = new WebSocket.Server({ server });

    wss.on("connection", (socket) =>
    {
        console.log("Dashboard Connected");

        socket.on("close", () =>
        {
            console.log("Dashboard Disconnected");
        });
    });
}

function broadcast(data)
{
    if (!wss) return;

    const json = JSON.stringify(data);

    wss.clients.forEach(client =>
    {
        if (client.readyState === WebSocket.OPEN)
        {
            client.send(json);
        }
    });
}

module.exports = {
    initialize,
    broadcast
};
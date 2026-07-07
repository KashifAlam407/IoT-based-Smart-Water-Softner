const express = require("express");
const http = require("http");

const mqttClient = require("./mqttClient");
const websocket = require("./websocket");

const app = express();
const server = http.createServer(app);

const PORT = 3000;

app.get("/api/sensors", (req, res) => {
    res.json(
        mqttClient.getLatestData()
    );
    // res.sen("EcoWell Backend Running");
});

app.use(express.json());

app.post("/api/command", (req, res) => {

    const command = req.body.command;

    console.log("================================");
    console.log("Dashboard Command");
    console.log(command);
    console.log("================================");

    mqttClient.publish(
        "ecowell/softener/cmd",
        command
    );

    res.json({
        success: true,
        command: command
    });

});

app.use(express.static("public"));

websocket.initialize(server);

server.listen(PORT, () => {

    console.log(`Server running on port ${PORT}`);

});



const mqtt = require("mqtt");

const websocket = require("./websocket");

let latestData = {};

const options = {
  username: "kashif_ecowell",
  password: "kashif_ecowell",
};

const client = mqtt.connect(
  "mqtts://14273b0d5919486292320d12986e227c.s1.eu.hivemq.cloud:8883",
  options
);

client.on("connect", () => {
  console.log("Connected to HiveMQ");

  client.subscribe("ecowell/softener/data");

  console.log("Subscribed");
});

client.on("message", (topic, message) => {

  latestData = JSON.parse(message.toString());
  console.log(latestData);
  websocket.broadcast(latestData);
  
//   console.log(topic);
//   console.log(message.toString());
});

function publish(topic, message)
{
    client.publish(topic, message);
}

module.exports = {
    client,
    getLatestData: () => latestData,
    publish
};
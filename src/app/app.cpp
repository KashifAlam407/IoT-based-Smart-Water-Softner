#include "app.h"
#include "../config/config.h"

String stateToString(DeviceState state)
{
    switch (state)
    {
        case DeviceState::IDLE:
            return "IDLE";

        case DeviceState::MONITORING:
            return "MONITORING";

        case DeviceState::REGENERATION_REQUIRED:
            return "REGENERATION REQUIRED";

        case DeviceState::REGENERATING:
            return "REGENERATING";

        case DeviceState::FAULT:
            return "FAULT";

        default:
            return "UNKNOWN";
    }
}

void App::begin()
{
    logger.begin();

    logger.info("Application Starting...");

    sensorManager.begin();

    stateMachine.begin();

    wifiManager.begin();

    mqttManager.begin();
}

void App::update()
{
    sensorManager.update();

    wifiManager.update();

    SensorData data = sensorManager.getData();


    // Alert Detection
    activeAlerts = "";

    if(data.saltLevel < LOW_SALT_THRESHOLD)
    {
        activeAlerts += "LOW_SALT;";
    }

    if(data.tds > HIGH_TDS_THRESHOLD)
    {
        activeAlerts += "HIGH_TDS;";
    }

    if(data.pressure < LOW_PRESSURE_THRESHOLD)
    {
        activeAlerts += "LOW_PRESSURE;";
    }

    if(data.flowRate < NO_FLOW_THRESHOLD)
    {
        activeAlerts += "NO_FLOW;";
    }


    stateMachine.update(data);

    mqttManager.update();

    if (mqttManager.hasNewCommand())
    {
        String command =
            mqttManager.getLastCommand();

        executeCommand(command);
    }


    // Regeneration Process
    // Runs EVERY loop

    if(regenerationRunning)
    {
        unsigned long elapsed =
            millis() - regenerationStartTime;

        if(elapsed >= 5000)
        {
            regenerationRunning = false;

            valveOpen = false;

            regenerationStatus = "COMPLETED";

            logger.info("Regeneration Completed");
        }
    }
    

    String payload =
    "{\"wifi\":\"" + String(wifiManager.isConnected() ? "CONNECTED" : "DISCONNECTED") +
    "\",\"flowRate\":" + String(data.flowRate) +
    ",\"pressure\":" + String(data.pressure) +
    ",\"saltLevel\":" + String(data.saltLevel) +
    ",\"tds\":" + String(data.tds) +
    ",\"state\":\"" + stateToString(stateMachine.getState()) +
    "\",\"valve\":\"" + String(valveOpen ? "OPEN" : "CLOSED") + 
    "\",\"regeneration\":\"" + regenerationStatus + 
    "\",\"reason\":\"" + 
    regenerationRejectReason +
    "\",\"alerts\":\"" +
    activeAlerts +
    "\"}";

    mqttManager.publish(payload);

    logger.info(payload);

    delay(1000);
}

void App::executeCommand(const String &command)
{
    if(command == "OPEN_VALVE")
    {
        valveOpen = true;

        logger.info("Valve Opened");
    }
    else if(command == "CLOSE_VALVE")
    {
        valveOpen = false;

        logger.info("Valve Closed");
    }
    else if (command == "START_REGEN")
    {
        SensorData data = sensorManager.getData();

        if(canStartRegeneration(data))
        {   
            Serial.println("Safety Check Pass");
            regenerationRunning = true;
            regenerationStartTime = millis();
            valveOpen = true;

            regenerationStatus = "RUNNING";

            logger.info("Regeneration Started");
        }
        else
        {
            regenerationStatus = "FAILED";

            logger.info("Regeneration Blocked : " + regenerationRejectReason);
        }
    }
    else if (command == "STOP_REGEN")
    {
        regenerationRunning = false;
        valveOpen = false;
        regenerationStatus = "STOPPED";
        logger.info("Regeneration Stopped");
    }
}


bool App::canStartRegeneration(SensorData data)
{
    if (regenerationRunning)
    {
        regenerationRejectReason = "ALREADY_RUNNING";
        return false;
    }


    if (data.pressure < 1.0)
    {
        regenerationRejectReason = "LOW_PRESSURE";
        return false;
    }

    if (data.saltLevel < 20)
    {
        regenerationRejectReason = "LOW_SALT";
        return false;
    }

    if (stateMachine.getState() == DeviceState::FAULT)
    {
        regenerationRejectReason = "FAULT";
        return false;
    }

    regenerationRejectReason = "";

    return true;
}

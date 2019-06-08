# API endpoint documentation

The API will consist of three different actor types: Client, Server and Sensor/Actuator.
The Server is them main controller that clients can reach and interact with. It in turn sends requests to the sensors/actuators.

## Device types

There are several types of sensor/actuator devices, a preliminary list is included below.
Every device type has specific state options, e.g. brightness or fan speed

### Actuators

- switch, `active:boolean`
- button, `active:boolean`, `activation-time:int` (how long the button stays on, stored on device)
- fan `power:int` (PWM power), `speed:int` (RPM representing speed)
- lamp-generic `active:boolean`
- lamp-hue-color `brightness:int`, `red:int`, `blue:int`, `blue:int`, `white:int` (the RGBW values of the bulb)
- lamp-hue-white `brightness:int`, `temperature:int` (light temperature according to hue API docs)
- alarm `active:boolean`, `time:timestamp`
- sound-player `active:boolean`, `sound:sound-name`, `volume:int` (plays the file named "sound-name" in a specified directory. Whether this list should be static or retrievable is TBD)

### Sensors

- thermometer `temperature:double` (double-precision temperature in celsius)
- hygrometer `humidity:int` (humidity in 0-255)
- movement-sensor `movement:boolean` (this only makes sense as an event subscription)
- rfid-reader `tag-present:boolean`, `tag-id:string`, `tag-content:string` (Intended for event subscription)
- brightness-sensor `brightness:int` (unit to be determined)
- generic-boolean `value:boolean`
- generic-8bit `value:8bit-int`
- generic-16bit `value:16bit-int`

## Control server endpoints

These are the endpoints accessible to users in order to interact with the devices through the central control server. For the internal communication between the control server and the individual devices, please see "Sensor / actuator endpoints" below.

### List devices

**Definition**
`GET /devices`

**Description**
Returns a list of devices in json format:

**Response**
The response depends on whether the request was successful:

- Success: `200 OK` (When no devices are registered, an empty list is returned)

    ```json
    [
        {
            "identifier": "lamp-01",
            "friendly-name": "Super Cool Lamp Name",
            "device-type": "lamp-hue"
        },
        {
            "identifier": "lamp-02",
            "friendly-name": "Super Cool Lamp Name 2",
            "device-type": "lamp-generic"
        },
        {
            "identifier": "pc-01-power",
            "friendly-name": "PC-01 power button",
            "device-type": "button"
        },
        {
            "identifier": "pc-01-temp",
            "friendly-name": "PC-01 temperature gauge",
            "device-type": "thermometer"
        },
        {
            "identifier": "rfid-01",
            "friendly-name": "RFID Reader front door",
            "device-type": "rfid-reader"
        }
    ]
    ```

- User does not have enough privileges: `403 FORBIDDEN`

### Create device

**Definition**
`POST /devices`

**Description**
Creates a new device entry with the parameters as specified below:

- `"identifier":string` unique identifier such as "lamp-01".
- `"name":string` human-readable name, e.g. "Super Cool Lamp Name".
- `"device-type":string` type of the device, see list above for different device types

**Response**
The response depends on whether the request was successful:

- Success: `201 CREATED`, `200 OK` if a device existed and was overwritten

    ```json
    {
        "identifier": "lamp-01",
        "name": "Super Cool Lamp Name",
        "device-type": "lamp-hue"
    }
    ```

- User does not have enough privileges: `403 FORBIDDEN`

### View device info

**Definition**
`GET /device/<identifier>`

**Description**
Returns the details of the specified device

**Response**
The response depends on whether the request was successful:

- Not found: `404 NOT FOUND`
- Success: `200 OK`

    ```json
    {
        "identifier": "lamp-01",
        "name": "Super Cool Lamp Name",
        "device-type": "lamp-hue"
    }
    ```

- User does not have enough privileges: `403 FORBIDDEN`

### Remove device

**Definition**
`DELETE /device/<identifier>`

**Description**
Deletes the specified device

**Response**
The response depends on whether the request was successful:

- Not found: `404 NOT FOUND`
- Success: `204 NO CONTENT`
- User does not have enough privileges: `403 FORBIDDEN`

### Check whether device is a coffee machine

**Definition**
`GET /device/<identifier>/coffee`

**Description**
Life is boring without having some fun

**Response**
The response depends on whether the request was successful:

- Not found: `404 NOT FOUND`
- Success: `204 NO CONTENT` if device is a coffee machine
- Success: `418 I'M A TEAPOT` if device is a teapot
- User does not have enough privileges: `403 FORBIDDEN`

## Sensor / actuator endpoints

The control server uses a comparable pattern to talk to the devices themselves. There are three different possible requests the control server might send: `GET` will retrieve the current state, `POST` updates the state (only possible on actuators) and gets the new state back, `POST /subscribe/` with (optional) `frequency:int` (in seconds) as parameter subscribes the control server to events. These events will send the current state to the control server either when something triggers (RFID tag presented, Movement detected) or every X seconds, as defined in the parameter.

This is being done in order to move as much of the logical processing to the main control server as possible. This way, endpoint devices are easily swappable and could go offfline without causing issues with programmed values. An exception to this is the alarm module, as this manages its own time and should be available even if power goes offline (using batteries).

**Definition**
`DELETE /device/<identifier>`

**Description**
Deletes the specified device

**Response**
The response depends on whether the request was successful:

- Not found: `404 NOT FOUND`
- Success: `204 NO CONTENT`
- User does not have enough privileges: `403 FORBIDDEN`

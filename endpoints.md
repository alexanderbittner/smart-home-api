# API endpoint documentation

The API will consist of three different actor types: Client, Server and Sensor/Actuator.
The Server is them main controller that clients can reach and interact with. It in turn sends requests to the sensors/actuators.

## Device types

There are several types of sensor/actuator devices, a preliminary list is included below.
Every device type has specific state options, e.g. brightness or fan speed

### Actuators

- switch, `active:boolean`
- button, `active:boolean`, `activation-time:int` (how long the button stays on, in milliseconds)
- fan `power:int` (PWM power), `speed:int` (RPM representing speed)
- lamp-generic `active:boolean`
- lamp-hue-color `brightness:int`, `red:int`, `blue:int`, `blue:int`, `white:int` (the RGBW values of the bulb)
- lamp-hue-white `brightness:int`, `temperature:int` (light temperature according to hue API docs)
- alarm `scheduled:boolean``active:boolean`, `time:unix-timestamp`, `timezone:string` `sound:string` The activation time is a unix timestamp in UTC time zone, specify local time zone as e.g. Europe/Amsterdam. The sound string specifies a file in the folder of alarm sounds, e.g. digital-beep.wav to play digital-beep.wav when the alarm triggers. When the alarm is playing, the "active" value is set to be true. To turn off the alarm, set the "active" value to 'false'.
- sound-player `active:boolean`, `sound:string`, `volume:int` (plays the file named "sound-name" in a specified directory. Whether this list should be static or retrievable is TBD)

### Sensors

- thermometer `temperature:float` (temperature in celsius)
- hygrometer `humidity:float` (humidity in percent)
- movement-sensor `movement:boolean` (this only makes sense as an event subscription)
- rfid-reader `tag-present:boolean`, `tag-id:string`, `tag-content:string` (Intended for event subscription), `tag-id` and `tag-content` are empty strings with length 0 when no tag is present
- brightness-sensor `brightness:int` (unit to be determined)
- generic-boolean `value:boolean`
- generic-int `value:int`
- generic-float `value:float`

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
            "name": "Super Cool Lamp Name",
            "type": "lamp-hue-color",
            "controller-id": "hue-controller",
            "state": {
                "on": {
                    "type": "boolean",
                    "value": false
                },
                "brightness": {
                    "type": "int",
                    "min": 1,
                    "max": 254,
                    "value": 100
                },
                "xy": [
                    {
                        "type": float,
                        "min": 0.0,
                        "max": 1.0,
                        "value": 0.3521
                    },
                    {
                        "type": float,
                        "min": 0.0,
                        "max": 1.0,
                        "value": 0.4153
                    }
                ]
            }
        },
        {
            "identifier": "lamp-02",
            "name": "Super Cool Lamp Name 2",
            "type": "lamp-generic",
            "controller-id": "433-mhz-controller",
            "state": {
                "on": {
                    "type": "boolean",
                    "value": false
                }
            }
        },
        {
            "identifier": "pc-01-power",
            "name": "PC-01 power button",
            "type": "button",
            "controller-id": "pc-01-controller",
            "state": {
                "active": {
                    "type": "boolean",
                    "value": false
                },
                "activation-time": {
                    "type": "int",
                    "min": 1,
                    "max": 10000,
                    "value": 500
                }
            }
        },
        {
            "identifier": "pc-01-temp",
            "name": "PC-01 CPU temperature",
            "type": "thermometer",
            "controller-id": "pc-01-controller",
            "state": {
                "temperature": {
                    "type": "float",
                    "min": -40.0,
                    "max": 125.0,
                    "value": 25.34
                }
            }
        },
        {
            "identifier": "rfid-01",
            "name": "RFID Reader front door",
            "type": "rfid-reader",
            "controller-id": "front-door-controller",
            "state": {
                "tag-present": {
                    "type": "float",
                    "min": -40.0,
                    "max": 125.0,
                    "value": 25.34
                },
                "tag-id": {
                    "type": "string",
                    "length": 8,
                    "value": "12345678"
                },
                "tag-content": {
                    "type": "string",
                    "length": 32,
                    "value": "12345678123456781234567812345678"
                }
            }
        }
    ]
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
        "identifier": "rfid-01",
        "name": "RFID Reader front door",
        "type": "rfid-reader",
        "controller-id": "front-door-controller",
        "state": {
            "tag-present": {
                "type": "float",
                "min": -40.0,
                "max": 125.0,
                "value": 25.34
            },
            "tag-id": {
                "type": "string",
                "length": 8,
                "value": "12345678"
            },
            "tag-content": {
                "type": "string",
                "length": 32,
                "value": "12345678123456781234567812345678"
            }
        }
    }
    ```

- User does not have enough privileges: `403 FORBIDDEN`

### Create device

**Definition**
`PUT /devices`

**Description**
Creates a new device entry with the parameters as specified below. Once registered, the central controller tries to connect to the specified device controller and tries to retrieve the state of the device (that follows the type definition).

- `"identifier":string` unique identifier such as "lamp-01".
- `"name":string` human-readable name, e.g. "Super Cool Lamp Name".
- `"type":string` type of the device, see list above for different device types
- `"controller-id":string` id of the controller that will handle requests going to said device

**Response**
The response depends on whether the request was successful:

- Success: `201 CREATED`

    ```json
    {
        "identifier": "pc-01-temp",
        "name": "PC-01 CPU temperature",
        "type": "thermometer",
        "controller-id": "pc-01-controller",
        "state": {
            "temperature": {
                "type": "float",
                "min": -40.0,
                "max": 125.0,
                "value": 25.34
            }
        }
    }
    ```

- Could not connect to device controller and get state: `404 NOT FOUND`
- User does not have enough privileges: `403 FORBIDDEN`
- Not logged in: `401 UNAUTHORIZED`
- Resource already exists: `409 CONFLICT`

### Change device

**Definition**
`POST /devices/<identifier>`

**Description**
Changes one or more devices using a POST request, with the parameters as specified below. This can be used to either change device names (though not the identifier or type) or their state (e.g. for activating on a `switch` device). Once the request has been completed successfully, it will be met with the proper response containing the updated content. If an illegal action happened (e.g. trying to change the temperature reading of a temperature sensor), an error will be returned.

- `"name":string` human-readable name, e.g. "Super Cool Lamp Name".
- `"state":json` the changed json object.

**Response**
The response depends on whether the request was successful:

- Success: `200 OK` if the content could be changed successfully

    ```json
    {
        "identifier": "pc-01-temp",
        "name": "PC-01 CPU temperature",
        "type": "thermometer",
        "controller-id": "pc-01-controller",
        "state": {
            "temperature": {
                "type": "float",
                "min": -40.0,
                "max": 125.0,
                "value": 25.34
            }
        }
    }
    ```

- Illegal request: `409 CONFLICT`
- Could not connect to device controller and get state: `404 NOT FOUND`
- User does not have enough privileges: `403 FORBIDDEN`
- Not logged in: `401 UNAUTHORIZED`

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
- Not logged in: `401 UNAUTHORIZED`

## Sensor / actuator endpoints

The control uses a comparable standard to talk to the device controllers. There are three differend possible request types the control server might sent: `GET /` will retrieve the current state array, `GET /<device-id>` will return only the current state of the specivied device, `POST` updates the state (only possible on actuators). `POST /<device-id>/subscribe` including `"frequency":int` and an (array of) empty state tag(s) (e.g. `"temperature"`) will subscribe the central controller to the specified value. Here, the frequency will determine how long the interview between sent events will be (in milliseconds). If the specified interval is 0, only updated events will be sent. These events will send the current state to the control server either when something triggers (RFID tag presented, Movement detected).

This is being done in order to move as much of the logical processing to the main control server as possible. This way, endpoint devices are easily swappable and could go offfline without causing issues with programmed values. An exception to this is the alarm module, as this manages its own time and should be available even if power goes offline (using batteries).

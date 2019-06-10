# Device type documentation

This documentation includes the different device types and an example json object containing all relevant device information. This can be used as a reference for implementing the device controllers.

## Actuators

- switch, `"active":boolean`

  ```json
    {
        "identifier": "monitor-01-power",
        "name": "Left Monitor Power",
        "type": "switch",
        "controller-id": "monitor-controller",
        "state": {
            "active": {
                "type": "boolean",
                "value": true
            }
        }
    }
    ```

- button, `"active":boolean`, `"activation-time":int` (how long the button stays on, in milliseconds)

  ```json
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
    }
    ```

- lamp-generic `"on":boolean`

  ```json
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
    }
    ```

- lamp-hue-color `"on":boolean`, `"brightness":int`, `"xy":[float,float]` (The on-status, brightness and xy-color values of the bulb according to the CIE color spectrum)

  ```json
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
                    "type": "float",
                    "min": 0.0,
                    "max": 1.0,
                    "value": 0.3521
                },
                {
                    "type": "float",
                    "min": 0.0,
                    "max": 1.0,
                    "value": 0.4153
                }
            ]
        }
    }
    ```

- lamp-hue-white `"brightness":int`, `"temperature":int` (light temperature according to hue API docs) (might be subject to changes)

  ```text
    to be implemented
    ```

- alarm `"active":boolean`, `"time":string`, `"timezone":string` `sound:string` The activation time is a 64-bit unix timestamp in UTC time zone, specify local time zone as e.g. Europe/Amsterdam. The sound string specifies a file in the folder of alarm sounds, e.g. digital-beep.wav to play digital-beep.wav when the alarm triggers.
1560186054
2147483647

  ```json
    {
        "identifier": "alarm-01",
        "name": "Main alarm",
        "type": "alarm",
        "controller-id": "alarm-controller",
        "state": {
            "active": {
                "type": "boolean",
                "value": false
            },
            "time": {
                "type": "string",
                "length": 64,
                "value": "64bittimestamp0064bittimestamp0064bittimestamp0064bittimestamp00"
            },
            "timezone": {
                "type": "string",
                "length": 16,
                "value": "Europe/Amsterdam"
            },
            "sound": {
                "type": "string",
                "length": 17,
                "value": "digital-alarm.wav"
            },
        }
    }
    ```

- sound-player `"active":boolean`, `"sound":string`, `"volume":int` (plays the file named "sound-name" in a specified directory. Whether this list should be static or retrievable is TBD)

  ```json
    {
        "identifier": "sound-player-01",
        "name": "Sound Player",
        "type": "sound-player",
        "controller-id": "main-iot-controller",
        "state": {
            "active": {
                "type": "boolean",
                "value": false
            },
            "sound": {
                "type": "string",
                "length": 17,
                "value": "digital-alarm.wav"
            },
            "volume": {
                "type": "int",
                "min": 0,
                "max": 255,
                "value": 100
            }
        }
    }
    ```

## Sensors

- thermometer `temperature:float` (temperature in celsius)

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

- hygrometer `humidity:float` (humidity in percent)

  ```json
    {
        "identifier": "outside-hygro-01",
        "name": "Outside Humidity",
        "type": "hygrometer",
        "controller-id": "outside-sensor-controller",
        "state": {
            "humidity": {
                "type": "float",
                "min": 0.0,
                "max": 100.0,
                "value": 45.21
            }
        }
    }
    ```

- movement-sensor `movement:boolean` (this only makes sense as an event subscription)

  ```json
    {
        "identifier": "movement-outside-01",
        "name": "Outside Movement Sensor",
        "type": "movement-sensor",
        "controller-id": "outside-sensor-controller",
        "state": {
            "movement": {
                "type": "boolean",
                "value": false
            }
        }
    }
    ```

- rfid-reader `tag-present:boolean`, `tag-id:string`, `tag-content:string` (Intended for event subscription), `tag-id` and `tag-content` are empty strings with length 0 when no tag is present

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

- brightness-sensor `brightness:int` (unit to be determined)

  ```json
    {
        "identifier": "brightness-outside-01",
        "name": "Outside Brightness",
        "type": "brightness-sensor",
        "controller-id": "outside-sensor-controller",
        "state": {
            "brightness": {
                "type": "int",
                "min": 0,
                "max": 255,
                "value": 98
            }
        }
    }
    ```

- generic-boolean `value:boolean`

  ```json
    {
        "identifier": "generic-boolean-01",
        "name": "A boolean sensor.",
        "type": "generic-boolean",
        "controller-id": "generic-controller",
        "state": {
            "value": {
                "type": "boolean",
                "value": true
            }
        }
    }
    ```

- generic-int `value:int`

  ```json
    {
        "identifier": "generic-int-01",
        "name": "An int sensor.",
        "type": "generic-int",
        "controller-id": "generic-controller",
        "state": {
            "value": {
                "type": "int",
                "min": 0,
                "max": 2047,
                "value": 1337
            }
        }
    }
    ```

- generic-float `value:float`

  ```json
    {
        "identifier": "generic-float-01",
        "name": "An float sensor.",
        "type": "generic-float",
        "controller-id": "generic-controller",
        "state": {
            "value": {
                "type": "float",
                "min": 0.0,
                "max": 99.99,
                "value": 13.37
            }
        }
    }
    ```

# API endpoint documentation

The API will consist of three different actor types: Client, Server and Sensor/Actuator.
The Server is them main controller that clients can reach and interact with. It in turn sends requests to the sensors/actuators.

## Device types

There are several types of sensor/actuator devices, a preliminary list is included below.

### Actuators

- switch
- button
- fan
- lamp-generic
- lamp-hue-color
- lamp-hue-white
- alarm

### Sensors

- thermometer
- hygrometer
- movement-sensor
- rfid-reader
- brightness-sensor
- generic-boolean
- generic-8bit
- generic-16bit

## Control server endpoints

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

# Smart Home Ideas

This document is meant to collect ideas of creating a smart home based on API functionality.

## Brainstorming

This brainstorm collects a many bullet points containing ideas. They will get more structured over time, ultimately leading to a concept.md.

### Device states

Every device should have a state. State ideas:

- turned off
- available
- error
- starting
- shutting down

### Endpoint stuff

API endpoint collection:

- /register
  - registers a new device
- /remove
  - deletes device
- /get
  - value to get in parameter
  - returns value
- /set
  - value in parameter
  - sets value provided to endpoint

### Device types

Device types to be used are listed here. One physical device can contain multiple devices! Example: Light Sensor, Temperature Sensor and Fan controlled by one Raspberry Pi. For more information, see the Architecture.

- Lamp
- Temperature Sensor
- Light Sensor
- Movement sensor
- Camera
- Sensor (really necessary?)
- Server
- Networking infra
- Fan
- IoT device (really necessary?)
- other
- Alarm
- Media Player
- Actuator

### Wanted capabilities

This is a list of capabilities ideally included in the smart home API and devices.

- Changing device data (e.g. light on / off / color change)
- Getting device data, e.g. temperature, light level, ...
- Getting device status (e.g. available / offline / error ...)
- one endpoint per type, e.g. temperature fan system != temperature sensor system
  - they might interact though! --> but who controls the interaction? central server.
- Central server that control apps connect to
- Use authentication (e.g. OAuth2)
- Use encryption (maybe not immediately, but keep in mind while developing)
- Logging to a central server running something like splunk
- Statistics server with own endpoints returning data for plotting (e.g. temperature over time)
- Services on system, e.g. SSH / Web server or Guest Wifi / Spotify media player (maybe, but sounds fun)
- Event subscription using something like web hooks
  - Examples: Temperature sensor sends data to statistics server every minute, Door opens -> sensor sends event to logging server
- Routines: specific triggers (e.g. time, device connecting to wifi, temperature threshold) lead to actions (turn on lights, push notification, increase fan speed, ...)
  - more complex programs could be possible, e.g. Turn on lights at 6:30, turn on alarm sound until button is pressed
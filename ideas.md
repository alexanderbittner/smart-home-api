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

This part has been moved to endpoints[.]md, please look at this file for more information

### Device types

This part has been moved to endpoints[.]md, please look at this file for more information.
However, future ideas that might be added later can be found below:

Device types to be used are listed here. One physical device can contain multiple devices! Example: Light Sensor, Temperature Sensor and Fan controlled by one Raspberry Pi. For more information, see the Architecture. Different device types might perform similar actions, e.g. an Actuator could be assigned a specific value just like a lightbulb. Distinction between types is still important for grouping and distinction through (for example) symbols in a mobile app.

- Camera
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

## Security concerns

One of the largest issues of the Internet of Things is the high percentage of vulnerable or poorly secured devices accessing the internet.
Therefore, some security measures should be implemented:

- All smart home devices should be located in a network that is only connected to the internet periodically in case updates are needed
  - This network should be internally separated from all other networks, at least by using different VLANs.
  - The control server has interfaces in the smart home and regular network.
- The control server should collect logs from all devices and forward them to a different server for analysis and anomaly detection
- All external requests to the control server should use HTTPS and OAuth 2.0
- The control server is open to the Internet and should therefore be isolated from the regular network where possible

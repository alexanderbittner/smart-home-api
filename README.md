# smart-home-api

This project is entirely developed in my free time. It might take a while to complete, but will remain active. If you have suggestions or ideas for improvement, please let me know!

## Roadmap

### [DONE] Phase 0: Determine initial architecture, set up infrastructure, plan implementation

Instead of starting this project by blindly implementing spontaneous ideas, some planning in advance should hopefully help avoiding headaches later!

### [DONE] Phase 1: Implement dummy devices + controllers

These dummy devices should have working API endpoints for testing purposes, but no physical devices yet. This makes development faster and more secure: If there are issues, no actual devices are affected.

### [In Progress] Phase 2: Set up and implement the central control server

This phase consists of several steps:

1. Set up the host system of the server
2. Set up logging and a Splunk forwarder
3. Implement the device registration system
4. Set up an online endpoint for the API

### [Planned] Phase 3: Initial testing of OAuth 2.0

Using proper authentication for the smart home API is one of the most important aspects of a secure setup.

### [In Progress] Phase 4: Implement smart home devices + controllers

Once the central controller is set up, the first physical device functionality can be implemented. This will start with simple sensors for light and temperature and will eventually include more complex endpoints (like enumerating the systems connected to a wi-fi network.) This phase will probably lead to the most discovered flaws discovered in the architecture as real use-time accumulates.

### [Planned] Phase 5: Implement programming functionality

Combinbing different events in order to create a complex workflow is the best aspect of having a smart home - I'm really looking forward to implementing this!

### [Planned] Start next development iterations

This project will likely never be 'completed': An iterative process of implementing small improvements is the end goal. After the first iteration is complete, a lot of issues will probably reveal themselves. This is the time to fix them!

## Idea collection

This brainstorm collects a many bullet points containing ideas.

### Device types

This part has been moved to endpoints[.]md, please look at this file for more information.
However, future ideas that might be added later can be found below:

Device types to be used are listed here. One physical device ("device controller") can contain multiple devices! Example: Light Sensor, Temperature Sensor and Fan controlled by one Raspberry Pi. Different device types might perform similar actions, e.g. an Actuator could be assigned a specific value just like a lightbulb. Distinction between types is still important for grouping and distinction through (for example) symbols in a mobile app. Device types that are not yet implemented but wanted:

- Camera
- Media Player (more than just audio)
- Servo or other physical actuator, e.g. door lock
- Digital services, e.g. wifi-clients, vpn-connections

### Wanted capabilities

This is a list of capabilities ideally included in the smart home API and devices.

- Changing device data (e.g. light on / off / color change)
- Getting device data, e.g. temperature, light level, ...
- Getting device status (e.g. available / offline / error ...)
- Central server that control apps connect to
- Use authentication (e.g. OAuth2)
- Logging to a central log server running something like splunk
- Statistics server with own endpoints returning data for plotting (e.g. temperature over time, could be part of the control server)
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
- The control server should only be accessible locally or for VPN connected clients

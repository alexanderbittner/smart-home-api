# smart-home-api

This project is entirely developed in my free time. It might take a while to complete, but will remain active. If you have suggestions or ideas for improvement, please let me know!

## Roadmap

### [In progress] Phase 0: Determine initial architecture, set up infrastructure, plan implementation

Instead of starting this project by blindly implementing spontaneous ideas, some planning in advance should hopefully help avoiding headaches later!

### [In progress] Phase 1: Implement dummy devices + controllers

These dummy devices should have working API endpoints for testing purposes, but no physical devices yet. This makes development faster and more secure: If there are issues, no actual devices are affected.

### [Planned] Phase 2: Set up and implement the central control server

This phase consists of several steps:

1. Set up the host system of the server
2. Set up logging and a Splunk forwarder
3. Implement the device registration system
4. Set up an online endpoint for the API

### [Planned] Phase 3: Initial testing of OAuth 2.0

Using proper authentication for the smart home API is one of the most important aspects of a secure setup.

### [Planned] Phase 4: Implement smart home devices + controllers

Once the central controller is set up, the first physical device functionality can be implemented. This will start with simple sensors for light and temperature and will eventually include more complex endpoints (like enumerating the systems connected to a wi-fi network.) This phase will probably lead to the most discovered flaws discovered in the architecture as real use-time accumulates.

### [Planned] Phase 5: Implement programming functionality

Combinbing different events in order to create a complex workflow is the best aspect of having a smart home - I'm really looking forward to implementing this!

### [Planned] Start next development iterations

This project will likely never be 'completed': An iterative process of implementing small improvements is the end goal. After the first iteration is complete, a lot of issues will probably reveal themselves. This is the time to fix them!

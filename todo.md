# Todo

- [ ] Finalise the state architecture
- [ ] Add rooms
  - Keep devices "stupid", so do not include e.g. whether a light turns off with the room or not. This logic should be added in the controller later. Example: When there is no one left in a room and no movement, turn off all devices. Except when temp > 30C, then keep fan running.
- [ ] Add zones/groups
- [ ] finalize design for control server / endpoint registration, subscription and communication. Some thoughts:
  - what should the /subscribe POST request contain?
  - how should offline devices be treated?
  - If sensor readings take a few seconds (e.g. as with DHT22), should a local copy be sent? maybe only if recent? This should be documented, including a possible time limit that endpoint controllers must adhere to.

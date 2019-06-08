# Todo

- [ ] Finalise the state architecture
- [ ] Add rooms
  - Keep devices "stupid", so do not include e.g. whether a light turns off with the room or not. This logic should be added in the controller later. Example: When there is no one left in a room and no movement, turn off all devices. Except when temp > 30C, then keep fan running.
- [ ] Add zones/groups
- [ ] finalize design for control server / endpoint registration, subscription and communication. Some thoughts:
  - what should the /subscribe POST request contain?
  - how should offline devices be treated?
  - If sensor readings take a few seconds (e.g. as with DHT22), should a local copy be sent? maybe only if recent? This should be documented, including a possible time limit that endpoint controllers must adhere to.
- [ ] add a music player, with state details: song name, song artist, song album, song length, elapsed length, playing/paused and the options to skip
  - should skip be done by a call to a different URL? should it be a part of the state json object and then changed with a POST request? This would be redundant data info from player to controller as the returned `skip:boolean` would always be false.
- [ ] Look into multi-room music playback integration (similar to SONOS, the amazon echo dot API has useful things: [Link](https://developer.amazon.com/docs/mrm/multi-room-music-sdk-overview.html), maybe this could be integrated.
- [ ] Look into more complex devices, such as cameras. A URL to the video stream could be included in order to enhance compatibility, or should the URL /stream be the norm? Should all non-text data content (Audio / Video stream, image) be hosted on a separate URL?
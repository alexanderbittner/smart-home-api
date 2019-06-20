# Todo

Collection of things that are on the to-do list, not ordered by priority. Done below.

## TODO

- [ ] Document the state architecture
- [ ] Add rooms / zones / groups
- [ ] add a music player, with state details:
  - [ ] song name
  - [ ] song artist
  - [ ] song album
  - [ ] song length
  - [ ] elapsed length
  - [ ] playing/pause
  - [ ] the options to skip
  - this should utilize separate endpoints:
    - [ ] `POST /skip` (with 0 seconds in json)
    - [ ] `POST /skip` (with amount of seconds in json body )
- [ ] Look into multi-room music playback integration (similar to SONOS, the amazon echo dot API has useful things: [Link](https://developer.amazon.com/docs/mrm/multi-room-music-sdk-overview.html), maybe this could be integrated.
- [ ] add documentation of controller - endpoint communication
- [ ] Improve pairing, maybe overcome wifi credential hardcoding.

## DONE

- [x] Finalise the state architecture
- [x] finalize design for control server / endpoint registration, subscription and communication. Some thoughts:
  - what should the /subscribe POST request contain?
    -> state with changed variables
  - how should offline devices be treated?
    -> add "online" tag on controller, set to false if unreachable; devices should have the ability to subscribe to a heartbeat
  - If sensor readings take a few seconds (e.g. as with DHT22), should a local copy be sent? maybe only if recent? This should be documented, including a possible time limit that endpoint controllers must adhere to.
    -> NO
  - what happens if one endpoint controls more than one resource of the same type? -> every endpoint has a UID, UID is sent with the state.
  - should endpoint devices hold their own name / id? This might be the best option. -> see above
- [x] Look into more complex devices, such as cameras. A URL to the video stream could be included in order to enhance compatibility, or should the URL /stream be the norm? Should all non-text data content (Audio / Video stream, image) be hosted on a separate URL? -> yes, separate URL

# DeadlockFPS

Standalone first-person camera prototype for Deadlock research and permitted offline experiments.

**Status: prototype / integration not included.** This repository does not currently change Deadlock's live gameplay camera. It contains a reusable camera controller, configuration, math tests, and an abstract host interface. No game injection, memory patching, anti-cheat bypass, or multiplayer advantage features are included.

## Relationship to Dolly

Deadlock Dolly describes itself as a camera-path editor for local replays. Its README says native mode uses a matching helper and reviewed game builds. Dolly is useful background for camera concepts, but its replay camera is not proof of a supported live-game camera API.

DeadlockFPS starts with the camera-control core and leaves game-specific integration behind an explicit adapter boundary. A future adapter must use a documented, permitted interface and be tested in an offline/private environment. Do not use this project to evade game protections or gain an unfair advantage in public matches.

## Included

- C++20 camera state and smoothing controller
- Configurable vertical offset, field of view, smoothing, and enable state
- Angle normalization and shortest-path angle interpolation
- Abstract ICameraHost boundary (no process access or game hooks)
- Command-line demo and unit tests
- CMake build

## Build

Requires CMake 3.20+ and a C++20 compiler.

    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
    ctest --test-dir build --output-on-failure

Run the demo with ./build/deadlockfps_demo (Windows multi-config builds usually place it under build/Release).

## Configuration

See config/default.json. The core API accepts CameraConfig directly so a future front end can own config parsing.

| Setting | Meaning | Default |
|---|---|---:|
| enabled | Enable prototype camera state | true |
| vertical_offset | Camera height offset in world units | 0.0 |
| fov_degrees | Requested vertical FOV | 90 |
| smoothing | Smoothing strength, 0–1 | 0.15 |
| near_clip | Suggested near clipping distance | 2.0 |

These are starting points, not validated Deadlock character measurements.

## Architecture

- include/deadlockfps/: public data types and controller API
- src/: implementation
- demo/: host-independent demonstration
- tests/: deterministic math/controller tests
- config/: example settings

The host adapter is intentionally an interface only. It does not locate, inject into, read, or modify the Deadlock process. Any future integration must use an explicitly supported interface and be reviewed for game rules and safety.

## Roadmap

- [x] Standalone camera math/controller
- [x] Config data model and example
- [x] Demo host and automated tests
- [ ] User-facing settings UI
- [ ] Documented, permitted offline host adapter (only if a supported interface exists)
- [ ] Per-hero calibration data gathered in a permitted test environment

## License

MIT. See LICENSE.

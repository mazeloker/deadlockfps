#pragma once
namespace deadlockfps {
struct Vec3 { float x{0.0F}; float y{0.0F}; float z{0.0F}; };
struct Angles { float pitch{0.0F}; float yaw{0.0F}; float roll{0.0F}; };
struct CameraPose { Vec3 position{}; Angles rotation{}; float fov_degrees{90.0F}; };
struct CameraConfig {
    bool enabled{true};
    float vertical_offset{0.0F};
    float fov_degrees{90.0F};
    // 0 = no smoothing, values near 1 = heavier smoothing.
    float smoothing{0.15F};
    float near_clip{2.0F};
};
} // namespace deadlockfps

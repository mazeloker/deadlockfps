#include "deadlockfps/camera_controller.hpp"
#include <algorithm>
#include <cmath>
namespace deadlockfps {
namespace {
float clamp_fov(float value) {
    return std::isfinite(value) ? std::clamp(value, 60.0F, 120.0F) : 90.0F;
}
float smooth_factor(float smoothing, float delta_seconds) {
    const float s = std::clamp(smoothing, 0.0F, 1.0F);
    const float dt = std::clamp(delta_seconds, 0.0F, 0.25F);
    if (s <= 0.0F) return 1.0F;
    const float time_constant = 0.005F + s * 0.245F;
    return 1.0F - std::exp(-dt / time_constant);
}
float lerp(float a, float b, float t) { return a + (b - a) * t; }
Vec3 lerp(Vec3 a, Vec3 b, float t) {
    return {lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t)};
}
}
CameraController::CameraController(CameraConfig config) { set_config(config); }
void CameraController::set_config(CameraConfig config) {
    config.vertical_offset = std::isfinite(config.vertical_offset) ? std::clamp(config.vertical_offset, -128.0F, 128.0F) : 0.0F;
    config.fov_degrees = clamp_fov(config.fov_degrees);
    config.smoothing = std::isfinite(config.smoothing) ? std::clamp(config.smoothing, 0.0F, 1.0F) : 0.15F;
    config.near_clip = std::isfinite(config.near_clip) ? std::clamp(config.near_clip, 0.1F, 16.0F) : 2.0F;
    config_ = config;
}
const CameraConfig& CameraController::config() const noexcept { return config_; }
CameraPose CameraController::make_target(Vec3 eye_position, Angles view_angles) const {
    eye_position.z += config_.vertical_offset;
    return {eye_position,
        {normalize_angle(view_angles.pitch), normalize_angle(view_angles.yaw), normalize_angle(view_angles.roll)},
        config_.fov_degrees};
}
CameraPose CameraController::update(const CameraPose& target, float delta_seconds) {
    if (!config_.enabled) return target;
    CameraPose safe = target;
    safe.fov_degrees = clamp_fov(safe.fov_degrees);
    safe.rotation.pitch = normalize_angle(safe.rotation.pitch);
    safe.rotation.yaw = normalize_angle(safe.rotation.yaw);
    safe.rotation.roll = normalize_angle(safe.rotation.roll);
    if (!initialized_) { current_ = safe; initialized_ = true; return current_; }
    const float t = smooth_factor(config_.smoothing, delta_seconds);
    current_.position = lerp(current_.position, safe.position, t);
    current_.rotation.pitch = normalize_angle(current_.rotation.pitch + angle_delta(current_.rotation.pitch, safe.rotation.pitch) * t);
    current_.rotation.yaw = normalize_angle(current_.rotation.yaw + angle_delta(current_.rotation.yaw, safe.rotation.yaw) * t);
    current_.rotation.roll = normalize_angle(current_.rotation.roll + angle_delta(current_.rotation.roll, safe.rotation.roll) * t);
    current_.fov_degrees = lerp(current_.fov_degrees, safe.fov_degrees, t);
    return current_;
}
void CameraController::reset() noexcept { current_ = {}; initialized_ = false; }
float CameraController::normalize_angle(float degrees) noexcept {
    if (!std::isfinite(degrees)) return 0.0F;
    float value = std::fmod(degrees + 180.0F, 360.0F);
    if (value < 0.0F) value += 360.0F;
    return value - 180.0F;
}
float CameraController::angle_delta(float from, float to) noexcept { return normalize_angle(to - from); }
} // namespace deadlockfps

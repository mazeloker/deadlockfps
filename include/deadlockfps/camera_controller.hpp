#pragma once
#include "deadlockfps/camera_types.hpp"
namespace deadlockfps {
class CameraController {
public:
    explicit CameraController(CameraConfig config = {});
    void set_config(CameraConfig config);
    [[nodiscard]] const CameraConfig& config() const noexcept;
    // Uses only caller-supplied position and angles; it never reads a game process.
    [[nodiscard]] CameraPose make_target(Vec3 eye_position, Angles view_angles) const;
    [[nodiscard]] CameraPose update(const CameraPose& target, float delta_seconds);
    void reset() noexcept;
    [[nodiscard]] static float normalize_angle(float degrees) noexcept;
    [[nodiscard]] static float angle_delta(float from, float to) noexcept;
private:
    CameraConfig config_{};
    CameraPose current_{};
    bool initialized_{false};
};
} // namespace deadlockfps

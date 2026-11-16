#include "deadlockfps/camera_controller.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
using namespace deadlockfps;
static bool near(float a, float b, float e = 0.01F) { return std::fabs(a - b) <= e; }
int main() {
    assert(near(CameraController::normalize_angle(190.0F), -170.0F));
    assert(near(CameraController::angle_delta(179.0F, -179.0F), 2.0F));
    CameraConfig cfg; cfg.vertical_offset = 4.0F; cfg.fov_degrees = 140.0F; cfg.smoothing = 0.0F;
    CameraController camera(cfg);
    assert(near(camera.config().fov_degrees, 120.0F));
    const auto target = camera.make_target({1.0F, 2.0F, 3.0F}, {0.0F, 181.0F, 0.0F});
    assert(near(target.position.z, 7.0F));
    assert(near(target.rotation.yaw, -179.0F));
    const auto first = camera.update(target, 1.0F / 60.0F);
    assert(near(first.position.x, 1.0F));
    const auto moved = camera.update({{9.0F, 8.0F, 7.0F}, {0.0F, -170.0F, 0.0F}, 100.0F}, 1.0F / 60.0F);
    assert(near(moved.position.x, 9.0F)); assert(near(moved.fov_degrees, 100.0F));
    CameraConfig smooth_cfg; smooth_cfg.smoothing = 0.9F;
    CameraController smooth_camera(smooth_cfg);
    smooth_camera.update({{0,0,0}, {0,0,0}, 90}, 1.0F / 60.0F);
    const auto partial = smooth_camera.update({{100,0,0}, {0,0,0}, 90}, 1.0F / 60.0F);
    assert(partial.position.x > 0.0F && partial.position.x < 100.0F);
    std::cout << "All DeadlockFPS tests passed.\n";
}

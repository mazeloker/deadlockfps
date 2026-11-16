#include "deadlockfps/camera_controller.hpp"
#include <iomanip>
#include <iostream>
int main() {
    deadlockfps::CameraConfig config;
    config.fov_degrees = 95.0F;
    config.smoothing = 0.2F;
    deadlockfps::CameraController camera(config);
    const auto target = camera.make_target({120.0F, 45.0F, 64.0F}, {2.0F, 179.0F, 0.0F});
    std::cout << "DeadlockFPS camera-core demo (host-independent)\n" << std::fixed << std::setprecision(2);
    for (int frame = 0; frame < 5; ++frame) {
        const auto pose = camera.update(target, 1.0F / 60.0F);
        std::cout << "frame " << frame << " | pos=(" << pose.position.x << ", " << pose.position.y << ", " << pose.position.z
                  << ") | angles=(" << pose.rotation.pitch << ", " << pose.rotation.yaw << ", " << pose.rotation.roll
                  << ") | FOV=" << pose.fov_degrees << '\n';
    }
    std::cout << "\nThis demo does not connect to or modify Deadlock.\n";
    return 0;
}

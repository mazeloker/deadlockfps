#pragma once
#include "deadlockfps/camera_types.hpp"
namespace deadlockfps {
// Integration seam for a future host that explicitly permits camera overrides.
// No injector, memory reader, hook, or implementation is provided here.
class ICameraHost {
public:
    virtual ~ICameraHost() = default;
    [[nodiscard]] virtual bool read_view(Vec3& eye_position, Angles& view_angles) = 0;
    virtual bool write_camera(const CameraPose& pose) = 0;
};
} // namespace deadlockfps

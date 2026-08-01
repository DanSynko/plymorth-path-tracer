export module path_tracing_objects;

#ifdef __INTELLISENSE__
#include <vector>
#else
import std;
#endif

import linear_algebra;

export namespace plymorth {
struct Ray {
    Vec3 origin;
    Vec3 direction;
};

struct Sphere {
    Vec3 position;
    float radius;
};
} // namespace plymorth
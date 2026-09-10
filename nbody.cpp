#include <iostream>
#include <vector>
#include <cmath>
// #include <thread>
// #include <chrono>

struct Vec3 {
    double x{0.0}, y{0.0}, z{0.0};

    // vector addition: a + b
    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    // in-place addition: a += b
    Vec3& operator+=(const Vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    // overload vector subtraction and compute directional displacement from 'other' to '*this'
    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    // in-place subtraction: a -= b
    Vec3& operator-=(const Vec3& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    // negation: -a
    Vec3 operator-() const {
        return {-x, -y, -z};
    }

    // overload scalar multiplication
    Vec3 operator*(double s) const {
        return {x * s, y * s, z * s};
    }

    // in-place scalar multiplication: a *= s
    Vec3& operator*=(double s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    // scalar division: a / s
    Vec3 operator/(double s) const {
        return {x / s, y / s, z / s};
    }

    // in-place scalar division: a /= s
    Vec3& operator/=(double s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    // squared length; avoids the sqrt when only comparing magnitudes
    double norm_sq() const {
        return x * x + y * y + z * z;
    }

    // euclidean length
    double norm() const {
        return std::sqrt(norm_sq());
    }
};

// scalar on the left: s * a
inline Vec3 operator*(double s, const Vec3& v) {
    return v * s;
}

struct Body {
    double mass{0.0};
    Vec3 position;
    Vec3 velocity;
    Vec3 acceleration;
};

// TODO: accumulate the pairwise gravitational acceleration on every body.
//
// Zero every body's acceleration first, then loop over each unordered pair
// (i, j) with j > i so each interaction is evaluated exactly once.
//
// For a pair, let r = bodies[j].position - bodies[i].position (points from i
// toward j). Newtonian gravity gives the acceleration on i as:
//
//     a_i += G * m_j * r / |r|^3
//     a_j -= G * m_i * r / |r|^3        (equal and opposite force, Newton's 3rd)
//
// SOFTENING PARAMETER: |r|^3 blows up as two bodies approach each other, which
// makes close encounters eject particles at absurd velocities and destroys the
// energy conservation of the integrator. Add a softening length eps (a small
// constant with units of distance, e.g. 1e-3 in simulation units) to the
// denominator so the force stays finite at r -> 0:
//
//     denom = (r.norm_sq() + eps*eps)^(3/2)
//     a_i += r * (G * m_j / denom)
//     a_j -= r * (G * m_i / denom)
//
// Compute denom once per pair with std::pow(r.norm_sq() + eps*eps, 1.5), and
// note that norm_sq() is used deliberately here: no sqrt is needed separately.
// Choose eps larger than the closest approach you care to resolve but small
// enough not to distort the large-scale dynamics.
void compute_gravity(std::vector<Body>& bodies) {
}

// TODO: advance the simulation by dt using VELOCITY VERLET (kick-drift-kick).
//
// Velocity Verlet is symplectic and second-order accurate, so it conserves
// energy far better than Euler at the same step size. One step, given the
// accelerations a(t) already stored on each body by compute_gravity:
//
//   1. HALF KICK:  v(t + dt/2) = v(t) + a(t) * (dt / 2)
//   2. DRIFT:      x(t + dt)   = x(t) + v(t + dt/2) * dt
//   3. RECOMPUTE:  a(t + dt)   = compute_gravity(bodies)   // at the NEW positions
//   4. HALF KICK:  v(t + dt)   = v(t + dt/2) + a(t + dt) * (dt / 2)
//
// Order matters: the drift in step 2 must use the half-updated velocity, and
// the accelerations must be refreshed in step 3 before the second half kick,
// otherwise the method degrades to plain Euler and leaks energy.
//
// This assumes a(t) is valid on entry, so main() must call compute_gravity()
// once before the first step (or step_simulation() must do it on the first
// call) to prime the accelerations.
void step_simulation(std::vector<Body>& bodies, double dt) {
}

// TODO: set up the initial bodies, run the integration loop, report the results.
//
//   1. Build a std::vector<Body> with the initial masses, positions and
//      velocities (e.g. a two-body circular orbit as a sanity check).
//   2. Prime the accelerations with a single compute_gravity(bodies) call.
//   3. Loop for N steps calling step_simulation(bodies, dt), printing the
//      positions (and ideally the total energy, which should stay ~constant)
//      every so many steps.
int main() {
    return 0;
}

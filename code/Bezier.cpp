#include "Bezier.hpp"

#include <glm/exponential.hpp>

glm::vec2 lerp(glm::vec2 cref a, glm::vec2 cref b, float t) {
    assert((0 <= t) and (t <= 1));
    return (1 - t) * a + t * b;
}

glm::vec2 getBezierPointFor(glm::vec2 cref p0, glm::vec2 cref p1, glm::vec2 cref p2, glm::vec2 cref p3, float t) {
    assert((0 <= t) and (t <= 1));
    let q1 = lerp(p0, p1, t);
    let q2 = lerp(p1, p2, t);
    let q3 = lerp(p2, p3, t);
    let q4 = lerp(q1, q2, t);
    let q5 = lerp(q2, q3, t);
    return lerp(q4, q5, t);
}

glm::vec2 getTangentForBezierAt(glm::vec2 cref p0, glm::vec2 cref p1, glm::vec2 cref p2, glm::vec2 cref p3, float t) {
    assert((0 <= t) and (t <= 1));
    // magical recipe for derivative
    let t2 = glm::pow(t, 2.f);
    let q1 = p0 * ((t2 * -3.f) + (t * 6.f) - 3.f);
    let q2 = p1 * ((t2 * 9.f) + (t * -12.f) + 3.f);
    let q3 = p2 * ((t2 * -9.f) + (t * 6.f));
    let q4 = p3 * ((t2 * 3.f));
    return q1 + q2 + q3 + q4;
}

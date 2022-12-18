
#include "SingleQBezier.hpp"

#include "Bezier.hpp"

glm::vec2 SingleQBezier::getPointAt(float t) const {
    return getBezierPointFor(getP0(), getP1(), getP2(), getP3(), t);
}

glm::vec2 SingleQBezier::getTangentAt(float t) const {
    return getTangentForBezierAt(getP0(), getP1(), getP2(), getP3(), t);
}

glm::vec2 SingleQBezier::getKnotA() const {
    return p0;
}

glm::vec2 SingleQBezier::getKnotB() const {
    return p3;
}

glm::vec2 SingleQBezier::getHandleA() const {
    return p1;
}

glm::vec2 SingleQBezier::getHandleB() const {
    return p2;
}

void SingleQBezier::setKnotA(glm::vec2 cref arg) {
    p0 = arg;
}

void SingleQBezier::setKnotB(glm::vec2 cref arg) {
    p3 = arg;
}

void SingleQBezier::setHandleA(glm::vec2 cref arg) {
    p0 = arg;
}

void SingleQBezier::setHandleB(glm::vec2 cref arg) {
    p3 = arg;
}

SingleQBezier::SingleQBezier(glm::vec2 cref knotA, glm::vec2 cref knotB, glm::vec2 cref handleA,
                             glm::vec2 cref handleB) :
        p0(handleA),
        p1(knotA),
        p2(knotB),
        p3(handleB) {
}

SingleQBezier
SingleQBezier::makeWithKnotsAndHandles(glm::vec2 cref kA, glm::vec2 cref kB, glm::vec2 cref hA, glm::vec2 cref hB) {
    return {kA, kB, hA, hB};
}


glm::vec2 SingleQBezier::getP0() const {
    return p0;
}

glm::vec2 SingleQBezier::getP1() const {
    return p1;
}

glm::vec2 SingleQBezier::getP2() const {
    return p2;
}

glm::vec2 SingleQBezier::getP3() const {
    return p3;
}

void SingleQBezier::setP0(glm::vec2 cref arg) {
    p0 = arg;
}

void SingleQBezier::setP1(glm::vec2 cref arg) {
    p1 = arg;
}

void SingleQBezier::setP2(glm::vec2 cref arg) {
    p2 = arg;
}

void SingleQBezier::setP3(glm::vec2 cref arg) {
    p3 = arg;
}

SingleQBezier
SingleQBezier::makeWithFourControls(glm::vec2 cref p1, glm::vec2 cref p2, glm::vec2 cref p3, glm::vec2 cref p4) {
    return {p2, p3, p1, p4};
}

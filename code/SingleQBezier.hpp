#pragma once

#include "utilities.hpp"
#include <glm/vec2.hpp>

class SingleQBezier {
public:
    ND static SingleQBezier
    makeWithFourControls(glm::vec2 cref p0, glm::vec2 cref p1, glm::vec2 cref p2, glm::vec2 cref p3);

    ND static SingleQBezier
    makeWithKnotsAndHandles(glm::vec2 cref kA, glm::vec2 cref kB, glm::vec2 cref hA, glm::vec2 cref hB);

    void setKnotA(glm::vec2 cref arg);
    void setKnotB(glm::vec2 cref arg);

    void setHandleA(glm::vec2 cref arg);
    void setHandleB(glm::vec2 cref arg);

    void setP0(glm::vec2 cref);
    void setP1(glm::vec2 cref);
    void setP2(glm::vec2 cref);
    void setP3(glm::vec2 cref);

    ND glm::vec2 getP0() const;
    ND glm::vec2 getP1() const;
    ND glm::vec2 getP2() const;
    ND glm::vec2 getP3() const;

    ND glm::vec2 getKnotA() const;
    ND glm::vec2 getKnotB() const;

    ND glm::vec2 getHandleA() const;
    ND glm::vec2 getHandleB() const;

    ND glm::vec2 getPointAt(float t) const;
    ND glm::vec2 getTangentAt(float t) const;

private:
    SingleQBezier(glm::vec2 cref knotA, glm::vec2 cref knotB, glm::vec2 cref handleA, glm::vec2 cref handleB);

    glm::vec2 p0;
    glm::vec2 p1;
    glm::vec2 p2;
    glm::vec2 p3;
};

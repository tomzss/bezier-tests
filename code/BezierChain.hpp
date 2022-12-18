#pragma once

#include "SingleQBezier.hpp"

class BezierChain {
public:
    /// ---- create ----
    explicit BezierChain(glm::vec2 cref firstControl);
    explicit BezierChain(std::vector<glm::vec2>);

    /// ---- get ----
    ND std::size_t getSegmentsCount() const;
    ND SingleQBezier getSegment(std::size_t index) const;

    ND std::size_t getControlsCount() const;
    ND glm::vec2 cref getControl(std::size_t index) const;

    /// Point in curve.
    /// t have to be in range [0;1]
    ND glm::vec2 getPoint(float t) const;
    ND glm::vec2 getTangent(float t) const;

    /// ---- modify ----
    void addSegmentBack(glm::vec2 handle1, glm::vec2 handle2, glm::vec2 knot);
    void addSmoothSegmentBack(glm::vec2 cref handle, glm::vec2 cref knot);

    /// Adds segment merging end of the curve with it's beginning
    void close(glm::vec2 cref handle1, glm::vec2 cref handle2);
    void closeSmooth();

    void removeLastSegment();

private:
    std::vector<glm::vec2> controls;
};

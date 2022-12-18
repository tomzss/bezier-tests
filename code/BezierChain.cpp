#include "BezierChain.hpp"

#include <cmath>
#include <utility>


glm::vec2 BezierChain::getPoint(float t) const {
    assert(0 <= t and t <= 1);
    if (t == 1)
        return getSegment(getSegmentsCount() - 1).getPointAt(1);
    let segmentIndexFloat = float(getSegmentsCount()) * t;
    let segmentIndex = std::size_t(std::floor(segmentIndexFloat));
    let segment = getSegment(segmentIndex);
    return segment.getPointAt((t - float(segmentIndex) / float(getSegmentsCount())) * float(getSegmentsCount()));
}

glm::vec2 BezierChain::getTangent(float t) const {
    assert(0 <= t and t <= 1);
    if (t == 1)
        return getSegment(getSegmentsCount() - 1).getTangentAt(1);
    let segmentIndexFloat = float(getSegmentsCount()) * t;
    let segmentIndex = std::size_t(std::floor(segmentIndexFloat));
    let segment = getSegment(segmentIndex);
    return segment.getTangentAt((t - float(segmentIndex) / float(getSegmentsCount())) * float(getSegmentsCount()));
}

std::size_t BezierChain::getSegmentsCount() const {
    if (getControlsCount() < 4)
        return 0;
    assert((getControlsCount() - 1) % 3 == 0);
    return (getControlsCount() - 1) / 3;
}

std::size_t BezierChain::getControlsCount() const {
    return controls.size();
}

SingleQBezier BezierChain::getSegment(std::size_t segmentIndex) const {
    assert(segmentIndex < getSegmentsCount());
    let firstControlIndex = segmentIndex * 3;
    return SingleQBezier::makeWithFourControls(
            getControl(firstControlIndex + 0),
            getControl(firstControlIndex + 1),
            getControl(firstControlIndex + 2),
            getControl(firstControlIndex + 3));
}

glm::vec2 cref BezierChain::getControl(std::size_t index) const {
    assert(index < getControlsCount());
    return controls[index];
}

BezierChain::BezierChain(glm::vec2 cref firstControl) :
        controls{firstControl} {
}

BezierChain::BezierChain(std::vector<glm::vec2> controls_) :
        controls{std::move(controls_)} {
}

void BezierChain::addSegmentBack(glm::vec2  handle1, glm::vec2  handle2, glm::vec2  knot) {
    controls.reserve(controls.size() + 3);
    controls.emplace_back(handle1);
    controls.emplace_back(handle2);
    controls.emplace_back(knot);
}

void BezierChain::addSmoothSegmentBack(glm::vec2 cref handle, glm::vec2 cref knot) {
    let lastSegment = getSegment(getSegmentsCount() - 1);
    let firstHandle = 2.f * lastSegment.getKnotB() - lastSegment.getHandleB();
    addSegmentBack(firstHandle, handle, knot);
}

void BezierChain::close(glm::vec2 cref handle1, glm::vec2 cref handle2) {
    addSegmentBack(handle1, handle2, getControl(0));
}

void BezierChain::closeSmooth() {
    let firstSegment = getSegment(0);
    let handle = 2.f * firstSegment.getKnotA() - firstSegment.getHandleA();
    addSmoothSegmentBack(handle, getControl(0));
}

void BezierChain::removeLastSegment() {
    controls.resize(controls.size() - 3);
}

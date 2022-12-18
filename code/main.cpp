#include <SFML/Graphics.hpp>
#include "BezierChain.hpp"
#include <glm/gtx/norm.hpp>
#include <deque>
#include <utility>
#include <iostream>


glm::vec2 vec2(sf::Vector2f const &v) {
    return {v.x, v.y};
}

sf::Vector2f vec2(glm::vec2 const &v) {
    return {v.x, v.y};
}

void drawPoint(sf::RenderTarget &target, sf::Vector2f const &position, sf::Color const &color, float radius) {
    auto circle = sf::CircleShape{};
    circle.setRadius(radius);
    circle.setFillColor(color);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);
    target.draw(circle);
}

void drawLine(sf::RenderTarget &target, std::vector<sf::Vector2f> const &points, sf::Color const &color) {
    auto vertexArray = sf::VertexArray{sf::LineStrip, points.size()};
    for (auto i = 0; i < vertexArray.getVertexCount(); ++i) {
        vertexArray[i].position = points[i];
        vertexArray[i].color = color;
    }
    target.draw(vertexArray);
}

sf::VertexArray generateGeometryThin(SingleQBezier const &curve, sf::Color const &color, unsigned resolution) {
    auto vertexArray = sf::VertexArray{sf::LineStrip, resolution + 1};
    for (auto i = 0; i < vertexArray.getVertexCount(); ++i) {
        vertexArray[i].position = vec2(curve.getPointAt(float(i) / float(resolution)));
        vertexArray[i].color = color;
    }
    return vertexArray;
}

glm::vec2 rotate90a(glm::vec2 const &vec) {
    return {vec.y, -vec.x};
}

glm::vec2 rotate90b(glm::vec2 const &vec) {
    return {-vec.y, vec.x};
}

glm::vec2 setLength(glm::vec2 const &vec, float newLength) {
    let oldLength = glm::length(vec);
    if (oldLength == 0)
        return {0, 0};
    return vec * (newLength / oldLength);
}

sf::VertexArray
generateGeometryThick(BezierChain cref curveChain, sf::Color const &color, unsigned resolution, float thickness) {
    auto vertexArray = sf::VertexArray{sf::TriangleStrip, resolution + 2};
    for (auto i = 0; i < vertexArray.getVertexCount(); i += 2) {
        assert(i < vertexArray.getVertexCount());
        let t = float(i) / float(resolution);
        let point = curveChain.getPoint(t);
        let tangent = curveChain.getTangent(t);
        vertexArray[i].position = vec2(point + setLength(rotate90a(tangent), thickness / 2.f));
        vertexArray[i + 1].position = vec2(point + setLength(rotate90b(tangent), thickness / 2.f));
        auto randColor = [](sf::Color c) {
            return sf::Color((c.r + std::rand() % 250) / 2,
                             (c.g + std::rand() % 250) / 2,
                             (c.b + std::rand() % 250) / 2);
        };
        if ((vertexArray[i].position.x * vertexArray[i + 1].position.x * vertexArray[i].position.y *
             vertexArray[i + 1].position.y == 0) or
            (std::isnan(vertexArray[i].position.x) or std::isnan(vertexArray[i + 1].position.x) or
             std::isnan(vertexArray[i].position.y) or std::isnan(vertexArray[i + 1].position.y)))
            std::cout << "{" << vertexArray[i].position.x << ", " << vertexArray[i + 1].position.x << "}, {"
                      << vertexArray[i].position.y << ", " << vertexArray[i + 1].position.y << "}\n";
        vertexArray[i].color = randColor(color);
        vertexArray[i + 1].color = randColor(color);
    }
    return vertexArray;
}

struct Chain {
    explicit Chain(BezierChain bChain_) :
            bChain{std::move(bChain_)},
            vertices{sf::Triangles},
            closed{false} {
    }

    BezierChain bChain;
    sf::VertexArray vertices;
    bool closed;
};

int main() {
    auto font = sf::Font{};
    font.loadFromFile("/usr/share/fonts/opentype/firacode/FiraCode-Medium.otf");
    auto text = sf::Text{};
    text.setFont(font);
    text.setFillColor(sf::Color::Blue);
    text.setCharacterSize(15);

    let windowSize = 800u;
    auto window = sf::RenderWindow{{windowSize, windowSize}, "bezier-tests"};
    window.setFramerateLimit(30);

    let curveColor = sf::Color{30, 230, 30};
    let pointsColor = sf::Color::Red;

    auto chains = std::deque<Chain>{};

    let resolution = 100;
    let thickness = 10.f;
    let pointSize = thickness / 2.f;

    auto controlPoints = std::vector<glm::vec2>{};

    auto redoLastGeometry = [&] {
        assert(not chains.empty());
        chains.back().vertices = generateGeometryThick(
                chains.back().bChain, curveColor, resolution * chains.back().bChain.getSegmentsCount(), thickness);
    };

    while (window.isOpen()) {
        auto event = sf::Event{};
        while (window.hasFocus() ? window.pollEvent(event) : window.waitEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::X) {
                        if (not controlPoints.empty()) {
                            controlPoints.pop_back();
                        } else if (not chains.empty()) {
                            if (chains.back().bChain.getSegmentsCount() > 1) {
                                chains.back().bChain.removeLastSegment();
                                redoLastGeometry();
                            } else {
                                chains.pop_back();
                                if (not chains.empty())
                                    redoLastGeometry();
                            }
                        }
                    } else if (event.key.code == sf::Keyboard::Enter) {
                        if ((not chains.empty()) and (not chains.back().closed)) {
                            if (controlPoints.size() >= 2) {
                                chains.back().bChain.close(controlPoints[0], controlPoints[1]);
                                redoLastGeometry();
                                controlPoints.clear();
                            } else {
                                chains.back().bChain.closeSmooth();
                                redoLastGeometry();
                            }
                            chains.back().closed = true;
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed: {
                    let mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                    controlPoints.emplace_back(vec2(mousePos));

                    break;
                }
                default:;
            }
        }

        assert(controlPoints.size() <= 4);
        if ((controlPoints.size() == 4) and (chains.empty() or chains.back().closed)) {
            chains.emplace_back(BezierChain{controlPoints});
            redoLastGeometry();
            controlPoints.clear();
        } else if (not chains.empty()) {
            if ((controlPoints.size() == 2) and (not chains.back().closed)) {
                chains.back().bChain.addSmoothSegmentBack(controlPoints[0], controlPoints[1]);
                redoLastGeometry();
                controlPoints.clear();
            }
        }

        window.clear();

        // points
        for (let chain: chains) {
            if (chain.closed or chain.bChain.getSegmentsCount() == 0)
                continue;
            let point1 = chain.bChain.getSegment(0).getP0();
            let point2 = chain.bChain.getSegment(chain.bChain.getSegmentsCount() - 1).getP0();
            drawPoint(window, vec2(point1), curveColor, thickness / 2.f);
            drawPoint(window, vec2(point2), curveColor, thickness / 2.f);
        }

        // geometry
        for (let chain: chains)
            window.draw(chain.vertices);

        // controlPoints
        for (let controlPoint: controlPoints)
            drawPoint(window, vec2(controlPoint), pointsColor, pointSize);

        window.display();
    }
}

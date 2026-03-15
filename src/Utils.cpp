#include "Utils.hpp"
#include <stdexcept>

namespace Utils {

Point parsePoint(const std::string& token) {
    if (token.length() < 3 || token.front() != '(' || token.back() != ')') {
        throw std::invalid_argument("Malformed point: " + token);
    }
    std::string inner = token.substr(1, token.length() - 2);
    size_t commaPos = inner.find(',');
    if (commaPos == std::string::npos) {
        throw std::invalid_argument("Missing comma in point: " + token);
    }
    Point p{};
    try {
        p.x = std::stoi(inner.substr(0, commaPos));
        p.y = std::stoi(inner.substr(commaPos + 1));
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid coordinates: " + token);
    }
    return p;
}

int parseRadius(const std::string& token) {
    int radius{};
    try {
        radius = std::stoi(token);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid radius value: " + token);
    }
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive: " + token);
    }
    return radius;
}

ZoneType parseZoneType(const std::string& token) {
    if (token == "normal")     return ZoneType::Normal;
    if (token == "restricted") return ZoneType::Restricted;
    if (token == "prohibited") return ZoneType::Prohibited;
    throw std::invalid_argument("Unknown zone type: " + token);
}

} // namespace Utils

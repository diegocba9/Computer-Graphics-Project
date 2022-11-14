#include "AABB.h"
#include <utility>

AABB::AABB(std::string newId, vec3 centerPos, vec3 distances)
{
    id = std::move(newId);
    center = centerPos;
    extends = distances;
}

AABB::~AABB()
= default;

AABB::AABB()
= default;

vec3 AABB::getCenter()
{
    return center;
}

vec3 AABB::getDistances()
{
    return extends;
}

void AABB::setId(std::string newId)
{
    id = std::move(newId);
}

void AABB::setCenter(vec3 centerCoords)
{
    center = centerCoords;
}

void AABB::setDistances(vec3 centerDistances)
{
    extends = centerDistances;
}

void AABB::createBox()
{
    boxCoords.clear();
    boxCoords.emplace_back(center.x + extends.x, center.y + extends.y, center.z + extends.z); //0
    boxCoords.emplace_back(center.x + extends.x, center.y - extends.y, center.z + extends.z); //1
    boxCoords.emplace_back(center.x - extends.x, center.y + extends.y, center.z + extends.z); //2
    boxCoords.emplace_back(center.x - extends.x, center.y - extends.y, center.z + extends.z); //3
    boxCoords.emplace_back(center.x + extends.x, center.y + extends.y, center.z - extends.z); //4
    boxCoords.emplace_back(center.x - extends.x, center.y + extends.y, center.z - extends.z); //5
    boxCoords.emplace_back(center.x + extends.x, center.y - extends.y, center.z - extends.z); //6
    boxCoords.emplace_back(center.x - extends.x, center.y - extends.y, center.z - extends.z); //7
}

void AABB::forward() {
    m_speed = m_direction * (-m_scl);
    vec3 newCenter = center + m_speed;
    setCenter(newCenter);
    for (auto & boxCoord : boxCoords)
    {
        boxCoord = boxCoord + m_speed;
    }
}

void AABB::backward() {
    m_speed = m_direction * (m_scl);
    vec3 newCenter = center + m_speed;
    setCenter(newCenter);
    for (auto & boxCoord : boxCoords)
    {
        boxCoord = boxCoord + m_speed;
    }
}

vec3 AABB::rotate(vec3 point, float ang, vec3 axis) {
    vec3 result;
    result.x = axis.x + (point.x - axis.x) * cos(ang) - (point.z - axis.z) * sin(ang);
    result.z = axis.z + (point.x - axis.x) * sin(ang) + (point.z - axis.z) * cos(ang);
    result.y = point.y;
    return result;
}

float AABB::cvtToRad(float ang) const {
    return (ang * m_PI)/180.0;
}

void AABB::update(float leftRightDirection, vec3 camPosVec) {
    m_yaw += leftRightDirection;
    float ang = cvtToRad(leftRightDirection);
    vec3 newCenter = rotate(center, ang, camPosVec);
    setCenter(newCenter);
    for (auto &boxCoord: boxCoords)
    {
        boxCoord = rotate(boxCoord, ang, camPosVec);
    }
    ang = cvtToRad(m_yaw);
    m_direction.x = sin(ang);
    m_direction.z = -cos(ang);
    m_direction.normalize();
}

const std::string &AABB::getId() const {
    return id;
}

void AABB::setSpeed(float newSpeed) {
    m_scl = newSpeed;
}

void AABB::drawBox() const {
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(boxCoords[0].x, boxCoords[0].y, boxCoords[0].z);
        glVertex3f(boxCoords[2].x, boxCoords[2].y, boxCoords[2].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[1].x, boxCoords[1].y, boxCoords[1].z);
        glVertex3f(boxCoords[3].x, boxCoords[3].y, boxCoords[3].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[0].x, boxCoords[0].y, boxCoords[0].z);
        glVertex3f(boxCoords[1].x, boxCoords[1].y, boxCoords[1].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[2].x, boxCoords[2].y, boxCoords[2].z);
        glVertex3f(boxCoords[3].x, boxCoords[3].y, boxCoords[3].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[4].x, boxCoords[4].y, boxCoords[4].z);
        glVertex3f(boxCoords[5].x, boxCoords[5].y, boxCoords[5].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[6].x, boxCoords[6].y, boxCoords[6].z);
        glVertex3f(boxCoords[7].x, boxCoords[7].y, boxCoords[7].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[4].x, boxCoords[4].y, boxCoords[4].z);
        glVertex3f(boxCoords[6].x, boxCoords[6].y, boxCoords[6].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[5].x, boxCoords[5].y, boxCoords[5].z);
        glVertex3f(boxCoords[7].x, boxCoords[7].y, boxCoords[7].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[0].x, boxCoords[0].y, boxCoords[0].z);
        glVertex3f(boxCoords[4].x, boxCoords[4].y, boxCoords[4].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[1].x, boxCoords[1].y, boxCoords[1].z);
        glVertex3f(boxCoords[6].x, boxCoords[6].y, boxCoords[6].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[3].x, boxCoords[3].y, boxCoords[3].z);
        glVertex3f(boxCoords[7].x, boxCoords[7].y, boxCoords[7].z);
    glEnd();

    glBegin(GL_LINES);
        glVertex3f(boxCoords[2].x, boxCoords[2].y, boxCoords[2].z);
        glVertex3f(boxCoords[5].x, boxCoords[5].y, boxCoords[5].z);
    glEnd();
    glColor3f(1, 1, 1);
}

void AABB::reset(vec3 camPosVec) {
    setCenter({camPosVec.x, static_cast<float>(camPosVec.y - 1.5), camPosVec.z - 3});
    m_speed = {0, 0, 0};
    m_direction = {0, 0, -1};
    m_yaw = 0.0;
    createBox();
}

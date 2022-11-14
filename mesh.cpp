#include "mesh.h"

#include <utility>

Mesh::Mesh(std::string id, std::vector<vec3> vertexCoord, std::vector<vec3> normalCoords) {
    meshId = std::move(id);
    positions = std::move(vertexCoord);
    normals = std::move(normalCoords);
}

Mesh::~Mesh()
= default;

Mesh::Mesh()
= default;

float Mesh::cvtToRad(float ang) const {
    return (ang * m_PI)/180.0;
}

vec3 Mesh::rotate(vec3 point, float ang, vec3 axis) {
    vec3 result;
    result.x = axis.x + (point.x - axis.x) * cos(ang) - (point.z - axis.z) * sin(ang);
    result.z = axis.z + (point.x - axis.x) * sin(ang) + (point.z - axis.z) * cos(ang);
    result.y = point.y;
    return result;
}

void Mesh::update(float leftRightDirection, vec3 camPosVec) {
    m_yaw += leftRightDirection;
    float ang = cvtToRad(leftRightDirection);
    for (auto & position : positions) {
        position = rotate(position, ang, camPosVec);
    }
    ang = cvtToRad(m_yaw);
    m_direction.x = sin(ang);
    m_direction.z = -cos(ang);
    m_direction.normalize();
}

void Mesh::update2(float leftRightDirection, vec3 camPosVec) {
    m_yaw += leftRightDirection;
    float ang = cvtToRad(leftRightDirection);
    for (auto & position : positions) {
        position = rotate(position, ang, camPosVec);
    }
    ang = cvtToRad(m_yaw);
    m_direction.x = -sin(ang);
    m_direction.z = cos(ang);
    m_direction.normalize();
}

void Mesh::forward() {
    m_speed = m_direction * (-m_scl);
    for (auto & position : positions) {
        position = position + m_speed;
    }
}

void Mesh::back() {
    m_speed = m_direction * (m_scl);
    for (auto & position : positions) {
        position = position + m_speed;
    }
}

void Mesh::setName(std::string newId) {
    meshId = std::move(newId);
}

void Mesh::setPositions(std::vector<vec3> newCoords) {
    positions = std::move(newCoords);
}

void Mesh::setNormals(std::vector<vec3> newNormals) {
    normals = std::move(newNormals);
}

std::vector<vec3> Mesh::getPositions() {
    return positions;
}

std::vector<vec3> Mesh::getNormals() {
    return normals;
}

void Mesh::setSpeed(float newSpeed) {
    m_scl = newSpeed;
}

void Mesh::prepareCar() {
    positionsInitial = positions;
    normalsInitial = normals;
    texturePositionsInitial = texturePositions;
}

void Mesh::draw() {
    if (positions.size() == 2) {
        int i = 0;
        while (i < positions.size()) {
            glBegin(GL_LINES);
                glNormal3f(normals[i].x, normals[i].y, normals[i].z);
                glVertex3f(positions[i].x, positions[i].y, positions[i].z);
            glEnd();
            i++;
        }
    }
    else if (positions.size() >= 3) {
        int i = 0;
        while (i < positions.size())
        {
            glBegin(GL_TRIANGLES);
                glNormal3f(normals[i].x, normals[i].y, normals[i].z);
                glVertex3f(positions[i].x, positions[i].y, positions[i].z);
                glNormal3f(normals[i + 1].x, normals[i + 1].y, normals[i + 1].z);
                glVertex3f(positions[i + 1].x, positions[i + 1].y, positions[i + 1].z);
                glNormal3f(normals[i + 2].x, normals[i + 2].y, normals[i + 2].z);
                glVertex3f(positions[i + 2].x, positions[i + 2].y, positions[i + 2].z);
            glEnd();
            i += 3;
        }
    }
}

void Mesh::resetPosition() {
    for (int i = 0; i < positions.size(); ++i) {
        positions[i] = positionsInitial[i];
    }
    for (int i = 0; i < normals.size(); ++i) {
        normals[i] = normalsInitial[i];
    }
    for (int i = 0; i < texturePositions.size(); ++i) {
        texturePositions[i] = texturePositionsInitial[i];
    }

    m_speed = {0, 0, 0};
    m_direction = {0, 0, -1};
    m_yaw = 0.0;
}
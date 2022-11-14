#include "vector.h"
#include <string>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>
#include <cmath>

class AABB
{
    private:
        std::string id;
        vec3 center;
        vec3 extends;
        vec3 m_speed = {0, 0, 0};
        vec3 m_direction = {0, 0 ,-1};
        std::vector<vec3> boxCoords;
        float m_yaw;
        float m_scl = 0.015;
        float m_PI = 3.14159265;

    public:
        explicit AABB(std::string newId, vec3 center, vec3 distances);
        ~AABB();
        AABB();

        vec3 getCenter();
        vec3 getDistances();
        void update(float leftRightDirection, vec3 camPosVec);
        void setId(std::string newId);
        const std::string &getId() const;
        void forward();
        void backward();
        void setCenter(vec3 centerCoords);
        void setDistances(vec3 centerDistances);
        void drawBox() const;
        void createBox();
        void reset(vec3 camPosVec);
        void setSpeed(float newSpeed);

    private:
        static vec3 rotate(vec3 point, float ang, vec3 axis);
        float cvtToRad(float ang) const;
};

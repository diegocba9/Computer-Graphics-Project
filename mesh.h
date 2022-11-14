#include "vector.h"
#include <GL/freeglut.h>
#include <string>
#include <vector>

class Mesh {
    private:
        std::string meshId;
        std::vector<vec3> positions;
        std::vector<vec3> normals;
        std::vector<vec3> texturePositions;
        std::vector<vec3> positionsInitial;
        std::vector<vec3> normalsInitial;
        std::vector<vec3> texturePositionsInitial;

        vec3 m_speed = {0, 0, 0};
        vec3 m_direction = {0, 0 ,-1};

        float m_yaw{};
        float m_scl = 0.015;
        float m_PI = 3.1415;

    public:
        explicit Mesh(std::string id, std::vector<vec3> vertexCoord, std::vector<vec3> normalCoords);
        ~Mesh();
        Mesh();

        void setName(std::string newId);
        void setPositions(std::vector<vec3> newCoords);
        void setNormals(std::vector<vec3> newNormals);

        std::vector<vec3> getPositions();
        std::vector<vec3> getNormals();

        void forward();
        void back();
        void update(float leftRightDirection, vec3 camPosVec);
        void update2(float leftRightDirection, vec3 camPosVec);
        void draw();
        void setSpeed(float newSpeed);
        void prepareCar();
        void resetPosition();

    private:
        static vec3 rotate(vec3 point, float ang, vec3 axis);
        float cvtToRad(float ang) const;
};
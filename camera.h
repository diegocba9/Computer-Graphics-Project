#pragma once

#include "vector.h"

class Camera {
private:
	vec3 m_pos;
	vec3 m_vertical;
	vec3 m_horizontal;
	vec3 m_up;

	vec3 m_verticalPrev;
	vec3 m_posPrev;

	vec3 m_speed;
	float m_scl=0.015;
	float m_PI = 3.1415;
	float m_yaw;
	float m_yawPrev;

public:
	Camera(vec3 pos);
	~Camera();
	void activate();

	void forward();
	void back();
	void left();
	void backwLeft();
	void right();
	void backwRight();

	void frontView();
	void backView();
	void upView();
	void update();
	void update2();
	void updateYaw (float dYaw);
	float cvtToRad (float ang) const;
	vec3 getPosition();
	void resetCamera();
};


#include "camera.h"
#include<GL/glu.h>
#include <GLFW/glfw3.h>

Camera::Camera(vec3 pos) {
	m_pos = vec3(pos);
	m_vertical = vec3(0, 0, 1);
	m_horizontal = vec3(-1, 0, 0);
	m_up = vec3(0,1, 0);
	m_speed = vec3 (0, 0, 0);
}


Camera::~Camera() {
}

void Camera::activate() {
	vec3 look = m_pos + m_vertical;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}

void Camera::frontView() {
	vec3 vector = vec3(0, -0.32, -0.1);
	m_pos = m_pos + vector;
	m_vertical = vec3(0, 0, 1);
	vec3 look = m_pos + m_vertical;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
	update();
}

void Camera::backView() {
	vec3 vector = vec3(0, 0, 1.2);
	m_pos = m_pos + vector;
	m_vertical = vec3(0, 0, -1);
	vec3 look = m_pos + m_vertical;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, -look.z, m_up.x, m_up.y, m_up.z);
	update2();
}

void Camera:: upView() {
	if (m_vertical.y == 0){
		vec3 vector = vec3(0, 0.32, -1.1);
		m_verticalPrev = m_vertical;			
		m_vertical = vec3(0, -1, 0);				
		m_posPrev = m_pos;				
		m_pos = m_pos + vector;	
		m_yawPrev = m_yaw;				
		updateYaw(-m_yaw);					
	}
	else {
		m_vertical = m_verticalPrev;				
		m_pos = m_posPrev;				
		updateYaw(m_yawPrev);			
	}
	vec3 look = m_pos + m_vertical;				
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, 
				look.x, look.y, look.z, 
				m_up.x, m_up.y, m_up.z);	
	update();								

}

float Camera:: cvtToRad (float ang) const {
	return (ang * m_PI)/180.0;
}

void Camera:: updateYaw (float dYaw) {
	m_yaw += dYaw;
}

void Camera:: update() {
	float ang = cvtToRad (m_yaw);
	m_vertical.x = -sin(ang);
	m_vertical.z = cos(ang);
	m_vertical.normalize();
}

void Camera:: update2() {
	float ang = cvtToRad (m_yaw);
	m_vertical.x = sin(ang);
	m_vertical.z = -cos(ang);
	m_vertical.normalize();
}

void Camera:: forward() {
	m_speed = m_vertical * m_scl;
	m_pos = m_pos + m_speed;
}

void Camera:: back() {
	m_speed = m_vertical * (-m_scl);
	m_pos = m_pos + m_speed;
}

void Camera:: left() {
	updateYaw(-1.0);
	update();
}

void Camera:: backwLeft() {
	updateYaw(-1.0);
	update2();
}

void Camera:: right() {
	updateYaw(1.0);
	update();
}

void Camera:: backwRight() {
	updateYaw(1.0);
	update2();
}

vec3 Camera:: getPosition() {
	return m_pos;
}

void Camera:: resetCamera() {
	m_pos = vec3(-1.05, 0.18, -0.9);
	m_vertical = vec3(0, 0, 1);
	vec3 look = m_pos + m_vertical;
	gluLookAt(m_pos.x, m_pos.y, m_pos.z, look.x, look.y, look.z, m_up.x, m_up.y, m_up.z);
}

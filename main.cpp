#include<GLFW/glfw3.h>
#include<GL/glu.h>
#include<iostream>
#include <GL/glut.h>
#include<vector>
#include <chrono>
#include<cstdlib>
#include "cores.h"
#include "camera.h"
#include "OBJ_Loader.h"
#include "mesh.h"
#include "AABB.h"

using namespace std;

bool keyPress[256];
objl:: Loader Loader;
int count = 0;
int view = 1;
Mesh track;
Mesh car;
Mesh grass;
AABB trackOuterCollisionBox;
AABB carCollisionBox;
vec3 outerDistances = vec3(2, 5, 2);
vec3 outerCenter = vec3(0, 0, 0);
vec3 carCollisionBoxDistances = vec3(0.03, 0.03, 0.1);

Camera camera(vec3(-1.05, 0.18, -0.9));


void changeCamera() {
	count++;
	if (count%3 == 0) {
		view=1;
		camera.frontView();
	}
	else if (count%3 == 1) {
		view = 2;
		camera.backView();
	}
	else if (count%3 == 2) {
		view=1;
		camera.upView();
	}
	
}

Mesh cvtOBJ(const char * fileName) { //Function used to convert the .obj files into Mesh objects
    vector<vec3> vertices;
    vector<vec3> normals;
    Mesh tempMesh;
    objl::Loader Loader;
    bool loadout = Loader.LoadFile(fileName);
    if (loadout)
    {
        for (const auto& currentMesh : Loader.LoadedMeshes)
        {
            for (auto & Vertex : currentMesh.Vertices)
            {
                vec3 temp_vertices;
                temp_vertices.x = Vertex.Position.X;
                temp_vertices.y = Vertex.Position.Y;
                temp_vertices.z = Vertex.Position.Z;
                vertices.push_back(temp_vertices);
                vec3 temp_normals;
                temp_normals.x = Vertex.Normal.X;
                temp_normals.y = Vertex.Normal.Y;
                temp_normals.z = Vertex.Normal.Z;
                normals.push_back(temp_normals);
            }
            tempMesh.setName(currentMesh.MeshName);
            tempMesh.setPositions(vertices);
            tempMesh.setNormals(normals);
            return tempMesh;
        }
    }
    return tempMesh;
}

void redimension(int w, int h) { //Function used do display the screen
	glViewport(0, 0, w, h);

	float aspect = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.activate();
}

void keyPerFrame() { //Function used to manage de keys pressed to move the car
	if (keyPress[27] == true) {
		exit(0);
	}
	if (keyPress[(int)'w']) {
		if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z > -outerDistances.z))
	        {
			if (view == 1) {
				camera.forward();
			}
			else {
				camera.back();
			}
			carCollisionBox.forward();
			car.forward();
		}
		else
        {
            camera.resetCamera();
            carCollisionBox.reset(camera.getPosition());
            car.resetPosition();
        }
		
	}
	if (keyPress[(int)'a']) {
		if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z > -outerDistances.z))
        {
			if (view == 1) {
				camera.left();
				car.update(-1.0, camera.getPosition());
			}
			else {
				camera.backwLeft();
				car.update2(-1.0, camera.getPosition());
			}
			carCollisionBox.update(-1.0, camera.getPosition());
		}
		else
        {
            camera.resetCamera();
            carCollisionBox.reset(camera.getPosition());
            car.resetPosition();
        }
	}
	if (keyPress[(int)'s']) {
		if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x + 0.5 < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x - 0.5 > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z + 0.5 < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z - 0.5 > -outerDistances.z))
	        {
			if (view == 1) {
				camera.back();
			}
			else {
				camera.forward();
			}
			carCollisionBox.backward();
			car.back();
		}
        else {
            camera.resetCamera();
            carCollisionBox.reset(camera.getPosition());
            car.resetPosition();
        }

	}
	if (keyPress[(int)'d']) {
		if ((carCollisionBox.getCenter().x + carCollisionBoxDistances.x < outerDistances.x && carCollisionBox.getCenter().x - carCollisionBoxDistances.x > -outerDistances.x) &&
        (carCollisionBox.getCenter().z + carCollisionBoxDistances.z < outerDistances.z && carCollisionBox.getCenter().z - carCollisionBoxDistances.z > -outerDistances.z))
        {
			if (view == 1) {
				camera.right();
				car.update(1.0, camera.getPosition());
			}
			else {
				camera.backwRight();
				car.update2(1.0, camera.getPosition());
			}
			carCollisionBox.update(1.0, camera.getPosition());
		}
		else {
            camera.resetCamera();
            carCollisionBox.reset(camera.getPosition());
            car.resetPosition();
        }

	}

	redimension(800,600);
}

void draw() {

	keyPerFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	float lastTime = 0.0;
	float now;
	float dt;

	do {
		now = glutGet(GLUT_ELAPSED_TIME);
		dt = now - lastTime;
	}
	while (dt < 1.0/15);

	glColor3fv(grey);
	track.draw();

	glColor3fv(red);
	car.draw();

	glColor3fv(green);
	grass.draw();

	glutSwapBuffers();
}


void init() { //Function used do initialize the elements of the scene
	
	GLfloat ambientLight[4] = {0.2, 0.2, 0.2, 1.0};
	GLfloat diffusedLight[4] = {0.7, 0.7, 0.7, 1.0};
	GLfloat specularLight[4] = {1.0, 1.0, 1.0, 1.0};
	GLfloat lightPosition[4] = {0.0, 50.0, 50.0, 1.0};

	GLfloat specularity[4] = {1.0, 1.0, 1.0, 1.0};
	GLint specMaterial = 60;

	glClearColor(0.54, 0.74, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, specularity);
	glMateriali(GL_FRONT, GL_SHININESS, specMaterial);

	glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambientLight);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffusedLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);

	car = cvtOBJ("car.obj");
	car.prepareCar();
	track = cvtOBJ("track.obj");
	grass = cvtOBJ ("grass.obj");

	trackOuterCollisionBox.setId("outerWall");
    trackOuterCollisionBox.setDistances(outerDistances);
    trackOuterCollisionBox.setCenter(outerCenter);
    trackOuterCollisionBox.createBox();

    carCollisionBox.setId("Mesh");
    carCollisionBox.setDistances(carCollisionBoxDistances);
    carCollisionBox.setCenter({camera.getPosition().x, static_cast<float>(camera.getPosition().y), camera.getPosition().z});
    carCollisionBox.createBox();
    
}

void keyboard (unsigned char key, int x, int y) {
	keyPress[(int)key] = true;
	if (key == 32) {
		changeCamera();
	}
}

void keyboardUp (unsigned char key, int x, int y) {
	keyPress[(int)key] = false;
}

void idle() { //Function used to refresh 
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	printf("Commands:\n\nW->Go forward\nA->Tilt left\nS->Go backwards\nD->Tilt right\nSpace->Change camera view\n");
	glutInit (&argc, argv);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(320, 120);
	glutCreateWindow("Camera");
	

	init();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	redimension(800, 600);
	
	glutDisplayFunc(draw);
	
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutIdleFunc(idle);
	
	glutMainLoop();

}

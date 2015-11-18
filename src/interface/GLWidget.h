#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GLM_FORCE_RADIANS

//#define GLEW_VERSION_3_2

// third-party libraries
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



#include <QtOpenGL/QGLWidget>
//#include <QtOpenGL>

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <list>
#include <sstream>
using namespace std;

#include <phonon/phonon>

#include <QLabel>

// tdogl classes
#include "Program.h"
#include "Texture.h"
#include "Camera.h"
#include "ShadersControler.h"
#include "ModelAsset.h"
#include "ModelInstance.h"
#include "importer.h"
#include "Light.h"

#include "Quaternions.h"

struct Raio
{
    ModelInstance laser;
    glm::vec3 delta;
    glm::vec3 chegada;
    //double tam;
};

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void LoadOBJ(const char*  arquivo, const char*  textura, const char*  vertex_shader, const char*  fragment_shader,
                 int drawStart, float shininess, glm::vec3 specularColor, bool haveTexture);

    void CalculaLaser();
    void AtualizaLaser();

    std::vector<ModelAsset> modelos;
    std::list<ModelInstance> gInstances;

    std::list<Raio> lasers;

    std::vector<ModelInstance> rebeldes;
    std::vector<ModelInstance> imperio;

    std::list<ModelInstance> imp;
    std::list<ModelInstance> reb;

    ModelInstance vader;

    QLabel *label;

public slots:
    void simStep();

protected:
    void initializeGL();
	void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent* event);
    void keyReleaseEvent(QKeyEvent *);
    void keyPressEvent(QKeyEvent *);

private:
    void CreateInstances();
    void RenderInstance(const ModelInstance& inst);


    tdogl::Camera gCamera;
    QTimer *simTimer;

    glm::vec2 screen_size = {800, 600};
    double posX, posY;
    double angX,angY;
    double rotLua;
    double rotNave;

    bool fix_cam;
    bool start;
    Phonon::MediaObject *music;
    Phonon::MediaObject *war;
    Phonon::MediaObject *xWing_Sound;
    Phonon::MediaObject *tieFighter_Sound;
    Phonon::MediaObject *tieFighter_Engine;
    Phonon::MediaObject *empire_Alert_Sound;
    Phonon::MediaObject *laser_Sound;
    Phonon::MediaObject *intro_Sound;

    std::vector<Light> gLights;

    enum
    {
		SPIN_BUTTON = Qt::LeftButton,
		PICK_BUTTON = Qt::RightButton
	};

    //QGLShaderProgram program;
};

#endif

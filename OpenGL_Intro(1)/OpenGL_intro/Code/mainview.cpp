#include "mainview.h"
#include "math.h"
#include "vertex.h"

#include <QDateTime>

MainView::MainView(QWidget *parent) : QOpenGLWidget(parent) {
    qDebug() << "MainView constructor";

    initializeGL();


    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));


    qDebug() << "a";
    shader.addShaderFromSourceFile(QOpenGLShader::Vertex ,":/shaders/vertshader.glsl");
    shader.addShaderFromSourceFile(QOpenGLShader::Fragment ,":/shaders/fragshader.glsl");
    qDebug() << "b";
    shader.link();
    shader.bind();



    GLuint VBO = 0;
    GLuint VAO = 0;


    vertex vertexArray[3];
    // V1
    vertexArray[0].x =   1;
    vertexArray[0].y =   0;
    vertexArray[0].red =   1;
    vertexArray[0].green = 0;
    vertexArray[0].blue =  0;

    // V2
    vertexArray[1].x =   0.5;
    vertexArray[1].y =   1;
    vertexArray[1].red =   0;
    vertexArray[1].green = 1;
    vertexArray[1].blue =  0;


    // V3
    vertexArray[2].x =   0;
    vertexArray[2].y =   0;
    vertexArray[2].red =   0;
    vertexArray[2].green = 0;
    vertexArray[2].blue =  1;



    qDebug() << "About to load VBO";
    glGenBuffers(1, &VBO);
    qDebug() << "About to load VAO";
    glGenVertexArrays(1, &VAO);


    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);


    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)*3, &vertexArray, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 2,  GL_FLOAT, GL_FALSE, sizeof(vertex),(GLvoid*)0);
    glVertexAttribPointer(1, 3,  GL_FLOAT, GL_FALSE, sizeof(vertex),(GLvoid*)(2*sizeof(float)) );

    MainView();
    qDebug() << "Program finished.";

}

MainView::~MainView() {
    debugLogger->stopLogging();

    qDebug() << "MainView destructor";
}

void MainView::initializeGL() {
    qDebug() << ":: Initializing OpenGL";
    initializeOpenGLFunctions();
    qDebug() << ":: Finished initalising functions";
    debugLogger = new QOpenGLDebugLogger();
    connect( debugLogger, SIGNAL( messageLogged( QOpenGLDebugMessage ) ), this, SLOT( onMessageLogged( QOpenGLDebugMessage ) ), Qt::DirectConnection );

    if ( debugLogger->initialize() ) {
        qDebug() << ":: Logging initialized";
        debugLogger->startLogging( QOpenGLDebugLogger::SynchronousLogging );
        debugLogger->enableMessages();
    }

    QString glVersion;
    glVersion = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    qDebug() << ":: Using OpenGL" << qPrintable(glVersion);
}

void MainView::resizeGL(int newWidth, int newHeight) {

    Q_UNUSED(newWidth)
    Q_UNUSED(newHeight)
}

void MainView::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor =
    glDrawArrays(GL_TRIANGLES, 0, 1);
}

void MainView::onMessageLogged( QOpenGLDebugMessage Message ) {
    qDebug() << " → Log:" << Message;
}

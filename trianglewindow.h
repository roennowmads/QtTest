#ifndef TRIANGLEWINDOW_H
#define TRIANGLEWINDOW_H

#include "openglwindow.h"
#include <QtGui/QScreen>

class TriangleWindow : public OpenGLWindow
{
public:
    TriangleWindow()
        : m_program(0)
        , m_frame(0)
    {
    }

    void initialize() override;
    void render() override;

private:
    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;

    QOpenGLShaderProgram *m_program;
    int m_frame;
};



#endif // TRIANGLEWINDOW_H

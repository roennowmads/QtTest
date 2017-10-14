#include "trianglewindow.h"

static QString s_vertexShaderSource =
    "in highp vec4 posAttr;\n"
    "//in lowp vec4 colAttr;\n"
    "//out lowp vec4 col;\n"
    "uniform highp mat4 matrix;\n"
    "void main() {\n"
    "   //col = colAttr;\n"
    "   gl_Position = matrix * posAttr;\n"
    "   gl_PointSize = 10.0;\n"
    "}\n";

static QString s_fragmentShaderSource =
    "//in lowp vec4 col;\n"
    "layout(location = 0) out highp vec4 colOut;\n"
    "void main() {\n"
    "   colOut = vec4(1.0);//col;\n"
    "}\n";

void TriangleWindow::initialize()
{
    m_program = new QOpenGLShaderProgram(this);

    QString vertexShaderSource, fragmentShaderSource;

    if (QOpenGLContext::currentContext()->isOpenGLES()) {
        vertexShaderSource.append(QByteArrayLiteral("#version 300 es\n"));
        fragmentShaderSource.append(QByteArrayLiteral("#version 300 es\n"));
    }
    else {
        vertexShaderSource.append(QByteArrayLiteral("#version 330\n"));
        fragmentShaderSource.append(QByteArrayLiteral("#version 330\n"));
    }

    vertexShaderSource.append(s_vertexShaderSource);
    fragmentShaderSource.append(s_fragmentShaderSource);

    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    m_program->link();
    m_posAttr = m_program->attributeLocation("posAttr");
    //m_colAttr = m_program->attributeLocation("colAttr");
    m_matrixUniform = m_program->uniformLocation("matrix");

    //glEnable( GL_PROGRAM_POINT_SIZE );
}

void TriangleWindow::render()
{
    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

    //glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);

    m_program->bind();

    QMatrix4x4 matrix;
    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 1000.0f);
    matrix.translate(0, 0, -99);
    //matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

    int numberOfTrisX = 1000;
    int numberOfTrisY = 1000;
    matrix.translate(-numberOfTrisX/2, -numberOfTrisY/2, 0);

    m_program->setUniformValue(m_matrixUniform, matrix);

    int numberOfVerts = numberOfTrisX * numberOfTrisY /** 3*/;

    QVector<QVector2D> verts;
    for (int i = 0; i < numberOfTrisX; i++) {
        for (int j = 0; j < numberOfTrisY; j++) {
            int delta = 2.0f;
            QVector2D vert1(0.0f + delta*i, 0.707f + delta*j);
           // QVector2D vert2(-0.5f + delta*i, -0.5f + delta*j);
            //QVector2D vert3(0.5f + delta*i, -0.5f + delta*j);
            verts.append(vert1);
            //verts.append(vert2);
            //verts.append(vert3);
        }
    }

    /*GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };*/

    glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, /*vertices*/verts.constData());
    //glVertexAttribPointer(m_colAttr, 3, GL_FLOAT, GL_FALSE, 0, colors);

    glEnableVertexAttribArray(m_posAttr);
    //glEnableVertexAttribArray(1);

    glDrawArrays(/*GL_TRIANGLES*/GL_POINTS, 0, numberOfVerts);

    //glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(m_posAttr);

    m_program->release();

    ++m_frame;
}

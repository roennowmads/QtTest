#include "openglwindow.h"
#include "trianglewindow.h"

#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>

#include <QtCore/qmath.h>

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    QSurfaceFormat format;
    //format.setVersion(3, 0);

    format.setDepthBufferSize(24);
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        //format.setVersion(3, 3);
        format.setProfile(QSurfaceFormat::CompatibilityProfile);
    } else {
        format.setVersion(3, 1);
    }
    QSurfaceFormat::setDefaultFormat(format);


    format.setSamples(16);

    TriangleWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    window.setAnimating(true);

    return app.exec();
}

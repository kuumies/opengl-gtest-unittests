/**
    @file   opengl_tests.cpp
    @author kuumies <kuumies@gmail.com>
    @brief  Implementation of opengl tests.
 **/

#include <gtest/gtest.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/QOpenGLWidget>
#include "opengl_mesh.h"

namespace
{

class OpenGLWidget : public QOpenGLWidget
{
public:
    typedef std::function<void()> RunTestCallback;

    OpenGLWidget(RunTestCallback c)
        : runTest(c)
    {}

    void initializeGL()
    {
#ifdef _WIN32
        glewExperimental = GL_TRUE;
        GLenum result = glewInit();
        if (result != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW." << std::endl;
            EXPECT_TRUE(false);
        }
#endif
        runTest();
        run = true;
        QApplication::quit();
    }

    bool isTestRun() const
    { return run; }

private:
    RunTestCallback runTest;
    bool run = false;
};

void runOpenGLTest(OpenGLWidget::RunTestCallback callback)
{
    // Set the wanted surface format.
    QSurfaceFormat format;
    format.setDepthBufferSize(16);
    format.setVersion(3, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(format);

    int argc = 0;
    char* argv[1];
    QApplication app(argc, argv);
    OpenGLWidget w(callback);
    w.setAttribute(Qt::WA_DontShowOnScreen);
    w.show();
    if (!w.isTestRun())
        app.exec();
}

} // anonynous namespace

TEST(MeshTest, Obj)
{
    auto testMesh = []()
    {
        using namespace kuu::opengl;

        const float w = 1.0f;
        const float h = 1.0f;
        const std::vector<float> inVertices =
        {
          // x   y   z     r     g     b
            -w, -h, 0.0f, 1.0f, 0.0f, 0.0f,
             w, -h, 0.0f, 0.0f, 1.0f, 0.0f,
             w,  h, 0.0f, 0.0f, 0.0f, 1.0f,
            -w,  h, 0.0f, 1.0f, 1.0f, 0.0f
        };

        const std::vector<unsigned int> inIndices =
        {
            0u, 1u, 2u,
            2u, 3u, 0u
        };

        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
        EXPECT_TRUE(mesh.get());

        mesh->writeVertexData(inVertices);
        mesh->writeIndexData(inIndices);

        std::vector<float> outVertices;
        mesh->readVertexData(outVertices);
        std::vector<unsigned int> outIndices;
        mesh->readIndexData(outIndices);

        EXPECT_EQ(inVertices.size(), 24);
        EXPECT_EQ(inVertices.size(), outVertices.size());
        for (int i = 0; i < 24; ++i)
            EXPECT_FLOAT_EQ(inVertices[i], outVertices[i]);

        EXPECT_EQ(inIndices.size(),  6);
        EXPECT_EQ(inIndices.size(),  outIndices.size());
        for (int i = 0; i < 6; ++i)
            EXPECT_FLOAT_EQ(inIndices[i], outIndices[i]);
    };

    runOpenGLTest(testMesh);
}

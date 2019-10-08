#include "widget.hpp"


void Widget::render (void)
{
    // basic GL commands to clear the screen buffer (sets to white)
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // render the mesh on the screen
    simpleshader.render(mesh, camera);
}

void Widget::openMeshFile(std::string fn)
{
    // imports a ply file
    if (Tucano::MeshImporter::loadPlyFile(&mesh, fn))
    {
        // normalize model matrix to place vertices are inside unit cube
        mesh.normalizeModelMatrix();
    }
}

void Widget::createGeometry (void)
{
    vector<Eigen::Vector4f> vertices;
    vector<GLuint> indices;

    vertices.push_back ( Eigen::Vector4f( -0.5, -0.5, 0.0, 1.0) );
    vertices.push_back ( Eigen::Vector4f(  0.5, -0.5, 0.0, 1.0) );
    vertices.push_back ( Eigen::Vector4f(  0.5,  0.5, 0.0, 1.0) );

    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);

    mesh.loadVertices(vertices);    
    mesh.loadIndices(indices);


    /**** solution exercise 4 *****/

    vector<Eigen::Vector4f> colors;    
    colors.push_back ( Eigen::Vector4f( 1.0, 0.0, 0.0, 1.0) );
    colors.push_back ( Eigen::Vector4f( 0.0, 1.0, 0.0, 1.0) );
    colors.push_back ( Eigen::Vector4f( 0.0, 0.0, 1.0, 1.0) );
    mesh.loadColors(colors);

    /**** end solution exercise 4 *****/
    
    mesh.setDefaultAttribLocations();
}

void Widget::initialize (int width, int height)
{
    // make sure default OpenGL depth test is enable
    glEnable(GL_DEPTH_TEST);

    createGeometry();

    // initialize the shader effect (if TUCANOSHADERDIR is set, no need to set dir before init)
    simpleshader.initialize();

    // create a default camera
    camera.setPerspectiveMatrix(60.0, (float)width/(float)height, 0.1f, 100.0f);    
    camera.setViewport(Eigen::Vector2f ((float)width, (float)height));
    // translate the camera backwards, so it is not inside the model (and set as default view)
    camera.viewMatrix()->translate (Eigen::Vector3f(0.0, 0.0, 2.0));
    camera.setAsDefault();
}


void Widget::screenshot (void)
{
    Eigen::Vector2i viewport = camera.getViewportSize();
    screenshot_fbo.create (viewport[0], viewport[1], 1, 1);
    screenshot_fbo.clearAttachments(Eigen::Vector4f(1.0, 1.0, 1.0, 0.0));
    screenshot_fbo.bindRenderBuffer(0);

    simpleshader.render(mesh, camera);


    static int counter = 0;
    screenshot_fbo.unbind();
    std::ostringstream screenshot_name;
    screenshot_name << "pipeline-screenshot" << counter << ".ppm";    
    screenshot_fbo.saveAsPPM(screenshot_name.str(), 0);
    counter ++;
}
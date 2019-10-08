#include "widget.hpp"

void Widget::render (void)
{
    // basic GL commands to clear the buffer and set the background color
    glClearColor(0.9, 0.9, 0.9, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // render the mesh with the shader_assignment effect
    helloworld.render(mesh, camera);
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

    mesh.setDefaultAttribLocations();
}

void Widget::initialize (int width, int height)
{
    // make sure default OpenGL depth test is enable
    glEnable(GL_DEPTH_TEST);

    // creates the triangle geometry and indices
    createGeometry();

    // initialize the shader effect (if TUCANOSHADERDIR is set, no need to set dir before init)
    helloworld.initialize();

    // set the projection matrix and the viewport size
    camera.setPerspectiveMatrix(60.0, (float)width/(float)height, 0.1f, 100.0f);    
    camera.setViewport(Eigen::Vector2f ((float)width, (float)height));
    // translate the camera backwards, so it is not inside the model (and set as default view)
    camera.viewMatrix()->translate (Eigen::Vector3f(0.0, 0.0, 2.0));
    camera.setAsDefault();    
}

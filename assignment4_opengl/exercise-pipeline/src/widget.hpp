#ifndef __MODELWIDGET__
#define __MODELWIDGET__

#include <GL/glew.h>

#include "tucano/utils/plyimporter.hpp" // for reading ply files
#include "tucano/framebuffer.hpp" // fbo for saving screenshot
#include "simpleshader.hpp" 

/**
 * @brief Widget to display model
 */
class Widget
{

private:    

    /// Mesh to be rendered in this widget
    Tucano::Mesh mesh;

    /// Trackball for manipulating the camera
    Tucano::Camera camera;

    /// Effect to render mesh
    Tucano::Effects::SimpleShader simpleshader;

    /// a buffer for saving screenshots
    Tucano::Framebuffer screenshot_fbo;

public:

    /*
     * @brief Default constructor
     */
    Widget(void) {}
    
    /**
     * @brief Initializes the widget and shaders
     * @param width Widget width in pixels
     * @param height Widget height in pixels 
     */
    void initialize(int width, int height);

    /**
     * Renders the mesh
     **/
    virtual void render();

    /**
     * @brief setMeshFile
     * @param fn
     * New function to setup a meshFile var
     */
    void openMeshFile(string fn);

    /**
     * @brief Creates a single triangle
     */
    void createGeometry (void);

    /**
     * @brief Recompile and reload the shaders
     */
    void reloadShaders (void) {simpleshader.reloadShaders();}

    /**
     * @brief Take a snaphot of the application and save it to a PPM file
     **/
    void screenshot (void);
};

#endif // MODELWIDGET


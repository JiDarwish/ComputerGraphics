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
    Tucano::Framebuffer snapshot_fbo;

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
     * @brief runs static exercises
     * Runs all static exercises and saves a result to an image file
     */ 
    void runExercises (void);

    /**
     * Exercises
    */
    void exercise1 (void);
    void exercise2 (void);
    void exercise3 (void);
    void exercise4 (void);
    void exercise5 (void);
    void exercise6 (void);
};

#endif // MODELWIDGET


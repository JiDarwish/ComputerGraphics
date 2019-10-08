#ifndef __WIDGET__
#define __WIDGET__

#include "helloworld.hpp" 

/**
 * @brief Widget to display model and GUI
  */
class Widget
{

private:    

    /// Mesh to be rendered in this widget, in this case a single triangle
    Tucano::Mesh mesh;

    /// Simple Camera (no interface)
    Tucano::Camera camera;

    /// Effect to render mesh
    Tucano::Effects::HelloWorld helloworld;

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
     * @brief Creates a single triangle
     */
    void createGeometry (void);
};

#endif // MODELWIDGET

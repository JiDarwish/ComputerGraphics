#ifndef __HELLOWORLD__
#define __HELLOWORLD__

#include "tucano/effect.hpp"
#include "tucano/camera.hpp"
#include "tucano/mesh.hpp"

namespace Tucano
{
namespace Effects
{

/**
 * @brief Renders a mesh using a custom shader.
 */
class HelloWorld : public Tucano::Effect
{

private:

    /// Shading Assignment shader
    Tucano::Shader shader;

public:

    /**
     * @brief Default constructor.
     * We do not call initialize here because we are not sure GLEW has been initialized yet
     * and the shaders can only be loaded after GLEW is ready
     */
    HelloWorld (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files shading.(vert,frag,geom,comp)
        // it should find shading.vert and shading.frag
        loadShader(shader, "helloworld") ;
    }

    /** 
     * @brief Render the mesh given a camera and light, using a Phong shader 
     * @param mesh Given mesh
     * @param camera Given camera 
     * @param lightTrackball Given light camera 
     */
    void render (Tucano::Mesh& mesh, const Tucano::Camera& camera)
    {

        // sest the current viewport to match the camera's viewport
        Eigen::Vector4f viewport = camera.getViewport();
        glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);

        // bind the shader, any operation until the unbind operation will affect this shader
        shader.bind();

        // sets all uniform variables for the current shader (these are the variables that will be used in the vertex/fragment shaders)
        // attention: do not set uniforms to shaders that are not "bind"
        shader.setUniform("projectionMatrix", camera.getProjectionMatrix());
        shader.setUniform("modelMatrix", mesh.getShapeModelMatrix());        
        shader.setUniform("viewMatrix", camera.getViewMatrix().inverse());

        // sets the mesh attributes automatically, such as vertex position and normals
        mesh.setAttributeLocation(shader);

        // render the mesh and call shaders
        mesh.render();

        // unbind the shader for a clean exit
        shader.unbind();
    }


};
}
}


#endif

#ifndef __SIMPLESHADER__
#define __SIMPLESHADER__

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
class SimpleShader : public Tucano::Effect
{

private:

    /// Shading Assignment shader
    Tucano::Shader shader;

	/// Default color
	Eigen::Vector4f default_color = Eigen::Vector4f (0.9, 0.5, 0.1, 1.0);

public:

    /**
     * @brief Default constructor.
     * We do not call initialize here because we are not sure GLEW has been initialized yet
     * and the shaders can only be loaded after GLEW is ready
     */
    SimpleShader (void) {}

    /**
     * @brief Load and initialize shaders
     */
    virtual void initialize (void)
    {
        // searches in default shader directory (/shaders) for shader files shading.(vert,frag,geom,comp)
        // it should find shading.vert and shading.frag
        loadShader(shader, "shading") ;
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
		shader.setUniform("default_color", default_color);

        // sets the mesh attributes automatically, such as vertex position and normals so they are read in the shaders
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

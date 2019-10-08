#include "widget.hpp"

/*******************************************************************************/
/**************write your code here*****************/


/**
 * @brief Exercise - rotate  model
 * Rotate the model by 90 degrees around the Z axis
*/
void Widget::exercise1 (void)
{
	Eigen::Affine3f modelMatrix = mesh.getModelMatrix()
		.rotate(Eigen::AngleAxisf(0.5 * M_PI, Eigen::Vector3f::UnitZ()));
	mesh.setModelMatrix(modelMatrix);
}

/**
 * @brief Exercise - translate model
 * Translate the model by 0.5 units on the X axis
*/
void Widget::exercise2 (void)
{        
	mesh.setModelMatrix(mesh.getModelMatrix().translate(Eigen::Vector3f(0.5, 0.0, 0.0)));
}

/**
 * @brief Exercise - rotate and translate model
 * Rotate the model by 90 degrees around the Z axis
 * and then translate it by 0.5 units on the X axis
*/
void Widget::exercise3 (void)
{
	Eigen::Affine3f modelMatrix = mesh.getModelMatrix();
	modelMatrix.rotate(Eigen::AngleAxisf(0.5 * M_PI, Eigen::Vector3f::UnitZ()));
	modelMatrix.translate(Eigen::Vector3f(0.5, 0.0, 0.0));
	mesh.setModelMatrix(modelMatrix);

}

/**
 * @brief Exercise - translate and rotate model
 * Inverse of Exercise 3, first translate and then rotate
 * Translate by 0.5 units on X axis
 * followed by a rotation of 90 degrees around Z axis
 * Do you see the difference?
 * Can you explain the difference?
*/
void Widget::exercise4 (void)
{        
	Eigen::Affine3f modelMatrix = mesh.getModelMatrix();
	modelMatrix.translate(Eigen::Vector3f(0.5, 0.0, 0.0));
	modelMatrix.rotate(Eigen::AngleAxisf(0.5 * M_PI, Eigen::Vector3f::UnitZ()));
	mesh.setModelMatrix(modelMatrix);
}

/**
 * @brief Exercise - rotate and translate camera
 * Instead of the model, repeat exercise 3 with the camera view matrix
 * What happened? Can you explain the result?
 */
 void Widget::exercise5 (void)
 {
	 Eigen::Affine3f viewMatrix = camera.getViewMatrix().rotate(Eigen::AngleAxisf(0.5 * M_PI, Eigen::Vector3f::UnitZ()));
	 camera.setViewMatrix(viewMatrix);
 }

/**
 * @brief Exercise - rotate model continuously 
 * rotate mesh every frame by PI/100.0 around the Y axis
 * note that this method is called inside the render method
 * so it runs every frame
*/
void Widget::exercise6 (void)
{    
	Eigen::Affine3f viewMatrix = camera.getViewMatrix().rotate(Eigen::AngleAxisf(M_PI / 100, Eigen::Vector3f::UnitZ()));
	camera.setViewMatrix(viewMatrix);
}


/*******************************************************************************/

void Widget::render (void)
{
    // basic GL commands to clear the screen buffer (sets to white)
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    // when exercise 6 is ready it will be called every frame
    exercise6();


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

void Widget::initialize (int width, int height)
{
    // make sure default OpenGL depth test is enable
    glEnable(GL_DEPTH_TEST);

    // initialize the shader effect (if TUCANOSHADERDIR is set, no need to set dir before init)
    simpleshader.initialize();    

    // create a default camera
    camera.setPerspectiveMatrix(60.0, (float)width/(float)height, 0.1f, 100.0f);    
    camera.setViewport(Eigen::Vector2f ((float)width, (float)height));
    // translate the camera backwards, so it is not inside the model (and set as default view)
    camera.viewMatrix()->translate (Eigen::Vector3f(0.0, 0.0, 2.0));
    camera.setAsDefault();
}


/**
 * @brief Runs all static exercises and saves screenshots as answers
 */
void Widget::runExercises (void)
{
    Eigen::Affine3f myaffinematrix = Eigen::Affine3f::Identity();
    myaffinematrix.rotate (Eigen::AngleAxisf (M_PI*0.25, Eigen::Vector3f::UnitY()));        

    int num_exercises = 5;
    Eigen::Vector2i viewport = camera.getViewportSize();
    for (int i = 1; i <= num_exercises; ++i)
    {
        // reset model and view matrices
        mesh.resetModelMatrix();
        camera.resetViewMatrix();

        snapshot_fbo.create (viewport[0], viewport[1], 1, 1);
        snapshot_fbo.clearAttachments(Eigen::Vector4f(1.0, 1.0, 1.0, 0.0));
        snapshot_fbo.bindRenderBuffer(0);

        switch (i)
        {            
            case 1: exercise1(); break;
            case 2: exercise2(); break;
            case 3: exercise3(); break;
            case 4: exercise4(); break;
            case 5: exercise5(); break;
        }
        render();

        snapshot_fbo.unbind();
        std::ostringstream snapshot_name;
        snapshot_name << "transformations-exercise" << i << ".ppm";
        snapshot_fbo.saveAsPPM(snapshot_name.str(), 0);

    }
    mesh.resetModelMatrix();
    camera.resetViewMatrix();
}
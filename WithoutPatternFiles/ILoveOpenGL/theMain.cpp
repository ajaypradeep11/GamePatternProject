
#include "GLCommon.h"
//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>

#include "globalThings.h"

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> 
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>      // "string stream" just like iostream and fstream
#include <vector>       // "smart array"
#include <fstream>      // C++ file I-O library (look like any other stream)


void DrawObject(
    cMesh* pCurrentMesh,
    glm::mat4 matModel,
    GLint matModel_Location,
    GLint matModelInverseTranspose_Location,
    GLuint program,
    cVAOManager* pVAOManager);



void setObjects(std::string meshName, glm::vec3 vectorPosition, float angle);
void setFloorObject(std::string meshName);

std::string getRandom(float low, float high);
void generateEnemy(std::string meshname, int height);
void generatePlayer();
void generateMissile();
void generateUFO();
void generateBlock();
int main(void)
{
    GLFWwindow* pWindow;

    GLuint program = 0;     // 0 means "no shader program"

    GLint mvp_location = -1;        // Because glGetAttribLocation() returns -1 on error

   

    glfwSetErrorCallback(GLFW_error_callback);

    if (!glfwInit())
    {
        return -1;
        //exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    pWindow = glfwCreateWindow(1920, 1080, "OpenGL is great!", NULL, NULL);

    if (!pWindow)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(pWindow, GLFW_key_callback);
    // NEW: 
    glfwSetCursorEnterCallback(pWindow, GLFW_cursor_enter_callback);
    glfwSetCursorPosCallback(pWindow, GLFW_cursor_position_callback);
    glfwSetScrollCallback(pWindow, GLFW_scroll_callback);
    glfwSetMouseButtonCallback(pWindow, GLFW_mouse_button_callback);
    glfwSetWindowSizeCallback(pWindow, GLFW_window_size_callback);

    glfwMakeContextCurrent(pWindow);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);
    GLint max_uniform_location = 0;
    GLint* p_max_uniform_location = NULL;
    p_max_uniform_location = &max_uniform_location;
    glGetIntegerv(GL_MAX_UNIFORM_LOCATIONS, p_max_uniform_location);


    std::cout << "GL_MAX_UNIFORM_LOCATIONS: " << max_uniform_location << std::endl;

    // Create global things
    ::g_StartUp(pWindow);

    ::g_pFlyCamera->setEye(glm::vec3(-1990.0f, -610.0f, -3130.0f));
    //::g_pFlyCamera->Pitch_UpDown(30);
    //::g_pFlyCamera->Yaw_LeftRight(23);


    /*::g_pTextureManager->Create2DTextureFromBMPFile("ShockwaveExplosion_square.bmp", true);
    ::g_pTextureManager->Create2DTextureFromBMPFile("ShockwaveExplosion_blue_square_2.bmp", true);
    *///if (!::g_pTextureManager->CreateCubeTextureFromBMPFiles("TropicalSunnyDay",
    //    "TropicalSunnyDayRight2048.bmp",    /* posX_fileName */
    //    "TropicalSunnyDayLeft2048.bmp",     /*negX_fileName */
    //    "TropicalSunnyDayDown2048.bmp",     /*posY_fileName*/
    //    "TropicalSunnyDayUp2048.bmp",       /*negY_fileName*/
    //    "TropicalSunnyDayBack2048.bmp",     /*posZ_fileName*/
    //    "TropicalSunnyDayFront2048.bmp",    /*negZ_fileName*/
    //    true, errorTextString))
    //{
    //    std::cout << "Didn't load because: " << errorTextString << std::endl;
    //}

    cShaderManager::cShader vertShader;
    vertShader.fileName = "assets/shaders/vertShader_01.glsl";

    cShaderManager::cShader fragShader;
    fragShader.fileName = "assets/shaders/fragShader_01.glsl";

    if (::g_pShaderManager->createProgramFromFile("Shader#1", vertShader, fragShader))
    {
        std::cout << "Shader compiled OK" << std::endl;
        // 
        // Set the "program" variable to the one the Shader Manager used...
        program = ::g_pShaderManager->getIDFromFriendlyName("Shader#1");
    }
    else
    {
        std::cout << "Error making shader program: " << std::endl;
        std::cout << ::g_pShaderManager->getLastError() << std::endl;
    }



    glUseProgram(program);


    //GLint mvp_location = -1;
    mvp_location = glGetUniformLocation(program, "MVP");

    // Get "uniform locations" (aka the registers these are in)
    GLint matModel_Location = glGetUniformLocation(program, "matModel");
    GLint matView_Location = glGetUniformLocation(program, "matView");
    GLint matProjection_Location = glGetUniformLocation(program, "matProjection");
    GLint matModelInverseTranspose_Location = glGetUniformLocation(program, "matModelInverseTranspose");





    ::g_pTheLights->theLights[0].position = glm::vec4(-3500.0f, -1280.0f, -600, 1.0f);
    ::g_pTheLights->theLights[0].diffuse = glm::vec4(4.0f, 4.0f, 4.0f, 1.0f);
    //... and so on...
//    	vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
//	                // 0 = pointlight
//					// 1 = spot light
//					// 2 = directional light
//    ::g_pTheLights->theLights[0].param1.x = 1.0f;    // Spot light
    ::g_pTheLights->theLights[0].param1.x = 0.0f;    // point light
    // Direction RELATIVE TO THE LIGHT
    // (-1 in y is straight down)
    ::g_pTheLights->theLights[0].direction = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    ::g_pTheLights->theLights[0].param1.y = 90.0f;   // Inner
    ::g_pTheLights->theLights[0].param1.z = 10.0f;   // Outer
    //::g_pTheLights->theLights[0].atten.x = 0.0000001f;
    ::g_pTheLights->theLights[0].atten.y = 0.0000001f;
    ::g_pTheLights->theLights[0].atten.z = 0.0000001f;

    ::g_pTheLights->TurnOnLight(0);  // Or this!

    ::g_pTheLights->SetUpUniformLocations(program);

    ::g_pVAOManager->setFilePath("assets/models/");

    /*::g_pTextureManager->SetBasePath("assets/models/Textures");
    ::g_pTextureManager->Create2DTextureFromBMPFile("Dungeons_2_Texture_01_A.bmp", true);
*/






    std::vector<std::string> vecModelsToLoad;
    std::vector<std::string> vecModelsChecl;

    vecModelsToLoad.push_back("SpaceInvader_Base_block.ply");
    vecModelsToLoad.push_back("SpaceInvader_Bomb_pose_1.ply");
    vecModelsToLoad.push_back("SpaceInvader_Bomb_pose_2.ply");
    vecModelsToLoad.push_back("SpaceInvader_Bomb_pose_3.ply");
    vecModelsToLoad.push_back("SpaceInvader_Explosions.ply");
    vecModelsToLoad.push_back("SpaceInvader_I1_block_pose_1.ply");
    vecModelsToLoad.push_back("SpaceInvader_I1_block_pose_2.ply");
    vecModelsToLoad.push_back("SpaceInvader_I2_block_pose_1.ply");
    vecModelsToLoad.push_back("SpaceInvader_I2_block_pose_2.ply");
    vecModelsToLoad.push_back("SpaceInvader_I3_block_pose_1.ply");
    vecModelsToLoad.push_back("SpaceInvader_I3_block_pose_2.ply");
    for (int i = 0; i <= 9; i++) {
        std::string strr = "";
        strr = "SpaceInvader_Number_" + std::to_string(i);
        strr.append(".ply");
        vecModelsToLoad.push_back(strr);
    }
    vecModelsToLoad.push_back("SpaceInvader_Shield_block.ply");
    vecModelsToLoad.push_back("SpaceInvader_UFO_block.ply");
    vecModelsToLoad.push_back("SpaceInvader_Missile.ply");



    unsigned int totalVerticesLoaded = 0;
    unsigned int totalTrianglesLoaded = 0;
    for (std::vector<std::string>::iterator itModel = vecModelsToLoad.begin(); itModel != vecModelsToLoad.end(); itModel++)
    {
        sModelDrawInfo theModel;
        std::string modelName = *itModel;
        std::cout << "Loading " << modelName << "...";
        if (!::g_pVAOManager->LoadModelIntoVAO(modelName, theModel, program))
        {
            std::cout << "didn't work because: " << std::endl;
            std::cout << ::g_pVAOManager->getLastError(true) << std::endl;
        }
        else
        {
            std::cout << "OK." << std::endl;
            std::cout << "\t" << theModel.numberOfVertices << " vertices and " << theModel.numberOfTriangles << " triangles loaded." << std::endl;
            totalTrianglesLoaded += theModel.numberOfTriangles;
            totalVerticesLoaded += theModel.numberOfVertices;
        }
    }//for (std::vector<std::string>::iterator itModel



    /*::g_pTextureManager->SetBasePath("assets/models/Textures");
    ::g_pTextureManager->Create2DTextureFromBMPFile("Dungeons_2_Texture_01_A.bmp", true);*/


    std::cout << "Done loading models." << std::endl;
    std::cout << "Total vertices loaded = " << totalVerticesLoaded << std::endl;
    std::cout << "Total triangles loaded = " << totalTrianglesLoaded << std::endl;

    setObjects("SpaceInvader_I2_block_pose_", glm::vec3(0.0f, 0.0f, 0.0f), 0);
    //setObjects("Floors/SM_Env_Dwarf_Floor_01.ply", glm::vec3(50.0f, 0.0f, 0.0f), 0);




    const double MAX_DELTA_TIME = 0.1;  // 100 ms
    double previousTime = glfwGetTime();
    int valuecheckAdd = 1;
    int conditionValue = 0;

    bool checkEnemyMovementRight = false;
    bool checkEnemyMovementLeft = true;
    bool checkEnemyMovementRightAnim = false;
    bool checkEnemyMovementLeftAnim = true;
    bool checkUFOMovementLeft = true;
    bool showUFO = false;

    bool whichoneToShow = true;
    int checkConditionValue = 0;
    int heightReduction = 100;
    int UFOcondition = 0;
    while (!glfwWindowShouldClose(pWindow))
    {
        valuecheckAdd++;
        UFOcondition++;
        float ratio;
        int width, height;
        glm::mat4 matModel;             // used to be "m"; Sometimes it's called "world"
        glm::mat4 matProjection;        // used to be "p";
        glm::mat4 matView;              // used to be "v";

        double currentTime = glfwGetTime();
        double deltaTime = previousTime - currentTime;
        deltaTime = (deltaTime > MAX_DELTA_TIME ? MAX_DELTA_TIME : deltaTime);
        previousTime = currentTime;

        glfwGetFramebufferSize(pWindow, &width, &height);
        ratio = width / (float)height;

        // Turn on the depth buffer
        glEnable(GL_DEPTH);         // Turns on the depth buffer
        glEnable(GL_DEPTH_TEST);    // Check if the pixel is already closer

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSetWindowTitle(pWindow, ::g_TitleText.c_str());

        // Copy the light information into the shader to draw the scene
        ::g_pTheLights->CopyLightInfoToShader();


        // HACK: Debug sphere is 5th item added
//        ::g_vecMeshes[5].positionXYZ = gTheLights.theLights[0].position;

        matProjection = glm::perspective(
            ::g_pFlyCamera->FOV,
            ratio,
            ::g_pFlyCamera->nearPlane,      // Near plane (as large as possible)
            ::g_pFlyCamera->farPlane);      // Far plane (as small as possible)


        ::g_pFlyCamera->Update(deltaTime);

        glm::vec3 cameraEye = ::g_pFlyCamera->getEye();
        glm::vec3 cameraAt = ::g_pFlyCamera->getAtInWorldSpace();
        glm::vec3 cameraUp = ::g_pFlyCamera->getUpVector();


        matView = glm::mat4(1.0f);
        matView = glm::lookAt(cameraEye,   // "eye"
            cameraAt,    // "at"
            cameraUp);


        glUniformMatrix4fv(matView_Location, 1, GL_FALSE, glm::value_ptr(matView));
        glUniformMatrix4fv(matProjection_Location, 1, GL_FALSE, glm::value_ptr(matProjection));


        for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
        {
            // So the code is a little easier...
            cMesh* pCurrentMesh = ::g_vec_pMeshes[index];

            matModel = glm::mat4(1.0f);  // "Identity" ("do nothing", like x1)
            //mat4x4_identity(m);

            DrawObject(pCurrentMesh,
                matModel,
                matModel_Location,
                matModelInverseTranspose_Location,
                program,
                ::g_pVAOManager);
            DrawObject(::g_UFO,
                matModel,
                matModel_Location,
                matModelInverseTranspose_Location,
                program,
                ::g_pVAOManager);

        }

        if (fireMissile) {

            if (::g_Missile->positionXYZ.y < 10) {
                ::g_Missile->positionXYZ.y = ::g_Missile->positionXYZ.y + 10;


                matModel = glm::mat4(1.0f);  // "Identity" ("do nothing", like x1)
                //mat4x4_identity(m);

                DrawObject(::g_Missile,
                    matModel,
                    matModel_Location,
                    matModelInverseTranspose_Location,
                    program,
                    ::g_pVAOManager);

            }
            else {
                fireMissile = false;
                ::g_Missile->positionXYZ.y = ::g_vec_pMeshes[0]->positionXYZ.y;
            }
        }

        for (unsigned int index = 0; index != ::g_vec_pMeshes.size(); index++)
        {
            ::g_vec_pMeshes.at(index)->bIsWireframe = bIsWireframe;

            //::g_vec_pMeshes.at(index)->bIsVisible = false;
        }

        if (UFOcondition == 20) {
            if (showUFO) {

                if (checkUFOMovementLeft) {
                    ::g_UFO->bIsVisible = true;
                    ::g_UFO->positionXYZ.x = ::g_UFO->positionXYZ.x + 20;
                }

                if ((::g_UFO->positionXYZ.x > (1000 - 1990.0f))) {
                    checkUFOMovementLeft = false;
                    showUFO = false;
                }





            }
            else {
                ::g_UFO->bIsVisible = false;
                ::g_UFO->positionXYZ.x = -3000.0f;
            }
            UFOcondition = 0;
        }


        if (valuecheckAdd == (60 - conditionValue)) {

            if (checkConditionValue % 2 == 1) {
                for (unsigned int index = 0; index != ::g_vec_pEnemy.size(); index++)
                {
                    ::g_vec_pEnemyTimeSkip.at(index)->bIsVisible = false;
                    ::g_vec_pEnemy.at(index)->bIsVisible = true;

                    /*::g_vec_pEnemyTimeSkip.at(index)->bIsVisible = false;
                    ::g_vec_pEnemy.at(index)->bIsVisible = true;*/
                    if (checkEnemyMovementLeft) {
                        ::g_vec_pEnemy.at(index)->positionXYZ.x = ::g_vec_pEnemy.at(index)->positionXYZ.x + 20;
                        std::cout << "index: " << index << " position: " << ::g_vec_pEnemy.at(index)->positionXYZ.x << "\n";
                        //checkEnemyMovementRight = true;

                    }
                    else if (checkEnemyMovementRight) {
                        ::g_vec_pEnemy.at(index)->positionXYZ.x = ::g_vec_pEnemy.at(index)->positionXYZ.x - 20;
                        std::cout << "index: " << index << " position: " << ::g_vec_pEnemy.at(index)->positionXYZ.x << "\n";


                        //checkEnemyMovementRight = false;
                    }

                    //::g_vec_pEnemy.at(index)->positionXYZ.x = ::g_vec_pEnemy.at(index)->positionXYZ.x - 20;
                }

                if ((::g_vec_pEnemy.at(0)->positionXYZ.x > (1000 - 1990.0f))) {
                    checkEnemyMovementLeft = false;
                    checkEnemyMovementRight = true;
                    if (conditionValue != 55) {
                        conditionValue = conditionValue + 11;
                    }
                    for (unsigned int index = 0; index != ::g_vec_pEnemy.size(); index++)
                    {
                        ::g_vec_pEnemy.at(index)->positionXYZ.y = ::g_vec_pEnemy.at(index)->positionXYZ.y - heightReduction;
                    }

                }
                if (checkEnemyMovementRight) {
                    if ((::g_vec_pEnemy.at(0)->positionXYZ.x < (400 - 1990.0f))) {
                        checkEnemyMovementLeft = true;
                        checkEnemyMovementRight = false;
                        if (conditionValue != 55) {
                            conditionValue = conditionValue + 11;
                        }
                        for (unsigned int index = 0; index != ::g_vec_pEnemy.size(); index++)
                        {
                            ::g_vec_pEnemy.at(index)->positionXYZ.y = ::g_vec_pEnemy.at(index)->positionXYZ.y - heightReduction;
                        }
                    }
                    showUFO = true;

                }
            }
            else {
                for (unsigned int index = 0; index != ::g_vec_pEnemyTimeSkip.size(); index++)
                {
                    ::g_vec_pEnemy.at(index)->bIsVisible = false;
                    ::g_vec_pEnemyTimeSkip.at(index)->bIsVisible = true;
                    if (checkEnemyMovementLeftAnim) {
                        ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.x = ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.x + 20;
                        //checkEnemyMovementRight = true;
                    }
                    else if (checkEnemyMovementRightAnim) {
                        ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.x = ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.x - 20;
                        //checkEnemyMovementRight = false;
                    }

                    //::g_vec_pEnemy.at(index)->positionXYZ.x = ::g_vec_pEnemy.at(index)->positionXYZ.x - 20;
                }

                if ((::g_vec_pEnemyTimeSkip.at(0)->positionXYZ.x > (1000 - 1990.0f))) {
                    checkEnemyMovementLeftAnim = false;
                    checkEnemyMovementRightAnim = true;
                    if (conditionValue != 55) {
                        conditionValue = conditionValue + 11;
                    }
                    for (unsigned int index = 0; index != ::g_vec_pEnemyTimeSkip.size(); index++)
                    {
                        ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.y = ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.y - heightReduction;
                    }

                }
                if (checkEnemyMovementRightAnim) {
                    if ((::g_vec_pEnemyTimeSkip.at(0)->positionXYZ.x < (400 - 1990.0f))) {
                        checkEnemyMovementLeftAnim = true;
                        checkEnemyMovementRightAnim = false;
                        if (conditionValue != 55) {
                            conditionValue = conditionValue + 11;
                        }
                        for (unsigned int index = 0; index != ::g_vec_pEnemyTimeSkip.size(); index++)
                        {
                            ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.y = ::g_vec_pEnemyTimeSkip.at(index)->positionXYZ.y - heightReduction;
                        }
                    }

                }
            }

            checkConditionValue++;
            valuecheckAdd = 0;

        }

        ;

        //std::cout << "asd: " << deltaTime<<"\n";



        // "Present" what we've drawn.
        glfwSwapBuffers(pWindow);        // Show what we've drawn

        // Process any events that have happened
        glfwPollEvents();

        // Handle OUR keyboard, mouse stuff
        handleAsyncKeyboard(pWindow, deltaTime);
        handleAsyncMouse(pWindow, deltaTime);

    }//while (!glfwWindowShouldClose(window))

    // All done, so delete things...
    ::g_ShutDown(pWindow);


    glfwDestroyWindow(pWindow);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void setFloorObject(std::string meshName) {
    cMesh* meshPointer = new cMesh();
    meshPointer->meshName = meshName;
    meshPointer->positionXYZ = glm::vec3(5.0f, 0.0f, 5.0f);

    /*meshPointer->bIsWireframe = true;
    meshPointer->bUseObjectDebugColour = true;
    meshPointer->objectDebugColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);*/
    //meshPointer->bDontLight = true;
    ::g_vec_pMeshes.push_back(meshPointer);

}

void setObjects(std::string meshName, glm::vec3 vectorPosition, float angle) {
    generatePlayer();
    generateUFO();
    generateMissile();
    generateBlock();
    generateEnemy("SpaceInvader_I2_block_pose_", 0);
    generateEnemy("SpaceInvader_I1_block_pose_", 240);
    generateEnemy("SpaceInvader_I3_block_pose_", 480);
}

void generateMissile() {
    cMesh* meshPointer3 = new cMesh();
    meshPointer3->scaleXYZ = glm::vec3(1.0f);
    meshPointer3->meshName = "SpaceInvader_Missile.ply";
    meshPointer3->positionXYZ = glm::vec3(-1400.0f, -1300.0f, 0.0f);
    meshPointer3->orientationXYZ.y = 0;
    meshPointer3->bIsWireframe = bIsWireframe;
    //::g_vec_pMeshes.push_back(meshPointer3);
    ::g_Missile = meshPointer3;
}

void generateUFO() {
    cMesh* meshPointer3 = new cMesh();
    meshPointer3->scaleXYZ = glm::vec3(1.0f);
    meshPointer3->meshName = "SpaceInvader_UFO_block.ply";
    meshPointer3->positionXYZ = glm::vec3(-3000.0f, 200.0f, 0.0f);
    meshPointer3->orientationXYZ.y = 0;
    meshPointer3->bIsWireframe = bIsWireframe;
    meshPointer3->bIsVisible = false;
    //::g_vec_pMeshes.push_back(meshPointer3);
    ::g_UFO = meshPointer3;
}

void generateBlock() {
    cMesh* block1 = new cMesh();
    block1->scaleXYZ = glm::vec3(1.0f);
    block1->meshName = "SpaceInvader_Shield_block.ply";
    block1->positionXYZ = glm::vec3(-1390.0f - 120, -900.0f, 0.0f);
    block1->orientationXYZ.y = 0;
    block1->bIsWireframe = bIsWireframe;
    ::g_vec_pMeshes.push_back(block1);

    cMesh* block2 = new cMesh();
    block2->scaleXYZ = glm::vec3(1.0f);
    block2->meshName = "SpaceInvader_Shield_block.ply";
    block2->positionXYZ = glm::vec3(-1690 - 120, -900.0f, 0.0f);
    block2->orientationXYZ.y = 0;
    block2->bIsWireframe = bIsWireframe;
    ::g_vec_pMeshes.push_back(block2);

    cMesh* block3 = new cMesh();
    block3->scaleXYZ = glm::vec3(1.0f);
    block3->meshName = "SpaceInvader_Shield_block.ply";
    block3->positionXYZ = glm::vec3(-1990 - 120, -900.0f, 0.0f);
    block3->orientationXYZ.y = 0;
    block3->bIsWireframe = bIsWireframe;
    ::g_vec_pMeshes.push_back(block3);

    cMesh* block4 = new cMesh();
    block4->scaleXYZ = glm::vec3(1.0f);
    block4->meshName = "SpaceInvader_Shield_block.ply";
    block4->positionXYZ = glm::vec3(-2290 - 120, -900.0f, 0.0f);
    block4->orientationXYZ.y = 0;
    block4->bIsWireframe = bIsWireframe;
    ::g_vec_pMeshes.push_back(block4);

}

void generatePlayer() {
    cMesh* meshPointer3 = new cMesh();
    meshPointer3->scaleXYZ = glm::vec3(1.0f);
    meshPointer3->meshName = "SpaceInvader_Base_block.ply";
    meshPointer3->positionXYZ = glm::vec3(-1990.0f, -1300.0f, 0.0f);
    meshPointer3->orientationXYZ.y = 0;
    meshPointer3->bIsWireframe = bIsWireframe;
    ::g_vec_pMeshes.push_back(meshPointer3);
}

void generateEnemy(std::string meshname, int height) {
    int value = -120;
    int value1 = -120;
    int value2 = -120;
    int value3 = -120;
    int locationChange = 1990.0f;
    for (int i = 0; i < 11; i++) {

        cMesh* meshPointer = new cMesh();
        meshPointer->scaleXYZ = glm::vec3(1.0f);
        meshPointer->meshName = meshname + "1.ply";
        meshPointer->positionXYZ = glm::vec3(700.0f + value - locationChange, 0.0f - height, 0.0f);
        meshPointer->orientationXYZ.y = 0;
        meshPointer->wholeObjectDiffuseRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);;
        meshPointer->bUseWholeObjectDiffuseColour = true;

        meshPointer->bIsWireframe = bIsWireframe;
        ::g_vec_pMeshes.push_back(meshPointer);
        ::g_vec_pEnemy.push_back(meshPointer);
        value = value - 160;

        cMesh* meshPointer1 = new cMesh();
        meshPointer1->scaleXYZ = glm::vec3(1.0f);
        meshPointer1->meshName = meshname + "1.ply";
        meshPointer1->positionXYZ = glm::vec3(700.0f + value1 - locationChange, 120.0f - height, 0.0f);
        meshPointer1->orientationXYZ.y = 0;
        meshPointer1->bIsWireframe = bIsWireframe;
        ::g_vec_pMeshes.push_back(meshPointer1);
        ::g_vec_pEnemy.push_back(meshPointer1);
        value1 = value1 - 160;

        cMesh* meshPointer2 = new cMesh();
        meshPointer2->scaleXYZ = glm::vec3(1.0f);
        meshPointer2->meshName = meshname + "2.ply";
        meshPointer2->positionXYZ = glm::vec3(700.0f + value2 - locationChange, 0.0f - height, 0.0f);
        meshPointer2->orientationXYZ.y = 0;
        meshPointer2->bIsWireframe = bIsWireframe;
        meshPointer2->bIsVisible = false;
        ::g_vec_pMeshes.push_back(meshPointer2);
        ::g_vec_pEnemyTimeSkip.push_back(meshPointer2);
        value2 = value2 - 160;

        cMesh* meshPointer3 = new cMesh();
        meshPointer3->scaleXYZ = glm::vec3(1.0f);
        meshPointer3->meshName = meshname + "2.ply";
        meshPointer3->positionXYZ = glm::vec3(700.0f + value3 - locationChange, 120.0f - height, 0.0f);
        meshPointer3->orientationXYZ.y = 0;
        meshPointer3->bIsVisible = false;
        meshPointer3->bIsWireframe = bIsWireframe;
        ::g_vec_pMeshes.push_back(meshPointer3);
        ::g_vec_pEnemyTimeSkip.push_back(meshPointer3);
        value3 = value3 - 160;
    }
}


std::string getRandom(float low, float high)
{
    int value = low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (high - low));
    return std::to_string(value);

}

void setObjectWall(std::string meshName, glm::vec3 vectorPosition, float angle) {

}

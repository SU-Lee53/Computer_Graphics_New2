#pragma once
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

#include <assimp/BaseImporter.h>


#include <vector>
#include <string>
#include <queue>
#include <algorithm>

#include "__enum.h"
#include "__struct.h"
#include "__defines.h"
#include "Utills.h"


#include "Shaders.h"
#include "VBO.h"
#include "VAO.h"
#include "Objects.h"
#include "Camera.h"
#include "Projection.h"
#include "Model.h"

#include "Core.h"
#include "InputManager.h"
#include "TransformManager.h"
#include "TimeManager.h"

#include "Examples.h"
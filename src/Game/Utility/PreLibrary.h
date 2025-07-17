#pragma once

// Third Party Libs

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SDL3/SDL.h>

#include <entt/entt.hpp>

#include "stb_image.h"

#include <freetype/freetype.h>

#include <sndfile.h>

#include <AL/al.h>
#include <AL/alc.h>

// Standard Libs

#include <algorithm>
#include <string_view>
#include <filesystem>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <array>
#include <stacktrace>
#include <print>
#include <stdexcept>
#include <random>
#include <thread>

// Classes

#include "Utility/GameCore.h"

#include "Render/Renderer.h"

#include "WorldTypes/Entity.h"


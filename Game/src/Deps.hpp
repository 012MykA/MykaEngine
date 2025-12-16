// Window
constexpr auto WINDOW_WIDTH = 1920;
constexpr auto WINDOW_HEIGHT = 1080;

// Shaders
constexpr auto COLOR_VERTEX_SHADER_PATH = "E:/vscode/MykaEngine/shaders/colorVert.glsl";
constexpr auto COLOR_FRAGMENT_SHADER_PATH = "E:/vscode/MykaEngine/shaders/colorFrag.glsl";

constexpr auto TEX_VERTEX_SHADER_PATH = "E:/vscode/MykaEngine/shaders/texVert.glsl";
constexpr auto TEX_FRAGMENT_SHADER_PATH = "E:/vscode/MykaEngine/shaders/texFrag.glsl";

constexpr auto LIGHT_VERTEX_SHADER_PATH = "E:/vscode/MykaEngine/shaders/lightVert.glsl";
constexpr auto LIGHT_FRAGMENT_SHADER_PATH = "E:/vscode/MykaEngine/shaders/lightFrag.glsl";

// Textures
constexpr auto SKYBOX_TEXTURE_PATH = "E:/vscode/MykaEngine/assets/skyboxes/ocean/skybox.png";
constexpr auto WOOD_TEXTURE_PATH = "E:/vscode/MykaEngine/assets/textures/wood.png";
constexpr auto BRICK_TEXTURE_PATH = "E:/vscode/MykaEngine/assets/textures/brick.png";
constexpr auto WHITE_CONCRETE_TEXTURE_PATH = "E:/vscode/MykaEngine/assets/textures/white-concrete.jpg";

// https://www.solarsystemscope.com/textures/
constexpr auto EARTH_TEXTURE_PATH = "E:/vscode/MykaEngine/assets/textures/8k_earth_daymap.jpg";
constexpr auto SUN_TEXTURE_PATH = "E:/vscode/MykaEngine/assets/textures/8k_sun.jpg";


// Planets Values
constexpr float REAL_TO_SCENE_SCALE = 100.0f / (6.96f * 1e8f);

constexpr float EARTH_RADIUS = (6.371f * 1e6f) * REAL_TO_SCENE_SCALE;
constexpr float SUN_RADIUS = (6.96f * 1e8f) * REAL_TO_SCENE_SCALE;

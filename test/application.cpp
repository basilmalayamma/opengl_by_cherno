#include <application.h>	

Application::Application():
	mShader(NULL),
	mVA(NULL),
	mVB(NULL),
	mIB1(NULL),
	mIB2(NULL),
	mTexture(NULL),
	mRenderer(new (Renderer)) {
}

int Application::init() {
    if(!glfwInit()) {
	std::cout << "glfwInit() failed." << std::endl;
	return -1;
    }

    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    GLCall(glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    GLCall(glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
    GLCall(glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE));

    GLCall(mWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL));
    if (!mWindow) {
        GLCall(glfwTerminate());
	return -1;
    }

    GLCall(glfwMakeContextCurrent(mWindow));

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(GLenum err = glewInit());
    if (err != GLEW_OK) {
        std::cout << "Error in glewInit()" << std::endl;
	return -1;
    }
    return 0;
}

void Application::initializeShader(std::string path) {
    mShader = std::shared_ptr<shader>(new shader(path));
    mShader->attach();
}

int Application::initializeBuffers() {
    mVA = std::shared_ptr<vertexArray>(new vertexArray(2));
    int vertexDataCount = sizeof(vertexData)/sizeof(vertexData[0]);
    mVB = std::shared_ptr<vertexBuffer>(new vertexBuffer(vertexDataCount, &vertexData[0]));
    mVB->bind();
    mVA->enablePointer(mShader->getID(), "position", 0);
    mVA->enablePointer(mShader->getID(), "coordinates", 2);


    mIB1 = std::shared_ptr<indexBuffer>(new indexBuffer(3, indices1));
    GLCall(mIB1->unBind());

    mIB2 = std::shared_ptr<indexBuffer>(new indexBuffer(3, indices2));
    GLCall(mIB2->unBind());
    return 0;
}

unsigned int Application::getShaderID() {
    return mShader->getID();
}

int Application::initializeTexture(std::string path) {
    mTexture = std::shared_ptr<Texture>(new Texture(path));
    return 0;
}

int Application::render() {
    glViewport(0, 0, WIDTH, HEIGHT);
    while (!glfwWindowShouldClose(mWindow)) {
        mRenderer->clear();

	mTexture->Bind();
	mRenderer->render(mVA, mIB1);
	mRenderer->render(mVA, mIB2);

        GLCall(glfwSwapBuffers(mWindow));
        GLCall(glfwPollEvents());
    }
    return 0;
}

int Application::setupBlend() {
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_ONE, GL_ZERO));
    GLCall(glBlendEquation(GL_FUNC_ADD));
    return 0;
}

Application::~Application() {
    mShader->detach();
    glfwTerminate();
}

int Application::setShaderValue(std::string name, int value) {
    GLuint texID = glGetUniformLocation(getShaderID(), name.c_str());
    glUniform1i(texID, value);
    return 0;
}

int Application::setShaderValue(std::string name, const glm::mat4 &proj) {
    GLuint texID = glGetUniformLocation(getShaderID(), name.c_str());
    glUniformMatrix4fv(texID, 1, GL_FALSE, &proj[0][0]);
    return 0;
}

int main(void) {
    Application app;
    app.init();

    app.initializeShader(SHADER_PATH);
    app.initializeBuffers();
    app.initializeTexture(TEXTURE_PATH);
    app.setupBlend();

    app.setShaderValue("text", 0);

    glm::mat4 proj = glm::ortho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);
    app.setShaderValue("u_MPV", proj);

    app.render();
    return 0;
}

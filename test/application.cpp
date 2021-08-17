#include <application.h>	
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

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

    glm::mat4 proj = glm::ortho(-2.0, 2.0, -1.5, 1.5, -1.0, 1.0);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-0.5f, 0.0f, 0.0f));

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(mWindow, true);

    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 background_colour = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

    while (!glfwWindowShouldClose(mWindow)) {
        mRenderer->clear(
		background_colour.x,
		background_colour.y,
		background_colour.z);

	ImGui_ImplGlfwGL3_NewFrame();

	{
            static float f = 0.0f;
            static int counter = 0;
            ImGui::Text("SpiloGasteR");
            ImGui::SliderFloat("Movement", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("Backgroung Colour", (float*)&background_colour);

	    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(f, 0.0, 0.0));
	    glm::mat4 MVP = proj * view * model;
	    setShaderValue("u_MPV", MVP);

	    ImGui::Checkbox("Check box", &show_demo_window);

            if (ImGui::Button("Button"))
                counter++;
            ImGui::SameLine();
            ImGui::Text("Counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

	mTexture->Bind();
	mRenderer->render(mVA, mIB1);
	mRenderer->render(mVA, mIB2);

	ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

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
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
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

    app.render();
    return 0;
}

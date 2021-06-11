#include <shader.h>
#include <fstream>
#include <string.h>
#include <sstream>

enum shaderType {
    unknown = -1,
    vertex = 0,
    fragment = 1
};

shader::shader(std::string file_name) {
    std::ifstream file(file_name, std::ifstream::in);
    std::string line;
    int mode = shaderType::unknown;
    std::stringstream ss[2];

    while(getline(file, line)) {
	if(line.find("#shader") != std::string::npos) {
	    if(line.find("vertex") != std::string::npos) {
		mode = shaderType::vertex;
		continue;
	    }
	    else if(line.find("fragment") != std::string::npos) {
		mode = shaderType::fragment;
		continue;
	    }
	}

	ss[mode] << line << "\n";
    }

#if 0
    std::cout << "Vertex shader: " << std::endl;
    std::cout <<  mVertexShader << std::endl;

    std::cout << "Fragment shader: " << std::endl;
    std::cout << mFragmentShader << std::endl;
#endif
    compileProgram(
    	ss[shaderType::vertex].str(),
	ss[shaderType::fragment].str());
}

shader::~shader() {
    glDeleteProgram(mID);
}

void shader::attach() {
    glUseProgram(mID);
}

void shader::detach() {
    glUseProgram(0);
}

unsigned int shader::getID() {
    return mID;
}

void shader::compileProgram(
		std::string vertexShader,
		std::string fragmentShader) {
    mID = glCreateProgram();
    unsigned int vShader = compileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fShader = compileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(mID, vShader);
    glAttachShader(mID, fShader);
    glLinkProgram(mID);

    glDeleteShader(vShader);
    glDeleteShader(fShader);
}

unsigned int shader::compileShader(
		std::string srcCode,
		GLenum target) {
    unsigned int shader = glCreateShader(target);
    const char *src = srcCode.c_str();
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    GLint shader_compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_compiled);
    if (shader_compiled != GL_TRUE) {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        
	std::cout << target << " shader failed to compile." << std::endl;
	std::cout << message << std::endl;
	return 0;
    }

    return shader;
}

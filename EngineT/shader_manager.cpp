  
#include "shader_manager.h"


namespace EngineT
{
	ShaderManager::ShaderManager() {}

	ShaderManager::~ShaderManager() {}


	GLuint ShaderManager::CreateProgram(const string& vertexShader, const string& fragmentShader, const string& geometryShader)
	{
		GLuint shaderProg = glCreateProgram();

		if(shaderProg == 0) {
			errors.push_back("Error creating shader program");
			return 0;
		}

		GLuint vertex = CreateShader(GL_VERTEX_SHADER, vertexShader);
		if(vertex == 0) return 0;
		glAttachShader(shaderProg, vertex);

		GLuint fragment = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);
		if(fragment == 0) return 0;
		glAttachShader(shaderProg, fragment);

		GLuint geometry;
		if(geometryShader.length() > 0){
			geometry = CreateShader(GL_GEOMETRY_SHADER, geometryShader);
			if(geometry == 0) return 0;
			glAttachShader(shaderProg, geometry);
		}


		GLint success = 0;
		GLchar errorLog[1024] = {0};

		glLinkProgram(shaderProg);

		glGetProgramiv(shaderProg, GL_LINK_STATUS, &success);
		if(success == 0) {
			glGetProgramInfoLog(shaderProg, sizeof(errorLog), NULL, errorLog);
			errors.push_back("Error linking shader program:" + (string) errorLog);
			return 0;
		}

		glValidateProgram(shaderProg);
		glGetProgramiv(shaderProg, GL_VALIDATE_STATUS, &success);
		if(!success) {
			glGetProgramInfoLog(shaderProg, sizeof(errorLog), NULL, errorLog);
			errors.push_back("Invalid shader program:" + (string) errorLog);
			return 0;
		}



		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if(geometryShader.length() > 0){
			glDeleteShader(geometry);
		}


		return shaderProg;
	}


	GLuint ShaderManager::CreateProgram(const char* vertexFname, const char* fragmentFname, const char* geometryFname)
	{
		string vertexStr = ReadShaderFile(vertexFname);
		if(vertexStr == "") return 0;
		string fragmentStr = ReadShaderFile(fragmentFname);
		if(fragmentStr == "") return 0;

		string geometryStr;
		if(geometryFname != "") {
			geometryStr = ReadShaderFile(geometryFname);
		}
		else{
			geometryStr = "";
		}

		return CreateProgram(vertexStr, fragmentStr, geometryStr);
	}


	GLuint ShaderManager::CreateShader(GLenum shaderType, const string& shaderText)
	{
		GLuint shaderObj = glCreateShader(shaderType);

		if(shaderObj == 0) {
			errors.push_back("Error creating " + ShaderTypeString(shaderType) + " shader");
			return 0;
		}

		const GLchar* p[1];
		p[0] = shaderText.c_str();
		GLint lengths[1];
		lengths[0] = strlen(shaderText.c_str());
		glShaderSource(shaderObj, 1, p, lengths);

		glCompileShader(shaderObj);

		GLint success;
		glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);

		if(!success) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderObj, 1024, NULL, infoLog);
			errors.push_back("Error compiling shader: " + (string) infoLog);
			return 0;
		}

		return shaderObj;
	}


	GLint ShaderManager::GetUniformLoc(GLuint shaderProg, const char* uniformName)
	{
		GLint location = glGetUniformLocation(shaderProg, uniformName);

		if(location == 0xFFFFFFFF) {
			errors.push_back("invalid uniform location:" + ((string) uniformName));
		}

		return location;
	}


	unordered_map<string, GLint> ShaderManager::GetAllUniforms(GLuint shaderProg)
	{
		unordered_map<string, GLint> locations;

		GLint count;
		glGetProgramiv(shaderProg, GL_ACTIVE_UNIFORMS, &count);

		cout << "<------ SHADER uniforms --------->" << endl;
		cout << "uniforms count: " << count << endl;
		std::vector<GLchar> nameData(256);
		for(int unif = 0; unif < count; ++unif)
		{
			GLint arraySize = 0;
			GLenum type = 0;
			GLsizei actualLength = 0;
			glGetActiveUniform(shaderProg, unif, nameData.size(), &actualLength, &arraySize, &type, &nameData[0]);
			string name((char*) &nameData[0], actualLength);

			cout << name << endl;
			GLint location = glGetUniformLocation(shaderProg, name.c_str());

			if(location == 0xFFFFFFFF) {
				errors.push_back("invalid uniform location:" + name);
			}
			else{
				locations.insert(pair<string, GLint>(name, location));
			}
		}

		cout << " " << endl;
		return locations;
	}



	string ShaderManager::ShaderTypeString(GLuint shaderType)
	{
		switch(shaderType){
		case GL_VERTEX_SHADER:
			return "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			return "fragment";
			break;
		case GL_GEOMETRY_SHADER:
			return "geometry";
			break;
		default:
			return "unknown";
			break;
		}

	}


	void ShaderManager::PrintErrors()
	{
		if(errors.size() == 0){
			//Debug::SetColor();
			cout << "No errors in shader manager" << endl;
			return;
		}
		for(auto it = errors.begin(); it < errors.end(); it++){
			cout << *it << endl;
		}
		errors.clear();
	}

	string ShaderManager::ReadShaderFile(const char* filename)
	{
		ifstream file;
		file.open(filename);
		if(!file) {
			cout << "Impossible to open shader file: " << filename << endl;
			return "";
		}
		stringstream stream;
		stream << file.rdbuf();
		file.close();

		return stream.str();
	}
}
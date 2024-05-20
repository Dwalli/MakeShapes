#ifndef  SHADER_CLASS_H
#define SHADER_CLASS_H

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>


class Shader {

public:
	GLuint ID;
	Shader(const char* fragFile, const char* vertFile);
	std::string get_file_contents(const char* filename);

	void OnDelete();
	void OnActivate();


};


#endif //  SHADER_CLASS_H

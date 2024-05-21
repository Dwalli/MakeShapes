#ifndef VBO_H
#define VBO_H

#include<glad/glad.h>

class VBO
{
public:
	GLuint ID; // ID for the Vertex Buffer Object
	VBO(GLfloat* vertices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

private:

};


#endif // !VBH_H

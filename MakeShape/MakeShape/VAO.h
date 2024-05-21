#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID; // ID for the Vertex Array Object
	VAO();

	void LinkAttribute(VBO& VBO, GLuint layout,GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	void Bind();
	void Unbind();
	void Delete();

private:

};


#endif // !VBH_H
#ifndef VAO_H
#define VAO_H

#include<glad/glad.h>
#include"VBO.h"

class VAO
{
public:
	GLuint ID; // ID for the Vertex Array Object
	VAO();

	void LinkVBO(VBO VBO, GLuint layout);
	void Bind();
	void Unbind();
	void Delete();

private:

};


#endif // !VBH_H
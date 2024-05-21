#ifndef EBO_H
#define EBO_H

#include<glad/glad.h>

class EBO
{
public:
	GLuint ID;  // ID for the Elements buffer Object
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

private:

};


#endif // !VBH_H
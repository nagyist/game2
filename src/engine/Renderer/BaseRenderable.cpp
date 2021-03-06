#include "BaseRenderable.h"

Matrix4f* BaseRenderable::model_matrix = new Matrix4f();
Matrix4f* BaseRenderable::model_matrix_rotate = new Matrix4f();
Matrix4f* BaseRenderable::model_matrix_scale = new Matrix4f();
Matrix4f* BaseRenderable::model_matrix_translate = new Matrix4f();
Matrix4f* BaseRenderable::temp_matrix = new Matrix4f();
    
BaseRenderable::BaseRenderable()
{
    coords = Vec2f(0.0f, 0.0f);
    angle = 0.0f;
    scale = 1.0f;
    draw_type = GL_TRIANGLE_STRIP;
	vertexes = NULL;
	shader = 0;
}

void BaseRenderable::set_shader(GLuint program)
{
    shader = program;
    gvPositionHandle = glGetAttribLocation(shader, "vPosition");
    gModelHandle = glGetUniformLocation(shader, "Model");
    gFragColorHandle = glGetUniformLocation(shader, "fragColor");
}

void BaseRenderable::Draw()
{    
    model_matrix_rotate->RotateZ(angle);
    model_matrix_scale->Scale(scale, scale, scale);
    model_matrix_translate->Translate(coords.x, coords.y, 0.0f);
    model_matrix->Identity();
    temp_matrix->Identity();
    matrixMultiply(*model_matrix_rotate, *model_matrix_scale, *temp_matrix);
    matrixMultiply(*model_matrix_translate, *temp_matrix, *model_matrix);
    
    glUseProgram(shader);
    glUniform3f(gFragColorHandle, color.r, color.g, color.b);
    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, vertexes);
    glEnableVertexAttribArray(gvPositionHandle);

    glUniformMatrix4fv(gModelHandle, 1, GL_FALSE, model_matrix->get_val());
    glDrawArrays(draw_type, 0, vertexes_count);
}

void BaseRenderable::delete_vertexes()
{
	if(vertexes != NULL)
	{
		delete [] vertexes;
	}
}

void BaseRenderable::SetColor(Color3f& color)
{
	this->color = color;
}

void BaseRenderable::SetColor(float red, float green, float blue)
{
	this->color = Color3f(red, green, blue);
}

BaseRenderable::~BaseRenderable()
{
	//TODO: delete matrixes!
	delete [] vertexes;
}
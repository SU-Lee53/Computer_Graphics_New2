#include "pch.h"
#include "Renderer.h"

void Renderer::Render(VAO* vao)
{
	glBindVertexArray(vao->GetVAOHandle());

	if (vao->GetVaoType() == NON_INDEXED)
	{
		glDrawArrays(GL_TRIANGLES, 0, vao->GetVertexCount());
	}
	else
	{
		glDrawElements(GL_TRIANGLES, vao->GetElementCount(), GL_UNSIGNED_INT, 0);
	}

}

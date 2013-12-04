/*
* Copyright (c) 2012, Seed Developers
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. The origin of this software must not be misrepresented; you must not
*    claim that you wrote the original software.
* 2. Altered source versions must be plainly marked as such, and must not be
*    misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
* 4. A credit line is required in the game credits, as the following line:
*    Powered by Seed Framework
* 5. A Seed Framework logo should be displayed within a splash screen, or in
*    the case where the game haven't or cannot have a splash, a logo should be
*    displayed somewhere in the game (eg. menu, credits, other place).
*
* THIS SOFTWARE IS PROVIDED BY SEED DEVELOPERS ''AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL SEED DEVELOPERS BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "ShaderProgram.h"

#if defined(SEED_ENABLE_OGL20)

#include "api/ogl/oglHeaders.h"
#include "Shader.h"

#define TAG "[Shader] "

namespace Seed { namespace OpenGL {

OGL20ShaderProgram::OGL20ShaderProgram(String name)
{
	sName = name;

	// Create the shader program
	iProgramId = glCreateProgram();
}

OGL20ShaderProgram::~OGL20ShaderProgram()
{
}

void OGL20ShaderProgram::Use()
{
	glUseProgram(iProgramId);
	bActive = true;
}

void OGL20ShaderProgram::Unbind()
{
	glUseProgram(0);
	bActive = false;
}

void OGL20ShaderProgram::AttachShader(IShader *shader)
{
	vShaders += shader;
	glAttachShader(iProgramId, shader->GetShaderHandle());
}

void OGL20ShaderProgram::BindAttribute(const u32 index, const String attribName)
{
	mAttributes[attribName] = index;
	glBindAttribLocation(iProgramId, index, attribName.c_str());
}

void OGL20ShaderProgram::Link()
{
	glLinkProgram(iProgramId);
	bLinked = true;
}

}} // namespace

#endif // SEED_ENABLE_OGL20

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

#ifndef __SHADERMANAGER_H__
#define __SHADERMANAGER_H__

#include "Defines.h"
#include "Container.h"
#include "Enum.h"

namespace Seed {

class IShader;
class IShaderProgram;

typedef Map<String, IShaderProgram*> ShaderProgramMap;
typedef ShaderProgramMap::iterator ShaderProgramMapIterator;

typedef Map<String, IShader*> ShaderMap;
typedef ShaderMap::iterator ShaderMapIterator;

class SEED_CORE_API ShaderManager : public IObject
{
	SEED_SINGLETON_DECLARE(ShaderManager)

	public:
		virtual u32 GetProgramId(const String &name);
		virtual void AttachShader(IShader *shader, const String &name);
		virtual void LoadShaderSource(const String &name, const String &filename, ResourceManager *res);
		virtual void CompileShader(const String &name);
		virtual bool LinkShader(const String &name);
		virtual void AttachShaderToProgram(const String shaderName, const String shaderProgramName);
		virtual void Use(const String &name);
		IShaderProgram* operator[](const String programName);
		void Add(const String &name, IShaderProgram *shaderProgram);
		void Remove(const String &name);

		// IObject
		virtual const String GetClassName() const override;
		virtual int GetObjectType() const override;

	private:
		SEED_DISABLE_COPY(ShaderManager);

		ShaderProgramMap		mShaderPrograms;
		ShaderMap				mShaders;
		IShaderProgram			*pCurrentProgram;
};

#define pShaderManager ShaderManager::GetInstance()

} // namespace

#endif // __SHADERMANAGER_H__

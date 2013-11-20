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

#include "JobManager.h"
#include "Defines.h"
#include "Log.h"
#include "Enum.h"
#include "Job.h"
#include "EventJob.h"
#include "interface/IEventJobListener.h"

#define TAG		"[JobManager] "

namespace Seed {

SEED_SINGLETON_DEFINE(JobManager)

JobManager::JobManager()
	: vJob()
	, bEnabled(true)
{
}

JobManager::~JobManager()
{
}

bool JobManager::Initialize()
{
	return IManager::Initialize();
}

bool JobManager::Reset()
{
	for (auto job: vJob)
		job->Abort();

	return true;
}

bool JobManager::Shutdown()
{
	for (auto job: vJob)
	{
		job->Destroy();
		Delete(job);
	}

	JobVector().swap(vJob);
	return IManager::Shutdown();
}

bool JobManager::Update(f32 dt)
{
	if (bEnabled)
	{
		JobVector completed;
		JobVector aborted;

		for (auto job: vJob)
		{
			job->Update(dt);

			switch (job->GetState())
			{
				case eJobState::Completed:
				{
					completed += job;
				}
				break;

				case eJobState::Aborted:
				{
					aborted += job;
				}
				break;

				default:
				break;
			}
		}

		for (auto job: completed)
		{
			vJob -= job;

			EventJob ev(job, job->iName);
			job->pListener->OnJobCompleted(&ev);
		}

		for (auto job: aborted)
		{
			vJob -= job;

			EventJob ev(job, job->iName);
			job->pListener->OnJobAborted(&ev);
		}
	}

	return true;
}

Job *JobManager::Add(Job *job)
{
	Log(TAG "Job created");
	job->Create();
	vJob += job;

	return job;
}

void JobManager::Remove(Job *job)
{
	vJob -= job;
	job->Destroy();
	Log(TAG "Job destroyed");
}

void JobManager::Disable()
{
	bEnabled = false;
}

void JobManager::Enable()
{
	bEnabled = true;
}

} // namespace

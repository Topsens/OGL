#include "Program.h"
#include "Cleanup.h"
#include <string>

using namespace std;

bool Program::Create(const wstring& vshader, const wstring& fshader)
{
    if (!GLProgram::Create())
    {
        return false;
    }
    ONCLEANUP(release, [this]{ this->Release(); });

    string log;
    if (!this->vshader.Create(GL_VERTEX_SHADER)   || !this->vshader.Load(vshader) || !this->vshader.Compile(log) ||
        !this->fshader.Create(GL_FRAGMENT_SHADER) || !this->fshader.Load(fshader) || !this->fshader.Compile(log))
    {
        return false;
    }

    this->Attach(this->vshader);
    this->Attach(this->fshader);

    RESETCLEANUP(release, nullptr);
    return true;
}

void Program::Release()
{
    this->Detach(this->vshader);
    this->Detach(this->fshader);
    this->vshader.Release();
    this->fshader.Release();
    GLProgram::Release();
}
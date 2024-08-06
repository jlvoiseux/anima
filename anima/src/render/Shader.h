#pragma once

#include <map>
#include <string>

class Shader 
{
public:
    Shader();
    Shader(const std::string& vertex, const std::string& fragment);
    ~Shader();
    void Load(const std::string& vertex, const std::string& fragment);
    void Bind();
    void UnBind();
    unsigned int GetAttribute(const std::string& name);
    unsigned int GetUniform(const std::string& name);
    unsigned int GetHandle();

private:
    unsigned int mHandle;
    std::map<std::string, unsigned int> mAttributes;
    std::map<std::string, unsigned int> mUniforms;

    Shader(const Shader&);
    Shader& operator=(const Shader&);

    std::string ReadFile(const std::string& path);
    unsigned int CompileVertexShader(const std::string& vertex);
    unsigned int CompileFragmentShader(const std::string& fragment);
    bool LinkShaders(unsigned int vertex, unsigned int fragment);
    void PopulateAttributes();
    void PopulateUniforms();
};
//
// Created by ellie on 7/29/26.
//

#ifndef AURA_SHADER_COMPILATION_HANDLER_H
#define AURA_SHADER_COMPILATION_HANDLER_H
#include <sstream>
#include <unordered_map>

#include <glad/glad.h>

namespace Aura {
    class ShaderCompilationHandler {
    public:
        static std::string ReadFromFile(const GLchar *filename);
        static std::unordered_map<std::string, std::string> ReadFromFolder(const std::string &folderPath, bool recursive = false);
        static GLenum ExtensionToShaderType(const std::string &ext);
        static GLuint CompileShader(const std::string &source, GLenum type, const std::string &debugName);
        static GLuint LinkProgram(GLuint vertexShader, GLuint fragmentShader, const std::string &debugName);
        static std::unordered_map<std::string, GLuint> LoadShadersFromFolder(const std::string &folderPath, bool recursive = false);
    };
} // Aura

#endif //AURA_SHADER_COMPILATION_HANDLER_H

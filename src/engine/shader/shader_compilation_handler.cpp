//
// Created by ellie on 7/29/26.
//

#include "shader_compilation_handler.h"

#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <string>
#include <unordered_set>

namespace Aura {
    std::string ShaderCompilationHandler::ReadFromFile(const GLchar *filename) {
        std::ifstream fileStream(filename, std::ios::in);
        if (!fileStream.is_open()) {
            std::cerr << "failed to open shaderfile " << filename << std::endl;
            return "";
        }

        std::cout << "Read file " << filename << std::endl;

        std::stringstream buffer;
        buffer << fileStream.rdbuf();
        return buffer.str();
    }

    std::unordered_map<std::string, std::string> ShaderCompilationHandler::ReadFromFolder(const std::string &folderPath, bool recusive) {
        namespace fs = std::filesystem;
        std::unordered_map<std::string, std::string> shaderSources;

        static const std::unordered_set<std::string> validExtensions = {
            ".glsl", ".vert", ".frag"
        };

        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            std::cerr << "failed to find shader directory: " << folderPath << std::endl;
            return shaderSources;
        }

        auto processEntry = [&](const fs::directory_entry &entry) {
            if (!entry.is_regular_file()) return;
            if (validExtensions.find(entry.path().extension().string()) == validExtensions.end()) return;

            std::string source = ReadFromFile(entry.path().string().c_str());
            if (!source.empty()) {
                shaderSources[entry.path().filename().string()] = std::move(source);
            }
        };

        if (recusive) {
            for (const auto &entry : fs::recursive_directory_iterator(folderPath)) {
                processEntry(entry);
            }
        } else {
            for (const auto &entry : fs::directory_iterator(folderPath)) {
                processEntry(entry);
            }
        }

        return shaderSources;
    }

    std::unordered_map<std::string, GLuint> ShaderCompilationHandler::LoadShadersFromFolder(const std::string &folderPath, bool recursive) {
        namespace fs = std::filesystem;

        auto sources = ReadFromFolder(folderPath, recursive);
        std::unordered_map<std::string, GLuint> compiledShaders; // filename -> shader id
        std::unordered_map<std::string, GLuint> programs;         // basename -> program id

        // compile every source file individually
        for (const auto &[filename, source] : sources) {
            fs::path p(filename);
            GLenum type = ExtensionToShaderType(p.extension().string());
            if (type == GL_INVALID_ENUM) {
                std::cerr << "skipping " << filename << " — unrecognized shader stage" << std::endl;
                continue;
            }

            GLuint shader = CompileShader(source, type, filename);
            if (shader != 0) {
                compiledShaders[filename] = shader;
            }
        }

        // pair .vert with matching .frag by basename and link
        for (const auto &[filename, shaderId] : compiledShaders) {
            fs::path p(filename);
            if (p.extension() != ".vert") continue;

            std::string baseName = p.stem().string();
            std::string fragName = baseName + ".frag";

            auto it = compiledShaders.find(fragName);
            if (it == compiledShaders.end()) {
                std::cerr << "no matching .frag for " << filename << std::endl;
                continue;
            }

            GLuint program = LinkProgram(shaderId, it->second, baseName);
            if (program != 0) {
                programs[baseName] = program;
            }
        }

        // shaders are no longer needed once linked
        for (const auto &[filename, shaderId] : compiledShaders) {
            glDeleteShader(shaderId);
        }

        return programs;
    }

    GLenum ShaderCompilationHandler::ExtensionToShaderType(const std::string &ext) {
        if (ext == ".vert") return GL_VERTEX_SHADER;
        if (ext == ".frag") return GL_FRAGMENT_SHADER;
        return GL_INVALID_ENUM;
    }

    GLuint ShaderCompilationHandler::CompileShader(const std::string &source, GLenum type, const std::string &debugName) {
        GLuint shader = glCreateShader(type);
        const char *src = source.c_str();
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "shader compile error (" << debugName << "): " << infoLog << std::endl;
            glDeleteShader(shader);
            return 0;
        }
        return shader;
    }

    GLuint ShaderCompilationHandler::LinkProgram(GLuint vertexShader, GLuint fragmentShader, const std::string &debugName) {
        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "program link error (" << debugName << "): " << infoLog << std::endl;
            glDeleteProgram(program);
            return 0;
        }

        return program;
    }
} // Aura
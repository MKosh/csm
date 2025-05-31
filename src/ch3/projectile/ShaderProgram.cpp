#include "ShaderProgram.hpp"
#include <iostream>
#include <fstream>

ShaderProgram::ShaderProgram(std::span<Shader> shaders) {
  ID = glCreateProgram();
  int success = -1;
  char info_log[512];
  for (auto& shader : shaders) {
    std::cout << "Compiling: " << shader.path << "\n";
    compileShader(shader);
  }

  glLinkProgram(ID);
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(ID, 512, nullptr, info_log);
    std::cerr << "ERROR: Linking shader program\n  " << info_log << std::endl;
  }

  for (auto& shader : shaders) {
    glDeleteShader(shader.shader_id);
  }
}

std::string readShaderFile(std::filesystem::path path) {
  std::string code;
  std::ifstream shader_file;
  shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    shader_file.open(path);
    std::stringstream shader_stream;
    shader_stream << shader_file.rdbuf();
    shader_file.close();
    code = shader_stream.str();
  } catch (std::ifstream::failure& e) {
    std::cerr << "ERROR: shader file " << path << " not successfully read.\n  " << e.what() << std::endl;
  }

  return code;
}

auto ShaderProgram::compileShader(ShaderProgram::Shader& shader) -> void {
  int success = -1;
  char info_log[512];
  
  shader.shader_id = glCreateShader(shader.type);
  std::string source_str = readShaderFile(shader.path);
  const char* source = source_str.c_str();
  if (source == nullptr) {
    return;
  }

  glShaderSource(shader.shader_id, 1, &source, nullptr);
  glCompileShader(shader.shader_id);

  glGetShaderiv(shader.shader_id, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader.shader_id, 512, nullptr, info_log);
    std::cerr << "ERROR: compiling shader " << shader.path << " of type " << shader.type << "\n  " << info_log << std::endl;
  }

  glAttachShader(ID, shader.shader_id);

}

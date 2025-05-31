#pragma once

#include <filesystem>
#include <span>
#include "glad/gl.h"
#include "utils.h"

class ShaderProgram {
public:
  u32 ID;
  struct Shader {
    GLenum type;
    std::filesystem::path path;
    u32 shader_id;
  };

  ShaderProgram(std::span<Shader> shaders);
  auto compileShader(Shader& shader) -> void;
private:
};

auto compileShaders(ShaderProgram& shader_program) -> i32;

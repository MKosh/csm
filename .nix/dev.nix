{ pkgs ? import <nixpkgs> {} }:

let 
  matplotplusplus = pkgs.callPackage ./matplotplusplus.nix { inherit pkgs; };
  implot = pkgs.callPackage ./implot.nix { inherit pkgs; };
in
  pkgs.mkShell {
    packages = with pkgs; [
      clang-tools # clang-tools must come before clang for it to work properly
      clang
      lldb
      cmake
      gnumake
      ninja
      nlohmann_json
      pkg-config
      # matplotplusplus
      imgui
      glfw
      implot
      imgui
    ];

    shellHook = ''
      export MATPLOTPP=${matplotplusplus}
      export IMGUI=${pkgs.imgui}
      export IMPLOT=${implot}
    '';

  }

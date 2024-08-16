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
      wayland
    ];

    shellHook = ''
      # export MATPLOTPP=${matplotplusplus}
      LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/run/opengl-driver/lib:/run/opengl-driver-32/lib"
      LD_LIBRARY_PATH="$LD_LIBRARY_PATH:${pkgs.wayland}/lib"
      export LD_LIBRARY_PATH
      export IMGUI=${pkgs.imgui}
      export IMPLOT=${implot}
    '';

  }

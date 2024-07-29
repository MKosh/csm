{ pkgs ? import <nixpkgs> {} }:

let 
  matplotplusplus = pkgs.callPackage ./matplotplusplus.nix { inherit pkgs; };
in
  pkgs.mkShell {
    packages = with pkgs; [
      clang
      clang-tools
      lldb
      cmake
      gnumake
      ninja
      nlohmann_json
      pkg-config
      matplotplusplus
    ];

    shellHook = ''
      export MATPLOTPP=${matplotplusplus}
    '';

  }

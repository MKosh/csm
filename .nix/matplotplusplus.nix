{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
    name = "matplotplusplus";
    src = pkgs.fetchFromGitHub {
        owner = "alandefreitas";
        repo  = "matplotplusplus";
        rev   = "v1.2.1";
        hash = "sha256-ZEVQA+GcwCGvThHtdP5DuLb5MujwmxdCdnY7rc/Lrl4";
      };

    nativeBuildInputs = with pkgs; [
      cmake
      clang
      gnumake
    ];

    configurePhase = ''
      mkdir -p build
      cd build
      cmake ../ -DCMAKE_INSTALL_PREFIX=$out/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS="-O2" -DMATPLOTPP_BUILD_EXAMPLES=OFF -DMATPLOTPP_BUILD_TESTS=OFF
    '';

    buildPhase = ''
      cmake --build . --parallel 2 --config Release
    '';

    installPhase = ''
      cmake --install .
    '';

  }

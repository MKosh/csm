{ pkgs ? import <nixpkgs> {} }:

pkgs.stdenv.mkDerivation {
    name = "implot";
    src = pkgs.fetchFromGitHub {
        owner = "epezent";
        repo  = "implot";
        rev   = "v0.16";
        # hash = "sha256-ZEVQA+GcwCGvThHtdP5DuLb5MujwmxdCdnY7rc/Lrl4";
        hash = "sha256-/wkVsgz3wiUVZBCgRl2iDD6GWb+AoHN+u0aeqHHgem0=";
      };

    configurePhase = ''
      ls $src
    '';

    buildPhase = ''
    '';

    installPhase = ''
      mkdir $out
      cp $src/* $out/
      echo $out
    '';

  }

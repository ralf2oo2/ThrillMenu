{ pkgs ? import <nixpkgs> {} }:

let
  crossPkgs = pkgs.pkgsCross.mingw32;
in
crossPkgs.mkShell {
  nativeBuildInputs = [
    pkgs.cmake
    pkgs.ninja
  ];

  shellHook = ''
    export CC=i686-w64-mingw32-gcc
    export CXX=i686-w64-mingw32-g++
    export THRILLVILLE_DIR="/mnt/m2GamingDrive/SteamLibrary/steamapps/common/Thrillville Off the Rails"
  '';
}

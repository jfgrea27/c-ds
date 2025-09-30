{
  description = "Flake for c-ds.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, utils }:
    utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
      in {
        devShells.default = pkgs.mkShell {
          packages = [ 
            pkgs.stdenv 
            pkgs.gcc 
            pkgs.gdb
          ] ++ pkgs.lib.optionals (!pkgs.stdenv.isDarwin) [
            # valgrind is not available on latest darwin
            pkgs.valgrind
          ];
        };
      });
}
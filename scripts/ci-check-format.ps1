Param(
  [ValidateSet("Debug", "MinSizeRel", "Release", "RelWithDebInfo")][string] $configuration = "Debug"
)

$RepoRoot = Join-Path -Path $PSScriptRoot -ChildPath ".."
$ArtifactsDir = Join-Path -Path $RepoRoot -ChildPath "artifacts"
$BuildDir = Join-Path -Path $ArtifactsDir -ChildPath "build/$configuration"

cmake --build $BuildDir --target clang-format-ci

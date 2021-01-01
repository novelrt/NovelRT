SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  ScriptRoot="$( cd -P "$( dirname "$SOURCE" )" && pwd )"
  SOURCE="$(readlink "$SOURCE")"
  [[ $SOURCE != /* ]] && SOURCE="$ScriptRoot/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
ScriptRoot="$( cd -P "$( dirname "$SOURCE" )" && pwd )"

RepoRoot="$ScriptRoot/.."
ArtifactsDir="$RepoRoot/artifacts"
CreateDirectory "$ArtifactsDir"

function CreateDirectory {
  if [ ! -d "$1" ]; then
    mkdir -p "$1"
  fi
}

#See if diff picks up any changes after running clang-format
git diff > "$ArtifactsDir/clang-format.patch"

if [-s "$ArtifactsDir/clang-format.patch" ]
then
  raise error "Changes are required!"
else
  echo "No changes are required :D Passing..."
fi

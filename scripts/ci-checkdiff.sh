git diff > ../clang-format.patch
if [-s clang-format.patch ]
then
  raise error "Changes are required!"
else
  echo "No changes are required :D"
fi

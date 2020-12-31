$RepoRoot = Join-Path -Path $PSScriptRoot -ChildPath ".."
$output = $RepoRoot + "/clang-format.patch"

git diff > $output

if ((Get-Item $output).length -eq 0)
{
	rm $output
	throw "Generated diff contained no data!"
}

#To correct Windows errors when using git diff on certain systems.
((Get-Content $output) -replace '┬⌐','©') | Set-Content $output
((Get-Content $output) -join "`n") + "`n" | Set-Content -NoNewline $output

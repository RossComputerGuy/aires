#!/usr/bin

set -e
temp=$(mktemp -d)
function finish {
	rm -rf "${temp}"
}
trap finish EXIT
mkdir -p "$temp"
curl -L "https://storage.googleapis.com/shaderc/artifacts/prod/graphics_shader_compiler/shaderc/linux/continuous_clang_release/233/20191210-094435/install.tgz" | tar -xzf - -C "$temp"
cp -r "${temp}/install"/* /usr/*

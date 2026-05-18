#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${repo_root}"

build_dir="${DANS_TEMPLATE_BUILD_DIR:-build}"
target="dans_template"

cmake_args=(-S . -B "${build_dir}")
if [[ -d "${repo_root}/../dans-core" ]]; then
    cmake_args+=("-DDANS_CORE_SOURCE_DIR=${repo_root}/../dans-core")
fi

if [[ ! -f "${build_dir}/CMakeCache.txt" ]]; then
    cmake "${cmake_args[@]}"
fi

build_log="$(mktemp "${TMPDIR:-/tmp}/dans_template_build.XXXXXX")"
cleanup() {
    rm -f "${build_log}"
}
trap cleanup EXIT

if ! cmake --build "${build_dir}" --target "${target}" -j >"${build_log}" 2>&1; then
    cat "${build_log}" >&2
    exit 1
fi

exec "${build_dir}/${target}" "$@"

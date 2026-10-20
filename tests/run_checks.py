#!/usr/bin/env python3
"""Run C++11 host regressions and expected template diagnostics."""
import argparse
import os
from pathlib import Path
import shlex
import subprocess
import tempfile


def main():
    tests = Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--library', type=Path, default=tests.parent/'Grafici-GFX',
                        help='Grafici-GFX checkout (default: the pinned submodule)')
    parser.add_argument('--cxx', default=os.environ.get('CXX', 'c++'))
    parser.add_argument('--sanitize', action='store_true', help='Enable UBSan and float-cast-overflow checks')
    args = parser.parse_args()
    library = args.library.expanduser().resolve()
    if not (library/'src/Grafici.h').is_file():
        parser.error('Grafici-GFX headers not found at ' + str(library) +
                     '; initialize the Grafici-GFX submodule or use --library PATH')
    compiler = shlex.split(args.cxx)
    flags = ['-std=c++11', '-Wall', '-Wextra', '-Werror', '-pedantic', '-O1']
    if args.sanitize:
        flags += ['-fsanitize=undefined,float-cast-overflow', '-fno-sanitize-recover=all']
    includes = ['-I', str(tests/'support'), '-I', str(library/'src')]
    checks = sorted(tests.glob('*.cpp'))
    if not checks:
        raise RuntimeError('No regression sources found in ' + str(tests))
    print('Testing Grafici-GFX at ' + str(library), flush=True)
    with tempfile.TemporaryDirectory(prefix='grafici-checks-') as directory:
        for source in checks:
            binary = str(Path(directory)/source.stem)
            subprocess.run(compiler + flags + includes + [str(source), '-o', binary], check=True)
            subprocess.run([binary], check=True)
        failures = {'colormap_zero.cpp': 'requires at least one color',
                    'histogram_zero.cpp': 'requires at least one bin'}
        for name, diagnostic in failures.items():
            result = subprocess.run(compiler + ['-std=c++11'] + includes +
                                    ['-fsyntax-only', str(tests/'compile_fail'/name)],
                                    text=True, capture_output=True)
            if result.returncode == 0 or diagnostic not in result.stderr:
                raise RuntimeError('Missing expected template rejection: ' + name + '\n' + result.stderr)
    print(f'{len(checks)} runtime checks and {len(failures)} expected template rejections passed.', flush=True)


if __name__ == '__main__':
    main()

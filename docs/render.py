#!/usr/bin/env python3
"""Render the marked Grafici-GFX guide examples through File_GFX."""

import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import struct
import subprocess
import tempfile


EXAMPLES = (
    ("README.md", "beats", "beats.png", "setup"),
    ("README.md", "plot-types", "plot_types.png", "draw_plot_types"),
    ("README.md", "polar", "polar_beats.png", "draw_polar_comparison"),
    ("CONTRIBUTE.md", "hype-cycle", "hype_cycle.png", "draw_hype_cycle"),
    ("CONTRIBUTE.md", "chirp", "chirp.png", "draw_chirp"),
)

HOST = """#include <math.h>
#include <cstdlib>
#include <string>
#include "File_GFX.h"
using String = std::string;
inline void randomSeed(unsigned long seed) { std::srand(seed); }
inline long random(long high) { return high > 0 ? std::rand() % high : 0; }
#include <Grafici.h>
"""


def digest(data):
    return hashlib.sha256(data).hexdigest()


def extract(library, document, marker):
    text = (library / document).read_text(encoding="utf-8")
    pattern = r"<!-- grafici-example: " + re.escape(marker) + r" -->\s*```cpp\n(.*?)\n```"
    matches = re.findall(pattern, text, flags=re.DOTALL)
    if len(matches) != 1:
        raise ValueError(f"Expected one '{marker}' example in {document}; found {len(matches)}")
    return matches[0]


def replace_once(text, old, new):
    if text.count(old) != 1:
        raise ValueError(f"The Arduino setup changed; update the host adapter for {old!r}")
    return text.replace(old, new, 1)


def host_source(snippets):
    sketch = snippets[0]
    for header in ("math.h", "Adafruit_GFX.h", "Adafruit_ILI9341.h", "Grafici.h"):
        sketch = replace_once(sketch, f"#include <{header}>\n", "")
    sketch = replace_once(
        sketch, "Adafruit_ILI9341 gfx{10, 9};",
        'File_GFX gfx{640, 480, std::getenv("GRAFICI_IMAGE")};',
    )
    for call in ("  gfx.begin();\n", "  gfx.setRotation(3);\n"):
        sketch = replace_once(sketch, call, "")

    dispatch = []
    for index, (_, marker, _, function) in enumerate(EXAMPLES):
        call = f"{function}()" if function == "setup" else f"{function}(plot)"
        prefix = "if" if index == 0 else "else if"
        dispatch.append(f'  {prefix} (name == "{marker}") {call};')
    main = """int main(int argc, char **argv) {
  if (argc != 2) return 2;
  const std::string name(argv[1]);
""" + "\n".join(dispatch) + "\n  else return 2;\n}\n"
    return HOST + sketch + "\n" + "\n\n".join(snippets[1:]) + "\n" + main


def source_digest(library):
    result = hashlib.sha256()
    for path in sorted((library / "src").rglob("*")):
        if path.is_file():
            result.update(path.relative_to(library).as_posix().encode() + b"\0")
            result.update(path.read_bytes() + b"\0")
    return result.hexdigest()


def main():
    root = Path(__file__).resolve().parent.parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--library", type=Path, required=True,
                        help="Grafici-GFX checkout containing the marked guide examples")
    parser.add_argument("--output", type=Path, default=root / "imgs" / "guides")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "c++"))
    parser.add_argument("--sanitize", action="store_true",
                        help="check undefined behavior and float-to-integer conversions")
    args = parser.parse_args()
    library = args.library.resolve()
    if not (library / "src" / "Grafici.h").is_file():
        parser.error("--library must point to a Grafici-GFX checkout")

    snippets = [extract(library, document, marker) for document, marker, _, _ in EXAMPLES]
    args.output.mkdir(parents=True, exist_ok=True)
    output = args.output.resolve()
    flags = ["-std=c++11", "-O1", "-Wall", "-Wextra", "-Wno-unused-parameter",
             "-Wno-missing-field-initializers"]
    if args.sanitize:
        flags += ["-fsanitize=undefined,float-cast-overflow", "-fno-sanitize-recover=all"]

    images = []
    with tempfile.TemporaryDirectory(prefix="grafici-guide-") as directory:
        build = Path(directory)
        source = build / "guides.cpp"
        binary = build / "guides"
        source.write_text(host_source(snippets), encoding="utf-8")
        subprocess.run(shlex.split(args.cxx) + flags + [
            "-I", str(root), "-I", str(library / "src"), str(source),
            str(root / "Adafruit_GFX.cpp"), "-o", str(binary),
        ], check=True)
        for (document, marker, filename, _), snippet in zip(EXAMPLES, snippets):
            path = build / filename
            environment = dict(os.environ, GRAFICI_IMAGE=str(path))
            subprocess.run([str(binary), marker], env=environment, check=True)
            data = path.read_bytes()
            if data[:8] != b"\x89PNG\r\n\x1a\n" or data[12:16] != b"IHDR":
                raise ValueError(f"Missing or invalid PNG output: {path}")
            dimensions = struct.unpack(">II", data[16:24])
            if dimensions != (640, 480):
                raise ValueError(f"Unexpected image dimensions: {dimensions}")
            (output / filename).write_bytes(data)
            images.append({
                "document": document, "marker": marker,
                "code_sha256": digest(snippet.encode()), "image": filename,
                "image_sha256": digest(data), "dimensions": list(dimensions),
            })
            print(f"Rendered {filename} ({len(data)} bytes)")

    commit = subprocess.check_output(
        ["git", "-C", str(library), "rev-parse", "HEAD"], text=True,
    ).strip()
    manifest = {
        "library_commit": commit, "library_source_sha256": source_digest(library),
        "renderer_sha256": digest(Path(__file__).read_bytes()), "examples": images,
    }
    (output / "manifest.json").write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")


if __name__ == "__main__":
    main()

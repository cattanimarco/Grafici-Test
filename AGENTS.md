# Grafici-Test agent guide

Use [grafici-render](.agents/skills/grafici-render/SKILL.md) for host rendering, documentation images and backend diagnostics. [README.md](README.md) contains the runnable commands.

This repository owns host tests, rendering tools and generated plot pictures. Grafici-GFX owns the Arduino API and its design contracts. When changing the library, read that checkout's AGENTS.md and relevant skills.

Select the intended library checkout explicitly. The `Grafici-GFX` and `Grafici-Wiki` submodules are pinned dependencies; do not update their revisions as a side effect of generating images. Plot pictures must show actual library output.

Keep changes focused. Explain visual results, behavioral checks and hardware measurements separately.

# Decompiled Nextion source

Text mirror of `nspanel_beastie.HMI`, one file per page plus `Program.s.txt`
for the global startup script. The `.HMI` is binary and produces useless git
diffs — these files exist so changes are reviewable and version-controlled.

**These files are read-only output.** Edits don't flow back into the `.HMI`
automatically; the Nextion Editor on Windows is still the only thing that
can write the binary. Workflow:

1. Edit the relevant `.txt` here, push to GitHub, discuss changes.
2. On the Windows machine with Nextion Editor, open `nspanel_beastie.HMI`,
   navigate to the matching page/component, paste the updated code into
   the corresponding event handler box.
3. Compile to TFT, save HMI, commit `nspanel_beastie.HMI`,
   `nspanel_beastie.tft`, and re-run `regenerate.sh` to refresh these
   text files so the diff matches the binary.

## Regenerating

Requires Python 3.8+. From this directory:

```sh
./regenerate.sh
```

The script clones [`MMMZZZZ/Nextion2Text`](https://github.com/MMMZZZZ/Nextion2Text)
to `/tmp` (if not present), patches a Windows-only encoding name
(`ansi` → `latin-1`) so it runs on macOS/Linux, then re-decompiles
`../nspanel_beastie.HMI` into this directory.

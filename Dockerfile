# Reproducible toolchain for Thrasher: Skate and Destroy decomp. The toolchain is baked into the
# image; only your disc is mounted (read-only), so nothing in your checkout is touched.
#   docker build -t thrasher .
#   docker run --rm -v "$PWD/disc:/disc:ro" thrasher                     # extract, split, build, sha1
#   docker run --rm thrasher tools/compile_units.py                      # what public CI runs (no disc)
FROM ubuntu:24.04

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        binutils-mipsel-linux-gnu cpp git ca-certificates python3 python3-venv python3-pip \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . /src
RUN python3 toolchain/setup.py --minimal

ENTRYPOINT ["/bin/sh", "-c", "if [ $# -gt 0 ]; then exec .venv/bin/python \"$@\"; fi; set -e; .venv/bin/python tools/extract_disc.py \"$(find /disc -name '*.bin' | head -n1)\"; .venv/bin/python tools/split.py; .venv/bin/python configure.py; exec .venv/bin/python -m ninja", "--"]

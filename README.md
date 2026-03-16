# Area Infringement Warning System (AIWS)

A command-line application for Air Traffic Control (ATC) that continuously monitors
aircraft position updates and alerts Air Traffic Control Officers (ATCOs) when an
aircraft enters a restricted or prohibited zone.

Built in Modern C++17. Robustness is prioritised over features — malformed input
never crashes the system.

---

## Architecture

```
main.cpp
├── MapParser        → Parses .map file into a ZoneMap
├── RadarParser      → Parses stdin lines into AircraftPosition list
├── ZoneMap          → Holds ordered list of zones, classifies a point
├── Zone (abstract)  → Base class for RectangleZone and CircleZone
│   ├── RectangleZone
│   └── CircleZone
├── AircraftPosition → Simple struct: id, position (Point)
└── Utils            → Shared parsing helpers (parsePoint, parseRadius, parseZoneType)
```

Each class has a single responsibility. Parsers are stateless (static methods only).
Zone classification is handled entirely by `ZoneMap`, not by `main`.

---

## Design Assumptions

The assignment intentionally leaves some details open. These are the assumptions made:

- **Zone precedence**: Zones are applied in order of definition using a painter's
  algorithm. The **last-defined** zone at a given coordinate takes effect. This allows
  a `normal` rectangle to clear a previously restricted area (as shown in Example 4).
- **Boundary inclusion**: A point exactly on a rectangle edge or circle boundary is
  considered **inside** the zone.
- **Coordinate system**: Integer-only (x, y) coordinates as specified. No
  floating-point positions are supported.
- **Malformed map file**: **Fatal.** The application exits with a descriptive error
  on `stderr`. A corrupt or unreadable map cannot be trusted in a safety-critical context.
- **Malformed radar input**: **Non-fatal.** The malformed token is skipped with a
  warning to `stderr`. The system continues processing subsequent updates.
- **Empty radar lines**: Silently ignored.
- **Windows line endings**: `\r\n` line endings in input are handled gracefully.
- **Output**: Strictly follows the spec format. No output is produced for aircraft
  in normal airspace.
- **Example output vs. geometry:** The example in section 3.4 lists FR664 as prohibited,
  but the geometry places it outside the prohibited circle (distance ≈ 5.83 > radius 3).
  Classification follows geometry. The application outputs `restricted` for this case.


---

## Build

Requires CMake and a C++17 compatible compiler. All warnings are treated as errors
(`-Wall -Wextra -Werror`).

```bash
mkdir -p build
cd build
cmake ..
make
```

---

## Usage

```bash
./build/aiws <mapfile.map>
```

The application loads the zone map from the provided `.map` file, then reads aircraft
position updates continuously from `stdin` until EOF.

### Interactive
```bash
./build/aiws maps/example3.map
# Type radar data manually, e.g.:
FR664(10,2) GB3265(4,9)
```

### Pipe (single line)
```bash
echo "FR664(5,6) GB3265(4,9)" | ./build/aiws maps/example3.map
```

### File redirection
```bash
./build/aiws maps/example3.map < radar_data.txt
```

---

## Map File Format

```
<type> <shape> - <args>
```

| Field  | Values                          |
|--------|---------------------------------|
| type   | `normal` `restricted` `prohibited` |
| shape  | `rectangle` `circle`            |
| args   | Rectangle: `(x1,y1) (x2,y2)` — top-left, bottom-right |
|        | Circle: `(cx,cy) radius`        |

### Example map
```
restricted rectangle - (0,0) (10,10)
prohibited circle - (5,5) 3
normal rectangle - (0,6) (10,8)
```

---

## Radar Input Format

Multiple aircraft per line, separated by whitespace:
```
FR664(10,2) GB3265(4,9) NO5521(3,3)
```

---

## Expected Output

```
GB3265 is in restricted zone at (4,9)
FR664 is in prohibited zone at (5,6)
```

Only restricted and prohibited infringements are printed. Normal airspace produces
no output.

## Testing

### Build

```bash
cd build && make && cd ..
```

### End-to-End Tests

**Test 1 — Aircraft in normal airspace (silent)**
```bash
echo "XX001(50,50)" | ./build/aiws maps/example3.map
```
Expected: No output.

---

**Test 2 — Malformed radar token**
```bash
echo "BADTOKEN XX001(4,4)" | ./build/aiws maps/example3.map 2>/dev/null
```
Expected: `XX001 is in prohibited zone at (4,4)` — warning for `BADTOKEN` goes to stderr only, valid token is still processed.

---

**Test 3 — Empty radar line**
```bash
echo "" | ./build/aiws maps/example3.map
```
Expected: No output, no crash.

---

**Test 4 — Zone override (painter's algorithm)**

Create `maps/example4.map`:
```
restricted rectangle - (0,0) (10,10)
prohibited circle - (5,5) 3
normal rectangle - (0,6) (10,8)
```
```bash
echo "AA001(3,7)" | ./build/aiws maps/example4.map
```
Expected: No output — `normal` zone overrides the `restricted` zone beneath it.

---

**Test 5 — Missing map file**
```bash
./build/aiws maps/nonexistent.map || echo "AIWS failed to start!"
```
Expected: Descriptive error message on stderr, followed by `AIWS failed to start!` — confirming the application exits with a non-zero code on a bad map file.



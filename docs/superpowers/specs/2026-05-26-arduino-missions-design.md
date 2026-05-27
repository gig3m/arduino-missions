# Arduino Missions — Design Spec

**Date:** 2026-05-26
**Author:** Kyle Arrington (with Claude)
**Status:** Approved design, ready for implementation planning

## Purpose

Replace the poorly-formatted, adult-pitched Elegoo PDF tutorial with a kid-friendly,
printable lesson set that a 9-year-old can work through **mostly on his own** (with a
parent nearby for the hard parts), using the **Elegoo UNO R3 Super Starter Kit**.

The source PDF (`ELEGOO Super Starter Kit for UNO V1.0.2023.05.05`, English) is
technically complete but unusable for a 9-year-old: a 13-page obsolete software-install
chapter, adult reading level, broken justified typography that smashes words together,
code shown as tiny cut-off screenshots, no project payoffs, no success checkpoints, and
no troubleshooting written for a kid. Its genuinely good assets — the component
progression and the Fritzing-style wiring diagrams — are worth keeping.

## Goals & success criteria

- A 9-year-old can read a lesson sheet and build the circuit **without an adult reading it to him**.
- He gets a working result **quickly** and rarely gets stuck; when he does, a kid-level
  troubleshooting box gets him unstuck without pulling in a parent.
- Each cluster of skills **pays off in something he built that does something** (a traffic
  light, a nightlight, a distance alarm) — not a parade of isolated components.
- Sheets are **printable** and live at the workbench; the computer is used only to load code.

## Key decisions (locked)

| Decision | Choice |
|---|---|
| Working mode | Mostly solo, parent nearby → 9yo reading level, very self-explanatory, strong checkpoints + troubleshooting |
| Coding approach | **Load ready-made code, then tweak it.** He opens a pre-written sketch, uploads, it works; lessons guide specific tweaks. No typing sketches from scratch. |
| Format | **Printable mission sheets/booklet.** Clean source that prints well; one self-contained sheet/spread per lesson. Readable on screen too. |
| Structure | **Mission-based with project payoffs** (Approach A) |
| Environment | **Linux.** Arduino IDE already installed. Port = `/dev/ttyUSB0` or `/dev/ttyACM0`. Most common upload failure = user not in `dialout` group. |
| Wiring visuals | Reuse the kit's Fritzing-style breadboard renders (regenerate in Fritzing only if a custom diagram is needed). |
| Diagrams-as-code (Mermaid) | **Not adopted for now.** |

## The mission arc

Mission 0 + 7 missions, folding all 25 kit lessons in. Drier/abstract kit lessons become
optional **bonus** builds so the child never has to slog through one to keep moving.

| Mission | Skills taught | Build payoff | Kit lessons |
|---|---|---|---|
| **0 · How Your Robot Brain Works** *(no wiring)* | Plug in; pick Board + Port (Linux); what Upload does; the load-and-tweak loop; meet the Serial Monitor | Blink the built-in light, then make it faster | 1, 2 |
| **1 · First Light** | LED + resistor on breadboard; brightness; breadboard basics | Traffic light (R/Y/G) · *bonus:* RGB color mixing | 3, 4 |
| **2 · You're in Control** | Button (digital in); potentiometer (analog in) | Push-button lamp + knob dimmer | 5 |
| **3 · Make Some Noise** | Active vs passive buzzer; playing tones | Button mini-piano / alarm | 6, 7 |
| **4 · Sensing the World** | Light sensor, tilt switch, ultrasonic distance, temp/humidity; reading values in Serial Monitor | Automatic nightlight + distance alarm | 8, 18, 10, 11 |
| **5 · Words & Numbers on Screen** | LCD "hello"; live sensor readout | Mini weather station (temp → LCD) · *bonus:* 7-seg counter, 8-LED bar (74HC595) | 14, 15, 19, 20, 16 |
| **6 · Things That Move** | Servo sweep; DC motor + fan; relay | Wave-on-command servo + push-button fan · *bonus:* stepper | 9, 21, 22, 23 |
| **7 · Remote Control** | IR remote + receiver; joystick | Remote-controlled light/fan · *bonus:* stepper-by-remote | 13, 12, 24 |

Serial Monitor (kit Lesson 17) is treated as a cross-cutting tool introduced in Mission 0
and reused in Mission 4, not its own lesson.

## Lesson-sheet template

Every build sheet uses the same skeleton (sections scale to the build; small builds stay short):

1. **🎯 What you're making** — one-line hook.
2. **🧰 Grab these parts** — checklist with quantities.
3. **🔌 Build it** — numbered steps + the wiring picture.
4. **💻 Load the code** — which sketch file to open and upload.
5. **✅ It works when…** — concrete, observable success.
6. **🔧 Not working? Try…** — kid-level checklist (Linux port/`dialout` note where relevant).
7. **🔬 Now try this** — 1–3 guided tweaks (the load-and-tweak core).
8. **💡 What's happening** — 2–3 plain sentences.
9. *(small)* **Grown-up's corner** — the deeper "why" for the parent.

## Production details

- **Source format:** Markdown, one self-contained sheet per lesson, authored to print
  cleanly as a booklet and remain readable on screen.
- **Wiring images:** reuse the kit's breadboard renders (extracted from the source PDF /
  bundled assets).
- **Code:** one tidy, well-commented sketch per build, derived from the kit's bundled
  `.ino` files, cleaned up for readability. Child opens and uploads; does not type from scratch.
- **Home:** `~/projects/arduino-missions/` (git-tracked).
- **Source material:** extracted English tutorial + bundled code/libraries currently at
  `~/Downloads/elegoo_extract/` (relevant assets to be copied into the project).

## Pilot-first rollout

Build **Mission 0 + Mission 1 only** first. Have the child actually use them, then tune the
template, reading level, and visuals to what lands with him **before** producing Missions 2–7.

## Out of scope

- Software-install instructions (IDE already set up).
- Typing sketches from scratch / teaching C++ syntax formally.
- Mermaid or other diagrams-as-code (deferred).
- Windows/Mac instructions (Linux only).
- A block-based/simulator track (Tinkercad, etc.).

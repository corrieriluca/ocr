# Cogito OCR

A simple optical character recognition system made for the final S3 project at EPITA.

# Building

## Dependencies

- SDL
- GTK

## Compiling

Type `make all` in the repository root to build the OCR with its GUI.

You can type `make cli` to build the OCR without its GUI.

You can type `make clean` when you're done.

# Usage

You can type `./ocr.out` to execute the program (when built with its GUI).

Type `./ocr.out <path_to_image>` to run the program when built without the GUI.

In the `tmp` folder you can find debug images (displayed in the GUI Advanced
window) showing the different steps of the process (grayscale, binarization and
segmentation)...

# Authors
- Alexis Boissière
- Alexis Boyadjian
- Valentin Cambazard
- Luca Corrieri

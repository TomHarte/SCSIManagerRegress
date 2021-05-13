# SCSIManagerRegress

## What?

This tool accepts a Macintosh drive image — conventionally labelled a .dsk file, and often used with emulators such as Basilisk II — and overwrites whatever storage driver it has on it with an early-68k-compatible version.

## Why?

I found online drive images containing bare versions of various old versions of the Macintosh System software, intended for use on a real Macintosh via a device such as scsi2sd.

These images were empirically not usable on older Macs*. Poking around inside the drive images revealed that they had embedded SCSI Manager 4.3-compatible drivers. SCSI Manager 4.3 is a Quadra-era innovation. Being suspicious I tried replacing it with the driver written by much older versions of Apple HD SC Setup. I found this to fix the problem.

I strongly suspect that machines with older versions of the SCSI Manager in ROM cannot boot from drives with a SCSI Manager 4.3-style driver.

\* tested in emulation on a Mac Plus and against real hardware on a Powerbook 180.

## Limitations

This is a dumb tool, thrown together very hastily. It isn't smart enough to resize an existing driver partition or to create one if none exists. It will likely do the wrong thing if multiple driver partitions exist.

It requires C++11.
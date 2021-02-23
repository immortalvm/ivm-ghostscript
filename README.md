# Ghostscript for iVM

In order to be able to render stored PDF files, the virtual machine needs the ability to render PDF files. To
achieve this we adapted the Ghostcript open source interpreter for the Postscript and PDF languages.
With some modifications, Ghostscript can be run on the ivm64 machine architecture, with Newlib as the C
library.

## Version of Ghostscript
This is Ghostscript 9.52, modified to run on ivm64.

## Prerequisites
The projects `ivm-compiler` and `ivm-implementations` must be installed and working. For performance reasons it is necessary to use the C implementation of the ivm64 virtual machine to execute the binary.

Note that below, `ivm` refers to the standard implementation of ivm64 and `vm` to the C implementation. For simplicity we assume here that both are in directories in PATH.

## Copy PDF input document
Since GS can't read the PDF document from standard input, we need to put it into romfs, which is embedded in the executable.

    cd ghostscript-9.52
    cp -i <myPDFdoc>.pdf Resource/Init/Input.pdf

## Build Ghostscript for ivm64
    CC=ivm64-gcc CFLAGS="-DGS_NO_FILESYSTEM -DCMS_NO_PTHREADS" ./configure --host=ivm64 --disable-threading --disable-contrib --disable-fontconfig --disable-dbus --disable-cups --with-drivers=ivm64
    make
    ivm as --noopt bin/gs

## Generate command line arguments file
    echo "bin/gs -sDEVICE=ivm64 -dGraphicsAlphaBits=4 -dTextAlphaBits=4 -r300x300 -dNOPAUSE -dBATCH -dSAFER -sOutputFile=- Input.pdf" | tr '[:space:]' '\000' > args

## Run Ghostscript:
    time vm -o /tmp -a args -m 100000000 bin/gs.b

The output can be found as XXXXXXXX.png files in `/tmp`.

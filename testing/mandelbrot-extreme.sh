#!/bin/sh

./bf testing/mandelbrot-extreme.b |
{
    echo 'P5'
    echo '1024 768'
    echo '255'
    sed 's/......//' | tr ' ' '@' | tr -d '\012'
} | ppmnorm | pnmtopng > mandelbrot-extreme.png
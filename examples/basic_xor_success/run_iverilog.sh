#!/bin/sh

mkdir -p iverilog_out
cd iverilog_out
iverilog -gspecify -s tb_basic_xor -o run ../*.v
./run

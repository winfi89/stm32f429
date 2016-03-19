#!/usr/bin/python
# -*- coding: utf-8 -*-
"""
Created on Sat Mar 19 21:44:16 2016

@author: z80
"""


import sys

l = len( sys.argv )
#if ( l < 2 ):
#    print( "Please, provide file as an argument..." )
#    exit( 0 )
fname = "./stm32f429-disco.dtb" #sys.argv[1]
f = open( fname, "rb" )

maxLen = 70;
qty = 0;
stri = "uint8_t dev_tree[] = { ";
if f:
    try:
        b = f.read( 1 )
        if b:
            qty += 1;
            stri += "0x{:02x}".format( ord(b) );
            if len(stri) >= maxLen:
                print( stri );
                stri = "";
        while b:
            b = f.read( 1 )
            if b:
                qty += 1
                stri += ", 0x{:02x}".format( ord(b) );
                if len(stri) >= maxLen:
                    print( stri );
                    stri = "";
    finally:
        f.close()
print( "    };" )
print( "int dev_tree_sz = {};".format( qty ) )
#!/usr/bin/python3

import sys
import subprocess

# project invariants
targets = [
    'felide-core',
    'felide-gtk3',
    'felide-win'
]

buildDir = './build/gcc-x64/'
confs = ['debug', 'release']

# command line options
action = sys.argv[1]
target = sys.argv[2]

def invoke(args):
    return subprocess.check_output(['ls', '-l']).decode('ascii'))

if action=="build":
    configurations = ["debug", "release"]

    for conf in configurations:
        output = invoke(['ls', '-l'])
        
elif action=="run":
    pass
else:
    print("Unknown option: ", action)

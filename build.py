# Must use Python 3
import os

CompilerName   = 'g++'
CppStandard    = '-std=c++11'
ExecutableName = 'breeze'

# Debug mode
DebugMode = False

# Add here all the files you want to be compiled.
files = [
	'Main.cpp',
	'Tokenizer.cpp',
	'Arguments.cpp',
	'Gen.cpp',
]

# Include and external libs paths
paths = [
	'',
]

# Compilation falgs
rflags = [
	'-Wall',
	'-Wextra',
	'-O2',
	'-s',
	'-lpthread',
]

dflags = [
	'-Wall',
	'-Wextra',
	'-g',
	'-lpthread',
]

# The string is going to be executed
OutString = f'{CompilerName} {CppStandard} -o {ExecutableName}'

# add debugs
if DebugMode:
	for f in dflags:
		OutString += ' '  + f
else:
	for f in rflags:
		OutString += ' '  + f

# Add the files into the 'OutString'
for fp in files:
	OutString += ' ' + fp

for p in paths:
	OutString += ' '  + p


# Execute the OutString
print(OutString)
os.system(f"{OutString} && {ExecutableName}")
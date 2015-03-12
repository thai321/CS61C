# Build file for CS61C Spring 2013 Project 2 - SmallWorld
# You should not need to edit this file.

# This file requires GNU make and depends on paths on instruction machines.

####

## Variables

# Source files (java code). wildcard selects all files matching a pattern.
SOURCES = $(wildcard *.java)
# Output JAR file
TARGET = sw.jar
# Extra JARs to have on the classpath when compiling.
CLASSPATH = /home/ff/cs61c/hadoop/hadoop-core.jar:/home/ff/cs61c/hadoop/lib/commons-cli.jar
# javac command to use
JAVAC = javac -g -deprecation -cp $(CLASSPATH)
# jar command to use
JAR = jar

## Make targets

# General form is target: dependencies (targets or files), followed by
# commands to run to build the target from the dependencies.

# Default target.
all: $(TARGET)

$(TARGET): classes $(SOURCES)
	$(JAVAC) -d classes $(SOURCES)
	$(JAR) cf $(TARGET) -C classes .

classes:
	mkdir classes

clean:
	rm -rf classes $(TARGET) *-out

runhadoop:
	hadoop jar sw.jar SmallWorld ~cs61c/proj2data/ring4.seq output-out 1

runbighadoop:
	hadoop jar sw.jar SmallWorld ~cs61c/proj2data/cit-HepPh.sequ output-out 10000

.PHONY: clean all

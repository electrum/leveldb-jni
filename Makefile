LEVELDB=$(HOME)/src/leveldb-cpp

all:
	javah -jni \
	    -classpath target/classes \
	    -o src/main/c++/org/acz/leveldb/LevelDbNative.h \
	    org.acz.leveldb.LevelDbNative
	g++ \
	    -Wall -Werror \
	    -o libleveldbnative.so \
	    -shared \
	    -I$(JAVA_HOME)/include \
	    -I$(LEVELDB)/include  \
	    -L$(LEVELDB) -lleveldb \
	    src/main/c++/org/acz/leveldb/LevelDbNative.cpp

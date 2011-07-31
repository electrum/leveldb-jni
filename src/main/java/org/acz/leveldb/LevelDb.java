package org.acz.leveldb;

import java.io.Closeable;
import java.util.Iterator;

public interface LevelDb
        extends Closeable, Iterable<LevelDb.Entry>
{
    @Override
    void close()
            throws LevelDbException;

    byte[] get(byte[] key)
            throws LevelDbException;

    void put(byte[] key, byte[] value)
            throws LevelDbException;

    void delete(byte[] key)
            throws LevelDbException;

    void writeBatch(WriteBatch batch)
            throws LevelDbException;

    @Override
    Iterator<Entry> iterator();

    Iterator<Entry> iterator(byte[] keyStart);

    interface WriteBatch
    {
        void put(byte[] key, byte[] value);

        void delete(byte[] key);

        void clear();
    }

    interface Entry
    {
        byte[] getKey();

        byte[] getValue();
    }
}
